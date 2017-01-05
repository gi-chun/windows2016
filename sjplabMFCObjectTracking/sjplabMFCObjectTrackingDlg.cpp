
// sjplabMFCObjectTrackingDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "sjplabMFCObjectTracking.h"
#include "sjplabMFCObjectTrackingDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
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


// CsjplabMFCObjectTrackingDlg 대화 상자



CsjplabMFCObjectTrackingDlg::CsjplabMFCObjectTrackingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SJPLABMFCOBJECTTRACKING_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CsjplabMFCObjectTrackingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OK, mbtnclose);
	DDX_Control(pDX, IDC_OBJTRACKING, mobjecttracking);
	DDX_Control(pDX, IDC_CONFIG, mbtnconfig);
	DDX_Control(pDX, IDC_PIC_PREVIEW, mPreviewCtl);
	DDX_Control(pDX, IDC_STATIC_SOURCE, stSource);
	DDX_Control(pDX, IDC_STATIC_METHOD, stMethod);
	DDX_Control(pDX, IDC_COMBO_METHOD, cbMethod);
	DDX_Control(pDX, IDC_COMBO_SOURCE, cbSource);
}

BEGIN_MESSAGE_MAP(CsjplabMFCObjectTrackingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
//	ON_COMMAND(IDOK, &CsjplabMFCObjectTrackingDlg::OnIdok)
ON_BN_CLICKED(IDC_OK, &CsjplabMFCObjectTrackingDlg::OnClickedOk)
ON_BN_CLICKED(IDC_CONFIG, &CsjplabMFCObjectTrackingDlg::OnClickedConfig)
ON_BN_CLICKED(IDC_OBJTRACKING, &CsjplabMFCObjectTrackingDlg::OnClickedObjtracking)
ON_WM_DESTROY()
ON_CBN_SELCHANGE(IDC_COMBO_METHOD, &CsjplabMFCObjectTrackingDlg::OnSelchangeComboMethod)
ON_CBN_SELCHANGE(IDC_COMBO_SOURCE, &CsjplabMFCObjectTrackingDlg::OnSelchangeComboSource)
ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CsjplabMFCObjectTrackingDlg 메시지 처리기

BOOL CsjplabMFCObjectTrackingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	ShowWindow(SW_MINIMIZE);

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	/*mbtnclose.LoadBitmaps(IDR_MAINFRAME, IDR_MAINFRAME);
	mobjecttracking.LoadBitmaps(IDR_MAINFRAME, IDR_MAINFRAME);
	*/

	if (m_CImage.Load(IDB_PNG_LINK)) {
		htbnmp = m_CImage;

		mbtnclose.SetBitmaps(htbnmp, RGB(255,255,255), NULL, RGB(255, 255, 255));
		mbtnclose.SetAlign(CButtonST::ST_ALIGN_OVERLAP, FALSE);
		mbtnclose.SetPressedStyle(CButtonST::BTNST_PRESSED_TOPBOTTOM, FALSE);
		mbtnclose.SizeToContent();
		mbtnclose.DrawBorder(FALSE, FALSE);
		mbtnclose.DrawTransparent();
		
		mbtnconfig.SetBitmaps(htbnmp, RGB(255, 255, 255), NULL, RGB(255, 255, 255));
		mbtnconfig.SetAlign(CButtonST::ST_ALIGN_OVERLAP, FALSE);
		mbtnconfig.SetPressedStyle(CButtonST::BTNST_PRESSED_TOPBOTTOM, FALSE);
		mbtnconfig.SizeToContent();
		mbtnconfig.DrawBorder(FALSE, FALSE);
		mbtnconfig.DrawTransparent();
	}

	htbnmp = NULL;
	m_CImage.Detach();

	if (m_CImage.Load(IDB_PNG_PLUS)) {
		htbnmp = m_CImage;

		mobjecttracking.SetBitmaps(htbnmp, RGB(255, 255, 255), NULL, RGB(255, 255, 255));
		mobjecttracking.SetAlign(CButtonST::ST_ALIGN_OVERLAP, FALSE);
		mobjecttracking.SetPressedStyle(CButtonST::BTNST_PRESSED_TOPBOTTOM, FALSE);
		mobjecttracking.SizeToContent();
		mobjecttracking.DrawBorder(FALSE, FALSE);
		mobjecttracking.DrawTransparent();
	}

	//SetWindowPos(&this->wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	if (!mPreviewCtl.isEnableVideo()) {
		AfxMessageBox(_T("해당하는 캠 장치가 없습니다. "));
	}
	else {
		mPreviewCtl.initObjectTracking();
		mPreviewCtl.startMyTimer(1);
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CsjplabMFCObjectTrackingDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CsjplabMFCObjectTrackingDlg::OnPaint()
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
HCURSOR CsjplabMFCObjectTrackingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CsjplabMFCObjectTrackingDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	CRect rect;

	GetClientRect(&rect);

	CBrush myBrush(RGB(0, 0, 0));    // dialog background color

	CBrush *pOld = pDC->SelectObject(&myBrush);

	BOOL bRes = pDC->PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);

	pDC->SelectObject(pOld);    // restore old brush

	return bRes;                       // CDialog::OnEraseBkgnd(pDC);
	//return CDialogEx::OnEraseBkgnd(pDC);
}

