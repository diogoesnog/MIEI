% 1. Escrever um Programa que lê a Imagem castle.png e que guarde o seu
% Nível de Cinza dentro de um array.

% Criar a Variável para alocar o PATH da Imagem a tratar
IMG_PATH = 'C:\Users\diogo\Documents\GitHub\MIEI\4th Year\1st Semester\Perfil 2 - Computação Gráfica\Visão por Computador\Slides e Exercícios\2. Image Acquisition and Processing\Resolução Exercícios\Images\castle.png';
% Ler a Imagem consoante o seu formato
% Terá os 3 Canais de Cor
IMG_COLOR = imread(IMG_PATH, 'png');
% Colocar a Imagem em Modo Gray
IMG_GRAY = rgb2gray(IMG_COLOR);
% Visualizar a Imagem
figure(1), imshow(IMG_GRAY);
% Guardar a Imagem em modo Gray
imwrite(IMG_GRAY,'C:\Users\diogo\Documents\GitHub\MIEI\4th Year\1st Semester\Perfil 2 - Computação Gráfica\Visão por Computador\Slides e Exercícios\2. Image Acquisition and Processing\Resolução Exercícios\Images\castleGray.png', 'png'); 