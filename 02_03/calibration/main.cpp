// main.cpp
// camera calibration using a chess board

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

int main()
{
    const int img_count = 41;
    const int board_w = 11, board_h = 8;
    const int board_n = board_w * board_h;
    Size board_size(11, 8);

    Mat gray_img, binary_img, drawn_img;
    std::vector<Point2f> point_pix_pos_buf;
    std::vector<std::vector<Point2f>> point_pix_pos;
    int isFound, successes = 0;
    Size img_size;
    int k = 0, n = 0;

    for (int i = 0; i < img_count; i++)
    {
        Mat src0 = imread("./chess/" + to_string(i).append(".jpg"));
        if (src0.channels() != 3)
        {
            cout << to_string(i) + ".jpg doesn't have 3 channels\n";
            continue;
        }

        cvtColor(src0, gray_img, COLOR_BGR2GRAY);
        // adaptiveThreshold(gray_img, binary_img, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 225, 1);
        // threshold(gray_img, binary_img, 50, 255, THRESH_BINARY);

        if (i == 0)
        {
            img_size.width = src0.cols;
            img_size.height = src0.rows;
        }

        isFound = findChessboardCorners(src0, board_size, point_pix_pos_buf);

        if (isFound && point_pix_pos_buf.size() == board_n)
        {
            successes++;

            find4QuadCornerSubpix(gray_img, point_pix_pos_buf, Size(5, 5));
            point_pix_pos.push_back(point_pix_pos_buf);

            // FOR TEST
            // if (i % (img_count / 5) == 0)
            // {
            //     drawn_img = src0.clone();
            //     drawChessboardCorners(drawn_img, board_size, point_pix_pos_buf, isFound);
            //     imshow("corners", drawn_img);
            //     waitKey();
            //     destroyAllWindows();
            // }
        }
        else
        {
            std::cout << "\tfailed to found all chess board corners in " + to_string(i) + ".jpg" << std::endl;
        }

        point_pix_pos_buf.clear();
    };

    std::cout << successes << " useful chess boards" << std::endl;

    Size square_size(10, 10);
    std::vector<std::vector<Point3f>> point_grid_pos; // the coordinates of the self-defined coordinate system
    std::vector<Point3f> point_grid_pos_buf;

    for (int i = 0; i < successes; i++)
    {
        for (int j = 0; j < board_h; j++)
        {
            for (int k = 0; k < board_w; k++)
            {
                Point3f pt;
                pt.x = k * square_size.width;
                pt.y = j * square_size.height;
                pt.z = 0;
                point_grid_pos_buf.push_back(pt);
            }
        }
        point_grid_pos.push_back(point_grid_pos_buf);
        point_grid_pos_buf.clear();
    }

    if (successes > 0)
    {
        Mat camera_matrix(3, 3, CV_32FC1, Scalar::all(0));
        Mat dist_coeffs(1, 5, CV_32FC1, Scalar::all(0));
        std::vector<Mat> rvecs;
        std::vector<Mat> tvecs;

        std::cout << calibrateCamera(point_grid_pos, point_pix_pos, img_size, camera_matrix, dist_coeffs, rvecs, tvecs) << std::endl;
        std::cout << camera_matrix << std::endl
                  << dist_coeffs << std::endl;
    }

    return 0;
}