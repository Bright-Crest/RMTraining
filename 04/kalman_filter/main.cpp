// main.cpp
// pedict dollar by Kalman Filter

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Eigen/Dense>
#include "kalman_filter.h"
#include "kalman_filter.cpp"

using namespace std;

int main()
{
    const string file_path = "./dollar.txt";
    const string fout_path = "./predictions.txt";

    const int N_X = 2, N_Y = 1;
    using KF = Kalman<N_X, N_Y>;

    fstream fin;
    fin.open(file_path, ios::in);

    if (!fin.is_open())
    {
        cout << file_path << " cannot be open\n";
        return 0;
    }

    vector<double> data;
    double tmp;

    while (fin >> tmp)
    {
        data.push_back(tmp);
    }
    fin.close();

    if (data.size() != 30)
    {
        cout << "data size is not 30\n";
    }

    KF kf;

    KF::VectorX x_0;
    x_0 << data.front(), 0;
    KF::MatrixXX F;
    F << 1, 1,
        0, 1;
    KF::MatrixXX P;
    P << 1, 0,
        0, 100;
    KF::MatrixXX Q;
    Q << 1, 0,
        0, 1;
    KF::MatrixYX H;
    H << 1, 0;
    KF::MatrixYY R;
    R << 0.01;

    kf.Initialize(x_0);
    kf.SetCoef(F, P, Q, H, R);
    for (int i = 0; i < data.size(); i++)
    {
        KF::VectorY z;
        z << data[i];

        kf.Predict();
        kf.MeasurementUpdate(z);
    }

    const int Days = 10;
    KF::VectorX *predictions;
    predictions = kf.FuturePredict(Days);

    fstream fout;
    fout.open(fout_path, ios::out);

    if (!fout.is_open())
    {
        cout << fout_path << " cannot be open\n";
        return 0;
    }

    for (int i = 0; i < Days; i++)
    {
        fout << predictions[i](0, 0) << endl;

        cout << predictions[i](0, 0) << endl;
    }

    fout.close();

    return 0;
}