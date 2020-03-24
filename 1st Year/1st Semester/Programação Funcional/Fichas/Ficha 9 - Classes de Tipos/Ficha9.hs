module Ficha9 where
import Data.Char
import Data.Maybe
    
---- Exercício 1 ----

data Frac = F Integer Integer

--- Alínea (b) ---
instance Eq Frac where
    (==) (F x1 y1) (F x2 y2) = ((x1*y2)==(x2*y1))

--- Alínea (c) ---
instance Ord Frac where
    compare (F x1 y1) (F x2 y2) | (x1==x2) && (y1<y2) = GT
                                | (x1==x2) && (y1>y2) = LT
                                | (x1<x2) && (y1==y2) = LT
                                | (x1>x2) && (y1==y2) = GT
                                | (x2*y1) == (y2*x1) = EQ

--- Alínea (d) ---
instance Show Frac where
    show (F x y) = (show x) ++ "/" ++ (show y)

--- Alínea (e) ---
instance Num Frac where
    (+) (F x1 y1) (F x2 y2) = (F (x1*y2 + x2*y1) (y1*y2))
    (-) (F x1 y1) (F x2 y2) = (F (x1*x2) (y1*y2))
    (*) (F x1 y1) (F x2 y2) = (F (x1*y2 - x2*y1) (y1*y2))
    negate (F x y) = (F (negate x) y)
    abs (F x y) = (F (abs x) (abs y))
    signum (F x y) = (F (signum x) (signum y))
    fromInteger n = (F n 1)

--- Alínea (f) ---
maioresDobro :: Frac -> [Frac] -> [Frac]
maioresDobro fracao lista = maioresDobroAux (2*fracao) lista where
                            maioresDobroAux a [] = []
                            maioresDobroAux a (h:t) = if (h>a) then h : maioresDobroAux a t else maioresDobroAux a t


---- Exercicio 2 ---

data Exp a = Const Integer
            | Simetrico (Exp a)
            | Var String
            | Mais (Exp a) (Exp a)
            | Menos (Exp a) (Exp a)
            | Mult (Exp a) (Exp a)

--- Alínea (a) ---
instance Show (Exp a) where
    show (Const a) = show a
    show (Var string) = id string
    show (Mais exp1 exp2) = "(" ++ show exp1 ++ " + " ++ show exp2 ++ ")"
    show (Mult exp1 exp2) = "(" ++ show exp1 ++ " * " ++ show exp2 ++ ")"
    show (Menos exp1 exp2) = "(" ++ show exp1 ++ " - " ++ show exp2 ++ ")"
    show (Simetrico exp1) = " - " ++ show exp1

--- Alinea (b) ---
instance Eq (Exp a) where 
    (Const a) == (Const b) = (a==b)
    (Simetrico a) == (Simetrico b) = (a==b)
    (Mais exp1 exp2) == (Mais exp3 exp4) = ((exp1+exp2)==(exp3+exp4))

---- Exercício 3 ----
data Movimento = Credito Float | Debito Float
data Data = D Int Int Int deriving (Eq)
data Extrato = Ext Float [(Data, String, Movimento)]

--- Alínea (a) ---
instance Ord Data where
    compare (D dia1 mes1 ano1) (D dia2 mes2 ano2) | (dia1==dia2) && (mes1==mes2) && (ano1==ano2) = EQ
                                                  | (ano1==ano2) && (mes1>mes2) = GT
                                                  | (ano1==ano2) && (mes1==mes2) && (dia1>dia2) = GT
                                                  | otherwise = LT

--- Alínea (b) ---
instance Show Data where
    show (D dia mes ano) = (show dia) ++ " / " ++ (show mes) ++ " / " ++ (show ano)
