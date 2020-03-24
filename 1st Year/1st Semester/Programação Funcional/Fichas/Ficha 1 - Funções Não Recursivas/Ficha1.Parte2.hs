module Ficha1.V2 where
import Data.Char

---- Exercício 4 ----

data Hora = H Int Int deriving (Show,Eq)

--- Alínea (a) ---

testa :: Hora -> Bool
testa (H h m) =  if (h>=0 && h<24) && (m>=0 && h<60) then True else False

--- Alínea (b) ---

comparahora :: Hora -> Hora -> Bool
comparahora (H h1 m1) (H h2 m2) = if (h1>h2) || (h1==h2 && m1>m2) then True else False

--- Alínea (c) ---

converte :: Hora -> Int
converte (H h m)  = h*60+m

--- Alínea (e) ---

diferencahoras :: Hora -> Hora -> Int
diferencahoras h1 h2 = if comparahora h1 h2 then ((converte h1)-(converte h2)) else ((converte h2) - (converte h1))

---- Exercício 5 ----

data Semaforo = Verde | Amarelo | Vermelho deriving (Show,Eq)

--- Alínea (a) ---
next :: Semaforo -> Semaforo
next Verde = Amarelo
next Amarelo = Vermelho
next Vermelho = Verde

-- Alínea (b) ---
stop :: Semaforo -> Bool
stop Verde = False
stop Amarelo = False
stop Vermelho = True

--- Alínea (c) ---
safe :: Semaforo -> Semaforo -> Bool
safe semaforo1 semaforo2  | (semaforo1 == Verde) && ((semaforo2 == Verde) || (semaforo2 == Amarelo)) = False
                          | (semaforo1 == Verde) && (semaforo2 == Vermelho) = True
                          | (semaforo1 == Vermelho) = True
                          | (semaforo1 == Amarelo) && ((semaforo2 == Verde) || (semaforo2 == Amarelo)) = False
                          | (semaforo1 == Amarelo) && (semaforo2 == Vermelho) = True
      
---- Exercício 6 ----

data Ponto = Cartesiano Double Double | Polar Double Double deriving (Show, Eq)

--- Alínea (a) --- 
posx :: Ponto -> Double
posx Cartesiano x y = y
posx Polar distancia angulo = cos angulo * distancia

--- Alínea (b) ---
posy :: Ponto -> Double
posy Cartesiano x y = x
posy Polar distancia angulo = sen angulo * distancia

--- Alínea (c) ---
raio :: Ponto -> Double
raio Cartesiano x y = sqrt ((x^2) + (y^2))
raio Polar distancia angulo = distancia

---- Exercício 7 ----

data Figura = Circulo Ponto Double
            | Rectangulo Ponto Ponto
            | Triangulo Ponto Ponto Ponto
            deriving (Show, Eq)

--- Alínea (a) ---
poligono :: Figura -> Bool
poligono Circulo _ _ = False
poligono Rectangulo _ _ = True
poligono Triangulo _ _ = True

---- Exercício 8 ----
-- A função ord recebe um Char e transforma no respetivo valor em Int. A função chr faz o inverso.

--- Alínea (a) ---
isLower1 :: Char -> Bool
isLower1 a = if (ord a>64 && ord a<91) then True else False

--- Alínea (b) ---
isDigit1 :: Char -> Bool 
isDigit1 a = if (ord a>47 && ord a<58) then True else False

--- Alínea (c) ---
isAlpha1 :: Char -> Bool 
isAlpha1 a =  if ((ord a>64 && ord a<91) || (ord a>96 && ord a<122))  then True else False

--- Alínea (d) ---
toUpper1 :: Char -> Char
toUpper1 a | (ord a>64 && ord a<91) = chr((ord a)+32)
           | (ord a>96 && ord a<122) = chr((ord a)-32)