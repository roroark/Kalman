duration = 7; 
dt = .1;  
% Matrices
A = [1 dt; 0 1] ; 
B = [dt^2/2; dt]; 
C = [1 0]; 
% Acceleration due to Gravity
g = -9.8;

% Initial State, Predicted State
Velocity = 40;
Angle = pi/3;
Y = [0; Velocity*sin(Angle)];

% Noise Params
Acceleration_Sensor_Noise = 1; 
Measurement_Noise = 10;
Initial_Velocity_Measurement_Noise = .5;

Ez = Measurement_Noise^2;
Ex = Acceleration_Sensor_Noise^2 * [dt^4/4 dt^3/2; dt^3/2 dt^2]; 


Actual_Position = []; 
Actual_Velocity = []; 
Randomly_Generated_Measurement_Values = []; 

% Generate Real Values and Measured Values
figure(1);clf
for t = 0 : dt: duration
    Instantaneous_Acceleration_Noise = Acceleration_Sensor_Noise * [(dt^2/2)*randn; dt*randn];
    Y= A*Y+ B * g + Instantaneous_Acceleration_Noise;
    Instantaneous_Measurement_Noise = Measurement_Noise * randn;
    y = C * Y+ Instantaneous_Measurement_Noise;
    Actual_Position = [Actual_Position; Y(1)];
    Randomly_Generated_Measurement_Values = [Randomly_Generated_Measurement_Values; y];
    Actual_Velocity = [Actual_Velocity; Y(2)];
end

% Start Kalman Filtering
Kalman_Position_Estimate = []; 
Kalman_Velocity_Estimate = []; 
Y = [0; Velocity*sin(Angle)];
Y_Estimate = Y + [0;Initial_Velocity_Measurement_Noise * randn];
% Y_Estimate = Y;
% Error Matrix
Sigma = Ex; 
for t = 1:length(Actual_Position)
%   Temporary New Estimate Calculation Based on Path of Motion
%   X' = AX + Bu
    Y_Estimate = A*Y_Estimate + B*g;
     
    Sigma = A * Sigma * A' + Ex;
%   Kalman Gain proportional to Ez
    K = Sigma*C'*inv(C*Sigma*C'+Ez);
%   Choose between measured value and that determined from Path of Motion
%   Equations
    Y_Estimate = Y_Estimate + K * (Randomly_Generated_Measurement_Values(t) - C * Y_Estimate);
%   New Error Matrix
    Sigma = (eye(2)-K*C)*Sigma;
    
%   Store Values of Estimates
    Kalman_Position_Estimate = [Kalman_Position_Estimate; Y_Estimate(1)];
    Kalman_Velocity_Estimate = [Kalman_Velocity_Estimate; Y_Estimate(2)];
end


TimeAxis = 0 : dt : duration;
plot(TimeAxis,Actual_Position,'-r.',TimeAxis,Randomly_Generated_Measurement_Values,'-k.', TimeAxis,Kalman_Position_Estimate,'-g.');
axis([0 duration 0 80])


