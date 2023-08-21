#include <iostream>
#include <cassert>

#include "des.h"

using namespace std;

Des::Des() : DeRouge(0), DeJaune(0), DeVert(0), DeBleu(0),  DeBlanc1(0), DeBlanc2(0){
}

int Des::getRouge() const{
    return DeRouge;
}

int Des::getJaune() const{
    return DeJaune;
}

int Des::getVert() const{
    return DeVert;
}

int Des::getBleu() const{
    return DeBleu;
}

int Des::getBlanc1() const{
    return DeBlanc1;
}

int Des::getBlanc2() const{
    return DeBlanc2;
}

void Des::getBlanc(int &de1, int &de2) const{
    de1 = DeBlanc1;
    de2 = DeBlanc2;
}

int Des::sommeBlancs() const{
    return DeBlanc1 + DeBlanc2;
}

void Des::setBlancs(int d1, int d2){
    DeBlanc1 = d1;
    DeBlanc2 = d2;
}

void Des::setDes(int d1, int d2, int dr, int dj, int dv, int db){
    DeRouge = dr;
    DeJaune = dj;
    DeVert = dv;
    DeBleu = db;
    DeBlanc1 = d1;
    DeBlanc2 = d2;
}

void Des::lanceLesDes(){
    
    DeRouge = rand()%6 + 1;
    DeJaune = rand()%6 + 1;
    DeVert = rand()%6 + 1;
    DeBleu = rand()%6 + 1;
    DeBlanc1 = rand()%6 + 1;
    DeBlanc2 = rand()%6 + 1;

}


bool Des::possibilites(int nb, char charDeCouleur, bool blanc) const{ 
     
    // je récupère les valeurs des des blanc 
    // apres je calcule les valeurs possibles pour le rouge, jaune, vert, bleu 
    // je verifie directement si c'est possible d'avoir nb comme resultat pour une couleur 

    int b1,b2; 
    getBlanc(b1, b2); 

    switch(charDeCouleur){
        case 'r':
            return (!blanc && (getRouge()+b1==nb || getRouge()+b2==nb)) ||
                    (blanc && b1+b2==nb);
            break;
        case 'j':
            return (!blanc && (getJaune()+b1==nb || getJaune()+b2==nb)) ||
                    (blanc && b1+b2==nb);
            break;
        case 'v':
            return (!blanc && (getVert()+b1==nb || getVert()+b2==nb)) ||
                    (blanc && b1+b2==nb);
            break;
        case 'b':
            return (!blanc && (getBleu()+b1==nb || getBleu()+b2==nb)) ||
                    (blanc && b1+b2==nb);
            break;
    }

    return false;
}

// fonction ecrit pour afficher dans le console les des (c'est pour debugger)
void Des::afficherDes() const{
    cout<<"Le resultat des des :"<<endl;
    cout<<"rouge : "<<DeRouge<<" , jaune : "<<DeJaune<<" , vert : "<<DeVert<<" , bleu : "<<DeBleu<<endl;
    cout<<" des blanc : "<<DeBlanc1<<" "<<DeBlanc2<<endl; 
}


void Des::testRegression(){
    cout<< "Test regression de Des.cpp" << endl;
    //1- Constructeur
    Des D1;
    assert(D1.DeRouge == 0);
    assert(D1.DeJaune == 0);
    assert(D1.DeVert == 0);
    assert(D1.DeBleu == 0);
    assert(D1.DeBlanc1 == 0);
    assert(D1.DeBlanc2 == 0);

    //2- Le lancé de dés
    //On effectue le test plusieurs fois
    int db1,db2;
    for(int i=0; i<4;i++){
        D1.lanceLesDes();        
        assert(D1.DeRouge>0 && D1.DeRouge<=6);
        assert(D1.DeJaune>0 && D1.DeJaune<=6);
        assert(D1.DeVert>0 && D1.DeVert<=6);
        assert(D1.DeBleu>0 && D1.DeBleu<=6);
        assert(D1.DeBlanc1>0 && D1.DeBlanc1<=6);
        assert(D1.DeBlanc2>0 && D1.DeBlanc2<=6);
        cout<<"DR : "<<D1.getRouge()<<" ";
        cout<<"DJ : "<<D1.getJaune()<<" ";
        cout<<"DV : "<<D1.getVert()<<" ";
        cout<<"DB : "<<D1.getBleu()<<" ";
        D1.getBlanc(db1,db2);
        assert(db1==D1.getBlanc1());
        assert(db2==D1.getBlanc2());
        
        cout<<endl;
    }

    //3- On teste la possibilite    
    for(int i=0; i<5;i++){ //Boucle pour tester plusieurs fois (le lancé étant aléatoire)
        D1.lanceLesDes();
        D1.setBlancs(4,2);
        //True car le nombre en paramètre est égal à la somme des dés blancs
        assert(D1.possibilites(6,'r',true));
        assert(D1.possibilites(6,'j',true));
        assert(D1.possibilites(6,'v',true));
        assert(D1.possibilites(6,'b',true));

        //False car le nombre en paramètre n'est pas égal à la somme des dés blancs
        assert(!D1.possibilites(2,'r',true));
        assert(!D1.possibilites(5 + 4,'j',true));
        assert(!D1.possibilites(7,'v',true));
        assert(!D1.possibilites(8,'b',true));

        //True car le nombre en paramètre est égal à la somme d'un dé blanc + un dé couleur
        assert(D1.possibilites(D1.getBlanc1()+D1.getRouge(),'r',false));
        assert(D1.possibilites(D1.getJaune()+D1.getBlanc2(),'j',false));
        assert(D1.possibilites(D1.getVert()+D1.getBlanc2(),'v',false));
        assert(D1.possibilites(D1.getBlanc1()+D1.getBleu(),'b',false));

        //False car le nombre en paramètre n'est pas égal à la somme d'un dé blanc + un dé couleur
        assert(!D1.possibilites(D1.getBlanc1()-1+D1.getRouge(),'r',false));
        assert(!D1.possibilites(D1.getJaune()+D1.getBlanc2() + 4,'j',false));
        assert(!D1.possibilites(D1.getVert() - 4+D1.getBlanc2(),'v',false));
        assert(!D1.possibilites(D1.getBlanc1() + 3+D1.getBleu(),'b',false));
    }

};
