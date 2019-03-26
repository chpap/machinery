//
//  Class: SmokeDetection
//  Description: An algorithm to detect smoke using background subtraction.
//  Created:     17/03/2018
//  Author:      Christos Papachristou
//  Mail:        tsoupap@gmail.com
//
/////////////////////////////////////////////////////

#ifndef __SmokeDetection_H_INCLUDED__   
#define __SmokeDetection_H_INCLUDED__  

#include "machinery/algorithm/Algorithm.h"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/video/video.hpp"

namespace kerberos
{
    char SmokeDetectionName[] = "SmokeDetection";
    class SmokeDetection : public AlgorithmCreator<SmokeDetectionName, SmokeDetection>
    {
        private:
            int m_threshold;
            Image m_erodeKernel;
            Image m_dilateKernel;
            Image m_backgroud;
            cv::Ptr<cv::BackgroundSubtractorMOG2> m_subtractor;

        public:
            SmokeDetection(){}
            void setup(const StringMap & settings);
        
            void setErodeKernel(int width, int height);
            void setDilateKernel(int width, int height);
            void setThreshold(int threshold);
            void initialize(ImageVector & images);
            Image evaluate(ImageVector & images, JSON & data);
    };
}
#endif
