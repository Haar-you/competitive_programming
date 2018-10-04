import Data.List
import Text.Printf

main = do
  s <- getLine

  let ans = solve s

  if ans == [] then
    print $ -1
    else
    mapM_ (\(a,b) -> printf "%d %d\n" a b) ans

solve s
  | length s == 2 = if s == "10" then [(1,2)] else []
  | otherwise = if last s == '0' && head s == '1' && last (init s) == '1' then
                  if isPalindrome (init s) then
                    aux 1 1 (fst $ splitAt (length s`div`2) (init s))
                  else
                    []
                else
                  []
  where
    aux root cur [] = [(root,i) | i<-[cur+1..length s]]
    aux root cur (x:xs) = if x == '1' then (root,cur+1) : aux (cur+1) (cur+1) xs else (root,cur+1) : aux root (cur+1) xs

isPalindrome xs = xs == reverse xs
