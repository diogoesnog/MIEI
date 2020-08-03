{-|
Module : Main
Description : Projeto LI - Tarefa 2 Parte F
Copyright : Diogo Nogueira <a78957@alunos.uminho.pt>; Guilherme Miranda <a55735@alunos.uminho.pt>
Uma proposta de módulo para resolver a parte F da Tarefa 2 do projeto de LI.
-}

module Main where

import System.IO
import Data.Char
import qualified Data.Text as T

import Graphics.Gloss
import Graphics.Gloss.Data.Picture
import Graphics.Gloss.Interface.Pure.Game

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

-- Tarefa F

-- | Função @__Main__@.
main :: IO ()
main = do 
       bola <- loadBMP "bola.bmp" --comprimento das imagems é 20
       caixa <- loadBMP "caixa.bmp"
       parede <- loadBMP "parede.bmp"
       vitoria <- loadBMP "vitoria.bmp"
       end <- loadBMP "end.bmp"
       putStrLn "Nome do ficheiro:"
       path <- readLn
       file <- readFile path
       joga ((20*fromIntegral(length(head(tarefa2 (inStr (file)))))-20,20*fromIntegral(length(tarefa2 (inStr (file))))-20),(tarefa2 (inStr (file))),(tarefa2 (inStr (file))),bola,caixa,parede,vitoria,end) desenhaMapa reageEvento

-- | Tipo de dados:
--
-- * Dimensões do mapa;
-- * Lista que represente o mapa.
-- * Imagem da bola;
-- * Imagem da caixa;
-- * Imagem da parede;
-- * Imagem do local vitória;
-- * Imagem do fim de jogo.
type Mapa = ((Float,Float),[String],[String],Picture,Picture,Picture,Picture,Picture)

-- | A função @__desenhaMapa__@ é a função responsável por imprimir o mapa.
desenhaMapa :: Mapa -> Picture
desenhaMapa ((xMapa,yMapa),l,li,bola,caixa,parede,vitoria,end) = Pictures [borda,tabuleiro,figuras,fim]
    where
    borda = Translate (-(xMapa+20)/2) (-(yMapa+20)/2) $ Color black (Polygon [(0,0),(0,yMapa + 20),(xMapa + 20,yMapa + 20),(xMapa + 20,0)])
    tabuleiro = Translate (-xMapa/2) (-yMapa/2) $ Color black (Polygon [(0,0),(0,yMapa),(xMapa,yMapa),(xMapa,0)])
    figuras = Translate (-xMapa/2) (-yMapa/2) $ auxDesenha l (xMapa/20,yMapa/20) (xMapa/20) bola caixa parede vitoria blank
    fim = if checkVictoryCond l == 1 then end else blank
 
-- | A função @__auxDesenha__@ é o ciclo que vai criando a imagem do mapa gráfico.
auxDesenha :: [String] -> (Float,Float) -> Float -> Picture -> Picture -> Picture -> Picture -> Picture -> Picture
auxDesenha m (x,y) xo b c p v pic | x >= 0 = Pictures[pic, (Translate (x*20) (y*20) (auxDesenha2 m (x,y) b c p v)),(auxDesenha m (x-1,y) xo b c p v pic)]
                                  | x < 0 && y > 0 = Pictures[pic,(auxDesenha m (xo,y-1) xo b c p v pic)]
                                  | otherwise = pic

-- | A função @__auxDesenha2__@ inside sobre dentro do mapa em caracteres e concede a imagem corrospondente.
auxDesenha2 :: [String] -> (Float,Float) -> Picture -> Picture -> Picture -> Picture -> Picture
auxDesenha2 s (x,y) p1 p2 p3 p4 | skipList (reverse s) (round(x+1),round(y+1)) == 'o' = p1
                                | skipList (reverse s) (round(x+1),round(y+1)) == 'O' = p1
                                | skipList (reverse s) (round(x+1),round(y+1)) == 'H' = p2
                                | skipList (reverse s) (round(x+1),round(y+1)) == 'I' = p2
                                | skipList (reverse s) (round(x+1),round(y+1)) == '#' = p3
                                | skipList (reverse s) (round(x+1),round(y+1)) == '.' = p4
                                | otherwise = blank

