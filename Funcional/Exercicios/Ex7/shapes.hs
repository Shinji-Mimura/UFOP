{-# OPTIONS_GHC -Wno-incomplete-patterns #-}

import Distribution.Simple.Program.HcPkg (list)

data Point = Point Float Float

dist :: (Point, Point) -> Float
dist (Point x1 y1, Point x2 y2) =
  sqrt (x11 * x11 + y11 * y11)
  where
    x11 = x1 - x2
    y11 = y1 - y2

data Shape
  = Rectangle Point Float Float
  | Circle Point Float
  | Triangle Point Point Point

semiP :: Shape -> Float
semiP (Triangle a b c) = dist (a, b) + dist (a, c) + dist (b, c) / 2

isEquilatero :: Point -> Point -> Point -> Bool
isEquilatero a b c = dist (a, b) == dist (b, c) && dist (b, c) == dist (a, c)

isIsoceles :: Point -> Point -> Point -> Bool
isIsoceles a b c = dist (a, b) == dist (b, c) && dist (b, c) /= dist (a, c)

isEscaleno :: Point -> Point -> Point -> Bool
isEscaleno a b c = dist (a, b) /= dist (b, c) && dist (b, c) /= dist (a, c) && dist (a, b) /= dist (a, c)

listOfPoints :: Point -> Point -> Point -> [Float]
listOfPoints a b c = [dist (a, b), dist (a, c), dist (b, c)]

escalenoArea :: Point -> Point -> Point -> Float
escalenoArea a b c = bi * hi / 2
  where
    bi = minimum (listOfPoints a b c)
    hi = maximum (listOfPoints a b c)

surface :: Shape -> Float
surface (Rectangle _ w h) = w * h
surface (Circle _ r) = 3.14 * r * r
surface (Triangle a b c)
  | isEquilatero a b c = (dist (a, b) * dist (a, b) * sqrt 3) / 4
  | isEscaleno a b c = escalenoArea a b c
  | isIsoceles a b c = 0.0