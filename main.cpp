#include <iostream>
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include "bezier.h"

Bezier bezierCurve;

int main(int argc, char* argv[])
{ 
	
	// Control points 
	float cp_init[2 * 4] = {
		// X
		200.0, 200.0, 250.0, 250.0,
		// Y
		150.0, 300.0, 200.0, 350.0
		};
	bezierCurve.setControlPoints(cp_init);

	// Create canvas	
    cv::Mat canvas(400, 400, CV_8UC3);

	// Draw curve
	for (int t = 0; t < 1000; t++)
	{
		cv::Point p = bezierCurve.getPoint(t);
		
		if (p.y > 500 || p.y < 0) p.y = 0;
		if (p.x > 500 || p.x < 0) p.x = 0;
        //std::cout << "X: " << p.x << "     Y: " << p.y << "\n";
		
        canvas.at<int>(p.x, p.y) = 255;
	}
	
    // Draw control points
    for (int j = 0; j < bezierCurve.getControlPointsCnt(); j++)
    {
        cv::Point p = bezierCurve.getControlPoint(j);

        if (p.y > 500 || p.y < 0) p.y = 0;
        if (p.x > 500 || p.x < 0) p.x = 0;
        //std::cout << "X: " << p.x << "     Y: " << p.y << "\n";

        circle(canvas, p, 5., cv::Scalar(200,200,200), 1, 8);
    }
		
	// Output control points
	bezierCurve.dumpControlPoints();
	
	//// Display output
    cv::namedWindow("BezierCurve", 1);
    cv::imshow("BezierCurve", canvas);
    cv::waitKey();
	
	return 0; 

}
