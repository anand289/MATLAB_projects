s = tf('s');

m = 18;
wn = 2*pi*1049;
beta = 0.05;

P = (1/(m*s^2)) - (1/(m*s^2 + 2*beta*wn*s + wn^2)); 




%LTI controller
kp = 10;
wi = 1;
C = kp*wi/s;