
// PicturePreview.cpp : implementation file
//

#include "stdafx.h"
#include "sjplabMFCObjectTracking.h"
#include "PicturePreview.h"
#include "sjplabMFCObjectTrackingDlg.h"


// CPicturePreview

IMPLEMENT_DYNAMIC(CPicturePreview, CStatic)

CPicturePreview::CPicturePreview()
{
	EnableAutomation();
}

CPicturePreview::~CPicturePreview()
{
}

void CPicturePreview::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CStatic::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CPicturePreview, CStatic)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(CPicturePreview, CStatic)
END_DISPATCH_MAP()

// Note: we add support for IID_IPicturePreview to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .IDL file.

// {7785C290-0675-41EF-88DC-27BF42CA9A97}
static const IID IID_IPicturePreview =
{ 0x7785C290, 0x675, 0x41EF, { 0x88, 0xDC, 0x27, 0xBF, 0x42, 0xCA, 0x9A, 0x97 } };

BEGIN_INTERFACE_MAP(CPicturePreview, CStatic)
	INTERFACE_PART(CPicturePreview, IID_IPicturePreview, Dispatch)
END_INTERFACE_MAP()

// CPicturePreview message handlers

void CPicturePreview::AdjustAspectImageSize(const Size& imageSize, const Size& destSize, Size& newSize)
{
	double destAspectRatio = float(destSize.width) / float(destSize.height);
	double imageAspectRatio = float(imageSize.width) / float(imageSize.height);

	if (imageAspectRatio > destAspectRatio)
	{
		// Margins on top/bottom
		newSize.width = destSize.width;
		newSize.height = int(imageSize.height  * (double(destSize.width) / double(imageSize.width)));
	}
	else
	{
		// Margins on left/right
		newSize.height = destSize.height;
		newSize.width = int(imageSize.width  * (double(destSize.height) / double(imageSize.height)));
	}
}

void CPicturePreview::DrawPicToHDC(Mat  cvImg, UINT nDlgID, bool bMaintainAspectRatio /* =true*/)
{
	// Get the HDC handle information from the ID passed
	//CDC* pDC = GetDlgItem(nDlgID)->GetDC();
	CDC* pDC = GetWindowDC();
	HDC  hDC = pDC->GetSafeHdc();

	CRect rect;
	GetWindowRect(&rect);
	GetParent()->ScreenToClient(&rect);
	Size winSize(rect.right-rect.left, rect.bottom-rect.top);

	// Calculate the size of the image that
	// will fit in the control rectangle.
	Size origImageSize(cvImg.cols, cvImg.rows);
	Size imageSize;
	int  offsetX;
	int  offsetY;

	if (!bMaintainAspectRatio)
	{
		// Image should be the same size as the control's rectangle
		lastImageSize = previewSize = imageSize = winSize;
	}
	else
	{
		Size newSize;
		AdjustAspectImageSize(origImageSize, winSize, imageSize);
		previewSize = winSize;
		lastImageSize = imageSize;
	}

	/*offsetX = (winSize.width - imageSize.width) / 2;
	offsetY = (winSize.height - imageSize.height) / 2;*/
	offsetX = 0;
	offsetY = 0;

	// change preview window size & location
	if (!previewResized) {
		//GetParent()
		//SetWindowPos(&CWnd::wndTopMost, rect.left+offsetX, rect.top+offsetY, imageSize.width, imageSize.height, NULL); //SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER
		SetWindowPos(NULL, rect.left + offsetX, rect.top + offsetY, imageSize.width, imageSize.height, NULL); //SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER
		previewResized = 1;
	}	

	// Resize the source to the size of the destination image if necessary
	Mat cvImgTmp;
	resize(cvImg, cvImgTmp, imageSize, 0, 0, INTER_AREA);

	// To handle our Mat object of this width, the source rows must
	// be even multiples of a DWORD in length to be compatible with 
	// SetDIBits().  Calculate what the correct byte width of the 
	// row should be to be compatible with SetDIBits() below.
	int stride = ((((imageSize.width * 24) + 31)  &  ~31) >> 3);

	// Allocate a buffer for our DIB bits
	uchar* pcDibBits = (uchar*)malloc(imageSize.height * stride);

	if (pcDibBits != NULL)
	{
		// Copy the raw pixel data over to our dibBits buffer.
		// NOTE: Can setup cvImgTmp to add the padding to skip this.
		for (int row = 0; row < cvImgTmp.rows; ++row)
		{
			// Get pointers to the beginning of the row on both buffers
			uchar* pcSrcPixel = cvImgTmp.ptr<uchar>(row);
			uchar* pcDstPixel = pcDibBits + (row * stride);

			// We can just use memcpy
			memcpy(pcDstPixel,
				pcSrcPixel,
				stride);
		}

		// Initialize the BITMAPINFO structure
		BITMAPINFO bitInfo;

		bitInfo.bmiHeader.biBitCount = 24;
		bitInfo.bmiHeader.biWidth = cvImgTmp.cols;
		bitInfo.bmiHeader.biHeight = -cvImgTmp.rows;
		bitInfo.bmiHeader.biPlanes = 1;
		bitInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bitInfo.bmiHeader.biCompression = BI_RGB;
		bitInfo.bmiHeader.biClrImportant = 0;
		bitInfo.bmiHeader.biClrUsed = 0;
		bitInfo.bmiHeader.biSizeImage = 0;      //winSize.height * winSize.width * * 3;
		bitInfo.bmiHeader.biXPelsPerMeter = 0;
		bitInfo.bmiHeader.biYPelsPerMeter = 0;

		// Add header and OPENCV image's data to the HDC
		StretchDIBits(hDC,
			offsetX,
			offsetY,
			cvImgTmp.cols,
			cvImgTmp.rows,
			0,
			0,
			cvImgTmp.cols,
			cvImgTmp.rows,
			pcDibBits,
			&bitInfo,
			DIB_RGB_COLORS,
			SRCCOPY);

		free(pcDibBits);
	}

	ReleaseDC(pDC);
}

