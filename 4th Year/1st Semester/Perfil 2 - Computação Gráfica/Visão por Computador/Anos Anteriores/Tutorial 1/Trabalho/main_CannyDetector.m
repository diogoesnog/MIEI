function [before, nonmax, hysteresis] = main_CannyDetector(NI,kernel,desvio)
   NI1 = Gaussian_smoothing(NI);
   [Gmag,Gdir] = gradient(NI1);
   before = NI1;
   IR = nonmax(Gdir,before);
 
end

