module Ficha3 where
import Data.Char

---- Exercício 1 ----

--- Alínea (a) ---
(><) :: Int -> Int -> Int
(><) a 0 = 0
(><) a b = a + ((><) a (b-1))

--- Alínea (c) ---
power :: Int -> Int -> Int
power a 0 = 1
power a b = a * (power a (b-1))

---- Exercício 2 ----

type Polinomio = [Monomio]
type Monomio = (Float,Int)

--- Alínea (a) ---
conta :: Int -> Polinomio -> Int
conta n [] = 0
conta grau polinomio = length (filter (\(x,y) -> grau==y) polinomio)

--- Alínea (b) ---
grau :: Polinomio -> Int
grau ((a,b):[]) = b
grau ((a,b):(x,y):t) = if (b>y) then grau ((a,b):t) else grau ((x,y):t)

--- Alínea (c) ---
selgrau :: Int -> Polinomio -> Polinomio
selgrau n [] = []
selgrau n ((a,b):t) = if (n==b) then [(a,b)]++selgrau n t else selgrau n t

--- Alínea (d) ---
deriv :: [(Float,Float)] -> [(Float, Float)]
deriv [] = []
deriv ((a,b):t) = [(b*a,b-1)]++deriv t

--- Alínea (e) ---
calcula :: Float -> Polinomio -> Float
calcula n [] = 0
calcula n ((a,b):t) = a*(n^b)+calcula n t

--- Alínea (f) ---
simp :: Polinomio -> Polinomio
simp [] = []
simp ((a,b):t) = if (b==0) then simp t else [(a,b)]++simp t

--- Alínea (g) ---
mult :: Monomio -> Polinomio -> Polinomio
mult _ [] = []
mult (a,b) ((x,y):t) = [(a*x,b+y)] ++ mult (a,b) t

--- Alínea (h) ---
normaliza :: Polinomio -> Polinomio
normaliza [] = []
normaliza (h:t) = normalizaAux h (normaliza t) 
        where normalizaAux (coef1, grau1) [] = [(coef1, grau1)]
              normalizaaux (coef1, grau1) ((coef2, grau2):t) | (grau1==grau2) = (coef1+coef2, grau1) : t
                                                             | otherwise = (coef2, grau2) : normalizaAux (coef1, grau1) t

--- Alínea (j) ---
produto :: Polinomio -> Polinomio -> Polinomio
produto [] polinomio = polinomio
produto polinomio [] = polinomio
produto [h] polinomio2 = (mult h polinomio2)
produto (h:t) polinomio2 = (mult h polinomio2) ++ (produto t polinomio2)

---- Alínea (k) ---
ordena :: Polinomio -> Polinomio
ordena [] = []
ordena (h:t) = ordenaAux h (ordena t)
        where ordenaAux monomio [] = [monomio]
              ordenaAux (coef1, grau1) ((coef2, grau2):t) | (grau1<grau2) = (coef1, grau1) : (coef2, grau2) : t
                                                          | otherwise = (coef2, grau2) : ordenaAux (coef1, grau1) t
---- Exercício 3 ----

type MSet a = [(a,Int)]

--- Alínea (a) ---
union1 :: Eq a => MSet a -> MSet a -> MSet a
union1 lista [] = lista
union1 lista ((x,y):t2) = union1 (unionOcorre lista (x,y)) t2

unionOcorre :: Eq a => MSet a -> (a,Int) -> MSet a
unionOcorre  [] (a,b) = [(a,b)] 
unionOcorre ((a,b):t) (x,y) | (a==x) = ((a,b+y):t)
                            | otherwise = [(a,b)] ++ unionOcorre t (x,y)
                            
--- Alínea (b) ---
intersect :: Eq a => MSet a -> MSet a -> MSet a
intersect ((a,b):t1) ((x,y):t2) | (a==x) && (b<y) = (a,b) : intersect t1 t2
                                | (a==x) && (b>y) = (x,y) : intersect t1 t2
                                | otherwise = intersect t1 t2

--- Alínea (c) ---
diff :: Eq a => MSet a -> MSet a -> MSet a 
diff lista [] = lista
diff lista ((x,y):t) = diff (diffAux lista (x,y)) t where
                             diffAux [] (x,y) = []
                             diffAux ((a,b):t) (x,y) | (x==a) = ((a,b-y):t)
                                                     | otherwise = [(a,b)] ++ diffAux t (x,y)

--- Alínea (d) ---
ordena1 :: MSet a -> MSet a
ordena1 [] = []
ordena1 (h:t) = ordena1Aux h (ordena1 t)
        where   ordena1Aux (letra1, numero1) [] = [(letra1, numero1)]
                ordena1Aux (letra1, numero1) ((letra2, numero2):t) | (numero1<numero2) = (letra1, numero1) : (letra2, numero2) : t
                                                                   | otherwise = (letra2, numero2) : ordena1Aux (letra1, numero1) t 

--- Alínea (e) ---
moda :: MSet a -> [a]
moda [] = []
moda [(letra, numero)] = [letra]
moda ((letra1, numero1):(letra2, numero2):t) | (numero1>numero2) = moda ((letra1, numero1):t)
                                             | (numero1<numero2) = moda ((letra2, numero2):t)
                                             | (numero1==numero2) = if existeMaior (letra2, numero2) t then [letra1] else moda t
        
        where   existeMaior _ [] = True
                existeMaior (letra1, numero1) ((letra2, numero2):t) = if (numero1>=numero2) then existeMaior (letra1, numero1) t else False