#ifndef _DISPCHART_H
#define _DISPCHART_H
#include <windows.h>
#include <vector>
#include <string>

// ͼ�����:���ڻ�������ϵ������
class CChartBase
{
protected:
	HDC       m_hChartDC;       // ͼ����Ƶ�DC
	RECT      m_rtWindow;       // ���괰��,���а���ͼ����ʾ����������,����    
	RECT      m_rtChart;        // ͼ����ʾ��(������m_rtWindow)

	// ������ʾ�߽�
	double    m_xStart;         // ʵ������x�����
	double    m_xEnd;           //         x���յ�
	double    m_yStart;         //         y�����
	double    m_yEnd;           //         y���յ�

	// ��ʾͼ����
	COLORREF  m_clrChartBg;     // ��ʾ������ɫ
	COLORREF  m_clrChartBorder; //       �߿�ɫ

	// ����
	bool      m_bGridOn;        // ���������Ƿ���ʾ
	double    m_dxGrid;         // ����Ԫ��
	double    m_dyGrid;         // ����Ԫ��
	COLORREF  m_clrGrid;        // ��������ɫ

	// ������,���,���
	char      m_xLabel[20];
	char      m_yLabel[20];
	bool      m_bxLabelOn; 
	bool      m_byLabelOn;

	bool      m_bxRulerOn;
	bool      m_byRulerOn;
	char      m_szRulerXFormat[128];
	char      m_szRulerYFormat[128];

	COLORREF  m_clrLabel;      // ������ֺͿ̶�������ɫ

	// ��������
	LOGFONT     m_logFont;

	// ��������

public:

	// ��������
	void SetChartDC(HDC hdc);
	HDC  GetChartDC() const ;
	void SetChartWindowPosition(RECT rect);
	void SetChartWindowPosition(int left, int top, int right, int bottom);
	RECT GetChartWindowPosition() const;
	void SetChartPosition(RECT rect);
	void SetChartPosition(int left, int top, int right, int bottom);

	RECT GetChartPosition() const;
	int  GetChartWidth()const  { return m_rtChart.right - m_rtChart.left ; };
	int  GetChartHeight()const { return m_rtChart.bottom - m_rtChart.top ; };
	int  GetChartWindowWidth() const { return m_rtWindow.right - m_rtWindow.left; };
	int  GetChartWindowHeight() const{ return m_rtWindow.bottom - m_rtWindow.top; };

	// ������ʾ�߽�
	double SetXStart(double xStart);
	double SetXEnd(double xEnd);
	void   SetXRange(double xStart,double xEnd);
	double SetYStart(double yStart);
	double SetYEnd(double yEnd);
	void   SetYRange(double yStart,double yEnd);
	double GetXStart()const;
	double GetXEnd()const;
	double GetYStart()const;
	double GetYEnd()const;
    
	// ��ʾͼ����
	void      SetClrChartBg(COLORREF clr);
	COLORREF  GetClrChartGb()const;
	void      SetClrChartBorder(COLORREF clr);
	COLORREF  GetClrChartBorder()const;

	// ����
	double   SetGriddx(double dxGrid);              // ����������,����ǰһ��ֵ
	double   SetGriddy(double dyGrid);              // ��������߶�,����ǰһ��ֵ
	void     SetGridxy(double dxGrid,double dyGrid);
	COLORREF SetGridColor(COLORREF color);          // ����������ɫ,����ǰһ��ֵ
	void SetGridOn();                               // ��������Ϊ��ʾ״̬
	void SetGridOff();                              // ��������Ϊ�ر�״̬

	double   GetGriddx()const;
	double   GetGriddy()const;
	COLORREF GetGridColor()const;
	bool     GetGridStatus()const;

	// ������,���,���
	void    SetXLabel(const char* xLabel);
	void    SetYLabel(const char* yLabel);
	void    SetXLabelOn();
	void    SetXLabelOff();
	BOOL    GetXLabelStatus()const;
	void    SetYLabelOn();
	void    SetYLabelOff();
	BOOL    GetYLabelStatus()const;

	void    SetXRulerOn();
	void    SetXRulerOff();
	BOOL    GetXRulerStatus()const;
	void    SetYRulerOn();
	void    SetYRulerOff();
	BOOL    GetYRulerStatus()const;

	void    SetRulerXFormat(const char str[]) { strcpy(m_szRulerXFormat, str);};
	void    SetRulerYFormat(const char str[]) { strcpy(m_szRulerXFormat, str);};

	void     SetClrLabel(COLORREF clr);
	COLORREF GetClrLabel()const;

	// ����
	void    SetLogFont(LOGFONT logFont);
	LOGFONT GetLogFont()const;


	// ÿһ�������������ʵ��ֵ
	double GetYPerPix() const;
	double GetXPerPix() const;

protected:
	int  ShowChartBg();
	int  ShowGrid();
	int  ShowRuler();
	int  ShowLabel();

public:
	CChartBase();
	~CChartBase();

