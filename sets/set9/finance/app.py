import os
import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")
'''uri = os.getenv("DATABASE_URL")
if uri.startswith("postgres://"):
    uri = uri.replace("postgres://", "postgresql://")
db = SQL(uri)'''

# Make sure API key is set
api_key = "pk_d8dd14d3d9874a669ed403dfa6e54c2b"
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stocks = db.execute("SELECT symbol, price, shares FROM buy WHERE user_id = ?", session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash = cash[0]["cash"]
    summ = 0
    for i in stocks:
        price = lookup(i["symbol"])
        price = price["price"]
        i["price"] = price
        i["TOTAL"] = i["price"] * i["shares"]
    for i in stocks:
        summ += i["TOTAL"]
    summ += cash
    return render_template("index.html", stocks=stocks, cash=cash, summ=summ)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("wrong symbol", 400)
        shares = request.form.get("shares")

        if not shares.isnumeric():
            return apology("Wrong amount of shares", 400)

        shares = int(shares)

        price = lookup(request.form.get("symbol"))
        if price == None:
            return apology("wrong symbol", 400)

        price = price["price"]

        person = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        date = datetime.datetime.now()

        if shares * price <= person[0]["cash"]:
            stocks = db.execute("SELECT * FROM buy WHERE user_id = ?", session["user_id"])
            check = False
            if len(stocks) <= 0:
                db.execute("INSERT INTO buy (user_id, symbol, price, shares) VALUES(?, ?, ?, ?)",
                           person[0]["id"], request.form.get("symbol"), price, shares)
                check = True
            else:
                for i in stocks:
                    if request.form.get("symbol") == i["symbol"]:
                        shares += i["shares"]
                        check = True
                        db.execute("UPDATE buy SET shares = ? WHERE user_id = ? AND symbol = ?",
                                   shares, session["user_id"], request.form.get("symbol"))
            if check != True:
                db.execute("INSERT INTO buy (user_id, symbol, price, shares) VALUES(?, ?, ?, ?)",
                           person[0]["id"], request.form.get("symbol"), price, shares)
            db.execute("INSERT INTO history (user_id, symbol, price, shares, date, type) VALUES(?, ?, ?, ?, ?, ?)",
                       person[0]["id"], request.form.get("symbol"), price, shares, date, "buy")
            db.execute("UPDATE users SET cash = ? WHERE id = ?", person[0]["cash"]-shares*price, session["user_id"])

        else:
            return apology("not enough money", 403)

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    stocks = db.execute("SELECT * FROM history WHERE user_id = ?", session["user_id"])
    return render_template("history.html", stocks=stocks)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

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
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)
        quote = lookup(request.form.get("symbol"))
        if quote == None:
            return apology("wrong symbol", 400)

        return render_template("quoted.html", quote=quote)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        if not request.form.get("username") or request.form.get("username") == None:
            return apology("must provide username", 400)

        elif not request.form.get("password") or request.form.get("password") == None:
            return apology("must provide password", 400)

        elif not request.form.get("confirmation") or request.form.get("confirmation") == None:
            return apology("must confirm password", 400)

        if not request.form.get("password") == request.form.get("confirmation"):
            return apology("passwords don't match", 400)

        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        if len(rows) != 0:
            return apology("username already taken", 400)

        # checking if password satisfies (personal touch) requirements
        # can't leave it without comments since check50 doesn't like it, but it works!!
        password = request.form.get("password")
        countl = 0 #count number of letters
        countn = 0 #count number of numbers
        counts = 0 #count number of symbols
        for i in password:
            if(i.isalpha()):
                countl += 1
            elif(i.isnumeric()):
                countn += 1
            else:
                counts += 1

        if countl < 3 or countn < 3 or counts < 1:
            return apology("password doesn't satisfy requirements :(", 400)


        username = request.form.get("username")
        hash = generate_password_hash(request.form.get("password"))
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hash)
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        session["user_id"] = rows[0]["id"]
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/passchange", methods=["POST", "GET"])
def passchange():
    if request.method == "POST":

        if not request.form.get("username") or request.form.get("username") == None:
            return apology("must provide username", 400)

        elif not request.form.get("password") or request.form.get("password") == None:
            return apology("must provide previous password", 400)

        elif not request.form.get("confirmation") or request.form.get("confirmation") == None:
            return apology("must provide new password", 400)

        password = db.execute("SELECT hash FROM users WHERE username = ?", request.form.get("username"))[0]["hash"]
        if check_password_hash(password, request.form.get("password")):
            db.execute("UPDATE users SET hash = ? WHERE username = ?", generate_password_hash(
                       request.form.get("confirmation")), request.form.get("username"))

        else:
            return apology("wrong previous password", 400)

        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        session["user_id"] = rows[0]["id"]
        return redirect("/")

    else:
        return render_template("passchange.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    stocks = db.execute("SELECT symbol, shares FROM buy WHERE user_id = ?", session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    if request.method == "POST":

        if request.form.get("symbol") == None:
            return apology("Choose a symbol")
        shares = request.form.get("shares")

        if not shares.isnumeric():
            return apology("Wrong amount of shares", 400)

        shares = int(shares)

        if shares < 1:
            return apology("wrong amount of shares", 400)
        a_shares = db.execute("SELECT shares, symbol FROM buy WHERE symbol = ? AND user_id = ?",
                              request.form.get("symbol"), session["user_id"])

        if shares > a_shares[0]["shares"]:
            return apology("not enough shares", 400)
        price = lookup(request.form.get("symbol"))
        price = price["price"]
        cash = cash[0]["cash"]
        cash += price * shares
        date = datetime.datetime.now()
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])
        db.execute("UPDATE buy SET shares = ? WHERE user_id = ? AND symbol = ?",
                   a_shares[0]["shares"] - shares, session["user_id"], request.form.get("symbol"))
        db.execute("INSERT INTO history (user_id, symbol, price, shares, date, type) VALUES(?, ?, ?, ?, ?, ?)",
                   session["user_id"], request.form.get("symbol"), price, shares, date, "sell")

        a_shares = db.execute("SELECT shares FROM buy WHERE symbol = ? AND user_id = ?",
                              request.form.get("symbol"), session["user_id"])
        if a_shares[0]["shares"] == 0:
            db.execute("DELETE FROM buy WHERE symbol = ? AND user_id = ?", request.form.get("symbol"), session["user_id"])

        return redirect("/")
    else:
        return render_template("sell.html", stocks=stocks)


