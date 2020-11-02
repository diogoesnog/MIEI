function [N,filename] = AddNoiseG(imagem,noise_param)
filename=imagem;
J= imread(imagem);
I = rgb2gray(J);

N=imnoise(I,'G',noise_param)
 
end

