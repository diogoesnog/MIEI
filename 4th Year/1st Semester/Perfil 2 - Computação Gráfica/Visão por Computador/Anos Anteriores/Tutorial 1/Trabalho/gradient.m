function [Gmag, Gdir] = gradient(NI)
 [Gx,Gy] = imgradientxy(NI);
 [Gmag,Gdir] = imgradient(NI,'sobel',Gx,Gy);
end

%encontrei uma outraaaaaa
%function [ grad, theta ] = gradient( aImg )
%sobel_y = [1 2 1; 0 0 0; -1 -2 -1];
%sobel_x = [-1 0 1; -2 0 2; -1 0 1];

%grad_x = conv2(aImg, sobel_x, 'same');
%grad_y = conv2(aImg, sobel_y, 'same');

%grad = abs(grad_x) + abs(grad_y);
%theta = atan2(grad_y, grad_x);
%end