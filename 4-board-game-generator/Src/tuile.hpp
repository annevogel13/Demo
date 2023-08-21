#ifndef TUILE_HPP
#define TUILE_HPP

#include "unionfind.hpp"
#include "case.hpp"
#include "couleurs.hpp"
#include "site.hpp"
#include "mur.hpp"
#include "draw.hpp"

#include <vector>

using namespace MMaze; 

class Tuile{

    public: 
        bool depart ; 
        bool tab_murs[24]; // savoir si le murs est en haut ou pas 
        Site tab_cases_contenue[16]; // savoir les placement des elements speciale
        std::vector<Mur> vecM;
        int racine_path ; 
        int tuile_c; 
        int tuile_l; 
        
        // true --> depart, false --> classqiue 
        Tuile(bool type_tuile, int index, int l, int c); 
        Tuile(bool type_tuile, int index, bool objective, bool sortie, MMaze::Couleur couleur); 
        Tuile(); 
        ~Tuile(); 
        void init_depart(UnionFind UF);
        void init_classique(UnionFind UF); 
        void init_classique(UnionFind UF, bool objectif, bool sortie, MMaze::Couleur couleur); 

        void determiner_portes(int nombre, bool tuil_classique);
        void genererLabyrinthe(UnionFind UF); 
        void genererObectif();
        void genererSortie();

        void genererObectif(MMaze::Couleur couleur);
        void genererSortie(MMaze::Couleur couleur);

        void detection_case_non_necessaire(UnionFind UF); 
        bool tousLeMemeRacine(UnionFind UF); 
        void casser_murs_entre_boutiques(); 
        int recuperere_murs_case(Case C, int tab_return[4]);
        int obtientMurEntreCases(Case C1, Case C2); 

        /*----------- rotation tuile ---------------------*/ 
        void rotation_tuile(int rotation); 
        // fonction qui genere le tuile a les coordination (l,c) 
        Tuile generation_tuile(Couleur C, PadPlateau& p, int l , int c, int indice);
        // fonction qui place les elements de plateau sur le tuile --> pour l'affichage 
        void placement_elements(PadPlateau& pad, int pos1, int pos2); 

        /*----------- autres ---------------------------*/ 
        //fonction renvoie d'index de tuile 
        unsigned int acces() const ;
        //fonction pour faire Si deux cases adjacentes sont séparées par un mur
        bool sepmur(Mur m) const;
        //fonction pour  si une case est accessible depuis les portes ou non
        //bool accessible(Case c , UnionFind UF) const ;
        // foction pour  si la tuile possède un object ou sortie
        bool site();

    private :
    //valeur pour fonction accessible et fonction return index de tuile
    unsigned int acc;
    //valeur pour fonction Site
    unsigned int typeSite ;
}; 

#endif 