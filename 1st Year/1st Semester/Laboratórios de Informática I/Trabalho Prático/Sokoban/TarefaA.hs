{-|
Module : Main
Description : Projeto LI - Tarefa 1 Parte A
Copyright : Diogo Nogueira <a78957@alunos.uminho.pt>; Guilherme Miranda <a55735@alunos.uminho.pt>
Uma proposta de módulo para resolver a parte A da Tarefa 1 do projeto de LI.
-}

module Main where

import System.IO
import Data.Char
import qualified Data.Text as T

-- | Transforma o __Input String__ /(tabuleiro + coordenadas)/ numa lista de __Strings__.
inStr :: String -> [String]
inStr [] = []
inStr ['\n'] = [[],[]]
inStr (x:xs) = case x of
    '\n' -> []:inStr xs
    otherwise -> case inStr xs of
        y:ys -> (x:y):ys
        [] -> [[x]]

-- | Saída de __String__.
outStr :: [String] -> String
outStr [] = "\n"
outStr t = unlines (map (T.unpack . T.stripEnd . T.pack) t)
--outStr t = unlines t

-- | Função @__Main__@.
main = do inp <- getContents
          putStr (outStr (tarefa1 (inStr inp)))

{- | A __tarefa1__ corre a função principal desta parte A (a função @__checkInput__@) usando o @__splitAux__@ do Input. -}
tarefa1 :: [String] -> [String]
tarefa1 = checkInput.splitAux

-- Tarefa A

-- | A função @__checkInput__@ é a função principal e verifica se o tabuleiro em teste cumpre todos os requisitos para ser considerado válido.
--
-- /Para tal recorre às seguintes funções:/
--
-- * @__checkInputMapa__@;
-- * @__checkInputCoord__@;
-- * @__checkInputOverLap__@;
-- * @__checkInputCaixas__@;
-- * @__checkCoordOverLap__@.
--
-- Cada uma das funções supracitadas têm um papel específico na verificação da veracidade do tabuleiro. Caso o mesmo não esteja correto então a função @__checkInput__@ devolverá a linha onde se encontra o erro.
checkInput :: ([String], [String]) -> [String]
checkInput (x,y) | length x < 3 = [show(length x)]
                 | length y == 1 = [ show ( length x + (length y - 1) )]
                 | ( checkInputMapa x == (length x + 1) && checkInputCoord (x,y) == (length y + 1) && checkInputOverlap (x,y) == (length y + 1) && checkInputCaixas (x, tail y) == 0 && checkCoordOverLap y y == (length y + 1) ) = ["OK"] 
                 | ( checkInputMapa x /= (length x + 1) ) = [show(checkInputMapa x)]
                 | aux (x,y) /= (length y + 1) = [ show (aux (x,y) + length x) ]
                 | (checkInputCaixas (x, tail y)) /= 0 = [ show(checkInputCaixas (x, tail y) + length x) ]
                 | otherwise = ["1"]
    where aux :: ([String],[String]) -> Int
          aux (x,y) = min (min a b) c
          a = checkInputCoord(x,y)
          b = checkInputOverlap(x,y)
          c = checkCoordOverLap y y

-- | A função @__checkInputMapa__@ verifica apenas a parte do mapa, excluindo a parte referente às coordenadas.
--
-- /Para isso garante que:/
--
-- * O mapa possua os carácteres aceitáveis;
-- * Todas as linhas tenham o mesmo tamanho;
-- * Todas as linhas começem e acabem no carácter __'#'__ (que representa uma parede) - recorrendo à função @__checkStartEndWalls__@.
checkInputMapa :: [String] -> Int
checkInputMapa [] = 1;
checkInputMapa (x:[]) = if aux x == True then 2 else 1
        where aux :: String -> Bool
              aux [] = True
              aux (s:ss) = if s == '#' || s == '.' || s == ' ' then aux ss else False
checkInputMapa (x:y:z) = if checkStartEndWalls (x) == True then ( if length y == length x then ( if aux x == True then 1 + checkInputMapa (y:z) else 1 ) else 2 ) else 2 
        where aux :: String -> Bool
              aux [] = True
              aux (s:ss) =  if s == '#' || s == '.' || s == ' ' then aux ss else False

