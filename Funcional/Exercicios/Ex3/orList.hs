{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Redundant bracket" #-}
{-# HLINT ignore "Use foldr" #-}
orList :: [Bool] -> Bool
orList [] = False
orList (x:xs) = x || (orList xs)