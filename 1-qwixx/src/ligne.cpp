#include <iostream>
#include <cassert>
#include <math.h>

#include "ligne.h"

using namespace std;

Ligne::Ligne(bool inverse){

    for (int i = 0; i < 12; i++)
    {
        tabCase[i] = false; // false = non coche, true = coche
    }

    fermer = false;
    decroissant = inverse;
}

int Ligne::conversionCase(int numero) const{
    assert(numero >= 2);
    assert(numero <= 12);
    if (decroissant)
        return 12 - numero;
    else
        return numero - 2;
}

void Ligne::cocherCase(int numero){
    // tabCase va de 0 a 10 ou:
    // case 0 --> numero 2 ou 12
    // case 1 --> numero 3 ou 11
    // ....
    // case 10 --> numero 12 ou 2
    assert(verifierChoix(numero));

    int indice = conversionCase(numero);
    tabCase[indice] = true;
    if (indice == 10)
    {
        fermerLigne();
        tabCase[11] = true; //Case "cadenas"
    }
}

bool Ligne::verifierChoix(int numero) const{
    // True si choix correct, false sinon
    if (numero < 2 || numero > 12 || fermer)
        return false;

    int caseReel;
    caseReel = conversionCase(numero); //On récupère l'indice pour tabCase[]

    //Pour cocher la dernière case, il faut déjà en avoir 5 de cochées.
    if (caseReel == 10)
    {
        if (compterNbCase() > 4)
            return true;
        else
            return false;
    }
    else
    {
        for (int i = caseReel; i < 11; i++)
        {
            if (tabCase[i])
                return false; //Une case superieur ou egale est cochee, choix impossible
        }
        return true;
    }
}

int Ligne::compterNbCase() const{
    int somme = 0;
    for (int i = 0; i < 12; i++)
    {
        if (tabCase[i])
            somme++;
    }
    return somme;
}

void Ligne::fermerLigne(){
    fermer = true;
}

int Ligne::pointsSurLigne() const{
    int coche;
    int score = 0;

    coche = compterNbCase();
    score = 0.5 * (coche * coche + coche);
    return score;
}

void Ligne::afficherLigne() const{
    for (int j = 0; j < 11; j++)
    {
        cout << tabCase[j] << " ";
    }

    cout << endl;
}

int Ligne::calculerMeilleurCaseIA(int db1, int db2, int dC, int &dif) const{

    // verifier que les valeurs de des sont bonnes
    assert(db1 > 0);
    assert(db1 < 7);
    assert(db2 > 0);
    assert(db2 < 7);
    assert(dC > 0);
    assert(dC < 7);

    int pos1 = db1 + dC; // premiere case qu'on peut cocher
    assert(pos1 > 1);
    assert(pos1 < 13);

    int pos2 = db2 + dC; // deuxieme case qu'on peut cocher
    assert(pos2 > 1);
    assert(pos2 < 13);

    int derniereCaseCocher;
    derniereCaseCocher = -1; // pour indiquer si on est a la premiere tour

    for (int i = 0; i < 10; i++)
    {
        if (tabCase[i])
        {
            derniereCaseCocher = i;
        }
    }

    int nbReel = 0;
    int dif1, dif2;
    dif1 = dif2 = 100; // pour le declarer et initialiser avant le boucle commence

    if (decroissant)
    { // lignes decroissant

        if (derniereCaseCocher == -1)
        { // pour regler le premiere tour
            nbReel = 12;
        }
        else
            nbReel = 12 - derniereCaseCocher;

        assert(nbReel < 13);
        assert(nbReel > 1);

        // numero que on veut cocher est plus petit que le nbReel
        dif1 = nbReel - pos1;
        dif2 = nbReel - pos2;
    }
    else
    { // lignes croissantes

        if (derniereCaseCocher == -1)
        { // pour regler le premiere tour
            nbReel = 2;
        }
        else
            nbReel = derniereCaseCocher + 2;

        assert(nbReel < 13);
        assert(nbReel > 1);

        // numero que on veut cocher est plus grande que le nbReel
        dif1 = pos1 - nbReel;
        dif2 = pos2 - nbReel;
    }

    if ((dif1 < 0) && (dif2 < 0))
    {
        dif = 100; // pour etre sure que ce dif est jamais utilise
        return -1; // conflit avec les regles
    }
    else if (dif1 < 0)
    {
        dif = dif2;
        return pos2;
    }
    else if (dif2 < 0)
    {
        dif = dif1;
        return pos1;
    }

    // si les deux sont egaux
    if (dif1 == dif2)
    {
        dif = dif1;
        return pos1;
    }

    if (dif1 < dif2)
    {
        dif = dif1;
        return pos1;
    }
    else
        dif = dif2;
    return pos2;
}

