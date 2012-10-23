#include "clique.hpp"
#include <vector>
#include <cstring>
#include <iterator>
#include <set>
#include <algorithm>
#include <bitset>
#include <cstdio>
using namespace std;

graph g;
int N;


void print_with_indent(const char * string, int indent){
    printf("%*s" "%s", indent, " ", string);
}

void print_set(const set<int>& x, int i) {
    printf("{ ");
    for (set<int>::iterator it = x.begin(); it != x.end(); ++it) {
        printf("%d ", *it);
    }
    printf("},");
}

/*
  Dada una matriz de adyacencias graph que representa un grafo de
  tamaño n, computaremos todos los cliques de tamaño size y los
  guardaremos en el arreglo cliques.

  Utilizamos el algoritmo de Bron-Kerbosch para esto.
  Wikipedia -> https://en.wikipedia.org/wiki/Bron%E2%80%93Kerbosch_algorithm
 */
bool find_cliques_of_size(const graph& g, int n, unsigned int size, int *cliques,
                          set<int> P, set<int> X, const set<int>& R,
                          const int i) {
    // print_with_indent("Recibida llamada: bk", i);
    // printf("(%d, ", size);
    // print_set(R, i);
    // print_set(P, i);
    // print_set(X, i);
    // printf(")\n");
    // printf("BROOOO");
    // TODO: Falta decir de cuanto es mi clique.
    // printf("%d %d\n", R.size(), size);
    if (R.size() == size) {
        // printf("HOLA");
        // Conseguimos un k-clique. Cambiamos nuestra lista de cliques
        // para no seguir buscando cliques con estos nodos.
        int i = *(R.begin());
        // printf("HOLA");
        for (set<int>::iterator it = R.begin(); it != R.end(); ++it ) {
            cliques[*it] = i;
        }
        cliques[i] = -1;
        // printf("Consegui el clique: ");
        // print_set(R, 0);
        // printf("\n");
        return true;
    } else if (P.size() == 0 && X.size() ==0) {
        // Conseguimos un k-clique con k < size. Lo ignoraremos porque
        // estamos buscando greedy los mas grandes y luego los mas
        // pequenos.
        return false;
    }
    for (set<int>::iterator it = P.begin(); it != P.end(); ) {
        // printf("brooo estoy pegao");
        int v = *it;
        set<int> Rv(R), Xv, Pv;
        // vector<int> Pv1(N), Xv1(N);
        Rv.insert(v);
        set_intersection(g[v].begin(), g[v].end(), P.begin(), P.end(),
                         inserter(Pv, Pv.begin()));
        set_intersection(g[v].begin(), g[v].end(), X.begin(), X.end(),
                         inserter(Xv, Xv.begin()));
        // set_intersection(g[v].begin(), g[v].end(), P.begin(), P.end(),
        //                  Pv1.begin());
        // set_intersection(g[v].begin(), g[v].end(), X.begin(), X.end(),
        //                  Xv1.begin());
        // set<int> Pv(Pv1.begin(), Pv1.end()), Xv(Xv1.begin(), Xv2.e
                                                // );
        bool ret = find_cliques_of_size(g, n, size, cliques, Pv, Xv, Rv, i+2);
        if (ret)
            return true;
        X.insert(v);
        set<int>::iterator cur = it;
        ++it;
        P.erase(cur);
    }
    return false;
}

/*
 * Esto es basicamente nuestra funcion heuristica. Le das un grafo
 * original, los nodos de ese grafo que aun no hemos quitado, y
 * calcula el valor de la heuristica.
 */
int find_disjoint_cliques_upto(const graph& g, const vector<char>& available,
                               int n, int grade) {
    int *cliques = new int[n];
    for (int i=0; i < n; i++) {
        cliques[i] = i;
    }
    set<int> x, initialP;
    int h = 0;
    for (int i=0; i < n; i++)
        if (available[i] == '1' || available[i] == '3')
            initialP.insert(i);

    for (int i = grade; i > 1; i--) {
        while (find_cliques_of_size(g, n, i, cliques, initialP, x)) {
            h += (i-1);
            for (set<int>::iterator it = initialP.begin(); it != initialP.end();) {
                int v = *it;
                if (cliques[v] != v || cliques[v] == -1) {
                    ++it;
                    initialP.erase(v);
                    x.insert(v);
                    continue;
                }
                ++it;
            }
        }
    }
    // printf("----\n");
    delete cliques;
    return h;
}

// int main(int argc, char **argv) {
//     int n, m, *cliques, v, u;
//     scanf("%d %d", &n, &m);
//     graph g(n);
//     cliques = new int[n];
//     for (int i=0; i < n; i++) {
//         cliques[i] = i;
//     }
//     bool *test = new bool[n];
//     // print_set(initialP, 0);printf("\n");

//     for (int i=0; i < m; i++) {
//         scanf("%d %d", &v, &u);
//         g[v].insert(u);
//         g[u].insert(v);
//     }
//     memset(test, true, sizeof(bool)*n);
//     printf("h(n) = %d\n", find_disjoint_cliques_upto(g, test, n, cliques, 4));
//     return 0;
// }
