#include<graphics.h>
#include<conio.h>
#include<ctime>
#include<string>
#include<cmath>
using namespace std;
#pragma comment(lib,"Winmm.lib")
#define W  600
#define H  600
#define PLSIZE  80	//�ɻ��Ĵ�С
#define BSIZE  40	//�ӵ��Ĵ�С
IMAGE Fimage;	//�ɻ���ԭͼ
IMAGE Fimage1;	//�ɻ�������ͼ
IMAGE Bimage;	//����ͼ
IMAGE Bulletim;	//�ӵ�ͼ
IMAGE Bulletim1;	//�ӵ�����ͼ
IMAGE Dijiim;	//�л�
IMAGE Dijiim1;	//�л�������ͼ
IMAGE Dijibull;	//�л��ӵ�
IMAGE Dijibuim;	//�л��ӵ�����ͼ
IMAGE Blast;
IMAGE Blastim;	//��ը����
struct Member
{
	double m_x;
	double m_y;
	bool m_flag;
};
//�л��ӵ�
struct Membull
{
	double m_x;
	double m_y;
	bool m_flag;
	double angle;
};
//�л�
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

//ʱ��ı仯��
DWORD start, last,start2,last2;
int score;

//����ͼƬ
void jiazai()
{
	loadimage(&Bimage, ".\\image\\�ǿ�.jpg", W, H);
	loadimage(&Fimage, ".\\image\\�ɻ�1.jpg", PLSIZE, PLSIZE);
	loadimage(&Fimage1, ".\\image\\����ͼ1.jpg", PLSIZE, PLSIZE);
	loadimage(&Bulletim, ".\\image\\�ӵ�2.jpg", BSIZE, BSIZE);
	loadimage(&Bulletim1, ".\\image\\����ͼ3.jpg", BSIZE, BSIZE);
	loadimage(&Dijiim, ".\\image\\�ɻ�2.jpg", BSIZE, BSIZE);
	loadimage(&Dijiim1, ".\\image\\����ͼ2.jpg", BSIZE, BSIZE);
	loadimage(&Dijibull, ".\\image\\�ӵ�3.jpg", BSIZE/2, BSIZE/2);
	loadimage(&Dijibuim, ".\\image\\�ӵ�3����ͼ.jpg", BSIZE/2, BSIZE/2);
	loadimage(&Blast, ".\\image\\��ը3.jpg", PLSIZE, PLSIZE);
	loadimage(&Blastim, ".\\image\\��ը3����ͼ.jpg", PLSIZE, PLSIZE);
	
}
//����
void operation()
{
	//�ϼ�
	if (GetAsyncKeyState(VK_UP))
	{
		if (Plane.m_y > 0)
			Plane.m_y -= 0.35;
	}
	//�¼�
	 if (GetAsyncKeyState(VK_DOWN)&0x8000)
	{
		if (Plane.m_y < H*1.0 - PLSIZE*1.0)
			Plane.m_y += 0.35;
	}
	//���
	 if (GetAsyncKeyState(VK_LEFT))
	{
		if (Plane.m_x > -PLSIZE / 2.0)
			Plane.m_x -= 0.35;
	}
	//�Ҽ�
    if (GetAsyncKeyState(VK_RIGHT))
	{
		if (Plane.m_x < (W - PLSIZE / 2.0)*1.0)
			Plane.m_x += 0.35;
	}
	//�ո�
	if (GetAsyncKeyState(VK_SPACE) && last - start > 80)		//ÿ���ӵ����80���룬���������ã��������ӵ��ص�
	{
		//�����ӵ�
		for (int i = 0; i < 10; i++)
		{
			if (!Bullter[i].m_flag )
			{
				Bullter[i].m_x = Plane.m_x + PLSIZE / 2.0 - BSIZE / 2.0;
				Bullter[i].m_y = Plane.m_y - BSIZE;
				Bullter[i].m_flag = true;	
				break;	//һ��ֻ����һ��
			}
		}
		start = last;	//ʱ������
	}
	//ʱ�������
	last = GetTickCount();
}
//��ʾͼƬ
void show()
{
	BeginBatchDraw();
	//����ͼ
	putimage(0, 0, &Bimage);
	//�ɻ�ͼ
	if (Plane.m_flag)
	{
		putimage(Plane.m_x, Plane.m_y, &Fimage1, SRCAND);
		putimage(Plane.m_x, Plane.m_y, &Fimage, SRCPAINT);
	}

	for (int i = 0; i < 10; i++)
	{
		//�ӵ�ͼ
		if (Bullter[i].m_flag)
		{
			
			putimage(Bullter[i].m_x, Bullter[i].m_y, &Bulletim1, SRCAND);
			putimage(Bullter[i].m_x, Bullter[i].m_y, &Bulletim, SRCPAINT);
		}
		//�л�ͼ
		if (Bplane[i].m_flag)
		{
			putimage(Bplane[i].m_x, Bplane[i].m_y, &Dijiim1, SRCAND);
			putimage(Bplane[i].m_x, Bplane[i].m_y, &Dijiim, SRCPAINT);
		}
		//�л��ӵ�
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
//�ӵ����ƶ�
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
		//�л��ӵ����ƶ�
		for (int j = 0; j < 5; j++)
		{
			if (Bplane[i].BBullter[j].m_flag)
			{
				Bplane[i].BBullter[j].m_x += 0.02 * Bplane[i].BBullter[j].angle;
				Bplane[i].BBullter[j].m_y += 0.1;
				//�����߿���ʧ
				if (Bplane[i].BBullter[j].m_x<0 || Bplane[i].BBullter[j].m_x>W || Bplane[i].BBullter[j].m_y > H	|| Bplane[i].BBullter[j].m_y <0)
				{
					Bplane[i].BBullter[j].m_flag = false;
				}
			}
		}
	}
}
//�л��ͷ��ӵ�
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
//�жϷɻ��Ƿ�����
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
			//�ɻ��Ƿ񱻵л��ӵ�����
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
	//����������
	srand((unsigned)time(NULL));
	//����
	score = 0;
	initgraph(W, H);
	SetWindowText(GetHWnd(), "�ɻ�С��Ϸ");
	//����ͼƬ
	jiazai();
	//�ɻ���ʼ��
	Plane.m_x = W / 2.0 - PLSIZE / 2.0;
	Plane.m_y = H * 1.0 - PLSIZE * 1.0;
	Plane.m_flag = true;
	//�ӵ����л���ʼ��
	for (int i = 0; i < 10; i++)
	{
		Bullter[i].m_flag = false;
		Bplane[i].m_flag = false;
		for (int j = 0; j < 5; j++)
		{
			Bplane[i].BBullter[j].m_flag = false;
		}
	}
	//ʱ���ʼ��
	start = last = GetTickCount();
	start2=last2= GetTickCount();
	//��������
	mciSendString("open �ɻ���Ϸ��������.mp3 alias bkmusic", NULL, 0, NULL);
	mciSendString("play bkmusic repeat", NULL, 0, NULL);
	while (1)
	{
		//��ӡͼƬ
		if (!Plane.m_flag)
		{
			string temp = "���ĵ÷�Ϊ��" + to_string(score);
			const char* defen = temp.c_str();
			MessageBox(GetHWnd(), defen, "��Ϸ����", MB_OK);
			//���¿�ʼ
			goto Repeat;
		}
		show();
		//����
		operation();
		//�ӵ����ƶ�
		tranbullterd();
		//�л��Ĵ���
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
			//�����±߽磬��ʧ
			if (Bplane[i].m_y > H)
			{
				Bplane[i].m_flag = false;
			}
			if (Bplane[i].m_flag)
			{
				for (int j = 0; j < 10; j++)
				{
					//�ж��ӵ��Ƿ���ел�
					if (Bullter[j].m_x + BSIZE / 2.0 >= Bplane[i].m_x && Bullter[j].m_x + BSIZE / 2.0 <= Bplane[i].m_x + PLSIZE
						&& Bullter[j].m_y >= Bplane[i].m_y && Bullter[j].m_y <= Bplane[i].m_y + PLSIZE)
					{
						Bullter[j].m_flag = false;
						Bplane[i].m_flag = false;
						mciSendString("close blastmusic", NULL, 0, NULL);
						mciSendString("open ��ը��.mp3 alias blastmusic", NULL, 0, NULL);
						mciSendString("play blastmusic", NULL, 0, NULL);
							putimage(Bplane[i].m_x, Bplane[i].m_y, &Blastim, SRCAND);
							putimage(Bplane[i].m_x, Bplane[i].m_y, &Blast, SRCPAINT);
							Sleep(80);
							//���ӷ���
						score += 20;
					}
				}
				Bplane[i].m_y += 0.05;
			}
		}
		//�л������ӵ�
		FIREBbull();
		//�жϷɻ��Ƿ񱻻���
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