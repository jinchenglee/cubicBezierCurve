#include <math.h>
#include <iostream>
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <fstream>

#include "bezier.h"

/* 	
* 	Constructor
*/
Bezier::Bezier(){
	m_controlPoints = new cv::Mat(2, 4, CV_32FC2);
	m_controlPointsCnt = 0;
}

/* 	
*	Loads the control points for a cubic Bezier from an array.
*/
void Bezier::setControlPoints(float* input)
{
	int cnt = 0;
	for(int i=0;i<2;++i)
		for(int j=0;j<4;++j) {
			m_controlPoints->at<float>(i, j) = *(input + i * 4 + j);
			//std::cout << m_controlPoints->at<float>(i, j) << std::endl;
			cnt++;
		}
	m_controlPointsCnt = cnt/2;
}

/* 	
*	Returns the number of control points.
*/
int Bezier::getControlPointsCnt()
{
	return m_controlPointsCnt;
}

/* 	
*	Returns a Point with coordinates of a particular control point at pos
*/
cv::Point Bezier::getControlPoint(int pos)
{
	cv::Point CP; 

	CP.x = int(m_controlPoints->at<float>(0, pos));
	CP.y = int(m_controlPoints->at<float>(1, pos));
	
	return CP;
}

/* 	
*	Outputs all control points to stdout.
*/
void Bezier::dumpControlPoints()
{
	std::cout << "Control points:" << std::endl;
	for (int i = 0; i < m_controlPointsCnt; i++)
	{
		std::cout << "X(" << i << "): " << m_controlPoints->at<float>(0, i);
		std::cout << "\tY: " << m_controlPoints->at<float>(1, i) << std::endl;
	}
}

/* 	
*	Returns a Point object with coordinates at a particular station 
*	  on the Bezier Curve given by t.
*/
cv::Point Bezier::getPoint(int t)
{
	cv::Point pt;

 	int splineCount = m_controlPointsCnt/4;
 	int currSpline = (int) ((t/1000.0f) * (float) splineCount);
 	int splineShare = 1000/splineCount;
 	float step = (t % splineShare) / (float)splineShare;
 	int CP[2][4];
 	
	for (int i = currSpline*4; i < (currSpline+1)*4; i++)
	{
		CP[0][i] = (int) m_controlPoints->at<float>(0, i);
		CP[1][i] = (int) m_controlPoints->at<float>(1, i);
	}
	
	int cx = 3 * (CP[0][1] - CP[0][0]);
	int bx = 3 * (CP[0][2] - CP[0][1]) - cx;
	int ax = CP[0][3] - CP[0][0] - cx - bx;
	
	int cy = 3 * (CP[1][1] - CP[1][0]);
	int by = 3 * (CP[1][2] - CP[1][1]) - cy;
	int ay = CP[1][3] - CP[1][0] - cy - by;

	pt.x = (int) (ax*step*step*step + bx*step*step + cx*step + CP[0][0]);
	pt.y = (int) (ay*step*step*step + by*step*step + cy*step + CP[1][0]);
		
	return pt;
}

