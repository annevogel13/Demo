#include "graph_supermarket.hpp"
#include "melangeur.hpp"
#include <iostream>
using namespace std; 

Graph_supermarket::Graph_supermarket(){ 
    pad.ajouter_tuile(0,0); 
    Tuile D(true, 0, 0, 0);
    D.placement_elements(pad, 0,0); 
    Graph_tuile GT(D); 

    // affiche le tuile de debut
    cout<<"Initialisatoin du Supermarket "<<endl<<endl; 
    cout<<pad<<endl; 

    contenue_supermarket[0] = GT;
    nb_tuiles = 1; 

    /* essayer de remplir les tuiles dans l'ensemble. Et pas un par une. Pas assez de temps pour finir 
    Melangeur <bool> objectif; 
    Melangeur <bool> sortie; 
    // les quatres objectives 
    objectif.inserer(true); sortie.inserer(true);
    objectif.inserer(true); sortie.inserer(true);
    objectif.inserer(true); sortie.inserer(true);
    objectif.inserer(true); sortie.inserer(true);    

    for(int i = 4 ; i < 12 ; i++){ 
        objectif.inserer(false); 
        sortie.inserer(false); 
    }

    int curseur_ob = 0 ;
    int curseur_so = 0 ;

    for(int i = 1 ; i < 16 ; i++){
        bool a = objectif.retirer();  
        bool b = sortie.retirer();  
        if(a){
            Tuile tmp(false, nb_tuiles, true, false, couleurs[curseur_ob]);
            Graph_tuile GT(tmp); 
            contenue_supermarket[i] = GT; 
            curseur_ob++; 
        }else if(b){
            
            Tuile tmp(false, nb_tuiles, false, true, couleurs[curseur_so]);
            Graph_tuile GT(tmp);
            contenue_supermarket[i] = GT; 
            curseur_so++;
        }else{
            Tuile tmp(false, nb_tuiles, false, false, couleurs[0]);
            Graph_tuile GT(tmp); 
            contenue_supermarket[i] = GT; 
        }

    } */ 
}


Graph_supermarket::~Graph_supermarket(){
    //contenue_supermarket.clear(); 
    //cout<<"Destructeur graph_supermarket"<<endl; 
    
}


bool Graph_supermarket::ajoute_tuile(MMaze::Couleur couleur_porte, Tuile voisin){
    
    bool a_porte_bonne_couleur = false; 
    int c = 0 ; // indice du case ou le porte se situe 
    int p = 0 ; // place dans le acces_portes[]
    // verifier si on a bien un porte de couleur couleur_porte 
    if((type_site(voisin.tab_cases_contenue[2])  == MMaze::Site::PORTE) && (couleur_site(voisin.tab_cases_contenue[2])  == couleur_porte))  { p = 0 ; c = 2 ; a_porte_bonne_couleur = true ; }
    if((type_site(voisin.tab_cases_contenue[4])  == MMaze::Site::PORTE) && (couleur_site(voisin.tab_cases_contenue[4])  == couleur_porte))  { p = 1 ;  c = 4 ; a_porte_bonne_couleur = true ; }
    if((type_site(voisin.tab_cases_contenue[11]) == MMaze::Site::PORTE) && (couleur_site(voisin.tab_cases_contenue[11]) == couleur_porte)) { p = 2 ; c = 11; a_porte_bonne_couleur = true ; }
    if((type_site(voisin.tab_cases_contenue[13]) == MMaze::Site::PORTE) && (couleur_site(voisin.tab_cases_contenue[13]) == couleur_porte)) { p = 3 ; c = 13; a_porte_bonne_couleur = true ; }

    if(a_porte_bonne_couleur){
        Tuile r = voisin.generation_tuile(couleur_porte, pad, voisin.tuile_l, voisin.tuile_c, voisin.acces()+1); 
        // creation de graphe 
        Graph_tuile GT(r); 
        // sauvegarde le dans le contenue_supermarket 
        contenue_supermarket[nb_tuiles] = GT; 
        // augmenter le taille de nb_tuiles; 
        nb_tuiles++; 

        // mettre le port dans Graph_tuile a vrai
        contenue_supermarket[voisin.acces()].acces_portes[p] = true;  

        cout<<"Ajoute une tuile aux porte "<<c<<" aux avec les coordonnees ( "<<r.tuile_l<<" , "<<r.tuile_c<<" )"<<endl; 
        cout<<pad<<endl; 
        ajoute_voisins(contenue_supermarket[voisin.acces()], contenue_supermarket[nb_tuiles-1], c ); 
        
        return true; 
    }else{ 
        cout<<"Le couleur choisi n'est pas dans le tuile( "<<voisin.tuile_l<<" , "<<voisin.tuile_c<<" )"<<endl<<endl;  
        return false; 
    }
}

Graph_supermarket* Graph_supermarket::operator =(Graph_supermarket GS){
    this->nb_tuiles = GS.nb_tuiles ; 
    this->pad = GS.pad; 
    
    for(int i = 0 ; i < GS.nb_tuiles ; i++){
        this->contenue_supermarket[i] = GS.contenue_supermarket[i]; 
    }

    return this; 

}

