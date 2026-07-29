#include<iostream>
#include<stack>//栈 
#include<vector>//容器 
#include<time.h>//获取当前时间 
#include <Windows.h>//颜色改变，时停 
#include<stdlib.h>//清屏 
 
using namespace std;
 
#define X 27//迷宫大小 
#define Y 27
#define start_x 2//起点
#define start_y 2
#define speed 30//速度 
 
struct box
{
	int x,y;//坐标
	int dir;//方向：右1 下2 左3 上4
};
 
int mg[X][Y];//初始迷宫
int mglx[X][Y];//展示迷宫路线，因原迷宫会被打乱
 
stack<box> path;//路线，包含坐标与方向信息
 
HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);//颜色
 
void create_mg();//随机生成迷宫
void copy_mg();//复制迷宫
void play_mg();//完成迷宫路线求解
void show_path();//坐标路线展示 
void show_mg();//迷宫路线展示
void cout_green();//打印绿色
void cout_red();//打印红色
void recover();//恢复白色
 
//清屏函数，代替system("cls")，防止闪烁，网上学习
void gotoxy(int x,int y);//将光标移动到（x,y）位置
void HideCursor();//隐藏光标
 
 
 
int main()
{
	while(true)
	{
		system("cls");
		char choice;
		cout<<endl<<endl<<"*****\t欢迎来到迷宫求解问题\t*******"<<endl<<endl<<endl;
		cout<<"\t[1] 随机生成迷宫."<<endl;
		cout<<"\t[2] 退出游戏."<<endl<<endl;
		cout<<"\t\t随机生成 "<<X-2<<" X "<<Y-2<<" 的迷宫"<<endl;
		cout<<"\t\t\t\t——QLU"<<endl;
		cout<<"****************************************"<<endl<<endl;
		cout<<"请输入你的选择：";
		cin>>choice;
		if(choice=='1')
		{
			system("cls");
			while(true)
			{
				create_mg();
				if(mg[X-3][Y-3]==0)//若终点是一堵墙，则重新生成迷宫
					break;
			}
			copy_mg();
			show_mg();
			system("pause");
			play_mg();
			show_path();
		}
		else if(choice=='2')
			return 0;
		else
			cout<<"请输入正确的选择!"<<endl;
		system("pause");
	}
}
 
void create_mg()//随机生成迷宫
{
	//初始化迷宫：内部为墙体；外围为通路，当做屏障
	for(int i=0; i<Y; i++)
	{
		mg[0][i]=0;
		mg[X-1][i]=0;
	}
	for(int i=1; i<X-1; i++)
		for(int j=0; j<Y; j++)
		{
			if(j==0||j==Y-1)
				mg[i][j]=0;
			else
				mg[i][j]=1;
		}
 
	//分别对应着上下左右方向
	int dRow[] = {1, 0, -1, 0};
	int dCol[] = {0, -1, 0, 1};
	//用于存储墙体坐标
	vector<int> QX,QY;
	QX.push_back(start_x);//从起点开始
	QY.push_back(start_y);
	while(QX.size())//拆墙
	{
		//根据当前时间，生成一个随机数种子
		srand((unsigned int)(time(NULL)));
		int index=rand()%(QX.size());//随机生成一个坐标，选取一堵墙
		int x=QX[index];
		int y=QY[index];
		int flag=0;//记录该墙四周通路个数
		int r,c;
		for(int i=0; i<4; i++)
		{
			r=x+dRow[i];
			c=y+dCol[i];
			if(mg[r][c]==0)
				flag++;
		}
 
		if(flag<=1)//当该墙体四周通路有一条或没有时，则该墙改为道路
		{
			mg[x][y]=0;
			for(int i=0; i<4; i++)
			{
				r=x+dRow[i];
				c=y+dCol[i];
				if(mg[r][c]==1)//将该墙四周的墙加入队列
				{
					QX.push_back(r);
					QY.push_back(c);
				}
			}
		}
 
		//将当前墙移除队列
		QX.erase(QX.begin()+index);
		QY.erase(QY.begin()+index);
	}
}
 
