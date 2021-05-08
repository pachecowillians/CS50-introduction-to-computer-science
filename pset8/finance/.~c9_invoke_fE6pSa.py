import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# API_KEY
# pk_ad50291c627544d69313efd0e806d82c

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Index tab
    # Getting the symbol and sum of shares of each stock that the user has
    stocks = db.execute(
        "select symbol, sum(shares) as shares from operations where id_user = :user group by symbol having sum(shares) > 0",
        user=session["user_id"])
    # Getting the total cash of user
    cash = db.execute("select cash from users where id = :user", user=session["user_id"])[0]['cash']
    # Calculating the total money invested
    total = cash
    # For each stock
    for stock in stocks:
        # Get the stock informations in real time
        look = lookup(stock['symbol'])
        # Create an field price and it recives te price of the moment of the stock
        stock['price'] = look['price']
        # Create a field name and store the name of stock with that symbol
        stock['name'] = look['name']

        # Stoore the total value in that stocks that the user has
        stock['total'] = stock['price'] * stock['shares']
        # Increment the total sum
        total += stock['total']

        # Convert to usd notation the price
        stock['price'] = usd(stock['price'])
        # Convert to usd notation the total
        stock['total'] = usd(stock['total'])
    # Convert to usd notation the price
    total = usd(total)
    # Convert to usd notation the cash of user
    cash = usd(cash)
    # Call the template with parameters
    return render_template("index.html", stocks=stocks, total=total, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # Buy tab
    # If call the route via get
    if request.method == "GET":
        # Just call the template to user fill the informations
        return render_template("buy.html")
    else:
        # Recive the symbol and shares informations of the form that was submitted
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        # Checking if there is some field blank
        if not symbol:
            return apology("The symbol is blank")
        elif not shares:
            return apology("The shares number is blank")
        # The number typed must be positive
        elif int(shares) <= 0:
            return apology("The shares number must be positive")
        else:
            # Getting the informations about the stock with that symbol
            stock = lookup(symbol)
            # If the symbol doesn't exists
            if not stock:
                return apology("The symbol doesn't exist")
            else:
                # Get the total cash of user
                moneyUser = db.execute("select cash from users where id = :user", user=session["user_id"])[0]['cash']
                # Calc the total value of shares
                totalPrice = float(shares) * float(stock['price'])
                # If the user doesn't have enough money
                if float(moneyUser) < float(totalPrice):
                    return apology("You don't have enough money")
                else:
                    # Store in database the operation of buy
                    # Store stock['symbol'] because it is a pattern
                    # Store the price of each share when bought
                    db.execute("insert into operations (id_user, symbol, shares, price) values(:user, :symbol, :shares, :price)",
                                user=session["user_id"], symbol=stock['symbol'], shares=shares, price=stock['price'])
                    # Discount the money of user cash
                    db.execute("update users set cash = cash - :totalPrice where id = :user",
                                totalPrice=totalPrice, user=session["user_id"])
                    # Flash a message of sucefull bough
                    flash("Bought!")
                    # Redirect the user to home
                    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Get the symbol, shares, price and date of every operation that the user done
    operations = db.execute("select symbol, shares, price, date from operations where id_user = :user", user=session["user_id"])
    for operation in operations:
        # Convert the price to usd format
        operation['price'] = usd(float(operation['price']))
    # Render the history template and pass the list of operations
    return render_template("history.html", operations=operations)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # Quote tab
    if request.method == "GET":
        # if is get, just render the template
        return render_template("quote.html")
    else:
        # Get the symbol from the form that the user sumbitted
        symbol = request.form.get("symbol")
        # If the field was blank
        if not symbol:
            return apology("The symbol is blank")
        else:
            # Get the informations of that stock in real time
            value = lookup(symbol)
            # Convert the value to usd notation
            value['price'] = usd(value['price'])
            # Render the template with the list of information about the stock
            return render_template("quoted.html", value=value)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Register tab
    # If just load the form
    if request.method == "GET":
        return render_template("register.html")
    else:
        # Get the values of fields that the user sumbmitted
        name = request.form.get("username")
        passw = request.form.get("password")
        conf = request.form.get("confirmation")
        # Check if the fields was blank
        if not name:
            return apology("The username is blank")
        elif not passw:
            return apology("The password is blank")
        elif not conf:
            return apology("The confirmation of password is blank")
        # If the passwords doesn't match
        elif passw != conf:
            return apology("The passwords doesn't match")
        else:
            # Try to find any user with the same username
            user = db.execute("select * from users where username = :name", name=name)
            # If the username already exists
            if len(user) > 0:
                return apology("The username already exists")
            else:
                # Insert the new user hashing the password
                id_user = db.execute("insert into users(username, hash) values(:user, :passw)",
                                     user=name, passw=generate_password_hash(passw))
                # Iniciallize the session to get the user logged in
                session["user_id"] = id_user
                # Flash a message that everything is ok
                flash("Registered!")
                # Return to home
                return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # Sell tab
    # If just render the template
    if request.method == "GET":
        # Select a list of symbols of operations that the user effetuated and the sum of total shares has a positive number
        symbols = db.execute(
            "select symbol from operations where id_user = :user group by symbol having sum(shares) > 0 ", user=session["user_id"])
        # Render the total templates with the symbols listed
        return render_template("sell.html", symbols=symbols)
    else:
        # Get the values that was submitted by the user
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        # If any field was blank
        if not symbol:
            return apology("The symbol is blank")
        elif not shares:
            return apology("The shares number is blank")
        else:
            # Get the number of shares that the user has
            sumShares = db.execute("select sum(shares) as shares from operations where id_user = :user and symbol = :symbol",
                                   user=session["user_id"], symbol=symbol)[0]['shares']
            # If for some reason he has not this number of shares anymore
            if sumShares - int(shares) < 0:
                return apology("You don't have enough shares")
            else:
                # Get the actual value of the share
                value = lookup(symbol)
                # Create an operation of sell shares
                db.execute("insert into operations (id_user, symbol, shares, price) values(:user, :symbol, :shares, :price)",
                           user=session["user_id"], symbol=value['symbol'], shares=(-1)*int(shares), price=value['price'])
                # Update the cash of user to increase the value owned from sell shares
                db.execute("update users set cash = cash + :totalPrice where id = :user",
                           totalPrice=float(shares) * float(value['price']), user=session["user_id"])
                # Flash a message to say that the operation was successfull
                flash("Sold!")
                # Go back to home
                return redirect("/")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
