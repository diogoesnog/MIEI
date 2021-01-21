% 1. Ler a Imagem Depth
depthImage = imread('Data/gait_depth_oneimage.png');
transformImage = imadjust(depthImage);

% 2. Fazer o Crop da Região de Interesse
% Target Size = [width, height]
% Este Crop é feito Centralizado - Facilita ao Recuperar as Coordenadas
targetSize = [300 150];
rectangleObject = centerCropWindow2d(size(transformImage), targetSize);
croppedImage = imcrop(transformImage, rectangleObject);
figure(1);
imshow(croppedImage);

% 3. Assumir a Imagem como Matriz e Transpor essa Matriz
% Dessa forma, conseguimos obter o Valor Máximo para Cada Linha da Imagem
% Dado que a função max calcula o maior por Coluna e não por Linha
transpostMatrix = croppedImage.';
maxForLineCroppedImage = max(transpostMatrix); % Valor Máximo de Cada Linha Imagem

% 4. Binarização da Imagem para Cada Linha
% Necessário Guardar a Imagem Cropped
% Função imread() abre a Imagem como Matrix
imwrite(croppedImage, 'croppedImage.png');
imageMatrix = imread('croppedImage.png');

matrixBinary = imageMatrix;
errorMargin = 1700;
[rows, columns] = size(matrixBinary);

% Binarização Consiste em Atribuir o Valor do Píxel Branco apenas aos 
% Pixéis que se encontrem abaixo do Valor Máximo da Linha associado a uma Margem de Erro
for row = 1 : rows
    for column = 1 : columns
        if matrixBinary(row, column) <= (maxForLineCroppedImage(1, row) - errorMargin)
            matrixBinary(row, column) = 255;
        else
            matrixBinary(row, column) = 0;
        end
    end
end

% Conversão da Matrix da Imagem com Binarização para uma Imagem
finalImage = mat2gray(matrixBinary);
figure(2);
imshow(finalImage);

% 5. Aplicar um Efeito de Erosão à Imagem
% Afina a Imagem e permite criar uma Separação entre as 2 Pernas
% Separação necessária para selecionar cada Perna Individualmente
se = strel('line', 20, 50);
erodeImage = imerode(finalImage, se);

figure(3);
imshow(erodeImage);

% 6. Obter Coordenadas X e Y dos Pixeis que estão a 1 da Imagem Edges
[Y, X] = ind2sub(size(erodeImage), find(ismember(erodeImage, 1)));

% 8. Separar as Pernas Individualmente
% Uso da função bwselect() juntamente com as Coordenadas Anteriores

% Pode-se usar tanto o Y como o X, dado que terão ambos o mesmo número de Rows
lengthCoordImage = height(Y);

% 8.1. Perna + Pé Esquerdo
% Usa-se o Valor 100 que será usado também como Margem para o outro Lado da
% Imagem
XLeftToeFoot = X(100);
YLeftToeFoot = Y(100);

c1 = XLeftToeFoot;
r1 = YLeftToeFoot;

% Função bwselect() retorna Conjunto Pixéis 1 Conectados perante as
% Coordenadas Fornecidas
leftToeFoot = bwselect(erodeImage, c1, r1, 4);

[rows, columns] = size(leftToeFoot);
for row = 1 : rows
    for column = 1 : columns
        if row < 105 && leftToeFoot(row, column) == 1
           leftToeFoot(row, column) = 0;
        end
    end
end

figure(4);
imshow(leftToeFoot);

[Y1, X1] = ind2sub(size(leftToeFoot), find(ismember(leftToeFoot, 1)));

% Obter as Coordenadas dos Pontos que Formam Retângulo Volta Pé Esquerdo
% São dadas 5 Coordenadas de Cada Eixo
% Dessa forma conseguem-se desenhar as 4 linhas
% Exemplo Desenho Linhas Incluído no Relatório
[rectxL, rectyL] = coordRectangle(X1, Y1);

line([rectxL(1) rectxL(2)], [rectyL(1) rectyL(2)]);
line([rectxL(2) rectxL(3)], [rectyL(2) rectyL(3)]);
line([rectxL(3) rectxL(4)], [rectyL(3) rectyL(4)]);
line([rectxL(4) rectxL(5)], [rectyL(4) rectyL(5)]);

% 8.2. Perna + Pé Direito
% Usa-se o Valor mais Final, dado que se sabe que corresponde ao Lado Direito da Imagem
% Margem Associada
XRightToeFoot = X(lengthCoordImage - 45);
YRightToeFoot = Y(lengthCoordImage - 45);

