import turtle as t
t.pensize(5)
t.color('red')
t.begin_fill()
t.circle(50)
t.end_fill()
t.goto(0,50)
t.color('yellow')
for i in range(12):
    t.right(30)
    t.pu()
    t.goto(0, 50)
    t.forward(60)
    t.pd()
    t.forward(30)

t.ht()
t.done()