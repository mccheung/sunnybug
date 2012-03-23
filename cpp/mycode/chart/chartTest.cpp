// chartTest.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "chartTest.h"
#include "DispChart.h"
#include <vector>
#include <math.h>
#define MAX_LOADSTRING 100



// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

// �˴���ģ���а����ĺ�����ǰ������:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

VOID CALLBACK TimerProc( HWND hwnd,  UINT uMsg, UINT_PTR idEvent,DWORD dwTime);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_CHARTTEST, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_CHARTTEST);

	// ����Ϣѭ��:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
//  ע��: 
//
//    ����ϣ��������ӵ� Windows 95 ��
//    ��RegisterClassEx������֮ǰ�˴����� Win32 ϵͳ����ʱ��
//    ����Ҫ�˺��������÷������ô˺���
//    ʮ����Ҫ������Ӧ�ó���Ϳ��Ի�ù�����
//   ����ʽ��ȷ�ġ�Сͼ�ꡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_CHARTTEST);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(CreateSolidBrush(RGB(0xcc,0xcc,0xcc)));
	wcex.lpszMenuName	= (LPCTSTR)IDC_CHARTTEST;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   ����: InitInstance(HANDLE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ����: WndProc(HWND, unsigned, WORD, LONG)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	static int cxClient, cyClient;

	static std::vector<double> data[3];

	//static CDAQContAI ai("ai0","Dev1/ai0",1,100,10000,100);
    static CChart chart(hWnd);

	

	chart.SetClrScaleSelectBg(RGB(0,0,0));

	switch (message) 
	{
	case WM_CREATE:
		{
		
			/*
			// �趨ʱ�� 
			SetTimer(hWnd,1,1000,NULL);

			
			chart.SetGridColor(RGB(255,0,0));
			chart.SetGriddx(10);
			chart.SetClrLabel(RGB(0,0,255));
			chart.SetXLabel("t/min");
			chart.SetYLabel("V/v");
			chart.SetRulerXFormat("%.2f");
			chart.SetGriddy( 0.01);
			chart.SetXRange( 0, 100);
			chart.SetYRange( -5, 5);
	
		*/
			chart.SetYRange(-10,10);
			chart.SetGriddy(2);
			
			int length = 1000;
			double amp = 5;
			for(int i=0;i<length;i++)
			{
				double t = (20 * 3.1415926 / length) * i;
				double y1 = amp*sin(t);
				double y2 = (amp/2)*cos(t);
				data[0].push_back(t);
				data[1].push_back(y1);
				data[2].push_back(y2);
			}
			 chart.AddMCurves(data,3);
			 chart.SetCurveColor(0,RGB(0,0,0));
			
            /*

			chart.AddACurve(&ai.m_Time);
			chart.AddMCurves(ai.m_Data,5);

			ai.StartTask();*/

		}
		break;
	case WM_TIMER:
		chart.Move(1,0);
		chart.ShowCurves();
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// �����˵�ѡ��:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_LBUTTONDOWN:
		
		chart.OnLeftButtonDown(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_LBUTTONUP:
		chart.OnLeftButtonUp(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_RBUTTONDOWN:
		chart.OnRightButtonDown(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_RBUTTONUP:
		chart.OnRightButtonUp(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_MOUSEMOVE:
		chart.OnMouseMove(LOWORD(lParam), HIWORD(lParam));
		break;
	case 0x020A:
		{
			POINT pt = { LOWORD(lParam), HIWORD(lParam) };
			ScreenToClient( hWnd,&pt );
		    chart.OnMouseWheel(wParam, pt.x, pt.y);
		}
		break;
	case WM_SIZE:
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: �ڴ���������ͼ����..
		RECT rect;
		GetClientRect(hWnd,&rect);

		chart.SetChartDC(hdc);
 
		chart.SetChartAndWindowPosition(rect);
		//chart.ShowAt(rect);
		//chart.ShowAt(rect);
		 chart.ShowCurves();
		

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		KillTimer(hWnd,1);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}

