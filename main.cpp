#include <iostream>
#include <stdio.h>
#include <ctime>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui_c.h>
#include "bezier.h"

Bezier bezierCurve;

int main(int argc, char* argv[])
{ 
    int const IMG_W = 640;
    int const IMG_H = 480;
    int const STEPS = 100;
    bool const RANDOM = true;

    // Control points
    float cp_init[2 * 4] = {
            // X
            133.0, 357.0, 20.0, 209.0,
            // Y
            350.0, 20.0, 30.0, 150.0
    };

    if (RANDOM) {
        // Seed
        std::srand(std::time(NULL));

        int i = 0;
        // X
        for(int j=0;j<4;++j)
            cp_init[i * 4 + j] = std::rand()%IMG_W;

        ++i;

        // Y
        for(int j=0;j<4;++j)
            cp_init[i * 4 + j] = std::rand()%IMG_H;
    }
    bezierCurve.setControlPoints(cp_init);

    // Create canvas
    cv::Mat canvas(IMG_H, IMG_W, CV_8UC3);

    // Draw curve
    int tMax = STEPS;
    for (int t = 0; t < tMax; t++)
    {
        cv::Point p = bezierCurve.getPoint(t, tMax);

        if (p.y > IMG_H || p.y < 0) p.y = 0;
        if (p.x > IMG_W || p.x < 0) p.x = 0;
        //std::cout << "X: " << p.x << "     Y: " << p.y << "\n";

        // FIXME: how to align (x,y) with CV_8UC3?
        //canvas.at<int>(p.y, p.x) = 255;
        cv::circle(canvas, p, 1., cv::Scalar(200,200,200), 1, 8);
    }

    // Draw control points
    for (int j = 0; j < bezierCurve.getControlPointsCnt(); j++)
    {
        cv::Point p = bezierCurve.getControlPoint(j);

        if (p.y > IMG_H || p.y < 0) p.y = 0;
        if (p.x > IMG_W || p.x < 0) p.x = 0;
        //std::cout << "X: " << p.x << "     Y: " << p.y << "\n";

        cv::circle(canvas, p, 3., cv::Scalar(0,200,0), 1, 8);
        cv::putText(canvas, std::to_string(j) + ":(" + std::to_string(p.x) + "," + std::to_string(p.y) +")",
                    p, cv::FONT_HERSHEY_PLAIN, 0.8, cv::Scalar(200, 0, 200));
    }

    // Output control points
    bezierCurve.dumpControlPoints();

    // Display output
    cv::imshow("cubicBezierCurve, tMax=" + std::to_string(STEPS) + ", imgSize=("
               + std::to_string(IMG_W) + "," + std::to_string(IMG_H) + ")", canvas);
    cv::waitKey();

    return 0;

}
