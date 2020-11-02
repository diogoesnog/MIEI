function DFT = dft(imagem)

%obter o Fourier Transform da imagem
F = fft2(imagem);

%obter o centro do espectro
Fsh= fftshift(F);
%figure(4);
%imshow(abs(Fsh),[]);

%aplicar o log transform
DFT=log(1+abs(Fsh));
%figure(5);
%imshow(DFT,[]);

end

