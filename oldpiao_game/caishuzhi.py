import os
while True:
    a=input('请出题者出题：')
    if a.isdigit():
        a=int(a)
        if a>=0 and a<100:
            break
        else:
            print('请输入100以内整数：')
    else:
        print('请输入100以内整数：')
i=os.system('cls')
n=99
print('呆瓜，你可以猜了:')
d=1
while d==1:
    b=int(input())
    if a==b:
        print('我靠，这么厉害吗！！')
        d=0
    else:
        n=n-17
        if a<b:
            print('大了，我的呆！！')
        else:
            print('小了，我的瓜！！')
    if n<=0:
        print('对不起您的智商余额已不足，请及时充值!')
        d=0
    print('对您智商的评价，智商余额:',n)