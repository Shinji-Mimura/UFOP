{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use foldr" #-}
myconcatMap :: (a -> [b]) -> [a] -> [b]
myconcatMap p [] = []
myconcatMap p (x:xs) = p x ++ myconcatMap p xs

myconcatMap' :: (a -> [b]) -> [a] -> [b]
myconcatMap' p = foldr step []
    where
        step x ac = p x ++ ac
