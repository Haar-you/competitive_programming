
diff [] _ = 0
diff _ [] = 0
diff (x:xs) (y:ys) = (if x/=y then 1 else 0) + diff xs ys


main = do
  s <- getLine

  print $ min (diff s $ cycle "01") (diff s $ cycle "10")
  
