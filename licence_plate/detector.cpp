// detector.cpp

#include "detector.h"

#include <iostream>
#include <vector>

using namespace std;

Detector::Detector(const string &path) : path_(path)
{
}

Detector::~Detector()
{
}

void Detector::Process()
{
    cv::Mat src, channels[3], sub, norm, binary, morph;

    src = cv::imread(path_);
    assert(src.channels() == 3);

    cv::split(src, channels);
    sub = channels[0] - channels[1] - channels[2];
    cv::normalize(sub, norm, 0., 255., cv::NORM_MINMAX);

    int thresh = 50;
    cv::threshold(norm, binary, thresh, 255., cv::THRESH_BINARY);

    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::morphologyEx(binary, morph, cv::MORPH_CLOSE, element, cv::Point(-1, -1), 10);

    vector<vector<cv::Point>> contours;
    vector<cv::Vec4i> hierarchy;
    cv::findContours(morph, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // cv::Mat zero_mat = cv::Mat::zeros(cv::Size(src.cols, src.rows), CV_8UC1);
    // cv::drawContours(src, contours, -1, cv::Scalar(255, 255, 255), 1);

    int right_index = 0;
    if (contours.size() > 1)
    {
        for (int i = 0; i < contours.size(); i++)
        {
            if (cv::contourArea(contours[i]) < 500)
                continue;

            cv::RotatedRect rect = cv::minAreaRect(contours[i]);

            if (rect.size.area() > 1.3 * cv::contourArea(contours[i]))
                continue;

            right_index = i;
            break;
        }
    }

    vector<vector<cv::Point>> new_contour(1);
    cv::approxPolyDP(contours[right_index], new_contour[0], 10, true);

    cv::drawContours(src, new_contour, 0, cv::Scalar(0, 0, 255), 1);

    // cv::imshow("norm", norm);
    // cv::imshow("binary", binary);
    // cv::imshow("morph", morph);
    cv::imshow("contours", src);
    cv::waitKey();
    cv::destroyAllWindows();
}