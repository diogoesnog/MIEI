
%-------------------------NOISE-------------------------------------%
%Salt & Pepper
% Inputs: Image, 'SP', density
%N = main_smoothfilters('baboon.png','SP',0.05, []);


%Gaussian
% Inputs: Image, 'G', 
%N = main_smoothfilters('lena.jpg','G',0.01,[]);



%----------------------SPATIAL DOMAIN-------------------------------------%
%Aplicar filtros de spatial domain numa imagem com noise SP

%GAUSSIAN
%I,type_noise,noise_param,'spatial','gaussian',[filter_size,desvio]

%[N,S] = main_smoothfilters('baboon.png','SP',0.05,'spatial','gaussian',[35,10]);


%AVERAGE 
%I,type_noise,noise_param,'spatial','average',kernel_size

%[N,S] = main_smoothfilters('baboon.png','SP',0.05,'spatial','average',[20]);


%MEDIAN
%I,type_noise,noise_param,'spatial','median', []

%[N,S] = main_smoothfilters('baboon.png','SP',0.05,'spatial','median',[]);



%-------------------
%Aplicar filtros de spatial domain numa imagem com noise G

%GAUSSIAN
%I,type_noise,noise_param,'spatial','gaussian',[kernel_size,desvio]

[N,S] = main_smoothfilters('baboon.png','G',0.05,'spatial','gaussian',[35,20]);


%AVERAGE
%I,type_noise,noise_param,'spatial','average',kernel_size

%[N,S] = main_smoothfilters('baboon.png','G',0.05,'spatial','average',[20]);


%MEDIAN
%I,type_noise,noise_param,'spatial','median', []

%[N,S] = main_smoothfilters('baboon.png','G',0.05,'spatial','median',[]);

%----------------------FREQUENCY DOMAIN-----------------------------------%
%GAUSSIAN

%[N,S]= main_smoothfilters(L1,'SP',0.02,'frequency','gaussian',[5,2],[]);

%BUTTERWORTH

%[N,S] = main_smoothfilters('castle.png','SP',0.02,'frequency','butterworth',[3,20/50],'low');
%[N2,S2] = main_smoothfilters('castle.png','SP',0.02,'frequency','butterworth',[3,20/50],'high');
%[N3,S3] = main_smoothfilters('castle.png','SP',0.02,'frequency','butterworth',[3,[0.2 0.6]],'stop');
%[N4,S4] = main_smoothfilters('castle.png','SP',0.02,'frequency','butterworth',[3,[0.2 0.6]],'bandpass');
%-------------------------------------------------------------------------%

%INPUTS: 7 (incluindo 1 array)
%IMAGEM
%TIPO DE NOISE('G'/'SP')
%NOISE_PARAM  
%FILTERING DOMAIN('spatial'/'frequency')
%TIPO DE SMOOTHING(gaussian/average/median/butterworth)
%FILTER_PARAM(array de parametros)
%     -spatial domain:
%           * gaussian: fsize(int) e desvio
%           * average:kernel(int)
%     -frequency domain:
%           * gaussian: kernel(int) e desvio
%           * butterworth: order e cutoff
%BUTTERTYPE - high, low, bandpass, stop


