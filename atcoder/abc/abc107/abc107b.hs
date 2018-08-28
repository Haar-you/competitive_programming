import Data.List
import Control.Applicative

f = transpose . filter (elem '#')
main = getLine >> getContents >>= mapM_ putStrLn . f . f . lines
