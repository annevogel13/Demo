#include "graph_tuile.hpp"
#include "graph_supermarket.hpp"
#include "noeud_case.hpp"
#include "melangeur.hpp"
#include <iostream>
#include <assert.h>
using namespace std; 

int main(){

    MelangeurOptions::imprevisible(); 
    PadPlateau pad ; 
    pad.ajouter_tuile(0,1); 

    // false indique que c'est un tuile normale 
    Tuile T(true, 0, 0,1); 
    T.placement_elements(pad, 0,1); 

    cout<<pad<<endl; 
    
    /*--------------- test construction de coup ----------------- */
    /*
    Case C1(4);
    Coup CC(C1, T, MMaze::Direction::DROITE); 
    
    CC.afficherCoup(); */

    /*-------------- test construction de Noeud_case ------------ */
    
    // on commence l'init a 13 parce que ce case est toujours inclus 
    //Case CasTest(13); 
    //Noeud_case NC(CasTest, T);

    /*------------check operateur= ---------------------*/
    /* 
    Case cT1(2);
    Case cT2(11);
    Noeud_case NCT(cT1, T);
    Noeud_case NCT2(cT2, T); 
    NCT.afficher(); 
    NCT2.afficher(); 
    
    NCT = NCT2; 
    NCT.afficher(); */

    cout<<"/*-------------- Test graph ------------------------------*/"<<endl; 
    
    cout<<endl<<"les fleches x <-- y , on doit le lire comme cela x <-- y : x est le predesseur de y"<<endl<<endl; 
    Noeud_case contenu_temp[16];
    Graph_tuile GT(T, 0,1); 
    GT.affichage(); 

    cout<<"/*-------------- Test supermarche (init) ------------------------------*/"<<endl; 
    Graph_supermarket GS; 

    cout<<"/*-------------- Test supermarche (ajouter tuiles) ------------------------------*/"<<endl; 
    
    bool a,b ; 
    a = b = false; 
    //cout<<"         Essayer ajoute une tuile en porte JAUNE "<<endl; 
    a = GS.ajoute_tuile(MMaze::Couleur::JAUNE, GS.contenue_supermarket[0].tuile); 

    cout<<GS.pad<<endl; 
    if(a){
        //cout<<"         Essayer ajoute une tuile en tuile 1 porte Jaune "<<endl; 
        b = GS.ajoute_tuile(MMaze::Couleur::JAUNE, GS.contenue_supermarket[1].tuile); 
    }
    
    if(b == false){
        //cout<<"         Essayer ajoute une tuile en tuile 1 porte Vert "<<endl; 
        b = GS.ajoute_tuile(MMaze::Couleur::VERT, GS.contenue_supermarket[1].tuile); 
    }

    
    return -1; 
}