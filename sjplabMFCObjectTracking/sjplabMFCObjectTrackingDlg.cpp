
// sjplabMFCObjectTrackingDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "sjplabMFCObjectTracking.h"
#include "sjplabMFCObjectTrackingDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define LIGHT_COLOR		250
#define DARK_COLOR		100


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
	: CBkDialogST(IDD_SJPLABMFCOBJECTTRACKING_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CsjplabMFCObjectTrackingDlg::DoDataExchange(CDataExchange* pDX)
{
	CBkDialogST::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OK, mbtnclose);
	DDX_Control(pDX, IDC_OBJTRACKING, mobjecttracking);
	DDX_Control(pDX, IDC_CONFIG, mbtnconfig);
	DDX_Control(pDX, IDC_PIC_PREVIEW, mPreviewCtl);
	//  DDX_Control(pDX, IDC_STATIC_SOURCE, stSource);
	//  DDX_Control(pDX, IDC_STATIC_METHOD, stMethod);
	//  DDX_Control(pDX, IDC_COMBO_METHOD, cbMethod);
	//  DDX_Control(pDX, IDC_COMBO_SOURCE, cbSource);
	//  DDX_Control(pDX, IDC_STATIC_BACK, m_rightBack);
	DDX_Control(pDX, IDC_STATIC_BACK, m_rightBack);
	DDX_Control(pDX, IDC_STATIC_CAMERA, m_camera_back);
	DDX_Control(pDX, IDC_STATIC_METHOD, m_method_back);
	DDX_Control(pDX, IDC_STATIC_SOURCE, m_source_back);
	DDX_Control(pDX, IDC_BTN_CMT, m_btnCmt);
	DDX_Control(pDX, IDC_BTN_CAM1, m_btnCam1);
	DDX_Control(pDX, IDC_BTN_CAM2, m_btnCam2);
	DDX_Control(pDX, IDC_BTN_DOWN, m_btnDown);
	DDX_Control(pDX, IDC_BTN_LEFT, m_btnLeft);
	DDX_Control(pDX, IDC_BTN_RIGHT, m_btnRight);
	DDX_Control(pDX, IDC_BTN_STREAM, m_btnStream);
	DDX_Control(pDX, IDC_BTN_TLD, m_btnTld);
	DDX_Control(pDX, IDC_BTN_UP, m_btnUp);
}

BEGIN_MESSAGE_MAP(CsjplabMFCObjectTrackingDlg, CBkDialogST)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_COMMAND(IDOK, &CsjplabMFCObjectTrackingDlg::OnIdok)
ON_BN_CLICKED(IDC_OK, &CsjplabMFCObjectTrackingDlg::OnClickedOk)
ON_BN_CLICKED(IDC_CONFIG, &CsjplabMFCObjectTrackingDlg::OnClickedConfig)
ON_BN_CLICKED(IDC_OBJTRACKING, &CsjplabMFCObjectTrackingDlg::OnClickedObjtracking)
ON_WM_DESTROY()
//ON_CBN_SELCHANGE(IDC_COMBO_METHOD, &CsjplabMFCObjectTrackingDlg::OnSelchangeComboMethod)
//ON_CBN_SELCHANGE(IDC_COMBO_SOURCE, &CsjplabMFCObjectTrackingDlg::OnSelchangeComboSource)
ON_STN_CLICKED(IDC_PIC_PREVIEW, &CsjplabMFCObjectTrackingDlg::OnStnClickedPicPreview)