void CPicturePreview::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	tic = cvGetTickCount();

	if (!reuseFrameOnce)
	{
		*mVideoCapture >> frame;
	}

	if (frame.empty()) {
		CStatic::OnTimer(nIDEvent);
		KillTimer(MY_TIMER);
		return;
	}

	resize(frame, frameProcessing, Size(640, 480));

	if (!skipProcessingOnce && tracking)
	{
		if (m_currentMethod != METHOD_CMT) {
			main->tld->processImage(frameProcessing);
		}
		else {
			if (cmt_tracking) {
				cv::Mat im_gray;
				cvtColor(frameProcessing, im_gray, CV_BGR2GRAY);
				cmt.processFrame(im_gray);
			}
		}
	}
	else
	{
		skipProcessingOnce = false;
	}

	double toc = (cvGetTickCount() - tic) / cvGetTickFrequency();
	toc = toc / 1000000;
	float fps = 1 / toc;
	int confident = (main->tld->currConf >= main->threshold) ? 1 : 0;

	if (main->showOutput || main->saveDir != NULL)
	{
		char string[128];
		char learningString[10] = "";

		if (main->tld->learning)
		{
			strcpy(learningString, "Learning");
		}

		sprintf(string, "fps: %.2f, %s, width:%d, height:%d", fps, learningString, frame.cols, frame.rows);
		CvScalar yellow = CV_RGB(255, 255, 0);
		CvScalar blue = CV_RGB(0, 0, 255);
		CvScalar black = CV_RGB(0, 0, 0);
		CvScalar white = CV_RGB(255, 255, 255);

		// set ratio
		double px = frame.cols / (double)frameProcessing.cols;
		double py = frame.rows / (double)frameProcessing.rows;

		if (m_currentMethod != METHOD_CMT) {
			if (main->tld->currBB != NULL)
			{
				CvScalar rectangleColor = (confident) ? blue : yellow;
				CvPoint topleft = cvPoint(main->tld->currBB->x, main->tld->currBB->y);
				CvPoint bottomRight = cvPoint(main->tld->currBB->x + main->tld->currBB->width, main->tld->currBB->y + main->tld->currBB->height);
				topleft.x = topleft.x * px; topleft.y = topleft.y * py;
				bottomRight.x = bottomRight.x * px; bottomRight.y = bottomRight.y * py;

				cv::Rect r = cv::Rect(topleft.x, topleft.y, bottomRight.x - topleft.x, bottomRight.y - topleft.y);
				cv::rectangle(frame, r, rectangleColor, 2);
				CvPoint center = cvPoint(r.x + r.width / 2, r.y + r.height / 2);
				cv::line(frame, cvPoint(center.x - 2, center.y - 2), cvPoint(center.x + 2, center.y + 2), rectangleColor, 2);
				cv::line(frame, cvPoint(center.x - 2, center.y + 2), cvPoint(center.x + 2, center.y - 2), rectangleColor, 2);
			}
		}
		else {
			if (cmt.hasResult && tracking) {
				for (int i = 0; i < cmt.trackedKeypoints.size(); i++) {
					//cvCircle(img, cmt.trackedKeypoints[i].first.pt, 3, cv::Scalar(255, 255, 255));
					CvPoint nPoint = cmt.trackedKeypoints[i].first.pt;
					nPoint.x = nPoint.x * px; nPoint.y = nPoint.y * py;
					cv::circle(frame, nPoint, 3, cv::Scalar(255, 255, 255));
				}
				//cvRectangle(img, cmt.boundingbox.tl(), cmt.boundingbox.br(), Scalar(0,0,255), 1, 4);
				CvPoint topleft = cvPoint(cmt.boundingbox.x, cmt.boundingbox.y);
				CvPoint bottomRight = cvPoint(cmt.boundingbox.x + cmt.boundingbox.width, cmt.boundingbox.y + cmt.boundingbox.height);
				topleft.x = topleft.x * px; topleft.y = topleft.y * py;
				bottomRight.x = bottomRight.x * px; bottomRight.y = bottomRight.y * py;
				cv::rectangle(frame, topleft, bottomRight, Scalar(0, 0, 255), 1, 4);

				//draw some crosshairs around the object
				int x, y = 0;
				x = topleft.x + (bottomRight.x - topleft.x) / 2;
				y = topleft.y + (bottomRight.y - topleft.y) / 2;

				cv::circle(frame, cv::Point(x, y), 10, Scalar(0, 255, 0), 1);
				cv::line(frame, cv::Point(x, y), cv::Point(x, y - 15), Scalar(0, 255, 0), 1);
				cv::line(frame, cv::Point(x, y), cv::Point(x, y + 15), Scalar(0, 255, 0), 1);
				cv::line(frame, cv::Point(x, y), cv::Point(x - 15, y), Scalar(0, 255, 0), 1);
				cv::line(frame, cv::Point(x, y), cv::Point(x + 15, y), Scalar(0, 255, 0), 1);
			}
		}
		
		cv::putText(frame, string, cvPoint(25, 25), 1, 1, white);
	}

	if (reuseFrameOnce)
	{
		reuseFrameOnce = false;
	}
	
	//draw ROI
	if (drag || !tracking) {
		
		cv::rectangle(frame, roiStartPoint, roiEndPoint, Scalar(255, 0, 0), 1, 4);
	}

	//IDD_SJPLABMFCOBJECTTRACKING_DIALOG
	//IDC_PIC_PREVIEW
	DrawPicToHDC(frame, IDD_SJPLABMFCOBJECTTRACKING_DIALOG, true);

	CStatic::OnTimer(nIDEvent);
}

