import Data.Char
import Data.List
import SelfReductionParser
{-
This is the core algorithm.
It is simply depth-first search over a successor function.
As we assume we're exploring a tree, we don't have any
state whatsoever (we don't need to remember which nodes
we've already visited or seen).

Observe that it is not tail-recursive.
Our focus is entirely on mathematical expression, not 
real-world efficiency.
-}

dfs :: (a->[a])->[a]->[a]
dfs succ [] = []
dfs succ (state:stack) =
    state : dfs succ (succ state++stack)


{-             -}
{- CNF SECTION -}
{-             -}

{-
These are the initial definitions used in solving SAT.
Observe that these are completely algorithm-independent:
they have nothing to do with self-reducibility or anything,
but rather just define basic CNF operations that any
CNF library would define.

Probably not the most efficient.
-}
type CNF = [[Int]]
type Assignment = [Int]
isSat [] = True
isSat _ = False
isUnSat = elem []
isTerminal cnf = isSat cnf || isUnSat cnf

applyVar :: CNF -> Int -> CNF
applyVar cnf a = 
    filter (notElem a) (map (filter (\v -> v /= -a)) cnf)
applyAssignment = foldl applyVar

satisfies cnf asgn = isSat (applyAssignment cnf asgn)

{-
Here is the only algorithm-particular function:
the successor function!
All we need to do (alternatively, all we *can* do)
to improve the algorithm is make this function better.
-}

{-
Our first successor function is dead-dead stupid:
see if the assignment is terminal (ie., obviously
satisfies or unsats the cnf), if so, it's a leaf.
Otherwise, pick the next variable and generate both options.
-}
cnfSucc :: CNF -> Assignment -> [Assignment]
cnfSucc cnf asgn =
  let cnf' = applyAssignment cnf asgn in
  -- if asgn doesn't define a leaf in our tree
  if not (isTerminal cnf') then
      -- have a very dumb way of generating children
    let a = chooseVar cnf' in [a:asgn, -a:asgn]
  -- otherwise, asgn is a leaf, so we're done on this branch.
  else []
    where chooseVar = head . head

{-
This is a slightly smarter version: If we have units, then
we only have one successor, which is those units applied to our
assignment.
-}
propogatingCNFSucc :: CNF -> Assignment -> [Assignment]
propogatingCNFSucc cnf asgn =
    let cnf' = applyAssignment cnf asgn in
    if not (isTerminal cnf') then
        let units = foldl (++) [] ((filter (\c -> length c == 1)) cnf') in
        if units /= [] then [units++asgn]
        else let a = chooseVar cnf' in [a:asgn, -a:asgn]
    else []
            where chooseVar = head . head

{-
Generates a list of all leaves, filtered by those which satisfy (rather than
unsat) the cnf.
In other words, our solver!
-}
enumSatCNF cnf =
  filter (satisfies cnf) (dfs (propogatingCNFSucc cnf) [[]])
  --filter (satisfies cnf) (dfs (cnfSucc cnf) [[]])

-- actually running the code!
cliEnumSatCNF input =
    let cnf = stringToCNF input in -- parse the input
    show $ length (enumSatCNF cnf) -- output the result

{-                          -}
{- Hamiltonian Path Section -}
{-                          -}
neighborFun :: (Eq a) => [(a,a)]->a->[a]
neighborFun edgeset v =
    map (\(_,y)-> y ) (filter (\(a,_) -> a == v) edgeset)

vertices edgeset = foldl (\vs-> \(u,v)->union [u,v] vs) [] edgeset

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

main = do contents <- getContents
          putStr ((cliEnumSatCNF contents)++"\n")
--main = print $ enumHamPaths exampleGraph
