function [Gmag, Gdir] = gradient(NI)
 [Gx,Gy] = imgradientxy(NI);
 [Gmag,Gdir] = imgradient(Gx,Gy);
end


