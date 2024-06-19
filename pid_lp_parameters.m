% PID and LP with Notch

% parameters
kp = 32000000;
fi = 105;
fd = 183;
flp = 5000;
wlp = 2*pi*flp;
beta = 0.65;

s = tf('s');

%pid_lp
Cp = kp;
Ci = (kp*2*pi*fi)/s ;
Cd = (s*kp)/(2*pi*fd);
Clp = (wlp^2)/(s^2 + 2*beta*wlp*s + wlp^2);

C = (Cp + Ci + Cd)*Clp;

%notch