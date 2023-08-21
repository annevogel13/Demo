#include "graph_tuile.hpp"
#include "noeud_case.hpp"

Graph_tuile::Graph_tuile(){
    tuile = Tuile(); 
    //acces_portes[4] = {false}; 
}


Graph_tuile::Graph_tuile(Tuile T){
    tuile = T;  
    acces_portes[4] = {false}; 

    for(int i = 0 ; i< 16 ; i++){
        
        if((T.tab_cases_contenue[i] == MMaze::Site::BOUTIQUE) == false){ 
            Noeud_case N(Case(i), T); 
            contenue[i] = N ; 

            if(type_site(T.tab_cases_contenue[i]) == MMaze::Site::PORTE ){
                    if(i ==  2) acces_portes[0] = true; 
                    if(i ==  4) acces_portes[1] = true; 
                    if(i == 11) acces_portes[2] = true; 
                    if(i == 13) acces_portes[3] = true; 
            }
        }
    }

    remplirPred(); 
}


Graph_tuile::Graph_tuile(Tuile T, int l , int c){
    tuile = T;  
    acces_portes[4] = {false}; 
    

    for(int i = 0 ; i< 16 ; i++){
        
        if((T.tab_cases_contenue[i] == MMaze::Site::BOUTIQUE) == false){ 
            Noeud_case N(Case(i), T); 
            contenue[i] = N ; 

            if(type_site(T.tab_cases_contenue[i]) == MMaze::Site::PORTE ){
                    if(i ==  2) acces_portes[0] = true; 
                    if(i ==  4) acces_portes[1] = true; 
                    if(i == 11) acces_portes[2] = true; 
                    if(i == 13) acces_portes[3] = true; 
            }
        }
    }

    remplirPred(); 
}

void Graph_tuile::remplirPred(){
    
    for(int i = 0 ; i < 16 ; i++){
        // veut dire que Noeud_case de Case(i) existe
        if(contenue[i].nbCoupsPossible != 0){
            // pour chaque coups possible on repmli le pred 
            
            Noeud_case* nc_pred = &contenue[i];  
            for(int j = 0 ; j < contenue[i].nbCoupsPossible ; j++){ 
                // on recupere le index de casefin d'un coup 
                int ind_courant = nc_pred->possibleCoups[j].caseFin.index();
                Noeud_case* nc_courant = &contenue[ind_courant]; 
                // dans le conenue on ajoute aux vector predecesseur le case ou on est maintenant
                contenue[ind_courant].predecesseur.push_back(nc_pred); 
                contenue[nc_pred->C.index()].voisins.push_back(nc_courant);
            } 
            
        }
    }  
}


void Graph_tuile::affichage(){
    cout<<"placement dans pad : "<<tuile.tuile_l<<" , "<<tuile.tuile_c<<endl; 
    for(int i = 0 ; i< 16 ; i++){
        if(contenue[i].nbCoupsPossible != 0){
            contenue[i].afficher(); 
        }     
    }

} 

Graph_tuile* Graph_tuile::operator=(Graph_tuile GT){

    for(int i = 0 ; i < 16 ; i++){
        this->contenue[i] = GT.contenue[i];
    }

    this->tuile = GT.tuile; 
    this->acces_portes[0] = GT.acces_portes[0];
    this->acces_portes[1] = GT.acces_portes[1];
    this->acces_portes[2] = GT.acces_portes[2];
    this->acces_portes[3] = GT.acces_portes[3];

    return this; 
}

Graph_tuile::~Graph_tuile(){
    //cout<<"Destructor Graph_tuile"<<endl; 
}


