function [N,S] = main_smoothfilters(I, type_noise, variance, occurrence, filtering_domain, type_smoothing, kernel, desvio, order,cutoff,butterType)

if(strcmp('SP',type_noise))    
 N = imnoise(I,'salt & pepper',occurrence);
end

if(strcmp('G',type_noise))
 h = fspecial('gaussian',variance,occurrence);
 N= imfilter(I,h);
end 
figure(2)
imshow(N);


if(strcmp('spatial domain', filtering_domain))
    
    if(strcmp('gaussian', type_smoothing))
        S = imgaussfilt(N,desvio,'FilterSize',kernel,'FilterDomain','spatial');
    end
    
    if(strcmp('average', type_smoothing))
        % kernel size 3
        %k=[1 1 1;
        %   1 1 1;
        %   1 1 1]/9;
        if(kernel == 5)
        % kernel size 5
        k=[1 1 1 1 1;
           1 1 1 1 1;
           1 1 1 1 1;
           1 1 1 1 1;
           1 1 1 1 1;]/25;

        S = imfilter(N,k);
        end
        
        if(kernel == 10)
        k=[1 1 1 1 1 1 1 1 1 1;
           1 1 1 1 1 1 1 1 1 1;
           1 1 1 1 1 1 1 1 1 1;
           1 1 1 1 1 1 1 1 1 1;
           1 1 1 1 1 1 1 1 1 1;
           1 1 1 1 1 1 1 1 1 1;
           1 1 1 1 1 1 1 1 1 1;
           1 1 1 1 1 1 1 1 1 1;
           1 1 1 1 1 1 1 1 1 1;
           1 1 1 1 1 1 1 1 1 1;]/100;
       
        S = imfilter(N,k);
        end
        
        if(kernel == 20)
        k=[1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
           1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
           1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
           1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
           1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
           1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
           1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
           1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
           1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
           1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
           1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
           1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
           1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
           1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
           1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
           1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
           1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
           1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
           1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;
           1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1;]/400;
       
        S = imfilter(N,k);
        end
        
    end
    
    if(strcmp('median', type_smoothing))
       S = medfilt2(N);
    end
end

if(strcmp('frequency domain', filtering_domain))
    if(strcmp('gaussian', type_smoothing)) 
        S = imgaussfilt(N,desvio,'FilterSize',kernel,'FilterDomain','frequency');
        
    end
    if(strcmp('butterworth', type_smoothing))
        h = butter(order,cutoff,butterType);
        S=imfilter(N,h);
    end
    
 end

end

