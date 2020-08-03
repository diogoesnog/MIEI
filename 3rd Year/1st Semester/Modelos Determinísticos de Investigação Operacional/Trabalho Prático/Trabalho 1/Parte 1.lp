
// Função Objetivo

min: 15 p1  + 15 p2  +
      8 p3  +  8 p4  +
     17 p5  + 17 p6  +
      7 p7  +  7 p8  +
      4 p9  +  4 p10 +
      4 p11 +  4 p12 +
     18 p13 + 18 p14 +
      8 p15 +  8 p16 +
      4 p17 +  4 p18 +
     77 p19 + 77 p20 +
      5 p21 +  5 p22;

// Constantes

xC1 =  2;
yC1 =  8;

xC2 = 10;
yC2 =  7;

xC3 =  1;
yC3 =  3;

xC4 =  6;
yC4 =  4;

xC5 =  7;
yC5 =  7;

// Restrições

-p1  <= xC1 - xD1;   xC1 - xD1 <= p1 ;
-p2  <= yC1 - yD1;   yC1 - yD1 <= p2 ;

-p3  <= xC2 - xD1;   xC2 - xD1 <= p3 ;
-p4  <= yC2 - yD1;   yC2 - yD1 <= p4 ;

-p5  <= xC3 - xD1;   xC3 - xD1 <= p5 ;
-p6  <= yC3 - yD1;   yC3 - yD1 <= p6 ;

-p7  <= xC4 - xD1;   xC4 - xD1 <= p7 ;
-p8  <= yC4 - yD1;   yC4 - yD1 <= p8 ;

-p9  <= xC5 - xD1;   xC5 - xD1 <= p9 ;
-p10 <= yC5 - yD1;   yC5 - yD1 <= p10;

-p11 <= xC1 - xD2;   xC1 - xD2 <= p11;
-p12 <= yC1 - yD2;   yC1 - yD2 <= p12;

-p13 <= xC2 - xD2;   xC2 - xD2 <= p13;
-p14 <= yC2 - yD2;   yC2 - yD2 <= p14;

-p15 <= xC3 - xD2;   xC3 - xD2 <= p15;
-p16 <= yC3 - yD2;   yC3 - yD2 <= p16;

-p17 <= xC4 - xD2;   xC4 - xD2 <= p17;
-p18 <= yC4 - yD2;   yC4 - yD2 <= p18;

-p19 <= xC5 - xD2;   xC5 - xD2 <= p19;
-p20 <= yC5 - yD2;   yC5 - yD2 <= p20;

-p21 <= xD1 - xD2;   xD1 - xD2 <= p21;
-p22 <= yD1 - yD2;   yD1 - yD2 <= p22;