void CPicturePreview::resetPosition(int& px, int& py)
{
	//px = px + (previewSize.width - lastImageSize.width) / 2;

	TRACE(_T("x:%d, y:%d, preview:width:%d, preview:height:%d, lastImage:width:%d, lastImage:height:%d \n"), px, py, previewSize.width, previewSize.height, lastImageSize.width, lastImageSize.height);

	px = px * frame.cols / previewSize.width;
	
	py = py * frame.rows / previewSize.height;
}

void CPicturePreview::resetSize(int type, int& value)
{
	if (type) //width 
	{
		value = value * (frame.cols / previewSize.width);
	}
	else      //height
	{
		value = value * (frame.rows / previewSize.height);
	}
}

int CPicturePreview::startMyTimer(int pCmdType)
{
	if (pCmdType) {

		SetTimer(MY_TIMER, 30, NULL);
	}
	else {
		KillTimer(MY_TIMER);
	}

	return 0;
}

int CPicturePreview::initObjectTracking()
{
	main = new MainClass();
	Config config;

	//ImAcq *imAcq = imAcqAlloc();
	//Gui *gui = new Gui();
	//main->gui = gui;
	//main->imAcq = imAcq;
	
	config.configure(main);
	srand(main->seed);

	*mVideoCapture >> frame;

	resize(frame, frameProcessing, Size(640, 480));

	cvtColor(frameProcessing, grey, CV_BGR2GRAY);
	
	main->tld->detectorCascade->imgWidth = grey.cols;
	main->tld->detectorCascade->imgHeight = grey.rows;
	main->tld->detectorCascade->imgWidthStep = grey.step;

	return TRUE;
}

