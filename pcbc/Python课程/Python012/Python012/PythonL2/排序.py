import random
#1—10随机排列
lis=[]
while True:
    i=random.randint(1,10)
    if i not in lis:
        lis.append(i)
    if len(lis)==10:
        break
print(lis)

#冒泡排序
'''
while True:
    f=0
    for i in range(len(lis)-1):
        if lis[i]>lis[i+1]:
            lis[i],lis[i+1]=lis[i+1],lis[i]
            f+=1
    if f==0:
        break
print(lis)
'''

#选择排序
'''
f=0
for i in range(f,len(lis)-1):
    for j in range(f+1,len(lis)):
        if lis[i]>lis[j]:
            lis[i],lis[j]=lis[j],lis[i]
    f+=1
print(lis)
'''




