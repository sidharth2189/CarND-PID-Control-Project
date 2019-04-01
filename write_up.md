# Reflection

In this project a PID controller is implemented in C++ to maneuver a vehicle around a track. The simulator provides the cross track error (CTE) and the velocity (mph) in order to compute the appropriate steering angle.

A link to the implementation video can be found [here](https://github.com/sidharth2189/CarND-PID-Control-Project/blob/master/video.mp4)

## Describe the effect each of the P, I, D components have in implementation

Initially, with zero values of P, I and D, the car continues without any steer and goes off the track.
A proportional control is introduced so that vehicle slowly keeps to the centre of the track. However, with time, the vehicle oscillates with respect to centre of track and goes off track eventually.

A derivative term is introduced that can contain this oscillation and smooth out the vehicle movement.

An integral part of the error is required to reduce any bias in the controller, by integrating the error over cycles. The effect of this is perceptible when car is allowed to run for longer time.

For this project, the order of magnitude of P and D were close, with P value being slightly smaller. And this was sufficient to keep vehicle on track, without any I value. However, a value of I, much smaller in order of magnitue compared to P and D, was tried when the vehicle was run for longer period of time.

## Describe how the final hyperparameters were chosen.

1) Set all of P, I and D values initially as zero. Increase P such that intially vehicle tries to keep to the curvature of the track. As time passes, vehcile is unable to keep to centre of lane and goes off track.
2) Increase P further, so that the vehicle keeps to the track for a longer distance. But now the, vehicle is unstable. It oscillates with increasing amplitude.
3) To contain this, increase D, such that the oscillations are contained even at corners that appear in the track.
4) If P is not high enough to steer through the corners, increase P
5) Adjust D accordingly to smoothen at curves.
6) Continue with this approach iteratively, making sure all part of track are covered safely.
7) The throttle can be a factor in deciding how much time the system allows a tuned PID to excercise control
8) Try to lower speeds as error increases at corners.
9) Finally, add a very small order of magnitude of I value and check if it affects the control in the long run.
