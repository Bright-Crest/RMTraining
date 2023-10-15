// recognize the armors of the robot
// main.cpp

#include <iostream>
#include <algorithm>
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

        cv::Mat hsv;
        cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);

        cv::Mat hsv_part;
        cv::inRange(hsv, cv::Scalar(10, 43, 100), cv::Scalar(26, 255, 255), hsv_part);

        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
        cv::Mat morph;
        cv::morphologyEx(hsv_part, morph, cv::MORPH_CLOSE, kernel, cv::Point(-1, -1), 9);

        vector<vector<cv::Point>> contours;
        vector<cv::Vec4i> hierarchy;
        cv::findContours(morph, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        vector<int> index;
        SelectContours(contours, index);

        if (index.size() == 0)
            continue;

        vector<vector<cv::Point2f>> short_edge_midpoints(index.size(), vector<cv::Point2f>(2));
        vector<double> angles(index.size());
        vector<int> new_index;
        const double PI = acos(-1);

        // select the contours that are nearly perpendicular to the horizontal plane
        for (int i = 0; i < index.size(); i++)
        {
            cv::RotatedRect rect;
            rect = cv::minAreaRect(contours[index[i]]);

            cv::Point2f points[4];
            rect.points(points);

            // find the short edges representing by short_index
            int short_index;
            if (pow(points[0].x - points[1].x, 2) + pow(points[0].y - points[1].y, 2) > pow(points[0].x - points[3].x, 2) + pow(points[0].y - points[3].y, 2))
                short_index = 3;
            else
                short_index = 0;

            short_edge_midpoints[i][0] = cv::Point2f((points[short_index].x + points[(short_index + 1) % 4].x) / 2, (points[short_index].y + points[(short_index + 1) % 4].y) / 2);
            short_edge_midpoints[i][1] = cv::Point2f((points[(short_index + 2) % 4].x + points[(short_index + 3) % 4].x) / 2, (points[(short_index + 2) % 4].y + points[(short_index + 3) % 4].y) / 2);

            angles[i] = atan2((short_edge_midpoints[i][0].y - short_edge_midpoints[i][1].y), (short_edge_midpoints[i][0].x - short_edge_midpoints[i][1].x)) * 180 / PI;
            if (angles[i] < 0)
                angles[i] = angles[i] + 180;
            angles[i] = angles[i] - 90;

            if (abs(angles[i]) < 20)
            {
                new_index.push_back(i);
                // cv::drawContours(frame, contours, index[i], cv::Scalar(255, 0, 0), 2);
            }
        }

        int max = 0;       // the most perpendicular
        int parallel;      // nearly parallel to "max"
        bool flag = false; // whether "parallel" is found

        if (new_index.size() > 1)
        {
            for (int i = 0; i < new_index.size(); i++)
            {
                if (abs(angles[new_index[i]]) < abs(angles[new_index[max]]))
                    max = i;
            }

            if (max == 0)
                parallel = 1;
            else
                parallel = 0;

            for (int i = 0; i < new_index.size(); i++)
            {
                if (i == max)
                    continue;

                if (abs(angles[new_index[i]] - angles[new_index[max]]) < abs(angles[new_index[parallel]] - angles[new_index[max]]))
                    parallel = i;
            }

            if (abs(angles[new_index[parallel]] - angles[new_index[max]]) > 5)
                flag = false;
            else
                flag = true;
        }

        if (flag)
        {
            vector<cv::Point2f> armor_points{short_edge_midpoints[new_index[max]][0], short_edge_midpoints[new_index[max]][1], short_edge_midpoints[new_index[parallel]][1], short_edge_midpoints[new_index[parallel]][0]};

            double height = sqrt(pow(armor_points[0].x - armor_points[1].x, 2) + pow(armor_points[0].y - armor_points[1].y, 2));
            double width = sqrt(pow(armor_points[0].x - armor_points[3].x, 2) + pow(armor_points[0].y - armor_points[3].y, 2));

            if (width / height < 3)
            {
                for (int j = 0; j < 4; j++)
                    cv::line(frame, armor_points[j], armor_points[(j + 1) % 4], cv::Scalar(255, 0, 0), 2);
            }
        }

        // FOR TEST: decrease computation
        // int frame_count = vcaptuer.get(cv::CAP_PROP_FRAME_COUNT);
        // if (count % (frame_count / 8) == 0)
        // {
        //     cv::imshow(to_string(count) + " frame", frame);
        //     // cv::imshow(to_string(count) + " canvas", canvas);
        //     // cv::imshow(to_string(count) + " norm", norm);
        //     // cv::imshow(to_string(count) + " binary", binary);
        //     // cv::imshow(to_string(count) + " hsv_part", hsv_part);
        //     // cv::imshow(to_string(count) + " morph", morph);
        //     // cv::imshow(to_string(count) + " dilate_frame", dilate_frame);
        //     // cv::imshow(to_string(count) + " contour_frame", contour_frame);

        //     cv::waitKey(0);
        //     cv::destroyAllWindows();
        // }

        vwriter.write(frame);
    }

    cv::destroyAllWindows();

    vcaptuer.release();
    vwriter.release();

    return 0;
}

void SelectContours(const vector<vector<cv::Point>> &contours, vector<int> &index)
{
    // FAILED: fit a line
    // vector<cv::Vec4f> lines;
    // lines.resize(contours.size());

    // for (int i = 0; i < contours.size(); i++)
    // {
    //     cv::fitLine(contours[i], lines[i], cv::DIST_L2, 0, 0.01, 0.01);

    //     // not too small
    //     if (cv::arcLength(contours[i], true) < 60 || cv::contourArea(contours[i]) < 60)
    //         continue;

    //     // vertical
    //     if (abs(lines[i][1]) < 0.08)
    //         continue;

    //     cv::Mat approx;
    //     cv::approxPolyDP(contours[i], approx, 2, true);

    //     if (!cv::isContourConvex(approx))
    //         continue;

    //     index.push_back(i);
    // }

    // // at least 2 contours to continue
    // if (index.size() <= 1)
    //     return;

    // // the contour which has the biggest area
    // int max = index[0];
    // for (int i = 0; i < index.size(); i++)
    // {
    //     if (cv::contourArea(contours[max]) < cv::contourArea(contours[index[i]]))
    //         max = index[i];
    // }

    // double max_vx = lines[max][0], max_vy = lines[max][1];

    // int j = 0;
    // while (index[j] == max)
    //     j++;

    // int theOther = index[j];
    // double other_vx = lines[theOther][0], other_vy = lines[theOther][1];

    // for (int i = 0; i < index.size(); i++)
    // {
    //     if (index[i] == max)
    //         continue;

    //     // parallel
    //     if (abs(max_vx * lines[index[i]][1] - max_vy * lines[index[i]][0]) < abs(max_vx * other_vy - max_vy * other_vx))
    //     {
    //         theOther = index[i];
    //         other_vx = lines[theOther][0];
    //         other_vy = lines[theOther][1];
    //     }
    // }

    // index.clear();
    // index.push_back(max);
    // index.push_back(theOther);

    for (int i = 0; i < contours.size(); i++)
    {
        // not too small
        if (cv::arcLength(contours[i], true) < 70 || cv::contourArea(contours[i]) < 70)
            continue;

        // basically convex
        cv::Mat approx;
        cv::approxPolyDP(contours[i], approx, 2, true);
        if (!cv::isContourConvex(approx))
            continue;

        index.push_back(i);
    }
}