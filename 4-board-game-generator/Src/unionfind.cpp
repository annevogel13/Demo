#include "unionfind.hpp"
#include <iostream>

UnionFind::UnionFind(int nbr){

    for(int i = 0; i< nbr ;i++){
        tab.push_back(i);
    }   
}

void UnionFind::set_parent(int child, int parent){
    tab[child] = parent; 
 }

void UnionFind::afficher(){
    int nbr = tab.size(); 
    cout<<"[";
    for(int i = 0; i< nbr ;i++){
        cout<<" "<<tab[i];
    }

    cout<<"]"<<endl;
}

int UnionFind::trouver_racine(int i){
     
    int tmp = tab[i]; 

    do{
        
        tmp = tab[tmp]; 
        if(tmp == tab[tmp]){
                return tmp; 
        }
    }while(tmp != tab[tmp]) ;

    return -1; 
} 

bool UnionFind::dans_meme_ensemble(int i, int j){
     // trouver les racines des nombres donnees 
    int r1 = trouver_racine(i); 
    int r2 = trouver_racine(j); 

    // verifier si c'est le meme racine donc le meme ensemble 
    return r1 == r2; 
}


void UnionFind::union_ensembles(int i, int j ){

    // trouver les racines des nombres donnees 
    int r1 = trouver_racine(i); 
    int r2 = trouver_racine(j);

    // r2 devient parent de r1
    tab[r1] = r2 ;      
}

