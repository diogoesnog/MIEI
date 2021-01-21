function [smoothImage, stringParams] = frequencyDomain(typeNoise, noiseParams, noiseImage, typeSmoothing, filterParams, butterType)

% Duas Condições para verificar o Tipo de Filtro de Smoothing a usar

% 1. Filtro Gaussiano
% Função MATLAB imgaussflit
% imgaussfilt(I, sigma, 'FilterSize', filterSize, 'FilterDomain', filterDomain)
% O parâmetro sigma representa o Desvio Padrão da Distribuição Gaussiana
if(strcmp('Gaussian', typeSmoothing))
    
    filterSize = filterParams(1); % Buscar Parâmetro 1 do Array Parâmetros
    standardDeviation = filterParams(2); % Buscar Parâmetro 2 do Array Parâmetros
    
    smoothImage = imgaussfilt(noiseImage, standardDeviation, 'FilterSize', filterSize, 'FilterDomain', 'frequency');
    stringParams = [typeNoise, '_', num2str(noiseParams), '_', num2str(filterSize), '_' ,num2str(standardDeviation)];
        
end

% 2. Filtro ButterWorth
% Função MATLAB butter
% buttet(n, Wn, ftype)
% O parâmetro n representa a Ordem do Filtro
% O parâmetro Wn representa a Cutoff Frequency
% O parâmetro ftype representa o Filter Type
% O Filter Type é o butterType. Está em separado por ser ums String relativamente aos outros parâmetros
if(strcmp('ButterWorth', typeSmoothing))
    
    % "If Wn (Cutoff) is scalar, then butter designs a lowpass or highpass filter with cutoff frequency Wn"
    if(strcmp('Low', butterType) || strcmp('High', butterType))
        filterOrder = filterParams(1);
        cutoffFrequency = filterParams(2);
        
        stringParams = [typeNoise, '_', num2str(noiseParams), '_', num2str(filterOrder), '_', num2str(cutoffFrequency)];
    % "If Wn is the two-element vector [w1 w2], where w1 < w2, then butter
    % designs a bandpass or bandstop filter with lower cutoff frequency w1
    % and higher cutoff frequency w2."
    else
        filterOrder = filterParams(1);
        cutoffFrequency = filterParams(2:3);
        
        stringParams = [typeNoise, '_', num2str(noiseParams), '_', num2str(filterOrder), '_', num2str(cutoffFrequency)];
    end
    
    matrix = butter(filterOrder, cutoffFrequency, butterType);
    smoothImage = imfilter(noiseImage, matrix);
    
end

end
