{-# LANGUAGE FlexibleContexts #-}

import Control.Applicative
import Control.Monad.ST
import Control.Monad.State
import Control.Monad
import Data.Array.ST
import Data.List
import Data.Array
import qualified Data.Set as Set

type Node = Int
type Cost = Int
type Edge = (Node, Cost)
type Graph = Array Node [Edge]
type Route = [Edge]

inf = maxBound :: Int

dijkstra :: Graph -> Node -> Array Node Cost
dijkstra graph start = runST $ do
  cost <- newArray (bounds graph) inf :: ST s (STUArray s Node Cost)
  check <- newArray (bounds graph) False :: ST s (STUArray s Node Bool)
  writeArray cost start 0
  evalStateT (dijkstra' cost check) (Set.singleton (0, start))
  freeze cost
  where
    dijkstra' cost check = do
      isNull <- Set.null <$> get
      when (not $ isNull) $ do
        (curCost, cur) <- state Set.deleteFindMin
        let nextNodes = graph ! cur

        lift $ writeArray check cur True

        forM_ nextNodes $ \(next, edgeCost) -> do
          nextCost <- lift $ readArray cost next
          
          if nextCost == -1 then do
            lift $ writeArray cost next (curCost + edgeCost)
            modify $ Set.insert (curCost + edgeCost, next)
            else do
            when (curCost + edgeCost < nextCost) $ lift $ writeArray cost next (curCost + edgeCost)
            isChecked <- lift $ readArray check next
            unless isChecked $ do
              (\x -> modify $ \s -> Set.insert (x, next) $ Set.delete (nextCost, next) s) =<< (lift $ readArray cost next)
        dijkstra' cost check

main :: IO ()
main = do
  return ()

