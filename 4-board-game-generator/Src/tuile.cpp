#include "tuile.hpp"
#include <iostream>
#include "melangeur.hpp"
#include "unionfind.hpp"
#include "mur.hpp"
#include "draw.hpp"

#include <assert.h>
#include <vector> 
using namespace MMaze; 


bool Tuile::tousLeMemeRacine(UnionFind UF){
    vector <int> necessaire; 
    
    for(int i = 0 ; i<16; i++){
        if(!(tab_cases_contenue[i] == Site::AUCUN) || (tab_cases_contenue[i] == Site::BOUTIQUE)){
            necessaire.push_back(i); 
        }
    }

    int racine1 = UF.trouver_racine(necessaire[0]);
        
    int len = necessaire.size(); 
    for(int i = 1 ; i < len ; i++){
        if( UF.trouver_racine(necessaire[i]) != racine1){
                return false; 
        }
    }
    
    this->racine_path = racine1; /*
    cout<<"indices de cases necessaires : ";
    for(int i = 0 ; i < len ; i++){
        cout<<necessaire[i]<<" ";
    } 
    cout<<endl; */
    return true;    
}

// fonction qui retourne le nombre de murs qui sont UP et retourne (par reference) le tab_return[4] avec les indices des murs du case C
int Tuile::recuperere_murs_case(Case C, int tab_return[4]){

    int border = 0 ; 
    int i = C.index();
    
    if(C.ligne() > 0)   tab_return[0] = obtientMurEntreCases(C.haut(), C); else border++;
    if(C.ligne() < 3)   tab_return[2] = obtientMurEntreCases(C.bas(),  C); else border++;   
    if(C.colonne() > 0) tab_return[3] = obtientMurEntreCases(C.gauche(),  C); else border++;
    if(C.colonne() < 3) tab_return[1] = obtientMurEntreCases(C.droite(), C); else border++; 
    
    // veut dire que on a une porte, donc c'est un mur en moins
    if(tab_cases_contenue[i] == MMaze::Site::PORTE) border = 0 ; 
    return border; 
}

void Tuile::casser_murs_entre_boutiques(){
    vector <int> tmp ; 
    for(int i = 0 ; i < 16 ; i++){
        if( tab_cases_contenue[i] == Site::BOUTIQUE){
            tmp.push_back(i); 
        }
    }
    int len = tmp.size(); 
    for(int i = 0 ; i < len; i++){
        Case C1(tmp[i]);
    	// verifie le case a gauche 
        if(i + 1 < len){
            Case C2(tmp[i+1]); 
            int m1 = obtientMurEntreCases(C1, C2); 
            tab_murs[m1] = false; 
        }
        // verifie le case en bas 
        if(i + 4 < len){
            Case C3(tmp[i+4]); 
            int m2 = obtientMurEntreCases(C1, C3); 
            tab_murs[m2] = false; 
        }  
    }
} 

int Tuile::obtientMurEntreCases(Case C1, Case C2){

    if((C1.ligne() > 0) && (C1.haut() == C2))  return min(C1.index(), C2.index()) ; 
    if((C1.ligne() < 3) && (C1.bas() == C2))   return min(C1.index(), C2.index()) ; 
    if((C1.colonne() > 0) && (C1.gauche() == C2))  return 12 + 4 * (C1.colonne() -1 ) + 1 * C1.ligne() ;
    if((C1.colonne() < 3) && (C1.droite() == C2))  return 12 + 4 * (C2.colonne() -1 ) + 1 * C2.ligne() ;
    
    return -1 ; // indique que les deux cases ne sont pas voisine 
}

// compter le nombre de mur qu'un cases a, et ajouter un boutique si c'est >= 3 
void Tuile::detection_case_non_necessaire(UnionFind UF){
    // on parcour tous les cases 
    int i =  0 ; 
    while(i<16){ 
        Case C(i); 
        // si le case a comme Site Aucun 
        if(tab_cases_contenue[i] == Site::AUCUN){
            // on cree le case, pour ensuite recupere le ligne et colonne 
            // initialise le tab_tmp_mur 
            int tab_tmp_mur[4] = {-1,-1,-1,-1}; // on initialise a -1 comme detection des erreurs 
            int b = recuperere_murs_case(C, tab_tmp_mur); 

            int compteur_murs = 0 ; 
            for(int m = 0 ; m < 4 ; m++){
                // index du mur 
                int index = tab_tmp_mur[m]; 
                if(tab_tmp_mur[m] > -1){
                    if(tab_murs[index] == true){
                        compteur_murs++; 
                    }
                }
            }

            // si il existe plus que 2 murs --> case non necesaire --> boutique 
            if((compteur_murs + b) >= 3){
                tab_cases_contenue[i] = Site::BOUTIQUE; 
                
                // mettre tous les murs dans les boutiques UP
                for(int j = 0 ; j < 4 ; j++){
                    if(tab_tmp_mur[j] != -1){
                        tab_murs[tab_tmp_mur[j]] = true;  
                        // repasser au ligne avant pour re-calculer le ligne 
                        if(i>5){
                            i = i - 5 ;
                        }else i = 0 ;   
                        
                    }   
                } 
            } 
        }
        i++;
    }

    casser_murs_entre_boutiques(); 
}

