{-# LANGUAGE FlexibleContexts #-}

import Data.Array.ST
import Data.Array
import Data.List
import Data.Ord
import qualified Data.ByteString.Char8 as BS
import Data.Maybe
import Control.Monad
import Control.Monad.ST
import Control.Monad.State
import Control.Applicative

{--
Union-Findは別に用意する。
--}


type Node = Int
type Cost = Int
type Edge = (Node, Node, Cost)

kruskal :: [Node] -> [Edge] -> [Edge]
kruskal nodes edges = runST $ do
  let sorted = sortBy (\(_,_,c1) (_,_,c2) -> compare c1 c2) edges
  uf <- newUF (length nodes)
  execStateT (kruskal' uf sorted) []
  where
    kruskal' _ [] = return ()
    kruskal' uf (e@(i,j,c):rest) = do
      isSame <- lift $ sameUF uf i j
      unless isSame $ do
        lift $ uniteUF uf i j
        modify (e:)
      kruskal' uf rest

main :: IO ()
main = do
  return ()
