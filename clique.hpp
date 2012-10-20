#ifndef __clique_hpp__
#define __clique_hpp__
#include<vector>
#include<set>
using namespace std;
typedef vector<set<int> > graph;

#define MAX_GRADE (4)
extern graph g;
extern int N;

bool find_cliques_of_size(const graph& g, int n, unsigned int size, int *cliques,
                          set<int> P, set<int> X, const set<int>& R = set<int>(),
                          const int i = 2);

int find_disjoint_cliques_upto(const graph& g, const vector<bool>& available,
                               int n, int grade);

#endif
