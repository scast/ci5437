#include "search.hpp"
#include<map>
#include<set>
#include<cstdio>
#include<climits>
#include<algorithm>
#include<unordered_set>
#include<unordered_map>
int W = 1;
// int exp = 0;

bool mycomp(int i, int j) {
    return g[i].size() < g[i].size();
}

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



int alpha = INT_MAX;
int EXPN = 0;
node best;
int *order;

void DFS_BnB(node& n, int p) {
    // printf("g(n) = %d\n", n.cost);
    // printf("h(n) = %d\n", n.h);
    // printf("f(n) = %d\n", n.h+n.cost);
    // printf("%d\n", n.cost);
    if (EXPN % 100000 == 0) {
        printf("Nodos expandidos -> %d\n", EXPN);
        printf("Profundidad actual -> %d\n", p);
    }
    if (n.h+n.cost >= alpha) {
        // printf("Podando, el mio -> alpha = %d\n", alpha);
        return;
    }

    if (n.is_goal()) {
        if (n.cost < alpha) {
            printf("Mejor goal conseguido -> %d\n", n.cost);
            printf("Profunfidad -> %d\n", p);
            alpha = n.cost;
            best = n;
        }
    }
    // printf("En un nodo de h(n) = %d\n", n.h);
    if (n.action + 1 != N) {
        state succ ;
        succ = generate_succ(n.s, n.action+1);
        node newNode(succ, &n, n.cost+1, n.action+1);
        EXPN++;
        DFS_BnB(newNode, p+1);
        /*
           Haremos dos podas:

           1. Si decidimos no agregar, necesariamente los nodos
           adyacentes se deben agregar eventualmente, por lo que
           podamos si decidimos no agregar.

           2. Si no lo podemos agregar (porque estamos en un nodo que
           ya decidio no agregar ese nodo), podamos.
         */

        // Chequeamos si necesariamente habia que agregar este nodo.
        if (n.s[n.action+1] == DEBE_INCLUIRSE) {
            printf("Podando por DEBE_INCLUIRSE\n");
            return; // Se debe incluir pero decidimos no hacerlo.
        }

        // Chequeamos los nodos adyacentes y revisamos podas.
        set<int>::iterator cend = g[n.action+1].end();
        for (set<int>::iterator it = g[n.action+1].begin(); it != cend; ++it) {
            if (*it < n.action+1 && n.s[*it] == EXCLUIDO) {
                printf("Podando por EXCLUIDO\n");
                return; // Se debe incluir pero ya decidimos en el
                        // árbol no incluirlo!
            }

            n.s[*it] = DEBE_INCLUIRSE;

        }
        n.action++;
        EXPN++;
        DFS_BnB(n, p+1); // exp+=2;
    }
}


pair<int, node> BnB(){
    node initial;
    // printf("g(n) = %d\n", n.cost);
    printf("h(n) = %d\n", initial.h);
    // printf("f(n) = %d\n", n.h+n.cost);
    // printf("%d\n", n.cost);
    order = new int[N];
    for (int i = 0; i<N; i++)
        order[i] = i;
    sort(order, order+N, mycomp);

    DFS_BnB(initial, 0);
    print_state(best.s);
    return make_pair(alpha, best);
}

// pair<int, node> Astar() {
//     return WAstar(1);
// }