ON_WM_CTLCOLOR()
//ON_WM_ERASEBKGND()
//ON_WM_NCPAINT()
//ON_WM_NCACTIVATE()
//ON_WM_NCHITTEST()
//ON_WM_NCLBUTTONDOWN()
//ON_WM_LBUTTONUP()
ON_BN_CLICKED(IDC_BTN_CAM1, &CsjplabMFCObjectTrackingDlg::OnClickedBtnCam1)
ON_BN_CLICKED(IDC_BTN_CAM2, &CsjplabMFCObjectTrackingDlg::OnClickedBtnCam2)
ON_BN_CLICKED(IDC_BTN_CMT, &CsjplabMFCObjectTrackingDlg::OnClickedBtnCmt)
ON_BN_CLICKED(IDC_BTN_DOWN, &CsjplabMFCObjectTrackingDlg::OnClickedBtnDown)
ON_BN_CLICKED(IDC_BTN_LEFT, &CsjplabMFCObjectTrackingDlg::OnClickedBtnLeft)
ON_BN_CLICKED(IDC_BTN_RIGHT, &CsjplabMFCObjectTrackingDlg::OnClickedBtnRight)
ON_BN_CLICKED(IDC_BTN_STREAM, &CsjplabMFCObjectTrackingDlg::OnClickedBtnStream)
ON_BN_CLICKED(IDC_BTN_TLD, &CsjplabMFCObjectTrackingDlg::OnClickedBtnTld)
ON_BN_CLICKED(IDC_BTN_UP, &CsjplabMFCObjectTrackingDlg::OnClickedBtnUp)
END_MESSAGE_MAP()


// CsjplabMFCObjectTrackingDlg 메시지 처리기

