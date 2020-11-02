I = imread("Image8.tif");
figure(1)
imshow(I);

%Calibration points in the world
X1 = 0; Y1 = 0;
X2 = 3; Y2 = 0;
X3 = 6; Y3 = 0;
X4 = 0; Y4 = 3;
X5 = 3; Y5 = 3;
X6 = 6; Y6 = 3;
X7 = 0; Y7 = 6;
X8 = 3; Y8 = 6;
X9 = 6; Y9 = 6;

% Calibration points in the image 
x1= 134; y1= 378;
x2= 165; y2= 379;
x3= 198; y3= 381;
x4= 138; y4= 354;
x5= 169; y5= 355;
x6= 199; y6= 356;
x7= 141; y7= 331;
x8= 171; y8= 333;
x9= 201; y9= 334;

f =[ x1 y1 x2 y2 x3 y3 x4 y4 x5 y5 x6 y6 x7 y7 x8 y8 x9 y9]';

%system of linear equations
D = [X1 Y1 1 0 0 0 -x1*X1 -x1*Y1;
    0 0 0 x1 y1 1 -y1*X1 -y1*Y1;
    X2 Y2 1 0 0 0 -x2*X2 -x2*Y2;
    0 0 0 x2 y2 1 -y2*X2 -y2*Y2;
    X3 Y3 1 0 0 0 -x3*X3 -x3*Y3;
    0 0 0 x3 y3 1 -y3*X3 -y3*Y3;
    X4 Y4 1 0 0 0 -x4*X4 -x4*Y4;
    0 0 0 x4 y4 1 -y4*X4 -y4*Y4;
    X5 Y5 1 0 0 0 -x5*X5 -x5*Y5;
    0 0 0 x5 y5 1 -y5*X5 -y5*Y5;
    X6 Y6 1 0 0 0 -x6*X6 -x6*Y6;
    0 0 0 x6 y6 1 -y6*X6 -y6*Y6;
    X7 Y7 1 0 0 0 -x7*X7 -x7*Y7;
    0 0 0 x7 y7 1 -y7*X7 -y7*Y7;
    X8 Y8 1 0 0 0 -x8*X8 -x8*Y8;
    0 0 0 x8 y8 1 -y8*X8 -y8*Y8;
    X9 Y9 1 0 0 0 -x9*X9 -x9*Y9;
    0 0 0 x9 y9 1 -y9*X9 -y9*Y9]
  
%calculate homography h 
h = pinv(D)*f;
h = [h;1];

% Test homography
H = (reshape(h, 3,3))';
test = H * [3,3,1]';
x5_new = test(1)/test(3)








