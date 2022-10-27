{-# LANGUAGE FlexibleInstances #-}
{-# LANGUAGE ScopedTypeVariables #-}

module Robot
  ( readLDM,
    readLCR,
    run,
  )
where

import Control.Monad.State (gets, modify, execState, MonadState(get), State, when)
import Data.List (elemIndex, intercalate)
import Data.Maybe ( fromMaybe )
import Parsing ( (<|>), first, greedy, listOf, symbol, Parser(..) )
import Data.Traversable (for)
import Control.Arrow (Arrow(second))

--Robot
----------------------------------------------------------------------------

type Fuel = Int

type Point = (Int, Int)

type Material = Int

data Robot = Robot
  { energy :: Fuel,
    position :: Point,
    collected :: Material
  }
  deriving (Eq, Ord)

instance Show Robot where
  show (Robot x (a, b) y) =
    concat ["Energy:", show x, "\nPosition:", show (a, b), "\nCollected:", show y, "\n"]

sampleRobot :: Robot
sampleRobot =
  Robot
    { energy = 100,
      position = (1, 1),
      collected = 0
    }

--Element
----------------------------------------------------------------------------

data Element
  = Empty -- espaço vazio
  | Entry -- entrada da mina
  | Wall -- parede
  | Earth -- terra
  | Rock -- rocha
  | Material Int -- material, Int indica quantidade.
  deriving (Eq, Ord)

instance Show Element where
  show Empty = " "
  show Entry = "E"
  show Wall = "%"
  show Earth = "."
  show Rock = "*"
  show (Material x)
    | x == 50 = "?"
    | x == 100 = ":"
    | x == 150 = ";"
    | otherwise = "$"

sampleElement :: Element
sampleElement = Material 10

pElement :: Parser Char Element
pElement =
  f
    <$> ( symbol ' '
            <|> symbol 'E' 
            <|> symbol '%' 
            <|> symbol '.' 
            <|> symbol '*' 
            <|> symbol '?' 
            <|> symbol ':' 
            <|> symbol ';' 
            <|> symbol '$' 
            -- quantidade
        )
  where
    f res
      | res == ' ' = Empty
      | res == 'E' = Entry
      | res == '%' = Wall
      | res == '.' = Earth
      | res == '*' = Rock
      | res == '?' = (Material 50)
      | res == ':' = (Material 100)
      | res == ';' = (Material 150)
      | res == '$' = (Material 1) 
      | otherwise = error "Invalid Element"

--Mina
----------------------------------------------------------------------------

type Line = [Element]

line1 :: Line
line1 = [Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall]
  
line2 :: Line
line2 = [Wall, Rock, Rock, Rock, Earth, Earth, Earth, Earth, Earth, Earth, Earth, Earth, Earth, Earth, Wall]

line3 :: Line
line3 = [Wall, Rock, Rock, Rock, Earth, Earth, Earth, Empty, Earth, Earth, Earth, Rock, Earth, Earth, Wall]

line4 :: Line
line4 = [Wall, Rock, Rock, Rock, Earth, Earth, Earth, Empty, Earth, Earth, Rock, Rock, Rock, Earth, Wall]

line5 :: Line
line5 = [Wall, Earth, (Material 50), Earth, Earth, Earth, Earth, Empty, Earth, Earth, Earth, Rock, Earth, Earth, Wall]

line6 :: Line
line6 = [Wall, Earth, Earth, Empty, Empty, Empty, Empty, Empty, Earth, Earth, Empty, Earth, Earth, Earth, Wall]

line7 :: Line
line7 = [Wall, Earth, Earth, Earth, Earth, Empty, Earth, Earth, Earth, Earth, Empty, Earth, Earth, Earth, Wall]

line8 :: Line
line8 = [Wall, Earth, (Material 100), Earth, Earth, Empty, Earth, Earth, Earth, Earth, Empty, Earth, Earth, Earth, Wall]

line9 :: Line
line9 = [Wall, Earth, Earth, Empty, Earth, Empty, Empty, Empty, Empty, Empty, Empty, Empty, Earth, Earth, Wall]

line10 :: Line
line10 = [Wall, Earth, Earth, Rock, Earth, Empty, Earth, Earth, Empty, Earth, Earth, Earth, Earth, Earth, Wall]

line11 :: Line
line11 = [Wall, Earth, Earth, Earth, Earth, Empty, Earth, Earth, Empty, Earth, (Material 150), (Material 150), Earth, Earth, Wall]

line12 :: Line
line12 = [Wall, Earth, Rock, Earth, Earth, Empty, Earth, Earth, Earth, (Material 150), (Material 150), Earth, Earth, Rock, Wall]

line13 :: Line
line13 = [Wall, Earth, Earth, Earth, Earth, Earth, Earth, Earth, Earth, Earth, Earth, Earth, Earth, (Material 1), Wall]

line14 :: Line
line14 = [Wall, Earth, Earth, Earth, Earth, Earth, Earth, Earth, Earth, Earth, Empty, Earth, Empty, Empty, Wall]

line15 :: Line
line15 = [Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall, Wall, Entry, Wall]

data Mine = Mine
  { lines :: Int,
    columns :: Int,
    elements :: [Line]
  }
  deriving (Eq, Ord)

exampleMine :: Mine
exampleMine =
  Mine
    { Robot.lines = 15,
      Robot.columns = 15,
      Robot.elements = [line1, line2, line3, line4, line5, line6, line7, line8, line9, line10, line11, line12, line13, line14, line15]
    }

instance Show Mine where
  show (Mine l c xs) = unlines $ map (intercalate "" . map show) $ xs

--Funcoes Gerais
----------------------------------------------------------------------------

validMine :: Mine -> Bool
validMine (Mine 0 0 [])       = True 
validMine (Mine _ _ [])       = False 
validMine (Mine l c xs) = (length xs == l) && mesmoTamanho xs c && procuraEntrada xs l c 0 where 

procuraEntrada :: [[Element]] -> Int -> Int -> Int -> Bool
procuraEntrada [] _ _ _ = False
procuraEntrada (x : xs) l c count
  | count == 0 = if elem Entry x then True else procuraEntrada xs l c (count + 1)
  | count == (l -1) = if elem Entry x then True else False
  | otherwise = (fromMaybe (-1) $ elemIndex Entry x) == 0 || (fromMaybe (-1) $ elemIndex Entry x) == (c -1) || procuraEntrada xs l c (count + 1)

mesmoTamanho :: [[Element]] -> Int -> Bool
mesmoTamanho [] _ = True
mesmoTamanho (x : xs) l = (all (\y -> length y == length x) xs) && (length x == l)

pLine :: Parser Char Line
pLine = greedy pElement

pMatrix :: Parser Char [Line]
pMatrix = first $ listOf pLine (symbol '\n')

linesToMine :: [Line] -> Mine
linesToMine x =
  Mine
    { Robot.lines = length x,
      Robot.columns = length (head x),
      Robot.elements = x
    }

pMine :: Parser Char Mine
pMine = linesToMine <$> pMatrix

data Instr
  = L -- move para esquerda
  | R -- move para direita
  | U -- move para cima
  | D -- move para baixo
  | C -- coleta material
  | S -- para para recarga.
  deriving (Eq, Ord, Show, Enum)

pInstr :: Parser Char Instr
pInstr =
  f
    <$> ( symbol 'L'
            <|> symbol 'R'
            <|> symbol 'U'
            <|> symbol 'D'
            <|> symbol 'C'
            <|> symbol 'S'
        )
  where
    f res
      | res == 'L' = L
      | res == 'R' = R
      | res == 'U' = U
      | res == 'D' = D
      | res == 'C' = C
      | res == 'S' = S
      | otherwise = error "Invalid Instruction"

pProgram :: Parser Char [Instr]
pProgram = greedy pInstr

type Conf = (Robot, Mine)

type ConfM a = State Conf a

current :: ConfM Point
current = gets $ position . fst

mine :: ConfM Mine
mine = gets $ snd

enoughEnergy :: Int -> ConfM Bool
enoughEnergy v = do
  c1 <- get
  return $ energy (fst c1) >= v

incEnergy :: ConfM ()
incEnergy = modify (\(r, m) -> (r {energy = energy r + 1}, m))

-- TODO: terminar com restrições
-- Ponto Para Atualizar o Robo -> Ponto Para Substituir por Vazio Na Mina -> Material Coletado -> Energia Para subtrair 
updatePosition :: Point -> Point -> Int -> Int -> ConfM ()
updatePosition (x, y) (x', y') c e = modify (\(r, m) -> (r {position = (x, y), energy = energy r - e, collected = collected r + c}, m{elements = substituirPorVazio m (x',y')}))

substituirPorVazio :: Mine -> Point -> [Line]
substituirPorVazio (Mine l c xs) (x, y) = (replaceAtIndex x (replaceAtIndex y Empty (xs !! x)) xs)

replaceAtIndex :: Int -> a -> [a] -> [a]    
replaceAtIndex i x xs = take i xs ++ [x] ++ drop (i+1) xs

isNotWall :: Mine -> Point -> Bool
isNotWall m (x, y) = (not $ elements m !! x !! y == Wall) && (not $ elements m !! x !! y == Entry)

haveOre :: Mine -> Point -> (Int, Int) -> Bool
haveOre m (x, y) (l, c) =
         if(x+1 > l-1) then False else fst (isOre m (x+1, y))
      || if(x-1 < 0)   then False else fst (isOre m (x-1, y))
      || if(y+1 > c-1) then False else fst (isOre m (x, y+1))
      || if(y-1 < 0)   then False else fst (isOre m (x, y-1))

pontoOre :: Mine -> Point -> Point
pontoOre m (x, y)  
      | fst (isOre m (x+1, y)) = (x+1, y) 
      | fst (isOre m (x-1, y)) = (x-1, y)
      | fst (isOre m (x, y+1)) = (x, y+1)
      | fst (isOre m (x, y-1)) = (x, y-1)
      | otherwise = (1, 1)

isMaterial :: Mine -> Point -> (Bool, Int)
isMaterial m (x, y) 
          |  elements m !! x !! y == Rock = (True, 0)
          |  elements m !! x !! y == Earth = (True, 0)
          |  elements m !! x !! y == Material 50 = (True, 50)
          |  elements m !! x !! y == Material 100 = (True, 100)
          |  elements m !! x !! y == Material 150 = (True, 150)
          |  elements m !! x !! y == Material 1 = (True, 1)
          |  otherwise = (False, 0)

isOre :: Mine -> Point -> (Bool, Int)
isOre m (x, y) 
          |  elements m !! x !! y == Material 50 = (True, 50)
          |  elements m !! x !! y == Material 100 = (True, 100)
          |  elements m !! x !! y == Material 150 = (True, 150)
          |  elements m !! x !! y == Material 1 = (True, 1)
          |  otherwise = (False, 0)

neddedEnergy :: Mine -> Point -> Int
neddedEnergy m (x, y)   
          | elements m !! x !! y == Rock = 30
          | elements m !! x !! y == Earth = 5
          | elements m !! x !! y == Material 50 = 10
          | elements m !! x !! y == Material 100 = 10
          | elements m !! x !! y == Material 150 = 10
          | elements m !! x !! y == Material 1 = 10
          | otherwise = 0

tamanhoMina :: Mine -> (Int, Int)
tamanhoMina (Mine l c xs) = (l, c)

valid :: Instr -> ConfM Bool
--L
valid L = do
  (x, y) <- current
  m <- mine
  (l, c) <- return $ tamanhoMina m
  if(y - 1 < 0) 
  then return $ False
  else do
    energia <- enoughEnergy (neddedEnergy m (x, y - 1) + 1)
    return $ energia && isNotWall m (x, y - 1)
--R
valid R = do
  (x, y) <- current
  m <- mine
  (l, c) <- return $ tamanhoMina m
  if(y + 1 > c-1) 
  then return $ False
  else do
    energia <- enoughEnergy (neddedEnergy m (x, y + 1) + 1)
    return $ energia && isNotWall m (x, y + 1)
--U
valid U = do
  (x, y) <- current
  m <- mine
  (l, c) <- return $ tamanhoMina m
  if(x - 1 < 0) 
  then return $ False
  else do
    energia <- enoughEnergy (neddedEnergy m (x - 1, y) + 1)
    return $ energia && isNotWall m (x - 1, y)
--D
valid D = do
  (x, y) <- current
  m <- mine
  (l, c) <- return $ tamanhoMina m
  if(x + 1 > l-1) 
  then return $ False
  else do
    energia <- enoughEnergy (neddedEnergy m (x + 1, y) + 1)
    return $ energia && isNotWall m (x + 1, y)
--S
valid S = return True
--C
valid C = do
  b <- enoughEnergy 10
  (x, y) <- current
  m <- mine
  return $ b && haveOre m (x, y) (tamanhoMina m)

updateMine :: Instr -> ConfM ()
--L
updateMine L = do
  b <- valid L
  m <- mine
  (x, y) <- current
  if b
    then updatePosition (x, y - 1) (x, y - 1) (snd (isMaterial m (x, y - 1))) (neddedEnergy m (x, y - 1) + 1)
    else incEnergy
--R
updateMine R = do
  b <- valid R
  m <- mine
  (x, y) <- current
  if b
    then updatePosition (x, y + 1) (x, y + 1) (snd (isMaterial m (x, y + 1))) (neddedEnergy m (x, y + 1) + 1)
    else incEnergy
--U
updateMine U = do
  b <- valid U
  m <- mine
  (x, y) <- current
  if b
    then updatePosition (x - 1, y) (x - 1, y) (snd (isMaterial m (x - 1, y))) (neddedEnergy m (x - 1, y) + 1)
    else incEnergy
--D
updateMine D = do
  b <- valid D
  m <- mine
  (x, y) <- current
  if b
    then updatePosition (x + 1, y) (x + 1, y) (snd (isMaterial m (x + 1, y))) (neddedEnergy m (x + 1, y) + 1)
    else incEnergy
--C
updateMine C = do 
  b <- valid C
  m <- mine
  (x, y) <- current
  if b
    then updatePosition (x, y) (pontoOre m (x, y)) (snd (isOre m (pontoOre m (x, y)))) (neddedEnergy m (pontoOre m (x, y)))
    else incEnergy
--S
updateMine S = do
  b <- valid S
  (x, y) <- current
  if b
    then incEnergy
    else return ()

exec :: Instr -> ConfM ()
exec x = updateMine x        

findEntry :: Mine -> Point
findEntry m = (l, c)
  where
    ls = map (elemIndex Entry) (elements m)
    jc = head $ filter (/= Nothing) ls
    l = fromMaybe (-1) (elemIndex jc ls)
    c = fromMaybe (-1) jc

initRobot :: Mine -> Robot
initRobot m =
  Robot
    { energy = 100,
      position = findEntry m,
      collected = 0
    }

run :: [Instr] -> Mine -> Mine
run is m = snd $ foldr step (initRobot m, m) (reverse is)
  where
  step :: Instr -> Conf -> Conf
  step i c = execState (exec i) c

----------------------------------------------------------------------------
--Leitura arquivo Mina

safeHead :: [a] -> Maybe a
safeHead [] = Nothing
safeHead (x : xs) = Just x

readLDM :: String -> IO (Either String Mine)
readLDM  nomeArq = do   
        contents <- readFile nomeArq
        resultado <- return (runParser pMine contents)
        resultadoTratado <- return (safeHead resultado)
        case resultadoTratado of 
            Just a -> do 
                      if validMine (fst a)
                        then return (Right (fst a))
                        else return (Left "Mina Invalida\n") 

            Nothing -> return (Left "Erro\n") 

----------------------------------------------------------------------------
--Leitura arquivo Instrução

readLCR :: String -> IO (Either String [Instr])
readLCR nomeArq = do   
        contents <- readFile nomeArq
        resultado <- return (runParser pProgram contents)
        resultadoTratado <- return (safeHead resultado)
        case resultadoTratado of 
            Just a -> return (Right (fst a))
            Nothing -> return (Left "Erro\n") 

