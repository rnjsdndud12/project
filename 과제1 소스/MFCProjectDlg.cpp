
// MFCProjectDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCProject.h"
#include "MFCProjectDlg.h"
#include "afxdialogex.h"
#include <thread>
#include <iostream>
#include <chrono>
#include <string>
#define WM_UPDATE_CIRCLES (WM_USER + 100)

using namespace std;
#define BLACK 0
#define WHITE 0xff

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
private:
	CImage m_image;

public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCProjectDlg 대화 상자



CMFCProjectDlg::CMFCProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCPROJECT_DIALOG, pParent)
	, m_nRad(10)
	, m_nLine(3)
	, center1(_T(""))
	, center2(_T(""))
	, center3(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NUM, m_nRad);
	DDX_Text(pDX, IDC_EDIT_NUM2, m_nLine);
	DDX_Text(pDX, IDC_EDIT2, center1);
	DDX_Text(pDX, IDC_EDIT3, center2);
	DDX_Text(pDX, IDC_EDIT4, center3);
}

BEGIN_MESSAGE_MAP(CMFCProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_START, &CMFCProjectDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_RESET, &CMFCProjectDlg::OnBnClickedReset)
	ON_BN_CLICKED(IDC_Circle, &CMFCProjectDlg::OnBnClickedCircle)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_RANDOM, &CMFCProjectDlg::OnBnClickedRandom)
	ON_MESSAGE(WM_UPDATE_CIRCLES, &CMFCProjectDlg::OnUpdateCircles)
	ON_BN_CLICKED(IDC_RANDOM2, &CMFCProjectDlg::OnBnClickedRandom2)
END_MESSAGE_MAP()


// CMFCProjectDlg 메시지 처리기

BOOL CMFCProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCProjectDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CPoint pos;
	GetCursorPos(&pos);
	ScreenToClient(&pos);

	if (validImgPos(pos.x, pos.y)) {
		if (count < 3 && image_state !=false) {
			UpdateData(true);
			circle[count++] = pos;

			unsigned char* fm = (unsigned char*)m_image.GetBits();

			createCircle(fm, pos, m_nRad, BLACK);
		}
		else if (validCirPos(pos.x, pos.y) && count == 3) {
			dragState = true;
		}

		else if(count == 3){
			AfxMessageBox(_T("3개 까지 생성 가능"));
		}

		CClientDC dc(this);
		m_image.Draw(dc, 0, 0);
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CMFCProjectDlg::createCircle(unsigned char* fm, CPoint pos, int m_nRad, int color)
{
	int nCenterX = pos.x;
	int nCenterY = pos.y;
	int nPitch = m_image.GetPitch();

	center1.Format(_T("%d, %d"), circle[0].x, circle[0].y);

	center2.Format(_T("%d, %d"), circle[1].x, circle[1].y);

	center3.Format(_T("%d, %d"), circle[2].x, circle[2].y);

	for (int j = pos.y - m_nRad; j < pos.y + m_nRad * 2; j++) {
		for (int i = pos.x- m_nRad; i < pos.x + m_nRad * 2; i++) {
			if(validImgPos(i, j) && isInCircle(i, j, nCenterX, nCenterY, m_nRad))
				fm[j * nPitch + i] = color;
		}
	}
	UpdateData(false);
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
}

void CMFCProjectDlg::OnBnClickedStart()
{
	if (image_state != true) {
		int nWidth = 640;
		int nHeight = 480;
		int nBpp = 8;

		m_image.Create(nWidth, -nHeight, nBpp);
		image_state = true;

		if (nBpp == 8) {
			static RGBQUAD rgb[256];
			for (int i = 0; i < 256; i++)
				rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
			m_image.SetColorTable(0, 256, rgb);
		}
		unsigned char* fm = (unsigned char*)m_image.GetBits();

		memset(fm, 0xff, sizeof(unsigned char) * nWidth * nHeight);

		CClientDC dc(this);
		m_image.Draw(dc, 0, 0);
	}
	else{
		AfxMessageBox(_T("Start 불가능(이미지 생성 되어 있음)"));
	}
}

bool CMFCProjectDlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int m_nRad)
{
	bool bRet = false;

	int dX = i - nCenterX;
	int dY = j - nCenterY;
	int dDist = dX * dX + dY * dY;

	if (dDist < m_nRad * m_nRad) {
		bRet = true;
	}
	return bRet;
}

bool CMFCProjectDlg::circleLine(int i, int j, int nCenterX, int nCenterY, int m_nRad, int m_nLine)
{
	UpdateData(TRUE);
	bool bRet = false;

	int dX = i - nCenterX;
	int dY = j - nCenterY;
	int dDist = dX * dX + dY * dY;

	int down = (m_nRad - m_nLine) * (m_nRad - m_nLine);
	int up = (m_nRad + m_nLine) * (m_nRad + m_nLine);

	if (down < dDist && dDist < up) {
		bRet = true;
	}
	return bRet;
}
bool CMFCProjectDlg::validImgPos(int x, int y)
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();

	CRect rect(0, 0, nWidth, nHeight);

	return rect.PtInRect(CPoint(x, y));

}

