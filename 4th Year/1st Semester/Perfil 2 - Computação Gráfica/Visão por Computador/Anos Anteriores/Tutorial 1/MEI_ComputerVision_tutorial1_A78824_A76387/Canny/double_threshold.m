function [strong, weak] = double_threshold(NI,high,low)
   todos = edge(NI,'Sobel', low);
   strong = edge(NI,'Sobel',high);
   weak=todos-strong;
end

