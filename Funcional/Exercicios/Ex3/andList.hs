{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Redundant bracket" #-}
{-# HLINT ignore "Use foldr" #-}
andList :: [Bool] -> Bool
andList [] = True
andList (x:xs) = x && (andList xs)