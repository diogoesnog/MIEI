module Ficha4 where
import Data.Char
import Data.Maybe

---- Exercício 1 ----

data Hora = H Int Int
      deriving Show

type Etapa = (Hora,Hora)
type Viagem = [Etapa]

-- Função que testa se uma hora é ou não válida --
testa :: Hora -> Bool
testa (H h m) =  if (h>=0 && h<24) && (m>=0 && h<60) then True else False
-- Função que compara se uma hora é ou não depois de outra --
comparahora :: Hora -> Hora -> Bool
comparahora (H h1 m1) (H h2 m2) = if (h1>h2) || (h1==h2 && m1>m2) then True else False
-- Função que converte as horas em minutos --
converte :: Hora -> Int
converte (H h m)  = h*60+m
-- Função que calcula em minutos a diferença entre duas horas --
diferencahoras :: Hora -> Hora -> Int
diferencahoras h1 h2 = if comparahora h1 h2 then ((converte h1)-(converte h2)) else ((converte h2) - (converte h1))

--- Alínea (a) ---
testaEtapa :: Etapa -> Bool
testaEtapa (H h1 m1 ,H h2 m2) = if comparahora (H h2 m2) (H h1 m1) && testa (H h1 m1) && testa (H h2 m2) then True
                                else False

--- Alínea (b) ---
testaViagem :: Viagem -> Bool
testaViagem [(H h1 m1,H h2 m2)] = if testaEtapa (H h1 m1, H h2 m2) then True else False
testaViagem((H h1 m1, H h2 m2):(H h3 m3, H h4 m4):t) | testaEtapa (H h1 m1, H h2 m2) && (comparahora (H h3 m3) (H h2 m2)) = testaViagem ((H h3 m3, H h4 m4):t)
                                                     | ((testaEtapa (H h1 m1, H h2 m2))==False) || comparahora (H h2 m2) (H h3 m3) = False

--- Alínea (c) ---
calculaHora :: Viagem -> Etapa
calculaHora ((H h1 m1, H h2 m2):t) = if testaViagem ((H h1 m1, H h2 m2):t) then calculaHoraAux (H h1 m1, H h2 m2) (last t)
                                     else (H 0 0, H 0 0)
                    where calculaHoraAux (H h1 m1, H h2 m2) (H h3 m3, H h4 m4) = (H h1 m1, H h4 m4)

--- Alínea (d) ---
calculaTempo :: Viagem -> Int
calculaTempo [] = 0
calculaTempo ((H h1 m1, H h2 m2):t) = if testaViagem ((H h1 m1, H h2 m2):t) then diferencahoras (H h1 m1) (H h2 m2) + calculaTempo t
                                      else 0

--- Alínea (e) ---
calculaTempoEspera :: Viagem -> Int
calculaTempoEspera [(H h1 m1, H h2 m2)] = 0
calculaTempoEspera ((H h1 m1, H h2 m2):(H h3 m3, H h4 m4):t) = diferencahoras (H h2 m2) (H h3 m3) + calculaTempoEspera ((H h3 m3, H h4 m4):t)

--- Alínea (f) ---
calculaTempoTotal :: Viagem -> Int
calculaTempoTotal ((H h1 m1, H h2 m2):(H h3 m3, H h4 m4):t) = calculaTempo ((H h1 m1, H h2 m2):(H h3 m3, H h4 m4):t) +
                                                              calculaTempoEspera ((H h1 m1, H h2 m2):(H h3 m3, H h4 m4):t)

---- Exercício 3 ----

data Contacto = Casa Integer
              | Trab Integer
              | Tlm Integer
              | Email String
              deriving Show
type Nome = String
type Agenda = [(Nome, [Contacto])]

--- Alínea (a) ---
acrescEmail :: Nome -> String -> Agenda -> Agenda
acrescEmail nome email agenda = agenda ++ [(nome,[Email email])]

--- Alínea (b) ---
verEmails :: Nome -> Agenda -> Maybe [String]
verEmails n [] = Nothing
verEmails n ((nome,contactos):t) | (n==nome) = Just (encontrarEmail contactos)
                                 | otherwise = verEmails n t

encontrarEmail :: [Contacto] -> [String]
encontrarEmail [] = []
encontrarEmail (Email email:t) = email : encontrarEmail t
encontrarEmail (Casa casa:t) = encontrarEmail t
encontrarEmail (Trab trabalho:t) = encontrarEmail t
encontrarEmail (Tlm telemovel:t) = encontrarEmail t

--- Alínea (c) ---
consTelefs :: [Contacto] -> [Integer]
consTelefs [] = []
consTelefs (Casa casa:t) = casa:consTelefs t
consTelefs (Trab trabalho:t) = trabalho:consTelefs t
consTelefs (Tlm telemovel:t) = telemovel:consTelefs t
consTelefs (Email email:t) = consTelefs t

