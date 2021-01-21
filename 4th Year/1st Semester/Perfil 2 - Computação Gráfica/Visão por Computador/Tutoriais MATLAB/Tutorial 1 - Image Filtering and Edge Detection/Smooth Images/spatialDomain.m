function [smoothImage, stringParams] = spatialDomain(typeNoise, noiseParams, noiseImage, typeSmoothing, filterParams)

% Três Condições para verificar o Tipo de Filtro de Smoothing a usar

% 1. Filtro Gaussiano
% Função MATLAB imgaussflit
% imgaussfilt(I, sigma, 'FilterSize', filterSize, 'FilterDomain', filterDomain)
% O parâmetro sigma representa o Desvio Padrão da Distribuição Gaussiana
if(strcmp('Gaussian', typeSmoothing))

    filterSize = filterParams(1); % Buscar Parâmetro 1 do Array Parâmetros
    standardDeviation = filterParams(2); % Buscar Parâmetro 2 do Array Parâmetros
    
    smoothImage = imgaussfilt(noiseImage, standardDeviation, 'FilterSize', filterSize, 'FilterDomain', 'spatial');
    stringParams = [typeNoise, '_', num2str(noiseParams), '_', num2str(filterSize), '_' ,num2str(standardDeviation)];
    
end

% 2. Filtro Average
% Função MATLAB imfilter
% imfilter(I, h)
% O parâmetro h representa o Filtro Multidimensional sob a forma de Matriz
if(strcmp('Average', typeSmoothing))
    
    kernel = filterParams(1); % Buscar Parâmetro 1 do Array Parâmetros
    
    matrixKernel = ones(kernel, kernel)/(kernel*kernel);
    
    smoothImage = imfilter(noiseImage, matrixKernel);
    stringParams = [typeNoise, '_', num2str(noiseParams), '_', num2str(kernel)];
    
end
 
% 3. Filtro Median
% Função MATLAB medfilt2
% medfilt2(I)
% Apenas a Imagem a Filtrar como Input
if(strcmp('Median', typeSmoothing))
    
    smoothImage = medfilt2(noiseImage);
    stringParams = [typeNoise, '_', 'None'];
    
end

end

