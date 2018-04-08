import random
import os
import msvcrt

import easygui
from colorama import init,Fore

init(autoreset=False)
class Fangkuai:
    def __init__(self,x=0,y=0,neirong=0,zhuangtai=0):
        self.x=x
        self.y=y
        self.neirong=neirong#0,9,1,2,3,4,5,6,7,8分别为 空，雷，数字1-8
        self.zhuangtai=zhuangtai#0,1,2,3,4分别为 未点击，插旗，问号，被点击,错误

    def getFangkuai(self):
        return [self.x,self.y,self.neirong,self.zhuangtai]

class Mymap:
    def __init__(self,xMax=10,yMax=10):
        self.xMax=xMax
        self.yMax=yMax
        self.fk=[]
        self.new_fk=Fangkuai()
        self.lei_xy=[]

    def found_map(self):
        for x in range(self.xMax):
            self.fk.append([])
            for y in range(self.yMax):
                new_fk = Fangkuai(x,y)
                self.fk[x].append([new_fk.getFangkuai()[2],new_fk.getFangkuai()[3]])

    def bulei(self):
        for i in range(lei_sum):
            while True:
                self.x = random.randint(0, map_xy_max[0] - 1)
                self.y = random.randint(0, map_xy_max[1] - 1)
                if [self.x,self.y] not in self.lei_xy:
                    self.fk[self.x][self.y][0]=9# 这一位的9代表雷
                    self.lei_xy.append([self.x,self.y])
                    break

    def bushu(self):
        for j in self.lei_xy:
            # print('j=',j)
            #为雷周围布数字
            for lei_x in [j[0]-1,j[0],j[0]+1]:
                for lei_y in [j[1]-1,j[1],j[1]+1]:
                    #超出地图不处理
                    if 0<=lei_x<map_xy_max[0] and 0<=lei_y<map_xy_max[1]:
                        #如果是雷不处理
                        if self.fk[lei_x][lei_y][0]==9:
                            # print(lei_x,lei_y,'我是雷',end='')
                            pass
                        else:
                            # print(lei_x,lei_y,'我加一',end='')
                            self.fk[lei_x][lei_y][0] += 1
                    else:
                        # print(lei_x,lei_y,'我不在',end='')
                        pass
            # print()

    def getfk(self):
        return self.fk


class State:
    def __init__(self,fk,x,y):
        self.fk=fk
        self.x=x
        self.y=y
    #点击
    def click(self):
        if self.fk[self.x][self.y][1]==0:
            self.fk[self.x][self.y][1]=3
            State.click_judge(self,self.x,self.y)
            over=State.game_over(self)
            return over
    # 判定点击效果
    def click_judge(self,x1,y1):
        if self.fk[x1][y1][0] == 0:
            for lei_x in [x1 - 1, x1, x1 + 1]:
                for lei_y in [y1 - 1,y1,y1 + 1]:
                    # 超出地图不处理
                    if 0 <= lei_x < map_xy_max[0] and 0 <= lei_y < map_xy_max[1]:
                        # 如果已被点击不处理
                        if self.fk[lei_x][lei_y][1] == 3:
                            pass
                        else:
                            self.fk[lei_x][lei_y][1] = 3
                            State.click_judge(self,lei_x,lei_y)
                    else:
                        pass
        else:
            pass
    #插旗
    def set_flag(self):
        if self.fk[self.x][self.y][1]==3:
            pass
        elif self.fk[self.x][self.y][1]==2:
            self.fk[self.x][self.y][1]=0
        elif self.fk[self.x][self.y][1]==0 or self.fk[self.x][self.y][1]==1:
            self.fk[self.x][self.y][1]+=1
        else:
            pass

    #游戏结束判定
    def game_over(self):
        # 判定是否点到了雷
        if self.fk[self.x][self.y][0] == 9:
            for fk_x in range(len(self.fk)):
                for fk_y in range(len(self.fk[fk_x])):
                    if self.fk[fk_x][fk_y][1] == 1:
                        if self.fk[fk_x][fk_y][0] != 9:
                            self.fk[fk_x][fk_y][1] = 4
                        else:
                            pass
                    else:
                        self.fk[fk_x][fk_y][1] = 3
            return 3

    #游戏获胜判定
    def game_win(self):
        # 判定所有的雷是不是都插了旗------------------------
        for fk_x in range(len(self.fk)):
            for fk_y in range(len(self.fk[fk_x])):
                # 如果有雷没插旗，继续游戏
                if self.fk[fk_x][fk_y][0] == 9 and self.fk[fk_x][fk_y][1] != 1:
                    return 1
                # 如果有不是雷的插着旗，继续游戏
                elif self.fk[fk_x][fk_y][0] != 9 and self.fk[fk_x][fk_y][1] == 1:
                    return 1
                # 此项是为防止通过插旗测试正确答案，必须点开所有的空地
                # 如果有没点开的砖块，继续游戏
                elif self.fk[fk_x][fk_y][1] == 0:
                    return 1
                else:
                    pass
        return 2

    def setfk(self):
        return self.fk

