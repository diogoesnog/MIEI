module Ficha6 where
import Data.Char
import Data.Maybe
    
---- Exercício 1 ----

--- Alínea (a) ---
any' :: (a -> Bool) -> [a] -> Bool
any' funcao [] = False
any' funcao (h:t) = if funcao h then True else any' funcao t

--- Alínea (b) ---
zipWith' :: (a->b->c) -> [a] -> [b] -> [c]
zipWith' funcao lista1 [] = []
zipWith' funcao [] lista2 = []
zipWith' funcao (h1:t1) (h2:t2) = funcao h1 h2 : zipWith' funcao t1 t2 

--- Alínea (c) ---
takeWhile' :: (a -> Bool) -> [a] -> [a]
takeWhile' funcao [] = []
takeWhile' funcao (h:t) | funcao h = h : takeWhile' funcao t
                        | otherwise = []

--- Alínea (d) ---
dropWhile' :: (a -> Bool) -> [a] -> [a] n 
dropWhile' funcao [] = []
dropWhile' funcao (h:t) | funcao h = dropWhile' funcao t
                        | otherwise = (h:t)

--- Alínea (f) ---
deleteBy' :: (a -> a -> Bool) -> a -> [a] -> [a]
deleteBy' funcao _ [] = []
deleteBy' funcao a (h:t) | funcao a h = t
                         | otherwise = h : deleteBy' funcao a t

---- Exercício 2 ----

type Polinomio = [Monomio]
type Monomio = (Float,Int)

--- Alínea (a) ---
selgrau :: Int -> Polinomio -> Polinomio 
selgrau grau polinomio = filter (\(x,y) -> y==grau) polinomio -- Saber o que são expressões lambda.

--- Alínea (b) ---z
conta :: Int -> Polinomio -> Int
conta grau polinomio = length (filter (\(x,y) -> y==grau) polinomio)

--- Alínea (c) ---
grau :: Polinomio -> Int
grau polinomio = maximum (map snd polinomio)

--- Alínea (e) ---
calcula :: Float -> Polinomio -> Float
calcula valor polinomio = sum (map (\(x,y) -> (x*valor)^y) polinomio)

--- Alínea (f) ---  
simp :: Polinomio -> Polinomio
simp polinomio = filter (\(x,y) -> x/=0) polinomio

--- Alínea (g) ---
mult :: Monomio -> Polinomio -> Polinomio
mult (coeficiente, expoente) polinomio = map (\(x,y) -> (coeficiente+x, expoente+y)) polinomio

---- Exercício 3 ----

type Mat a = [[a]]

--- Alínea (a) ---
dimOK :: Mat a -> Bool
dimOK [h] = True
dimOK (a:b:c) | (length a == length b) = dimOK (b:c)
              | otherwise = False

--- Alínea (b) --- Uma matriz tem m linhas e n colunas.
dimMat :: Mat a -> (Int,Int)
dimMat (h:t) = (length (h:t), length h)

--- Alínea (c) ---
addMat :: Num a => Mat a -> Mat a -> Mat a
addMat [] [] = []
addMat (h1:t1) (h2:t2) = zipWith (+) h1 h2 : addMat t1 t2

