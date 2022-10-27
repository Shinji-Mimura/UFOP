{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Eta reduce" #-}
bools :: [Bool]
bools = [True]

nums :: [[Int]]
nums = [[1]]

add :: Int -> Int -> Int -> Int
add x y z = x + y + z

copy :: a -> (a, a)
copy x = (x, x)

apply :: (a -> b) -> a -> b
apply f x = f x

swap :: (a, b) -> (b , a)
swap (x, y) = (y, x)