#include<graphics.h>
#include<conio.h>
#include<ctime>
#include<string>
#include<cmath>
using namespace std;
#pragma comment(lib,"Winmm.lib")
#define W  600
#define H  600
#define PLSIZE  80	//飞机的大小
#define BSIZE  40	//子弹的大小
IMAGE Fimage;	//飞机的原图
IMAGE Fimage1;	//飞机的掩码图
IMAGE Bimage;	//背景图
IMAGE Bulletim;	//子弹图
IMAGE Bulletim1;	//子弹掩码图
IMAGE Dijiim;	//敌机
IMAGE Dijiim1;	//敌机的掩码图
IMAGE Dijibull;	//敌机子弹
IMAGE Dijibuim;	//敌机子弹掩码图
IMAGE Blast;
IMAGE Blastim;	//爆炸掩码
struct Member
{
	double m_x;
	double m_y;
	bool m_flag;
};
//敌机子弹
struct Membull
{
	double m_x;
	double m_y;
	bool m_flag;
	double angle;
};
//敌机
struct BBplane
{
	double m_x;
	double m_y;
	bool m_flag;
	Membull BBullter[5];
};
Member Plane;
Member Bullter[10];
BBplane Bplane [10];

//时间的变化量
DWORD start, last,start2,last2;
int score;