@app.route("/addcash", methods=["GET", "POST"])
@login_required
def addcash():
    if request.method == "POST":
        if int(request.form.get("addcash")) == 0:
            return apology("wrong amount of cash", 400)
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        cash += int(request.form.get("addcash"))
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])
        return redirect("/")
    else:
        return render_template("addcash.html")


@app.route("/sell_in_index", methods=["GET", "POST"])
@login_required
def sell_in_index():
    if request.method == "POST":
        shares_sell = request.form.get("shares_sell")

        if not shares_sell.isnumeric() or int(shares_sell) < 1:
            return apology("Wrong amount of shares", 400)

        shares_sell = int(shares_sell)
        stock = request.form.get("symbol2")
        price = lookup(stock)["price"]
        shares = int(request.form.get("shares2"))
        portfolio = db.execute("SELECT * FROM buy WHERE user_id = ?", session["user_id"])[0]
        date = datetime.datetime.now()
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        if shares_sell > portfolio["shares"]:
            return apology("not enough shares", 400)

        cash += shares_sell * price
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])
        db.execute("UPDATE buy SET shares = ? WHERE user_id = ? AND symbol = ?", shares - shares_sell, session["user_id"], stock)
        db.execute("INSERT INTO history (user_id, symbol, price, shares, date, type) VALUES(?, ?, ?, ?, ?, ?)",
                   session["user_id"], stock, price, shares_sell, date, "sell")

        if db.execute("SELECT shares FROM buy WHERE user_id = ? AND symbol = ?", session["user_id"], stock)[0]["shares"] == 0:
            db.execute("DELETE FROM buy WHERE symbol = ? AND user_id = ?", stock, session["user_id"])

        return redirect("/")
    else:
        return redirect("/")


@app.route("/buy_in_index", methods=["GET", "POST"])
@login_required
def buy_in_index():
    if request.method == "POST":
        shares_buy = request.form.get("shares_buy")

        if not shares_buy.isnumeric() or int(shares_buy) < 1:
            return apology("Wrong amount of shares", 400)

        shares_buy = int(shares_buy)
        stock = request.form.get("symbol2")
        price = lookup(stock)["price"]
        shares = int(request.form.get("shares2"))
        person = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
        date = datetime.datetime.now()

        if shares_buy * price <= person[0]["cash"]:
            db.execute("INSERT INTO history (user_id, symbol, price, shares, date, type) VALUES(?, ?, ?, ?, ?, ?)",
                       person[0]["id"], stock, price, shares_buy, date, "buy")
            db.execute("UPDATE users SET cash = ? WHERE id = ?", person[0]["cash"]-shares_buy*price, session["user_id"])
            shares_buy += shares
            db.execute("UPDATE buy SET shares = ? WHERE user_id = ? AND symbol = ?", shares_buy, session["user_id"], stock)

        else:
            return apology("not enough cash", 400)

        return redirect("/")
    else:
        return redirect("/")