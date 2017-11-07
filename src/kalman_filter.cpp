#include "kalman_filter.h"
#include <iostream>
#include <math.h>

using Eigen::MatrixXd;
using Eigen::VectorXd;

// Please note that the Eigen library does not initialize 
// VectorXd or MatrixXd objects with zeros upon creation.

KalmanFilter::KalmanFilter() {}

KalmanFilter::~KalmanFilter() {}

void KalmanFilter::Init(VectorXd &x_in, MatrixXd &P_in, MatrixXd &F_in,
                        MatrixXd &H_in, MatrixXd &R_in, MatrixXd &Q_in) {
  x_ = x_in;
  P_ = P_in;
  F_ = F_in;
  H_ = H_in;
  R_ = R_in;
  Q_ = Q_in;
}

void KalmanFilter::Predict() {
  /**
  TODO:
    * predict the state
  */
  x_ = F_ * x_;
  MatrixXd Ft = F_.transpose();
  P_ = F_ * P_ * Ft + Q_;
}

void KalmanFilter::Update(const VectorXd &z) {
  /**
  TODO:
    * update the state by using Kalman Filter equations
  */
  VectorXd z_pred = H_ * x_;
  VectorXd y = z - z_pred;

  Updatex_andP_(y);

}

void KalmanFilter::UpdateEKF(const VectorXd &z) {
  /**
  TODO:
    * update the state by using Extended Kalman Filter equations
  */
  double px = x_(0);
  double py = x_(1);
  double vx = x_(2);
  double vy = x_(3);

  double rho = sqrt(px*px + py*py);
  //defensive logic to prevent "undefined" atan2(0,0)
  double phi;
  if (fabs(px) < 1e-10 && fabs(py) < 1e-10) {
    phi = 0.0;
  } else {
    phi = atan2(py,px);
  }
  //defensive logic to avoid dividing by 0
  double rho_d;
  if (fabs(px) < 1e-10 && fabs(py) < 1e-10) {
    rho_d = 0.0;
  } else {
    rho_d = (px*vx + py*vy)/rho;
  }


  VectorXd z_pred(3);
  z_pred << rho, phi, rho_d;



  VectorXd y = z - z_pred;

    // Normalizing Angles, -pi to pi
    while (y[1] > M_PI || y[1] < -M_PI) {
      if (y[1] > M_PI) {
        y[1] -= 2 * M_PI;
      }
      if (y[1] < -M_PI) {
        y[1] += 2 * M_PI;
      }
    }

    Updatex_andP_(y);
}

void KalmanFilter::Updatex_andP_(const VectorXd &y) {
  MatrixXd Ht = H_.transpose();
  // moving this variable instead of repeating the calculation
  MatrixXd PHt = P_ * Ht;
  MatrixXd S = H_ * PHt + R_;
  MatrixXd Si = S.inverse();
  MatrixXd K = PHt * Si;

  //new estimate
  x_ = x_ + (K * y);

  long x_size = x_.size();
  MatrixXd I = MatrixXd::Identity(x_size, x_size);
  P_ = (I - K * H_) * P_;
}