-- | A função @__reageEvento__@ é definida no Gloss, pelo que só é necessário ler o mapa indicando o que fazer.
reageEvento (EventKey (SpecialKey KeyUp)    Down _ _) ((xMapa,yMapa),l,li,bola,caixa,parede,vitoria,end) = if checkVictoryCond l == 0 then ((xMapa,yMapa),(updateMap 'U' l (updatePlayer (["x"],(checkPlayerPos (reverse l) (0,0))++["U"]) l)),li,bola,caixa,parede,vitoria,end) else ((xMapa,yMapa),l,li,bola,caixa,parede,vitoria,end)
reageEvento (EventKey (SpecialKey KeyDown)  Down _ _) ((xMapa,yMapa),l,li,bola,caixa,parede,vitoria,end) = if checkVictoryCond l == 0 then ((xMapa,yMapa),(updateMap 'D' l (updatePlayer (["x"],(checkPlayerPos (reverse l) (0,0))++["D"]) l)),li,bola,caixa,parede,vitoria,end) else ((xMapa,yMapa),l,li,bola,caixa,parede,vitoria,end)
reageEvento (EventKey (SpecialKey KeyLeft)  Down _ _) ((xMapa,yMapa),l,li,bola,caixa,parede,vitoria,end) = if checkVictoryCond l == 0 then ((xMapa,yMapa),(updateMap 'L' l (updatePlayer (["x"],(checkPlayerPos (reverse l) (0,0))++["L"]) l)),li,bola,caixa,parede,vitoria,end) else ((xMapa,yMapa),l,li,bola,caixa,parede,vitoria,end)
reageEvento (EventKey (SpecialKey KeyRight) Down _ _) ((xMapa,yMapa),l,li,bola,caixa,parede,vitoria,end) = if checkVictoryCond l == 0 then ((xMapa,yMapa),(updateMap 'R' l (updatePlayer (["x"],(checkPlayerPos (reverse l) (0,0))++["R"]) l)),li,bola,caixa,parede,vitoria,end) else ((xMapa,yMapa),l,li,bola,caixa,parede,vitoria,end)
reageEvento (EventKey (Char 'R') Down _ _) ((xMapa,yMapa),l,li,bola,caixa,parede,vitoria,end) = ((xMapa,yMapa),li,li,bola,caixa,parede,vitoria,end)
reageEvento (EventKey (Char 'r') Down _ _) ((xMapa,yMapa),l,li,bola,caixa,parede,vitoria,end) = ((xMapa,yMapa),li,li,bola,caixa,parede,vitoria,end)
reageEvento _ mapa = mapa

-- | A função @__reageTempo__@ não reage ao passar passar do tempo.
reageTempo :: Float -> Mapa -> Mapa
reageTempo t m = m

-- | A função @__joga__@ é a função responsável por criar o jogo.
joga :: Mapa -> (Mapa -> Picture) -> (Event -> Mapa -> Mapa) -> IO ()
joga mapaInicial desenha reage = play
     (InWindow "Sokoban - Spider-Man Version" (670, 510) (0, 0))
     (greyN 0)
     45
     mapaInicial
     desenha
     reage
     reageTempo

-- | A função @__checkPlayerPos__@ corre o mapa de caracteres dando como output a posição do jogador.
checkPlayerPos :: [String] -> (Int,Int) -> [String] -- mudar para [String]
checkPlayerPos (x:xs) (a,b)| length (x:xs) == 0 = ["Error"]
                           | length x == 0 = checkPlayerPos xs (0,b+1)
                           | head x == 'o' || head x == 'O' = [show(a)++" "++show(b)]
                           | otherwise = checkPlayerPos ((tail x):xs) (a+1,b)

{- | A tarefa2 corre a função principal desta parte B (a função @__printSokoban__@) usando o @__splitAux__@ do Input. -}
tarefa2 :: [String] -> [String]
tarefa2 = printSokoban.splitAux

-- Tarefa F 

-- Tarefa D 

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
printSokoban (s,sx) = reverse( addCrates (( addPlayer a b ),tail sx))
    where a = reverse((lines( printWalls (s,sx) (1,length s) )))
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
                       | otherwise = []
    where aux :: String -> Int -> String
          aux x a | a > 0 = (head x : aux (tail x) (a-1))
                  | a == 0 = if (head x == '.' || head x == 'I') then ('O':tail x) else ('o':tail x)

-- | A função @__addCrates__@ recebe o mapa (sendo este mapa o corrospondente ao obtido na função @__addPlayer__@) e o resto das coordenadas. Adiciona cada um das caixas ao mapa e depois retorna-o.
addCrates :: ([String],[String]) -> [String]
addCrates ((x:xs),(y:ys)) | y == [] = []
                          | ys == [] = (aux2 (x:xs) y)
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
