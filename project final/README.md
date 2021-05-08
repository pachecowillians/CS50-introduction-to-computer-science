Project name: Tasks
Author: Willian Pacheco Silva
Motivation:
    The main idea of this project is create a website to help people to organize the tasks of everyday. This is one problem that i face sometimes.
    I used many task managers but something is always missing. Sometimes it was too complex, sometimes was too simple. So, i created my own website where i can store my tasks and organize it by day as i want.
Tools:
    This website was developed using the Python, sqlite3 database (with SQL), HTML, CSS, javascript, Bootstrap and Jinja.
    The Python was used to connect with database, manipulate the result of querys, validate inputs, create routes and deal with date and week days.
    The SQL was used to store(create), read, update and delete (CRUD) data from the sqlite database and manipulate it (creating tables and setting the primary keys, foreign keys and 'not null' fields).
    The HTML and CSS was used to create the structure and style of the pages respectively. In this project, a layout template was created and the others HTML pages just extends it and added the HTML that was necessary.
    The Javascript was used mainly on the "Add tasks" page. In this page, while selecting between unique or recurring event, the Javascript enable, disable and reset fields based on what the user should fill. This prevent some errors.
    The Bootstrap was used to develop the HTML pages easily with a great design. With this framework the site is more harmonic and minimalistic.
    The Jinja was used to fill the HTML pages with information. With this feature is possible to use loops, conditionals and commands to display the value of an variable.
Functionalities:
    Login:
        This project was developed to be used by everyone on internet. To make this possible, the website has a user validation.
        Everybody can create an account, just need an username and a password. After register, the user can access the main menu of the site.
        To store passwords, it was used a hash password to make the system more safe.
    Change the password:
        This website allows the user to change his password. Maybe he needs to change the password for a more complex one, or for other reason, and he can do it with this resourse.
    Homepage:
        The homepage shows to the user a table with all the tasks he has to do today and the tasks that have already been done.
        Besides that, the user can navegate trough the days before or after the current day to see the tasks of each day.
    Add tasks:
        As the name describes, this function allows the user to create a new task.
        The tasks on this site was divided in two categories. Are they:
            Unique tasks: This is a task that only need to be done one time. The user will do the task in a specific day and hour.
            Recurrent tasks: This is a task that will be repeated in some days of week. This is how the website deals with some routines of the user. Recurrent tasks can be, for example, eat lunch everyday 12 o'clock, or go to the church every sunday at 8:40, or play soccer every monday, friday and saturday at 19 o'clock. This functionality helps the user to manage his routine tasks.
    Edit tasks:
        Here, the user can edit the tasks that were created and fix or change some information to help him to get better organized.
    Remove tasks:
        The user also can delete tasks. This may help him to organize his tasks.
    Search for tasks:
        This functionality allow the user to search for tasks by name, or by a day. The user can search for all the tasks that contains the word "wash" or he can search for all the tasks of day 2020-10-02. This recourse is good to plan the days or the weeks, and see how busy you are each day.
Handling errors:
    To make the website consistent, safe and fluid, every input was verifyed. Using this technique, the user can not run querys on the database and get access to informations that he should not. The user also can't store inconsistent informations on the database. He must fill the number fields with numbers, time with time, date with date and so on.
    When the user leaves a required field in blank, he is notified and he can not continue until input the correct value.
    The Javascript was used to enable and disable some fields to prevent users from fill a wrong field.
    SQL injection also was trated, executing the querys by a parameterized string.
    When the delete button is pressed, an alert message is shown to the user confirm that he really want to delete that task. This feature prevents the user to delete a task unintentionally.
    In the most part of the site the POST method was used to send information from one page to another. Using POST, the user can't manipulate the datas on the URL like is possible to do with GET. This makes the site safer.
Conclusion:
    This site works with a simple idea, but it was implemented with many functionalities to make it as useful as possible.
    On this project was used all the features studied on this course, like HTML, CSS, Javascript, SQL, Python and other knowledge acquired through practice.
    Frameworks like Bootstrap was used to make the development more agile, without losing the quality of the website.
    The database modeling was designed to reduce the redundancies, and to connect the data properly. For that, it was used the primary and foreign key to link the tables and connect the information.
    Finally, several resourses were used to make the website user friendly, beautiful and consistent to assure that the user will recive the best product.