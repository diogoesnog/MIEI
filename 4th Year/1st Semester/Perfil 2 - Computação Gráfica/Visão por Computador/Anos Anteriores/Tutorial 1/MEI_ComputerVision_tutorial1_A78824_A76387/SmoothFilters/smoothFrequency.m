function [S,filename] = smoothFrequency(N, type_smoothing,filter_param, butterType)

%adiciona um filtro Gaussian
if(strcmp('gaussian', type_smoothing))
    kernel = filter_param(1);
    desvio = filter_param(2);
    
    S = imgaussfilt(N,desvio,'FilterSize',kernel,'FilterDomain','frequency');    
    filename=[num2str(kernel),'_',num2str(desvio)];
end

%adiciona um filtro ButterWorth
if(strcmp('butterworth', type_smoothing))
    if strcmp('low', butterType) || strcmp('high', butterType)
        % cutoff é escalar
        order = filter_param(1)
        cutoff = filter_param(2)
        filename=[num2str(order),'_',num2str(cutoff)];
    else
        % else cutoff é 2 elementos do vector
        order = filter_param(1)
        cutoff = filter_param(2:3)
        filename=[num2str(order),'_',num2str(cutoff)];
    end
    
    h = butter(order,cutoff,butterType);
    S=imfilter(N,h);
end

end

