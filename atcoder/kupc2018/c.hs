import Control.Monad
import Debug.Trace
import Data.List

main = do
  let ans =
        [
          "......#..",
          "..#......",
          "#......#.",
          ".....#...",
          "....#....",
          "...#.....",
          ".#......#",
          "......#..",
          "..#......"
        ]

  mapM_ putStrLn ans


