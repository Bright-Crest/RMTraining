// recognize the armors of the robot
// main.cpp

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>

using namespace std;

void SelectContours(const vector<vector<cv::Point>> &contours, vector<int> &index);

int main()
{
    string video_path = "./armor.mp4";
    string save_path = "./recognized_armor.avi";
    cv::VideoCapture vcaptuer(video_path);

    if (!vcaptuer.isOpened())
        return false;

    int frame_width = vcaptuer.get(cv::CAP_PROP_FRAME_WIDTH);
    int frame_height = vcaptuer.get(cv::CAP_PROP_FRAME_HEIGHT);

    cv::VideoWriter vwriter(save_path, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), vcaptuer.get(cv::CAP_PROP_FPS), cv::Size(frame_width, frame_height));

    int count = 0;
    while (true)
    {
        cv::Mat frame;

        vcaptuer >> frame;
        if (frame.empty())
            break;

        count++;

        // TODO

        cv::Mat hsv;
        cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);

        cv::Mat hsv_part;
        cv::inRange(hsv, cv::Scalar(10, 43, 100), cv::Scalar(26, 255, 255), hsv_part);

        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
        cv::Mat morph;
        cv::morphologyEx(hsv_part, morph, cv::MORPH_CLOSE, kernel, cv::Point(-1, -1), 3);

        vector<vector<cv::Point>> contours;
        vector<cv::Vec4i> hierarchy;

        cv::findContours(morph, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        vector<int> index;
        SelectContours(contours, index);

        cv::Mat canvas = cv::Mat::zeros(cv::Size(frame_width, frame_height), CV_8UC1);

        for (int i = 0; i < index.size(); i++)
        {
            cv::drawContours(frame, contours, index[i], cv::Scalar(255, 0, 0), 2);
            cv::drawContours(canvas, contours, index[i], cv::Scalar(255), 1);
        }

        // decrease computation
        int frame_count = vcaptuer.get(cv::CAP_PROP_FRAME_COUNT);
        if (count % (int)ceil(frame_count / 5) == 0)
        {
            // channel method failed
            // cv::Mat channels[3];
            // cv::split(frame, channels);
            // cv::Mat sub = channels[2]- channels[0];
            // cv::Mat norm;
            // cv::normalize(sub, norm, 0., 255., cv::NORM_MINMAX);

            // hsv extraction successed
            // int thresh = 150;
            // cv::Mat binary;
            // cv::threshold(norm, binary, thresh, 255, cv::THRESH_BINARY);

            // cv::Mat hsv;
            // cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);

            // cv::Mat hsv_part;
            // cv::inRange(hsv, cv::Scalar(10, 43, 100), cv::Scalar(26, 255, 255), hsv_part);

            // cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
            // cv::Mat morph;
            // cv::morphologyEx(hsv_part, morph, cv::MORPH_CLOSE, kernel, cv::Point(-1, -1), 3);

            // vector<vector<cv::Point>> contours;
            // vector<cv::Vec4i> hierarchy;

            // cv::findContours(morph, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

            // vector<int> index;
            // SelectContours(contours, index);

            // cv::Mat canvas = cv::Mat::zeros(cv::Size(frame_width, frame_height), CV_8UC1);

            // for (int i = 0; i < index.size(); i++)
            // {
            //     cv::drawContours(frame, contours, index[i], cv::Scalar(255, 0, 0), 2);
            //     cv::drawContours(canvas, contours, index[i], cv::Scalar(255), 1);
            // }

            // cv::drawContours(canvas, contours, -1, cv::Scalar(255), 1);

            // cv::imshow(to_string(count) + " frame", frame);
            // cv::imshow(to_string(count) + " canvas", canvas);
            // cv::imshow(to_string(count) + " norm", norm);
            // cv::imshow(to_string(count) + " binary", binary);
            // cv::imshow(to_string(count) + " hsv_part", hsv_part);
            // cv::imshow(to_string(count) + " morph", morph);
            // cv::imshow(to_string(count) + " dilate_frame", dilate_frame);
            // cv::imshow(to_string(count) + " contour_frame", contour_frame);

            // cv::waitKey(0);
            // cv::destroyAllWindows();
        }

        vwriter.write(frame);
    }

    cv::destroyAllWindows();

    vcaptuer.release();
    vwriter.release();

    return 0;
}

void SelectContours(const vector<vector<cv::Point>> &contours, vector<int> &index)
{
    vector<cv::Vec4f> lines;
    lines.resize(contours.size());

    for (int i = 0; i < contours.size(); i++)
    {
        cv::fitLine(contours[i], lines[i], cv::DIST_L2, 0, 0.01, 0.01);

        // not too small
        if (cv::arcLength(contours[i], true) < 60 || cv::contourArea(contours[i]) < 60)
            continue;

        // vertical
        if (abs(lines[i][1]) < 0.08)
            continue;

        cv::Mat approx;
        cv::approxPolyDP(contours[i], approx, 2, true);

        if (!cv::isContourConvex(approx))
            continue;

        index.push_back(i);
    }

    // at least 2 contours to continue
    if (index.size() <= 1)
        return;

    // the contour which has the biggest area
    int max = index[0];
    for (int i = 0; i < index.size(); i++)
    {
        if (cv::contourArea(contours[max]) < cv::contourArea(contours[index[i]]))
            max = index[i];
    }

    double max_vx = lines[max][0], max_vy = lines[max][1];

    int j = 0;
    while (index[j] == max)
        j++;

    int theOther = index[j];
    double other_vx = lines[theOther][0], other_vy = lines[theOther][1];

    for (int i = 0; i < index.size(); i++)
    {
        if (index[i] == max)
            continue;

        // parallel
        if (abs(max_vx * lines[index[i]][1] - max_vy * lines[index[i]][0]) < abs(max_vx * other_vy - max_vy * other_vx))
        {
            theOther = index[i];
            other_vx = lines[theOther][0];
            other_vy = lines[theOther][1];
        }
    }

    index.clear();
    index.push_back(max);
    index.push_back(theOther);
}