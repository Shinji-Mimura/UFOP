data Person = Person {
    name :: String,
    age :: Int
}

instance Eq Person where
    (Person x y) == (Person x' y') = x == x'
    x /= y = not (x == y)
