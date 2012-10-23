#include "search.hpp"
#include<map>
#include<set>
#include<cstdio>
#include<climits>
#include<algorithm>
int W = 1;
// int exp = 0;

bool mycomp(int i, int j) {
    return g[i].size() > g[j].size();
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
int *order, *actionMap;

void DFS_BnB(node& n, int p) {
    // printf("g(n) = %d\n", n.cost);
    // printf("h(n) = %d\n", n.h);
    // printf("f(n) = %d\n", n.h+n.cost);
    // printf("%d\n", n.cost);
    if (EXPN % 10000 == 0) {
        printf("Nodos expandidos -> %d\n", EXPN);
        printf("Profundidad actual -> %d\n", p);
        print_state(n.s);
    }
    if (n.h+n.cost >= alpha) {
        // printf("Podando por peor costo\n");
        return;
    }

    if (n.is_goal()) {
        if (n.cost < alpha) {
            printf("Mejor goal conseguido -> %d\n", n.cost);
            printf("Profunfidad -> %d\n", p);
            alpha = n.cost;
            best = n;
            print_state(best.s);
        }
        return;
    }
    // printf("En un nodo de h(n) = %d\n", n.h);
    if (n.action + 1 != N) {
        state succ ;
        int next = n.action + 1;
        // printf("NEXT -> %d\n", next);
        succ = generate_succ(n.s, next);
        // printf("GENERADO\n");
        // print_state(succ);
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
        if (n.s[next] == DEBE_INCLUIRSE) {
            // printf("Podando por DEBE_INCLUIRSE %d\n", n.action+1);
            return; // Se debe incluir pero decidimos no hacerlo.
        }

        // Chequeamos los nodos adyacentes y revisamos podas.
        // printf("Sucesores de %d -> ", n.action+1);
        // printf("profundidad -> %d\n", p);
        // print_state(n.s);
        set<int>::iterator cend = g[next].end();
        // printf("HOLA\n");
        for (set<int>::iterator it = g[next].begin(); it != cend; ++it) {
            // if (n.s[*it] == EXCLUIDO)
            //     printf("%d %d %c\n", actionMap[*it], actionMap[next], n.s[*it]);
            if (*it < next && n.s[*it] == EXCLUIDO) {
                // printf("Podando por EXCLUIDO\n");
                return; // Se debe incluir pero ya decidimos en el
                        // árbol no incluirlo!
            }
            // printf("%d, ", *it);
            if (n.s[*it] != INCLUIDO)
                n.s[*it] = DEBE_INCLUIRSE;

        }
        // printf("estado nuevo -> ");
        // print_state(n.s);
        // printf("\n");
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
    // order = new int[N];
    // actionMap = new int[N];
    // for (int i = 0; i<N; i++)
    //     order[i] = i;
    // sort(order, order+N, mycomp);
    // for (int i=0; i < N; i++) {
    //     printf("Vertice %d tiene %ld lados\n", order[i], g[order[i]].size());
    //     actionMap[order[i]] = i;
    // }


    DFS_BnB(initial, 0);
    print_state(best.s);
    return make_pair(alpha, best);
}

// pair<int, node> Astar() {
//     return WAstar(1);
// }
