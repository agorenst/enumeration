module SelfReductionParser where

stringToCNF :: String -> [[Int]]
stringToCNF str =
    let ls = lines str -- each line is at most 1 clause
        split = (map words ls) -- parse around whitespace in each line
        nonzero = map (filter (/= "0")) split -- rid of all zeros
        nonempt = filter (\l -> length l >= 1) nonzero -- get rid of whitespace only lines
        clauses = filter (\l -> head l /= "c" && head l /= "p") nonempt -- ignore comments, problem spec
    in map (map readInt) clauses

readInt :: String -> Int
readInt = read
