% Função que recebe uma Imagem e devolver as Arestas Fracas e Fortes dessa
% mesma Imagem.
% Função edge MATLAB devolve todas as aretas do limite dado como parâmetro.
% Usa-se o método de deteção de Edges Sobel
% "Finds edges at those points where the gradient of the image I is maximum, using the Sobel approximation to the derivative."
function [strongEdges, weakEdges] = double_threshold(image, highLimit, lowLimit)

   allEdges = edge(image, 'Sobel', lowLimit);
   strongEdges = edge(image, 'Sobel', highLimit);
   weakEdges = allEdges - strongEdges;
   
end

