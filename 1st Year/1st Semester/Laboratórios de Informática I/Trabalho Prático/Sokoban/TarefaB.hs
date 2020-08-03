{-|
Module : Main
Description : Projeto LI - Tarefa 1 Parte B
Copyright : Diogo Nogueira <a78957@alunos.uminho.pt>; Guilherme Miranda <a55735@alunos.uminho.pt>
Uma proposta de módulo para resolver a parte B da Tarefa 1 do projeto de LI.
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
          putStr (outStr (tarefa2 (inStr inp)))

{- | A __tarefa2__ corre a função principal desta parte B (a função @__printSokoban__@) usando o @__splitAux__@ do Input. -}
tarefa2 :: [String] -> [String]
tarefa2 = printSokoban.splitAux


-- Tarefa B


-- | A função @__printSokoban__@ é a função principal, pelo recebe o input e recorre às funções:
--
-- * @__printWalls__@;
-- * @__addPlayer__@;
-- * @__addCrates__@.
--
-- Cada uma das funções supracitadas têm um papel específico no resultado da visualização do mapa do jogo.
printSokoban :: ([String],[String]) -> [String]
printSokoban (s,sx) = reverse ( addCrates ( ( addPlayer a b ) , tail sx ) )
    where a = reverse ( (lines( printWalls (s,sx) (1,length s) )) )
          b = string2Coord (head sx)

-- | A função @__printWalls__@ corre o mapa e verifica se as parede são ou não redundantes (analisando se todas as casa à volta também são paredes).
--
-- A função @__printWalls__@ recorre à função @__skipList__@.
printWalls :: ([String], [String]) -> (Int,Int) -> String
printWalls (x,y) (_,0) = []
printWalls (x,y) (0,_) = []
printWalls (x,y) (ia,ib) | ia == length (head x) && ib == 1 && skipList (reverse x) (ia,ib) == '#' = if skipList (reverse x) (ia - 1,ib) == '#' && skipList (reverse x) (ia,ib + 1) == '#' && skipList (reverse x) (ia - 1,ib + 1) == '#' then (' ':[]) else ('#':[])
                         | ia == length (head x) && ib == length x && skipList (reverse x) (ia,ib) == '#' = if skipList (reverse x) (ia - 1,ib) == '#' && skipList (reverse x) (ia,ib - 1) == '#' && skipList (reverse x) (ia - 1,ib - 1) == '#' then (' ':'\n':printWalls (x,y) (1,ib - 1)) else ('#':'\n':printWalls (x,y) (1,ib - 1))
                         | ia == length (head x) && ib > 1 && skipList (reverse x) (ia,ib) == '#' = if skipList (reverse x) (ia - 1,ib) == '#' && skipList (reverse x) (ia,ib + 1) == '#' && skipList (reverse x) (ia,ib - 1) == '#' && skipList (reverse x) (ia - 1,ib - 1) == '#' && skipList (reverse x) (ia - 1,ib + 1) == '#' then (' ':'\n':printWalls (x,y) (1,ib - 1)) else ('#':'\n':printWalls (x,y) (1,ib - 1))
                         | ia == 1 && ib == 1 && skipList (reverse x) (ia,ib) == '#' = if skipList (reverse x) (ia + 1,ib) == '#' && skipList (reverse x) (ia,ib + 1) == '#' && skipList (reverse x) (ia + 1,ib + 1) == '#' then (' ':printWalls ((x),y) (ia + 1,ib)) else ('#':printWalls ((x),y) (ia + 1,ib))
                         | ia == 1 && ib == length x && skipList (reverse x) (ia,ib) == '#' = if skipList (reverse x) (ia + 1,ib) == '#' && skipList (reverse x) (ia,ib - 1) == '#' && skipList (reverse x) (ia + 1,ib - 1) == '#' then (' ':printWalls (x,y) (ia + 1,ib)) else ('#':printWalls (x,y) (ia + 1,ib))
                         | ia > 1 && ib == length x && skipList (reverse x) (ia,ib) == '#' = if skipList (reverse x) (ia + 1,ib) == '#' && skipList (reverse x) (ia - 1,ib) == '#' && skipList (reverse x) (ia,ib - 1) == '#' && skipList (reverse x) (ia + 1,ib - 1) == '#' && skipList (reverse x) (ia - 1,ib - 1) == '#' then (' ':printWalls (x,y) (ia + 1,ib)) else ('#':printWalls (x,y) (ia + 1,ib))
                         | ia == 1 && ib > 1 && skipList (reverse x) (ia,ib) == '#' = if skipList (reverse x) (ia + 1,ib) == '#' && skipList (reverse x) (ia,ib + 1) == '#' && skipList (reverse x) (ia,ib - 1) == '#' && skipList (reverse x) (ia + 1,ib + 1) == '#' && skipList (reverse x) (ia + 1,ib - 1) == '#' then (' ':printWalls ((x),y) (ia + 1,ib)) else ('#':printWalls ((x),y) (ia + 1,ib))
                         | ia > 1 && ib == 1 && skipList (reverse x) (ia,ib) == '#' = if skipList (reverse x) (ia + 1,ib) == '#' && skipList (reverse x) (ia - 1,ib) == '#' && skipList (reverse x) (ia,ib + 1) == '#' && skipList (reverse x) (ia + 1,ib + 1) == '#' && skipList (reverse x) (ia - 1,ib + 1) == '#' then (' ':printWalls ((x),y) (ia + 1,ib)) else ('#':printWalls ((x),y) (ia + 1,ib))
                         | ia > 1 && ib > 1 && skipList (reverse x) (ia,ib) == '#' = if skipList (reverse x) (ia + 1,ib) == '#' && skipList (reverse x) (ia - 1,ib) == '#' && skipList (reverse x) (ia,ib + 1) == '#' && skipList (reverse x) (ia,ib - 1) == '#' && skipList (reverse x) (ia - 1,ib - 1) == '#' && skipList (reverse x) (ia - 1,ib + 1) == '#' && skipList (reverse x) (ia + 1,ib - 1) == '#' && skipList (reverse x) (ia + 1,ib + 1) == '#' then (' ':printWalls (x,y) (ia + 1,ib)) else ('#':printWalls ((x),y) (ia + 1,ib))
                         | skipList (reverse x) (ia,ib) /= '#' = (skipList (reverse x) (ia,ib):printWalls (x,y) (ia + 1,ib)) 
                         | otherwise = []

-- | A função @__addPlayer__@ vai receber o mapa e a respetiva localização do jogador, devolvendo uma versão do mapa com o jogador incluído.
addPlayer :: [String] -> (Int,Int) -> [String]
addPlayer (x:xs) (a,b) | b == 0 = ((aux x a):xs)
                       | b > 0 = (x:addPlayer xs (a,b-1))
    where aux :: String -> Int -> String
          aux x a | a > 0 = (head x : aux (tail x) (a-1))
                  | a == 0 = ('o':tail x)

-- | A função @__addCrates__@ recebe o mapa (sendo este mapa o corrospondente ao obtido na função @__addPlayer__@) e o resto das coordenadas. Adiciona cada um das caixas ao mapa e depois retorna-o.
addCrates :: ([String],[String]) -> [String]
addCrates ((x:xs),(y:ys)) | ys == [] = (aux2 (x:xs) y)
                          | otherwise = addCrates ((aux2 (x:xs) y),ys)
    where aux2 :: [String] -> String -> [String]
          aux2 (x:xs) y | b == 0 = ((aux x a):xs)
                        | b > 0 = (x:aux2 xs (show a ++ " " ++ show (b-1)))
            where (a,b) = string2Coord y
  
-- | A função @__aux__@ é uma função auxiliar usada em @__addCrates__@.        
aux :: String -> Int -> String
aux x a | a > 0 = (head x : aux (tail x) (a-1))
        | a == 0 = if head x == '.' then ('I':tail x) else ('H':tail x)
        |otherwise = []

-- | A função @__skipList__@ recebe o mapa e uma coordenada e devolve o caractér nessa posição do mapa.
skipList :: [String] -> (Int,Int) -> Char
skipList (x:y) (0,_) = 'E'
skipList (x:y) (_,0) = 'E'
skipList [] (_,_) = 'E'
skipList (x:y) (a,b) | a == 1 && b == 1 = head x
                     | a > 1 && b == 1 = skipList (tail x:y) (a-1,b) 
                     | b > 1 = skipList y (a,b-1)
                     | otherwise = 'E'

-- Tarefa B

-- | A função @__splitAux__@ separa o mapa e as coordenadas, de modo a que a função @__checkInput__@ receba esses dois como variáveis separadas.
splitAux :: [String] -> ([String], [String])
splitAux [] = ([],[])
splitAux (h:t) | string2Coord h == (999,999) = (h:mapa,coord)
               | otherwise =  ([], aux (h:t))
    where (mapa, coord) = splitAux t
          aux :: [String] -> [String]
          aux [] = []
          aux (l:ls) | l == [] = []
                     | otherwise = (l:aux ls)

-- | A função @__string2Coord__@ certifica-se se ass coordenadas se encontram na forma correta, convertendo-as na forma (Int,Int).
string2Coord :: String -> (Int,Int)
string2Coord [] = (999,999)
string2Coord s | length (words s) == 1 = (999,999)  
string2Coord s | length (words s) > 2 = (999,999)
               | otherwise = if isDigit (head x) == True && isDigit (head y) == True then (read x, read y) else (999,999)
    where (x:y:[]) = words s
