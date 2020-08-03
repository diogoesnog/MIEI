{-|
Module : Main
Description : Projeto LI - Tarefa 1 Parte C
Copyright : Diogo Nogueira <a78957@alunos.uminho.pt>; Guilherme Miranda <a55735@alunos.uminho.pt>
Uma proposta de módulo para resolver a parte D da Tarefa 2 do projeto de LI.
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

-- | Função @__Main__@.
main = do inp <- getContents
          putStr (outStr (tarefa4 (inStr inp)))

{- | A tarefa2 corre a função principal desta parte B (a função @__printSokoban__@) usando o @__splitAux__@ do Input. -}
tarefa2 :: [String] -> [String]
tarefa2 = printSokoban.splitAux

{- | A tarefa3 usa o @__splitAux__@ do Input, juntamente com o resultado da tarefa2 com o mesmo Input. -}
tarefa3 :: [String] -> [String]
tarefa3 s = updatePlayer (splitAux s) (tarefa2 (init (init s)))

{- | A tarefa4 faz o @__checkVictoryCond__@ no __mapa final__ recorrendo à função @__mapAfterCommands__@.
--
-- * Se o resultado for igual a 0 então o __output__ será a mensagem: __INCOMPLETO + (NÚMERO DE COMANDOS QUE FIZERAM ALGO USANDO A FUNÇÃO @__execCommands__@)
-- * Se não, o __output__ será a mensagem: __FIM__.-}
tarefa4 :: [String] -> [String]
tarefa4 s | checkVictoryCond (mapAfterCommands (x,y) (tarefa2 (init (init s)))) == 0 = ["INCOMPLETO " ++ show(execCommands (x,y) (tarefa2 (init (init s))))]
          | otherwise = ["FIM " ++ show(execCommands (x,y) (tarefa2 (init (init s))))]
    where (x,y) = splitAux s


-- Tarefa D

-- | A função @__mapAfterCommands__@ corre a função @__updateMap__@ para cada um dos comandos dados no ficheiro, devolvendo o mapa final.
mapAfterCommands :: ([String],[String]) -> [String] -> [String]
mapAfterCommands (x,y) l | last y == [] = l
                         | checkVictoryCond l == 1 = l
                         | otherwise = mapAfterCommands (x,((updatePlayer (x,y) l) ++ [tail(last y)])) (updateMap (head(last y)) l (updatePlayer (x,y) l))

-- | A função @__execCommands__@ corre a função @__updateMap__@ para cada um dos comandos dados no ficheiro, devolvendo um /Int/ que mostra o número de comandos que levaram à alteração do mapa.
execCommands :: ([String],[String]) -> [String] -> Int -- usar updatePlayer
execCommands (x,y) l | last y == [] = 0
                     | checkVictoryCond l == 1 = 0
                     | updateMap (head(last y)) l (updatePlayer (x,y) l) == l = 0 + execCommands (x,((updatePlayer (x,y) l) ++ [tail(last y)])) l
                     | otherwise = 1 + execCommands (x,((updatePlayer (x,y) l) ++ [tail(last y)])) (updateMap (head(last y)) l (updatePlayer (x,y) l))

-- | A função @__updateMap__@ recebe um __mapa__, uma __direção__ e a __casa__ para onde o jogador vai, mudando (ou não) o mapa.
--
-- Esta função recorre portanto a diversas funções para tornar tudo isto possível.
updateMap :: Char -> [String] -> [String] -> [String]
updateMap c l p | skipList l (x,y) == 'o' = l
                | c == 'U' && (skipList (reverse l) (x+1, y+1) == 'H' || skipList (reverse l) (x+1, y+1) == 'I') = reverse( addPlayer (removePlayer(addCrates (reverse l ,[show(x) ++ " " ++ show(y+1)]))) (x,y) )
                | c == 'D' && (skipList (reverse l) (x+1, y+1) == 'H' || skipList (reverse l) (x+1, y+1) == 'I') = reverse( addPlayer (removePlayer(addCrates (reverse l ,[show(x) ++ " " ++ show(y-1)]))) (x,y) )
                | c == 'L' && (skipList (reverse l) (x+1, y+1) == 'H' || skipList (reverse l) (x+1, y+1) == 'I') = reverse( addPlayer (removePlayer(addCrates (reverse l ,[show(x-1) ++ " " ++ show(y)]))) (x,y) )
                | c == 'R' && (skipList (reverse l) (x+1, y+1) == 'H' || skipList (reverse l) (x+1, y+1) == 'I') = reverse( addPlayer (removePlayer(addCrates (reverse l ,[show(x+1) ++ " " ++ show(y)]))) (x,y) )
                | otherwise = reverse( addPlayer(removePlayer (reverse l))(x,y))
    where (x,y) = string2Coord (head p)

-- | A função @__checkVictoryCond__@ recebe um __mapa__, verificando se o jogo chegou ao fim.
checkVictoryCond :: [String] -> Int
checkVictoryCond (x:y) | aux x == 1 = 0
                       | y == [] = 1
                       | otherwise = checkVictoryCond y
    where aux :: String -> Int
          aux (x:xs) | x == 'H' || x == '.' || x == 'O' = 1
                     | xs == [] = 0
                     | otherwise = aux xs

-- | A função @__removePlayer__@ corre todo o mapa, substituindo o ícone do jogador por um espaço vazio ou um espaço denominado vitória, dependendo, como é claro, da posição do jogador.
removePlayer :: [String] -> [String]
removePlayer (x:y) | y == [] = [aux x]
                   | otherwise = (aux x:removePlayer y)
    where aux :: String -> String
          aux (x:xs) | x == 'o' = " " ++ xs
                     | x == 'O' = "." ++ xs
                     | xs == [] = [x]
                     | otherwise = [x] ++ aux xs

-- Tarefa D 

-- Tarefa C

-- | A função @__updatePlayer__@ recebe o mapa (x), as coordenadas (y:ys) e o mapa dado pelo __ProjB__ (l).
--
-- Esta função tem a particularidade de usar a função @__checkObstacles__@ para verificar __se existem obstáculos__:
--
-- * Se sim, retorna a posição original do jogador;
-- * Se não, usa o último elemento das coordenadas (U, D, L ou R) para determinar em qual direção se mexe o jogador e retorna a posição nova.
updatePlayer :: ([String],[String]) -> [String] -> [String]
updatePlayer (x,(y:ys)) l | checkObstacles ls (y:ys) (head z) == 1 = [auxUP y (head z)]
                          | checkObstacles ls (y:ys) (head z) == 0 = [y]
    where z = last ys
          ls = reverse l
          auxUP :: String -> Char -> String
          auxUP y d | d == 'U' = show(a) ++ " " ++ show(b+1)
                    | d == 'D' = show(a) ++ " " ++ show(b-1)
                    | d == 'L' = show(a-1) ++ " " ++ show(b)
                    | d == 'R' = show(a+1) ++ " " ++ show(b)
                    | otherwise = y
            where (a,b) = string2Coord y

            
-- | A função @__checkObstacles__@ recebe o mapa dado pelo __ProjB__, as coordenadas, e a direção dada pelo Input. Verifica se a localização para onde o jogador se quer mover é válida.
checkObstacles :: [String] -> [String] -> Char -> Int
checkObstacles l (y:ys) d | d == 'U' && skipList l (a,b+1) == '#' = 0
                          | d == 'D' && skipList l (a,b-1) == '#' = 0
                          | d == 'L' && skipList l (a-1,b) == '#' = 0
                          | d == 'R' && skipList l (a+1,b) == '#' = 0
                          | d == 'U' && (skipList l (a,b+1) == 'H' || skipList l (a,b+1) == 'I') = if skipList l (a,b+2) == '#' || skipList l (a,b+2) == 'H' || skipList l (a,b+2) == 'I' then 0 else 1
                          | d == 'D' && (skipList l (a,b-1) == 'H' || skipList l (a,b-1) == 'I') = if skipList l (a,b-2) == '#' || skipList l (a,b-2) == 'H' || skipList l (a,b-2) == 'I' then 0 else 1
                          | d == 'L' && (skipList l (a-1,b) == 'H' || skipList l (a-1,b) == 'I') = if skipList l (a-2,b) == '#' || skipList l (a-2,b) == 'H' || skipList l (a-2,b) == 'I' then 0 else 1
                          | d == 'R' && (skipList l (a+1,b) == 'H' || skipList l (a+1,b) == 'I') = if skipList l (a+2,b) == '#' || skipList l (a+2,b) == 'H' || skipList l (a+2,b) == 'I' then 0 else 1
                          |otherwise = 1
    where (a,b) = aux (string2Coord y)
          aux :: (Int,Int) -> (Int, Int)
          aux (c,d) = (c+1,d+1)


-- Tarefa C


-- Tarefa B


-- | A função @__printSokoban__@ recebe o input e recorre às funções:
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

-- | A função @__skipList__@ recebe o mapa e uma coordenada e devolve o caracter nessa posição do mapa.
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
