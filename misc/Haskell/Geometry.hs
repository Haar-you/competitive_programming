{-# LANGUAGE FlexibleContexts #-}
{-# LANGUAGE MultiWayIf #-}

import Data.List
import Data.Complex
import Control.Applicative
import Control.Monad
import Control.Monad.State
import Text.Printf
import Debug.Trace
import Numeric
import Data.Ord
import qualified Data.Set as Set
import Data.Maybe


type Point2D = Complex Double
type Line2D = (Point2D, Point2D)
type Segment2D = (Point2D, Point2D)
type Circle2D = (Point2D, Double)
type Polygon2D = [Point2D]

eps = 10**(-9)

size2D :: Point2D -> Double
size2D = realPart . abs

dot2D :: Point2D -> Point2D -> Double
dot2D (x1:+y1) (x2:+y2) = x1*x2+y1*y2

cross2D :: Point2D -> Point2D -> Double
cross2D (x1:+y1) (x2:+y2) = x1*y2-y1*x2

unit2D :: Point2D -> Point2D
unit2D p = p / (abs p)

normal2D :: Point2D -> Point2D
normal2D = (* (0:+1))

scale2D :: Point2D -> Double -> Point2D
scale2D (x:+y) a = (a*x):+(a*y)

sizeSq2D :: Point2D -> Double
sizeSq2D (x:+y) = x*x+y*y

eqDbl x y = abs (x-y) < eps

eqPt (x1:+y1) (x2:+y2) = x1 `eqDbl` x2 && y1 `eqDbl` y2


angleDiff :: Point2D -> Point2D -> Double
angleDiff p1 p2
  | a < -pi = a + 2*pi
  | a > pi = a - 2*pi
  | otherwise = a
  where a = phase p2 - phase p1


projection :: Line2D -> Point2D -> Point2D
projection (p1,p2) p = p1 + (((unit2D $ p2-p1) `dot2D` (p-p1)) :+ 0) * (unit2D $ p2-p1)

reflection :: Line2D -> Point2D -> Point2D
reflection (p1,p2) p = p + (projection (p1,p2) p - p) * 2

data CCW = ONLINE_BACK | COUNTER_CLOCKWISE | ON_SEGMENT | CLOCKWISE | ONLINE_FRONT deriving (Show, Enum, Eq)

ccw :: Point2D -> Point2D -> Point2D -> CCW
ccw p0 p1 p2
  | abs cr < eps =
    if
      | dot < 0 -> ONLINE_BACK
      | size2D (p2-p0) > size2D (p1-p0) -> ONLINE_FRONT
      | otherwise -> ON_SEGMENT
  | cr > 0 = COUNTER_CLOCKWISE
  | cr < 0 = CLOCKWISE
  where
    cr = cross2D (p1-p0) (p2-p0)
    dot = dot2D (p1-p0) (p2-p0)

ccwEnum :: Point2D -> Point2D -> Point2D -> Int
ccwEnum p0 p1 p2 = (+(-2)) . fromEnum $ ccw p0 p1 p2


parallelLine :: Line2D -> Line2D -> Bool
parallelLine (p1,p2) (p3,p4) = abs ((p2-p1) `cross2D` (p4-p3)) < eps

orthogonalLine :: Line2D -> Line2D -> Bool
orthogonalLine (p1,p2) (p3,p4) = abs ((p2-p1) `dot2D` (p4-p3)) < eps



intersectSegments :: Segment2D -> Segment2D -> Bool
intersectSegments (p1,p2) (p3,p4) =
  ccwEnum p1 p2 p3 * ccwEnum p1 p2 p4 <= 0 &&
  ccwEnum p3 p4 p1 * ccwEnum p3 p4 p2 <= 0

intersectSegmentLine :: Segment2D -> Line2D -> Bool
intersectSegmentLine (s1,s2) (l1,l2) = ((l2-l1) `cross2D` (s1-l1)) * ((l2-l1) `cross2D` (s2-l1)) < eps

intersectLinePoint :: Line2D -> Point2D -> Bool
intersectLinePoint (l1,l2) p = abs ((l2-l1) `cross2D` p) < eps


crosspointSegments :: Segment2D -> Segment2D -> Either String Point2D
crosspointSegments (p1,p2) (p3,p4)
  | abs cr < eps = Left "Parallel"
  | t1 + eps < 0 || t1 - eps > 1 || t2 + eps < 0 || t2 - eps > 1 = Left "No crosspoint"
  | otherwise = Right $ p1 + (p2-p1) * (t1 :+ 0)
  where
    cr = ((p2-p1) `cross2D` (p4-p3))
    t1 = ((p3-p1) `cross2D` (p4-p3)) / cr
    t2 = ((p3-p1) `cross2D` (p2-p1)) / cr


data Position = LeftSide | RightSide | Parallel deriving Show

crosspointSegmentLine :: Segment2D -> Line2D -> Either Position Point2D
crosspointSegmentLine (s1,s2) (l1,l2)
  | abs a <= eps && abs b <= eps = Left Parallel
  | a < 0 && b < 0 = Left RightSide
  | a > 0 && b > 0 = Left LeftSide
  | otherwise = Right $ s1 + (s2-s1) `scale2D` (((l2-l1)`cross2D`(l1-s1))/((l2-l1)`cross2D`(s2-s1)))
  where
    a = ((l2-l1) `cross2D` (s1-l1))
    b = ((l2-l1) `cross2D` (s2-l1))

crosspointLinePoint :: Line2D -> Point2D -> Either Position Point2D
crosspointLinePoint (l1,l2) p
  | abs a < eps = Right p
  | a < 0 = Left RightSide
  | a > 0 = Left LeftSide
  where
    a = (l2-l1) `cross2D` (p-l1)

distanceSegmentPoint :: Segment2D -> Point2D -> Double
distanceSegmentPoint (p1,p2) p
  | (p2-p1) `dot2D` (p-p1) < eps = size2D (p-p1)
  | (p1-p2) `dot2D` (p-p2) < eps = size2D (p-p2)
  | otherwise = (abs $ (p2-p1) `cross2D` (p-p1)) / (size2D (p2-p1))

distanceSegments :: Segment2D -> Segment2D -> Double
distanceSegments (p1,p2) (p3,p4)
  | intersectSegments (p1,p2) (p3,p4) = 0
  | otherwise = minimum [distanceSegmentPoint (p1,p2) p3, distanceSegmentPoint (p1,p2) p4,
                         distanceSegmentPoint (p3,p4) p1, distanceSegmentPoint (p3,p4) p2]

distanceLinePoint :: Line2D -> Point2D -> Double
distanceLinePoint (l1,l2) p = abs ((l2-l1) `cross2D` (p-l1)) / size2D (l2-l1)

area :: Polygon2D -> Double
area ps = (/2) . abs . sum $ zipWith (\(x1:+y1) (x2:+y2) -> (x1-x2)*(y1+y2)) ps (last ps : init ps)

isConvex :: Polygon2D -> Bool
isConvex ps = aux2 cs
  where
    rot ps = last ps : init ps
    cs = zipWith3 (\p1 p2 p3 -> ccwEnum p1 p2 p3) ps (rot ps) (rot . rot $ ps)
    aux1 _ [] = True
    aux1 a (x:xs) = if x == a || x == 2 then aux1 a xs else False
    aux2 [] = True
    aux2 (x:xs) = case x of
                    1 -> aux1 1 xs
                    -1 -> aux1 (-1) xs
                    _ -> aux2 xs


-- 0: outside, 1: on segment, 2: inside
includePoint :: Polygon2D -> Point2D -> Int
includePoint ps p@(px:+py) = case aux (zip ps (last ps : init ps)) of
                               Left x ->  x
                               Right x -> if abs (abs x - 2*pi) < eps then 2 else 0 
  where
    aux :: [(Point2D,Point2D)] -> Either Int Double
    aux [] = Right 0
    aux ((a@(ax:+ay),b@(bx:+by)):rest)
      | ccw a b p == ON_SEGMENT = Left 1
      | otherwise = fmap ((if abs ang < pi then ang else -2*pi*(signum ang)+ang) +) (aux rest)
      where
        pa = let t = atan2 (ay-py) (ax-px) in if t < eps then t + 2*pi else t
        pb = let t = atan2 (by-py) (bx-px) in if t < eps then t + 2*pi else t
        ang = pb - pa


convexHull :: [Point2D] -> Polygon2D
convexHull ps = (aux [] sorted) ++ (aux [] (reverse sorted))
  where
    sorted = sortBy (comparing imagPart) ps
    aux list@(p1:p2:rest) (x:xs) = case ccw p2 p1 x of
                                COUNTER_CLOCKWISE -> aux (x:list) xs
                                ONLINE_FRONT -> aux (x:list) xs
                                CLOCKWISE -> aux (p2:rest) (x:xs)
                                ON_SEGMENT -> aux list xs
                                ONLINE_BACK -> aux (p2:rest) (x:xs)
    aux list (x:xs) = aux (x:list) xs
    aux list [] = reverse $ tail list

convexDiameter :: Polygon2D -> Double
convexDiameter ps = aux (zip ba (tail ba)) (zip dc (tail dc)) (size2D $ ymax - ymin)
  where
    ymin = minimumBy (comparing imagPart) ps
    ymax = maximumBy (comparing imagPart) ps
    (a,b) = break (==ymin) ps
    (c,d) = break (==ymax) ps
    ba = b ++ a
    dc = d ++ c

    aux _ [] mx = mx
    aux [] _ mx = mx
    aux ((x,xn):xs) ((y,yn):ys) mx
      | (xn-x) `cross2D` (yn-y) >= 0 = aux ((x,xn):xs) ys (max mx $ size2D (yn - x))
      | otherwise = aux xs ((y,yn):ys) (max mx $ size2D (xn - y))


convexCut :: Polygon2D -> Line2D -> (Polygon2D, Polygon2D)
convexCut ps (l1,l2) = aux (zip (last ps : init ps) ps) [] [] Nothing
  where
    aux [] left right _ = (left, right)
    aux ((x1,x2):xs) left right pos =
      case crosspointSegmentLine (x1,x2) (l1,l2) of
        Left LeftSide -> aux xs (x1:left) right (Just LeftSide)
        Left RightSide -> aux xs left (x1:right) (Just RightSide)
        Left Parallel -> case pos of
                           Just LeftSide -> aux xs (x1:left) right (Just LeftSide)
                           Just RightSide -> aux xs left (x1:right) (Just RightSide)
                           Nothing -> aux xs (x1:left) (x1:right) Nothing
        Right p -> case pos of
          Just LeftSide ->
            if p `eqPt` x2 then
              aux xs (x1:left) right (Just LeftSide) 
            else
              aux xs (p:x1:left) (p:right) (Just RightSide)
          Just RightSide ->
            if p `eqPt` x2 then
              aux xs left (x1:right) (Just RightSide)
            else
              aux xs (p:left) (p:x1:right) (Just LeftSide)
          Nothing -> case crosspointLinePoint (l1,l2) x1 of
            Left LeftSide ->
              if p `eqPt` x2 then
                aux xs (x1:left) right (Just LeftSide)
              else
                aux xs (p:x1:left) (p:right) (Just RightSide)
            Left RightSide ->
              if p `eqPt` x2 then
                aux xs left (x2:right) (Just RightSide)
              else
                aux xs (p:left) (p:x1:right) (Just LeftSide)
            Right _ -> case crosspointLinePoint (l1,l2) x2 of
              Left LeftSide -> aux xs (p:left) (p:right) (Just LeftSide)
              Left RightSide -> aux xs (p:left) (p:right) (Just RightSide)

manhattanCrossing :: [Segment2D] -> Int
manhattanCrossing segs = evalState (aux sortedhs sortedvs) (Set.empty) 
  where
    (hs,vs) = partition (\(sx:+sy,tx:+ty) -> abs (sy - ty) < eps) segs
    sortedhs = sortBy (comparing (imagPart . fst)) hs
    sortedvs = sortBy (comparing (imagPart . fst)) . concat . map (\(s@(sx:+sy),t@(tx:+ty)) -> [(s,sy<ty),(t,sy>ty)]) $ vs

    aux [] _ = return 0
    aux _ [] = return 0
    aux hors vers = do
      let
        ymin = min (imagPart . fst . head $ hors) (imagPart . fst . head $ vers)
        (rs,rrest) = span (\(_:+y,_) -> abs (ymin-y) < eps) hors
        (ps,prest) = span (\(_:+y,_) -> abs (ymin-y) < eps) vers

      forM_ ps $ \((x:+_),b) -> do
        when b $ do
          modify $ Set.insert x

      cr <- sum <$> do
        forM (map (\(x1:+_,x2:+_) -> (min x1 x2, max x1 x2)) rs) $ \(x1,x2) -> do
          fx1 <- Set.lookupGE x1 <$> get
          fx2 <- Set.lookupGT x2 <$> get

          case fx1 of
            Just gx1 -> do
              case fx2 of
                Just gx2 -> (\set -> (fromJust $ Set.lookupIndex gx2 set) - (fromJust $ Set.lookupIndex gx1 set)) <$> get
                Nothing -> (\set -> Set.size set - (fromJust $ Set.lookupIndex gx1 set)) <$> get
            Nothing -> return 0

      forM_ ps $ \((x:+_),b) -> do
        when (not b) $ do
          modify $ Set.delete x

      (cr+) <$> aux rrest prest


data Relation = Same | Inside | Inscribed | Intersect | Circumscribed | Outside deriving Show

intersectCircles :: Circle2D -> Circle2D -> Relation
intersectCircles (c1,r1) (c2,r2)
  | abs (r1+r2-d) < eps = Circumscribed
  | r1+r2-d < eps = Outside
  | r1+r2-d > eps && d - abs (r1-r2) > eps = Intersect
  | abs (abs (r1-r2) - d) < eps = Inscribed
  | abs (r1-r2) - d > 0 = Inside
  | otherwise = Same
  where
    d = size2D (c1-c2)

crosspointCircleLine :: Circle2D -> Line2D -> [Point2D]
crosspointCircleLine (c,r) (l1,l2)
  | abs (d-r) < eps = [b]
  | d > r = []
  | otherwise = [b+(unit2D$l2-l1)`scale2D`a, b-(unit2D$l2-l1)`scale2D`a]
  where
    d = distanceLinePoint (l1,l2) c
    a = sqrt (r*r-d*d)
    n = normal2D (l2-l1)
    b = l1+(l2-l1) `scale2D` ((n`cross2D`(c+n-l1))/(n`cross2D`(l2-l1)))

crosspointCircles :: Circle2D -> Circle2D -> Either Relation [Point2D]
crosspointCircles (c1@(x1:+y1),r1) (c2@(x2:+y2),r2)
  | abs (r1+r2-d) < eps = Right [c1 + mkPolar r1 t]
  | r1+r2-d < eps = Left Outside
  | r1+r2-d > eps && d - abs (r1-r2) > eps = Right [c1 + mkPolar r1 (t+a), c1 + mkPolar r1 (t-a)]
  | abs (abs (r1-r2) - d) < eps = Right [c1 + mkPolar r1 t]
  | abs (r1-r2) - d > 0 = Left Inside
  | otherwise = Left Same
    where
      d = size2D (c1-c2)
      a = acos $ (r1*r1+d*d-r2*r2) / (2*d*r1)
      t = atan2 (y2-y1) (x2-x1)

tangentCircle :: Circle2D -> Point2D -> [Point2D]
tangentCircle (c@(cx:+cy),r) p@(px:+py)
  | abs (d-r) < eps = [p]
  | d-r < 0 = []
  | otherwise = [c + mkPolar r (t+a), c + mkPolar r (t-a)]
  where
    d = size2D (p-c)
    a = acos $ r / d
    t = atan2 (py-cy) (px-cx)

crosspointCircleSegment :: Circle2D -> Segment2D -> Either Relation [Point2D]
crosspointCircleSegment (c,r) (s1,s2)
  | d1 < r && d2 < r = Left Inside
  | abs (d1-r) < eps && abs (d2-r) < eps = Right [s1,s2]
  | (d1-r)*(d2-r) < eps =  Right [s1 + (unit2D $ s2-s1) `scale2D` (minimum . filter (>=0) $ [-b+sqrt(b*b-a), -b-sqrt(b*b-a)])]
  | abs (v-r) < eps = Right [k]
  | v > r = Left Outside
  | otherwise = Right [k-(unit2D$s2-s1)`scale2D`m, k+(unit2D$s2-s1)`scale2D`m]
  where
    d1 = size2D (c-s1)
    d2 = size2D (c-s2)
    v = distanceSegmentPoint (s1,s2) c

    b = (unit2D $ s2-s1) `dot2D` (s1-c)
    a = sizeSq2D s1 + sizeSq2D c - 2 * (s1 `dot2D` c) - r*r

    n = normal2D (s2-s1)
    m = sqrt (r*r-v*v)
    k = s1 + (s2-s1) `scale2D` ((n`cross2D`(c+n-s1))/(n`cross2D`(s2-s1)))


areaIntersectionCirclePolygon :: Circle2D -> Polygon2D -> Double
areaIntersectionCirclePolygon (c,r) ps = aux (zip (last ps : init ps) ps)
  where
    aux [] = 0
    aux ((p1,p2):rest) =
      let
        a =
          case crosspointCircleSegment (c,r) (p1,p2) of
            Left Inside -> (p1-c)`cross2D`(p2-c)/2
            Left Outside -> pi*r*r*(angleDiff (p1-c) (p2-c))/(2*pi)
            Right [q] ->
              let d1 = size2D (p1-c); d2 = size2D (p2-c)
              in
                if
                  | d1 >= r && d2 >= r -> pi*r*r*(angleDiff (p1-c) (p2-c))/(2*pi)
                  | d1 >= r -> pi*r*r*(angleDiff (p1-c) (q-c))/(2*pi) + (q-c)`cross2D`(p2-c)/2
                  | d2 >= r -> (p1-c)`cross2D`(q-c)/2 + pi*r*r*(angleDiff (q-c) (p2-c))/(2*pi)
            Right [q1,q2] ->
              pi*r*r*(angleDiff (p1-c) (q1-c))/(2*pi) +
              (q1-c)`cross2D`(q2-c)/2 +
              pi*r*r*(angleDiff (q2-c) (p2-c))/(2*pi)
      in a + aux rest

commonTangentPoints :: Circle2D -> Circle2D -> Either Relation [Point2D]
commonTangentPoints (c1,r1) (c2,r2)
  | abs (r1+r2-d) < eps =
    Right [
      c1 + ((c2-c1)`scale2D`(r1-r2) + (normal2D$c2-c1)`scale2D`(sqrt$(sizeSq2D$c2-c1)-(r1-r2)^2)) `scale2D` (r1/(sizeSq2D$c2-c1)),
      c1 + ((c2-c1)`scale2D`(r1-r2) - (normal2D$c2-c1)`scale2D`(sqrt$(sizeSq2D$c2-c1)-(r1-r2)^2)) `scale2D` (r1/(sizeSq2D$c2-c1)),
      c1 + n `scale2D` r1
      ]
  | r1+r2-d < eps =
    Right [
      c1 + ((c2-c1)`scale2D`(r1-r2) + (normal2D$c2-c1)`scale2D`(sqrt$(sizeSq2D$c2-c1)-(r1-r2)^2)) `scale2D` (r1/(sizeSq2D$c2-c1)),
      c1 + ((c2-c1)`scale2D`(r1-r2) - (normal2D$c2-c1)`scale2D`(sqrt$(sizeSq2D$c2-c1)-(r1-r2)^2)) `scale2D` (r1/(sizeSq2D$c2-c1)),
      c1 + ((c2-c1)`scale2D`(r1+r2) + (normal2D$c2-c1)`scale2D`(sqrt$(sizeSq2D$c2-c1)-(r1+r2)^2)) `scale2D` (r1/(sizeSq2D$c2-c1)),
      c1 + ((c2-c1)`scale2D`(r1+r2) - (normal2D$c2-c1)`scale2D`(sqrt$(sizeSq2D$c2-c1)-(r1+r2)^2)) `scale2D` (r1/(sizeSq2D$c2-c1))
      ]
  | r1+r2-d > eps && d - abs (r1-r2) > eps =
    Right [
      c1 + ((c2-c1)`scale2D`(r1-r2) + (normal2D$c2-c1)`scale2D`(sqrt$(sizeSq2D$c2-c1)-(r1-r2)^2)) `scale2D` (r1/(sizeSq2D$c2-c1)),
      c1 + ((c2-c1)`scale2D`(r1-r2) - (normal2D$c2-c1)`scale2D`(sqrt$(sizeSq2D$c2-c1)-(r1-r2)^2)) `scale2D` (r1/(sizeSq2D$c2-c1))
      ]
  | abs (abs (r1-r2) - d) < eps = Right [if r1>r2 then c1+n`scale2D`r1 else c2-n`scale2D`r2]
  | abs (r1-r2) - d > 0 = Right []
  | otherwise = Left Same
  where
    d = size2D (c2-c1)
    n = unit2D (c2-c1)




main :: IO ()
main = do
  return ()
