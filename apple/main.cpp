// recognize an apple
// main.cpp

#include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <assert.h>

using namespace std;

struct MyData
{
    cv::Mat src;
    cv::Mat dst;

    MyData(cv::Mat s, cv::Mat d) : src(s), dst(d) {}
};

void onTrackbar(int value, void *data_p);

int main()
{
    cv::Mat src, channels[3], red_sub_blue, norm, binary, morph, morph2;
    src = cv::imread("./apple.png");
    assert(src.channels() == 3);

    cv::split(src, channels);
    red_sub_blue = channels[2] - channels[1] - channels[0];

    cv::normalize(red_sub_blue, norm, 0., 255., cv::NORM_MINMAX);

    int thresh = 20;
    cv::threshold(norm, binary, thresh, 255, cv::THRESH_BINARY);

    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::morphologyEx(binary, morph, cv::MORPH_OPEN, kernel, cv::Point(-1, -1));

    cv::Mat kernel2 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::morphologyEx(morph, morph2, cv::MORPH_CLOSE, kernel2, cv::Point(-1, -1), 3);

    vector<vector<cv::Point>> contours;
    vector<cv::Vec4i> hierarchy;
    cv::findContours(morph2, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);

    int max = 0;
    for (int i = 0; i < contours.size(); i++)
    {
        if (cv::arcLength(contours[i], true) > cv::arcLength(contours[max], true))
            max = i;
    }
    cv::drawContours(src, contours, max, cv::Scalar(255, 255, 255), 2);

    cv::Rect rect = cv::boundingRect(cv::Mat(contours[max]));
    cv::rectangle(src, rect, cv::Scalar(255, 255, 255), 2);

    // MyData data(norm, binary);
    // cv::Mat hsv, hsv_part1, hsv_part2, ones_mat;
    // cv::namedWindow("Thresh Bar", cv::WINDOW_AUTOSIZE);
    // cv::createTrackbar("Thresh", "Thresh Bar", &thresh, 255, onTrackbar, &data);
    // onTrackbar(thresh, &data);

    // hsv extraction failed
    // cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);
    // cv::inRange(hsv, cv::Scalar(0, 40, 40), cv::Scalar(20, 255, 255), hsv_part1);
    // cv::inRange(hsv, cv::Scalar(156, 40, 40), cv::Scalar(180, 255, 255), hsv_part2);
    // ones_mat = cv::Mat::ones(cv::Size(src.cols, src.rows), CV_8UC1);
    // binary = 255 * (ones_mat - (ones_mat - hsv_part1 / 255).mul(ones_mat - hsv_part2 / 255));

    // cv::imshow("morph", morph);
    // cv::imshow("morph2", morph2);

    cv::imshow("contours", src);
    cv::waitKey();
    cv::destroyAllWindows();

    cv::imwrite("./recognized_apple.png", src);
}

void onTrackbar(int thresh, void *data_p)
{
    MyData data = *(MyData *)data_p;
    cv::threshold(data.src, data.dst, thresh, 255, cv::THRESH_BINARY);
    cv::imshow("binary", data.dst);
}