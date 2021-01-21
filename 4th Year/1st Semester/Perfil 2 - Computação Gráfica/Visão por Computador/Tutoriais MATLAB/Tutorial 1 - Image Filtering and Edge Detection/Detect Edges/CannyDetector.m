
% 1. Nossas Funçõe/Algoritmos
% Diferentes testes para Diferentes Valores Filter Size.

nameFirstImage = 'baboon.png';
nameSecondImage = 'lena.jpg';
nameThirdImage = 'flower.jpg';

% 1.1. Primeira Imagem (Baboon)
% Adicionar Gaussian Noise à Imagem Preto e Branco.
% Densidade (d) no valor de 0.01.
originalImage = imread(nameFirstImage);
grayImage = rgb2gray(originalImage);
noiseImage = imnoise(grayImage, 'Gaussian', 0.01);

[imageBeforeNM1, imageAfterNM1, imageAfterHT1] = main_CannyDetector(nameFirstImage, noiseImage, 3, 2);
[imageBeforeNM2, imageAfterNM2, imageAfterHT2] = main_CannyDetector(nameFirstImage, noiseImage, 5, 2);
[imageBeforeNM3, imageAfterNM3, imageAfterHT3] = main_CannyDetector(nameFirstImage, noiseImage, 11, 2);

% 1.2. Segunda Imagem (Lena)
% Adicionar Gaussian Noise à Imagem Preto e Branco.
% Densidade (d) no valor de 0.01.
originalImage = imread(nameSecondImage);
grayImage = rgb2gray(originalImage);
noiseImage = imnoise(grayImage, 'Gaussian', 0.01);

[imageBeforeNM4, imageAfterNM4, imageAfterHT4] = main_CannyDetector(nameSecondImage, noiseImage, 3, 2);
[imageBeforeNM5, imageAfterNM5, imageAfterHT5] = main_CannyDetector(nameSecondImage, noiseImage, 5, 2);
[imageBeforeNM6, imageAfterNM6, imageAfterHT6] = main_CannyDetector(nameSecondImage, noiseImage, 11, 2);

% 1.3. Terceira Imagem
% Imagem Original já a Preto e Branco.
% Adicionar Gaussian Noise à Imagem Preto e Branco.
% Densidade (d) no valor de 0.01.
grayImage = imread(nameThirdImage);
noiseImage = imnoise(grayImage, 'Gaussian', 0.01);

[imageBeforeNM7, imageAfterNM7, imageAfterHT7] = main_CannyDetector(nameThirdImage, noiseImage, 3, 2);
[imageBeforeNM8, imageAfterNM8, imageAfterHT8] = main_CannyDetector(nameThirdImage, noiseImage, 5, 2);
[imageBeforeNM9, imageAfterNM9, imageAfterHT9] = main_CannyDetector(nameThirdImage, noiseImage, 11, 2);

% 2. MATLAB's Edge Function

% 2.1. Canny Edge Detection Method
% Aplica-se a Variance e Threshold.
% Vamos variar os dois.
% FilterSize não se aplica.
imageCanny1 = MatlabTests(nameFirstImage, 'Canny', 0, 2);
imageCanny2 = MatlabTests(nameFirstImage, 'Canny', 0.5, 2);
imageCanny3 = MatlabTests(nameFirstImage, 'Canny', 0.5, 6);

imageCanny4 = MatlabTests(nameSecondImage, 'Canny', 0, 2);
imageCanny5 = MatlabTests(nameSecondImage, 'Canny', 0.5, 2);
imageCanny6 = MatlabTests(nameSecondImage, 'Canny', 0.5, 6);

imageCanny7 = MatlabTests(nameThirdImage, 'Canny', 0, 2);
imageCanny8 = MatlabTests(nameThirdImage, 'Canny', 0.5, 2);
imageCanny9 = MatlabTests(nameThirdImage, 'Canny', 0.5, 6);

% 2.2. Sobel Edge Detection Method
% Não se aplicam a Variance nem o FilterSize.
imageSobel10 = MatlabTests(nameFirstImage, 'Sobel', 0, 0);
imageSobel11 = MatlabTests(nameSecondImage, 'Sobel', 0, 0);
imageSobel12 = MatlabTests(nameThirdImage, 'Sobel', 0, 0);

% 2.3. Prewitt Edge Detection Method
% Não se aplicam a Variance nem o FilterSize.
imagePrewitt13 = MatlabTests(nameFirstImage, 'Prewitt', 0, 0);
imagePrewitt14 = MatlabTests(nameSecondImage, 'Prewitt', 0, 0);
imagePrewitt15 = MatlabTests(nameThirdImage, 'Prewitt', 0, 0);

% 2.4. Laplacian Edge Detection Method
% Aplica-se a Variance e Threshold.
% Vamos variar os dois.
% FilterSize não se aplica.
imageLaplacian16 = MatlabTests(nameFirstImage, 'log', 0, 2);
imageLaplacian17 = MatlabTests(nameFirstImage, 'log', 0.5, 0.5);

imageLaplacian19 = MatlabTests(nameSecondImage, 'log', 0, 2);
imageLaplacian20 = MatlabTests(nameSecondImage, 'log', 0.5, 0.5);

imageLaplacian22 = MatlabTests(nameThirdImage, 'log', 0, 2);
imageLaplacian23 = MatlabTests(nameThirdImage, 'log', 0.5, 0.5);