//加载图片
void jiazai()
{
	loadimage(&Bimage, ".\\image\\星空.jpg", W, H);
	loadimage(&Fimage, ".\\image\\飞机1.jpg", PLSIZE, PLSIZE);
	loadimage(&Fimage1, ".\\image\\掩码图1.jpg", PLSIZE, PLSIZE);
	loadimage(&Bulletim, ".\\image\\子弹2.jpg", BSIZE, BSIZE);
	loadimage(&Bulletim1, ".\\image\\掩码图3.jpg", BSIZE, BSIZE);
	loadimage(&Dijiim, ".\\image\\飞机2.jpg", BSIZE, BSIZE);
	loadimage(&Dijiim1, ".\\image\\掩码图2.jpg", BSIZE, BSIZE);
	loadimage(&Dijibull, ".\\image\\子弹3.jpg", BSIZE/2, BSIZE/2);
	loadimage(&Dijibuim, ".\\image\\子弹3掩码图.jpg", BSIZE/2, BSIZE/2);
	loadimage(&Blast, ".\\image\\爆炸3.jpg", PLSIZE, PLSIZE);
	loadimage(&Blastim, ".\\image\\爆炸3掩码图.jpg", PLSIZE, PLSIZE);
	
}
//操作
void operation()
{
	//上键
	if (GetAsyncKeyState(VK_UP))
	{
		if (Plane.m_y > 0)
			Plane.m_y -= 0.35;
	}
	//下键
	 if (GetAsyncKeyState(VK_DOWN)&0x8000)
	{
		if (Plane.m_y < H*1.0 - PLSIZE*1.0)
			Plane.m_y += 0.35;
	}
	//左键
	 if (GetAsyncKeyState(VK_LEFT))
	{
		if (Plane.m_x > -PLSIZE / 2.0)
			Plane.m_x -= 0.35;
	}
	//右键
    if (GetAsyncKeyState(VK_RIGHT))
	{
		if (Plane.m_x < (W - PLSIZE / 2.0)*1.0)
			Plane.m_x += 0.35;
	}
	//空格
	if (GetAsyncKeyState(VK_SPACE) && last - start > 80)		//每颗子弹间隔80毫秒，不进行设置，产生的子弹重叠
	{
		//发射子弹
		for (int i = 0; i < 10; i++)
		{
			if (!Bullter[i].m_flag )
			{
				Bullter[i].m_x = Plane.m_x + PLSIZE / 2.0 - BSIZE / 2.0;
				Bullter[i].m_y = Plane.m_y - BSIZE;
				Bullter[i].m_flag = true;	
				break;	//一次只发射一颗
			}
		}
		start = last;	//时间差归零
	}
	//时间差增加
	last = GetTickCount();
}
//显示图片
void show()
{
	BeginBatchDraw();
	//背景图
	putimage(0, 0, &Bimage);
	//飞机图
	if (Plane.m_flag)
	{
		putimage(Plane.m_x, Plane.m_y, &Fimage1, SRCAND);
		putimage(Plane.m_x, Plane.m_y, &Fimage, SRCPAINT);
	}

	for (int i = 0; i < 10; i++)
	{
		//子弹图
		if (Bullter[i].m_flag)
		{
			
			putimage(Bullter[i].m_x, Bullter[i].m_y, &Bulletim1, SRCAND);
			putimage(Bullter[i].m_x, Bullter[i].m_y, &Bulletim, SRCPAINT);
		}
		//敌机图
		if (Bplane[i].m_flag)
		{
			putimage(Bplane[i].m_x, Bplane[i].m_y, &Dijiim1, SRCAND);
			putimage(Bplane[i].m_x, Bplane[i].m_y, &Dijiim, SRCPAINT);
		}
		//敌机子弹
		for (int j = 0; j < 5; j++)
		{
			if (Bplane[i].BBullter[j].m_flag)
			{
				putimage(Bplane[i].BBullter[j].m_x, Bplane[i].BBullter[j].m_y, &Dijibuim, SRCAND);
				putimage(Bplane[i].BBullter[j].m_x, Bplane[i].BBullter[j].m_y, &Dijibull, SRCPAINT);
			}
		}
	}
	EndBatchDraw();
}
//子弹的移动
void tranbullterd()
{
	for (int i = 0; i < 10; i++)
	{
		if(Bullter[i].m_flag)
		{
			Bullter[i].m_y--;
			if (Bullter[i].m_y < 0)
			{
				Bullter[i].m_flag = false;
			}
		}
		//敌机子弹的移动
		for (int j = 0; j < 5; j++)
		{
			if (Bplane[i].BBullter[j].m_flag)
			{
				Bplane[i].BBullter[j].m_x += 0.02 * Bplane[i].BBullter[j].angle;
				Bplane[i].BBullter[j].m_y += 0.1;
				//超出边框，消失
				if (Bplane[i].BBullter[j].m_x<0 || Bplane[i].BBullter[j].m_x>W || Bplane[i].BBullter[j].m_y > H	|| Bplane[i].BBullter[j].m_y <0)
				{
					Bplane[i].BBullter[j].m_flag = false;
				}
			}
		}
	}
}
//敌机释放子弹
void FIREBbull()
{
	for (int i = 0; i < 10; i++)
	{
		if (Bplane[i].m_flag && last-start>300)
		{
			for (int j = 0; j < 5 ; j++)
			{
				if (!Bplane[i].BBullter[j].m_flag)
				{
					Bplane[i].BBullter[j].m_x = Bplane[i].m_x + PLSIZE / 2.0 - BSIZE / 2;
					Bplane[i].BBullter[j].m_y = Bplane[i].m_y + PLSIZE * 1.0;
					Bplane[i].BBullter[j].angle = (Plane.m_y - Bplane[i].m_y) / (Plane.m_x - Bplane[i].m_x);
					Bplane[i].BBullter[j].m_flag = true;
					start = last;
					break;
				}
				last = GetTickCount();
			}
		}
	}
}
//判断飞机是否受损
bool test()
{
	for (int i = 0; i < 10; i++)
	{
		if (Bplane[i].m_flag && Plane.m_x + PLSIZE / 2.0 >= Bplane[i].m_x && Plane.m_x + PLSIZE / 2.0 <= Bplane[i].m_x + BSIZE
			&& Plane.m_y >= Bplane[i].m_y && Plane.m_y <= Bplane[i].m_y + BSIZE)
		{
			return false;
		}
		for (int j = 0; j < 5; j++)
		{
			//飞机是否被敌机子弹击中
			if (Bplane[i].BBullter[j].m_flag && Plane.m_x + PLSIZE / 2.0 >= Bplane[i].BBullter[j].m_x
				&& Plane.m_x + PLSIZE / 2.0 <= Bplane[i].BBullter[j].m_x + BSIZE / 2.0
				&& Plane.m_y >= Bplane[i].BBullter[j].m_y && Plane.m_y <= Bplane[i].BBullter[j].m_y + BSIZE / 2.0)
				return false;
		}
	}
	return true;
}



