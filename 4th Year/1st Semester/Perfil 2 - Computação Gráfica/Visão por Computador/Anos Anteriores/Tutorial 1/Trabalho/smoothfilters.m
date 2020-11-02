%INPUTS: 11
%IMAGEM
%TIPO DE NOISE(G/SP)
%VARIANCIA([ int int ])
%OCORRENCIA(float)
%FILTERING DOMAIN(spatial domain/frequency domain)
%TIPO DE SMOOTHING(gaussian/average/median/butterworth)
%KERNEL
%DESVIO 
%ORDER
%CUTOFF
%BUTTERTYPE - high, low, bandpass, stop

%-------------------------------------------------------------------------%
B= imread('baboon.png');
B1 = rgb2gray(B);
%figure(1)
%imshow(B1);

C= imread('castle.png');
C1 = rgb2gray(C);
%figure(2)
%imshow(C1);

L= imread('lena.jpg');
L1 = rgb2gray(L);
figure(1)
imshow(L1);


%-------------------------------------------------------------------------%
%salt & pepper
[N,S] = main_smoothfilters(B1,'SP',0, 0.02,'spatial domain','gaussian',0);



%gaussian
%[N,S] = main_smoothfilters(L1,'G',200, 0.9,'spatial domain','gaussian',0);
%figure(3)
%imshow(N)


%----------------------SPATIAL DOMAIN-------------------------------------%
%smoothing gaussian -> spatial domain
%[N,S] = main_smoothfilters(L1,'SP',0, 0.02,'spatial domain','gaussian',5,2);


%smoothing average -> spatial domain
%[N1,S1] = main_smoothfilters(L1,'SP',0, 0.02,'spatial domain','average',5);

%smoothing median -> spatial domain
%[N,S] = main_smoothfilters(L1,'SP',0, 0.02,'spatial domain','median',1);
%[N,S] = main_smoothfilters(L1,'G',[3 3], 0.5,'spatial domain','median',2);


%----------------------FREQUENCY DOMAIN-----------------------------------%
%smoothing gaussian -> frequency domain
%[N,S]= main_smoothfilters(L1,'SP',0, 0.02,'frequency domain','gaussian',5,2);

%smoothing butterworth -> frequency domain
%[N1,S1] = main_smoothfilters(L1,'SP',0, 0.02,'frequency domain','butterworth',0,0,3,20/50,'low');
%[N2,S2] = main_smoothfilters(L1,'SP',0, 0.02,'frequency domain','butterworth',0,0,3,20/50,'high');
%[N3,S3] = main_smoothfilters(L1,'SP',0, 0.02,'frequency domain','butterworth',0,0,3,[0.2 0.6],'stop');
%[N4,S4] = main_smoothfilters(L1,'SP',0, 0.02,'frequency domain','butterworth',0,0,3,[0.2 0.6],'bandpass');
%-------------------------------------------------------------------------%
figure(3)
imshow(S4);
saveas(gcf,Lena_SP_densidade.png)

