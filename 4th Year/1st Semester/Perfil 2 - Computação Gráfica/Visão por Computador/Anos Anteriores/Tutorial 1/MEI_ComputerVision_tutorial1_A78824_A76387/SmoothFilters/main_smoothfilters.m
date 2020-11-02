function [N,S] = main_smoothfilters(F, type_noise, noise_param, filtering_domain, type_smoothing, filter_param, butterType)

%transforma a imagem numa escala de cinzentos
J= imread(F);
I = rgb2gray(J);
%I= 8*round(L/8) %mudar a grayscale

%adiciona o Noise à imagem de escala cinzenta
[N,filename] = addNoise(I, type_noise, noise_param);
imwrite(N,[F, '_', type_noise, '_', filename, '.png']);

%adiciona filtro de Spatial domain
if(strcmp('spatial', filtering_domain))
    [S,name] = smoothSpatial(N,type_smoothing,filter_param);
    imwrite(S,[F, '_', filtering_domain, '_', type_smoothing, '_', name, '.png']);
   
end

%adiciona filtro de Frequency domain
if(strcmp('frequency', filtering_domain))
    [S,name] = smoothFrequency(N, type_smoothing,filter_param,butterType);
    imwrite(S,[F, '_', filtering_domain, '_', type_smoothing, '_', name, '_', butterType '.png']);

end

%----------------DFT------------------------
%calcula o dft da imagem original
Original=dft(I);
figure(1);
imshow(Original,[]); title('DFT Original Image');


%calcula o dft da imagem com noise aplicado
NN=dft(N);
figure(2);
imshow(NN,[]); title('DFT Noised Image');

%calcula o dft da imagem com o filtro aplicado
SS=dft(S);
figure(3);
imshow(SS,[]); title('DFT Smoothed Image');

end