import turtle as t
t.bgcolor("red")
t.speed(5)
def star(size):
    t.color('yellow')
    t.begin_fill()
    a=0
    while a<5:
        t.forward(size)
        t.right(144)
        a=a+1
    t.end_fill()

t.penup()
t.goto(-700,300)
t.pendown()
star(120)

# t.penup()
t.goto(-700,260)
t.right(90)
t.circle(100,108)
t.pendown()

a=0
while a<4:
    star(40)
    t.penup()
    t.circle(100,36)
    t.pendown()
    a=a+1
t.ht()

