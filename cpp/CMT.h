#ifndef CMT_H
#define CMT_H

#include <opencv2/opencv.hpp>
#include <opencv2/features2d/features2d.hpp>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/ocl.hpp>



class CMT
{
public:
    std::string detectorType;
    std::string descriptorType;
    std::string matcherType;
    int descriptorLength;
    int thrOutlier;
    float thrConf;
    float thrRatio;

    bool estimateScale;
    bool estimateRotation;

    cv::Ptr<cv::FeatureDetector> detector;
    cv::Ptr<cv::DescriptorExtractor> descriptorExtractor;
    cv::Ptr<cv::DescriptorMatcher> descriptorMatcher;

    cv::UMat selectedFeatures;
    std::vector<int> selectedClasses;
    cv::UMat featuresDatabase;
    std::vector<int> classesDatabase;

    std::vector<std::vector<float> > squareForm;
    std::vector<std::vector<float> > angles;

    cv::Point2f topLeft;
    cv::Point2f topRight;
    cv::Point2f bottomRight;
    cv::Point2f bottomLeft;

    cv::Rect_<float> boundingbox;
    bool hasResult;


    cv::Point2f centerToTopLeft;
    cv::Point2f centerToTopRight;
    cv::Point2f centerToBottomRight;
    cv::Point2f centerToBottomLeft;

    std::vector<cv::Point2f> springs;

    cv::UMat im_prev;
    std::vector<std::pair<cv::KeyPoint,int> > activeKeypoints;
    std::vector<std::pair<cv::KeyPoint,int> > trackedKeypoints;

    unsigned int nbInitialKeypoints;

    std::vector<cv::Point2f> votes;

    std::vector<std::pair<cv::KeyPoint, int> > outliers;

    CMT();
    bool initialise(cv::UMat im_gray0, cv::Point2f topleft, cv::Point2f bottomright);
    void estimate(const std::vector<std::pair<cv::KeyPoint, int> >& keypointsIN, cv::Point2f& center, float& scaleEstimate, float& medRot, std::vector<std::pair<cv::KeyPoint, int> >& keypoints);
    void processFrame(cv::UMat im_gray);

//    bool Save(const char *path);
//    bool Load(const char *path);
};

class Cluster
{
public:
    int first, second;//cluster id
    float dist;
    int num;
};

void inout_rect(const std::vector<cv::KeyPoint>& keypoints, cv::Point2f topleft, cv::Point2f bottomright, std::vector<cv::KeyPoint>& in, std::vector<cv::KeyPoint>& out);
void track(cv::UMat im_prev, cv::UMat im_gray, const std::vector<std::pair<cv::KeyPoint, int> >& keypointsIN, std::vector<std::pair<cv::KeyPoint, int> >& keypointsTracked, std::vector<unsigned char>& status, int THR_FB = 20);
cv::Point2f rotate(cv::Point2f p, float rad);
#endif // CMT_H
