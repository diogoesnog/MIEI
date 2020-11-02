function [S,filename] = smoothSpatial(N,type_smoothing,filter_param)
%adiciona um filtro Gaussian
if(strcmp('gaussian', type_smoothing))
    fsize = filter_param(1);
    desvio = filter_param(2);
    
    S = imgaussfilt(N,desvio,'FilterSize',fsize,'FilterDomain','spatial');
    filename=[num2str(fsize),'_',num2str(desvio)];
end

%adiciona um filtro Average
if(strcmp('average', type_smoothing))
    kernel = filter_param(1);
    
    k=ones(kernel,kernel)/(kernel*kernel);
    S = imfilter(N,k);
    filename=num2str(kernel);
end
 
%adiciona um filtro Median
if(strcmp('median', type_smoothing))
    S = medfilt2(N);
    filename=' ';
end

end