void play_mg()
{
	//分别对应着上下左右方向
	int dRow[] = {0, 1, 0, -1};
	int dCol[] = {1, 0, -1, 0};
 
	box start;//起始位置
	start.x=start_x;
	start.y=start_y;
	path.push(start);
	while(!path.empty())
	{
		box temp;
		bool flag=false;//判断该坐标是否有通路
		int x = path.top().x;
		int y = path.top().y;
		mg[x][y]=1;//该坐标已经过,设置为墙
		for(int i=0; i<4; i++) //向四个位置进行试探,方向：右1 下2 左3 上4
		{
			int r=x+dRow[i];
			int c=y+dCol[i];
			if(mg[r][c]==0)
			{
				temp.x=r;
				temp.y=c;
				temp.dir=i+1;
				path.push(temp);
				flag=true;
				break;
			}
		}
		if(x==X-3&&y==Y-3)//到达终点
			break;
		mglx[x][y]=temp.dir+1;//该坐标已经过,右2 下3 左4 上5
		if(!flag)//若该坐标点无通路，则回溯
		{
			box t=path.top();
			mglx[t.x][t.y]=6;//回溯后要把该坐标设为不可走路线
			path.pop();
		}
		HideCursor();
		gotoxy(0,0);
		Sleep(speed);//设置速度
		show_mg();
	}
}
 
void show_path()//展示坐标路线
{
	if(path.empty())
	{
		cout<<"此迷宫无解"<<endl;
		return;
	}
	box temp[100];
	int length=0;
	while(!path.empty())
	{
		temp[length]=path.top();
		length++;
		path.pop();
	}
	cout<<"方向路线:"<<endl;
	cout<<"起点=>";
	for(int i=length-1; i>=0; i--)
	{
		if(temp[i].dir==1)
			cout<<"右=>";
		else if(temp[i].dir==2)
			cout<<"下=>";
		else if(temp[i].dir==3)
			cout<<"左=>";
		else if(temp[i].dir==4)
			cout<<"上=>";
	}
	cout<<"终点"<<endl<<endl;
	cout<<"坐标路线："<<endl;
	cout<<"起点=>";
	for(int i=length-1; i>=0; i--)
	{
		cout<<"("<<temp[i].x-1<<","<<temp[i].y-1<<")=>";
	}
	cout<<"终点"<<endl;
}
 
void show_mg()//展示迷宫路线
{
	for(int i=0; i<X; i++)
	{
		for(int j=0; j<Y; j++)
		{
			//墙■路  右2→ 下3↓ 左4← 上5↑ 错×
			if(i==start_x&&j==start_y)
				cout<<"☆";
			else if(i==X-3&&j==Y-3)
				cout<<"★";
			else if(mglx[i][j]==1)
				cout<<"■";
			else if(mglx[i][j]==2)
			{
				cout_green();
				cout<<"→";
				recover();
			}
			else if(mglx[i][j]==3)
			{
				cout_green();
				cout<<"↓";
				recover();
			}
			else if(mglx[i][j]==4)
			{
				cout_green();
				cout<<"←";
				recover();
			}
			else if(mglx[i][j]==5)
			{
				cout_green();
				cout<<"↑";
				recover();
			}
			else if(mglx[i][j]==6)
			{
				cout_red();
				cout<<"×";
				recover();
			}
			else
				cout<<"  ";
		}
		cout<<endl;
	}
}
 
void copy_mg()//复制迷宫
{
	for(int i=0; i<X; i++)
	{
		for(int j=0; j<Y; j++)
		{
			mglx[i][j]=mg[i][j];
		}
	}
}
 
void cout_green()//绿色
{
	SetConsoleTextAttribute(hout, 2);
}
 
void cout_red()//红色
{
	SetConsoleTextAttribute(hout, 4);
}
 
void recover()//白色
{
	SetConsoleTextAttribute(hout, 1|2|4);
}
 
void gotoxy(int x,int y)//将光标移动到（x,y）位置
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);    //获取标准输出设备句柄
	COORD pos= {x,y};     //坐标位置
	SetConsoleCursorPosition(handle,pos);   //设置控制台光标位置
}
void HideCursor()//隐藏光标
{
	CONSOLE_CURSOR_INFO cursor_info= {1,0}; //0表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}
