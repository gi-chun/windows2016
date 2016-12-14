
#include <jni.h>
#include <string>
#include <opencv2/opencv.hpp>
#include "libopentld/tld/tld.h"
#include "cmt.h"

using namespace cv;
using namespace std;
using namespace tld;

#ifdef __cplusplus
extern "C" {
#endif

bool CMTinitiated=false;
TLD * etld=NULL ;
CMT * cmt=new CMT();

long rect[4];

jstring
Java_com_sjp_sjplab_sjplabandroidot_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

CascadeClassifier cascade;

void
Java_com_sjp_sjplab_sjplabandroidot_MainActivity_nativeDetectAndDisplay(
        JNIEnv *env,
        jobject,
        jlong addrMat) {
    if (cascade.empty()) {
        cascade.load("/sdcard/lbpcascade_frontalface.xml");
    }

    /*
    if (cascade.empty()) {
        return;
    }
     */

    /*
    Mat &src = *(Mat *) addrMat;
    Mat gray, gray2;
    cvtColor(src, gray, COLOR_BGRA2GRAY);
    resize(gray, gray2, Size(640, 480));
    */

    /*
    vector<Rect> faces;
    cascade.detectMultiScale(gray2, faces, 1.2, 3, 0, Size(40, 40));
    for (size_t i = 0; i < faces.size(); i++) {
        Rect rc = faces[i];
        rc.x *= 2;
        rc.y *= 2;
        rc.width *= 2;
        rc.height *= 2;
        rectangle(src, rc, Scalar(255, 0, 255), 2);
    }
    */
}

void
Java_com_sjp_sjplab_sjplabandroidot_MainActivity_OpenTLD(JNIEnv*, jobject, jlong addrGray, jlong addrRgba,
                                                  jlong x, jlong y, jlong width, jlong height)
{

    if (etld!=NULL)
    {
        etld->release();
        delete etld;
    }
    etld = new TLD();
    Mat& mGr  = *(Mat*)addrGray;
    Mat& mRgb = *(Mat*)addrRgba;

    int t=  mRgb.cols;
    etld->detectorCascade->imgWidth =mGr.cols;
    etld->detectorCascade->imgHeight = mGr.rows;
    etld->detectorCascade->imgWidthStep = mGr.step;

    Rect r;
    r.x= x;//mGr.size().width/2-mGr.size().width/4;
    r.y= y;// mGr.size().height/2-mGr.size().height/4;
    r.width= width;//mGr.size().width/2;
    r.height= height;//mGr.size().height/2;
    etld->selectObject(mGr,& r );

}


jintArray Java_com_sjp_sjplab_sjplabandroidot_MainActivity_getRect(JNIEnv *env, jobject)
{

    jintArray result;
    result = env->NewIntArray(4);

    if (etld->currBB == NULL) {
        return NULL;
    }

    jint fill[4];
    if (etld->currBB!=NULL)
    {
        fill[0]=etld->currBB->x;
        fill[1]=etld->currBB->y;
        fill[2]=etld->currBB->width;
        fill[3]=etld->currBB->height;
        env->SetIntArrayRegion(result, 0, 4, fill);
        return result;
    }

    return NULL;

}


void
Java_com_sjp_sjplab_sjplabandroidot_MainActivity_ProcessTLD(JNIEnv*, jobject, jlong addrGray, jlong addrRgba)
{
    Mat& mRgb = *(Mat*)addrRgba;

    etld->processImage(mRgb);

    if (etld->currBB!=NULL)
    {
        Rect r;
        r.x=etld->currBB->x;
        r.y=etld->currBB->y;
        r.width= etld->currBB->width;
        r.height= etld->currBB->height;

        rectangle(mRgb ,r,Scalar(0,0,255,0),5);
        /*   for(size_t i = 0; i < etld->detectorCascade->detectionResult->fgList->size(); i++)
                        {
                            Rect r = etld->detectorCascade->detectionResult->fgList->at(i);
                            rectangle(mRgb, r, Scalar(255,0,0,0), 1);
                        }
                        */
    }
    else
    {
        Rect r;
        r.x=mRgb.size().width/2;
        r.y=mRgb.size().height/2;;
        r.width= 100;
        r.height= 100;
        rectangle(mRgb ,r,Scalar(0,0,0,255),5);
    }

}

void
Java_com_sjp_sjplab_sjplabandroidot_MainActivity_OpenCMT(JNIEnv*, jobject, jlong addrGray, jlong addrRgba, jlong x, jlong y, jlong width, jlong height)
{

//	 if (cmt!=NULL)
//	 {
//		 delete cmt;
//	 }
//	 cmt = new CMT();
    cv::Mat& im_gray  = *(cv::Mat*)addrGray;
    //gclee
    cv::UMat temp;
    im_gray.copyTo(temp);

//    //find largest_countour
//    cv::Rect roi = cv::Rect(x, y, x+width, y+height);
//    cv::UMat roiMat = temp(roi);
//    cv::UMat src_bin;
//    cv::threshold(roiMat, src_bin, 0, 255, THRESH_BINARY | THRESH_OTSU);
//    vector<vector<Point> > contours;
//    cv::findContours(src_bin, contours, RETR_LIST, CHAIN_APPROX_NONE);
//    double a, largest_area = 0.0;
//    unsigned largest_contour_index = 0;
//    for (unsigned i = 0; i < contours.size(); i++) {
//        double a = contourArea(contours[i], false);  //Find the largest area of contour
//        if (a>largest_area)
//        {
//            largest_area = a;
//            largest_contour_index = i;
//        }
//    }
//    vector<cv::Point> contours_poly;
//    Rect boundRect;
//    cv::approxPolyDP(cv::Mat(contours[largest_contour_index]), contours_poly, 3, true);
//    boundRect = cv::boundingRect(cv::Mat(contours_poly));
//
////    double px = (im_gray.cols) / (double) (width);
////    double py = (im_gray.rows) / (double) (height);
////    double px = (width) / (double) (im_gray.cols);
////    double py = (height) / (double) (im_gray.rows);
////
//    boundRect.x = boundRect.x + x;
//    boundRect.y = boundRect.y + y;
////    boundRect.width = boundRect.width * px;
////    boundRect.height = boundRect.height * py;
//    //

    Point p1(x, y);
    Point p2(x+width, y+height);

    CMTinitiated=false;
    if (cmt->initialise(temp, p1, p2))
        CMTinitiated=true;

}

void
Java_com_sjp_sjplab_sjplabandroidot_MainActivity_ProcessCMT(JNIEnv*, jobject, jlong addrGray, jlong addrRgba)
{
    if (!CMTinitiated)
        return;
    Mat& img  = *(Mat*)addrRgba;
    Mat& im_gray  = *(Mat*)addrGray;
//    Mat& im_roi = *(Mat*)addrRoiRgba;
    //gclee
    UMat temp;
    im_gray.copyTo(temp);

    cmt->processFrame(temp);

//    if(cmt->hasResult) {
//
//        double px = (double) img.cols / (double) im_gray.cols;
//        double py = (double) img.rows / (double) im_gray.rows;
//
//        int roix, roiy, roiwidth, roiheight = 0;
//        roix = cmt->topLeft.x * px;
//        roiy = cmt->topLeft.y * py;
//        roiwidth = cmt->bottomRight.x * px - cmt->topLeft.x * px;
//        roiheight = cmt->bottomRight.y * py - cmt->topLeft.y * py;
//
//        if(roix >= 0 && roiwidth >= 0 && roix+roiwidth <= img.cols && roiy >=0 && roiheight >=0 && roiy+roiheight <= img.rows){
//
////            resize(im_roi, im_roi, cvSize(roiwidth, roiheight));
////            //double alpha = 0.0;
//            cv::Rect roi = cv::Rect(roix, roiy, roiwidth, roiheight);
////            cv::addWeighted(img(roi), 1, im_roi, 1, 0.0, img(roi));
//
//            int lineLength = 30;
//            /* corners:
//    * p1 - p2
//    * |     |
//    * p4 - p3
//    */
//            int cornerRadius = 10;
//            Scalar lineColor = Scalar(0, 255, 0);
//            int thickness = 2;
//            int lineType = 8;
//            Point p1 = Point(roi.x, roi.y);
//            Point p2 = Point (roi.x+roi.width, roi.y);
//            Point p3 = Point(roi.x+roi.width, roi.y+roi.height);
//            Point p4 = Point (roi.x, roi.y+roi.height);
//
//            // draw straight lines
//            line(img, Point (p1.x+cornerRadius,p1.y), Point (p1.x+cornerRadius+lineLength,p1.y), lineColor, thickness, lineType);
//            line(img, Point (p2.x-cornerRadius-lineLength,p2.y), Point (p2.x-cornerRadius,p2.y), lineColor, thickness, lineType);
//
//            line(img, Point (p2.x,p2.y+cornerRadius), Point (p2.x,p2.y+cornerRadius+lineLength), lineColor, thickness, lineType);
//            line(img, Point (p3.x,p3.y-cornerRadius-lineLength), Point (p3.x,p3.y-cornerRadius), lineColor, thickness, lineType);
//
//            line(img, Point (p4.x+cornerRadius,p4.y), Point (p4.x+cornerRadius+lineLength,p4.y), lineColor, thickness, lineType);
//            line(img, Point (p3.x-cornerRadius-lineLength,p3.y), Point (p3.x-cornerRadius,p3.y), lineColor, thickness, lineType);
//
//            line(img, Point (p1.x,p1.y+cornerRadius), Point (p1.x,p1.y+cornerRadius+lineLength), lineColor, thickness, lineType);
//            line(img, Point (p4.x,p4.y-cornerRadius-lineLength), Point (p4.x,p4.y-cornerRadius), lineColor, thickness, lineType);
//
//            // draw arcs
//            ellipse( img, p1+Point(cornerRadius, cornerRadius), Size( cornerRadius, cornerRadius ), 180.0, 0, 90, lineColor, thickness, lineType );
//            ellipse( img, p2+Point(-cornerRadius, cornerRadius), Size( cornerRadius, cornerRadius ), 270.0, 0, 90, lineColor, thickness, lineType );
//            ellipse( img, p3+Point(-cornerRadius, -cornerRadius), Size( cornerRadius, cornerRadius ), 0.0, 0, 90, lineColor, thickness, lineType );
//            ellipse( img, p4+Point(cornerRadius, -cornerRadius), Size( cornerRadius, cornerRadius ), 90.0, 0, 90, lineColor, thickness, lineType );
//            //////////////////////////////////////////////////////////////////////////////////////
//
//            //draw some crosshairs around the object
//            int x, y = 0;
//            x = roi.x + roi.width / 2;
//            y = roi.y + roi.height / 2;
//
//            cv::circle(img, cv::Point(x, y), roi.width/5, Scalar(0, 255, 0), 1, 0.5);
//            cv::circle(img, cv::Point(x, y), 3, Scalar(255, 0, 0), CV_FILLED);
//
////            cv::line(frame, cv::Point(x, y), cv::Point(x, y - 15), Scalar(0, 255, 0), 1);
////            cv::line(frame, cv::Point(x, y), cv::Point(x, y + 15), Scalar(0, 255, 0), 1);
////            cv::line(frame, cv::Point(x, y), cv::Point(x - 15, y), Scalar(0, 255, 0), 1);
////            cv::line(frame, cv::Point(x, y), cv::Point(x + 15, y), Scalar(0, 255, 0), 1);
//
//
//            CvPoint nPoint;
//            for (int i = 0; i < cmt->trackedKeypoints.size(); i++) {
//                nPoint.x = cmt->trackedKeypoints[i].first.pt.x * px;
//                nPoint.y = cmt->trackedKeypoints[i].first.pt.y * py;
//                cv::circle(img, nPoint, 3, cv::Scalar(255, 255, 255));
//            }
//        }
//    }

}

jintArray
Java_com_sjp_sjplab_sjplabandroidot_MainActivity_CMTgetRect(JNIEnv *env, jobject)
{

    if (!CMTinitiated)
        return NULL;

    jintArray result;
    result = env->NewIntArray(8);



    jint fill[8];

    {

        fill[0]=cmt->topLeft.x;
        fill[1]=cmt->topLeft.y;
        fill[2]=cmt->topRight.x;
        fill[3]=cmt->topRight.y;
        fill[4]=cmt->bottomLeft.x;
        fill[5]=cmt->bottomLeft.y;
        fill[6]=cmt->bottomRight.x;
        fill[7]=cmt->bottomRight.y;
        env->SetIntArrayRegion(result, 0, 8, fill);
        return result;
    }

    return NULL;

}
#ifdef __cplusplus
}
#endif