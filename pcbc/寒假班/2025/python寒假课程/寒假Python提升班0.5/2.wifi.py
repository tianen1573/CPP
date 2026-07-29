import turtle as t
t.speed(10)
t.pensize(5)
t.dot(10)

def cc(r,y):
    #t.penup() # 抬笔到位置
    t.goto(0,y)
    t.circle(r,130) # 不落笔 移动
    t.pendown()
    t.circle(r,100) # 落笔 移动
    #t.penup()
    t.circle(r,130) # 不落笔 移动 凑够360°

# 远点依次向下，半径依次增大
for i in range(0,61,20):
    cc(i,-i)
t.hideturtle()
