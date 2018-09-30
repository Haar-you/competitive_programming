main = putStrLn =<< map (\c -> if c=='1' then '9' else '1') <$> getLine
