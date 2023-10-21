// kalman_filter.cpp

#include "kalman_filter.h"

#include <iostream>

using namespace std;

template <int N_X, int N_Y>
void Kalman<N_X, N_Y>::SetCoef(const MatrixXX &F_in, const MatrixXX &P_in, const MatrixXX &Q_in, const MatrixYX &H_in, const MatrixYY &R_in)
{
    F = F_in;
    P = P_in;
    Q = Q_in;
    H = H_in;
    R = R_in;
}

template <int N_X, int N_Y>
void Kalman<N_X, N_Y>::Predict()
{
    xp = F * x;
    P = F * P * F.transpose() + Q;
}

template <int N_X, int N_Y>
Kalman<N_X, N_Y>::VectorX Kalman<N_X, N_Y>::MeasurementUpdate(const VectorY &z_in)
{
    z = z_in;
    auto y = z - H * xp;
    auto H_T = H.transpose();
    auto S = H * P * H_T + R;
    K = P * H_T * S.inverse();
    x = xp + K * y;
    P = (Eigen::MatrixXd::Identity(N_X, N_X) - K * H) * P;

    // cout << x << endl;

    return x;
}

template <int N_X, int N_Y>
Kalman<N_X, N_Y>::VectorX *Kalman<N_X, N_Y>::FuturePredict(int iterations)
{
    if (iterations < 1)
        return nullptr;

    VectorX *predictions = new VectorX[iterations];
    predictions[0] = F * x;
    for (int i = 1; i < iterations; i++)
    {
        predictions[i] = F * predictions[i - 1];
    }

    return predictions;
}