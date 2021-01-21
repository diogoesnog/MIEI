% Este Script chamará a Função main_smoothfilters para executar os Algoritmos em si

% 1. Noisy Images

% 1.1. Noise Salt & Pepper
% Variação do valor da densidade (d)
noiseSP1 = main_smoothfilters('castle.png', 'SaltPepper', 0.05, []);
noiseSP2 = main_smoothfilters('castle.png', 'SaltPepper', 0.1, []);
noiseSP3 = main_smoothfilters('castle.png', 'SaltPepper', 0.5, []);

% 1.2. Noise Gaussian
% Variação do valor da Média Ruído Gaussiano (m)
noiseG1 = main_smoothfilters('castle.png', 'Gaussian', 0.05, []);
noiseG2 = main_smoothfilters('castle.png', 'Gaussian', 0.1, []);
noiseG3 = main_smoothfilters('castle.png', 'Gaussian', 0.5, []);

% Variação do valor da Variância Ruído Gaussiano (var_gauss)
% Para o valor da Média Ruído Guassiano (m) = 0.1
noiseG21 = main_smoothfilters('castle.png', 'Gaussian', [0.1, 0.1], []);
noiseG22 = main_smoothfilters('castle.png', 'Gaussian', [0.1, 0.5], []);

% 2. Smoothed Images

% 2.1. Domínio Filtragem Spatial

% 2.1.1. Noise Salt & Pepper
% Valor da Densidade (d) = 0.1

% Filtro Smoothing Average
smoothedImageSpatialNSPA1 = main_smoothfilters('castle.png', 'SaltPepper', 0.1, 'Spatial', 'Average', 5, []);
smoothedImageSpatialNSPA2 = main_smoothfilters('castle.png', 'SaltPepper', 0.1, 'Spatial', 'Average', 10, []);
smoothedImageSpatialNSPA3 = main_smoothfilters('castle.png', 'SaltPepper', 0.1, 'Spatial', 'Average', 20, []);

% Filtro Smoothing Gaussian
% O valor do Filter Size tem de ser um ODD - Inteiro Não Divisível por 2
% O Sigma tomará o valor de 10

smoothedImageSpatialNSPG1 = main_smoothfilters('castle.png', 'SaltPepper', 0.1, 'Spatial', 'Gaussian', [3, 10], []);
smoothedImageSpatialNSPG2 = main_smoothfilters('castle.png', 'SaltPepper', 0.1, 'Spatial', 'Gaussian', [7, 10], []);
smoothedImageSpatialNSPG3 = main_smoothfilters('castle.png', 'SaltPepper', 0.1, 'Spatial', 'Gaussian', [21, 10], []);

% Filtro Smoothing Median
smoothedImageSpatialNSPM1 = main_smoothfilters('castle.png', 'SaltPepper', 0.1, 'Spatial', 'Median', []);

% 2.1.2. Noise Gaussian
% Valor da Densidade (d) = 0.1
% 
% Filtro Smoothing Average
smoothedImageSpatialNGA1 = main_smoothfilters('castle.png', 'Gaussian', 0.1, 'Spatial', 'Average', 5, []);
smoothedImageSpatialNGA2 = main_smoothfilters('castle.png', 'Gaussian', 0.1, 'Spatial', 'Average', 10, []);
smoothedImageSpatialNGA3 = main_smoothfilters('castle.png', 'Gaussian', 0.1, 'Spatial', 'Average', 20, []);

% Filtro Smoothing Gaussian
% O valor do Filter Size tem de ser um ODD - Inteiro Não Divisível por 2
% O Sigma tomará o valor de 10

smoothedImageSpatialNGG1 = main_smoothfilters('castle.png', 'Gaussian', 0.1, 'Spatial', 'Gaussian', [3, 10], []);
smoothedImageSpatialNGG2 = main_smoothfilters('castle.png', 'Gaussian', 0.1, 'Spatial', 'Gaussian', [7, 10], []);
smoothedImageSpatialNGG3 = main_smoothfilters('castle.png', 'Gaussian', 0.1, 'Spatial', 'Gaussian', [21, 10], []);
 
