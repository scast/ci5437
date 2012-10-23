#ifndef __node_hpp__
#define __node_hpp__
#include "clique.hpp"

#define INCLUIDO ('0')
#define EXCLUIDO ('1')
#define DEBE_INCLUIRSE ('3')

typedef vector<char> state;

struct node {
    state s; // cuanto del grafo queda
    node *parent; // padre de este nodo en el arbol de busqueda
    int cost; // costo del nodo hasta aca
    int action; // cual nodo agregue cuando llegue a este nodo
    int h;
    node(state& _state, node *_parent, int _costo, int _action);
    node();
    bool is_goal();
};

state init();
state generate_succ(state& s, int nodo);



#endif
