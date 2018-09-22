import Control.Monad
import Control.Applicative
import Text.Printf


main = do
  n <- readLn :: IO Int

  printf "%d %d %d\n" (1::Int) (1+(if (n-2)`mod`3==0 then 1 else 0) :: Int) (n-2-(if (n-2)`mod`3==0 then 1 else 0))
