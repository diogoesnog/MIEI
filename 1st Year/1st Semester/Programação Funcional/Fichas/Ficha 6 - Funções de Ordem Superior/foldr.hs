-- Ficha 5 --

import Data.Char

tamanho :: [Int] -> Int
tamanho [] = 0
tamanho (_:t) = f h (tamanho t)
    where f :: Int -> Int -> Int
          f x r = 1+r

soma :: [Int] -> [Int]
soma [] = 0
soma (h:t) = f h (soma t)
    where f :: Int -> Int -> Int
          f x r = x +r

contaPares :: [Int] -> Int
contaPares [] = 0
contaPares (h:t) = f h (contaPares t)
    where f :: Int -> Int -> Int
          f x r | even x = 1+r
                | otherwise = r


-- Função foldr para lista de Int que devolvem Int --

foldr' :: (Int -> Int -> Int) -> Int -> [Int] -> Int
foldr' f rLvazia [] = rLvazia
foldr' f rLvazia (h:t) = f h (foldr' f rLvazia t)

-----------------------------------------------------


tamanho' :: [Int] -> Int
tamanho' l = foldr' f 0 l
    where f :: Int -> Int -> Int
          f x r = 1+r

soma' :: [Int] -> Int
soma' l = foldr' f 0 lista
    where f :: Int -> Int -> Int
          f x r = x+r
