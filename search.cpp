#include "search.hpp"
#include<map>
#include<set>
#include<cstdio>

int W = 1;
int exp = 0;
void print_state(state& st) {
    for (unsigned int i=0; i < st.size(); i++) {
        if (st[i])
            printf("1");
        else
            printf("0");
    }
    printf("\n");
}

bool is_better(node& n, map<state, int>& distances) {
    map<state, int>::iterator it = distances.find(n.s);
    if (it == distances.end())
        return true;
    return it->second > n.cost;
}

pair<int, node> WAstar(int w) {
    node n;
    set<state> closed; /* TODO: como guardar un arreglo en el set */
    map<state, int> distances; /* TODO: igual que arriba */
    pqueue queue;
    int k = 0;
    queue.push(node());
    W = w;
    while(!queue.empty()) {
        n = queue.top();
        printf("Este nodo tiene h(n) = %d\n", n.h);
        printf("He expandido %d nodos\n", k);
        // print_state(n.s);
        queue.pop();
        if (closed.find(n.s) == closed.end() /* esto prob no funciona */ ||
            is_better(n, distances)) {
            // Guardamos este nuevo costo y cerramos.
            distances[n.s] = n.cost;
            closed.insert(n.s);
            if (n.is_goal())
                return make_pair(n.cost, n);
            // Expandimos!
            // printf("Generando sucesores...\n");
            for (int i=0; i<N; i++) {
                state succ;
                if (!n.s[i])
                    continue;
                succ = generate_succ(n.s, i);
                node newNode(succ, &n, n.cost+1, i);
                queue.push(newNode);
                k++;
            }
            exp += k;

        // } else {
        //     if (closed.find(n.s) != closed.end())
        //         printf("Este nodo ya lo vi\n");
        // }
        // printf("----\n");
        }
    }
    return make_pair(-1, node());
}

pair<int, node> Astar() {
    return WAstar(1);
}
