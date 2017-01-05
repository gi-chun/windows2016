#pragma once
#include "MainClass.h"
#include "Config.h"
#include "ImAcq.h"
#include "Gui.h"
#include "TLDUtil.h"
#include "Trajectory.h"
#include "CMT.h"

using namespace tld;
using namespace cv;

#define MY_TIMER 100
//static char* video_name = "PETS2000.avi";

// CPicturePreview

class CPicturePreview : public CStatic
{
	DECLARE_DYNAMIC(CPicturePreview)

public:
	CPicturePreview();
	virtual ~CPicturePreview();

	virtual void OnFinalRelease();

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:

	MainClass *main;
	VideoCapture *mVideoCapture;
	CMT cmt;
	Mat frame;
	Mat grey;
	Mat frameProcessing;
	bool reuseFrameOnce = false;
	bool skipProcessingOnce = false;
	double tic;
	CvPoint roiStartPoint;
	CvPoint roiEndPoint;
	Rect roiRect;
	int drag = 0;
	Size previewSize;
	Size lastImageSize;
	int tracking = 0;

	bool cmt_tracking;

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void AdjustAspectImageSize(const Size& imageSize, const Size& destSize, Size& newSize);
	void DrawPicToHDC(Mat  cvImg, UINT nDlgID, bool bMaintainAspectRatio /* =true*/);
	int startMyTimer(int pCmdType);
	int isEnableVideo();
	int initObjectTracking();
	int selectObject();
	int clearObjectTracking();
	int clearSelectObject();
	void resetPosition(int& px, int& py);
	void resetSize(int type, int& value);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


