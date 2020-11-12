% Histograma Sem Equalização
IMG_PATH = 'C:\Users\diogo\Documents\GitHub\MIEI\4th Year\1st Semester\Perfil 2 - Computação Gráfica\Visão por Computador\Slides e Exercícios\2. Image Acquisition and Processing\Resolução Exercícios\Images\castleGray.png';
IMG_GRAY = imread(IMG_PATH, 'png');
imshow(IMG_GRAY);
figure, imhist(IMG_GRAY); % Função do MATLAB que faz o Histograma
figure, imhist(IMG_GRAY);
ylim('auto');

% Histograma Com Equalização
NEW_IMG = histeq(IMG_GRAY, 256);
figure, imshow(NEW_IMG);
figure, imhist(NEW_IMG);
ylim('auto');