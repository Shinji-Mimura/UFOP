data Vec3 = Vec3 Int Int Int

instance Eq Vec3 where
  (Vec3 x y z) == (Vec3 x' y' z') = x == x' && y == y' && z == z'
  x /= y = not (x == y)
