import Control.Monad.State
import Control.Monad

main = do
  [n,m,p,q] <- map read . words <$> getLine :: IO [Int]

  let
    solve :: Int -> State Int Int
    solve i = do
      r <- get
      if r > 0 then do
        if i`mod`12 >= p-1 && i`mod`12 < p+q-1 then
          modify $ \x -> x-2*m
          else
          modify $ \x -> x-m
        solve (i+1)

        else
        return $ i

  print $ evalState (solve 0) n
    
