import Control.Applicative
import Data.List
import Data.Ord
import Text.Printf

main :: IO ()
main = do
  n <- readLn :: IO Int
  dat <- reverse . sortBy (comparing (\[_,_,h] -> h)) . map (map read . words) . lines <$> getContents :: IO [[Int]]

  let
    ([x1,y1,h1]:rest) = dat
    solve cx cy = (all (\[x,y,h] -> h == max (height - abs (x-cx) - abs (y-cy)) 0) rest, height)
      where
        height = h1 + abs (x1-cx) + abs (y1-cy)

    (ax,ay,ah) = head [(x,y,h) | x<-[0..100], y<-[0..100], let (t,h) = solve x y, t]
  
  printf "%d %d %d\n" ax ay ah
