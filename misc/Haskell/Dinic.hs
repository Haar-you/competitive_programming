{-# LANGUAGE FlexibleContexts #-}

import Control.Monad
import Control.Monad.ST
import Control.Monad.State
import Control.Applicative
import Data.Array
import Data.Array.ST
import Data.STRef
import qualified Data.Sequence as Sq

type Node = Int
type Cost = Int
type Flow = Int
type Edge = (Node, Cost)
type Graph = Array Node [Edge]

dinic :: [(Node,Node,Flow)] -> (Node,Node) -> Node -> Node -> Flow
dinic graph bound@(lower,upper) s t = runST $ do
  cap <- newArray ((lower,lower),(upper,upper)) 0 :: ST s (STUArray s (Node,Node) Flow)
  level <- newArray bound 0 :: ST s (STUArray s Node Int)

  forM_ graph $ \(src,dst,cost) -> do
    readArray cap (src,dst) >>= \x -> writeArray cap (src,dst) (x+cost)

  let
    loop = do
      a <- buildLevel cap level
      if a then do
        f <- augment cap level
        (f+) <$> loop
        else do
        return 0
  loop

  where
    buildLevel cap level = do
      forM_ [lower..upper] $ \i -> writeArray level i 0
      
      writeArray level s 1

      let
        bfs = do
          que <- get
          unless (Sq.null que) $ do
            let (cur Sq.:< rest) = Sq.viewl que

            put rest
            curlev <- lift $ readArray level cur
            
            forM_ [lower..upper] $ \next -> do
              lev <- lift $ readArray level next
              c <- lift $ readArray cap (cur,next)

              when (lev == 0 && c > 0) $ do
                lift $ writeArray level next (curlev+1)
                modify $ (Sq.|> next)
            bfs

      runStateT bfs (Sq.singleton s)
      (/=0) <$> readArray level t

    augment cap level = do
      flow <- newSTRef 0 :: ST s (STRef s Flow)

      let
        dfs [] = return ()
        dfs path@(cur:rest) = do
          when (cur == t) $ do
            f <- minimum <$> (forM (zip path (tail path)) $ \(j,i) -> readArray cap (i,j))
            forM_ (zip path (tail path)) $ \(j,i) -> do
              readArray cap (i,j) >>= \x -> writeArray cap (i,j) (x-f)
              readArray cap (j,i) >>= \x -> writeArray cap (j,i) (x+f)
            modifySTRef flow (+f)
              
          when (cur /= t) $ do
            forM_ [lower..upper] $ \next -> do
              c <- readArray cap (cur,next)
              curlev <- readArray level cur
              nextlev <- readArray level next
        
              when (c > 0 && nextlev > curlev) $ do
                dfs (next:path)
      dfs [s]
      readSTRef flow


main = do
  return ()
