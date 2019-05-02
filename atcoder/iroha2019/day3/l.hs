
main :: IO ()
main = do
  let
    l = foldl1 lcm [1..1000]
    a = map (l-) [1..1000]
  putStrLn $ unwords . map show $ a
