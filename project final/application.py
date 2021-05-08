from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from functools import wraps
from datetime import date
import datetime
from datetime import datetime
from datetime import timedelta
import calendar

from werkzeug.security import check_password_hash, generate_password_hash

app = Flask(__name__)

app.config["TEMPLATES_AUTO_RELOAD"] = True

app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///tasks.db")

def login_required(f):
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function

def apology(message):
    return render_template("apology.html", message=message)

@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    dateToday = date.today()
    if request.method == "POST":
        datePrev = request.form.get("datePrev")
        dateNext = request.form.get("dateNext")
        dateTodayForm = request.form.get("dateToday")
        if not dateTodayForm and datePrev:
            datePrev = datetime.strptime(datePrev, '%Y-%m-%d')
            dateToday = (datePrev + timedelta(days=-1))
        elif not dateTodayForm:
            dateNext = datetime.strptime(dateNext, '%Y-%m-%d')
            dateToday = (dateNext + timedelta(days=+1))

    today = calendar.day_name[dateToday.weekday()]  #'Wednesday'
    today = f'%{today}%'
    dateToday = date(dateToday.year, dateToday.month, dateToday.day)
    tasks = db.execute("select * from task where ((type = 'r' and days like :dayweek) or (type = 'u' and date = :date)) and id_user = :user and id not in (select id_task from task_done where date = :date) order by time", date=dateToday, dayweek=today, user=session["user_id"])
    done = db.execute("select * from task where ((type = 'r' and days like :dayweek) or (type = 'u' and date = :date)) and id_user = :user and id in (select id_task from task_done where date = :date) order by time", date=dateToday, dayweek=today, user=session["user_id"])

    return render_template("index.html", tasks=tasks, done=done, today=dateToday)

@app.route("/done", methods=["POST"])
@login_required
def done():
    idTask = request.form.get("task")
    dateForm = request.form.get("date")
    if not dateForm:
        dateForm = date.today()
    db.execute("insert into task_done(id_task, date) values(:idtask, :date)", idtask=idTask, date=dateForm)
    return redirect("/")

@app.route("/undo", methods=["POST"])
@login_required
def undo():
    idTask = request.form.get("task")
    dateForm = request.form.get("date")
    if not dateForm:
        dateForm = date.today()
    db.execute("delete from task_done where id_task = :idtask and date = :date", idtask=idTask, date=dateForm)
    return redirect("/")

@app.route("/delete", methods=["POST"])
@login_required
def delete():
    idTask = request.form.get("task")
    db.execute("delete from task where id = :idtask", idtask=idTask)
    flash("Task deleted!")
    return redirect("/")

