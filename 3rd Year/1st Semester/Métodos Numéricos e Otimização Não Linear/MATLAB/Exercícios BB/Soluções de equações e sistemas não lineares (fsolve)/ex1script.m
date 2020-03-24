format long;
x0=2;
options=optimset('TolX',1e-10,'TolFun',1e-9);
[xsol,fsol,exitflag,output]=fsolve('ex1fun',x0,options)

% Alínea 1 %
% Usei a rotina fsolve no MATLAB. %

% Alínea 2 %
% Sim, o método convergiu uma vez que a exitflag é igual a 1. %

% Alínea 3 %
% 7 iterações. %

% Alínea 4 %
% 2.540426279263 %