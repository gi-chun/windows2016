
// sjplabMFCObjectTracking.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CsjplabMFCObjectTrackingApp:
// �� Ŭ������ ������ ���ؼ��� sjplabMFCObjectTracking.cpp�� �����Ͻʽÿ�.
//

class CsjplabMFCObjectTrackingApp : public CWinApp
{
public:
	CsjplabMFCObjectTrackingApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CsjplabMFCObjectTrackingApp theApp;