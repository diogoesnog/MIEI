[GI,filename] = AddNoiseG('lena.jpg',0.01);  
name=filename;


[BEFORE,NM,H]=main_CannyDetector(name,GI,5,2);

