#ifndef __node_hpp__
#define __node_hpp__
#include "clique.hpp"

struct node {
    bool *state; // cuanto del grafo queda
    node *parent; // padre de este nodo en el arbol de busqueda
    int cost; // costo del nodo hasta aca
    int action; // cual nodo agregue cuando llegue a este nodo
    int h;
    node(bool *_state, node *_parent, int _costo, int _action);
    node();
    bool is_goal();
};

bool *init();
bool *generate_succ(bool *state, int nodo);


#endif