BOOL CsjplabMFCObjectTrackingDlg::OnInitDialog()
{
	CBkDialogST::OnInitDialog();

	SetBitmap(IDB_BKGROUND);
	//SetBitmap(IDB_SKY);
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

	//ShowWindow(SW_MINIMIZE);

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	/*mbtnclose.LoadBitmaps(IDR_MAINFRAME, IDR_MAINFRAME);
	mobjecttracking.LoadBitmaps(IDR_MAINFRAME, IDR_MAINFRAME);
	*/

	// button style [BUTTONSTYLE_FLAT / BUTTONSTYLE_SEMIFLAT / BUTTONSTYLE_3D]
	//m_cButton_Test1.m_nFlatStyle   = CMFCButton::BUTTONSTYLE_NOBORDERS;
	//m_cButton_Test1.m_bTransparent  = TRUE;    // 투명도 설정
	//m_cButton_Test1.m_bDrawFocus  = FALSE;
	//m_cButton_Test1.SetImage(hBit1, TRUE, hBit2);
	////    m_cButton_Test1.SizeToContent(TRUE);
	//m_cButton_Test1.SetWindowText("");
	//m_cButton_Test1.SetMouseCursorHand();

	m_currentSource = VIDEO_SOURCE_STREAM;
	m_currentMethod = METHOD_CMT;
	mPreviewCtl.m_currentMethod = m_currentMethod;

	m_btnStream.SetBitmaps(IDB_BMP_CHECK_SELECTED, RGB(255, 0, 255));
	m_btnStream.SetAlign(CButtonST::ST_ALIGN_OVERLAP, FALSE);
	m_btnStream.SetPressedStyle(CButtonST::BTNST_PRESSED_LEFTRIGHT, FALSE);
	m_btnStream.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 255, 255));
	m_btnStream.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	m_btnStream.SizeToContent();
	m_btnStream.DrawBorder(FALSE, FALSE);

	m_btnCam1.SetBitmaps(IDB_BMP_CHECK_NORMAL, RGB(255, 0, 255));
	m_btnCam1.SetAlign(CButtonST::ST_ALIGN_OVERLAP, FALSE);
	m_btnCam1.SetPressedStyle(CButtonST::BTNST_PRESSED_LEFTRIGHT, FALSE);
	m_btnCam1.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 255, 255));
	m_btnCam1.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	m_btnCam1.SizeToContent();
	m_btnCam1.DrawBorder(FALSE, FALSE);

	m_btnCam2.SetBitmaps(IDB_BMP_CHECK_NORMAL, RGB(255, 0, 255));
	m_btnCam2.SetAlign(CButtonST::ST_ALIGN_OVERLAP, FALSE);
	m_btnCam2.SetPressedStyle(CButtonST::BTNST_PRESSED_LEFTRIGHT, FALSE);
	m_btnCam2.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 255, 255));
	m_btnCam2.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	m_btnCam2.SizeToContent();
	m_btnCam2.DrawBorder(FALSE, FALSE);

	m_btnCmt.SetBitmaps(IDB_BMP_CHECK_SELECTED, RGB(255, 0, 255));
	m_btnCmt.SetAlign(CButtonST::ST_ALIGN_OVERLAP, FALSE);
	m_btnCmt.SetPressedStyle(CButtonST::BTNST_PRESSED_LEFTRIGHT, FALSE);
	m_btnCmt.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 255, 255));
	m_btnCmt.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	m_btnCmt.SizeToContent();
	m_btnCmt.DrawBorder(FALSE, FALSE);

	m_btnTld.SetBitmaps(IDB_BMP_CHECK_NORMAL, RGB(255, 0, 255));
	m_btnTld.SetAlign(CButtonST::ST_ALIGN_OVERLAP, FALSE);
	m_btnTld.SetPressedStyle(CButtonST::BTNST_PRESSED_LEFTRIGHT, FALSE);
	m_btnTld.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 255, 255));
	m_btnTld.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	m_btnTld.SizeToContent();
	m_btnTld.DrawBorder(FALSE, FALSE);

	m_btnUp.SetBitmaps(IDB_BMP_UP, RGB(255, 0, 255));
	m_btnUp.SetAlign(CButtonST::ST_ALIGN_OVERLAP, FALSE);
	m_btnUp.SetPressedStyle(CButtonST::BTNST_PRESSED_LEFTRIGHT, FALSE);
	m_btnUp.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 255, 255));
	m_btnUp.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	m_btnUp.SizeToContent();
	m_btnUp.DrawBorder(FALSE, FALSE);

	m_btnRight.SetBitmaps(IDB_BMP_RIGHT, RGB(255, 0, 255));
	m_btnRight.SetAlign(CButtonST::ST_ALIGN_OVERLAP, FALSE);
	m_btnRight.SetPressedStyle(CButtonST::BTNST_PRESSED_LEFTRIGHT, FALSE);
	m_btnRight.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 255, 255));
	m_btnRight.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	m_btnRight.SizeToContent();
	m_btnRight.DrawBorder(FALSE, FALSE);

	m_btnDown.SetBitmaps(IDB_BMP_DOWN, RGB(255, 0, 255));
	m_btnDown.SetAlign(CButtonST::ST_ALIGN_OVERLAP, FALSE);
	m_btnDown.SetPressedStyle(CButtonST::BTNST_PRESSED_LEFTRIGHT, FALSE);
	m_btnDown.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 255, 255));
	m_btnDown.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	m_btnDown.SizeToContent();
	m_btnDown.DrawBorder(FALSE, FALSE);

	m_btnLeft.SetBitmaps(IDB_BMP_LEFT, RGB(255, 0, 255));
	m_btnLeft.SetAlign(CButtonST::ST_ALIGN_OVERLAP, FALSE);
	m_btnLeft.SetPressedStyle(CButtonST::BTNST_PRESSED_LEFTRIGHT, FALSE);
	m_btnLeft.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(255, 255, 255));
	m_btnLeft.SetColor(CButtonST::BTNST_COLOR_FG_OUT, RGB(0, 0, 0));
	m_btnLeft.SizeToContent();
	m_btnLeft.DrawBorder(FALSE, FALSE);
	
	m_rightBack.SubclassDlgItem(IDC_STATIC_BACK, this);
	m_rightBack.SetTextColor(::GetSysColor(COLOR_INFOTEXT));
	m_rightBack.SetBkColor(RGB(70, 70, 70));

	m_source_back.SubclassDlgItem(IDC_STATIC_SOURCE, this);
	m_source_back.SetTextColor(RGB(255, 255, 255));
	m_source_back.SetBkColor(RGB(83, 83, 83));

	m_method_back.SubclassDlgItem(IDC_STATIC_METHOD, this);
	m_method_back.SetTextColor(RGB(255, 255, 255));
	m_method_back.SetBkColor(RGB(83, 83, 83));

	m_camera_back.SubclassDlgItem(IDC_STATIC_CAMERA, this);
	m_camera_back.SetTextColor(RGB(255, 255, 255));
	m_camera_back.SetBkColor(RGB(83, 83, 83));

	if (m_CImage.Load(IDB_PNG_EXIT)) {
		htbnmp = m_CImage;

		mbtnclose.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
		mbtnclose.m_bTransparent = TRUE;
		mbtnclose.m_bDrawFocus = FALSE;
		mbtnclose.SetImage(htbnmp, TRUE, htbnmp);
		mbtnclose.SetMouseCursorHand();
	}

	htbnmp = NULL;
	m_CImage.Detach();

	if (m_CImage.Load(IDB_PNG_TRACKING_NORMAL)) {
		htbnmp = m_CImage;

		mobjecttracking.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
		mobjecttracking.m_bTransparent = TRUE;
		mobjecttracking.m_bDrawFocus = FALSE;
		mobjecttracking.SetImage(htbnmp, TRUE, htbnmp);
		mobjecttracking.SetMouseCursorHand();
	}

	htbnmp = NULL;
	m_CImage.Detach();

	if (m_CImage.Load(IDB_PNG_CONFIG)) {
		htbnmp = m_CImage;

		mbtnconfig.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
		mbtnconfig.m_bTransparent = TRUE;
		mbtnconfig.m_bDrawFocus = FALSE;
		mbtnconfig.SetImage(htbnmp, TRUE, htbnmp);
		mbtnconfig.SetMouseCursorHand();
	}


	//SetWindowPos(&this->wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	if (!mPreviewCtl.isEnableVideo(m_currentSource)) {
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
		CBkDialogST::OnSysCommand(nID, lParam);
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
		CBkDialogST::OnPaint();
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

	if (m_CImage.Load(IDB_PNG_TRACKING_NORMAL)) {
		htbnmp = m_CImage;

		mobjecttracking.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
		mobjecttracking.m_bTransparent = TRUE;
		mobjecttracking.m_bDrawFocus = FALSE;
		mobjecttracking.SetImage(htbnmp, TRUE, htbnmp);
		mobjecttracking.SetMouseCursorHand();
		mobjecttracking.Invalidate();
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

		if (m_CImage.Load(IDB_PNG_TRACKING_PRESSED)) {
			htbnmp = m_CImage;

			mobjecttracking.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
			mobjecttracking.m_bTransparent = TRUE;
			mobjecttracking.m_bDrawFocus = FALSE;
			mobjecttracking.SetImage(htbnmp, TRUE, htbnmp);
			mobjecttracking.SetMouseCursorHand();
		}
	}
	else {
		mPreviewCtl.roiStartPoint.x = 0; mPreviewCtl.roiStartPoint.y = 0;
		mPreviewCtl.roiEndPoint.x = 0; mPreviewCtl.roiEndPoint.y = 0;
		mPreviewCtl.clearSelectObject();

		htbnmp = NULL;
		m_CImage.Detach();

		if (m_CImage.Load(IDB_PNG_TRACKING_NORMAL)) {
			htbnmp = m_CImage;

			mobjecttracking.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
			mobjecttracking.m_bTransparent = TRUE;
			mobjecttracking.m_bDrawFocus = FALSE;
			mobjecttracking.SetImage(htbnmp, TRUE, htbnmp);
			mobjecttracking.SetMouseCursorHand();
		}
	}

	mobjecttracking.Invalidate();
}

