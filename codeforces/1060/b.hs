import Control.Applicative
import Data.Char
import Data.Int

sumDigits n = sum . map digitToInt . show $ n

main = do
  n <- readLn :: IO Int64
  let k = 10 ^ (floor $ logBase (10::Double) (fromIntegral n))
  print $ maximum [sumDigits m + sumDigits (n-m) | i<-[1..10], let m = i*k-1, m<=n]
