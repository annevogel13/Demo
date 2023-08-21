#ifndef GRAPH_SUPERMARKET_HPP
#define GRAPH_SUPERMARKET_HPP

#include "graph_tuile.hpp"

using namespace MMaze; 

class Graph_supermarket{

    public: 
    Graph_tuile contenue_supermarket[6]; // decision de faire un jeu avec 6 tuiles 

    int nb_tuiles; 
    PadPlateau pad; 

    Graph_supermarket(); 
    ~Graph_supermarket(); 
    
    void afficher(); 
    bool ajoute_tuile(MMaze::Couleur couleur_porte, Tuile voisin); 
    void ajoute_voisins(Graph_tuile courante, Graph_tuile destination, int indice_porte); 
    Coup ajoute_coup(int origin, int dest, MMaze::Direction d, Graph_tuile GT, int t_debut, int t_fin);
    void remplir_supermarket(); 
    Graph_supermarket* operator =(Graph_supermarket NC);

}; 

#endif 