// recognize licence plates
// main.cpp

#include <string>

#include "detector.h"

using namespace std;

int main()
{
    Detector detector;
    for (int i = 0; i < 5; i++)
    {
        string path = "./plates/00" + to_string(i + 1) + ".jpg";
        string save_path = "./plates/recognized_00" + to_string(i + 1) + ".jpg";
        detector.path_ = path;
        detector.save_path_ = save_path;
        detector.Process();
    }

    return 0;
}