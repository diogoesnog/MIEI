function [noiseImage, stringParams] = addNoiseImage(image, typeNoise, noiseParams)

% Criar duas condições que verifiquem o tipo de Noise a aplicar

% 1. Noise Salt & Pepper
% Função MATLAB imnoise
% imnoise(I, 'salt & pepper', d)
% O parâmetro d representa a Densidade do Noise
% Densidade Padrão = 0.05       
if(strcmp('SaltPepper', typeNoise))
    noiseImage = imnoise(image, 'salt & pepper', noiseParams);
    stringParams = num2str(noiseParams); % Converter os Parâmetros para String para usar no Nome

end

% 2. Noise Guassian
% Função MATLAB imnoise
% imnoise(I, 'gaussian', m, var_guass)
% O parâmetro (m) representa a Média do Ruído Guasiano
% Média do Ruído Guasiano Padrão = 0
% O parâmetro (var_guass) representa a Variância do Ruído Guassiano
if(strcmp('Gaussian', typeNoise))
    
    if(length(noiseParams) == 2)
    
        guassNoise = noiseParams(1);
        varianceGuassNoise = noiseParams(2); 

        noiseImage = imnoise(image, 'gaussian', guassNoise, varianceGuassNoise);
        stringParams = [num2str(guassNoise) '_' num2str(varianceGuassNoise)];% Converter os Parâmetros para String para usar no Nome
        
    else
        noiseImage = imnoise(image, 'gaussian', noiseParams);
        stringParams = num2str(noiseParams); % Converter os Parâmetros para String para usar no Nome
    end
end 

end

