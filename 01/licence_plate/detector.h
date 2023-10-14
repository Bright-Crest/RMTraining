// detector.h

#ifndef _DETECTOR_H_
#define _DETECTOR_H_

#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <assert.h>

using namespace std;

class Detector
{
public:
    string path_;
    string save_path_;

    Detector(const string &path = "", const string &save_path = "");
    ~Detector();
    void Process();
};

#endif // _DETECTOR_H_
