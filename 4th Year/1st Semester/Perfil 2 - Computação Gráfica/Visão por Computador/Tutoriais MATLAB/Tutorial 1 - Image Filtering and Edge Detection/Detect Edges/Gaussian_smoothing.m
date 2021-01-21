% Função que faz o Smooth da Nosiy Image por aplicação do Filtro Guassian
% do Domínio de Filtragem Spatial
% Função MATLAB imgaussfilt
% imgaussfilt(I, sigma, 'FilterSize', filterSize, 'FilterDomain', filterDomain)
% O parâmetro sigma representa o Desvio Padrão da Distribuição Guassiana
function [smoothImage, stringParams] = Gaussian_smoothing(name, noiseImage, filterSize, standardDeviation)

    smoothImage = imgaussfilt(noiseImage, standardDeviation, 'FilterSize', filterSize, 'FilterDomain', 'spatial');
    stringParams = name;

end

