% Função que define o Input e o Output da Função em si
% Recebe a Guassian Noise Image e os Parâmetros do Filter Size e Sigma a.k.a. Standard Deviation
function [imageBeforeNM, imageAfterNM, imageAfterHT] = main_CannyDetector(nameImage, guassianNoiseImage, filterSize, standardDeviation)

    % A Imagem passa pelo processo de Adição de Ruído através do Guassian Noise
    % Depois aplica-se o Guassian Smooth
    [guassianSmoothImage, originalNameImage] = Gaussian_smoothing(nameImage, guassianNoiseImage, filterSize, standardDeviation);
    
    % 1. Image Before Nonmax Suppression
    
    % Essa Imagem Smooth será a Imagem Antes do Nonmax Suppression
    % Guarda-se essa Imagem
    imageBeforeNM = guassianSmoothImage;
    [pathImage, nameImage, extensionImage] = fileparts(originalNameImage);
    imwrite(imageBeforeNM, ['Results Images/', nameImage, '_edge_canny_', num2str(filterSize), '_', num2str(standardDeviation), '.png']);

    % 2. Image After Nonmax Suppression
    
    % Calcular a Magnitude e Direção do Gradiente
    [gradientMagn, gradientDirect] = gradient(guassianSmoothImage);

    % Calcular o Nonmax Suppression
    % Será necessário Normalizar as Direções
    % Guarda-se essa Imagem
    directions = arrayfun(@(x)normalize_directions(x), gradientDirect);
    imageAfterNM = nonmax(gradientMagn,directions);
    [pathImage, nameImage, extensionImage] = fileparts(originalNameImage);
    imwrite(imageAfterNM, ['Results Images/', nameImage, '_edge_canny_nonmax_',num2str(filterSize), '_', num2str(standardDeviation), '.png']);
    
    % 3. Imagem After Hysteresis Thresholding
    
    % Calcular o Double Threshold para termos as Strong Edges e Weak Edges
    % Com essas Edges, calcula-se o resultado do Hysteresis Thresholding
    % Guarda-se essa Imagem
    [strongEdges, weakEdges] = double_threshold(imageAfterNM, 0.2, 0.1);
    imageAfterHT = hysteresis_thresholding(strongEdges, weakEdges);
    [pathImage, nameImage, extensionImage] = fileparts(originalNameImage);
    imwrite(imageAfterHT, ['Results Images/', nameImage, '_edge_canny_hysteresis_',num2str(filterSize), '_', num2str(standardDeviation), '.png']);
    
end

