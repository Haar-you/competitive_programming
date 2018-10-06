import Control.Monad

main :: IO ()
main = do
  n <- readLn :: IO Int

  when (n==1) $ putStrLn "Hello World"
  when (n==2) $ print =<< (+) <$> readLn <*> readLn
  
