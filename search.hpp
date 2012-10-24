#ifndef __search_hpp__
#define __search_hpp__
#include <queue>
// #include <unordered_map>
#include "node.hpp"

#ifndef STATIC
#define EXPN_NUM (100000)
#else
#define EXPN_NUM (100000000)
#endif

// Esto era usado para WA* y WIDA*
// extern int W;
//
// // extern graph g;
// // extern int N;

// struct CompareNode
// {
//     bool operator()(const node &a, const node &b) {
//         if (W*a.h + a.cost == W*b.h + b.cost) {
//             return a.h > b.h;
//         }
//         return W*a.h + a.cost > W*b.h + b.cost;
//     }
// };

// typedef priority_queue<node, vector<node>, CompareNode> pqueue;

// bool is_better(node& n, unordered_map<bool*, int>& distances);
// pair<int, node> WIDAstar(int w);
// pair<int, node> IDAstar();
// pair<int, node> WAstar(int w);
// pair<int, node> Astar();
pair<int, node> BnB();

#endif
