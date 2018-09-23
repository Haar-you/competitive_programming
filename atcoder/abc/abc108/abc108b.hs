import Control.Applicative
import Text.Printf

main :: IO ()
main = do
  [x1,y1,x2,y2] <- map read . words <$> getLine :: IO [Int]
  let
    dy = y2 - y1
    dx = x2 - x1

  printf "%d %d %d %d\n" (x2 - dy) (y2 + dx) (x1 - dy) (y1 + dx)
  
