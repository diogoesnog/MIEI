function [out] = pre_processing(filename,I)
   %Pré processamento da imagem coins, com e sem ruído
   if (strcmp(filename,'coins.jpg') || strcmp(filename,'sr_coins.jpg'))
    
    I = imgaussfilt(I,2,'FilterSize',3,'FilterDomain','spatial');
    out = histeq(I);
    
   %Pré processamento da imagem coins2 com ruído
   elseif (strcmp(filename,'coins2.jpg'))
      
       I = imgaussfilt(I,11,'FilterSize',25,'FilterDomain','spatial');
       se=strel('disk',15);
       background =imopen(I,se);
       I2= I-background;
       I3 =imadjust(I2);
       
       bw =imbinarize(I3);
       bw = bwareaopen(bw,50);
    
       out=bw;
   
   %Pré processamento da imagem coins2 sem ruído
   elseif (strcmp(filename,'sr_coins2.jpg'))
       se=strel('disk',15);
       background =imopen(I,se);
       I2= I-background;
       I3 =imadjust(I2);
       
       bw =imbinarize(I3);
       bw = bwareaopen(bw,50);
    
       out=bw;
   
   %Pré processamento da imagem coins3, com e sem ruído
   elseif (strcmp(filename,'coins3.jpg') || strcmp(filename,'sr_coins3.jpg'))
    
    I = imgaussfilt(I,5,'FilterSize',15,'FilterDomain','spatial');
    out = histeq(I);

    
   else
       I = imgaussfilt(I,2,'FilterSize',3,'FilterDomain','spatial');
       out = histeq(I);
   end

end

