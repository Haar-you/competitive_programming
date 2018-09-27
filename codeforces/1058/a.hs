import Control.Applicative

main = do
  getLine
  putStrLn =<< (\x -> if x then "EASY" else "HARD") . all (==0) . map read . words <$> getLine