void Tuile::determiner_portes(int nombre, bool tuil_classique){
    
        // les quatres portes avec des couleurs aleatoires   
        Melangeur <int> melCouleur; 
        for(int i = 0 ; i < 4 ; i++) melCouleur.inserer(i);
        
        // les nombre de portes sur des places aleatoires 
        Melangeur <int> nbPortes; 
        int tab_places_port[4] = {2,4,11,13}; 
        for(int i = 0 ; i < nombre; i++) nbPortes.inserer(tab_places_port[i]); 

        for(int i = 0 ; i < nombre ; i++){
            tab_cases_contenue[nbPortes.retirer()] = colorer_site(MMaze::Site::PORTE, couleurs[melCouleur.retirer()]); 
        }

        if(tuil_classique) tab_cases_contenue[13] = MMaze::Site::PORTE; 
}

void Tuile::genererLabyrinthe(UnionFind UF){

    Melangeur <int> mel; 

    for(int i =0 ; i < 24 ; i++) mel.inserer(i);
        
    int j = 0 ;
    while((j < 24) && !tousLeMemeRacine(UF)){    
        j++; 
        int r1 = mel.retirer(); 
        
        Mur mur_tmp(r1); 
        Case case1 = mur_tmp[0]; // voisin haut/gauche        
        Case case2 = mur_tmp[1]; // voisin bas/droite 

        int indiceCase1 = case1.index(); 
        int indiceCase2 = case2.index(); 

        // calculer racine
        int racine1 = UF.trouver_racine(indiceCase1); 
        int racine2 = UF.trouver_racine(indiceCase2); 
        
        // dans le meme ensemble 
        if(UF.dans_meme_ensemble(racine1, racine2)){
            // else tab_murs[r1] = true;  // --> garder le mur 
        }else{
            tab_murs[r1] = false ; // abbatre le mur 
            UF.union_ensembles(racine1, racine2);                     
            }       
    }
}


void Tuile::genererObectif(){


    Melangeur <int> melCouleur; 
    for(int i = 0 ; i < 4 ; i++) melCouleur.inserer(i);

    Melangeur <int> placementObjectif; 
    for(int i = 0 ; i < 16 ; i++) placementObjectif.inserer(i);

    int p = placementObjectif.retirer(); 
    
    while(type_site(tab_cases_contenue[p]) == MMaze::Site::PORTE){
        p = placementObjectif.retirer(); 
    }
    tab_cases_contenue[p] = colorer_site(MMaze::Site::OBJECTIF, couleurs[melCouleur.retirer()]);
    
}

void Tuile::genererObectif(MMaze::Couleur couleur){

    Melangeur <int> placementObjectif; 
    for(int i = 0 ; i < 16 ; i++) placementObjectif.inserer(i);

    int p = placementObjectif.retirer(); 
    
    while(type_site(tab_cases_contenue[p]) == MMaze::Site::PORTE){
        p = placementObjectif.retirer(); 
    }
    tab_cases_contenue[p] = colorer_site(MMaze::Site::OBJECTIF, couleur);
    
}

void Tuile::genererSortie(){

    Melangeur <int> melCouleur; 
    for(int i = 0 ; i < 4 ; i++) melCouleur.inserer(i);
    
    Melangeur <int> placementSortie; 
    for(int i = 0 ; i < 16 ; i++) placementSortie.inserer(i);

    int p = placementSortie.retirer(); 
    while(type_site(tab_cases_contenue[p]) == MMaze::Site::PORTE){
        p = placementSortie.retirer(); 
    }
    tab_cases_contenue[p] = colorer_site(MMaze::Site::SORTIE, couleurs[melCouleur.retirer()]); 
    
}


