import Control.Monad

main :: IO ()
main = do
  xs <- replicateM 5 $ readLn :: IO [Int]
  let ys = map ((*10) . ceiling . (/10) . fromIntegral) xs
  let ans = sum ys - (maximum $ zipWith (-) ys xs)
  
  print $ ans
