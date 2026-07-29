import turtle as t
t.fillcolor('yellow')
t.begin_fill()
t.pensize(3)
t.speed(0)
a=0
while a<19:
    t.backward(30)
    t.forward(150)
    if a!=18:
        t.goto(0,0)
        t.left(10)
    a=a+1
t.left(90)
t.circle(120,-180)
t.end_fill()