-- | A função @__checkStartEndWalls__@ é invocada na função @__checkInputMapa__@ e é ela que garante que todas as linhas do mapa começem e acabem no carácter __'#'__.
checkStartEndWalls :: String -> Bool
checkStartEndWalls a = if head a == '#' && last a == '#' then True else False

-- | A função @__checkInputCoord__@ verifica a parte referente às coordenadas.
--
-- /Para isso garante que:/
--
-- * O número de coordenadas seja igual ao número de "Caixas + Boneco";
-- * Se alguma das coordenadas excede o tamanho do mapa.
--
-- A função @__checkInputCoord__@ recorre à função @__string2Coord__@ de modo a receber as coordenadas na forma __(Int,Int)__
checkInputCoord :: ([String], [String]) -> Int

checkInputCoord ([],[]) = 1
checkInputCoord ((_:_),[]) = 1
checkInputCoord ((l:ls),(x:y)) | a == 999 && b == 999 && y == [] = 1
                               | otherwise = if a > 0 && b > 0 && a <= length l && b <= length (l:ls) then 1 + checkInputCoord ((l:ls),y) else 1
    where (a,b) = string2Coord (x)

-- | A função @__checkInputOverlap__@ verifica se alguma das coordenadas se encontra em cima de uma parede, recorrendo também por essa razão à função __string2Coord__.
checkInputOverlap :: ([String], [String]) -> Int
checkInputOverlap (l,[]) = 1
checkInputOverlap (l,(x:y)) | a == 999 && b == 999 && y == [] = 1
                            | otherwise = if aux (reverse l) (a,b) == True then 1 + checkInputOverlap (l,y) else 1
    where (a,b) = string2Coord x
          aux :: [String] -> (Int,Int) -> Bool
          aux [] (a,b) = False
          aux (l:ls) (a,b) | l == [] = False
                           | a == 0 && b == 0 = if head l == '#' then False else True
                           | a > 0 && b == 0 = aux (tail l:ls) (a-1,b)
                           | b > 0 = aux ls (a,b-1)

-- | A função @__checkInputCaixas__@ verifica se o número de caixas é igual ao número de locais para colocar as mesmas.
checkInputCaixas :: ([String], [String]) -> Int
checkInputCaixas (l,a) | (length a) == aux l = 0
                       | (length a) > aux l = aux l + 1
                       | (length a) < aux l = length a + 2
    where aux :: [String] -> Int
          aux [] = 0
          aux ([]:ls) = aux ls
          aux (l:ls) = if head l == '.' then 1 + aux(tail l:ls) else 0 + aux(tail l :ls)

-- | A função @__checkCoordOverLap__@ verifica se duas coordenadas se repetem.
checkCoordOverLap :: [String] -> [String] -> Int
checkCoordOverLap [] [] = 1
checkCoordOverLap (x:y) (l:[]) = - (length y) + 1 + checkCoordOverLap y y 
checkCoordOverLap x (l:ls) = if l == head ls then 2 else 1 + checkCoordOverLap x (l:tail ls) 

-- Tarefa A

-- | A função @__splitAux__@ separa o mapa e as coordenadas, de modo a que a função __checkInput__ receba esses dois como variáveis separadas.
splitAux :: [String] -> ([String], [String])
splitAux [] = ([],[])
splitAux (h:t) | string2Coord h == (999,999) = (h:mapa,coord)
               | otherwise =  ([], aux (h:t))
    where (mapa, coord) = splitAux t
          aux :: [String] -> [String]
          aux [] = []
          aux (l:ls) | l == [] = []
                     | otherwise = (l:aux ls)

-- | A função @__string2Coord__@ certifica-se se ass coordenadas se encontram na forma correta, convertendo-as na forma __(Int,Int)__.
string2Coord :: String -> (Int,Int)
string2Coord [] = (999,999)
string2Coord s | length (words s) == 1 = (999,999)  
string2Coord s | length (words s) > 2 = (999,999)
               | otherwise = if isDigit (head x) == True && isDigit (head y) == True then (read x, read y) else (999,999)
    where (x:y:[]) = words s
