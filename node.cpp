#include "node.hpp"
#include "clique.hpp"
#include "cstring"

/*
 * Constructor de un nuevo nodo.
 */
node::node(state& _state, node *_parent, int _costo, int _action) :
    s(_state), parent(_parent), cost(_costo), action(_action) {
    h = find_disjoint_cliques_upto(g, s, N, MAX_GRADE);
}

node::node() {
    s = init();
    cost = 0;
    parent = 0;
    action = -1;
    h = find_disjoint_cliques_upto(g, s, N, MAX_GRADE);
}

/*
 * Revisar si estamos en un goal
 */
bool node::is_goal() {
    return (h == 0);
}



// bool operator<(const node& a, const node& b) {
//     if (a.h + a.cost == b.h + b.cost) {
//         return a.h < b.h;
//     }
//     return a.h + a.cost < b.h + b.cost;
// }

/*
 * Generar *un* sucesor
 */
state generate_succ(state& s1, int nodo) {
    vector<bool> newState(s1);
    newState[nodo] = false;
    return newState;
}

/*
 * Retorna el estado inicial del arbol de busqueda dado un grafo de
 * tamano n.
 */
state init() {
    state g(N, true);
    return g;
}

