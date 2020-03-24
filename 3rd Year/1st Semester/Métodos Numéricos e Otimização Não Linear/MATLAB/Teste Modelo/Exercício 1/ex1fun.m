function [F] = ex1fun(x)
F(1)=0.5*cos(x(1))+0.4*cos(x(1)+x(2))-0.6;
F(2)=0.5*sin(x(1))+0.4*sin(x(1)+x(2))-0.4;
end