--- Alínea (d) ---
casa :: Nome -> Agenda -> Maybe Integer
casa n [] = Nothing
casa n ((nome,contactos):t1) = if (n==nome) then Just (retirarNumeroCasa contactos) else casa n t1

retirarNumeroCasa :: [Contacto] -> Integer
retirarNumeroCasa (Casa casa:t) = casa
retirarNumeroCasa (Trab trabalho:t) = retirarNumeroCasa t
retirarNumeroCasa (Tlm telemovel:t) = retirarNumeroCasa t
retirarNumeroCasa (Email email:t) = retirarNumeroCasa t

---- Exercício 4 ---- 

type Dia = Int
type Mes = Int
type Ano = Int
-- type Nome = String (Já definido no exercício anterior.)

data Data = D Dia Mes Ano
      deriving Show

type TabDN = [(Nome,Data)]

--- Alínea (a) ---
procura :: Nome -> TabDN -> Maybe Data
procura nome [] = Nothing
procura nome ((nome1,data1):t) = if nome==nome1 then Just data1 else procura nome t

--- Alínea (b) ---
idade :: Data -> Nome -> TabDN -> Maybe Int
idade (D dia mes ano) nome [] = Nothing
idade (D dia mes ano) nome ((nome1,(D dia1 mes1 ano1)):t) | nome == nome1 && ano>ano1 = Just (ano-ano1)
                                                          | nome == nome1 && ano<ano1 = Just (ano1-ano)
                                                          | otherwise = idade (D dia mes ano) nome t

--- Alínea (c) ---
anterior :: Data -> Data -> Bool
anterior (D dia1 mes1 ano1) (D dia2 mes2 ano2) | dia1==dia2 && mes1==mes2 && ano1<ano2 = True
                                               | dia1==dia2 && mes1==mes2 && ano1>ano2 = False
                                               | dia1==dia2 && mes1<mes2 = True
                                               | dia1==dia2 && mes1<mes2 = False
                                               | dia1<dia2 = True 
                                               | dia1>dia2 = False

--- Alínea (d) 
ordena :: TabDN -> TabDN
ordena (h:t) = ordenaAux h (ordena t) where
            ordenaAux (nome, D dia mes ano) [] = [(nome, D dia mes ano)]
            ordenaAux (nome1, data1) ((nome2, data2):t) | anterior data1 data2 = (nome1, data1) : ordenaAux (nome2, data2) t
                                                        | otherwise = (nome2, data2) : ordenaAux (nome1, data1) t

---- Exercício 5 ----

data Movimento = Credito Float | Debito Float deriving Show
 -- data Data = D Int Int Int deriving Show (Já definido anteriormente.)
data Extracto = Ext Float [(Data, String, Movimento)] deriving Show

--- Alínea (a) ---
extValor :: Extracto -> Float -> [Movimento]
extValor (Ext numero []) valor2 = []
extValor (Ext numero ((_, _, Credito valor1):t)) valor2 | (valor1>valor2) = (Credito valor1) : extValor (Ext numero t) (valor2)
                                                        | otherwise = extValor (Ext numero t) (valor2)
extValor (Ext numero ((_, _, Debito valor1):t)) valor2  | (valor1>valor2) = (Debito valor1) : extValor (Ext numero t) (valor2)
                                                        | otherwise = extValor (Ext numero t) (valor2)     

--- Alínea (b) ---
filtro :: Extracto -> [String] -> [(Data,Movimento)]
filtro (Ext numero []) lista = []
filtro (Ext numero ((data1, descricao, movimento):t)) lista | elem (descricao) lista = [(data1, movimento)] ++ filtro (Ext numero t) lista
                                                            | otherwise = filtro (Ext numero t) lista
                                                            
--- Alínea (c) ---
creDeb :: Extracto -> (Float,Float)
creDeb extrato = creDebAux extrato (0,0) where
                        creDebAux (Ext numero []) (a,b) = (a,b)
                        creDebAux (Ext numero ((data1, descricao, Credito valor):t)) (a,b) = creDebAux (Ext numero t) (a+valor,b)
                        creDebAux (Ext numero ((data1, descricao, Debito valor):t)) (a,b) = creDebAux (Ext numero t) (a,b+valor)

--- Alínea (d) ---
saldo :: Extracto -> Float
saldo extrato = saldoAux extrato 0 where
                        saldoAux (Ext numero []) a = a
                        saldoAux (Ext numero ((date, descricao, Credito valor):t)) a = saldoAux (Ext numero t) (a+valor)
                        saldoAux (Ext numero ((date, descricao, Debito valor):t)) a = saldoAux (Ext numero t) (a-valor)