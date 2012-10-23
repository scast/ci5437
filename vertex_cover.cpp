#include "clique.hpp"
#include "node.hpp"
#include "search.hpp"
#include <cstdio>

// extern int N;
// extern graph g;
// extern

int main(int argc, char **argv) {
    int m, v, u;
    scanf("%d %d", &N, &m);
    // printf("%d", N);
    g.resize(N, set<int>());
    g.clear();
    for(int i=0; i<m; i++) {
        scanf("%d %d", &v, &u);
        g[v].insert(u);
        g[u].insert(v);
    }
    pair<int, node> result_A_star = BnB();
    printf("Costo final -> %d\n", result_A_star.first);
    return 0;
}
