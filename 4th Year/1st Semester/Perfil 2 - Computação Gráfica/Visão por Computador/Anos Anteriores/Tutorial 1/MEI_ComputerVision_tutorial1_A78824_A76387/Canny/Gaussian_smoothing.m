function [output, filename] = Gaussian_smoothing(name,NI,filtersize,variance)
 output= imgaussfilt(NI,variance,'FilterSize',filtersize,'FilterDomain','spatial');
 filename = name;
end

