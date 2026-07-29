import turtle as t
import random

t.colormode(255)

for i in range(20):
    r = random.randint(0,255)
    g = random.randint(0,255)
    b = random.randint(0,255)
    x = random.randint(-200,200)
    y = random.randint(-200,200)

    t.penup()
    t.goto(x,y)
    t.pendown()
    t.color(r,g,b)
    t.begin_fill()
    t.circle(30)
    t.end_fill()

    t.right(90)
    t.forward(30)
    t.left(90)

t.done()