void Ligne::testRegressionAI(){
    // test regression AI ligne
    cout << "Test regression de AI dans ligne" << endl;
    //Test pour les lignes croissants
    Ligne l1(false);

    // verifier que on peut cocher numero 2 (premiere case)
    int pos0, dif0;
    pos0 = l1.calculerMeilleurCaseIA(4, 1, 1, dif0);

    assert(pos0 == 2);
    assert(dif0 == 0);

    // verifier que on coche le bonne numero quand on prends en compte une case deja cochees
    l1.cocherCase(pos0);
    int pos1, dif1;
    pos1 = l1.calculerMeilleurCaseIA(2, 5, 3, dif1);

    assert(pos1 == 5);
    assert(dif1 == 3);
    l1.cocherCase(pos1);

    // verifier que le fonction retourne -1 (--> on veut faire une pass)
    int posX, difX;
    posX = l1.calculerMeilleurCaseIA(1, 1, 2, difX);

    assert(posX == -1);
    assert(difX == 100);

    //Test pour les lignes decroissant
    Ligne l2(true); // decroissant

    // verifier que on peut cocher numer 12 (premiere case)
    int dif2, pos2;
    pos2 = l2.calculerMeilleurCaseIA(5, 5, 6, dif2);

    assert(pos2 == 11);
    assert(dif2 == 1);

    // verifier que on coche le bonne numero quand on prends en compte une case deja cochees
    int pos3, dif3;
    pos3 = l2.calculerMeilleurCaseIA(2, 3, 6, dif3);
    assert(pos3 == 9);
    assert(dif3 == 3);
    l2.cocherCase(pos3);

    int pos4, dif4;
    pos4 = l2.calculerMeilleurCaseIA(4, 3, 2, dif4);
    assert(pos4 == 6);
    assert(dif4 == 3);
    l2.cocherCase(pos4);

    // verifier que le fonction retourne -1 (--> on veut faire une pass)
    int posY, difY;
    posY = l2.calculerMeilleurCaseIA(6, 5, 4, difY);

    assert(posY == -1);
    assert(difY == 100);
}

void Ligne::testRegression(){
    cout << "Test regression de Ligne.cpp" << endl;
    //1- Test du constructeur basique
    Ligne lg;
    assert(lg.decroissant == false);
    assert(fermer == false);
    for (int i = 0; i < 12; i++)
    {
        assert(!lg.tabCase[i]);
    }

    //2- Test du constructeur avec argument
    Ligne lg2(true);
    assert(lg2.decroissant == true);
    assert(fermer == false);
    for (int i = 0; i < 12; i++)
    {
        assert(!lg2.tabCase[i]);
    }

    //3- Conversion de case
    for (int i = 2; i <= 12; i++)
    {
        //Case 2 --> tab[0]
        //Case 3 --> tab[1]
        //...
        //Case 12 --> tab[10]
        assert(lg.conversionCase(i) == i - 2);

        //Case 2 --> tab[10]
        //Case 3 --> tab[9]
        //...
        //Case 12 --> tab[0]
        assert(lg2.conversionCase(i) == 12 - i);
    }

    //4- verifierChoix()
    assert(!lg.verifierChoix(1));   //False car <2
    assert(!lg2.verifierChoix(13)); //False car >12
    assert(!lg.verifierChoix(12));  //False car il faut 5 cases cochées.
    assert(!lg2.verifierChoix(2));  //False car il faut 5 cases cochées.

    assert(lg.verifierChoix(2));
    assert(lg2.verifierChoix(12));

    //Test général
    for (int i = 2; i <= 12; i++)
    {
        lg.cocherCase(i);
        lg2.cocherCase(14 - i);
    }
    for (int i = 0; i < 11; i++)
    {
        assert(lg.tabCase[i]);
        assert(lg2.tabCase[i]);
    }

    //Test précis
    Ligne lg3;
    Ligne lg4(true);

    lg3.cocherCase(2);
    assert(lg3.tabCase[0]);

    lg3.cocherCase(4);
    assert(lg3.tabCase[2]);

    lg4.cocherCase(12);
    assert(lg4.tabCase[0]);

    lg4.cocherCase(10);
    assert(lg4.tabCase[2]);

    //6- Combinaison verifier + cocher
    lg3.cocherCase(5);
    lg3.cocherCase(6);
    lg3.cocherCase(7);
    assert(!lg3.verifierChoix(3)); //False car case superieur cochée

    assert(lg3.verifierChoix(12)); //True car 5 cases déjà cochées
    assert(!lg3.fermer);           //False car case 12 non cochée
    lg3.cocherCase(12);
    assert(lg3.tabCase[10]);
    assert(lg3.fermer); //True car case 12 cochée

    //7- pointsSurLigne
    assert(lg3.pointsSurLigne() == 28); //6 cases cochées + cadenas = 28pts
    assert(lg4.pointsSurLigne() == 3);
}
