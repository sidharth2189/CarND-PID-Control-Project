#include "PID.h"
#include <math.h>

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
  // pid variables
  Kp = Kp_;
  Ki = Ki_;
  Kd = Kd_;
  
  // errors
  p_error = 0;
  i_error = 0;
  d_error = 0;
  err_sum = 0;
  count = 0;
  
  // Twiddle parmeters
  p = {Kp_, Ki_, Kd_};     // parameter
  dp = {0.05, 0.0001, 1.0}; // delta parameter
  tolerance = 0.02;        // tolerance threshold
  best_err = 10000000000;  // error comparison variable
}

void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
   */
  d_error = cte - p_error; // p_error contains previous cte
  p_error = cte;
  i_error = i_error + cte;
  
  // Sum of Errors
  err_sum = err_sum + pow(cte,2);
  
  // Count
  count++;
  
  // Twiddle starts--
  sum_dp = 0;
  for (unsigned int index = 0; index < dp.size(); index++)
  {
    sum_dp = sum_dp + dp[index];
  }
  if (sum_dp > tolerance)
  {
    for (unsigned int i = 0; i < p.size(); i++)
    {
      p[i] = p[i] + dp[i];
      if( PID::AvgError() < best_err)
      {
        best_err = PID::AvgError();
        dp[i] = 1.1 * dp[i];
      }
      else
      {
        p[i] = p[i] - 2 * dp[i];
        if( PID::AvgError() < best_err)
        {
          best_err = PID::AvgError();
          dp[i] = 1.1 * dp[i];
        }
        else
        {
          p[i] = p[i] + dp[i];
          dp[i] = 0.9 * dp[i];
        }
      }
    }
  }
  Kp = p[0];
  Ki = p[1];
  Kd = p[2];
  // Twiddle ends--    
}

double PID::TotalError() {
  /**
   * TODO: Calculate and return the total error
   */
  return -Kp * p_error - Kd * d_error - Ki * i_error;  // TODO: Add your total error calc here!
}

double PID::AvgError() {
  /**
   * Calculate and return average error
   */
  return err_sum/count;
}