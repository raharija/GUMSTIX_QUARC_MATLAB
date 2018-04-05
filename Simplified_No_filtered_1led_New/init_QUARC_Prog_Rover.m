
%
% PRECAUTIONS:
% Before run this script, be sure to have correctly complete the TWO models
% QUARC_your_model_name and VERDEX_your_model_name.
%                                                                         %
% Augustin MANECY 29/05/2012                                              %
%                                                                         %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clc;
clear all;
close all;
    
%% %%%%%%%%%%%%%%%%%% section to be completed by user %%%%%%%%%%%%%%%%%%%%%

% model name (without WINDOWS or VERDEX on the beginning...)
HostModelName = 'Prog_Rover';

%%%%%%%%% Monitoring display options %%%%%%%%%%%
Nb_sec_display = 60;      % number of last second displayed onto scopes
refresh_time = 0.006;        % number of second between each update onto scope
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%% PARAMETERES %%%%%%%%%%    

% Sample time initialisation
Ts_Gumstix_min = 0.002;     % put here the minimal sample time in seconds for gumstix (which will correspond to fundamental sample time)
Ts_Host        = 0.002;     % put here your sample time in seconds for Host
Ts_Vicon       = 0.002;     % put here your sample time in seconds for the Vicon system
Ts_control     = 0.01;
Parm =[194.963419002586 95.9772476888769 2.15929744161042 74.6813385197025 8.78925485318541 84.1318278951173 -20.9859847099287 -18.2914009263784 -56.2676532914632 1.04074481863251];
%Parm =[216.568 224.277 -4.168 55.969 10.123 69.79 20.623 19.60 98.8945 1.033];
%display parameter calculation
Scope_decimation = refresh_time/Ts_Host;
ScopeDataLimit = Nb_sec_display/refresh_time;

NB_DATA_UDP_receive = 20;
%% Pour le filtrage
R =200;
Q=1;
Rpred = 200;
Qpred = 1;

%% DO NOT MODIFY THIS PART!

    % clean up all previous compiled file and directories
CleanUpHostModel(HostModelName);

    % Generation of sources and rtw executable for host
mex SfunCPP_RecoverVicon_SDK.cpp;
GenereHost(HostModelName,Ts_Host);