void CsjplabMFCObjectTrackingDlg::OnDestroy()
{
	CBkDialogST::OnDestroy();

	// TODO: Add your message handler code here

	mPreviewCtl.clearObjectTracking();
}


//void CsjplabMFCObjectTrackingDlg::OnSelchangeComboMethod()
//{
//	// TODO: Add your control notification handler code here
//}


//void CsjplabMFCObjectTrackingDlg::OnSelchangeComboSource()
//{
//	// TODO: Add your control notification handler code here
//}


HBRUSH CsjplabMFCObjectTrackingDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CBkDialogST::OnCtlColor(pDC, pWnd, nCtlColor);

	//HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	/*if (pWnd->GetDlgCtrlID() == IDC_STATIC_PIC) {
		pDC->SetBkColor(RGB(255, 0, 0));
	}*/
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}


void CsjplabMFCObjectTrackingDlg::OnStnClickedPicPreview()
{
	// TODO: Add your control notification handler code here
}


//void CsjplabMFCObjectTrackingDlg::OnNcRButtonDblClk(UINT nHitTest, CPoint point)
//{
//	// TODO: Add your message handler code here and/or call default
//
//	CDialogEx::OnNcRButtonDblClk(nHitTest, point);
//}


void CsjplabMFCObjectTrackingDlg::OnNcPaint()
{
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnNcPaint() for painting messages

	//CDC* pDC = GetWindowDC();

	////work out the coordinates of the window rectangle,
	//CRect rect;
	//GetWindowRect(&rect);
	//rect.OffsetRect(-rect.left, -rect.top);

	////Draw a single line around the outside
	//CBrush brush(RGB(255, 0, 0));
	//pDC->FrameRect(&rect, &brush);
	//ReleaseDC(pDC);

	//CRect rcWindow;
	//GetWindowRect(&rcWindow);
	//rcWindow.OffsetRect(-rcWindow.left, -rcWindow.top);

	//int nX = 0;
	//int nY = 0;
	//LONG lStyle = ::GetWindowLong(this->GetSafeHwnd(), GWL_STYLE);
	//// WS_BORDER 속성이 적용되어 있느냐 없느냐에 따라 두께 계산
	//if (lStyle & WS_BORDER)
	//{
	//	nX = GetSystemMetrics(SM_CXSIZEFRAME);
	//	nY = GetSystemMetrics(SM_CYSIZEFRAME);
	//}
	//else
	//{
	//	nX = GetSystemMetrics(SM_CXSIZEFRAME) - GetSystemMetrics(SM_CXBORDER);
	//	nY = GetSystemMetrics(SM_CYSIZEFRAME) - GetSystemMetrics(SM_CYBORDER);
	//}

	//CDC* pDC = GetWindowDC();
	//// 테두리 영역만을 위해 가운데 영역 제외
	//pDC->ExcludeClipRect(nX, nY, rcWindow.right - nX, rcWindow.bottom - nY);
	//{
	//	// 테두리에 그릴 내용
	//	pDC->FillSolidRect(&rcWindow, RGB(255, 0, 0));
	//}
	//ReleaseDC(pDC);

	//CWindowDC dc(this);

	//CRect rc2, rc1;
	//GetWindowRect(&rc2);

	//int x, y;
	//// Compute the caption bar's origin. This window has a system box
	//// a minimize box, a maximize box, and has a resizeable frame
	//x = GetSystemMetrics(SM_CXSIZE) +
	//	GetSystemMetrics(SM_CXBORDER) +
	//	GetSystemMetrics(SM_CXFRAME);
	//y = GetSystemMetrics(SM_CYFRAME);

	//rc1.left = x;
	//rc1.top = y;

	//// 2*x gives twice the bitmap+border+frame size. Since there are
	//// only two bitmaps, two borders, and one frame at the end of the
	//// caption bar, subtract a frame to account for this.
	//rc1.right = rc2.right - rc2.left - 2 * x -
	//	GetSystemMetrics(SM_CXFRAME);
	//rc1.bottom = GetSystemMetrics(SM_CYSIZE);
	//// Render the caption. Use the active caption color as the text
	//// background.
	//dc.SetBkColor(GetSysColor(0x000000));
	//dc.SetTextColor(0xFF0000);
	////dc.SetBkMode(TRANSPARENT);
	//dc.FillSolidRect(&rc1, 0x000000);
	//dc.DrawText((LPCTSTR)(LPSTR)"Left Justified Caption", -1,
	//	(LPRECT)&rc1, DT_LEFT);

	// If you only change the menu bar, let the framework draw 
	// the window first
	Default();

	// To accesses the entire screen area of a CWnd 
	// (both client and nonclient areas).
	CWindowDC dc(this);

	CRect rc;
	GetWindowRect(rc);

	// Size of menu bar (non-client area) is smaller
	rc.bottom = GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYFRAME);

	// Compute color increment
	double decrement = (double)(LIGHT_COLOR - DARK_COLOR) / rc.Width();

	// Draw menu bar
	for (int i = 2; i < rc.Width() - 2; i++)
	{
		double color;
		CPen* oldPen;
		color = LIGHT_COLOR - decrement * (double)i;
		CPen pen(PS_SOLID, 1, RGB(0, 0, (int)color));
		dc.MoveTo(i, 1);
		oldPen = dc.SelectObject(&pen);
		dc.LineTo(i, rc.bottom - 1);
		dc.SelectObject(oldPen);
	}

	// Area for buttons
	CRect closeRect;
	closeRect.left = rc.right - rc.left - 20;
	closeRect.top = GetSystemMetrics(SM_CYFRAME);
	closeRect.right = rc.right - rc.left - 5;
	closeRect.bottom = GetSystemMetrics(SM_CYSIZE);

	// Put the close button on the caption
	dc.DrawFrameControl(closeRect,
		DFC_CAPTION,
		DFCS_CAPTIONCLOSE);

	// Save button position
	m_rcClose = closeRect;
	
}



