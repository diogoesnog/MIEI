function [tipos] = tiposMoeda(filename,radii)
  
%TIPOS DE MOEDA DA IMAGEM COINS.JPG
if(strcmp(filename,'coins.jpg'))
     n = 1;
     
     moedas1cent=0;
     %Moedas de 1 cent da imagem coins.jpg
    for i=1:length(radii)
       if ((radii(i) >= 55) && (radii(i) <= 75))
           moedas1cent=moedas1cent+1;
         
       end
    end
  
    
    moedas25cent=0;
    %Moeda de 25 cent da imagem coins.jpg
    for i=1:length(radii)
       if ((radii(i) >= 75) && (radii(i) <= 95))
           moedas25cent=moedas25cent+1;  
          
       end  
    end
 
    
    if moedas1cent > 0
        tipo{n,1} = '1 cent';
        quantidade{n,1} = moedas1cent;
        raio{n,1} = 'Entre 55 e 75 pixeis';
        n = n + 1;
    end
    
    if moedas25cent > 0
        tipo{n,1} = '25 cent';
        quantidade{n,1} = moedas25cent;
        raio{n,1} = 'Entre 75 e 95 pixeis';
        n = n + 1;
    end
    
    tipos = table(tipo,quantidade,raio);


    
    
%TIPOS DE MOEDA DA IMAGEM COINS2.JPG
elseif(strcmp(filename,'coins2.jpg'))
    n = 1;
     
     moedas1euro=0;
     %Moedas de 1 euro da imagem coins2.jpg
    for i=1:length(radii)
       if ((radii(i) >= 145) && (radii(i) <= 185))
           moedas1euro=moedas1euro+1;
         
       end
    end
moedas2euros=0;
    %Moeda de 2 euros da imagem coins2.jpg
    for i=1:length(radii)
       if ((radii(i) >= 185) && (radii(i) <= 310))
           moedas2euros=moedas2euros+1;  
          
       end  
    end
    
     if moedas1euro > 0
        tipo{n,1} = '1 euro';
        quantidade{n,1} = moedas1euro;
        raio{n,1} = 'Entre 145 e 185 pixeis';
        n = n + 1;
    end
    
    if moedas2euros > 0
        tipo{n,1} = '2 euros';
        quantidade{n,1} = moedas2euros;
        raio{n,1} = 'Entre 185 e 310 pixeis';
        n = n + 1;
    end
    
    tipos = table(tipo,quantidade,raio);
 


%TIPOS DE MOEDA DA IMAGEM COINS3.JPG
elseif(strcmp(filename,'coins3.jpg'))
     
    n = 1;
     
     moedas10cent=0;
     %Moedas de 10 centimos da imagem coins3.jpg
    for i=1:length(radii)
       if ((radii(i) >= 200) && (radii(i) <= 250))
           moedas10cent=moedas10cent+1;
         
       end
    end
    
    moedas20cent=0;
     %Moedas de 20 centimos da imagem coins3.jpg
    for i=1:length(radii)
       if ((radii(i) >= 250) && (radii(i) <= 270))
           moedas20cent=moedas20cent+1;
         
       end
    end
    
    moedas50cent=0;
     %Moedas de 50 centimos da imagem coins3.jpg
    for i=1:length(radii)
       if ((radii(i) >= 270) && (radii(i) <= 300))
           moedas50cent=moedas50cent+1;
         
       end
    end
    
    if moedas10cent > 0
        tipo{n,1} = '10 centimos';
        quantidade{n,1} = moedas10cent;
        raio{n,1} = 'Entre 200 e 250 pixeis';
        n = n + 1;
    end
    
    if moedas20cent > 0
        tipo{n,1} = '20 centimos';
        quantidade{n,1} = moedas20cent;
        raio{n,1} = 'Entre 250 e 270 pixeis';
        n = n + 1;
    end
    
    if moedas50cent > 0
        tipo{n,1} = '50 centimos';
        quantidade{n,1} = moedas50cent;
        raio{n,1} = 'Entre 270 e 300 pixeis';
        n = n + 1;
    end
    
    tipos = table(tipo,quantidade,raio);
end


   
end

