% Função que recebe as Arestas Fortes e Fracas da Imagesm
function [edgeMapOriginalImage] = hysteresis_thresholding(strongEdges, weakEdges)

[h,w] = size(strongEdges);

edgeMapOriginalImage = strongEdges;

for i = 2:h-1
    for j = 2:w-1
        if (weakEdges(i,j) == 1 && strongEdges(i,j) == 0)
            if (strongEdges(i,j+1) == 1 || strongEdges(i,j-1 )== 1 || strongEdges(i+1,j) == 1 || strongEdges(i-1,j) == 1 || strongEdges(i-1,j-1) == 1 || strongEdges(i+1,j+1) == 1 || strongEdges(i-1,j+1) == 1 || strongEdges(i+1,j-1) == 1)
                edgeMapOriginalImage(i,j) = 1;
            end
        end
    end

end

