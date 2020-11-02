function [strong, weak] = double_threshold(NI,high,low)
   weak = edge(NI,'Sobel', low);
   strong = edge(weak,'Sobel',high);
end

