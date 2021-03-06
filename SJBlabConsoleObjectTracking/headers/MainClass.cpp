/*  Copyright 2011 AIT Austrian Institute of Technology
*
*   This file is part of OpenTLD.
*
*   OpenTLD is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   OpenTLD is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with OpenTLD.  If not, see <http://www.gnu.org/licenses/>.
*
*/
/*
 * MainX.cpp
 *
 *  Created on: Nov 17, 2011
 *      Author: Georg Nebehay
 */

#include "MainClass.h"

#include "Config.h"
#include "ImAcq.h"
#include "Gui.h"
#include "TLDUtil.h"
#include "Trajectory.h"
#include "CMT.h"

using namespace tld;
using namespace cv;

void MainClass::doWork()
{
    CMT cmt;
    
	//gclee
	VideoCapture cap(0); // open the default camera
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 640); //640 , 1280
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480); //480 , 720
	//double fps = 50;
	//cap.set(CV_CAP_PROP_FPS, fps);

	if (!cap.isOpened())  // check if we succeeded
		return;

	Mat frame;
	//gclee end

	Trajectory trajectory;
    //IplImage *img = imAcqGetImg(imAcq);
	cap >> frame;
	//IplImage *img = &IplImage(frame);
	//IplImage* img = cvCloneImage(&(IplImage)frame);
	
    //Mat grey(img->height, img->width, CV_8UC1);
    //cvtColor(cvarrToMat(img), grey, CV_BGR2GRAY);
	cv::Mat grey;
	cvtColor(frame, grey, CV_BGR2GRAY);

    tld->detectorCascade->imgWidth = grey.cols;
    tld->detectorCascade->imgHeight = grey.rows;
    tld->detectorCascade->imgWidthStep = grey.step;

	/*if(showTrajectory)
	{
		trajectory.init(trajectoryLength);
	}

    if(selectManually)
    {

        CvRect box;

        if(getBBFromUser(img, box, gui) == PROGRAM_EXIT)
        {
            return;
        }

        if(initialBB == NULL)
        {
            initialBB = new int[4];
        }

        initialBB[0] = box.x;
        initialBB[1] = box.y;
        initialBB[2] = box.width;
        initialBB[3] = box.height;
    }

    FILE *resultsFile = NULL;

    if(printResults != NULL)
    {
        resultsFile = fopen(printResults, "w");
        if(!resultsFile)
        {
            fprintf(stderr, "Error: Unable to create results-file \"%s\"\n", printResults);
            exit(-1);
        }
    }*/

    bool reuseFrameOnce = false;
    bool skipProcessingOnce = false;

    /*if(loadModel && modelPath != NULL)
    {
        tld->readFromFile(modelPath);
        reuseFrameOnce = true;
    }
    else if(initialBB != NULL)
    {
        Rect bb = tldArrayToRect(initialBB);

        printf("Starting at %d %d %d %d\n", bb.x, bb.y, bb.width, bb.height);

        tld->selectObject(grey, &bb);
        skipProcessingOnce = true;
        reuseFrameOnce = true;
    }*/

	//gclee
    //while(imAcqHasMoreFrames(imAcq))
	while(1)
    {
        double tic = cvGetTickCount();

        if(!reuseFrameOnce)
        { 
            //cvReleaseImage(&img);
			//gclee
			cap >> frame;
			//img = &IplImage(frame);
			//img = cvCloneImage(&(IplImage)frame);
            //img = imAcqGetImg(imAcq);

           /* if(img == NULL)
            {
                printf("current image is NULL, assuming end of input.\n");
                break;
            }
            cvtColor(cvarrToMat(img), grey, CV_BGR2GRAY);*/
        }

        if(!skipProcessingOnce)
        {
            //tld->processImage(cvarrToMat(img));
			tld->processImage(frame);
            //gclee
    //        if(cmt_tracking){
    //            cv::Mat im_gray;
    //            //cvtColor(cvarrToMat(img), im_gray, CV_BGR2GRAY);
				//cvtColor(frame, im_gray, CV_BGR2GRAY);
    //            cmt.processFrame(im_gray);
    //        }
            //gclee end
        }
        else
        {
            skipProcessingOnce = false;
        }

        /*if(printResults != NULL)
        {
            if(tld->currBB != NULL)
            {
                fprintf(resultsFile, "%d %.2d %.2d %.2d %.2d %f\n", imAcq->currentFrame - 1, tld->currBB->x, tld->currBB->y, tld->currBB->width, tld->currBB->height, tld->currConf);
            }
            else
            {
                fprintf(resultsFile, "%d NaN NaN NaN NaN NaN\n", imAcq->currentFrame - 1);
            }
        }*/

        double toc = (cvGetTickCount() - tic) / cvGetTickFrequency();

        toc = toc / 1000000;

        float fps = 1 / toc;

        int confident = (tld->currConf >= threshold) ? 1 : 0;

        if(showOutput || saveDir != NULL)
        {
            char string[128];

            char learningString[10] = "";

            if(tld->learning)
            {
                strcpy(learningString, "Learning");
            }

            sprintf(string, "#%d,Posterior %.2f; fps: %.2f, #numwindows:%d, %s", imAcq->currentFrame - 1, tld->currConf, fps, tld->detectorCascade->numWindows, learningString);
            CvScalar yellow = CV_RGB(255, 255, 0);
            CvScalar blue = CV_RGB(0, 0, 255);
            CvScalar black = CV_RGB(0, 0, 0);
            CvScalar white = CV_RGB(255, 255, 255);
            
            //gclee
            //if(tld->currBB == NULL){
                
			//if (cmt.hasResult) {
			//	for (int i = 0; i < cmt.trackedKeypoints.size(); i++) {
			//		//cvCircle(img, cmt.trackedKeypoints[i].first.pt, 3, cv::Scalar(255, 255, 255));
			//		CvPoint nPoint = cmt.trackedKeypoints[i].first.pt;
			//		cv::circle(frame, nPoint, 3, cv::Scalar(255, 255, 255));
			//	}
			//    //cvRectangle(img, cmt.boundingbox.tl(), cmt.boundingbox.br(), Scalar(0,0,255), 1, 4);
			//	CvPoint topleft = cvPoint(cmt.boundingbox.x, cmt.boundingbox.y);
			//	CvPoint bottomRight = cvPoint(cmt.boundingbox.x + cmt.boundingbox.width, cmt.boundingbox.y + cmt.boundingbox.height);
			//	cv::rectangle(frame, topleft, bottomRight, Scalar(0, 0, 255), 1, 4);

			//	//draw some crosshairs around the object
			//	int x, y = 0;
			//	x = topleft.x + (bottomRight.x - topleft.x) / 2;
			//	y = topleft.y + (bottomRight.y - topleft.y) / 2;

			//	cv::circle(frame, cv::Point(x, y), 10, Scalar(0, 255, 0), 1);
			//	cv::line(frame, cv::Point(x, y), cv::Point(x, y - 15), Scalar(0, 255, 0), 1);
			//	cv::line(frame, cv::Point(x, y), cv::Point(x, y + 15), Scalar(0, 255, 0), 1);
			//	cv::line(frame, cv::Point(x, y), cv::Point(x - 15, y), Scalar(0, 255, 0), 1);
			//	cv::line(frame, cv::Point(x, y), cv::Point(x + 15, y), Scalar(0, 255, 0), 1);
   //        }
           //gclee end
            
            if(tld->currBB != NULL)
            {
                CvScalar rectangleColor = (confident) ? blue : yellow;
				//cvRectangle(img, tld->currBB->tl(), tld->currBB->br(), rectangleColor, 8, 8, 0);
				CvPoint topleft = cvPoint(tld->currBB->x, tld->currBB->y);
				CvPoint bottomRight = cvPoint(tld->currBB->x + tld->currBB->width, tld->currBB->y + tld->currBB->height);

				cv::Rect r = cv::Rect(topleft.x, topleft.y, bottomRight.x - topleft.x, bottomRight.y - topleft.y);
				cv::rectangle(frame, r, rectangleColor, 2);
				CvPoint center = cvPoint(r.x + r.width / 2, r.y + r.height / 2);
				cv::line(frame, cvPoint(center.x - 2, center.y - 2), cvPoint(center.x + 2, center.y + 2), rectangleColor, 2);
				cv::line(frame, cvPoint(center.x - 2, center.y + 2), cvPoint(center.x + 2, center.y - 2), rectangleColor, 2);

				/*if(showTrajectory)
				{
					CvPoint center = cvPoint(tld->currBB->x+tld->currBB->width/2, tld->currBB->y+tld->currBB->height/2);
					cvLine(img, cvPoint(center.x-2, center.y-2), cvPoint(center.x+2, center.y+2), rectangleColor, 2);
					cvLine(img, cvPoint(center.x-2, center.y+2), cvPoint(center.x+2, center.y-2), rectangleColor, 2);
					trajectory.addPoint(center, rectangleColor);
				}*/
            }
			/*else if(showTrajectory)
			{
				trajectory.addPoint(cvPoint(-1, -1), cvScalar(-1, -1, -1));
			}

			if(showTrajectory)
			{
				trajectory.drawTrajectory(img);
			}*/

            /*CvFont font;
            cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, .5, .5, 0, 1, 8);
            cvRectangle(img, cvPoint(0, 0), cvPoint(img->width, 50), black, CV_FILLED, 8, 0);*/
			//cvPutText(img, string, cvPoint(25, 25), &font, white);
			cv::putText(frame, string, cvPoint(25, 25), 1, 1, white);

            //gclee test
			/*
            if(showForeground)
            {
                for(size_t i = 0; i < tld->detectorCascade->detectionResult->fgList->size(); i++)
                {
                    Rect r = tld->detectorCascade->detectionResult->fgList->at(i);
                    cvRectangle(img, r.tl(), r.br(), white, 1);
                }
			}
			*/
            //gclee end

            if(showOutput)
            {
                //gui->showImage(img);
				gui->showImage(frame);

                char key = gui->getKey();

                if(key == 'q') break;

                if(key == 'b')
                {

                    ForegroundDetector *fg = tld->detectorCascade->foregroundDetector;

                    if(fg->bgImg.empty())
                    {
                        fg->bgImg = grey.clone();
                    }
                    else
                    {
                        fg->bgImg.release();
                    }
                }

                if(key == 'c')
                {
                    //clear everything
                    tld->release();
                    //gclee
                    cmt_tracking = false;
                    //gclee end
                }

                if(key == 'l')
                {
                    tld->learningEnabled = !tld->learningEnabled;
                    printf("LearningEnabled: %d\n", tld->learningEnabled);
                }

                if(key == 'a')
                {
                    tld->alternating = !tld->alternating;
                    printf("alternating: %d\n", tld->alternating);
                }

                if(key == 'e')
                {
                    tld->writeToFile(modelExportFile);
                }

                if(key == 'i')
                {
                    tld->readFromFile(modelPath);
                }

                if(key == 'r')
                {
                    CvRect box;
					IplImage* img = cvCloneImage(&(IplImage)frame);
                    if(getBBFromUser(img, box, gui) == PROGRAM_EXIT)
                    {
                        break;
                    }

                    Rect r = Rect(box);
					cvtColor(cvarrToMat(img), grey, CV_BGR2GRAY);

                    tld->selectObject(grey, &r);

					cvReleaseImage(&img);
					img = NULL;
                    //gclee
                    //cmt tracket init
                   /* cv::Point2f initTopLeft(r.x, r.y);
                    cv::Point2f initBottomDown(r.x+r.width,r.y+r.height);
                    cmt_tracking = cmt.initialise(grey, initTopLeft, initBottomDown);
					*/
                    
                }
            }

            /*if(saveDir != NULL)
            {
                char fileName[256];
                sprintf(fileName, "%s/%.5d.png", saveDir, imAcq->currentFrame - 1);

                cvSaveImage(fileName, img);
            }*/
        }

        if(reuseFrameOnce)
        {
            reuseFrameOnce = false;
        }
    }

    /*cvReleaseImage(&img);
    img = NULL;
	*/

    if(exportModelAfterRun)
    {
        tld->writeToFile(modelExportFile);
    }

    /*if(resultsFile)
    {
        fclose(resultsFile);
    }*/
}
