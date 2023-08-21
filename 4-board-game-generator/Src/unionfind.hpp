#ifndef UNIONFIND_HPP_
#define UNIONFIND_HPP_

#include <vector>

using namespace std; 

class UnionFind{

    public:
    std::vector<int> tab; 
    
    UnionFind(int nbr); 

    void set_parent(int child, int parent); 

    int trouver_racine(int i); 

    bool dans_meme_ensemble(int i, int j); 

    void union_ensembles(int i, int j); 

    void afficher(); 

};

#endif