c2 = XRightToeFoot;
r2 = YRightToeFoot;

% Função bwselect() retorna Conjunto Pixéis 1 Conectados perante as
% Coordenadas Fornecidas
rightToeFoot = bwselect(erodeImage, c2, r2, 4);

[rows, columns] = size(rightToeFoot);
for row = 1 : rows
    for column = 1 : columns
        if row < 45 && rightToeFoot(row, column) == 1
           rightToeFoot(row, column) = 0;
        end
    end
end

figure(5);
imshow(rightToeFoot);

[Y2, X2] = ind2sub(size(rightToeFoot), find(ismember(rightToeFoot, 1)));

% Obter as Coordenadas dos Pontos que Formam Retângulo Volta Pé Direito
% São dadas 5 Coordenadas de Cada Eixo
% Dessa forma conseguem-se desenhar as 4 linhas
% Exemplo Desenho Linhas Incluído no Relatório
[rectxR, rectyR] = coordRectangle(X2,Y2);

line([rectxR(1) rectxR(2)], [rectyR(1) rectyR(2)]);
line([rectxR(2) rectxR(3)], [rectyR(2) rectyR(3)]);
line([rectxR(3) rectxR(4)], [rectyR(3) rectyR(4)]);
line([rectxR(4) rectxR(5)], [rectyR(4) rectyR(5)]);

% 9. Desenhar Linhas dos Pés na Imagem Original
% Carregar a Imagem para depois desenhar Linhas sobre a mesma
imageRGB = imread('Data/gait_RGB_oneimage.png');
imgCropped = imread('croppedImage.png');

% Tamanho Imagem Original RGB e da Cropped
[widthImageRGB, heightImageRGB, z1] = size(imageRGB);
[widthImageCropped, heightImageCropped, z2] = size(imgCropped);

differenceWidth = (widthImageRGB - widthImageCropped)/2;
differenceHeight = (heightImageRGB - heightImageCropped)/2;

figure(6);
imshow(imageRGB);

% Vamos assumir a Ponta do Pé e Tornozelo como estando ao meio da Linha
% Cima e de Baixo
xLeftTorn = (rectxL(1) + ((rectxL(2)- rectxL(1))/2)) + differenceHeight;
yLeftTorn = rectyL(2) + differenceWidth;
xLeftPonta = (rectxL(4) + ((rectxL(3)- rectxL(4))/2)) + differenceHeight;
yLeftPonta = rectyL(3) + differenceWidth;

line([xLeftTorn  xLeftPonta], [yLeftTorn yLeftPonta], 'Color', 'red', 'LineWidth', 2, 'Marker', 'v');

xRightTorn = (rectxR(1) + ((rectxR(4)- rectxR(1))/2)) + differenceHeight;
yRightTorn = rectyR(4) + differenceWidth;
xRightPonta = (rectxR(3) + ((rectxR(2)- rectxR(3))/2)) + differenceHeight;
yRightPonta = rectyR(3) + differenceWidth;

line([xRightTorn  xRightPonta], [yRightTorn yRightPonta], 'Color', 'red', 'LineWidth', 2, 'Marker', 'v');

% Desenhar os Valores de Ground Truth
leftToe = [256 302];
leftFoot = [266 350];
rightToe = [338 232];
rightFoot = [324 269];

line([640-leftFoot(1)  640-leftToe(1)], [480-leftFoot(2) 480-leftToe(2)], 'Color', 'magenta', 'LineWidth', 2, 'Marker', 'v');
line([640-rightFoot(1)  640-rightToe(1)], [480-rightFoot(2) 480-rightToe(2)], 'Color', 'magenta', 'LineWidth', 2, 'Marker', 'v');

% Guardar Imagem Com os Pontos Ground Truth e Nossos Resultados
windowFrame = getframe(gca);
imwrite(windowFrame.cdata, 'imageWithLines.png');

% 10. Escrever Valores para Ficheiro Excel
leftTorn = {xLeftTorn; yLeftTorn;};
leftPonta = {xLeftPonta; yLeftPonta;};

rightTorn = {xRightTorn; yRightTorn;};
rightPonta = {xRightPonta; yRightPonta;};

data = table(leftTorn, leftPonta, rightTorn, rightPonta);
writetable(data, 'ourValues.xlsx');