void Tuile::genererSortie(MMaze::Couleur couleur){
    
    Melangeur <int> placementSortie; 
    for(int i = 0 ; i < 16 ; i++) placementSortie.inserer(i);

    int p = placementSortie.retirer(); 
    while(type_site(tab_cases_contenue[p]) == MMaze::Site::PORTE){
        p = placementSortie.retirer(); 
    }
    tab_cases_contenue[p] = colorer_site(MMaze::Site::SORTIE, couleur); 
    
}

void Tuile::init_depart(UnionFind UF){

    // entre les joueurs de depart il y n'a pas une mur 
    tab_murs[5] = false ; 
    tab_murs[6] = false ; 
    tab_murs[17] = false; 
    tab_murs[18] = false; 

    // placement des differents portes 
    determiner_portes(4, false); 

    // repartitions des joueurs sur les places de depart 
    Melangeur <int> melCouleur2; 

    for(int i = 0 ; i < 4 ; i++) melCouleur2.inserer(i);
    // les quatres departs avec des couleurs aleotoires        
    tab_cases_contenue[5]  = colorer_site(MMaze::Site::DEPART, couleurs[melCouleur2.retirer()]); 
    tab_cases_contenue[6]  = colorer_site(MMaze::Site::DEPART, couleurs[melCouleur2.retirer()]); 
    tab_cases_contenue[9]  = colorer_site(MMaze::Site::DEPART, couleurs[melCouleur2.retirer()]); 
    tab_cases_contenue[10] = colorer_site(MMaze::Site::DEPART, couleurs[melCouleur2.retirer()]);  

    /*---------GENERATION LABYRINTHE------------------------------*/
    genererLabyrinthe(UF); 
    detection_case_non_necessaire(UF); 
}

void Tuile::init_classique(UnionFind UF){

    /*---------- PORTES --------------------------------------------*/     
    Melangeur <int> nombrePorts; 
    for(int i = 0 ; i < 4 ; i++) nombrePorts.inserer(i); 
    int nbPortes = nombrePorts.retirer(); 
    while(nbPortes == 0){
        nbPortes = nombrePorts.retirer(); 
    }

    determiner_portes(nbPortes, true); 

    /*---------OBJECIF-OU-SORTIE----------------------------------*/
    Melangeur <bool> objectVSsortie; 
    // soit 1 objectif ou un sortie ou rien 
    objectVSsortie.inserer(true);
    objectVSsortie.inserer(false); 
    objectVSsortie.inserer(false);

    if(objectVSsortie.retirer()){
        //std::cout<<"Objectif"<<endl; 
        genererObectif();
    }  

    if(objectVSsortie.retirer()){
        //std::cout<<"Sortie"<<endl; 
        genererSortie(); 
    } 

    /*---------GENERATION LABYRINTHE------------------------------*/
    genererLabyrinthe(UF); 
    detection_case_non_necessaire(UF); 
    
}

void Tuile::init_classique(UnionFind UF, bool objectif, bool sortie, MMaze::Couleur couleur){

    /*---------- PORTES --------------------------------------------*/     
    Melangeur <int> nombrePorts; 
    for(int i = 0 ; i < 4 ; i++) nombrePorts.inserer(i); 
    int nbPortes = nombrePorts.retirer(); 
    while(nbPortes == 0){
        nbPortes = nombrePorts.retirer(); 
    }

    determiner_portes(nbPortes, true); 

    /*---------OBJECIF-OU-SORTIE----------------------------------*/
    // soit l'une est vrai soit l'autre, soit aucun 

    assert((objectif == !sortie) || (objectif == false && sortie == false)); 

    if(objectif)    genererObectif(couleur);
    if(sortie)      genererSortie(couleur); 
    

    /*---------GENERATION LABYRINTHE------------------------------*/
    genererLabyrinthe(UF); 
    detection_case_non_necessaire(UF); 
    
}

Tuile::Tuile(bool type_tuile, int index, int l , int c ){ 
    tuile_c = c; 
    tuile_l = l; 
    acc = index ; 
    depart = type_tuile; 
    UnionFind UF(16); 
    
    /*---------INITIALISATION DES TUILES--------------------------*/
    // mettre tous les murs en UP
    for(int i = 0 ; i < 24 ; i++) tab_murs[i] = true;  
    // donne a chaque case le site AUCUN     
    for(int i = 0 ; i < 16; i++) tab_cases_contenue[i] = MMaze::Site::AUCUN; 
    
    /*---------PLACEMENT DES ELEMENT DU JEU-----------------------*/
    if(depart){
        init_depart(UF); 
    }else init_classique(UF); 

    tousLeMemeRacine(UF); // stoquer le racine du path principale 

}