int CPicturePreview::selectObject()
{
	cvtColor(frameProcessing, grey, CV_BGR2GRAY);

	if (roiRect.width < 1 || roiRect.height < 1)
		return FALSE;

	// set ratio
	double px =frameProcessing.cols / (double)frame.cols;
	double py = frameProcessing.rows / (double)frame.rows;

	roiRect.x = roiRect.x * px;
	roiRect.y = roiRect.y * py;
	roiRect.width = roiRect.width * px;
	roiRect.height = roiRect.height * py;

	if (m_currentMethod != METHOD_CMT) {
		main->tld->selectObject(grey, &roiRect);
	}
	else {
		//cmt tracket init
		cv::Point2f initTopLeft(roiRect.x, roiRect.y);
		cv::Point2f initBottomDown(roiRect.x + roiRect.width, roiRect.y + roiRect.height);
		cmt_tracking = cmt.initialise(grey, initTopLeft, initBottomDown);
	}

	return TRUE;
}

int CPicturePreview::isEnableVideo(int currentSource)
{
	//String url = "https://devimages.apple.com.edgekey.net/samplecode/avfoundationMedia/AVFoundationQueuePlayer_HLS2/master.m3u8";
	//mVideoCapture.open(0);
	//mVideoCapture.open("https://devimages.apple.com.edgekey.net/samplecode/avfoundationMedia/AVFoundationQueuePlayer_HLS2/master.m3u8");
	//mVideoCapture.open("151127.mp4");
	//mVideoCapture = new VideoCapture("https://devimages.apple.com.edgekey.net/samplecode/avfoundationMedia/AVFoundationQueuePlayer_HLS2/master.m3u8");
	//mVideoCapture = new VideoCapture("151127.mp4");
	//mVideoCapture = new VideoCapture(0);
	/*char* video_name;
	video_name = "768x576.avi";
	mVideoCapture.open(video_name);*/

	switch (currentSource)
	{
	case VIDEO_SOURCE_CAM1:
		mVideoCapture = new VideoCapture(0);
		break;
	case VIDEO_SOURCE_CAM2:
		mVideoCapture = new VideoCapture(1);
		break;
	case VIDEO_SOURCE_STREAM:
		mVideoCapture = new VideoCapture("https://devimages.apple.com.edgekey.net/samplecode/avfoundationMedia/AVFoundationQueuePlayer_HLS2/master.m3u8");
		break;
	
	default:
		mVideoCapture = new VideoCapture("https://devimages.apple.com.edgekey.net/samplecode/avfoundationMedia/AVFoundationQueuePlayer_HLS2/master.m3u8");
	}
	
	if (!mVideoCapture->isOpened())
		return false;
	
	mVideoCapture->set(CV_CAP_PROP_FRAME_WIDTH, 1280); //640 (1280) 1920
	mVideoCapture->set(CV_CAP_PROP_FRAME_HEIGHT, 720); //480 -> 340 (720) 1080

	return TRUE;

}

int CPicturePreview::clearObjectTracking()
{
	delete main;
	main = NULL;
	mVideoCapture->release();
	mVideoCapture = NULL;
	return TRUE;
}

int CPicturePreview::clearSelectObject()
{
	main->tld->release();
	cmt_tracking = false;

	return TRUE;
}


void CPicturePreview::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	//clear everything
	main->tld->release();
	tracking = false;
	cmt_tracking = false;
	
	roiStartPoint = cvPoint(point.x, point.y);
	resetPosition(roiStartPoint.x, roiStartPoint.y);
	
	drag = 1;

	CsjplabMFCObjectTrackingDlg* pParent = (CsjplabMFCObjectTrackingDlg*)GetParent();
	pParent->changeTrackingButton();
	//CsjplabMFCObjectTrackingDlg* pParent = static_cast<CsjplabMFCObjectTrackingDlg*>(GetParent());

	CStatic::OnLButtonDown(nFlags, point);
}


void CPicturePreview::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CvPoint tPoint;
	tPoint = cvPoint(point.x, point.y);
	resetPosition(tPoint.x, tPoint.y);
	roiRect = cvRect(roiStartPoint.x, roiStartPoint.y, tPoint.x - roiStartPoint.x, tPoint.y - roiStartPoint.y);
	drag = 0;

	CStatic::OnLButtonUp(nFlags, point);
}


void CPicturePreview::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (drag) {
		roiEndPoint = cvPoint(point.x, point.y);
		resetPosition(roiEndPoint.x, roiEndPoint.y);
	}	

	CStatic::OnMouseMove(nFlags, point);
}


int CPicturePreview::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}
