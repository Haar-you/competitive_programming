import Control.Applicative
import Data.Char

main = do
  n <- readLn :: IO Int
  as <- map digitToInt <$> getLine
  let s = sum as

  putStrLn $ if or [solve (s`div`i) as | i<-[2..n], s`mod`i==0] then "YES" else "NO"

  where
    solve _ [] = True
    solve x as =
      case aux x 0 as of
        Just bs -> solve x bs
        Nothing -> False

    aux y s [] = if y == s then Just [] else Nothing
    aux y s (b:bs)
      | s+b == y = if bs /= [] && head bs == 0 then aux y (s+b) bs else Just bs
      | s+b > y = Nothing
      | s+b < y = aux y (s+b) bs
