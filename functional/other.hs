
{-                          -}
{- Hamiltonian Path Section -}
{-                          -}
neighborFun :: (Eq a) => [(a,a)]->a->[a]
neighborFun edgeset v =
    map snd (filter (\(a,_) -> a == v) edgeset)

{- takes as input an edgeset, and just collects all vertices -}
vertices :: [(Int, Int)] -> [Int]
vertices = foldl (\vs (u,v)->union [u,v] vs) []
-- can we just do a list comprehension?
--vertices edgeset = nub [u | (u,v) <- edgeset]

exampleGraph :: [(Int, Int)]
exampleGraph = [(1,2), (2,3),(1,3),(3,2),(3,1),(1,4),(4,1)]

{- Finding a hamiltonian path lends itself to our formulation very well.
 - The successor function is very straightforward: -}
hampathSucc :: (Eq a) => (a->[a]) -> [a] -> [[a]]
hampathSucc neighbors (v:vs) = 
    {- (v:vs) is our current path. From that, we create a set of paths,
    extended by vertices which are both
    a) neighbors of v, and b) not already in the path -}
    let ns = neighbors v \\ (v:vs) in
    map (:(v:vs)) ns

enumHamPaths g =
    let vs = vertices  g
        k = length vs
        nfunc = neighborFun g
        succ = hampathSucc nfunc
    in filter (\l -> length l == k) (dfs succ (map (:[]) vs))


{-                      -}
{- Matching Permutation -}
{-                      -}

type MatchPerm = [(Int, Int)]

matchPermSucc :: (MatchPerm, [Int]) -> [(MatchPerm, [Int])]
matchPermSucc (solSoFar, []) = []
matchPermSucc (solSoFar, unMatched) =
    let x = minimum unMatched
        ys = filter (>x) unMatched
    in [((x,y):solSoFar, unMatched \\ [x,y]) | y <- ys]

enumMatchPerms n =
    let startStates :: [(MatchPerm, [Int])]
        startStates = [([(1,y)], ([2..n]\\[y])) | y <- [2..n]] in
    filter (\(m,unmatched)-> unmatched == []) (dfs matchPermSucc startStates)
--main = print $ enumHamPaths exampleGraph
--main = do
--    args <- getArgs
--    print $ length ( enumMatchPerms (readInt (head args)) )