% Filtro Smoothing Median
smoothedImageSpatialNGM1 = main_smoothfilters('castle.png', 'Gaussian', 0.1, 'Spatial', 'Median', []);

% 2.2. Domínio Filtragem Frequency

% 2.1.1. Noise Salt & Pepper
% Valor da Densidade (d) = 0.1

% Filtro Smoothing Gaussian
smoothedImageFrequencyNSPG1 = main_smoothfilters('castle.png', 'SaltPepper', 0.1, 'Frequency', 'Gaussian', [3, 10], []);
smoothedImageFrequencyNSPG2 = main_smoothfilters('castle.png', 'SaltPepper', 0.1, 'Frequency', 'Gaussian', [7, 10], []);
smoothedImageFrequencyNSPG3 = main_smoothfilters('castle.png', 'SaltPepper', 0.1, 'Frequency', 'Gaussian', [21, 10], []);

% Filtro Smoothing Butterworth

% Variação Filter Order
smoothedImageFrequencyNSPB1 = main_smoothfilters('castle.png', 'SaltPepper', 0.1, 'Frequency', 'ButterWorth', [5, 0.45], 'Low');
smoothedImageFrequencyNSPB2 = main_smoothfilters('castle.png', 'SaltPepper', 0.1, 'Frequency', 'ButterWorth', [10, 0.45], 'Low');
smoothedImageFrequencyNSPB3 = main_smoothfilters('castle.png', 'SaltPepper', 0.1, 'Frequency', 'ButterWorth', [20, 0.45], 'Low');

% Variação do Cutoff
smoothedImageFrequencyNSPB4 = main_smoothfilters('castle.png', 'SaltPepper', 0.1, 'Frequency', 'ButterWorth', [5, 0.05], 'Low');
smoothedImageFrequencyNSPB5 = main_smoothfilters('castle.png', 'SaltPepper', 0.1, 'Frequency', 'ButterWorth', [5, 0.3], 'Low');
smoothedImageFrequencyNSPB6 = main_smoothfilters('castle.png', 'SaltPepper', 0.1, 'Frequency', 'ButterWorth', [5, 0.5], 'Low');

% 2.1.2. Noise Gaussian
% Valor da Densidade (d) = 0.1

%Filtro Smoothing Gaussian
smoothedImageFrequencyNGG1 = main_smoothfilters('castle.png', 'Gaussian', 0.1, 'Frequency', 'Gaussian', [3, 10], []);
smoothedImageFrequencyNGG2 = main_smoothfilters('castle.png', 'Gaussian', 0.1, 'Frequency', 'Gaussian', [7, 10], []);
smoothedImageFrequencyNGG3 = main_smoothfilters('castle.png', 'Gaussian', 0.1, 'Frequency', 'Gaussian', [21, 10], []);

% Filtro Smoothing Butterworth
    
% Variação Filter Order
smoothedImageFrequencyNGB1 = main_smoothfilters('castle.png', 'Gaussian', 0.1, 'Frequency', 'ButterWorth', [5, 0.45], 'Low');
smoothedImageFrequencyNGB2 = main_smoothfilters('castle.png', 'Gaussian', 0.1, 'Frequency', 'ButterWorth', [10, 0.45], 'Low');
smoothedImageFrequencyNGB3 = main_smoothfilters('castle.png', 'Gaussian', 0.1, 'Frequency', 'ButterWorth', [20, 0.45], 'Low');

% Variação do Cutoff
smoothedImageFrequencyNGB4 = main_smoothfilters('castle.png', 'Gaussian', 0.1, 'Frequency', 'ButterWorth', [5, 0.05], 'Low');
smoothedImageFrequencyNGB5 = main_smoothfilters('castle.png', 'Gaussian', 0.1, 'Frequency', 'ButterWorth', [5, 0.3], 'Low');
smoothedImageFrequencyNGB6 = main_smoothfilters('castle.png', 'Gaussian', 0.1, 'Frequency', 'ButterWorth', [5, 0.5], 'Low');