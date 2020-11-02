%Escolha uma das 3 imagens retirando-a de comentário e colocando/mantendo as outras como comentário

%I = 'coins.jpg';
%I = 'coins2.jpg';
%I = 'coins3.jpg';

J= imread(I);

IGray = rgb2gray(J);
type_noise = 'G';
noise_param = 0.1;

[IS, ISN, SNR, PreI, Histogram, Types] = main_image_recognition(I,IGray,type_noise,noise_param);