	int ShowAt(int left, int top, int right, int bottom); // ��rect����ʾ��ͼ�괰��,�ⲿ����øú���
	int ShowAt(RECT rect);
	int Show();                                           // ͨ�����ø��ֲ�����ʾ

	// ����ת�� r--real  s--screen 2--to
	int rx2sx(double rx);  
	int ry2sy(double ry);
	double sx2rx(int sx);
	double sy2ry(int sy);

	// ����任
	void Move(double drx, double dry);                   // ����ϵƽ��
	void ScaleCenter(double times);                      // ���������������ķ���
	                                                     // times>1ʱ,��ʾ��Χ����,����С������
	                                                     // times<1ʱ,��ʾ��Χ��С,�𵽷Ŵ������
	void ScaleX(double times);                           // X�᷶Χ���ţ���x�����ģ�
	void ScaleY(double times);                           // Y�᷶Χ���ţ���y�����ģ�
};

class CChart:public CChartBase
{
private:
	HWND       m_hWnd;           // ͼ�����ڵĴ��ڣ��ô��ڿ��Դ�����Ϣ������ʵ������任�ȣ�
	HDC        m_memDCWindow;    // �洢������ͼ���õ��ڴ���
	HBITMAP    m_bmpInDCWindow;  
	HDC        m_memDCChart;     // �洢chart���ڴ��豸���
    HBITMAP    m_bmpInDCChart;   // ͼ������Ӧ��λͼ���

	// ��������
public:
	
	std::vector<std::vector<double>*> m_pvCurvesData;             // ������ַ������,���Կ����������κ���vector<double>���͵�����
	std::vector<double>               m_vCurvesScale;             // �����������ֵ���������,Ĭ��Ϊ1,��������
	std::vector<std::string>         m_vsCurvesName;              // �������ߵ�����,Ĭ������Ϊx,y1,y2,y3..

	void   AddACurve(std::vector<double>* pvCurveData);          // ���һ�����ߣ���һ��Ϊx��
	void   AddMCurves(std::vector<double> pvCuveData[], int n);  // ���n������

	double GetDataAt(int m, int n);                    // ȡ����(��������)��m��0ʱΪx�����ݣ�m��1,2,3..Ϊ����1,2,3..��y����
	long   GetNumCurves();                             // �ж���������
	long   GetNumDataInCurve(int m);                   // ����m���ж��ٸ�����

	void   DeleteLastCurve();                          // ɾ�����һ������
	void   DeleteAllCurves();                          // ɾ����������

	void   SetCurveScale(int m, double scale);          // �趨m�����ߵ���������
	double GetCurveScale(int m);                        // ��ȡm�����ߵ�������֮

	void   SetCurveName (int m, char * name) ;                       // �趨m�����ߵ�����
    #define GetCurveName(m) (m_vsCurvesName.at(m).c_str())      // ��ȡm�����ߵ�����

	long    FindDataInX(double x);        // ����x��λ�� �����ڸ����� x1=<x<x2 ��ȡx1��λ�ã� ���ַ�����,û�ҵ�����-1
	                                      // X���±������������

	// ��������
private:
	std::vector<bool>       m_vbCurvesShow;         // ���������Ƿ���ʾ,Ĭ��Ϊ��ʾ(true)
	std::vector<int>        m_vCurvesLineWidth ;    // �������ߵ��߿�,[0]ʱ������;[1]..[n] �ֱ�Ϊ���ߵ��߿�Ĭ��Ϊ1
	std::vector<COLORREF>   m_vCurvesColor;         // �������ߵ���ɫ,[0]ʱ������;[1]..[n] �ֱ�Ϊ���ߵ���ɫ

public:
	void SetCurveLineWidth(int m, int width);       // Ϊm�����������߿�
	void SetCurveColor  (int m, COLORREF clr);      // Ϊm������������ɫ
	void SetCurveStatus (int m, bool bShow);        // Ϊm������������ʾ����,true��ʾ,false����
	int  GetCurveLineWidth(int m);                  // ���m�������߿�,���󷵻�-1
	COLORREF GetCurveColor(int m);                   // ���m��������ɫ,���󷵻�-1
	bool GetCurveStatus (int m);                    // ���m��������ʾ����

	// ���߻��ƺ�����ϵ
	void SetChartAndWindowPosition(RECT rect);         // ͬʱ�ı�m_rtChart��m_rtWindows
	void SetChartAndWindowPosition (int left, int top, int right, int bottom);

	void ShowCurves();


public:
	CChart(HWND hWnd = NULL);
	~CChart();

	// ������Ϣ����:���º��������ض��Ĵ�����Ϣ
	// ����϶�������ƽ�ƣ�����x�ᣩ
	// �Ҽ��϶�������һ�����Σ�ѡ���ض���x�᷶Χ���Ŵ�
	// ������£���ʾ��ǰx���Ӧ�����������ϵ�ֵ�������������ʾ���ں����궨λ��
	// �����飬�Ϲ��Ŵ��¹���С

