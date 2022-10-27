isPrime :: Int -> Bool
isPrime n  =  [n] == take 1 [i | i <- [2..n], mod n i == 0]

withoutPrimes :: [Int] -> [Int]
withoutPrimes x = filter isPrime x