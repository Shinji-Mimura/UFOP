{-# HLINT ignore "Use camelCase" #-}
{-# OPTIONS_GHC -Wno-incomplete-patterns #-}
{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}

type Name = String

type Surname = String

type SendOffer = Bool

data Client = Customer
  { name :: Name,
    surname :: Surname,
    offers :: SendOffer
  }

c1 = Customer "a" "1" False

c2 = Customer "b" "2" True

c3 = Customer "c" "3" True

lc = [c1, c2, c3]

name_values = name

print_all_clients :: [Client] -> [String]
print_all_clients = map name

wantOffer :: [Client] -> [Client]
wantOffer [] = []
wantOffer (x : xs) = if offers x then x : wantOffer xs else wantOffer xs