import Control.Applicative
import Data.List
import Text.Printf
import Data.Ratio
import Data.Array.IO.Safe
import Control.Monad
import Data.Int
import Data.Maybe
import qualified Data.ByteString.Char8 as BS

readIntBS = fst . fromJust . BS.readInt

main = do
  n <- readLn :: IO Int
  as <- map readIntBS . BS.words <$> BS.getLine :: IO [Int]

  let
    countNeg = length . filter (<0) $ as
    countZero = length . filter (==0) $ as
    countPos = length . filter (>0) $ as

    positives = map snd . filter ((>0) . fst) $ zip as ([1..] :: [Int])
    negatives = map snd . filter ((<0) . fst) $ zip as ([1..] :: [Int])
    zeros = map snd . filter ((==0) . fst) $ zip as ([1..] :: [Int])
    maxneg = maximum $ filter (<0) as
    maxnegpos = if null negatives then Nothing else fmap (+1) (elemIndex maxneg as)


  if countZero == 0 && countNeg == 0 then do
    forM_ (f $ positives) $ \(a,b) -> printf "1 %d %d\n" a b

    else if odd countNeg then do
    forM_ (f $ reverse $ (fromJust maxnegpos) : zeros) $ \(a,b) -> printf "1 %d %d\n" a b
    unless (countZero == n-1 && countNeg == 1) $ printf "2 %d\n" (fromJust maxnegpos)
    forM_ (f $ positives ++ (delete (fromJust maxnegpos) negatives)) $ \(a,b) -> printf "1 %d %d\n" a b

    else do
    forM_ (f $ zeros) $ \(a,b) -> printf "1 %d %d\n" a b
    unless (countZero == 0 || countZero == n) $ printf "2 %d\n" (last zeros)
    forM_ (f $ positives ++ negatives) $ \(a,b) -> printf "1 %d %d\n" a b
    
f xs = zip xs (tail xs)
