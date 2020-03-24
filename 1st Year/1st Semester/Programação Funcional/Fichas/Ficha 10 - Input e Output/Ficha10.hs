module Ficha10 where
import Data.Char
import System.Random
    
---- Exercício 1 ----
bingo :: IO ()
bingo = acumulaValores [] >>= print

acumulaValores :: [Int] -> IO [Int]
acumulaValores lista | (length lista == 90) = return lista
                     | otherwise = do
                        a <- randomRIO (1,90)
                        let novalista = if (elem a lista) then lista else a:lista
                        acumulaValores novalista

catMaybes :: [Maybe a] -> [a]
catMaybes [] = []
catMaybes (Just a:t) = a : catMaybes t
catMaybes (Nothing:t) = catMaybes t

insert1 :: Ord a => a -> [a] -> [a]
insert1 _ [] = []
insert1 numero (h:t) = if (numero>h) then (h : insert1 numero t) else (numero : h : t)