Coup Graph_supermarket::ajoute_coup(int origin, int dest, MMaze::Direction d, Graph_tuile GT, int t_debut, int t_fin){
        Coup CO(Case(origin), Case(dest), d, GT.tuile.acces());
        // on dit si on change de tuile 
        CO.tuile_de_case_debut = t_debut;
        CO.tuile_de_case_fin = t_fin;

        // on ajoute les coups dans les graphes 
        GT.contenue[origin].possibleCoups.push_back(CO); 
        GT.contenue[origin].nbCoupsPossible++;

        // pour de raison de debuggage 
        return CO; 
}

// GT c'est le tuile qu'on viens de ajouter -> et du coup on dois ajouter des voisins si il existe
void Graph_supermarket::ajoute_voisins(Graph_tuile courante, Graph_tuile destination,  int indice_porte){
    
    /*    courante                             destination 
    porte 2  : direction haut        porte 2 -> 13   : direction bas   
    porte 4  : direction gauche      porte 4 -> 11   : direction droite
    porte 11 : direction droite      porte 11 -> 4   : direction gauche  
    porte 13 : direction bas         porte 13 -> 2   : direction haut */

    // recupere les coups a ajouter dans le courante a partir du Noeud_case indice porte 
    int port_adjecent = 0 ;
    MMaze::Direction d ; 
    // on trouve les portes qui peut être connecte 
    if(indice_porte == 2) { port_adjecent = 13; d = MMaze::Direction::HAUT; }
    if(indice_porte == 4) { port_adjecent = 11; d = MMaze::Direction::GAUCHE;} 
    if(indice_porte == 11) { port_adjecent = 4; d = MMaze::Direction::DROITE;} 
    if(indice_porte == 13) { port_adjecent = 2; d = MMaze::Direction::BAS;}

    int t_debut = courante.tuile.acces();
    int t_fin =  destination.tuile.acces();
    // ajoute les coups facile (entre les deux portes par exemple (2,13) ou (4,11))
    Coup co_port = ajoute_coup(indice_porte, port_adjecent, d, courante, t_debut, t_fin );
    Coup cd_port = ajoute_coup(port_adjecent, indice_porte,  d, destination, t_fin, t_debut);
    co_port.afficherCoup();

    // initialisation des variables a utilise dans le boucle for 
    Noeud_case nc_tmp = destination.contenue[port_adjecent];      
    int origin = destination.contenue[port_adjecent].C.index(); 

    for(int i = 0 ; i < nc_tmp.nbCoupsPossible ; i++ ){
        int dest = nc_tmp.possibleCoups[i].caseFin.index(); 
        // on decide sur quelle porte on travaille 
        switch (indice_porte){
            case 2 : 
                // si le coup a le bonne direction (qui peut continuer), on l'ajoute 
                if(nc_tmp.possibleCoups[i].d == MMaze::Direction::HAUT){
                    // on l'ajoute dans les deux sense 
                    Coup CO = ajoute_coup(origin, dest, MMaze::Direction::HAUT, courante, t_debut, t_fin);
                    Coup CD = ajoute_coup(dest, origin, MMaze::Direction::HAUT, destination, t_fin, t_debut);
                    CO.afficherCoup(); 
            } break; 
            case 4 :
                if(nc_tmp.possibleCoups[i].d == MMaze::Direction::GAUCHE){
                    
                    Coup CO = ajoute_coup(origin, dest, MMaze::Direction::GAUCHE, courante, t_debut, t_fin);
                    Coup CD = ajoute_coup(dest, origin, MMaze::Direction::GAUCHE, destination, t_fin, t_debut);
                    CO.afficherCoup(); 
                }
                break; 
            case 11:
                if(nc_tmp.possibleCoups[i].d == MMaze::Direction::DROITE){
                    
                    Coup CO = ajoute_coup(origin, dest, MMaze::Direction::DROITE, courante, t_debut, t_fin);
                    Coup CD = ajoute_coup(dest, origin, MMaze::Direction::DROITE, destination, t_fin, t_debut);
                    CO.afficherCoup(); 
                    
                }
                break; 
            case 13: 
                if(nc_tmp.possibleCoups[i].d == MMaze::Direction::BAS){

                    Coup CO = ajoute_coup(origin, dest, MMaze::Direction::BAS, courante, t_debut, t_fin);
                    Coup CD = ajoute_coup(dest, origin, MMaze::Direction::BAS, destination, t_fin, t_debut);
                    CO.afficherCoup(); 
                }
                break;
            default: break;  
        }
    }
    cout<<endl<<endl; 

    // relancer les remplir_pred() de Graph_tuile comme cela les coups seront ajoute dans les predecceseur 
    courante.remplirPred(); 
    destination.remplirPred(); 
}



void Graph_supermarket::afficher(){

    cout<<endl<<pad<<endl; 
    
    cout<<"Coordonees de tuiles : "<<endl; 
    cout<<contenue_supermarket[0].tuile.tuile_l<<endl; 
    cout<<contenue_supermarket[0].tuile.tuile_c<<endl; 
    cout<<endl; 
}

