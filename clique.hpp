#ifndef __clique_hpp__
#define __clique_hpp__
#include<vector>
#include<set>
using namespace std;
typedef vector<set<int> > graph;
extern graph g;
extern int N;
#define MAX_GRADE (4)

bool find_cliques_of_size(const graph& g, int n, unsigned int size, int *cliques,
                          set<int> P, set<int> X, const set<int>& R = set<int>(),
                          const int i = 2);

int find_disjoint_cliques_upto(const graph& g, const bool * available,
                               int n, int grade);

#endif
