
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
Java_com_sjp_sjplab_sjplabandroidot_MainActivity_OpenCMT(JNIEnv*, jobject, jlong addrGray, jlong addrRgba,jlong x, jlong y, jlong width, jlong height)
{

//	 if (cmt!=NULL)
//	 {
//		 delete cmt;
//	 }
//	 cmt = new CMT();
    Mat& im_gray  = *(Mat*)addrGray;
    //gclee
    UMat temp;
    im_gray.copyTo(temp);

    Point p1(x,y);
    Point p2(x+width,y+height);

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

    //gclee
    UMat temp;
    im_gray.copyTo(temp);

    cmt->processFrame(temp);

//	        for(int i = 0; i<cmt->trackedKeypoints.size(); i++)
//	            cv::circle(img, cmt->trackedKeypoints[i].first.pt, 3, cv::Scalar(255,255,255));
//    cv::line(img, cmt->topLeft, cmt->topRight, cv::Scalar(255,255,255));
//    cv::line(img, cmt->topRight, cmt->bottomRight, cv::Scalar(255,255,255));
//    cv::line(img, cmt->bottomRight, cmt->bottomLeft, cv::Scalar(255,255,255));
//    cv::line(img, cmt->bottomLeft, cmt->topLeft, cv::Scalar(255,255,255));

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