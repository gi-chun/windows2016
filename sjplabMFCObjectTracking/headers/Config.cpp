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

#include "Config.h"

#include "MainClass.h"

using namespace std;

namespace tld
{

static char help_text[] =
    "usage: tld [option arguments] [arguments]\n"
    "option arguments:\n"
    "[-a <startFrameNumber>] video starts at the frameNumber <startFrameNumber>\n"
    "[-b <x,y,w,h>] Initial bounding box\n"
    "[-c] shows color images instead of greyscale\n"
    "[-d <device>] select input device: <device>=(IMGS|CAM|VID)\n"
    "    IMGS: capture from images\n"
    "    CAM: capture from connected camera\n"
    "    VID: capture from a video\n"
    "    STREAM: capture from a stream\n"
    "[-e <path>] export model after run to <path>\n"
    "[-f] shows foreground\n"
    "[-i <path>] <path> to the images or to the video\n"
    "[-h] shows help\n"
    "[-j <number>] specifies the <number> of the last frames which are considered by the trajectory; 0 disables the trajectory\n"
    "[-m <path>] if specified load a model from <path>. An initialBoundingBox must be specified or selectManually must be true.\n"
    "[-n <number>] specifies which camera device to use.\n"
    "[-p <path>] prints results into the file <path>\n"
    "[-s] if set, user can select initial bounding box\n"
    "[-t <theta>] threshold for determining positive results\n"
    "[-z <lastFrameNumber>] video ends at the frameNumber <lastFrameNumber>.\n"
    "    If <lastFrameNumber> is 0 or the option argument isn't specified means\n"
    "    take all frames.\n"
    "arguments:\n"
    "[<path>] <path> to the config file\n";

Config::Config() :
    m_selectManuallySet(false),
    m_methodSet(false),
    m_startFrameSet(false),
    m_lastFrameSet(false),
    m_trajectorySet(false),
    m_showDetectionsSet(false),
    m_showForegroundSet(false),
    m_thetaSet(false),
    m_printResultsSet(false),
    m_camNoSet(false),
    m_imagePathSet(false),
    m_modelPathSet(false),
    m_initialBBSet(false),
    m_showOutputSet(false),
    m_exportModelAfterRunSet(false)
{
}

Config::Config(Settings &settings) :
    m_settings(settings)
{
}

Config::~Config()
{
}

int Config::init(int argc, char **argv)
{

    return SUCCESS;
}

int Config::configure(MainClass *main)
{
 //   ImAcq *imAcq = main->imAcq;

 //   // imAcq
 //   imAcq->method = m_settings.m_method;
	////imAcq->method = IMACQ_CAM;
 //   imAcq->imgPath = (m_settings.m_imagePath.empty()) ? NULL : m_settings.m_imagePath.c_str();
 //   imAcq->lastFrame = m_settings.m_lastFrame;
	////imAcq->lastFrame = 0;
 //   imAcq->currentFrame = m_settings.m_startFrame;
	////imAcq->currentFrame = 0;
 //   imAcq->camNo = m_settings.m_camNo;
	////imAcq->camNo = 0;
 //   //imAcq->fps = m_settings.m_fps;
	//imAcq->fps = 30;
	
    // main
    main->tld->trackerEnabled = m_settings.m_trackerEnabled;
    main->showOutput = m_settings.m_showOutput;
    //gclee
	main->showTrajectory = (m_settings.m_trajectory) ? true : false;
    //main->showTrajectory =  true;
	main->trajectoryLength = m_settings.m_trajectory;
    main->printResults = (m_settings.m_printResults.empty()) ? NULL : m_settings.m_printResults.c_str();
    main->saveDir = (m_settings.m_outputDir.empty()) ? NULL : m_settings.m_outputDir.c_str();
    main->threshold = m_settings.m_threshold;
    main->showForeground = m_settings.m_showForeground;
    main->showNotConfident = m_settings.m_showNotConfident;
    main->tld->alternating = m_settings.m_alternating;
    main->tld->learningEnabled = m_settings.m_learningEnabled;
    main->selectManually = m_settings.m_selectManually;
    main->exportModelAfterRun = m_settings.m_exportModelAfterRun;
    main->modelExportFile = m_settings.m_modelExportFile.c_str();
    main->loadModel = m_settings.m_loadModel;
    main->modelPath = (m_settings.m_modelPath.empty()) ? NULL : m_settings.m_modelPath.c_str();
    main->seed = m_settings.m_seed;

    if(m_settings.m_initialBoundingBox.size() > 0)
    {
        main->initialBB = new int[4];

        for(int i = 0; i < 4; i++)
        {
            main->initialBB[i] = m_settings.m_initialBoundingBox[i];
        }
    }

    DetectorCascade *detectorCascade = main->tld->detectorCascade;
    detectorCascade->varianceFilter->enabled = m_settings.m_varianceFilterEnabled;
    detectorCascade->ensembleClassifier->enabled = m_settings.m_ensembleClassifierEnabled;
    detectorCascade->nnClassifier->enabled = m_settings.m_nnClassifierEnabled;

    // classifier
    detectorCascade->useShift = m_settings.m_useProportionalShift;
    detectorCascade->shift = m_settings.m_proportionalShift;
    detectorCascade->minScale = m_settings.m_minScale;
    detectorCascade->maxScale = m_settings.m_maxScale;
    detectorCascade->minSize = m_settings.m_minSize;
    detectorCascade->numTrees = m_settings.m_numTrees;
    detectorCascade->numFeatures = m_settings.m_numFeatures;
    detectorCascade->nnClassifier->thetaTP = m_settings.m_thetaP;
    detectorCascade->nnClassifier->thetaFP = m_settings.m_thetaN;

    return SUCCESS;
}

/*
 POSIX getopt for Windows

 AT&T Public License

 Code given out at the 1985 UNIFORUM conference in Dallas.
 */
#ifndef __GNUC__

#define NULL    0
#define EOF (-1)
#define ERR(s, c)   if(opterr){\
    fputs(argv[0], stderr);\
    fputs(s, stderr);\
    fputc(c, stderr);}

int opterr = 1;
int optind = 1;
int optopt;
char *optarg;

int getopt(int argc, char **argv, char *opts)
{
    static int sp = 1;
    register int c;
    register char *cp;

    if(sp == 1)
        if(optind >= argc || argv[optind][0] != '-' || argv[optind][1] == '\0')
            return (EOF);
        else if(strcmp(argv[optind], "--") == NULL)
        {
            optind++;
            return (EOF);
        }

    optopt = c = argv[optind][sp];

    if(c == ':' || (cp = strchr(opts, c)) == NULL)
    {
        ERR(": illegal option -- ", c);

        if(argv[optind][++sp] == '\0')
        {
            optind++;
            sp = 1;
        }

        return ('?');
    }

    if(*++cp == ':')
    {
        if(argv[optind][sp + 1] != '\0')
            optarg = &argv[optind++][sp + 1];
        else if(++optind >= argc)
        {
            ERR(": option requires an argument -- ", c);
            sp = 1;
            return ('?');
        }
        else
            optarg = argv[optind++];

        sp = 1;
    }
    else
    {
        if(argv[optind][++sp] == '\0')
        {
            sp = 1;
            optind++;
        }

        optarg = NULL;
    }

    return (c);
}

#endif  /* __GNUC__ */

}
