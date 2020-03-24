module Ficha7 where
import Data.Char
import Data.Maybe
           
---- Exercício 1 ----

data BTree a = Empty | Node a (BTree a) (BTree a)
               deriving Show

--- Alínea (a) ---
altura :: BTree a -> Int
altura Empty = 0
altura (Node a esquerda direita) = 1 + (max (altura esquerda) (altura direita))

--- Exemplos de Árvores Binárias ---
b1 :: BTree Int
b1 = Empty

b2 :: BTree Int
b2 = Node 5 Empty Empty

b3 :: BTree Int
b3 = Node 8 (Node 5 (Node 3 Empty Empty) Empty) (Node 15 (Node 12 (Node 10 Empty Empty) Empty) Empty) 

--- Alínea (b) ---
contaNodos :: BTree a -> Int
contaNodos Empty = 0
contaNodos (Node a esquerda direita) = 1 + contaNodos esquerda + contaNodos direita

--- Alínea (c) ---
folhas :: BTree a -> Int
folhas Empty = 0
folhas (Node a Empty Empty) = 1
folhas (Node a esquerda direita) = folhas esquerda + folhas direita

--- Alínea (d) ---
prune :: Int -> BTree a -> BTree a
prune _ Empty = Empty
prune 0 _ = Empty
prune n (Node a esquerda direita) | (n == 1) = Node a Empty Empty 
                                  | otherwise = Node a (prune (n-1) esquerda) (prune (n-1) direita)

--- Alínea (e) ---
path :: [Bool] -> BTree a -> [a]
path [] Empty = []
path (False:t) (Node a esquerda direita) = a : path t esquerda
path (True:t) (Node a esquerda direita) = a : path t direita
path [] arvore = []

--- Alínea (f) ---
mirror :: BTree a -> BTree a
mirror Empty = Empty
mirror (Node a esquerda direita) = Node a (mirror direita) (mirror esquerda)

--- Alínea (g) ---
zipWithBT :: (a -> b -> c) -> BTree a -> BTree b -> BTree c
zipWithBT funcao Empty _ = Empty
zipWithBT funcao _ Empty = Empty
zipWithBT funcao (Node a esquerda1 direita1) (Node b esquerda2 direita2) = (Node (funcao a b) (zipWithBT funcao esquerda1 esquerda2) (zipWithBT funcao direita1 direita2))

---- Exercício 2 ---

--- Alínea (a) ---
minimo :: Ord a => BTree a -> a
minimo (Node a Empty Empty) = a
minimo (Node a esquerda direita) = minimo esquerda

--- Alínea (b) ---
semMinimo :: Ord a => BTree a -> BTree a
semMinimo (Node a Empty Empty) = Empty
semMinimo (Node a Empty direita) = direita
semMinimo (Node a esquerda direita) = (Node a (semMinimo esquerda) direita)

--- Alínea (c) ---
minSmin :: Ord a => BTree a -> (a,BTree a)
minSmin arvore = (minimo arvore, semMinimo arvore)

--- Alínea (d) ---
remove :: Ord a => a -> BTree a -> BTree a
remove numero Empty = Empty
remove numero (Node a esquerda direita) | (numero==a) = Empty
                                        | (numero>a) = (Node a esquerda (remove numero direita))
                                        | (numero<a) = (Node a (remove numero esquerda) direita))

---- Exercício 3 ----

type Aluno = (Numero,Nome,Regime,Classificacao)
type Numero = Int
type Nome = String
data Regime = ORD | TE | MEL deriving Show
data Classificacao = Aprov Int | Rep | Faltou deriving Show
type Turma = BTree Aluno -- Árvore Binária de Procura (ordenada por número)

--- Alínea (a) ---
inscNum :: Numero -> Turma -> Bool
inscNum numero Empty = False
inscNum numero (Node (nr,_,_,_) esquerda direita) | numero == nr = True
                                                  | numero < nr = inscNum numero esquerda
                                                  | otherwise = inscNum numero direita
--- Alínea (b) ---
inscNome :: Nome -> Turma -> Bool
inscNome nome Empty = False
inscNome nome (Node (_,n,_,_) esquerda direita) | nome == n = True
                                                | otherwise = (inscNome nome esquerda) || (inscNome nome direita)
     
--- Alínea (c) ---
trabEst :: Turma -> [(Numero,Nome)]
trabEst Empty = []
trabEst (Node (nr, n, TE, classif) esquerda direita) = [(nr,n)] ++ trabEst direita ++ trabEst esquerda
trabEst (Node _ esquerda direita) = trabEst esquerda ++ trabEst direita

--- Alínea (d) ---
nota :: Numero -> Turma -> Maybe Classificacao
nota numero Empty = Nothing
nota numero (Node (nr, nome, estatudo, classificacao) esquerda direita) | (numero==nr) = Just classificacao 
                                                                        | (numero<nr) = nota numero esquerda
                                                                        | otherwise = nota numero direita

--- Alínea (e) ---
percFaltas :: Turma -> Float
percFaltas turma = calculaPercentagem turma 0 0 where
    calculaPercentagem Empty a b = (a/b)*100
    calculaPercentagem (Node (nr, nome, estatuto, Faltou) esquerda direita) total faltaram = (calculaPercentagem esquerda (total+1) (faltaram+1)) + (calculaPercentagem direita (total+1) (faltaram+1))
    calculaPercentagem (Node (nr, nome, estatuto, Faltou) esquerda direita) total faltaram = (calculaPercentagem esquerda (total+1) faltaram) + (calculaPercentagem direita (total+1) faltaram)
