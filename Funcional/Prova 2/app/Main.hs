module Main (main) where

import Robot
import System.Environment (getArgs)

{- 
stack build
stack exec prova02-exe 
stack exec prova02-exe data/mina.txt data/instrucoes.txt
-}

main :: IO ()
main = do
          args <- getArgs
          doIt args

doIt :: [String] -> IO ()
doIt [fm , fr]
   = do
        pm <- readLDM fm
        pr <- readLCR fr
        let
           m = either error id pm
           r = either error id pr
           m' = run r m
        print m'
doIt _ = putStrLn "Informe dois arquivos de entrada!"