BOOL CsjplabMFCObjectTrackingDlg::OnNcActivate(BOOL bActive)
{
	// TODO: Add your message handler code here and/or call default

	//if (!bActive)
	//{
	//	CBkDialogST::OnNcActivate(bActive);
	//	// Add code here to draw caption when window is inactive.
	//	return TRUE;

	//	// Fall through if wParam == TRUE, i.e., window is active.     
	//}

	OnNcPaint();
	return TRUE;

	//return CBkDialogST::OnNcActivate(bActive);
}

DWORD CsjplabMFCObjectTrackingDlg::HitTest(CPoint pt)
{
	// Check for buttons
	CRect rect = m_rcClose;
	if (rect.PtInRect(pt))
		return (DWORD)DHT_CLOSE;
	else
		return (DWORD)DHT_CAPTION;
}

LRESULT CsjplabMFCObjectTrackingDlg::OnNcHitTest(CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	//return CBkDialogST::OnNcHitTest(point);

	if (this != GetCapture())
		return CDialog::OnNcHitTest(point); // The default handler

											// Coords are relative to screen
	CPoint pt = point;
	// Convert for relative to client area
	ScreenToClient(&pt);
	// Adjust for client area
	pt.y += GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYFRAME);
	pt.x += 5;

	// Now test for button
	DWORD hitTest = HitTest(pt);

	if (hitTest == m_LastHit)
		return CDialog::OnNcHitTest(point);

	m_LastHit = hitTest;

	UINT pushed = 0;
	if (m_ButtonDown == hitTest)
		pushed = DFCS_PUSHED;

	CWindowDC dc(this);
	switch (hitTest)
	{
	case DHT_CLOSE:
	{
		DrawFrameControl(dc.m_hDC,
			m_rcClose,
			DFC_CAPTION,
			DFCS_CAPTIONCLOSE | pushed);
	}
	break;
	default:
		DrawFrameControl(dc.m_hDC,
			m_rcClose,
			DFC_CAPTION,
			DFCS_CAPTIONCLOSE);
		break;
	}
	// return value	
	return hitTest;
}


void CsjplabMFCObjectTrackingDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	//CBkDialogST::OnNcLButtonDown(nHitTest, point);

	// Coords are relative to screen
	CPoint pt = point;
	// Convert for relative to client area
	ScreenToClient(&pt);
	// Adjust for client area
	pt.y += GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYFRAME);
	pt.x += 5;

	// Now test for button
	DWORD hitTest = HitTest(pt);

	switch (hitTest)
	{
	case DHT_CLOSE:
	{
		CWindowDC dc(this);
		DrawFrameControl(dc.m_hDC,
			m_rcClose,
			DFC_CAPTION,
			DFCS_CAPTIONCLOSE | DFCS_PUSHED);
		m_LastHit = hitTest;
		m_ButtonDown = hitTest;
		// Set capture for mouse events
		SetCapture();
	}
	break;
	default:
		Default();
		break;
	}
}


void CsjplabMFCObjectTrackingDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	//CBkDialogST::OnLButtonUp(nFlags, point);

	if (this != GetCapture())
		return;

	// Coords are relative to window now
	CPoint pt = point;
	// Adjust for client area
	point.y += GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYFRAME);
	point.x += 5;

	// Now test for button
	DWORD hitTest = HitTest(point);

	switch (m_ButtonDown) // Release the pressed button
	{
	case DHT_CLOSE:
	{
		CWindowDC dc(this);

		DrawFrameControl(dc.m_hDC,
			m_rcClose,
			DFC_CAPTION,
			DFCS_CAPTIONCLOSE);
	}
	break;
	default:
		break;
	}

	switch (hitTest)		// Process command if released at on a button
	{
	case 1:
		SendMessage(WM_CLOSE, 0, 0);
		break;
	default:
		break;
	}
	m_ButtonDown = 0;
	// Release mouse capture
	ReleaseCapture();
}


