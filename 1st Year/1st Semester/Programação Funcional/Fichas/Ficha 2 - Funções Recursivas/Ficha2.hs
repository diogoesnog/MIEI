module Ficha2 where
import Data.Char

---- Exercício 1 ----

--- Alínea (a) ---
funA :: [Double] -> Double
funA [] = 0
funA (y:ys) = y^2 + (funA ys)
{- O valor da função é a soma dos quadrados dos elementos da lista.
Vai pegando em cada um e aplicando a função para a cauda, ou seja,
para os restantes elementos da lista em questão. -}

--- Alínea (b) ---
funB :: [Int] -> [Int]
funB [] = []
funB (h:t) = if (mod h 2)==0 then h:(funB t)
             else (funB t)
{- Caso o 1º elemento da lista seja múltiplo de 2, ou seja, par, então junta-o à lista final.
Caso não seja aplica a função para o resto da lista esquecendo 1º elemento. -}

--- Alínea (c) ---
funC (x:y:t) = funC t
funC [x] = []
funC [] = []
{- O valor da função, seja para que lista for, será sempre a lista vazia. -}

--- Alínea (d) --- 
funD l = g [] l
g l [] = l
g l (h:t) = g (h:l) t
{- Neste caso estamos a recorrer a uma função auxiliar de nome "g".
Dada uma determinada lista, recorremos à função auxiliar usando essa mesma lista
e uma lista vazia.
Caso a nossa lista inicial dada seja vazia então damos a lista vazia.
Caso a nossa lista não seja vazia vai trocando a ordem dos elementos e por isso,
retorna o inverso da lista inicialmente passada. -}

---- Exercício 2 ----

---Alínea (a) ---
dobros :: [Float] -> [Float]
dobros [] = []
dobros (h:t) = h*2 : dobros t

--- Alínea (b) ---
numOcorre :: Char -> String -> Int
numOcorre c (h:t) = if (c==h) then 1 + (numOcorre c t) else (numOcorre c t)

--- Alínea (c) ---
positivos :: [Int] -> Bool 
positivos [x] = if (x>=0) then True else False
positivos [] = True
positivos (h:hs) = if (h>=0) then positivos hs else False

--- Alínea (d) ---
soPos :: [Int] -> [Int]
soPos [] = []
soPos (h:hs) = if (h>0) then (h:soPos hs) else (soPos hs)

--- Alínea (e) ---
somaNeg :: [Int] -> Int
somaNeg [] = 0
somaNeg (h:hs) = if (h<0) then (h+somaNeg hs) else somaNeg hs

--- Alínea (f) ---
tresUlt :: [a] -> [a]
tresUlt [] = []
tresUlt (h:t) | length (h:t) <= 3 = (h:t)
              | length (h:t) > 3 = tresUlt t
              
---- Exercício 3 ----

--- Alínea (a) ---
soDigitos :: [Char] -> [Char]
soDigitos [] = []
soDigitos (a:as) = if (isDigit a) then (a:soDigitos as) else soDigitos as

--- Alínea (b) ---
minusculas :: [Char] -> Int
minusculas [] = 0
minusculas (h:t) = if (ord h>64 && ord h<91) then 1+minusculas t else minusculas t

--- Alínea (c) ---
nums :: String -> [Char]
nums "" = []
nums (a:as) = if (ord a>47 && ord a<58) then a:(nums as) else nums as

---- Exercício 4 ----

--- Alínea (a) ---
segundos :: [(a,b)] -> [b]
segundos [] = []
segundos ((a,b):t) = [b]++segundos t

--- Alínea (b) ---
nosPrimeiros :: (Eq a) => a -> [(a,b)] -> Bool
nosPrimeiros _ [] = False
nosPrimeiros a ((x,y):t) = if (a==x) then True else nosPrimeiros a t

--- Alínea (c) ---
minfst :: (Ord a) => [(a,b)] -> a
minfst ((a,b):t) = minfstAux a t
                         where minfstAux a [] = a
                               minfstAux a ((x,y):t) = if (a>x) then minfstAux x t else minfstAux a t

--- Alínea (d) ---
sndMinFst :: (Ord a) => [(a,b)] -> b 
sndMinFst [(a,b)] = b
sndMinFst ((a,b):(c,d):t) | (a>c) = sndMinFst ((c,d):t)
                          | (a<c) = sndMinFst ((a,b):t)

--- Alínea (e) ---
sumTriplos :: (Num a, Num b, Num c) => [(a,b,c)] -> (a,b,c)
sumTriplos ((a,b,c):[]) = (a,b,c)
sumTriplos ((a,b,c):(x,y,z):ts) = sumTriplos ((a+x,b+y,c+z):ts)

--- Alínea (f) ---
maxTriplo :: (Ord a, Num a) => [(a,a,a)] -> a
maxTriplo [(a,b,c)] = (a+b+c)
maxTriplo ((a,b,c):(d,e,f):t) | ((a+b+c)>=(d+e+f)) = maxTriplo ((a,b,c):t)
                              | ((a+b+c)<(d+e+f)) = maxTriplo ((d,e,f):t)