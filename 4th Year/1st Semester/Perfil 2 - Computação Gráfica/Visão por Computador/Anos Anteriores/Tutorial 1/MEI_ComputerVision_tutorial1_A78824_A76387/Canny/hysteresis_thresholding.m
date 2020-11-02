function [output] = hysteresis_thresholding(strong,weak)
[h,w] = size(strong);

output = strong;

for i = 2:h-1
    for j = 2:w-1
        if (weak(i,j) == 1 && strong(i,j) == 0)
            if (strong(i,j+1) == 1 || strong(i,j-1 )== 1 || strong(i+1,j) == 1 || strong(i-1,j) == 1 || strong(i-1,j-1) == 1 || strong(i+1,j+1) == 1 || strong(i-1,j+1) == 1 || strong(i+1,j-1) == 1)
                output(i,j) = 1;
            end
        end
    end

end

