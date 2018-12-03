get3s :: String -> [Int]
get3s xs@(a:b:c:_) = read [a,b,c] : get3s (tail xs)
get3s _ = []

main :: IO ()
main = do
  s <- getLine
  print $ minimum $ map (abs . (subtract 753)) (get3s s)
