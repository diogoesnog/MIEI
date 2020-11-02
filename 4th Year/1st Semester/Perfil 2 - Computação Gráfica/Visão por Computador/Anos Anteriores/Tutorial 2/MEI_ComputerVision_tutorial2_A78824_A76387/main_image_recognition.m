function [ISSR, ISCR, SNR, PreI, Histogram, Types] = main_image_recognition(filename,I,type_noise,noise_param)
     
    %IMAGEM ORIGINAL A PRETO E BRANCO
     IS= I;
     figure(1);
     imshow(IS); 
     imwrite(IS,'Imagem_preto_e_branco.png');

     %IMAGEM COM RU�DO APLICADO
     ISN = addNoise(IS,type_noise,noise_param);
     figure(2);
     imshow(ISN);
     imwrite(ISN,'Imagem_Noise.png');
     
     % C�LCULO DO SNR (em que o x � o sinal da imagem do input e o y a estimativa do ruido). 
     x=double(IS);
     y=double(ISN);
     SNR=snr(x,y-x);
     SNR
     
     %PR�-PROCESSAMENTO (filtragem, equaliza��o de contraste e subtra��o de thresholding).
     PreI= pre_processing(filename,ISN);
     PreISR= pre_processing(strcat('sr_',filename),IS);
     figure(3); imshow(PreI);
     imwrite(PreI,'Imagem_Processada.png');
     
     %DETE��O DE BORDAS (Canny Edge Detector).
     e = edge(PreI,'Canny');
     eSR = edge(PreISR, 'Canny');
     figure(4); imshow(e);
     imwrite(e,'Imagem_Canny_Edge.png');
     
     
     %DETE��O DE CIRCULOS
     % coins
     if (strcmp(filename,'coins.jpg'))
      [centers, radii] = imfindcircles(e,[60 100],'ObjectPolarity','bright','Sensitivity',0.95);
      [centers_sr, radii_sr] = imfindcircles(eSR,[60 100],'ObjectPolarity','bright','Sensitivity',0.95);
     
     % coins2
     elseif(strcmp(filename,'coins2.jpg'))
      [centers, radii] = imfindcircles(e,[145 310],'ObjectPolarity','bright','Sensitivity',0.97,'Method','twostage');
      [centers_sr, radii_sr] = imfindcircles(eSR,[145 310],'ObjectPolarity','bright','Sensitivity',0.96,'Method','twostage');
    
     % coins3
     elseif(strcmp(filename,'coins3.jpg'))
      [centers, radii] = imfindcircles(e,[220 310],'ObjectPolarity','dark','Sensitivity',0.97);
      [centers_sr, radii_sr] = imfindcircles(eSR,[220 310],'ObjectPolarity','dark','Sensitivity',0.97);
     
     %Para outras possiveis imagens
     else
      [centers, radii] = imfindcircles(e,[60 100],'ObjectPolarity','bright','Sensitivity',0.95);
      [centers_sr, radii_sr] = imfindcircles(eSR,[60 100],'ObjectPolarity','bright','Sensitivity',0.95);
     
     end
    
     %CRIA��O DOS C�RCULOS 
     %Imagem segmentada com ru�do
     figure(2);
     ISCR = viscircles(centers, radii);
     %Imagem segmentada sem ru�do
     figure(1); 
     ISSR =viscircles(centers_sr, radii_sr);
     
     saveas(figure(2),sprintf('Imagem_segmentada_com_ruido.png'));
     saveas(figure(1),sprintf('Imagem_segmentada_sem_ruido.png'));
    
     
     %N�MERO TOTAL DE C�RCULOS NA IMAGEM
     TotalCircles = length(centers);
     TotalCircles
     
     radii
     
     %N�MERO DE MOEDAS DE CADA TIPO
     Types = tiposMoeda(filename,radii);
     Types
    
     %HISTOGRAMA (com o n�mero de moedas de cada tipo).
     figure(5);
     Histogram = histogram(radii);
     title('Distribui��o do Tamanho das Moedas', 'FontSize', 14);
     xlabel('Raio (em pixeis)', 'FontSize', 11);
     ylabel('Quantidade', 'FontSize', 11);
     saveas(figure(5),sprintf('Histograma.png'));
    
end


