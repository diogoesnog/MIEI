module Teste1 where

import Data.Char
import Data.List
import Data.Either

-- Questão 1

enumFromto :: Int -> Int -> [Int]
enumFromto a b | (a<b)  = a:(enumFromTo (a+1) b)
               | (a>=b) = [b]

-- Questão 2

enumFromThento :: Int -> Int -> Int -> [Int]
enumFromThento a b c | (a<=c) = a:(enumFromThento b (b+(b-a)) c)
                     | otherwise = []

-- Questão 3

maismais :: [a] -> [a] -> [a]
maismais [] [] = []
maismais [] (b:bs) = b:(maismais [] bs)
maismais (a:as) b = a:(maismais as b)

-- Questão 4

exclamexclam :: [a] -> Int -> a
exclamexclam (a:as) 0 = a
exclamexclam (a:as) b = exclamexclam as (b-1)

-- Questão 5

reverter :: [a] -> [a]
reverter [] = []
reverter (a:as) = reverter as ++ (a:[])

-- Questão 6

manter :: Int -> [a] -> [a]
manter a [] = []
manter 0 l = []
manter a (b:bs) = b:(tirar (a-1) bs)

-- Questão 7

tirar :: Int -> [a] -> [a] 
tirar a [] = []
tirar 0 l = l
tirar a (b:bs) = tirar (a-1) bs

-- Questão 8

juntar :: [a] -> [b] -> [(a,b)]
juntar (a:as) [] = []
juntar [] (b:bs) = []
juntar (a:as) (b:bs) = [(a,b)] ++ juntar as bs

-- Questão 9
ocorre :: Eq a => a -> [a] -> Bool
ocorre a [] = False
ocorre a (b:bs) = if (a==b) then True else (ocorre a bs)

-- Questão 10

replicar :: Int -> a -> [a]
replicar 0 b = []
replicar a b = b:(replicar (a-1) b)

-- Questão 11

intercalar :: a -> [a] -> [a]
intercalar a [] = []
intercalar a (b:bs) = a:b:(intercalar a bs)

-- Questão 12

mygroup :: Eq a => [a] -> [[a]]
mygroup [] = [[]]
mygroup (h:t) = mygroupAux [h] t where
                mygroupAux a [] = [a]
                mygroupAux a (h:t) = if ( (elem h a) == True ) then mygroupAux (a++[h]) t
                                        else a:mygroupAux [h] t        

-- Questão 13

myconcat :: [[a]] -> [a]
myconcat [] = []
myconcat (a:as) = a ++ myconcat as

-- Questão 14

inits' :: [a] -> [[a]]
inits' list = initsAux list [] where
            initsAux [] end = [end]
            initsAux (h:ts) list = (list : initsAux ts (list ++ [h]))

-- Questão 15

sufixos :: [a] -> [[a]]
sufixos []= [[]]
sufixos (a:as) = (a:as) : sufixos as

-- Questão 16

prefixode :: Eq a => [a] -> [a] -> Bool
prefixode [] l = True
prefixode (a:as) (b:bs) = if (a==b) then prefixode as bs else False

-- Questão 17

sufixode :: Eq a => [a] -> [a] -> Bool
sufixode [] _ = True
sufixode l1 l2 = if ((last l1)==(last l2)) && sufixode (init l1) (init l2) then True 
                 else False 

-- Questão 18

sequenciade :: Eq a => [a] -> [a] -> Bool
sequenciade [] [] = True
sequenciade _ [] = False
sequenciade (a:as) (b:bs) = if (a==b) then sequenciade as bs else sequenciade (a:as) bs

-- Questão 19

elementoindice :: Eq a => a -> [a] -> [Int]
elementoindice a [] = []
elementoindice a lista = elementoindiceAux 0 a lista where
                            elementoindiceAux i a [] = []
                            elementoindiceAux i a (b:bs) = if (a/=b) then elementoindiceAux (i+1) a bs
                                                                     else i:elementoindiceAux (i+1) a bs
            
-- Questão 20

repetidos :: Eq a => [a] -> [a]
repetidos [] = []
repetidos lista = repetidosAux [] lista where
                    repetidos a [] = a
                    repetidosAux a (b:bs) =  if ((elem b a) == False) then b:repetidosAux (a++(b:[])) bs
                                                                      else repetidosAux a bs

-- Questão 21

deletar :: Eq a => a -> [a] -> [a]
deletar a [] = []
deletar a (b:bs) = if (a==b) then bs else b:deletar a bs

-- Questão 22

mybarra :: Eq a => [a] -> [a] -> [a]
mybarra lista [] = lista
mybarra [] _ = []
mybarra lista (a:as) = mybarra (delete a lista) as


-- Questão 23

unir :: Eq a => [a] -> [a] -> [a]
unir [] [] = []
unir l [] = []
unir (a:as) (b:bs) = if ((elem b (a:as)) == True) then unir (a:as) bs
                                                  else unir( (a:as) ++ (b:[]) ) bs

-- Questão 24

remove :: Eq a => [a] -> [a] -> [a]
remove [] [] = []
remove [] l = []
remove l [] = []
remove (a:as) b = if ((elem a b) == True) then a:(remove as b)
                                          else remove as b

-- Questão 25

inserir :: Ord a => a -> [a] -> [a]
inserir a [] = [a]
inserir a (b:bs) = if (a>b) then b:(inserir a bs) else a:(b:bs)

-- Questão 26

juntapalavras :: [String] -> String
juntapalavras [] = ""
juntapalavras (a:as) = a ++ " " ++ juntapalavras as

-- Questão 27

