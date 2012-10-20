from collections import defaultdict
import random

V = 20
EV = 3
G = defaultdict(list)

for i in range(V):
    hijos = range(V)
    random.shuffle(hijos)
    while len(G[i]) < 16 and hijos:
        current = hijos.pop()
        if current not in G[i] and len(G[current]) < 16 and current != i:
            G[i].append(current)
            G[current].append(i)
Y = set([tuple(sorted([x, y])) for x in G for y in G[x]])
print V, len(Y)
for (a, b) in Y:
    print a, b

