// main.cpp
// change the point in the world coordinate system to the pixel in the photo

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Eigen/Dense>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;
using namespace Eigen;

Point2d World2Photo(Point3d world_p);

int main()
{
    const string file_path = "points.txt";
    ifstream fin;
    fin.open(file_path, ios::in);

    if (fin.is_open())
    {
        const string photo_path = "points.png";
        Mat photo = Mat::zeros(cv::Size(2560, 1600), CV_8UC3);

        int count;
        fin >> count;

        for (int i = 0; i < count; i++)
        {
            vector<double> world_v;
            for (int j = 0; j < 3; j++)
            {
                string tmp_s;
                fin >> tmp_s;
                double tmp_d = stod(tmp_s);
                world_v.push_back(tmp_d);
            }
            Point3d world_p(world_v[0], world_v[1], world_v[2]);
            Point2d photo_p = World2Photo(world_p);

            if (i % (count / 30) == 0)
                cout << photo_p << endl;

            circle(photo, photo_p, 2, cv::Scalar(0, 0, 255), 2);
        }

        imshow("photo", photo);
        waitKey();
        destroyAllWindows();

        imwrite(photo_path, photo);
    }
    fin.close();

    return 0;
}

Point2d World2Photo(Point3d world_p)
{
    static const Quaterniond Q(-0.5, 0.5, 0.5, -0.5);
    static const Matrix3d R = Q.toRotationMatrix();
    static const Vector3d T(2, 2, 2);
    static Matrix4d transform_matrix;
    transform_matrix << R, T, 0, 0, 0, 1;

    // cout << transform_matrix.inverse() << endl;

    static Matrix<double, 3, 4> F;
    F << 400., 0., 190., 0.,
        0., 400., 160., 0.,
        0., 0., 1., 0.;

    // Quaternion method
    Quaterniond tmp_q(0, world_p.x - T(0, 0), world_p.y - T(1, 0), world_p.z - T(2, 0));
    Quaterniond camera_rotate_q = Q.conjugate() * tmp_q * Q;
    Vector4d camera_v(camera_rotate_q.x(), camera_rotate_q.y(), camera_rotate_q.z(), 1);
    Vector3d photo_v = F * camera_v;

    // rotation matrix method
    // Vector4d world_v(world_p.x, world_p.y, world_p.z, 1);
    // Vector3d photo_v = F * transform_matrix.inverse() * world_v;

    return Point2d(photo_v(0, 0) / photo_v(2, 0), photo_v(1, 0) / photo_v(2, 0));
}