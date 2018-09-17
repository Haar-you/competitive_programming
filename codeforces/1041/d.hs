import Control.Applicative
import Data.List
import Data.Maybe
import qualified Data.ByteString.Char8 as BS
import Data.Array.Unboxed

readIntBS = fst . fromJust . BS.readInt

main = do
  [n,h] <- map read . words <$> getLine :: IO [Int]
  seg <- map (map readIntBS . BS.words) . BS.lines <$> BS.getContents :: IO [[Int]]

  let
    arr = listArray (0,n) $ scanl (+) 0 (map (\[x1,x2] -> x2-x1) seg) :: UArray Int Int
    arr2 = listArray (0,n) $ scanl (+) 0 $ zipWith (\[x1,x2] [y1,y2] -> y1-x2) seg (tail seg) ++ [2*10^9] :: UArray Int Int

  print $ maximum $ (flip map) (zip [1..] seg) $
    \(i,[x1,x2]) -> let j = lowerBound arr2 (arr2!(i-1)+h) i n in arr!j - arr!(i-1)+h
  

lowerBound :: UArray Int Int -> Int -> Int -> Int -> Int
lowerBound arr x lower upper = lowerBound' lower upper
  where
    lowerBound' l r
      | r - l <= 1 = if arr!l < x then r else l
      | otherwise = let m = div (l+r) 2 in
                      if arr!m < x then
                        lowerBound' m r
                      else
                        lowerBound' l m
