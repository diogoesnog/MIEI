function [BEFORE,NM,H] = main_CannyDetector(name,GI,filtersize,sigma)
   %transformar a imagem em gaussian
   [G,filename] = Gaussian_smoothing(name, GI, filtersize, sigma);
   BEFORE = G;
   imwrite(BEFORE, [filename, '_edge_canny_',num2str(filtersize), '_', num2str(sigma), '.png']);
   
   figure(1); imshow(BEFORE); title('Gaussian Smoothing Image');
   
   %achar a magnitude e a direção do edge
   [Gmag,Gdir] = gradient(G);
   
   figure(2); imshow(Gmag,[]); title('Gradient Image');   
   
   %fazer o nonmax
   direc = arrayfun(@(x)normalize_directions(x), Gdir);
   NM = nonmax(Gmag,direc);
   
   %figure; imshow([Gmag,Gdir,NM]);
   
   imwrite(NM, [filename, '_edge_canny_nonmax_',num2str(filtersize), '_', num2str(sigma), '.png']);
   figure(3); imshow(NM); title('NonMax Image'); 
   
   %fazer o double threshold (high,low)
   [strong, weak] = double_threshold(NM,0.3,100);

   figure(4); imshow([strong, weak]); title('Strong and Weak Edges');
   
   H= hysteresis_thresholding(strong,weak);
   imwrite(H, [filename, '_edge_canny_hysteresis_',num2str(filtersize), '_', num2str(sigma), '.png']);
   figure(5); imshow(H); title('Hysteresis Thresholding Image'); 
end

