B= imread('baboon.png');
B1 = rgb2gray(B);
%figure(1)
%imshow(B1);

C= imread('castle.png');
C1 = rgb2gray(C);
%figure(2)
%imshow(C1);
 
L= imread('lena.jpg');
L1 = rgb2gray(L);
h = fspecial('gaussian',[3 3],0.1);
L2= imfilter(L1,h);
figure(1)
imshow(L2);


