takeWhile :: (a -> Bool) -> [a] -> [a]
takeWhile p = foldr step []
    where
        step x ac = if p x then x : ac else ac