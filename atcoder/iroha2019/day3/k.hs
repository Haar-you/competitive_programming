
import Prelude hiding (init)
import Data.Int (Int16)
import Control.Monad (replicateM_)

inc_val :: IO ()
inc_val = putChar '+'

dec_val :: IO ()
dec_val = putChar '-'

inc_ptr :: IO ()
inc_ptr = putChar '>'

dec_ptr :: IO ()
dec_ptr = putChar '<'

get :: IO ()
get = putChar ','

put :: IO ()
put = putChar '.'

while :: IO () -> IO ()
while prc = do
  putChar '['
  prc
  putChar ']'

for :: IO () -> IO ()
for prc = do
  while $ do
    prc
    dec_val
  
init :: IO ()
init = while dec_val

assign :: Int -> IO ()
assign n = do
  init
  replicateM_ n inc_val

-- *(ptr+p) += *ptr 
add_at :: Int -> IO ()
add_at p
  | p > 0 = do
      while $ do
        replicateM_ p inc_ptr
        inc_val
        replicateM_ p dec_ptr
        dec_val
  | p < 0 = do
      while $ do
        replicateM_ (abs p) dec_ptr
        inc_val
        replicateM_ (abs p) inc_ptr
        dec_val


sub_at :: Int -> IO ()
sub_at p
  | p > 0 = do
      while $ do
        replicateM_ p inc_ptr
        dec_val
        replicateM_ p dec_ptr
        dec_val
  | p < 0 = do
      while $ do
        replicateM_ (abs p) dec_ptr
        dec_val
        replicateM_ (abs p) inc_ptr
        dec_val



move_ptr :: Int -> IO ()
move_ptr p
  | p >= 0 = replicateM_ p inc_ptr
  | p < 0 = replicateM_ (abs p) dec_ptr

move_to :: Int -> IO ()
move_to p = do
  proc_at p $ do
    init
  add_at p

move_from :: Int -> IO ()
move_from p = do
  init
  proc_at p $ do
    move_to (-p)



proc_at :: Int -> IO () -> IO ()
proc_at p prc = do
  move_ptr p
  prc
  move_ptr (-p)


copy_at :: Int -> Int -> IO ()
copy_at p temp = do
  proc_at p $ init
  proc_at temp $ init

  for $ do
    proc_at p $ do
      inc_val
      proc_at (temp-p) $ do
        inc_val
        
  move_ptr temp
  for $ do
    proc_at (-temp) $ do
      inc_val
  
  move_ptr (-temp)


add_from_to :: Int -> Int -> IO()
add_from_to f t = do
  proc_at f $ do
    add_at (t-f)

if_then :: IO () -> IO ()
if_then prc = do
  while $ do
    prc
    init

if_then_at :: Int -> IO () -> IO ()
if_then_at p prc = do
  proc_at p $ do
    if_then $ do
      proc_at (-p) $ do
        prc
    

add :: Int -> IO ()
add n
  | n > 0 = replicateM_ n $ inc_val
  | n < 0 = replicateM_ (-n) $ dec_val
  | otherwise = return ()

if_not :: Int -> IO () -> IO ()
if_not temp prc = do
  proc_at temp $ assign 1
  if_then $ do
    proc_at temp $ dec_val

  proc_at temp $ do
    if_then $ do
      dec_val
      proc_at (-temp) $ do
        prc

if_not_at :: Int -> Int -> IO () -> IO ()
if_not_at p temp prc= do
  proc_at p $ do
    if_not (temp-p) $ do
      proc_at (-temp) $ do
        prc

while_at :: Int -> IO () -> IO ()
while_at p prc = do
  proc_at p $ do
    while $ do
      proc_at (-p) $ do
        prc


le :: Int -> Int -> Int -> Int -> IO ()
le p ret temp temp2 = do
  proc_at ret $ assign 1

  for $ do
    proc_at p $ do
      copy_at (temp2-p) (temp-p)
      if_not (temp-p) $ do
        proc_at (ret-p) $ assign 0
        proc_at (-p) $ assign 1
      move_from (temp2-p)
    proc_at p $ dec_val
  proc_at p $ init

  
main :: IO ()
main = do
  solve
  putChar '\n'



solve :: IO ()
solve = do
  let base = 5
  
  -- get input
  assign 48
  copy_at 1 2
  copy_at 2 3

  proc_at (base+1) $ do
    get
  sub_at (base+1)

  proc_at (base+2) $ do
    get
  move_from 1
  sub_at (base+2)
    
  proc_at (base+3) $ do
    get
  move_from 2
  sub_at (base+3)

  get
  init

  assign 48
  copy_at 1 2
  copy_at 2 3

  proc_at (base+4) $ do
    get
  sub_at (base+4)

  proc_at (base+5) $ do
    get
  move_from 1
  sub_at (base+5)
    
  proc_at (base+6) $ do
    get
  move_from 2
  sub_at (base+6)

  -- add

  proc_at base $ do
    add_from_to 3 6
    proc_at 6 $ do
      copy_at 1 2
      proc_at 2 $ assign 9
      proc_at 1 $ le 1 2 3 4

      proc_at 3 $ do
        if_not 5 $ do
          proc_at (-3) $ add (-10)
          proc_at (-4) $ inc_val

      move_to (-3)


    add_from_to 2 5
    proc_at 5 $ do
      copy_at 1 2
      proc_at 2 $ assign 9
      proc_at 1 $ le 1 2 3 4

      proc_at 3 $ do
        if_not 5 $ do
          proc_at (-3) $ add (-10)
          proc_at (-4) $ inc_val

      move_to  (-3)

      
    add_from_to 1 4
    proc_at 4 $ do
      copy_at 1 2
      proc_at 2 $ assign 9
      proc_at 1 $ le 1 2 3 4

      proc_at 3 $ do
        if_not 5 $ do
          proc_at (-3) $ add (-10)
          proc_at (-7) $ inc_val

      move_to (-3)

  -- output

  proc_at base $ do
    proc_at 0 $ do
      add 48
      put
    proc_at 1 $ do
      add 48
      put
    proc_at 2 $ do
      add 48
      put
    proc_at 3 $ do
      add 48
      put
      
