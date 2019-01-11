#ifndef BEZIER_H
#define BEZIER_H

#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui_c.h>

class Bezier 
{
public:
    Bezier();
    cv::Point getPoint(int t, int tMax);

    void setControlPoints(float* input);
    int getControlPointsCnt();
    cv::Point getControlPoint(int p);
    void dumpControlPoints();

private:
    cv::Mat* m_controlPoints;
    int m_controlPointsCnt;
};

#endif
