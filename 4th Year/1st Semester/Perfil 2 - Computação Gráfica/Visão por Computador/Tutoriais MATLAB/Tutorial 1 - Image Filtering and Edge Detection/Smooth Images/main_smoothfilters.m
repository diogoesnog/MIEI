% Função que define o Input e o Output da Função em si
% Recebe a Noise e a Smooth Image
function [noiseImage, smoothImage] = main_smoothfilters(image, typeNoise, noiseParams, filteringDomain, typeSmoothing, filterParams, butterType)

% Transformar a Imagem para Escala de Cinzas
imageOriginal = imread(image);
imageGrey = rgb2gray(imageOriginal);

% 1. Adicionar o Noise na Imagem Escala Cinzas
[noiseImage, stringParams] = addNoiseImage(imageGrey, typeNoise, noiseParams);
% Para dar o output do nome da Imagem consoante pedido no Enunciado
[pathImage, nameImage, extensionImage] = fileparts(image);
imwrite(noiseImage, ['Results Images/', nameImage, '_', typeNoise, '_', stringParams, '.png']);

% 2. Adicionar o Smooth na Imagem
% A verificação do Type of Smoothing é feita no Script criado para cada um dos domínios 

if(strcmp('Spatial', filteringDomain))
    
    [smoothImage, stringParams] = spatialDomain(typeNoise, noiseParams, noiseImage, typeSmoothing, filterParams);
    [pathImage, nameImage, extensionImage] = fileparts(image);
    newName = [nameImage, '_', filteringDomain, '_', typeSmoothing, '_', stringParams, '.png'];
    imwrite(smoothImage, ['Results Images/', newName]);
    
end

if(strcmp('Frequency', filteringDomain))
    
    [smoothImage, stringParams] = frequencyDomain(typeNoise, noiseParams, noiseImage, typeSmoothing, filterParams, butterType);
    [pathImage, nameImage, extensionImage] = fileparts(image);
    newName = [nameImage, '_', filteringDomain, '_', typeSmoothing, '_', stringParams, '_', butterType, '.png'];
    imwrite(smoothImage, ['Results Images/', newName]);
    
end

% 3. Calcular o Discrete Fast Fourier Transform (DFT)
% Apenas se aplicam aos Filtros

if(strcmp('Spatial', filteringDomain) || strcmp('Frequency', filteringDomain))

    % 3.1. DFT Original Image
    originalImage = fft2(imageGrey);
    shiftImage = fftshift(originalImage);
    dftOriginalImage = log(1 + abs(shiftImage));

    dft1  = figure(1);
    imshow(dftOriginalImage, []);
    title('DFT Original Image');
    
    saveas(dft1, ['DFT Images/', 'Original_', nameImage, '.png']);
    
    % 3.2. DFT Noisy Image
    noisyImage = fft2(noiseImage);
    shiftImage = fftshift(noisyImage);
    dftNoisyImage = log(1 + abs(shiftImage));

    dft2 = figure(2);
    imshow(dftNoisyImage, []);
    title('DFT Noisy Image');

    saveas(dft2, ['DFT Images/', 'Noisy_', nameImage, '.png']);

    % 3.3. DFT Filtered Image
    filteredImage = fft2(smoothImage);
    shiftImage = fftshift(filteredImage);
    dftFilteredImage = log(1 + abs(shiftImage));

    dft3 = figure(3);
    imshow(dftFilteredImage, []);
    title('DFT Filtered Image');
    
    saveas(dft3, ['DFT Images/', newName]);
    
end