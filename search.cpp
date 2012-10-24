#include "search.hpp"
#include<map>
#include<set>
#include<cstdio>
#include<climits>
#include<algorithm>

int alpha = INT_MAX;
unsigned long long int EXPN = 0;
int PROF = 0;
node best;

// bool mycomp(int i, int j) {
//     return g[i].size() > g[j].size();
// }

void print_state(state& st) {
    for (unsigned int i=0; i < st.size(); i++) {
        printf("%c", st[i]);
    }
    printf("\n");
}

// bool is_better(node& n, unordered_map<state, int>& distances) {
//     unordered_map<state, int>::iterator it = distances.find(n.s);
//     if (it == distances.end())
//         return true;
//     return it->second > n.cost;
// }

// pair<int, node> WAstar(int w) {
//     node n;
//     unordered_set<state> closed; /* TODO: como guardar un arreglo en el set */
//     unordered_map<state, int> distances; /* TODO: igual que arriba */
//     pqueue queue;
//     int k = 0;
//     int *order = new int[N];
//     for (int i = 0; i<N; i++)
//         order[i] = i;
//     sort(order, order+N, mycomp);
//     printf("order[0] = (%d, %d), order[1] = (%d, %d)", order[0], g[order[0]].size(), order[1], g[order[1]].size());
//     queue.push(node());
//     W = w;
//     while(!queue.empty()) {
//         printf("He expandido %d nodos\n", k);
//         n = queue.top();
//         queue.pop();
//         // if (closed.find(n.s) == closed.end() /* esto prob no funciona */ ||
//         //     is_better(n, distances)) {
//             printf("%d\n", n.cost+n.h);
//             // Guardamos este nuevo costo y cerramos.
//             distances[n.s] = n.cost;
//             closed.insert(n.s);
//             if (n.is_goal())
//                 return make_pair(n.cost, n);
//             // Expandimos!
//             printf("Generando sucesores...\n");
//             if (n.action + 1 != N) {
//                 // printf("Generado ");
//                 state succ = generate_succ(n.s, order[n.action+1]);
//                 // print_state(succ);
//                 node newNode(succ, &n, n.cost+1, n.action+1);
//                 queue.push(newNode);
//                 n.action++;
//                 // print_state(n.s);
//                 queue.push(n);
//                 k += 2;

//             }
//            //  for (int i=0; i<N; i++) {
//            //      state succ;
//            //      if (!n.s[i])
//            //          continue;
//            //      succ = generate_succ(n.s, i);
//            //      node newNode(succ, &n, n.cost+1, i);
//            //      // print_state(succ);
//            //      // printf("Costo del sucesor: %d\n", W*newNode.h+newNode.cost);
//            //      queue.push(newNode);
//            //      // exp++;
//            //      k++;
//            // }

//         // } else {
//         //     printf("Este nodo ya lo vi\n");
//         // }
//         // printf("----\n");
//         // }
//     }
//     return make_pair(-1, node());
// }


/*
 * Implementación de Depth First Branch and Bound.
 */
void DFS_BnB(node& n, int p) {
    if (EXPN % EXPN_NUM == 0) {
        // Imprimimos cada 100mm de nodos.
        printf("Nodos expandidos -> %llu\n", EXPN);
        printf("Profundidad actual -> %d\n", p);
        print_state(n.s);
    }
    if (n.h+n.cost >= alpha) {
        // Pruning por no ser un buen candidato
        return;
    }

    if (n.is_goal()) {
        if (n.cost < alpha) {
            printf("Mejor goal conseguido -> %d\n", n.cost);
            printf("Profunfidad -> %d\n", p);
            alpha = n.cost;
            best = n;
            PROF = p;
            print_state(best.s);
        }
        return;
    }
    if (n.action + 1 != N) {
        // Seleccionamos este vertice.
        state succ ;
        int next = n.action + 1;
        succ = generate_succ(n.s, next);
        node newNode(succ, &n, n.cost+1, n.action+1);
        EXPN++;
        DFS_BnB(newNode, p+1);

        /*
           No seleccionamos este vertice. Haremos dos podas:

           1. Si decidimos no agregar, necesariamente los nodos
           adyacentes se deben agregar eventualmente, por lo que
           podamos si decidimos no agregar.

           2. Si no lo podemos agregar (porque estamos en un nodo que
           ya decidio no agregar ese nodo), podamos.
         */

        // Chequeamos si necesariamente había que agregar este nodo.
        node newNode2(n);
        if (newNode2.s[next] == DEBE_INCLUIRSE) {
            return; // Se debe incluir pero decidimos no
                    // hacerlo. Podamos.
        }

        set<int>::iterator cend = g[next].end();
        for (set<int>::iterator it = g[next].begin(); it != cend; ++it) {
            if (*it < next && newNode2.s[*it] == EXCLUIDO) {
                return; // Se debe incluir pero ya decidimos en el
                        // árbol no incluirlo!
            }
            if (newNode2.s[*it] != INCLUIDO)
                newNode2.s[*it] = DEBE_INCLUIRSE;
        }
        EXPN++;
        // Si llegamos hasta aca, vale la pena revisar este nodo.
        DFS_BnB(newNode2, p+1);
    }
}

/*
 * Implementación Branch and Bound.
 */
pair<int, node> BnB(){
    node initial;
    DFS_BnB(initial, 0);
    printf("RESULTADO\n");
    print_state(best.s);
    printf("Nodos expandidos -> %llu\n", EXPN);
    printf("Profundidad de la mejor solución -> %d\n", PROF);
    return make_pair(alpha, best);
}