bool CMFCProjectDlg::validCirPos(int x, int y)
{
	for (int i = 0; i < 3; i++) {
		if (pow(m_nRad, 2) > pow(circle[i].x - x, 2) + pow(circle[i].y - y, 2))
			return true;
	}
	return false;
}

void CMFCProjectDlg::OnBnClickedReset()
{
	if (image_state != false) {
		count = 0;
		circle[0] = { 0, };
		center1.Format(_T(""));
		center2.Format(_T(""));
		center3.Format(_T(""));

		UpdateData(false);

		m_image.Destroy();
		image_state = false;
		OnBnClickedStart();
		
	}
	else {
		AfxMessageBox(_T("Reset 불가능(이미지 생성되어 있지 않음)"));
	}
}

void CMFCProjectDlg::OnBnClickedCircle()
{
	if (image_state != false) {
		if (count == 3) {
			drawCircle(0);
		}
		CClientDC dc(this);
		m_image.Draw(dc, 0, 0);
	}
	else {
		AfxMessageBox(_T("이미지 미생성"));
	}
}


void CMFCProjectDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CPoint pos;
	GetCursorPos(&pos);
	ScreenToClient(&pos);

	if(dragState){
		unsigned char* fm = (unsigned char*)m_image.GetBits();
		for (int i = 0; i < 3; i++) {
			if (pow(m_nRad, 2) > pow(circle[i].x - pos.x, 2) + pow(circle[i].y - pos.y, 2)) {
				drawCircle(WHITE);
				createCircle(fm, circle[i], m_nRad, WHITE);

				circle[i].x = pos.x;
				circle[i].y = pos.y;

			}
		}
		for(int j=0; j<3; j++)
			createCircle(fm, circle[j], m_nRad, BLACK);
		drawCircle(BLACK);
		CClientDC dc(this);
		m_image.Draw(dc, 0, 0);
		UpdateWindow();
	}
	CDialogEx::OnMouseMove(nFlags, point);
}

void CMFCProjectDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (dragState == true) {
		AfxMessageBox(_T("드래그 끝"));
		dragState = false;
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CMFCProjectDlg::drawCircle(int color)
{
	CPoint center;
	float d1 = float(circle[1].x - circle[0].x) / (circle[1].y - circle[0].y);
	float d2 = float(circle[2].x - circle[1].x) / (circle[2].y - circle[1].y);

	float cx = ((circle[2].y - circle[0].y) + (circle[1].x + circle[2].x) * d2 - (circle[0].x + circle[1].x) * d1) / (2 * (d2 - d1));
	float cy = (-d1 * (cx - (circle[0].x + circle[1].x) / 2) + (circle[0].y + circle[1].y) / 2);
	center.x = cx;
	center.y = cy;

	int r = sqrt(pow((float)(circle[0].x - cx), 2) + pow((float)(circle[0].y - cy), 2));

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	int Line = r + m_nLine;

	for (int j = center.y - Line; j < center.y + Line * 2; j++) {
		for (int i = center.x - Line; i < center.x + Line * 2; i++) {
			if (validImgPos(i, j) && circleLine(i, j, center.x, center.y, r, m_nLine))
				fm[j * nPitch + i] = color;
		}
	}
}

LRESULT CMFCProjectDlg::OnUpdateCircles(WPARAM wParam, LPARAM lParam)
{
	for (int i = 0; i < 10; i++) {
		randCircle();
		UpdateWindow();
		Sleep(2000);
	}

	return 0;
}

void threadProcess(CWnd* Cwnd, CRect rect)
{
	CMFCProjectDlg* pWnd = (CMFCProjectDlg*)Cwnd;
	
	pWnd->PostMessage(WM_UPDATE_CIRCLES, 0, 0);

}

void CMFCProjectDlg::OnBnClickedRandom()
{
	randCircle();
}

void CMFCProjectDlg::randCircle()
{
	srand(static_cast<unsigned int>(time(0)));
	if (image_state != false) {
		int nWidth = m_image.GetWidth();
		int nHeight = m_image.GetHeight();
		unsigned char* fm = (unsigned char*)m_image.GetBits();

		memset(fm, 0xff, sizeof(unsigned char) * nWidth * nHeight);

		for (int i = 0; i < 3; i++) {
			circle[i].x = rand() % nWidth;
			circle[i].y = rand() % nHeight;

			createCircle(fm, circle[i], m_nRad, 0);

		}
		count = 3;
		drawCircle(0);

		CClientDC dc(this);
		m_image.Draw(dc, 0, 0);
	}
	else {
		AfxMessageBox(_T("이미지 미생성"));
	}
}

void CMFCProjectDlg::OnBnClickedRandom2()
{
	if (image_state != false) {
		int nWidth = m_image.GetWidth();
		int nHeight = m_image.GetHeight();
		CRect rect(0, 0, nWidth, nHeight);

		thread _thread0(threadProcess, this, rect);

		_thread0.detach();
	}
	else {
		AfxMessageBox(_T("이미지 미생성"));
	}
}
