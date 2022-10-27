{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use foldr" #-}

minList :: [Double] -> Double
minList [x] = x
minList (x:xs) = min x (minList xs)
minList [] = error "Empty List"