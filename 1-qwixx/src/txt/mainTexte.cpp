#include "winTxt.h"
#include "txtJeu.h"


int main(){  
    txtJeu txt;
    srand(time(NULL));   
    txt.txtBoucle();   
    return 0;
}























/*
int main(int argc, char *argv[])
{
    //Vérification que tout fonctionne avec un "Hello world !"
    //std::cout<<"Hello world !";
    Fiche fiche;
    cout<<fiche.ligneBleue.decroissant<<endl; //Problème !!!

    fiche.ligneRouge.cocherCase(2);
    fiche.ligneRouge.cocherCase(4);

    fiche.ligneJaune.cocherCase(3);
    fiche.ligneJaune.cocherCase(6);
    fiche.ligneJaune.cocherCase(7);
    fiche.ligneJaune.cocherCase(10);
    fiche.ligneJaune.cocherCase(11);

    fiche.ligneVerte.cocherCase(4);
    fiche.ligneVerte.cocherCase(3);

    fiche.ligneBleue.cocherCase(7);
    
    termClear();	
	txtBoucleFiche(fiche);
    termClear();   
    

    return 0;
}
*/