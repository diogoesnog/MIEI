
function gls = build_histogram(IMG_GRAY)

gls = linspace(0,255,256);

for i = 0:255
 gls(i+1) = sum(sum(IMG_GRAY==i));
end

bar(gls)

end