@app.route("/edit", methods=["GET", "POST"])
@login_required
def edit():
    if request.method == "GET":
        #Via GET
        idTask = request.args.get("task")
        task = db.execute("select * from task where id = :idtask", idtask=idTask)[0]
        print(task)
        return render_template("edit.html", task=task)
    else:
        taskId = request.form.get("id")
        name = request.form.get("taskname")
        description = request.form.get("description")
        option = request.form.get("option")
        time = request.form.get("time")
        date = request.form.get("date")
        sunday = request.form.get("sunday")
        monday = request.form.get("monday")
        tuesday = request.form.get("tuesday")
        wednesday = request.form.get("wednesday")
        thursday = request.form.get("thursday")
        friday = request.form.get("friday")
        saturday = request.form.get("saturday")

        if not name:
            return apology("The name is blank")
        elif not option:
            return apology("The task type is blank")
        elif not time:
            return apology("The time is blank")
        elif option=="unique" and not date:
            return apology("The date is blank")
        elif option=="recurrent" and not sunday and not monday and not tuesday and not wednesday and not thursday and not friday and not saturday:
            return apology("The day of week is blank")
        else:
            if not description:
                description = None
            if option == "unique":
                db.execute("update task set name = :name, description = :desc, time = :time, date = :date, type = :t where id = :taskid", name=name, desc=description, time=time, date=date, t='u', taskid=taskId)
                flash("The changes has been saved!")
                return redirect("/")
            else:
                s = [sunday] + [monday] + [tuesday] + [wednesday] + [thursday] + [friday] + [saturday]
                days = ""
                for d in s:
                    if d is not None:
                        days += f'{d} '
                db.execute("update task set name = :name, description = :desc, time = :time, days = :days, type = :t where id = :taskid", name=name, desc=description, time=time, days=days, t='r', taskid=taskId)
                flash("The changes has been saved!")
                return redirect("/")

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("The username is blank")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("The password is blank")

        # Query database for username
        rows = db.execute("SELECT * FROM user WHERE name = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["password"], request.form.get("password")):
            return apology("Invalid username and/or password")

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        session["user_name"] = request.form.get("username").upper()

        # Redirect user to home page
        flash("Welcome!")
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
            user = db.execute("select * from user where name = :name", name=name)
            # If the username already exists
            if len(user) > 0:
                return apology("The username already exists")
            else:
                # Insert the new user hashing the password
                id_user = db.execute("insert into user(name, password) values(:user, :passw)",
                                     user=name, passw=generate_password_hash(passw))
                # Iniciallize the session to get the user logged in
                session["user_id"] = id_user
                session["user_name"] = name.upper()
                # Flash a message that everything is ok
                flash("Registered!")
                # Return to home
                return redirect("/")

@app.route("/changepassword", methods=["GET", "POST"])
@login_required
def changepassword():
    # Change Password tab
    # If just render the template
    if request.method == "GET":
        # Render the template to change password
        return render_template("changePassword.html")
    else:
        # Get the values that was submitted by the user
        oldPass = request.form.get("oldpass")
        newPass = request.form.get("newpass")
        conf = request.form.get("confirmation")
        # If the fields was blank
        if not oldPass:
            return apology("The old password is blank")
        elif not newPass:
            return apology("The new password is blank")
        elif not conf:
            return apology("The confirmation of password is blank")
        # If the new password is equal to the old one
        elif oldPass == newPass:
            return apology("The new password can't be equal to the old password")
        # If the confirmation password is diferent than new password
        elif conf != newPass:
            return apology("The passwords doesn't match")
        else:
            # Get the original password
            old = db.execute("select password from user where id = :user", user=session["user_id"])[0]['password']
            # Verify if the passwords match
            if not check_password_hash(old, oldPass):
                return apology("The old password is wrong")
            else:
                # Update the table and set the new password
                db.execute("update user set password = :passwd where id = :user",
                           passwd=generate_password_hash(newPass), user=session["user_id"])
                # Display a message indicating that the password was changed sucefully
                flash("Password changed!")
                # Go back to home
                return redirect("/")

@app.route("/add", methods=["GET", "POST"])
@login_required
def add():
     # Change Password tab
    # If just render the template
    if request.method == "GET":
        # Render the template to change password
        return render_template("add.html")
    else:
        name = request.form.get("taskname")
        description = request.form.get("description")
        option = request.form.get("option")
        time = request.form.get("time")
        date = request.form.get("date")
        sunday = request.form.get("sunday")
        monday = request.form.get("monday")
        tuesday = request.form.get("tuesday")
        wednesday = request.form.get("wednesday")
        thursday = request.form.get("thursday")
        friday = request.form.get("friday")
        saturday = request.form.get("saturday")

        if not name:
            return apology("The name is blank")
        elif not option:
            return apology("The task type is blank")
        elif not time:
            return apology("The time is blank")
        elif option=="unique" and not date:
            return apology("The date is blank")
        elif option=="recurrent" and not sunday and not monday and not tuesday and not wednesday and not thursday and not friday and not saturday:
            return apology("The day of week is blank")
        else:
            if not description:
                description = None
            if option == "unique":
                db.execute("insert into task(name, description, time, date, type, id_user) values(:name, :desc, :time, :date, :t, :user)", name=name, desc=description, time=time, date=date, t='u', user=session["user_id"])
                return redirect("/")
            else:
                s = [sunday] + [monday] + [tuesday] + [wednesday] + [thursday] + [friday] + [saturday]
                days = ""
                for d in s:
                    if d is not None:
                        days += f'{d} '
                db.execute("insert into task(name, description, time, days, type, id_user) values(:name, :desc, :time, :days, :t, :user)", name=name, desc=description, time=time, days=days, t='r', user=session["user_id"])
                return redirect("/")
            flash("Task added!")

@app.route("/search", methods=["GET", "POST"])
@login_required
def search():
    if request.method == "GET":
        return render_template("search.html")
    else:
        name = request.form.get("task")
        dateForm = request.form.get("date")
        if not name and not date:
            return apology("At least one field must be filled")
        else:
            tasks = []
            post = True
            if name:
                name = f'%{name}%'
                tasks = db.execute("select * from task where name like :name and id_user = :user and ((type='u' and id not in (select id_task from task_done)) or ( type='r' and id not in (select id_task from task_done where date = :date))) order by time, date", name=name, user=session["user_id"], date=date.today())
                done = db.execute("select * from task where name like :name and id_user = :user and ((type='u' and id in (select id_task from task_done)) or ( type='r' and id in (select id_task from task_done where date = :date))) order by time, date", name=name, user=session["user_id"], date=date.today())

                return render_template("search.html", tasks=tasks, post=post, done=done)
            else:
                newDate = datetime.strptime(dateForm, '%Y-%m-%d')
                day = calendar.day_name[newDate.weekday()]  #'Wednesday'
                day = f'%{day}%'

                tasks = db.execute("select * from task where ((type = 'r' and days like :dayweek) or (type = 'u' and date = :date)) and id_user = :user and id not in (select id_task from task_done where date = :date) order by time", date=dateForm, dayweek=day, user=session["user_id"])
                done = db.execute("select * from task where ((type = 'r' and days like :dayweek) or (type = 'u' and date = :date)) and id_user = :user and id in (select id_task from task_done where date = :date) order by time", date=dateForm, dayweek=day, user=session["user_id"])

                return render_template("search.html", tasks=tasks, post=post, done=done)