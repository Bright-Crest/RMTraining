// main.cpp
// PnP

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <string>
#include <Eigen/Dense>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d.hpp> // for FileStorage
#include <yaml-cpp/yaml.h>
#include "./hw3_t1/big_armor_scale.hpp"

using namespace std;
using namespace cv;
using namespace Eigen;
using namespace YAML;

extern const vector<Point3d> PW_BIG;

bool GetFAndC(const string &yml_path, Mat &camera_matrix, Mat &dist_coeffs);
bool GetImuAndArmor(const string &txt_path, Quaterniond &q, vector<Point2d> &img_points);

int main()
{
    const string yml_path = "./hw3_t1/f_mat_and_c_mat.yml";
    const string txt_path = "./hw3_t1/imu_and_armor.txt";
    const vector<Point3d> object_points = PW_BIG;

    Quaterniond QCamera2World; // (-0.0816168, 0.994363, -0.0676645, -0.00122528);
    vector<Point2d> img_points;
    Mat camera_matrix, dist_coeffs;

    if (!GetImuAndArmor(txt_path, QCamera2World, img_points))
        return 0;
    if (!GetFAndC(yml_path, camera_matrix, dist_coeffs))
        return 0;

    const Matrix3d RMCamera2World = QCamera2World.matrix();

    Mat rvec, tvec;
    solvePnP(object_points, img_points, camera_matrix, dist_coeffs, rvec, tvec);

    // object => camera => gyro
    cout << RMCamera2World.reverse() * Vector3d(tvec.at<double>(0), tvec.at<double>(1), tvec.at<double>(2)) << endl;
    // cout << RMCamera2World * Vector3d(tvec.at<double>(0), tvec.at<double>(1), tvec.at<double>(2)) << endl;

    return 0;
}

bool GetFAndC(const string &yml_path, Mat &camera_matrix, Mat &dist_coeffs)
{
    FileStorage fsi(yml_path, FileStorage::READ);
    if (!fsi.isOpened())
    {
        cout << yml_path << " cannot be open\n";
        return false;
    }

    fsi["F"] >> camera_matrix;
    fsi["C"] >> dist_coeffs;
    fsi.release();

    return true;
}

bool GetImuAndArmor(const string &txt_path, Quaterniond &q, vector<Point2d> &img_points)
{
    fstream fin(txt_path, ios::in);
    if (!fin.is_open())
    {
        cout << txt_path << " cannot be open\n";
        return false;
    }

    string tmp;
    getline(fin, tmp);
    getline(fin, tmp);

    double x, y, z, w;
    sscanf(tmp.c_str(), "%lfi + %lfj + %lfk + %lf", &x, &y, &z, &w);
    q = Quaterniond(w, x, y, z);

    getline(fin, tmp);

    for (int i = 0; i < 4; i++)
    {
        double a, b;
        fin >> a >> b;
        img_points.push_back(Point2d(a, b));
    }

    fin.close();

    return true;
}