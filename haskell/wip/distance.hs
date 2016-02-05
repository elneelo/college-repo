type Point = (Int,Int)

absValue :: Int -> Int
absValue n | n >= 0    = n
           | otherwise = -n

intSquareRoot :: Int -> Int
intSquareRoot n = try n where
  try i   | i*i > n   = try (i - 1) 
          | i*i <= n  = i

distance :: Point -> Point -> Int
--distance _ _ = 42
distance (0,0) (0,0) = 0
distance (0,0) (x,y) = absValue( intSquareRoot( (x*x) + (y*y) ) )
distance (a,b) (0,0) = absValue( intSquareRoot( (a*a) + (b*b) ) )
distance (a,b) (x,y) = absValue( intSquareRoot( ( (x-a)*(x-a) ) + (y-b)*(y-b) ) )