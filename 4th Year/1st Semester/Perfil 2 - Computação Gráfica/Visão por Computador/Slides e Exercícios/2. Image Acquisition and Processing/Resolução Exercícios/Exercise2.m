% 2. Qual é o Nível Médio de Cinza da Imagem? Subtrair esse valor ao valor
% total da Imagem. O que acontece?

% A subtração do Nível Médio permite normalizar a imagem em torno de zero, ficando
% consequentemente mais escura, ou seja, remove componentes mais brilhantes da Imagem. 

IMG_PATH = 'C:\Users\diogo\Documents\GitHub\MIEI\4th Year\1st Semester\Perfil 2 - Computação Gráfica\Visão por Computador\Slides e Exercícios\2. Image Acquisition and Processing\Resolução Exercícios\Images\castleGray.png';
IMG_GRAY = imread(IMG_PATH, 'png');

% Função que fornece o valor Médio de Cinza da Imagem
% Faz-se 2 vezes o mean por ser uma matriz
avg=uint8(mean(mean(IMG_GRAY)));

% Subtração do Valor Médio de Cinza ao Valor Total da Imagem
IMG_FT=IMG_GRAY-avg;
IMG_FT(IMG_FT<=0) = 0; % Evitar Valores Negativos

% Mostrar a Nova Imagem
imshow(IMG_FT);
