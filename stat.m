clc; clear all; close all;
%Dane
M=1000;             %[kg]
c=800;              %[J/(kg*K)]
m=300;              %[kg/m]
n=7;                %[1]
v=1;                %[m/h]
T0=20;              %[^oC]
Tp=1200;            %[^oC]
cs=1000;            %[J/(kg*K)]
gs=1.15;            %[kg/m^3]

A=(n+1)*gs*cs;
B=m*v*c;
qpracy=0:0.01:10;
Tpracy=(A*Tp*qpracy+B*T0)./(A*qpracy+B);

plot(qpracy,Tpracy);
title("Charakterystyka statyczna",'FontSize',16);
xlabel("q_P_R_A_C_Y [m^3/h]",'FontSize',14);
ylabel("T_P_R_A_C_Y [^oC]",'FontSize',14);