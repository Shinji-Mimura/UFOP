data Person = Person {
    name :: String,
    age :: Int
}

instance Show Person where
    show (Person x y) = show x