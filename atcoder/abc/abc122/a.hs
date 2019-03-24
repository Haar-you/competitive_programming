
main :: IO ()
main = do
  c <- getChar
  putChar $
    case c of
      'A' -> 'T'
      'T' -> 'A'
      'C' -> 'G'
      'G' -> 'C'
  putStrLn ""
  
