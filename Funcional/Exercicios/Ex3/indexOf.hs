indexOf :: Int -> [Int] -> Int
indexOf a xs = indexOf' a 0 xs

indexOf' :: Int -> Int -> [Int] -> Int
indexOf' _ _ [] = -1
indexOf' a i (x:xs) = if a == x then i else indexOf' a (i+1) xs 


-- indexOf :: Int -> [Int] -> Int
-- indexOf _ [] = -1
-- indexOf 0 (x:xs) = x
-- indexOf a (x:xs) = indexOf (a-1) xs
