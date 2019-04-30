import Data.List

main :: IO ()
main = do
  [n,x,y] <- map read . words <$> getLine :: IO [Int]
  as <- flip zip [0..] . reverse . sort . map read . words <$> getLine :: IO [(Int,Int)]
  

  let
    takahashi = x + (sum . map fst . filter (\(p,i) -> i`mod`2==0)) as
    aoki = y + (sum . map fst . filter (\(p,i) -> i`mod`2==1)) as

  putStrLn $
    if takahashi > aoki then
      "Takahashi"
    else if takahashi < aoki then
      "Aoki"
    else
      "Draw"
