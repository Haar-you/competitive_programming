import Control.Applicative
import Control.Monad.State
import Data.List
import Data.Maybe
import qualified Data.ByteString.Char8 as BS
import Data.Array.IO.Safe
import qualified Data.Set as Set

readIntBS = fst . fromJust . BS.readInt

main = do
  [n,m,d] <- map read . words <$> getLine :: IO [Int]
  as <- map read . words <$> getLine :: IO [Int]

  check <- newArray (1,n) 0 :: IO (IOUArray Int Int)

  let
    set = Set.fromList $ zip as [1..]

    solve :: Int -> StateT (Set.Set (Int,Int)) IO Int
    solve day = do
      set <- get
      if Set.null set then
        return (day-1)

        else do
        let ((mn,i), set_) = Set.deleteFindMin set
        put set_

        lift $ writeArray check i day

        let
          aux k = do
            res <- Set.lookupGT (k+d+1,0) <$> get
            case res of
              Just (b, j) -> do
                modify $ Set.delete (b, j)
                lift $ writeArray check j day
                aux b
              Nothing -> return ()

        aux mn
        solve (day+1)


  print =<< evalStateT (solve 1) set
  putStrLn =<< unwords . map show <$> getElems check
