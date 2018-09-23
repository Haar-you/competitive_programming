import Control.Monad
import Control.Monad.State
import Control.Applicative
import Data.List
import qualified Data.Map as Map

main :: IO ()
main = do
  s <- getLine
  t <- getLine

  let
    m1 = map (map head . group . sort . snd) $ Map.toList $ (f s t) `execState` (Map.empty)
    m2 = map (map head . group . sort . snd) $ Map.toList $ (f t s) `execState` (Map.empty)

  putStrLn $ if all ((==1) . length) m1 && all ((==1) . length) m2 then "Yes" else "No"

f :: [Char] -> [Char] -> State (Map.Map Char [Char]) ()
f [] [] = return ()
f (x:xs) (y:ys) = do
  mp <- get
  if x `Map.member` mp then
    put $ Map.insert x (y : (mp Map.! x)) mp
    else
    put $ Map.insert x [y] mp
  f xs ys