juntapalavras2 :: [String] -> String
juntapalavras2 [] = ""
juntapalavras2 [a] = a
juntapalavras2 (a:as) = a ++ "\n" ++ juntapalavras2 as

-- Questão 28

pMaior :: Ord a => [a] -> Int
pMaior (a:as) = pMaiorAux 0 a as where
                pMaiorAux x y [] = x
                pMaiorAux x y (b:bs) = if (b>y) then pMaiorAux (x+1) b bs 
                                                else pMaiorAux x y bs
-- Questão 29

temrepetidos :: Eq a => [a] -> Bool 
temrepetidos [] = False
temrepetidos (a:as) = if ((elem a as) == True) then True 
                                               else temrepetidos as

-- Questão 30

algarismos :: [Char] -> [Char]
algarismos [] = []
algarismos (a:as) = if ((a>='0') && (a<='9')) then a:(algarismos as)
                                          else algarismos as

-- Questão 31

impares :: [a] -> [a]
impares [] = []
impares [a] = []
impares (a:b:bs) = b:impares bs

-- Questão 32

pares :: [a] -> [a]
pares [] = []
pares [a] = [a]
pares (a:b:bs) = a:pares bs

-- Questão 33

ordenada :: Ord a => [a] -> Bool
ordenada [a] = True
ordenada [] = True
ordenada (a:b:as) = if (a<=b) then ordenada (b:as) else False

-- Questão 34

iSort1 :: (Ord a) => [a] -> [a]
iSort1 [] = []
iSort1 a = isort1Aux [] a where
           isort1Aux l [] = l
           isort1Aux l (a:as) = isort1Aux (inserir a l) as

-- Questão 35

menor :: String -> String -> Bool
menor [] [] = False
menor [] _ = True
menor _ [] = False
menor (a:as) (b:bs) | (a<b) = True
                    | (a>b) = False
                    | (a==b) = menor as bs

-- Questão 36 

elemMSet :: Eq a => a -> [(a,Int)] -> Bool
elemMSet _ [] = False;
elemMSet a ((x,y):bs) = if (a==x) then True
                                  else elemMSet a bs

-- Questão 37

lengthMSet :: [(a,Int)] -> Int
lengthMSet [] = 0
lengthMSet ((x,y):as) = y+(lengthMSet as)

-- Questão 38

converteMSet :: [(a,Int)] -> [a]
converteMSet [] = []
converteMSet ((x,y):as) = if (y>0) then x:(converteMSet ((x,(y-1)):as))
                                   else converteMSet as

-- Questão 39

insereMSet :: Eq a => a -> [(a,Int)] -> [(a,Int)]
insereMSet a [] = [(a,1)]
insereMSet a ((x,y):bs) = if (a==x) then ((x,(y+1)):bs) else (x,y):insereMSet a bs

-- Questão 40

removeMSet :: Eq a => a -> [(a,Int)] -> [(a,Int)]
removeMSet _ [] = []
removeMSet a ((x,y):bs)  | (a==x) && (y==1) = bs
                         | (a==x) && (y>1) = (x,(y-1)):bs
                         | otherwise = (x,y):removeMSet a bs

-- Questão 41

constroiMSet :: Ord a => [a] -> [(a,Int)]
constroiMSet [] =  []
constroiMSet lista = constroiMSetAux lista 1 where
                     constroiMSetAux [a] c = (a,c):[]
                     constroiMSetAux (a:b:bs) c | (a==b) = constroiMSetAux (b:bs) (c+1)
                                                | otherwise = (a,c):constroiMSetAux (b:bs) 1

-- Questão 42

partitionEithers1 :: [Either a b] -> ([a],[b])
partitionEithers1 lista = (left lista, right lista) where
                                left(Left a:t) = a:left t
                                left(Right a:t) = left t
                                left _ = []
                                right(Left a:t) = right t
                                right(Right a:t) = a:right t
                                right _ = []

-- Questão 43

catMaybes :: [Maybe a] -> [a]
catMaybes [] = []
catMaybes (Just a:xs)  = a:catMaybes xs
catMaybes (Nothing:xs) = catMaybes xs

-- Questão 44

data Movimento = Norte | Sul | Este | Oeste
            deriving Show

posicao :: (Int, Int) -> [Movimento] -> (Int, Int)
posicao (x,y) [] = (x,y)
posicao (x,y) (Norte:bs) = posicao (x,y+1) bs
posicao (x,y) (Sul:bs) = posicao (x,y-1) bs
posicao (x,y) (Este:bs) = posicao (x+1,y) bs
posicao (x,y) (Oeste:bs) = posicao (x-1,y) bs

-- Questão 45

caminho :: (Int,Int) -> (Int,Int) -> [Movimento]
caminho (x1,y1) (x2,y2) | x1==x2 && y1==y2 = []
                        | x1<x2            = [Este] ++ caminho (x1+1,y1) (x2,y2)
                        | x1>x2            = [Oeste] ++ caminho (x1,y1) (x2+1,y2)
                        | y1<y2            = [Norte] ++ caminho (x1,y1+1) (x2,y2)
                        | y1>y2            = [Sul] ++ caminho (x1,y1) (x2,y2+1)
            
-- Questão 46

vertical :: [Movimento] -> Bool
vertical [] = True
vertical (Norte:as) = vertical as
vertical (Sul:as) = vertical as
vertical (Este:as) = False
vertical (Oeste:as) = False

-- Questão 47

-- Questão 48

-- Questão 49

-- Questão 50

data Semaforo = Verde | Amarelo | Vermelho
        deriving Show

