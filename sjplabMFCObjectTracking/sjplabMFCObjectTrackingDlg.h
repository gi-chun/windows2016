
// sjplabMFCObjectTrackingDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "afxext.h"
#include "ColorStaticST.h"
#include "BkDialogST.h"
#include "BtnST.h"
#include "PicturePreview.h"

// HitTest Constants
#define DHT_CLOSE		0x01
#define DHT_CAPTION		0x02

#define LIGHT_COLOR		250
#define DARK_COLOR		100

typedef enum { VIDEO_SOURCE_CAM1, VIDEO_SOURCE_CAM2, VIDEO_SOURCE_STREAM } Video_SOURCETYPE;
typedef enum { METHOD_CMT, METHOD_TLD } Video_METHODTYPE;

// CsjplabMFCObjectTrackingDlg 대화 상자
class CsjplabMFCObjectTrackingDlg : public CBkDialogST //CDialogEx
{
// 생성입니다.
public:
	CsjplabMFCObjectTrackingDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SJPLABMFCOBJECTTRACKING_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	
	CWnd* LastCapture;
	CRect m_rcIcon;
	CRect m_rcClose;
	DWORD m_LastHit;
	DWORD m_ButtonDown;

	DWORD HitTest(CPoint pt);

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	int m_currentSource = 0;
	int m_currentMethod = 0;

	CMFCButton mbtnclose; //CButtonST CMFCButton
	CMFCButton mobjecttracking;
	CMFCButton mbtnconfig;
	CPicturePreview mPreviewCtl;
	CColorStaticST m_rightBack;
	CColorStaticST m_camera_back;
	CColorStaticST m_method_back;
	CColorStaticST m_source_back;

	CButtonST m_btnCmt;
	CButtonST m_btnCam1;
	CButtonST m_btnCam2;
	CButtonST m_btnStream;
	CButtonST m_btnTld;

	CButtonST m_btnLeft;
	CButtonST m_btnRight;
	CButtonST m_btnUp;
	CButtonST m_btnDown;

	CPngImage m_CImage; //CPngImage
	HBITMAP htbnmp;
	void changeTrackingButton();

//	afx_msg void OnIdok();
	afx_msg void OnClickedOk();
	afx_msg void OnClickedConfig();
	afx_msg void OnClickedObjtracking();
	afx_msg void OnDestroy();
//	CStatic stSource;
//	CStatic stMethod;
//	CComboBox cbMethod;
//	CComboBox cbSource;
//	afx_msg void OnSelchangeComboMethod();
//	afx_msg void OnSelchangeComboSource();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnStnClickedPicPreview();
//	afx_msg void OnNcRButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnNcPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClickedBtnCam1();
	afx_msg void OnClickedBtnCam2();
	afx_msg void OnClickedBtnCmt();
	afx_msg void OnClickedBtnDown();
	afx_msg void OnClickedBtnLeft();
	afx_msg void OnClickedBtnRight();
	afx_msg void OnClickedBtnStream();
	afx_msg void OnClickedBtnTld();
	afx_msg void OnClickedBtnUp();
};
