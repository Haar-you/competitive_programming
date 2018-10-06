import Control.Applicative
import Data.List
import qualified Data.Vector.Unboxed as VU

main :: IO ()
main = do
  [n,m] <- map read . words <$> getLine :: IO [Int]

  let
    sqm = ceiling $ sqrt (fromIntegral m)
    divs = [i | i<-[1..sqm], m`mod`i==0]
    divisors = VU.fromList $ divs ++ map (\d -> m`div`d) (reverse divs)
    l = VU.length divisors

    aux i = m `div` (divisors VU.! i) >= n
    solve l r
      | l == r = l
      | l + 1 == r = if aux r then r else l
      | otherwise =
          let
            m = (l+r)`div`2
          in
            if aux m then
              solve m r
            else
              solve l m
  
  print $ divisors VU.! (solve 0 (l-1))
  
