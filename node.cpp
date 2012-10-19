#include "node.hpp"
#include "clique.hpp"
#include "cstring"


/*
 * Constructor de un nuevo nodo.
 */
node::node(bool *_state, node *_parent, int _costo, int _action) :
    state(_state), parent(_parent), cost(_costo), action(_action) {
    h = find_disjoint_cliques_upto(g, state, N, MAX_GRADE);
}

node::node() {
    state = init();
    cost = 0;
    parent = 0;
    action = -1;
    h = find_disjoint_cliques_upto(g, state, N, MAX_GRADE);
}

/*
 * Revisar si estamos en un goal
 */
bool node::is_goal() {
    return (h == 0);
}

/*
 * Generar *un* sucesor
 */
bool *generate_succ(bool *state, int nodo) {
    bool *newState = new bool[N];
    memcpy(newState, state, sizeof(bool)*N);
    newState[nodo] = false;
    return newState;
}

/*
 * Retorna el estado inicial del arbol de busqueda dado un grafo de
 * tamano n.
 */
bool *init() {
    bool *g = new bool[N];
    memset(g, true, sizeof(bool)*N);
    return g;
}

