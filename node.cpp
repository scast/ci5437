#include "node.hpp"
#include "clique.hpp"
#include "cstring"

/*
 * Constructor de un nuevo nodo.
 */
node::node(state& _state, node *_parent, int _costo, int _action) :
    s(_state), parent(_parent), cost(_costo), action(_action) {
#ifndef STATIC
    h = find_disjoint_cliques_upto(g, s, N, MAX_GRADE);
#else
    int total = 0;
    for (int i=0; i <N; i++) {
        if ((s[i] == INCLUIDO) && (parent->s[i] != INCLUIDO)) { // Veo si incluí este nodo y sumo 1 a su
            total += (cliques[i]==i) ? 0 : 1;					// total, si pertenece a una clique
        }
    }
    h = max(parent->h - total, 0);
#endif
}

/*
 * Crea un nodo en el estado inicial
 */
node::node() {
    s = init();
    cost = 0;
    parent = 0;
    action = -1;
    h = find_disjoint_cliques_upto(g, s, N, MAX_GRADE);
}

/*
 * Crea una copia de este nodo.
 */
node::node(const node& n) {
    s = n.s;
    cost = n.cost;
    parent = &n;
    action = n.action+1;
    h = n.h;
}


/*
 * Revisar si estamos en un goal
 */
bool node::is_goal() {
#ifndef STATIC
    return (h == 0);
#else
    for (int i=0; i<N; i++) {
        if (s[i] != INCLUIDO) {
            for(set<int>::iterator it=g[i].begin(); it != g[i].end(); ++it) {
                if (s[*it] != INCLUIDO)
                    return false;
            }
        }
    }
    return true;
#endif
}

/*
 * Generar *un* sucesor
 */
state generate_succ(state& s1, int nodo) {
    vector<char> newState(s1);
    newState[nodo] = INCLUIDO;
    return newState;
}

/*
 * Retorna el estado inicial del arbol de busqueda dado un grafo de
 * tamano n.
 */
state init() {
    state g(N, EXCLUIDO);
    return g;
}

