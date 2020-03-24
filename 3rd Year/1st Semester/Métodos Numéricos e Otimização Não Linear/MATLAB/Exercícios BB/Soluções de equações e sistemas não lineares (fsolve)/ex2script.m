x0=[-1 -0.1];
options=optimset('TolX',1e-10,'TolFun',1e-8);
[xsol,fsol,exitflag,output]=fsolve('ex2fun',x0,options)