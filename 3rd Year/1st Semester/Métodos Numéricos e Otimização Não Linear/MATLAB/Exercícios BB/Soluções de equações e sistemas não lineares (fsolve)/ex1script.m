format long;
x0=2;
options=optimset('TolX',1e-10,'TolFun',1e-9);
[xsol,fsol,exitflag,output]=fsolve('ex1fun',x0,options)

% Al�nea 1 %
% Usei a rotina fsolve no MATLAB. %

% Al�nea 2 %
% Sim, o m�todo convergiu uma vez que a exitflag � igual a 1. %

% Al�nea 3 %
% 7 itera��es. %

% Al�nea 4 %
% 2.540426279263 %