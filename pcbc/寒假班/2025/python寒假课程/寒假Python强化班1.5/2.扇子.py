import turtle as t

t.speed(100)
a = 0
t.pensize(2)
t.color('black', 'yellow')
t.begin_fill()
while a <= 34:
    t.left(5)
    t.pu()
    t.goto(0, 0)
    t.pd()
    t.forward(-20)
    t.forward(120)
    a = a + 1
t.right(90)
t.circle(-100, 170)
t.end_fill()
t.hideturtle()
t.done()
