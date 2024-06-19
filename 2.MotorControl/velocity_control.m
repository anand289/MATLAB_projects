%%% Parameters for the motor simulink model

% Actuator Gain calcuation

V = [0.25 0.5 0.75];
i_monitor = [0.23 0.47 0.72];
i_probe = [0.233 0.464 0.701];
i_avg = (i_monitor + i_probe) / 2;
K_a = mean(i_avg ./ V);

% Motor Properties
K_t = 4.24e-2; % Nm/A
J = 8.5e-6; %Kg-m^2
b = 3.7e-6; % Nm-s damping constant
T_friction = 8.05e-3; % Nm
% T_friction  = 0;

CPR = 500; % encoder resolution
delta_theta = 2*pi / (4 * CPR); % quantization level theta-m
Tau_filter = 0.01;

% loading criteria
% T_load = 0.03; % Nm (max of .081 Nm)
T_load = 0;
time_load = 1; % s

command = 4*pi; % rad

%plant
G_s = tf([K_t*K_a],[J,b])

%controller parameter
% Kp = 0.5;
% % Kd = Kp/11.31;
% Ki = 8*Kd;
% C = tf([Kd Kp Ki],[1 0.5 0])

K = 0.01591;
z1 = 0.8;
p1 = 0;
z2 = 16.5;
p2 = 70;
C = K*tf([1 z1],[1 p1])*tf([1 z2],[1 p2])

L_cl = feedback(C*G_s,1);

figure(1)
bode(L_cl);
title('Closed loop bode');

L = C*G_s;
figure(2)
bode(L);
title('Open loop bode');

%% running simulink

sim('CL_Motor_model_velocity_control',1)

%%
figure(3)
clf
% plot theta vs time
plot(tout, position, 'LineWidth', 4)
hold on 
plot(tout, Theta_measured, 'LineWidth', 3)
xlabel('time (s)');
ylabel('angular position (rad)');
title('motor angular position');
grid on
% xlim([2,4])
set(gca, 'fontsize', 18)
legend('Simulated Actual Angle', 'Simulated Measured Angle', 'Location', 'southwest')

figure(4)
% plot speed vs time
xlabel('time (s)');
ylabel('angular velocity (rad/s)');
title('motor angular velocity');
grid on
plot(tout,speed, 'LineWidth', 1)
hold on;
plot(tout,velocity_measured, 'LineWidth', 1)
legend('Simulated Actual Velocity', 'Simulated Measured Velocity', 'Location', 'southwest')
% xlim([2,4])
set(gca, 'fontsize', 18)






