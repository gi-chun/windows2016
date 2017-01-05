
// sjplabMFCObjectTrackingDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "afxext.h"
#include "BtnST.h"
#include "PicturePreview.h"

// CsjplabMFCObjectTrackingDlg ��ȭ ����
class CsjplabMFCObjectTrackingDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CsjplabMFCObjectTrackingDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SJPLABMFCOBJECTTRACKING_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CButtonST mbtnclose;
	CButtonST mobjecttracking;
	CButtonST mbtnconfig;
	CPicturePreview mPreviewCtl;
	
	CPngImage m_CImage;
	HBITMAP htbnmp;
	void changeTrackingButton();

//	afx_msg void OnIdok();
	afx_msg void OnClickedOk();
	afx_msg void OnClickedConfig();
	afx_msg void OnClickedObjtracking();
	afx_msg void OnDestroy();
	CStatic stSource;
	CStatic stMethod;
	CComboBox cbMethod;
	CComboBox cbSource;
	afx_msg void OnSelchangeComboMethod();
	afx_msg void OnSelchangeComboSource();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
