{-# OPTIONS_GHC -Wno-incomplete-patterns #-}
{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use foldr" #-}

existsPositive :: [Int] -> Bool
existsPositive [] = False
existsPositive (x : xs) =  (x > 0) || existsPositive xs

existsPositive2 :: [Int] -> Bool
existsPositive2 (x:xs)
    | null (x:xs) = False
    | x > 0 = True
    | otherwise = existsPositive2 xs


