import Data.Char
import Data.List
import System.Environment
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
        let units = concat (filter (\c -> length c == 1) cnf') in
        if units /= [] then [units++asgn]
        else let a = chooseVar cnf' in [a:asgn, -a:asgn]
    else []
            where chooseVar = head . head

{-
Input: a cnf with asgn *already assigned*.
Outpt: applies any units in cnf recursively, appends them to assignment
-}
applyUnits :: CNF -> Assignment -> (CNF, Assignment)
applyUnits cnf asgn =
    let units = concat (filter (\c -> length c == 1) cnf) in
    if units /= [] then applyUnits (applyAssignment cnf units) (units++asgn)
    else (cnf, asgn)

saveStateCNFSucc :: CNF -> (CNF, Assignment) -> [(CNF, Assignment)]
saveStateCNFSucc origCNf (cnf, asgn) =
    if isTerminal cnf then []
    else
        let a :: Int
            a = head . head $ cnf in
        [(applyUnits (applyVar cnf a) (a:asgn)), applyUnits (applyVar cnf (-a)) ((-a):asgn)]


saveStateCNFExploration cnf = dfs (saveStateCNFSucc cnf) [(cnf,[])]
-- this mess can be optimized (inner lambda -> c == []), but hey.
enumSatCNF3 cnf = map (\(c,a) -> a) (filter (\(c,a) -> satisfies cnf a) (saveStateCNFExploration cnf))

{-
Generates a list of all leaves, filtered by those which satisfy (rather than
unsat) the cnf.
In other words, our solver!
-}

cnfExploration2 cnf = dfs (propogatingCNFSucc cnf) [[]]
enumSatCNF2 cnf = filter (satisfies cnf) (cnfExploration2 cnf)

cnfExploration1 cnf = dfs (cnfSucc cnf) [[]]
enumSatCNF1 cnf = filter (satisfies cnf) (cnfExploration1 cnf)

enumSat1' contents =
    let cnf = stringToCNF contents in
    show (length (cnfExploration1 cnf))
enumSat1 = do contents <- getContents
              putStr ((enumSat1' contents)++"\n")

cliSat1' contents =
    let cnf = stringToCNF contents in
    show (take 1 (enumSatCNF1 cnf))
cliSat1 = do contents <- getContents
             putStr ((cliSat1' contents)++"\n")

cliSat2' contents =
    let cnf = stringToCNF contents in
    show (length (enumSatCNF2 cnf))
cliSat2 = do contents <- getContents
             putStr ((cliSat2' contents)++"\n")

cliSat3' contents =
    let cnf = stringToCNF contents in
    show (take 1 (enumSatCNF3 cnf))
cliSat3 = do contents <- getContents
             putStr ((cliSat3' contents)++"\n")

enumSat3' contents =
    let cnf = stringToCNF contents in
    show (length (enumSatCNF3 cnf))
enumSat3 = do contents <- getContents
              putStr ((enumSat3' contents)++"\n")

main = enumSat1

--main = do contents <- getContents
--          putStr ((cliEnumSatCNF contents)++"\n")

--main = do contents <- getContents
--          putStr ((cliTakeSomeSAT contents)++"\n")

