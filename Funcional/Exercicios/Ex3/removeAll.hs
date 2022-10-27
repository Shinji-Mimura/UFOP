removeAll :: Int -> [Int] -> [Int]
removeAll _ [] = []
removeAll y (x:xs) = if y == x then removeAll y xs else x : removeAll y xs