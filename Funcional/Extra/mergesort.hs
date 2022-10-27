{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use :" #-}
{-# HLINT ignore "Fuse foldr/map" #-}
mergesort :: Ord a => [a] -> [a]
mergesort xs = foldr merge [] (map (\x -> [x]) xs)

merge :: Ord a => [a] -> [a] -> [a]
merge xs [] = xs
merge [] ys = ys
merge (x:xs) (y:ys) | x <= y    = x:merge xs (y:ys)
                    | otherwise = y:merge (x:xs) ys