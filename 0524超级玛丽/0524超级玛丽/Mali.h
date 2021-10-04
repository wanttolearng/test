#include<Windows.h>
#include "resource.h"
class CMali{
public:
	int m_nx;
	int m_ny;
	int m_nDirection;//方向
   //创建四个图片资源对应的句柄
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
		::DeleteObject(m_hUp);//删除四个图片资源对应的句柄
		m_hUp = NULL;

		::DeleteObject(m_hDown);
		m_hDown = NULL;

		::DeleteObject(m_hLeft);
		m_hLeft = NULL;

		::DeleteObject(m_hRight);
		m_hRight = NULL;
	}
public:
	//类里面不是有构造函数，那个不是初始化的吗？为啥又来一个初始化？
	void InitPeople(HINSTANCE hIns){//xy方向可以固定不用传，故可以不作为参数
								//实例句柄要传（LoadBitmap参数之一）
		m_nx=200;
		m_ny=200;

		//加载位图资源，并把资源赋值给左值
		m_hUp=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_up));
		m_hDown=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_down));
		m_hLeft=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_left));
		m_hRight=::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_right));
	}

	//让人显示在屏幕上
	void ShowPeople(HDC hdc){//是做一个贴图的流程，所以想想有什么参数
		//1.创建兼容性DC
		HDC compDC=::CreateCompatibleDC(hdc);
		//2.选入相应的位图
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
		//3.贴图
		::BitBlt(hdc,m_nx,m_ny,60,60,compDC,0,0,SRCAND);
		//4.删除兼容性DC
		::DeleteDC(compDC);
		compDC = NULL;
	}
	//移动有三个要点：移动的频率，方向和步长
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