%%%%%%%%%%%%%%%%%%%%%%%%% init_COM_InOut_Full_MultiTask_Clock.m %%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% init_COM_InOut_Full_MultiTask_Clock: generates all the sources needed to 
%           build the model InOut_Full_MultiTask_Clock on your embedded Linux. 
%           An archive named COM_InOut_Full_MultiTask_Clock_sources.zip was 
%           generetaed in the directory ./ToBuid_COM_InOut_Full_MultiTask_Clock 
%           as a shell script to build the model. If your FTP server is 
%           correctly installed, this archive and this script were
%           automatically copied to the server.
%
%   - You can build this model on your embedded Linux using:
%       root@EmbeddedLinux~: ./UpToDate InOut_Full_MultiTask_Clock
%   - You can run this model on your embedded Linux using:
%       root@EmbeddedLinux~: ./RunModel InOut_Full_MultiTask_Clock -d <duration>
%
%   You can change the fundamental Sample Time of the model by adjusting
%   TsMin in this script.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Author: Augustin Manecy
%
% Copyright (C) 2011-2014 Augustin Manecy
%
% augustin.manecy@gmail.com
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% This file is part of RT-MaG Toolbox.
%
%   RT-MaG Toolbox is free software: you can redistribute it and/or modify
%   it under the terms of the GNU General Public License as published by
%   the Free Software Foundation, either version 3 of the License, or
%   (at your option) any later version.
%
%   RT-MaG Toolbox is distributed in the hope that it will be useful,
%   but WITHOUT ANY WARRANTY; without even the implied warranty of
%   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
%   GNU General Public License for more details.
%
%   You should have received a copy of the GNU General Public License
%   along with RT-MaG Toolbox.  If not, see <http://www.gnu.org/licenses/>.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% This version of GPL is at https://www.gnu.org/licenses/gpl-3.0.txt
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


clc;
clear all;
close all;


%% %%%%%%%%%%%%%%%%%% section to be completed by user %%%%%%%%%%%%%%%%%%%%%

% model name without the prefix 'COM_'
HostModelName = 'Prog_Rover';

% Base Sample Time 
SerialSampleTime = 0.01;    %sample time for serial communication
Ts_control = SerialSampleTime;
TsMin = 0.002;     % put here the minimal sample time in seconds for gumstix (which will correspond to the fundamental sample time of the solver)
R =200;
Q=1;
Rpred=200;
Qpred=1;
L =0.15;
l=0.15;                 
Rw = 0.05;
J_0_plus = 0.25*Rw*[1, 1, 1, 1; -1, 1, 1, -1; -1/(L+l), 1/(L+l), -1/(L+l), 1/(L+l)];
%% Fusion des capteurs
tr=0.01;
a_max = 1.5*2*pi*Rw/tr;
A = [eye(3,3) Ts_control.*eye(3,3); zeros(3,3)  eye(3,3)];
C = zeros(5,6);
C(1:2,1:2) = eye(2,2);              
C(3:5,4:6)= eye(3,3);
R_fus = zeros(5,5);
R_cap = 0.01;  %m^2
R_odo = 0.0001; %(m/s)^2
R_fus(1:2,1:2) =R_cap.*eye(2,2); 
R_fus(3:5,3:5) =R_odo.*eye(3,3); 
Q_fus = zeros(6,6);
Q_fus(1:3,1:3) = (((Ts_control)^2)*a_max/2).*eye(3,3);
Q_fus(4:6,4:6) = (Ts_control*a_max).*eye(3,3);


GenereCOM(HostModelName, TsMin);