int main()
{
Repeat:
	//添加随机种子
	srand((unsigned)time(NULL));
	//分数
	score = 0;
	initgraph(W, H);
	SetWindowText(GetHWnd(), "飞机小游戏");
	//加载图片
	jiazai();
	//飞机初始化
	Plane.m_x = W / 2.0 - PLSIZE / 2.0;
	Plane.m_y = H * 1.0 - PLSIZE * 1.0;
	Plane.m_flag = true;
	//子弹、敌机初始化
	for (int i = 0; i < 10; i++)
	{
		Bullter[i].m_flag = false;
		Bplane[i].m_flag = false;
		for (int j = 0; j < 5; j++)
		{
			Bplane[i].BBullter[j].m_flag = false;
		}
	}
	//时间初始化
	start = last = GetTickCount();
	start2=last2= GetTickCount();
	//背景音乐
	mciSendString("open 飞机游戏背景音乐.mp3 alias bkmusic", NULL, 0, NULL);
	mciSendString("play bkmusic repeat", NULL, 0, NULL);
	while (1)
	{
		//打印图片
		if (!Plane.m_flag)
		{
			string temp = "您的得分为：" + to_string(score);
			const char* defen = temp.c_str();
			MessageBox(GetHWnd(), defen, "游戏结束", MB_OK);
			//重新开始
			goto Repeat;
		}
		show();
		//操作
		operation();
		//子弹的移动
		tranbullterd();
		//敌机的创建
		for (int i = 0; i < 10; i++)
		{
			if (Bplane[i].m_flag==false && last2-start2>500	&&!rand()%5)
			{
				Bplane[i].m_flag = true;
				Bplane[i].m_x = abs(rand() % W * 1.0 - PLSIZE*1.0);
				Bplane[i].m_y = 0;
				start2 = last2;
				break;
			}
			last2 = GetTickCount();
			//超出下边界，消失
			if (Bplane[i].m_y > H)
			{
				Bplane[i].m_flag = false;
			}
			if (Bplane[i].m_flag)
			{
				for (int j = 0; j < 10; j++)
				{
					//判断子弹是否击中敌机
					if (Bullter[j].m_x + BSIZE / 2.0 >= Bplane[i].m_x && Bullter[j].m_x + BSIZE / 2.0 <= Bplane[i].m_x + PLSIZE
						&& Bullter[j].m_y >= Bplane[i].m_y && Bullter[j].m_y <= Bplane[i].m_y + PLSIZE)
					{
						Bullter[j].m_flag = false;
						Bplane[i].m_flag = false;
						mciSendString("close blastmusic", NULL, 0, NULL);
						mciSendString("open 爆炸声.mp3 alias blastmusic", NULL, 0, NULL);
						mciSendString("play blastmusic", NULL, 0, NULL);
							putimage(Bplane[i].m_x, Bplane[i].m_y, &Blastim, SRCAND);
							putimage(Bplane[i].m_x, Bplane[i].m_y, &Blast, SRCPAINT);
							Sleep(80);
							//增加分数
						score += 20;
					}
				}
				Bplane[i].m_y += 0.05;
			}
		}
		//敌机发射子弹
		FIREBbull();
		//判断飞机是否被击中
		if (!test())
		{
			Plane.m_flag = false;
		}
	}
	mciSendString("close bkmusic", NULL, 0, NULL);
	getch();
	closegraph();
	system("pause");
	return 0;
}