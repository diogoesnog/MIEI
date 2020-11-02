%//Ficha filters

%//1 Load the image (e.g., lena.jpg) as a grayscale image, as in previous lessons (load also other images);
%// PB - PRETO E BRANCO

I = imread('lena.jpg');
PB = rgb2gray(I);
figure(1)
imshow(PB);

%//2. Add, separately, salt-an-pepper and gaussian noise to the images; Play with the parameters of these noises (e.g., variance)
%//SP - SALTER & PEPPER, G - GAUSSIAN

SP = imnoise(PB,'salt & pepper',0.1);
figure(2)
imshow(SP)

h = fspecial('gaussian',[3 3],0.5);
G = imfilter(SP,h);
figure(3)
imshow(G)

%//3. Implement a function that applies a moving average (box) filter, without recurring to Matlab's imfilter(), and use it on the original images. What is the result?


%//4. Use the Matlab functions to perform correlation (imfilter) and convolution (conv2) using the moving average kernel. Apply them to the gaussian noise and salt-an-pepper image. What is the difference between both procedures? Is the end-result the same?
%//k - kernel, F - filter da SP, FF - filter da G, C - o conv2 da F

k=[1 1 1;
   1 1 1;
   1 1 1]/9;

F = imfilter(SP,k);
figure(5)
imshow(F)
FF = imfilter(G,k);
figure(6)
imshow(FF)

C = conv2(F,k);
figure(7)

imshow(uint8(C))

C = conv2(FF,k);
figure(8)
imshow(uint8(C))

%//5. Use a gaussian kernel and perform smoothing on the gaussian noise and
%//salt-and- pepper image. What happens? Do not use Matlab's imfilter() andfspecial functions. 

S= imgaussfilt(F,2);
figure(9)
imshow(S)

SS = imgaussfilt(FF,2);
figure(10)
imshow(SS)

%//6. Repeat the operations with different kernel sizes (5, 10, 20) and different variances (sigma = 2, 5, 10); What combination of window size and standard deviation reduce the greatest amount of noise?
%//Resposta: aumentando o tamanho da matriz do k, a imagem vai ficando mais escura, e aumentando o sigma, a imagem vai ficando mais desfocada
k = [1,1,1,1,1;
    1,1,1,1,1,;
    1,1,1,1,1]/25

NF = imfilter(SP,k);
NFF = imfilter(G,k);

NS= imgaussfilt(NF,5);
figure(11)
imshow(uint8(NS))

NSS = imgaussfilt(NFF,5);
figure(12)
imshow(uint8(NSS))

%//7. Check the image borders before and after filtering. Is there any difference? With imfilter use different types of boundary interpolation methods;



%//8. Use Matlab's implementation of a median filter on the noisy images and compare it to the gaussian and box filters - which better removes the noise?




%//9. Perform high frequency emphasis on the original image, using a gaussian filter and the suggested sharpening filter in the class; Which one better enhances the image edges?