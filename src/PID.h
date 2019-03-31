#ifndef PID_H
#define PID_H
#include <vector>

using namespace std;

class PID {
 public:
  // Parameters for Twiddle
  vector<double> p;  // parameter
  vector<double> dp; // delta parameter
  double best_err;   // error comparison variable
  double tolerance;  // tolerance threshold
  double sum_dp;     // sum of delta parameters
  /**
   * Constructor
   */
  PID();

  /**
   * Destructor.
   */
  virtual ~PID();

  /**
   * Initialize PID.
   * @param (Kp_, Ki_, Kd_) The initial PID coefficients
   */
  void Init(double Kp_, double Ki_, double Kd_);

  /**
   * Update the PID error variables given cross track error.
   * @param cte The current cross track error
   */
  void UpdateError(double cte);

  /**
   * Calculate the total PID error.
   * @output The total PID error
   */
  double TotalError();
  
  /**
   * Calculate the average PID error.
   * @output The average PID error
   */
  double AvgError();
  
private:
  /**
   * PID Errors
   */
  double p_error;
  double i_error;
  double d_error;

  /**
   * PID Coefficients
   */ 
  double Kp;
  double Ki;
  double Kd;
  
  // Error
  double err_sum;
  int count; // to calculate average error
};

#endif  // PID_H