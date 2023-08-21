#include "draw.hpp"
#include "tuile.hpp"
#include <iostream>
#include "melangeur.hpp"
using namespace MMaze;
using namespace std; 

#include <assert.h>

int main() {

    MelangeurOptions::imprevisible(); 
    PadPlateau pad ; 
    pad.ajouter_tuile(0,0); 

    // false indique que c'est un tuile normale 
    Tuile T(false, 0, 0, 0); 
    T.placement_elements(pad, 0,0); 
    cout<<endl<<"Ceci c'est un tuile classique (pour afficher l'autre make test_tuile)"<<endl<<endl; 
    cout<<pad<<endl; 

    assert(T.obtientMurEntreCases(Case(0), Case(4)) == 0);
    assert(T.obtientMurEntreCases(Case(1), Case(5)) == 1);
    assert(T.obtientMurEntreCases(Case(2), Case(6)) == 2); 
    return -1; 
}