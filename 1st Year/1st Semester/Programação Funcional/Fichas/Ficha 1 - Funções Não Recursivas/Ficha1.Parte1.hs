module Ficha1.V1 where

---- Exercício 1 ----

-- Alínea (a) --
perimetro :: Float -> Float
perimetro a = 2*3.14*a

-- Alínea (b) --
dist :: (Double, Double) -> (Double,Double) -> Double
dist (a,b) (c,d) = sqrt ((c-a)^2 + (d-b)^2)

-- Alínea (c) --
primUlt :: [Int] -> (Int,Int)
primUlt (a:as) = (a,last as)

-- Alínea (d) --
multiplo :: Int -> Int -> Bool
multiplo m n = if (mod m n == 0) then True else False

-- Alínea (e) -- 
truncaImpar :: [Int] -> [Int]
truncaImpar [] = []
truncaImpar l = if (mod (length l) 3) == 0 then tail l else l

-- Alínea (f) --
max2 :: Int -> Int -> Int
max2 m n = if (m>n) then m else n

-- Alínea (g) -- 
max3  :: Int -> Int -> Int -> Int
max3 a b c = if (a>b) then max2 a c else max2 b c

---- Exercício 2 ----

-- Alínea (a) --
nRaizes :: Float -> Float -> Float -> Float
nRaizes a b c | ((b^2)-4*a*c) < 0 = 0
              | ((b^2)-4*a*c) == 0 = 1
              | ((b^2)-4*a*c) > 0 = 2

-- Alínea (b) --
raizes :: Float -> Float -> Float -> [Float]
raizes a b c | nRaizes a b c == 0 = []
             | nRaizes a b c == 1 = [(-b)/2*a]
             | nRaizes a b c == 2 = [((-b)+sqrt(b^2-4*a*c)) / (2*a),((-b)-sqrt(b^2-4*a*c)) / (2*a)]


---- Exercício 3 ----

type Hora = (Int, Int)
 
--- Alínea (a) ---
testa :: Hora -> Bool
testa (h,m) =  if (h>=0 && h<24) && (m>=0 && h<60) then True else False

--- Alínea (b) ---
comparahora :: Hora -> Hora -> Bool
comparahora (h1, m1) (h2,m2) = if (h1>h2) || (h1==h2 && m1>m2) then True else False

--- Alínea (c) ---
convertehoras :: Hora -> Int
convertehoras (h,m) = h*60+m

--- Alínea (d) ---
converteminutos :: Int -> Hora
converteminutos min = ((div min 60),(mod min 60))

--- Alínea (e) ---
diferencahoras :: Hora -> Hora -> Int
diferencahoras h1 h2 = if comparahora h1 h2 then ((convertehoras h1)-(convertehoras h2)) else ((convertehoras h2) - (convertehoras h1))

--- Alínea (f) ---
adicionarminutos :: Int -> Hora -> Hora
adicionarminutos min (a,b) = ((div min 60)+a,(mod min 60)+b)

