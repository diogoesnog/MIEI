% Este Script serve para fazer os Testes e obter os Resultados relativos à
% função pré-definida do MATLAB edge
% A função está pronta para receber diferentes tipos de métodos e aplicar
% aquele que recebe como input

function [imageMethod] = MatlabTests(nameImage, typeMethod, filterSize, sigma)

% Converter Imagem Tons Cinza
nameOriginalImage = nameImage;
rgbImage = imread(nameOriginalImage);
grayImage = im2gray(rgbImage);

if ( strcmp(typeMethod, 'Canny') || strcmp(typeMethod, 'log'))
    
    imageMethod = edge(grayImage, typeMethod, filterSize, sigma);
    [pathImage, nameImage, extensionImage] = fileparts(nameOriginalImage);
    imwrite(imageMethod, ['MATLAB Function Results Images/', nameImage, '_Matlabedge_', typeMethod , '_', num2str(filterSize), '_', num2str(sigma), '.png']);
    
else
    
    imageMethod = edge(grayImage, typeMethod);
    [pathImage, nameImage, extensionImage] = fileparts(nameOriginalImage);
    imwrite(imageMethod, ['MATLAB Function Results Images/', nameImage, '_Matlabedge_', typeMethod , '_', num2str(filterSize), '_', num2str(sigma), '.png']);
    
end

end