void CsjplabMFCObjectTrackingDlg::OnClickedBtnCam1()
{
	// TODO: Add your control notification handler code here
	if (m_currentSource != VIDEO_SOURCE_CAM1) {
		m_currentSource = VIDEO_SOURCE_CAM1;

		m_btnCam1.SetBitmaps(IDB_BMP_CHECK_SELECTED, RGB(255, 0, 255));
		m_btnCam2.SetBitmaps(IDB_BMP_CHECK_NORMAL, RGB(255, 0, 255));
		m_btnStream.SetBitmaps(IDB_BMP_CHECK_NORMAL, RGB(255, 0, 255));

		mPreviewCtl.startMyTimer(0);
		mPreviewCtl.clearObjectTracking();
		
		if (!mPreviewCtl.isEnableVideo(m_currentSource)) {
			AfxMessageBox(_T("해당하는 캠 장치가 없습니다. "));
		}
		else {
			mPreviewCtl.initObjectTracking();
			mPreviewCtl.startMyTimer(1);
		}

	}
}


void CsjplabMFCObjectTrackingDlg::OnClickedBtnCam2()
{
	// TODO: Add your control notification handler code here
	if (m_currentSource != VIDEO_SOURCE_CAM2) {
		m_currentSource = VIDEO_SOURCE_CAM2;

		m_btnCam1.SetBitmaps(IDB_BMP_CHECK_NORMAL, RGB(255, 0, 255));
		m_btnCam2.SetBitmaps(IDB_BMP_CHECK_SELECTED, RGB(255, 0, 255));
		m_btnStream.SetBitmaps(IDB_BMP_CHECK_NORMAL, RGB(255, 0, 255));

		if (!mPreviewCtl.isEnableVideo(m_currentSource)) {
			AfxMessageBox(_T("해당하는 캠 장치가 없습니다. "));
		}
		else {
			mPreviewCtl.initObjectTracking();
			mPreviewCtl.startMyTimer(1);
		}
	}

}

