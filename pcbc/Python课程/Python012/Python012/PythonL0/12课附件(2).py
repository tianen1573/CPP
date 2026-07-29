import turtle as t
t.penup()
t.goto(0,-250)
t.pendown()
t.goto(0,-200)

def a(y):
    t.penup()
    t.goto(0,y)
    t.pendown()
    t.circle(50)
a(-200)
a(-100)
a(0)
a(100)

t.penup()
t.goto(0,200)
t.pendown()
t.goto(0,250)
