#include "draw.hpp"
#include "tuile.hpp"
#include <iostream>
#include "melangeur.hpp"
#include "dijkstra.hpp"

using namespace MMaze;
using namespace std; 

#include <assert.h>

int main() {
    
    MelangeurOptions::imprevisible(); 
    PadPlateau pad ; 
    pad.ajouter_tuile(0,0); 


    parcour P;
    P.trever_lar(16);



    cout<<pad<<endl;
    //cout<<"hello world"<<endl;
    
    return -1;
    }