	// ����궨�壺��chart�����ƶ�ʱΪʮ���ͣ���������Ϊָ��
	//               ����϶�ʱΪ���ͣ��Ҽ��϶�ʱΪ�Ŵ�
	//               �����ʾ������ʾ����ʱΪʮ����
private:
	bool   m_bLeftButtonDown;             // �������Ϊtrue
	bool   m_bRightButtonDown;            // �Ҽ�����Ϊture
	POINT  m_ptLeftButtonDown;            // ��¼ǰһ��������µ�����,(-1,-1)ʱ��ʾ�����µ�λ�ò���chart��
	POINT  m_ptRightButtonDown;           // ��¼ǰһ���Ҽ����µ�����,(-1,-1)ʱ��ʾ�����µ�λ�ò���chart��


    // �����Ҽ��϶�һ����Χ���ŵĳ�Ա�����ͳ�Ա����
	HBITMAP m_bmpRightButtonDown;             // �Ҽ�����ʱ������ʾ����λͼ
	HDC     m_memDCRightButtonDown;
	COLORREF m_clrScaleSelectBg;              // �Ҽ�ѡ���͸�����򱳾�ɫ
	COLORREF m_clrScaleSelectBorder;          //               �߿�ɫ
	int      m_nLineWidthOfScaleSelectBorder; //               �߿���
	int      m_nTransRate;                    //               ����͸����0---255

	// ���궨λ��
	COLORREF m_clrCoordinateLine;             // ���궨λ����ɫ
	int      m_nLineWidthCoordinateLine;      // ���궨λ�߿��

	// ������ʾ����
	COLORREF m_clrCoordWindowBg;               // ������ʾ���ڵı���ɫ
	COLORREF m_clrCoordWindowBorder;           // ������ʾ���ڵı߿�ɫ
	int      m_nLineWidthOfCoordWindowBorder;  //               �߿��߿�
	int      m_nCoordWindowTransRate;          //               ͸���� 0---255
	LOGFONT  m_lfCoordWindow;                  // ������ʾ�����ϵ�����


public:
	void SetClrScaleSelectBg(COLORREF clr) { m_clrScaleSelectBg = clr;};
	void SetClrScaleSelectBorder( COLORREF clr){ m_clrScaleSelectBorder = clr;};
	void SetLineWidthScaleSelectBorder( int width) {m_nLineWidthOfScaleSelectBorder = width;};
	void SetTransRate(int rate){ m_nTransRate = rate;};
	void SetClrCoordinateLine(COLORREF clr) { m_clrCoordinateLine = clr; };
	void SetLineWidthCoordinateLine( int width) { m_nLineWidthCoordinateLine = width; };


	COLORREF GetClrScaleSelectBg() const { return m_clrScaleSelectBg;};
	COLORREF GetClrScaleSelectBorder() const { return m_clrScaleSelectBorder;};
	COLORREF GetClrCoordinateLine() const { return m_clrCoordinateLine; };
	int      GetLineWidthScaleSelectBorder()const{ return m_nLineWidthOfScaleSelectBorder;};
	int      GetTransRate()const { return m_nTransRate;};
	int      GetLineWidthCoordinateLine()const { return m_nLineWidthCoordinateLine;};

	// ������ʾ����
	void  SetClrCoordWindowBg(COLORREF clr) { m_clrCoordWindowBg = clr ; } ;
	void  SetClrCoordWindowBorder(COLORREF clr) { m_clrCoordWindowBorder = clr ; } ;
	void  SetLineWidthCoordWindowBorder(int width) { m_nLineWidthOfCoordWindowBorder = width ; } ;
	void  SetCoordWindowTransRate(int rate) {  m_nCoordWindowTransRate = rate ; } ;
	void  SetCoordWindowLogFont(LOGFONT lf) {  m_lfCoordWindow = lf ; } ;

	COLORREF GetClrCoordWindowBg()const { return  m_clrCoordWindowBg ; } ;
	COLORREF GetClrCoordWindowBorder()const { return m_clrCoordWindowBorder ; } ;
	int      GetLineWidthCoordWindowBorder()const { return m_nLineWidthOfCoordWindowBorder ; } ;
	int      GetCoordWindowTransRate()const { return m_nCoordWindowTransRate ; } ; 
	LOGFONT  GetCoordWindowLogFont()const { return m_lfCoordWindow; } ;

public:
	int  OnLeftButtonDown(int x, int y);  // WM_LBUTTONDOWN x,yΪ����ڴ����ϵ�λ��
	int  OnLeftButtonUp(int x, int y);    // WM_LBUTTONUP
	int  OnRightButtonDown(int x, int y); // WM_RBUTTONDOWN
	int  OnRightButtonUp(int x, int y);   // WM_RBUTTONUP
	int  OnMouseMove(int x, int y);       // WM_MOUSEMOVE
	int  OnMouseWheel(int zDelta, int x, int y);        // WM_MOUSEWHEEL               

	// ����������Ϣ����
	bool IsMouseInChart(int x, int y);    // �ж�pt��x��y���Ƿ���chart������
	bool IsMouseInChart(POINT pt); 


};
#endif