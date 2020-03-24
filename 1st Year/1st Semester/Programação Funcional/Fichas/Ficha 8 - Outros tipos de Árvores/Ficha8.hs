module Ficha8 where
import Data.Char
import Data.Maybe

---- Exercício 1 ----

data ExpInt = Const Int
            | Simetrico ExpInt
            | Mais ExpInt ExpInt
            | Menos ExpInt ExpInt
            | Mult ExpInt

--- Alínea (a) ---
calcula :: ExpInt -> Int
calcula (Const x) =  x
calcula (Simetrico x) = - calcula x
calcula (Mais um dois) = calcula um + calcula dois
calcula (Menos um dois) = calcula um - calcula dois
calcula (Mult x) = calcula x * calcula x

--- Alínea (b) ---
infixa :: ExpInt -> String
infixa (Const x) = show x -- Usamos o show de modo a dar como output o x como sendo uma String.
infixa (Simetrico x) = "-" ++ infixa x
infixa (Mais um dois) = "(" ++ infixa um ++ "+" ++ infixa dois ++ ")"
infixa (Menos um dois) = "(" ++ infixa um ++ "-" ++ infixa dois ++ ")"
infixa (Mult x) = "(" ++ infixa x ++ "x" ++ infixa x ++ ")"

--- Alínea (c) ---
posfixa :: ExpInt -> String
posfixa (Const x) =  show x
posfixa (Simetrico x) = posfixa x ++ " " ++ "-"
posfixa (Mais um dois) = posfixa um ++ " " ++ posfixa dois ++ " " ++ "+"
posfixa (Menos um dois) = posfixa um ++ " " ++ posfixa dois ++ " " ++ "-"
posfixa (Mult x) = posfixa x ++ " " ++ "x"

---- Exercício 2 ----

data RTree a = R a [RTree a]

--- Alínea (a) --- Vamos usar o map para aplicar o mesmo a todos.
soma1 :: Num a => RTree a -> a
soma1 (R a []) = a
soma1 (R a (cabeca:cauda)) = a + soma1 cabeca + soma1 (R 0 cauda)

soma2 :: Num a => RTree a -> a
soma2 (R a []) = a
soma2 (R a l) = a + sum (map soma2 l)

soma3 :: Num a => RTree a -> a
soma3 (R a l) = a + sum (aux l) where
        aux :: Num a => [RTree a] -> [a]
        aux [] = []
        aux (h:t) = soma3 h : aux t

soma4 :: Num a => RTree a -> a
soma4 (R a l) = a + foldr f 0 l where
                f :: Num a => (RTree a) -> a -> a
                f rt x = soma4 rt + x

--- Alínea (b) ---
altura :: RTree a -> Int
altura (R a []) = 1
altura (R a lista) = 1 + maximum (map altura lista)

--- Alínea (c) ---
{- prune :: Int -> RTree a -> RTree a
prune 1 (R x _) = R x []
prune n (R x lista) = R x (map prune (n-1) lista) -}

--- Alinea (d) ---
mirror :: RTree a -> RTree a
mirror (R a []) = R a []
mirror (R a nodos) = R a (reverse (map mirror nodos))

---- Exercicio 3 ----

data BTree a = Empty | Node a (BTree a) (BTree a)
data LTree a = Tip a | Fork (LTree a) (LTree a)

--- Alinea (a) ---
ltSum :: Num a => LTree a -> a
ltSum (Tip a) = a
ltSum (Fork esquerda direita) = ltSum esquerda + ltSum direita

--- Alinea (b) ---
listaT :: LTree a -> [a]
listaT (Tip a) = [a]
listaT (Fork esquerda direita) = listaT esquerda ++ listaT direita

--- Alinea (c) ---
ltHeight :: LTree a -> Int
ltHeight (Tip a) = 1
ltHeight (Fork esquerda direita) = 1 + maximum ([ltHeight esquerda] ++ [ltHeight direita])

---- Exercício 4 ----

data FTree a b = Leaf b | No a (FTree a b) (FTree a b)

--- Alínea (a) ---
splitFTree :: FTree a b -> (BTree a, LTree b)
splitFTree (Leaf b) = (Empty, Tip b)
splitFTree (No a esquerda direita) = (Node a bt1 bt2, Fork lt1 lt2)
      where (bt1,lt1) = splitFTree esquerda
            (bt2,lt2) = splitFTree direita