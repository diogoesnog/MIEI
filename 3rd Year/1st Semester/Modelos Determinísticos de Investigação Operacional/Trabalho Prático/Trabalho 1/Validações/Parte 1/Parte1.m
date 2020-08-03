objetivo = @(x) 15*abs(x(1)-2)+15*abs(x(2)-8)+8*abs(x(1)-10)+8*abs(x(2)-7)+17*abs(x(1)-1)+17*abs(x(2)-3)+7*abs(x(1)-6)+7*abs(x(2)-4)+4*abs(x(1)-7)+4*abs(x(2)-7)+4*abs(x(3)-2)+4*abs(x(4)-8)+18*abs(x(3)-10)+18*abs(x(4)-7)+8*abs(x(3)-1)+8*abs(x(4)-3)+4*abs(x(3)-6)+4*abs(x(4)-4)+77*abs(x(3)-7)+77*abs(x(4)-7)+5*abs(x(1)-x(3))+5*abs(x(2)-x(4));
x0  = [0,0,0,0];

x = fmincon(objetivo,x0)