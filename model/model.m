clc; clear all; close all;
%Dane
M=1000;             %[kg]
c=800;              %[J/(kg*K)]
m=300;              %[kg/m]
n=7;                %[1]
v=1;                %[m/h]
T0=20;              %[^oC]
Tp=1500;            %[^oC]
cs=1000;            %[J/(kg*K)]
gs=1;               %[kg/m^3]

%Obliczanie punktu pracy
A=(n+1)*gs*cs;
B=m*v*c;
Tpracy=800;
qpracy=(B*(Tpracy-T0))/(A*(Tp-Tpracy));

%Zadawanie przyrostu dq
dq=1;

%Do modelu zlinearyzowanego
Tczas=M*c/((n+1)*qpracy*gs*cs+m*v*c);
k=((n+1)*gs*cs*Tp-(n+1)*gs*cs*Tpracy)/((n+1)*qpracy*gs*cs+m*v*c);

%Do modelu nieliniowego
a3=((n+1)*gs*cs)/(M*c);
a2=((n+1)*gs*cs*Tp)/(M*c);
a1=m*v/M;
a0=m*v*T0/M;

%Odpalanie symulacji, wyjœcia jako serie czasowe
set_param('model_nielin','Solver','ode15s','StopTime','10','MaxStep','1e-3');
set_param('model_zlin','Solver','ode15s','StopTime','10','MaxStep','1e-3');
sim('model_nielin');                                                            %Tnielin
sim('model_zlin');                                                              %Tzlin

%Prezentacja wyników
plot(Tnielin,'g');
hold on
plot(Tzlin,'r');
ylabel('T [^oC]','FontSize',14,'Interpreter','tex');
xlabel('t [h]','FontSize',14,'Interpreter','tex');
title(['Przepieg czasowy dla \Deltaq= ' num2str(dq) ' m^3/h'],'FontSize',14,'Interpreter','tex');
legend('Model nieliniowy','Model liniowy');