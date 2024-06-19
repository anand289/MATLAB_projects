s = tf('s');

p = 1;
w = 2*pi*5;
q = 3;
beta = 0.7;

N = ((s+q)*w^2);
D = (s-p)*(s^2 + 2*beta*w*s + w^2);

P = N/D;

%LTI controller
kp = 10;
wi = 1;
C = kp*wi/s;