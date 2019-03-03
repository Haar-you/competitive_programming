import qualified Data.ByteString.Char8 as BS

main :: IO ()
main = do
  s <- BS.getLine

  print $ (*2) $ min (BS.count '0' s) (BS.count '1' s)
