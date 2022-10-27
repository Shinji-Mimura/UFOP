myall :: (a -> Bool) -> [a] -> Bool
myall _ [] = True
myall p (x:xs) = p x && myall p xs

myall' :: (a -> Bool) -> [a] -> Bool
myall' p = foldr step True
    where
        step x ac = p x && ac
