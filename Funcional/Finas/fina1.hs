{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Avoid lambda using `infix`" #-}
{-# HLINT ignore "Avoid lambda" #-}
import Data.Char
count :: (a -> Bool) -> [a] -> Int
count _ [] = 0
count p (x : xs) = if p x then 1 + count p xs else count p xs

divide :: Int -> [a] -> ([a], [a])
divide 0 xs = ([], xs)
divide _ [] = ([], [])
divide n (x : xs) = (x : ls1, ls2)
    where
        (ls1, ls2) = divide (n-1) xs

capitalize :: String -> String
capitalize "" = ""
capitalize xs = ls3
    where
        ls = words xs
        ls2 = map (\(y:ys) -> toUpper y : ys) ls
        ls3 = tail $ concatMap (\x -> ' ' : x) ls2