Tuile::Tuile(bool type_tuile, int index, bool objective, bool sortie, MMaze::Couleur couleur){ 
    acc = index ; 
    depart = type_tuile; 
    UnionFind UF(16); 
    
    /*---------INITIALISATION DES TUILES--------------------------*/
    // mettre tous les murs en UP
    for(int i = 0 ; i < 24 ; i++) tab_murs[i] = true;  
    // donne a chaque case le site AUCUN     
    for(int i = 0 ; i < 16; i++) tab_cases_contenue[i] = MMaze::Site::AUCUN; 
    
    /*---------PLACEMENT DES ELEMENT DU JEU-----------------------*/
    init_classique(UF, objective, sortie, couleur); 

    tousLeMemeRacine(UF); // stoquer le racine du path principale 

}


void Tuile::rotation_tuile(int rotation){
    
    // rotation cases 
    Site tmp_tab_cases[16];
    for(int i = 0 ; i < 16 ; i++){
        
        Case C_tmp = Case(i); 
        Case C_new = C_tmp.tourne(rotation);
        tmp_tab_cases[C_new.index()] = this->tab_cases_contenue[i]; 
    }

    // rotation murs 
    bool tmp_tab_murs[24];
    for(int j = 0 ; j < 24 ; j++){
        
        Mur M_tmp = Mur(j); 
        Mur M_new = M_tmp.tourne(rotation); 
        tmp_tab_murs[M_new.index()] = this->tab_murs[j]; 
    }

    // mettre le tmp_tab_cases dans les donnes de Tuile 
    for(int k = 0 ; k < 16 ; k++) tab_cases_contenue[k] = tmp_tab_cases[k];    
    for(int m = 0 ; m < 24 ; m++) tab_murs[m] = tmp_tab_murs[m];

} 



