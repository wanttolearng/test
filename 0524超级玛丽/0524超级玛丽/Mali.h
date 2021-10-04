#include<Windows.h>
#include "resource.h"
class CMali{
public:
	int m_nx;
	int m_ny;
	int m_nDirection;//����
   //�����ĸ�ͼƬ��Դ��Ӧ�ľ��
	HBITMAP m_hUp;
	HBITMAP m_hDown;
	HBITMAP m_hLeft;
	HBITMAP m_hRight;
public:
	CMali(){
		m_nx=0;
		m_ny=0;
		m_nDirection=VK_LEFT;

		m_hUp=NULL;
		m_hDown=NULL;
		m_hLeft=NULL;
		m_hRight=NULL;
	}
	~CMali(){
		::DeleteObject(m_hUp);//ɾ���ĸ�ͼƬ��Դ��Ӧ�ľ��
		m_hUp = NULL;

		::DeleteObject(m_hDown);
		m_hDown = NULL;

		::DeleteObject(m_hLeft);
		m_hLeft = NULL;

		::DeleteObject(m_hRight);
		m_hRight = NULL;
	}
public:
	//�����治���й��캯�����Ǹ����ǳ�ʼ������Ϊɶ����һ����ʼ����
	void InitPeople(HINSTANCE hIns){//xy������Թ̶����ô����ʿ��Բ���Ϊ����
								//ʵ�����Ҫ����LoadBitmap����֮һ��
		m_nx=200;
		m_ny=200;

		//����λͼ��Դ��������Դ��ֵ����ֵ
		m_hUp=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_up));
		m_hDown=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_down));
		m_hLeft=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_left));
		m_hRight=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_right));
	}

	//������ʾ����Ļ��
	void ShowPeople(HDC hdc){//����һ����ͼ�����̣�����������ʲô����
		//1.����������DC
		HDC compDC=::CreateCompatibleDC(hdc);
		//2.ѡ����Ӧ��λͼ
		if (m_nDirection==VK_LEFT)
		{
			::SelectObject(compDC,m_hLeft);
		}else if (m_nDirection==VK_RIGHT)
		{
			::SelectObject(compDC,m_hRight);
		}
		else if (m_nDirection==VK_UP)
		{
			::SelectObject(compDC,m_hUp);
		}else if (m_nDirection==VK_DOWN)
		{
			::SelectObject(compDC,m_hDown);
		}	
		//3.��ͼ
		::BitBlt(hdc,m_nx,m_ny,60,60,compDC,0,0,SRCAND);
		//4.ɾ��������DC
		::DeleteDC(compDC);
		compDC = NULL;
	}
	//�ƶ�������Ҫ�㣺�ƶ���Ƶ�ʣ�����Ͳ���
	void MovePeopel(int direct,int step=4){
		switch (direct)
		{
		case VK_LEFT:
			if (m_nx-step<=0)
			{
				m_nx=0;
			}else
			{
				m_nx-=step;
			}
			m_nDirection=VK_LEFT;
			break;
		case VK_RIGHT:
			if (m_nx+step>=500-60)
			{
				m_nx=440;
			}else
			{
				m_nx+=step;
			}
			m_nDirection=VK_RIGHT;
			break;
		case VK_UP:
			if (m_ny-step<=0)
			{
				m_ny=0;
			}else
			{
				m_ny-=step;
			}
			m_nDirection=VK_UP;
			break;
		case VK_DOWN:
			if (m_ny+step>=500-60)
			{
				m_ny=440;
			}else
			{
				m_ny+=step;
			}
			m_nDirection=VK_DOWN;
			break;
		}
	}
};