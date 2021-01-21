% Função que recebe a Noisy Image e calcula a Magnitude e Direção do Gradiente
% Função MATLAB imgradientxy(I)
% Função MATLAB imgradient(Gx, Gy)
% Gx representa o Horizontal Gradient e Gy representa o Vertical Gradient
% Dessa forma temos a Magnitude e Direção do Gradiente
function [gradientMagn, gradientDirect] = gradient(smoothImage)

    [horizontalGradient,verticalGradient] = imgradientxy(smoothImage);
    [gradientMagn,gradientDirect] = imgradient(horizontalGradient,verticalGradient);

end


