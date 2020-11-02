function [output] = Gaussian_smoothing(NI,kernel,desvio)
 output= imgaussfilt(NI,desvio,'FilterSize',kernel,'FilterDomain','spatial');
end