//void CsjplabMFCObjectTrackingDlg::OnIdok()
//{
//	// TODO: Add your command handler code here
//}


void CsjplabMFCObjectTrackingDlg::OnClickedOk()
{
	// TODO: Add your control notification handler code here
	::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
}


void CsjplabMFCObjectTrackingDlg::OnClickedConfig()
{
	// TODO: Add your control notification handler code here
}

void CsjplabMFCObjectTrackingDlg::changeTrackingButton()
{
	htbnmp = NULL;
	m_CImage.Detach();

	if (m_CImage.Load(IDB_PNG_PLUS)) {
		htbnmp = m_CImage;

		mobjecttracking.SetBitmaps(htbnmp, RGB(255, 255, 255), NULL, RGB(255, 255, 255));
		mobjecttracking.SetAlign(CButtonST::ST_ALIGN_OVERLAP, FALSE);
		mobjecttracking.SetPressedStyle(CButtonST::BTNST_PRESSED_TOPBOTTOM, FALSE);
		mobjecttracking.SizeToContent();
		mobjecttracking.DrawBorder(FALSE, FALSE);
		mobjecttracking.DrawTransparent();
	}
}
void CsjplabMFCObjectTrackingDlg::OnClickedObjtracking()
{
	// TODO: Add your control notification handler code here
	mPreviewCtl.tracking = (mPreviewCtl.tracking) ? FALSE : TRUE;
	if (mPreviewCtl.tracking) {
		mPreviewCtl.selectObject();

		htbnmp = NULL;
		m_CImage.Detach();

		if (m_CImage.Load(IDB_PNG_CROSS)) {
			htbnmp = m_CImage;

			mobjecttracking.SetBitmaps(htbnmp, RGB(255, 255, 255), NULL, RGB(255, 255, 255));
			mobjecttracking.SetAlign(CButtonST::ST_ALIGN_OVERLAP, FALSE);
			mobjecttracking.SetPressedStyle(CButtonST::BTNST_PRESSED_TOPBOTTOM, FALSE);
			mobjecttracking.SizeToContent();
			mobjecttracking.DrawBorder(FALSE, FALSE);
			mobjecttracking.DrawTransparent();
		}
	}
	else {
		mPreviewCtl.roiStartPoint.x = 0; mPreviewCtl.roiStartPoint.y = 0;
		mPreviewCtl.roiEndPoint.x = 0; mPreviewCtl.roiEndPoint.y = 0;
		mPreviewCtl.clearSelectObject();

		htbnmp = NULL;
		m_CImage.Detach();

		if (m_CImage.Load(IDB_PNG_PLUS)) {
			htbnmp = m_CImage;

			mobjecttracking.SetBitmaps(htbnmp, RGB(255, 255, 255), NULL, RGB(255, 255, 255));
			mobjecttracking.SetAlign(CButtonST::ST_ALIGN_OVERLAP, FALSE);
			mobjecttracking.SetPressedStyle(CButtonST::BTNST_PRESSED_TOPBOTTOM, FALSE);
			mobjecttracking.SizeToContent();
			mobjecttracking.DrawBorder(FALSE, FALSE);
			mobjecttracking.DrawTransparent();
		}
	}
}

void CsjplabMFCObjectTrackingDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here

	mPreviewCtl.clearObjectTracking();
}


void CsjplabMFCObjectTrackingDlg::OnSelchangeComboMethod()
{
	// TODO: Add your control notification handler code here
}


void CsjplabMFCObjectTrackingDlg::OnSelchangeComboSource()
{
	// TODO: Add your control notification handler code here
}


HBRUSH CsjplabMFCObjectTrackingDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	COLORREF red = RGB(0, 0, 0);

	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC_SOURCE:
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->SetBkColor(red);
	case IDC_STATIC_METHOD:
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->SetBkColor(red);
	case IDC_COMBO_METHOD:
		pDC->SetTextColor(RGB(255, 0, 0));
		//pDC->SetDCBrushColor(RGB(255, 0, 0));
		//pDC->SetBkMode(TRANSPARENT);
		pDC->SetBkColor(red);
	case IDC_COMBO_SOURCE:
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->SetBkColor(red);
	}
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}
