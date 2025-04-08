
// MFCProjectDlg.h: 헤더 파일
//

#pragma once


// CMFCProjectDlg 대화 상자
class CMFCProjectDlg : public CDialogEx
{
// 생성입니다.
private:
	CImage m_image;
	bool image_state= false;
	bool validImgPos(int x, int y);
	bool validCirPos(int x, int y); 
	bool dragState = false;
	CPoint circle[3];
	int count=0;
public:
	CMFCProjectDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCPROJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void createCircle(unsigned char* fm, CPoint pos, int m_nRad, int color);
	afx_msg void OnBnClickedStart();
	bool isInCircle(int i, int j, int nCenterX, int nCenterY, int m_nRad);
	bool circleLine(int i, int j, int nCenterX, int nCenterY, int m_nRad, int m_nLine);
	int m_nRad;
	afx_msg void OnBnClickedReset();
	afx_msg void OnBnClickedCircle();
	int m_nLine;
	CString center1;
	CString center2;
	CString center3;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void drawCircle(int color);
	afx_msg void OnBnClickedRandom();
	void randCircle();
	LRESULT OnUpdateCircles(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedRandom2();
};