void CsjplabMFCObjectTrackingDlg::OnClickedBtnStream()
{
	// TODO: Add your control notification handler code here
	if (m_currentSource != VIDEO_SOURCE_STREAM) {
		m_currentSource = VIDEO_SOURCE_STREAM;

		m_btnCam1.SetBitmaps(IDB_BMP_CHECK_NORMAL, RGB(255, 0, 255));
		m_btnCam2.SetBitmaps(IDB_BMP_CHECK_NORMAL, RGB(255, 0, 255));
		m_btnStream.SetBitmaps(IDB_BMP_CHECK_SELECTED, RGB(255, 0, 255));

		if (!mPreviewCtl.isEnableVideo(m_currentSource)) {
			AfxMessageBox(_T("해당하는 캠 장치가 없습니다. "));
		}
		else {
			mPreviewCtl.initObjectTracking();
			mPreviewCtl.startMyTimer(1);
		}
	}
}

void CsjplabMFCObjectTrackingDlg::OnClickedBtnCmt()
{
	// TODO: Add your control notification handler code here
	mPreviewCtl.m_currentMethod = m_currentMethod = METHOD_CMT;

	m_btnCmt.SetBitmaps(IDB_BMP_CHECK_SELECTED, RGB(255, 0, 255));
	m_btnTld.SetBitmaps(IDB_BMP_CHECK_NORMAL, RGB(255, 0, 255));

	mPreviewCtl.tracking = FALSE;

	mPreviewCtl.roiStartPoint.x = 0; mPreviewCtl.roiStartPoint.y = 0;
	mPreviewCtl.roiEndPoint.x = 0; mPreviewCtl.roiEndPoint.y = 0;
	mPreviewCtl.clearSelectObject();

	htbnmp = NULL;
	m_CImage.Detach();

	if (m_CImage.Load(IDB_PNG_TRACKING_NORMAL)) {
		htbnmp = m_CImage;

		//mobjecttracking.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
		//mobjecttracking.m_bTransparent = TRUE;
		//mobjecttracking.m_bDrawFocus = FALSE;
		mobjecttracking.SetImage(htbnmp, TRUE, htbnmp);
		mobjecttracking.Invalidate();
		//mobjecttracking.SetMouseCursorHand();
	}
}

void CsjplabMFCObjectTrackingDlg::OnClickedBtnTld()
{
	// TODO: Add your control notification handler code here
	mPreviewCtl.m_currentMethod = m_currentMethod = METHOD_TLD;

	m_btnCmt.SetBitmaps(IDB_BMP_CHECK_NORMAL, RGB(255, 0, 255));
	m_btnTld.SetBitmaps(IDB_BMP_CHECK_SELECTED, RGB(255, 0, 255));

	mPreviewCtl.tracking = FALSE;

	mPreviewCtl.roiStartPoint.x = 0; mPreviewCtl.roiStartPoint.y = 0;
	mPreviewCtl.roiEndPoint.x = 0; mPreviewCtl.roiEndPoint.y = 0;
	mPreviewCtl.clearSelectObject();

	htbnmp = NULL;
	m_CImage.Detach();

	if (m_CImage.Load(IDB_PNG_TRACKING_NORMAL)) {
		htbnmp = m_CImage;

		//mobjecttracking.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
		//mobjecttracking.m_bTransparent = TRUE;
		//mobjecttracking.m_bDrawFocus = FALSE;
		mobjecttracking.SetImage(htbnmp, TRUE, htbnmp);
		mobjecttracking.Invalidate();
		//mobjecttracking.SetMouseCursorHand();
	}

}

void CsjplabMFCObjectTrackingDlg::OnClickedBtnDown()
{
	// TODO: Add your control notification handler code here
}

void CsjplabMFCObjectTrackingDlg::OnClickedBtnLeft()
{
	// TODO: Add your control notification handler code here
}

void CsjplabMFCObjectTrackingDlg::OnClickedBtnRight()
{
	// TODO: Add your control notification handler code here
}

void CsjplabMFCObjectTrackingDlg::OnClickedBtnUp()
{
	// TODO: Add your control notification handler code here
}