void Tuile::placement_elements(PadPlateau& pad, int pos1, int pos2){
    
    for(int i = 0 ; i<24; i++){
        if(tab_murs[i]) pad.ajouter_mur(pos1,pos2, Mur(i)); 
    }

    for(int i = 0 ; i < 16 ; i++){
        switch (tab_cases_contenue[i]){ 
            case MMaze::Site::PORTE             : pad.ajouter_porte(pos1,pos2, Case(i) , MMaze::Couleur::AUCUNE); break; 
            case MMaze::Site::PORTE_JAUNE       : pad.ajouter_porte(pos1,pos2, Case(i) , couleur_site(tab_cases_contenue[i])); break; 
            case MMaze::Site::PORTE_ORANGE      : pad.ajouter_porte(pos1,pos2, Case(i) , couleur_site(tab_cases_contenue[i])); break; 
            case MMaze::Site::PORTE_VERTE       : pad.ajouter_porte(pos1,pos2, Case(i) , couleur_site(tab_cases_contenue[i])); break; 
            case MMaze::Site::PORTE_VIOLETTE    : pad.ajouter_porte(pos1,pos2, Case(i) , couleur_site(tab_cases_contenue[i])); break; 
            
            case MMaze::Site::SORTIE            : pad.ajouter_sortie(pos1,pos2, Case(i) , couleur_site(tab_cases_contenue[i])); break; 
            case MMaze::Site::SORTIE_JAUNE      : pad.ajouter_sortie(pos1,pos2, Case(i) , couleur_site(tab_cases_contenue[i])); break; 
            case MMaze::Site::SORTIE_ORANGE     : pad.ajouter_sortie(pos1,pos2, Case(i) , couleur_site(tab_cases_contenue[i])); break; 
            case MMaze::Site::SORTIE_VERTE      : pad.ajouter_sortie(pos1,pos2, Case(i) , couleur_site(tab_cases_contenue[i])); break; 
            case MMaze::Site::SORTIE_VIOLETTE   : pad.ajouter_sortie(pos1,pos2, Case(i) , couleur_site(tab_cases_contenue[i])); break; 
            
            case MMaze::Site::OBJECTIF          : pad.ajouter_objectif(pos1,pos2, Case(i) , couleur_site(tab_cases_contenue[i])); break; 
            case MMaze::Site::OBJECTIF_JAUNE    : pad.ajouter_objectif(pos1,pos2, Case(i) , couleur_site(tab_cases_contenue[i])); break; 
            case MMaze::Site::OBJECTIF_ORANGE   : pad.ajouter_objectif(pos1,pos2, Case(i) , couleur_site(tab_cases_contenue[i])); break; 
            case MMaze::Site::OBJECTIF_VERT     : pad.ajouter_objectif(pos1,pos2, Case(i) , couleur_site(tab_cases_contenue[i])); break; 
            case MMaze::Site::OBJECTIF_VIOLET   : pad.ajouter_objectif(pos1,pos2, Case(i) , couleur_site(tab_cases_contenue[i])); break; 

            case MMaze::Site::VORTEX            : pad.ajouter_vortex(pos1,pos2, Case(i) , couleur_site(tab_cases_contenue[i])); break; 
            case MMaze::Site::VORTEX_JAUNE      : pad.ajouter_vortex(pos1,pos2, Case(i) , couleur_site(tab_cases_contenue[i])); break; 
            case MMaze::Site::VORTEX_ORANGE     : pad.ajouter_vortex(pos1,pos2, Case(i) , couleur_site(tab_cases_contenue[i])); break; 
            case MMaze::Site::VORTEX_VERT       : pad.ajouter_vortex(pos1,pos2, Case(i) , couleur_site(tab_cases_contenue[i])); break; 
            case MMaze::Site::VORTEX_VIOLET     : pad.ajouter_vortex(pos1,pos2, Case(i) , couleur_site(tab_cases_contenue[i])); break; 

            case MMaze::Site::DEPART            : pad.placer_joueur(pos1,pos2, Case(i) , couleur_site(tab_cases_contenue[i])); break; 
            case MMaze::Site::DEPART_JAUNE      : pad.placer_joueur(pos1,pos2, Case(i) , couleur_site(tab_cases_contenue[i])); break; 
            case MMaze::Site::DEPART_ORANGE     : pad.placer_joueur(pos1,pos2, Case(i) , couleur_site(tab_cases_contenue[i])); break; 
            case MMaze::Site::DEPART_VERTE      : pad.placer_joueur(pos1,pos2, Case(i) , couleur_site(tab_cases_contenue[i])); break; 
            case MMaze::Site::DEPART_VIOLETTE   : pad.placer_joueur(pos1,pos2, Case(i) , couleur_site(tab_cases_contenue[i])); break; 

            case MMaze::Site::BOUTIQUE          : pad.ajouter_boutique(pos1,pos2, Case(i)); break; 
            case MMaze::Site::AUCUN             : break; 
        }
    }

}

Tuile::Tuile(){
    depart = false; 
    tab_murs[24] = {false};

}

Tuile::~Tuile(){
    vecM.clear(); 
}

Tuile Tuile::generation_tuile(Couleur C, PadPlateau& p, int l , int c, int indice){
    int r = 0 ; 
    Tuile next(false, indice, l ,c);
    for(int i = 0 ; i< 16; i++){
        if((type_site(tab_cases_contenue[i]) == Site::PORTE) &&  (couleur_site(tab_cases_contenue[i]) == C)){
            if(i == 2)  r =  0, l = l - 1; 
            if(i == 4)  r =  1, c = c - 1;   
            if(i == 11) r = -1, c = c + 1;
            if(i == 13) r =  2, l = l + 1; 
            
        }
    }
    next.tuile_l = l ; 
    next.tuile_c = c ; 
    next.rotation_tuile(r); 
    p.ajouter_tuile(l, c);
    next.placement_elements(p, l,c); 
    //cout<<l<<" , "<<c<<endl; 
    return next; 
}

//renvoie d'index de tuille 
unsigned int Tuile::acces() const
{
    return acc ;
}

// Si deux cases adjacentes sont séparées par un mur
bool Tuile::sepmur(Mur m) const
{ 
    for (unsigned i = 0 ; i< vecM.size() ; i++ )
    {
        if(vecM[i] == m)
        {
            return true ;
        }
    }
    return false ;
}

//fonction pour  si une case est accessible depuis les portes ou non
/*bool Tuile::accessible(Case c , UnionFind UF) const
{
  int index = c.index();
  return UF[acc] == UF[index];
}*/

// object ou sortie 
bool Tuile::site()
{
    if(typeSite == 1 || typeSite == 2)
    {
        return true ;
    }
    return false;
}



