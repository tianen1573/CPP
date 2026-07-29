import random
lis=[]
while True:
    i=random.randint(1,10)
    if i not in lis:
        lis.append(i)
    if len(lis)==10:
        break
print(lis)

while True:
    j=0
    for i in range(9):
        if lis[i]>lis[i+1]:
            lis[i],lis[i+1]=lis[i+1],lis[i]
            j+=1
    if j==0:
        break
print(lis)
