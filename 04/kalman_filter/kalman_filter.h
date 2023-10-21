// kalman_filter.h

#ifndef _KALMAN_FILTER_H_
#define _KALMAN_FILTER_H_

#include <Eigen/Dense>

using Eigen::Matrix;

template <int N_X, int N_Y>
class Kalman
{
public:
    using MatrixXX = Matrix<double, N_X, N_X>;
    using MatrixXY = Matrix<double, N_X, N_Y>;
    using MatrixYX = Matrix<double, N_Y, N_X>;
    using MatrixYY = Matrix<double, N_Y, N_Y>;
    using VectorX = Matrix<double, N_X, 1>;
    using VectorY = Matrix<double, N_Y, 1>;

    Kalman() {}
    ~Kalman() {}
    void Initialize(const VectorX &x_0) { x = x_0; }
    void SetCoef(const MatrixXX &F_in, const MatrixXX &P_in, const MatrixXX &Q_in, const MatrixYX &H_in, const MatrixYY &R_in);
    void Predict();
    VectorX MeasurementUpdate(const VectorY &z_in);
    inline VectorX GetX() { return x; }
    VectorX *FuturePredict(int iterations = 1);

private:
    VectorX x;  // estimated state
    VectorX xp; // predicted state
    MatrixXX F; // state transistion matrix
    MatrixXX P; // state covariance matrix
    MatrixXX Q; // process covariance matrix
    VectorY z;  // measuring state
    MatrixYX H; // measurement matrix
    MatrixYY R; // measurement covariance matrix
    MatrixXY K; // Kalman Gain
};

#endif // _KALMAN_FILTER_H_