module Ficha5 where
import Data.Char
import Data.Maybe
    
---- Exercício 1 ----

-- Função que gera uma lista de um dado número a outro, especificados desde início.
gera :: Int -> Int -> [Int]
gera min max | min <= max = min : gera (min+1) max 
             | otherwise = []

--- Alínea (a) --- 
ex1a :: [Int]
ex1a = filtra1 (gera 1 20)
    where
        filtra1 :: [Int] -> [Int]
        filtra1 [] = []
        filtra1 (x:xs) | mod x 2 == 0 && mod x 3 == 0 = x : filtra1 xs
                       | otherwise = filtra1 xs

--- Alínea (b) ---
-- Devolve exatamente o mesmo que a alínea (a).

--- Alínea (c) ---
ex1c :: [(Int,Int)]
ex1c = filtra2 $ junta (gera 0 20) (gera 0 20)  -- Dólar em vez de usar parêntises.
        where
            append :: Int -> [Int] -> [(Int,Int)]
            append x [] = []
            append x (y:ys) = (x,y) : append x ys

            junta :: [Int] -> [Int] -> [(Int, Int)]
            junta [] l2 = []
            junta (x:xs) l2 = append x l2 ++ junta xs l2

            filtra2 :: [(Int, Int)] -> [(Int, Int)]
            filtra2 [] = []
            filtra2 ((x,y):t) | x + y == 30 = (x,y) : filtra2 t
                              | otherwise = filtra2 t 

--- Alínea (d) ---
-- Devolve os número ímpares de uma lista entre 1 e x. O x vai variar de 1 a 10. Ou seja, primeiro temos a lista só com 1. Segundo a lsta com 1 e 2.
-- Terceiro a lista com 1,2 e 3. E assim sucessivamente até à lista de 1 a 10. De cada uma destas listas retiramos apenas os elementos ímpares. --


---- Exercício 2 ----
 
--- Alínea (a) --- 
ex2a :: [Int]
ex2a = [2^x | x <- [0..10]]

--- Alínea (b) ---
ex2b :: [(Int,Int)]
ex2b = [(x, 6-x) | x <- [1..5]]

--- Alínea (c) ---
ex2c :: [[Int]]
ex2c = [[x | x <- [1..y]] | y <- [1..5]]

--- Alínea (d) --- 
ex2d1 :: [[Int]]
ex2d1 = [ replicate x 1 | x <- [1..5] ]


---- Exercício 3 ---- (Importante)

-- Com tuplings --
digitAlpha :: String -> (String,String)
digitAlpha [] = ([],[])
digitAlpha (x:xs) | isAlpha x = (x:letras, numeros)
                  | isDigit x = (letras, x:numeros)
                  | otherwise = (letras, numeros)
            where
                (letras,numeros) = digitAlpha xs
             
-- Com acumuladores --
digitAlpha' :: String -> (String,String)
digitAlpha' string = aux string ([],[])
    where
        aux [] (letras,numeros) = (letras,numeros)
        aux (x:xs) (letras,numeros) | isAlpha x = aux xs (letras ++ [x], numeros)
                                    | isDigit x = aux xs (letras, numeros ++ [x])
                                    | otherwise = aux xs (letras, numeros)

-- Com funções de ordem superior --
digitAlpha2 :: String -> (String, String)
digitAlpha2 string = (filter isAlpha string, filter isDigit string)

--- Exercício 4 ----

-- Com tuplings --
nzp :: [Int] -> (Int,Int,Int)
nzp [] = (0,0,0)
nzp (x:xs) | x < 0 = (neg+1,zeros,pos)
           | x > 0 = (neg,zeros,pos+1)
           | x == 0 = (neg,zeros+1,pos)
    where
        (neg,zeros,pos) = nzp xs

-- Com acumuladores --
nzp' :: [Int] -> (Int,Int,Int)
nzp' lista = aux lista (0,0,0)
        where
            aux [] (neg,zeros,pos) = (neg,zeros,pos)
            aux (x:xs) (neg,zeros,pos) | x < 0 = aux xs (neg+1, zeros, pos)
                                       | x > 0 = aux xs (neg, zeros, pos+1)
                                       | x == 0 = aux xs (neg, zeros+1, pos)

---- Exercício 5 ----

-- Com tuplings --
divMod1 :: Integral a => a -> a -> (a, a)
divMod1 x y | x < y = (0,x)
            | x == y = (1,0)
            | otherwise  = (d+1, m)
        where 
            (d,m) = divMod1 (x-y) y

-- Com acumuladores --
divMod2 :: Integral a => a -> a -> (a,a)
divMod2 x y = aux x y 0
        where
            aux x y d | x < y = (d,x)
                      | x == y = (d+1,0)
                      | otherwise = aux (x-y) y (d+1)

