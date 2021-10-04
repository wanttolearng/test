//WinMain.cpp
// window 应用程序，多字符集
#include<windows.h>
#include "Mali.h"
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HINSTANCE hIns = 0;  //全局变量，程序实例句柄

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//-----------------------------------------------------
	HWND hwnd = 0;
	MSG msg;       //  装消息的结构体
	WNDCLASSEX wndclass;
	//-----------------------------------------------------

	hIns = hInstance;
	LPCSTR lClassName = "yue"; //窗口类名
	int nx=0;                  //窗口位置X
	int ny=0;                  //窗口位置Y
	int nwidth=0;              //窗口宽度
	int nheigh=0;              //窗口高度
	const CHAR * strTitle="yue";     //窗口标题名
	int pos_x=nx;
	if(pos_x<0){
		pos_x=0;
	}
	int pos_y=ny;
	if(pos_y<0){
		pos_y=0;
	}
	int nWidth=nwidth;
	if(nWidth<=0){
		nWidth = 500;
	}
	int nHeight=nheigh;
	if(nHeight<=0){
		nHeight = 500;
	}

	//----------------------创建窗口过程-----------------------------------
	//  1. 设计
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.cbSize = sizeof(wndclass);
	wndclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wndclass.hCursor = LoadCursor(0, MAKEINTRESOURCE(IDC_ARROW));
	wndclass.hIcon = 0;
	wndclass.hIconSm = 0;
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WindowProc;
	wndclass.lpszClassName = lClassName;
	wndclass.lpszMenuName = 0;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	// 2.  注册
	if (RegisterClassEx(&wndclass) == FALSE)
	{
		MessageBox(0, "注册失败", "提示", MB_OK);
		return 0;
	}
	//  3.  创建
	hwnd = CreateWindow(lClassName, strTitle, WS_OVERLAPPEDWINDOW, pos_x, pos_y, nWidth, nHeight, 0, 0, hInstance, 0);
	if (hwnd == 0)
	{
		MessageBox(0, "创建失败", "提示", MB_OK);
		return 0;
	}
	//  4.  显示窗口
	ShowWindow(hwnd, SW_SHOW);
	//---------------------------创建窗口过程------------------------------------------------

	//----------------------------消息循环-------------------------------------------
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	//----------------------------消息循环-------------------------------------------

	return 0;
}
CMali * pMali =NULL;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE: //窗口创建消息
	{
		if (pMali ==NULL)
		{
			pMali = new CMali;
			pMali->InitPeople(hIns);
		}
	}
	break;
	case WM_PAINT:  //重绘消息
	{
		PAINTSTRUCT ps ={0};		
		HDC hdc =::BeginPaint(hwnd,&ps);
		//-------------------------------------绘图
		if (pMali !=NULL){
			pMali->ShowPeople(hdc);
		}
		//-------------------------------------绘图结束
		::EndPaint(hwnd,&ps);
	}
	break;
	case WM_KEYDOWN:  //键盘按下触发消息
	{	
		if (pMali !=NULL){
//第一个参数：移动的方向需要键盘的上下左右键来判断，而键盘消息存储在wParam中
			pMali->MovePeopel(wParam);
		}
		RECT rect={0,0,500,500};//指定窗口的哪个部分到哪个部分为过时的
		::InvalidateRect(hwnd,&rect,FALSE);
	}
	break;
	case WM_CLOSE:
		{
			int res = ::MessageBox(NULL, "[WM_CLOSE] 是否确定退出", "提示", MB_OKCANCEL);
			if (res ==IDOK){ //点击 【确定】按钮
			
			}else if (res ==IDCANCEL){//点击【取消】按钮，不调用默认的消息处理 DefWindowProc 
			
				return 0;
			}else{
				return 0;
			}
		}
		break;
	case WM_DESTROY: 
		{
			//::MessageBox(NULL, "WM_DESTROY", "提示", MB_OK);
			//释放游戏资源:WM_CREATE中new的pMali要delete掉
			//一般情况下是这么写
			if(pMali){
				delete pMali;
				pMali = NULL;
			}
			PostQuitMessage(0);
		}
		break;
	case WM_QUIT:
		{
			::MessageBox(NULL, "WM_QUIT", "提示", MB_OK);
		}
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
	
}