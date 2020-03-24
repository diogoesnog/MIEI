x = [-2 -1 0 1 2];
y = [-2 2 1 0 4];

p=polyfit(x,y,3); %descobrir o polinomio
xx=-2:0.1:2; % definir os xx para plot
yy=polyval(p,xx); %descobrir os f(xx) do polinomio

plot(x,y,'o',xx,yy) % O 'o' é para fazer gráfico de pontos