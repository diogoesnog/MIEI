function [rectx, recty] = coordRectangle(coordX, coordY)

coordX = coordX(:);
coordY = coordY(:);
sizeX = length(coordX);

if sizeX ~= length(coordY)
  error 'X e Y Têm ter Mesmo Tamanho'
end

if sizeX > 3
  edges = convhull(coordX, coordY);
  coordX = coordX(edges);
  coordY = coordY(edges);
  numberEdges = length(coordX) - 1;
  
elseif sizeX > 1
  numberEdges = sizeX;
  coordX(end+1) = coordX(1);
  coordY(end+1) = coordY(1);
else
  numberEdges = sizeX;
end

switch numberEdges
  case 0
    rectx = [];
    recty = [];
    return
  case 1
    rectx = repmat(coordX,1,5);
    recty = repmat(coordY,1,5);
    return
  case 2
    rectx = coordX([1 2 2 1 1]);
    recty = coordY([1 2 2 1 1]);
    return
end

Rmat = @(theta) [cos(theta) sin(theta);-sin(theta) cos(theta)];

ind = 1:(length(coordX)-1);
edgeangles = atan2(coordY(ind+1) - coordY(ind),coordX(ind+1) - coordX(ind));

edgeangles = unique(mod(edgeangles, pi/2));
nang = length(edgeangles);
met = inf;
xy = [coordX, coordY];

for i = 1:nang
  rot = Rmat(-edgeangles(i));
  xyr = xy*rot;
  xymin = min(xyr, [], 1);
  xymax = max(xyr, [], 1);
  
  A_i = prod(xymax - xymin);
  M_i = A_i;
  
  if M_i<met
    met = M_i;    
    rectangle = [xymin;[xymax(1),xymin(2)];xymax;[xymin(1),xymax(2)];xymin];
    rectangle = rectangle*rot';
    rectx = rectangle(:,1);
    recty = rectangle(:,2);
  end
end
end
