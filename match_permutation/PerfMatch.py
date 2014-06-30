import sys
from collections import defaultdict
import subprocess

graphFile = sys.argv[1]

G = defaultdict(lambda : defaultdict(float))

for line in open(graphFile):
    line = line.strip().replace('i', 'j').replace(',','+')
    if (line != ''):
        u, v, w = line.split()
        u = int(u)
        v = int(v)
        G[u][v] = complex(w)
        G[v][u] = complex(w)

size = max(G.keys())
print size

match_perm_proc = subprocess.Popen(['./match_perm_printer', str(size)], stdout=subprocess.PIPE)
out, err = match_perm_proc.communicate()
result = complex("0.0")
for line in out.split("\n"):
    verts = map(int, line.split())
    subprod = complex("1.0")
    for i in range(len(verts)/2):
        subprod *= G[verts[2*i]][verts[(2*i)+1]]
    result += subprod

print result
