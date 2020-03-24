
% Splines %
x2=[0 4 8 12 16 20];
y2=[67 82 95 120 149 185];


[C,RESNORM,RESIDUAL,EXITFLAG,OUTPUT]=lsqcurvefit('ex3fun',[2 2],x2,y2)