class Model:
    def __init__(self,fk,start_x,start_y):
        self.fk=fk
        self.start_x=start_x
        self.start_y=start_y
        self.qishu=lei_sum
    def dayin(self):
        os.system('cls')
        print()#打印开头空行
        print('x\\y',end='  ')
        for top in range(len(self.fk[0])):
            print('%2d'%top,end='')
        print('\n')
        for x in range(len(self.fk)):
            print('%2d'%x,end='   ')
            for y in range(len(self.fk[x])):
                # self.fk[x][y][0] 0,9,1,2,3,4,5,6,7,8分别为 空，雷，数字1-8
                # self.fk[x][y][1] 0,1,2,3分别为 未点击，插旗，问号，被点击
                if x==self.start_x and y==self.start_y:
                    print(Fore.GREEN,end='')

                if self.fk[x][y][1]==0:
                    print('■',end='')
                elif self.fk[x][y][1]==1:
                    print(Fore.RED+'▶'+Fore.RESET,end='')
                    self.qishu-=1
                elif self.fk[x][y][1]==2:
                    print('？',end='')
                elif self.fk[x][y][1]==3:
                    if self.fk[x][y][0]==0:
                        print('□',end='')
                    elif self.fk[x][y][0]==9:
                        print('¤',end='')
                    elif self.fk[x][y][0]==1:
                        print('①',end='')
                    elif self.fk[x][y][0]==2:
                        print('②',end='')
                    elif self.fk[x][y][0]==3:
                        print('③',end='')
                    elif self.fk[x][y][0]==4:
                        print('④',end='')
                    elif self.fk[x][y][0]==5:
                        print('⑤',end='')
                    elif self.fk[x][y][0]==6:
                        print('⑥',end='')
                    elif self.fk[x][y][0]==7:
                        print('⑦',end='')
                    elif self.fk[x][y][0]==8:
                        print('⑧',end='')
                    #数字
                    # else:
                    #     print('%2d'%self.fk[x][y][0],end='')
                elif self.fk[x][y][1]==4:
                    print('×',end='')
                else:
                    pass

                if x == self.start_x and y == self.start_y and self.fk[x][y][1]!=1:
                    print(Fore.RESET,end='')  # autoreset = True
            print()#打印一行后回车
        print()#打印结尾空行
        print('你还有%d面旗子'%self.qishu)

class Control:
    def __init__(self,key,x=0,y=0):
        self.key=key
        self.x=x
        self.y=y
    #Up, Down, Left,Right
    def fk_move(self):
        if ord(self.key) ==119:
            self.x-=1
        elif ord(self.key) ==115:
            self.x+=1
        elif ord(self.key) ==97:
            self.y-=1
        elif ord(self.key) ==100:
            self.y+=1
        elif ord(self.key) ==106:
            return 'j'
        elif ord(self.key) ==107:
            return 'k'
        elif ord(self.key) == 27:  # key nr 27 is escape
            if easygui.ccbox('是否退出游戏','退出',choices=(['是','否'])):
                return 'esc'
            else:
                pass
        #边缘判定
        if self.x<0:
            self.x=map_xy_max[0]-1
        if self.x>=map_xy_max[0]:
            self.x=0
        if self.y<0:
            self.y=map_xy_max[1]-1
        if self.y>=map_xy_max[1]:
            self.y=0

    def get_all(self):
        return [self.x,self.y]

map_xy_max=[]
lei_sum=0
def cli():
    global map_xy_max,lei_sum
    choices=['简单','普通','困难','自定义']
    xuanguan=easygui.buttonbox('选择您要玩的难度','选关',choices)
    if xuanguan==choices[3]:
        fields = ['雷区长度：', '雷区宽度：', '雷数：']
        xuan=easygui.multenterbox('请输入您要挑战的难度','自定义难度',fields)
        for xuan_key in range(len(xuan[:])):
            xuan[xuan_key]=int(xuan[xuan_key])
        map_xy_max=xuan[:2]
        lei_sum=xuan[2]
    else:
        guan={choices[0]:[10,10,10],
              choices[1]:[15,15,30],
              choices[2]:[20,20,60],
              }
        map_xy_max=guan[xuanguan][:2]#地图大小
        lei_sum=guan[xuanguan][2]

    mymap=Mymap(map_xy_max[0],map_xy_max[1])
    mymap.found_map()
    mymap.bulei()
    mymap.bushu()
    fk=mymap.getfk()
    over,win=1,1
    start_x=0
    start_y=0
    while True:
        model = Model(fk,start_x,start_y)
        model.dayin()
        if over == 3:
            print('游戏失败!')
            break
        if win == 2:
            print('胜利，撒花！')
            break
        print('按Esc键退出：\n方向键W↑ S↓ A← D→:')
        key = msvcrt.getch()
        cont = Control(key,start_x, start_y)
        start_jk = cont.fk_move()
        start_x =cont.get_all()[0]
        start_y =cont.get_all()[1]
        start = State(fk, start_x, start_y)
        if start_jk=='j':
            over =start.click()

        elif start_jk=='k':
            start.set_flag()
        elif start_jk=='esc':
            break
        win = start.game_win()
        fk=start.setfk()

if __name__ == '__main__':
    cli()

