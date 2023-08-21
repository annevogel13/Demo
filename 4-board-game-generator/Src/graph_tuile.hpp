#ifndef GRAPH_TUILE_HPP
#define GRAPH_TUILE_HPP

#include "noeud_case.hpp"
#include "tuile.hpp"
#include <vector> 
#include <list>

class Graph_tuile{
    public: 

        Noeud_case contenue[16];  
        Tuile tuile ; 
        bool acces_portes[4]; 
         // si porte ouverte --> acces_port[i] = true 
         // 0 -> c'est port case  2
         // 1 -> c'est port case  4 
         // 2 -> c'est port case 11
         // 3 -> c'est port case 13 
        
        
        // constructeurs
        Graph_tuile(Tuile T, int l, int c);
        Graph_tuile(Tuile T);
        Graph_tuile(); 
        ~Graph_tuile();
        
        // autre fonctions 
        void remplirPred();  
        void affichage(); 
        Graph_tuile* operator =(Graph_tuile GT); 
        

};


#endif 