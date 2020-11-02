function [N,filename] = addNoise(I,type_noise, noise_param)

%adiciona tipo de noise Salt&Pepper
if(strcmp('SP',type_noise))  
    N = imnoise(I,'salt & pepper',noise_param);
    filename=num2str(noise_param);
end
%adiciona tipo de noise Gaussian
if(strcmp('G',type_noise))
    N= imnoise(I,'gaussian',noise_param);
    filename=num2str(noise_param);
end 

end

