x0=[1 1];
options=optimset('TolX',1e-7,'TolFun',1e-10);
[xsol,fsol,exitflag,output]=fsolve('ex1fun',x0,options)