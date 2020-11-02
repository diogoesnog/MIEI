I = imread('eight.png');
J = imnoise(I,'salt & pepper',0.1);
figure(1)
imshow(J)
%figure(2)
%imshow(I)

h = fspecial('gaussian',[3 3],0.5);
L = imfilter(J,h);
figure(2)
imshow(L)

k=[1 1 1;
   1 1 1;
   1 1 1]/9;

M = imfilter(J,k);
figure(3)
imshow(M)
