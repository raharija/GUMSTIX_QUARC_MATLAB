%% saving_file

folder = '..\Interception2\';
% folder = '..\Hoverfly\';

Reply=[];
while(isempty(Reply))
    Reply = input('Do you want to save the data of this test? [Y / N] : ', 's');
end

if Reply =='Y'
    Reply=[];
    while(isempty(Reply))
        Reply = input('Repertory name? : ', 's');
    end
    
    mkdir([folder Reply]);
    
%     file2cpy = {'vision.mat';...
%                 'VICON.mat';...
%                 'Sensors.mat';...
%                 'Robot_Control.mat';...
%                 'Param.mat';...
%                 'Gumstix_visual.mat';...
%                 'Eye_cotrol_data.mat';...
%                 };
%     
% %     for i=1:length(file2cpy)
% %         copyfile(['.\' file2cpy{i}],[folder Reply '\' file2cpy{i}]);
% %     end
    copyfile('*.mat',[folder Reply]);
end
