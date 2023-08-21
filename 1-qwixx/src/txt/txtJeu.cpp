#include <iostream>
#include <cassert>
#include <unistd.h>
#include "txtJeu.h"


txtJeu::txtJeu() : jeu(), win(100,18){};

void txtJeu::affLigne(int x, int y, const Ligne & lg){
	string str; //Chaine à afficher
	string c; //Separateur entre les nombres
	if(lg.fermer) {
		c = "-";
		win.printString(x + 33,y,"Ferme");
	}
	else c = " ";

	//Affichage des cases de 2 à 11 (ou 12 à 3)
	for(int i=0;i<10;i++){
		if(lg.tabCase[i]){ //Si la case est cochée
			str = "X" + c + c; //"X--"		
		}
		else{
			if(lg.decroissant){ //Si ligne décroissante
				str = to_string(12-i);
				if(i<3) str += c; //2 chiffres +  1 separateur
				else str = str + c + c ; //1 chiffre +  2 separateurs

			}
			else{ //Même principe que ci-dessus
				str = to_string(i+2);
				if(i>7) str += c;
				else str = str + c + c ;
			}
		}
		//On affiche la case à l'écran
		//i*3 car chaque case est represente sur 3 caractères.
		win.printString(x+i*3,y,str);
	}

	//Gestion de la dernière case
	if(lg.tabCase[10]){ //Si la case est cochée
		str = "X" + c; //"X-"		
	}
	else{
		if(lg.decroissant){ //Si ligne décroissante
			str = "2" + c;

		}
		else{ //Même principe que ci-dessus
			str = "12";
		}
	}
	win.printString(x+30,y,str);
}

void txtJeu::affFiche(int x, int y,const Fiche & fiche){//Mettre un const une fois fiche.cpp modifié	
	//Dimension de la fiche
	int dimx = 43;
	int dimy = 10;
	assert(x+dimx<=win.getlargeur());
	assert(y+dimy<=win.gethauteur());

	//Traçage des contours
	for(int i=x; i<dimx+x;i++){
		win.print(i,y,'-');
		win.print(i,dimy + y - 1,'-');
	}
	for(int j=y;j<dimy + y;j++){
		win.print(x,j,'|');
		win.print(dimx + x - 1,j,'|');
	}

	//Nom joueur
	//pos qui centre au milieu de la fiche : largeur/2 - longueurpseudo/2
	int pos = x + dimx/2 - fiche.getPseudo().length()/2;
	win.printString(pos,y+1,fiche.getPseudo());

	//Affichage des lignes
	win.printString(x+1,y+2,"R:");
	affLigne(x+4,y+2,fiche.ligneRouge);

	win.printString(x+1,y+3,"J:");
	affLigne(x+4,y+3,fiche.ligneJaune);

	win.printString(x+1,y+4,"V:");
	affLigne(x+4,y+4,fiche.ligneVerte);

	win.printString(x+1,y+5,"B:");
	affLigne(x+4,y+5,fiche.ligneBleue);


	//Affichage coup manqué
	win.printString(x+1,y+7,"Coups manques :");
	win.printString(x+17,y+7, to_string(fiche.coupsManques) + "/4");

	//affichage score
	win.printString(x+1,y+8,"Score actuel  :");
	win.printString(x+17,y+8,to_string(fiche.compterNbPointsTotal()));

}

void txtJeu::affPlateau(int x, int y){
	//Largeur Plateau = 43 ou 86 selon nombre de joueur
	//Hauteur Plateau = 10 ou 21 selon nombre de joueur
	for(int i=0;i<jeu.getNbJoueurs();i++){
		if(i<2)
			affFiche(x + 43*(i%2),y,jeu.ensembleFiches[i]);
		else
			affFiche(x + 43*(i%2),y + 11,jeu.ensembleFiches[i]);
	}
}

void txtJeu::affDe(int x, int y){
	//Dimension en largeur --> 58
	string tirage = "Tirage --> ";
	tirage += "DB1 : " + to_string(jeu.des.getBlanc1()) +
			" DB2 : " + to_string(jeu.des.getBlanc2()) +
			"  --  DR : " + to_string(jeu.des.getRouge()) +
			" DJ : " + to_string(jeu.des.getJaune()) +
			" DV : " + to_string(jeu.des.getVert()) +
			" DB : " + to_string(jeu.des.getBleu());

	win.printString(x,y,tirage); 
}

bool txtJeu::verifInitiale(char &c) const{
	if(c >= 'A' && c <= 'Z')
        c += 32;
	return (c != 'r' && c != 'j' && c != 'v' && c != 'b' && c != 'p');
}

void txtJeu::tourDeJeu(int numJoueur, bool &fin){
    int sommeBlanc; 
	bool reussiBlanc,tmp; 
	char charCouleur1; 	

	//Affichage du lancée de dés sur la ligne 3
	//Boucle permettant de simuler un tirage au sort visuel.
	for(int i=0;i<20;i++){
		usleep(20000);
		sommeBlanc = jeu.initTour(); 
		affDe(2,3);
		win.draw();
	}

	//Partie 1 d'un tour : cocher la valeur en combinant les 2 blancs
	//TOUS les joueurs jouent
    for(int i=0; i<jeu.getNbJoueurs() ; i++){		
		win.clearLigne(4);
		win.printString(2,4,jeu.ensembleFiches[i].getPseudo() + 
							" --> Des blancs : Sur quelle ligne souhaitez-vous cocher le " 
							+ to_string(sommeBlanc) + " ? [r,j,v,b,p]");
		win.draw();

		//Evenement clavier : choix de ligne
		do{
			charCouleur1 = win.getCh(); 
			if(charCouleur1 == '\r'){
				fin = true; //Touche "entree" pour finir le jeu
				return;
			} 
		}while(verifInitiale(charCouleur1));

		jeu.partieTour(charCouleur1, sommeBlanc, jeu.ensembleFiches[i] ,tmp, true);
		//On enregistre le booleen du joueur en cours
		if(i == numJoueur) reussiBlanc = tmp; 
		affPlateau(2,6);
		win.draw();  //pour toute les joueurs sauf joueur 1         
    }

	//Partie 2 d'un tour : cocher la valeur en combinant blanc + couleur
	//Uniquement le joueur en cours joue
	bool reussicouleur; 
	int numeroCalculer; 
	char charCouleur2,charCase;
	string choix;	
	
	win.clearLigne(4);
	win.printString(2,4,jeu.ensembleFiches[numJoueur].getPseudo() +
						" --> Des couleurs : Sur quelle ligne souhaitez-vous cocher une case ? [r,j,v,b,p]");
	win.draw();

	//Evenement clavier : choix de ligne
	do{
		charCouleur2 = win.getCh(); 
		if(charCouleur2 == '\r'){ 
			fin = true; //Touche "entree" pour finir le jeu
			return;
		} 
	}while(verifInitiale(charCouleur2));

	//Si le joueur a choisi une case
	if(charCouleur2 != 'p'){

		win.clearLigne(4);
		switch (charCouleur2){ //Permet d'afficher le bon texte
		case 'r':
			choix = "rouge";
			break;
		case 'j':
			choix = "jaune";
			break;
		case 'v':
			choix = "verte";
			break;
		case 'b':
			choix = "bleue";
			break;				
		default:  
			choix = "???";
		}
		win.printString(2,4,jeu.ensembleFiches[numJoueur].getPseudo()
						+ " --> Des couleurs : Quelle case souhaitez-vous"
						+ " cocher sur la ligne " 
						+ choix + " ?");
		win.draw();

		//Evenement clavier : choix de la case
		do{
			charCase = win.getCh(); 
			if(charCase == '\r'){
				fin = true; //Touche "entree" pour finir le jeu
				return;
			} 
		}while(charCase<'1' || charCase > '9'); //On continue tant que le numéro est invalide

		//Pour saisir 10,11,12, il faut 2 chiffres, donc on continue la saisie.
		if(charCase == '1'){
			charCase = ' ';
			do{
				charCase = win.getCh(); 
				if(charCase == '\r'){
				fin = true; //Touche "entree" pour finir le jeu
				return;
				} 
			}while(charCase<'0' || charCase > '2');
			numeroCalculer = 10 + (charCase - '0');
		}
		else numeroCalculer = charCase - '0';

		//On affiche le plateau de jeu (=fiches)
		jeu.partieTour(charCouleur2, numeroCalculer, jeu.ensembleFiches[numJoueur], reussicouleur,false); 
		affPlateau(2,6);
		win.draw();
	}
	else reussicouleur = false;			
	
	// Si le joueur passe/echoue à ses 2 coups, il fait un coup manqué  
	if(!reussiBlanc && !reussicouleur) {
		jeu.ensembleFiches[numJoueur].coupsManques++;
		affPlateau(2,6);
		win.draw();
	}

    fin = jeu.finPartie(numJoueur);
   
}

void txtJeu::finDePartie(){
	string tabResultat[4];
	int tabScore[4];
	char c;

	win.clear();
	jeu.resultatpartie(tabResultat,tabScore);
	win.printString(2,1,"Resultats de la partie : ");
	for(int i=0;i<jeu.getNbJoueurs();i++){
		win.printString(2,i+2,to_string(i+1)+") " + tabResultat[i] + " "
							+ to_string(tabScore[i]) + " points");
	}
	win.printString(2,7,"Appuyer sur Entree pour quitter");
	win.draw();
	do{
		c = win.getCh();
	}while(c != '\r');
}

void txtJeu::initPseudo(){
	char c;
	int curseur;
	string nom;
	for(int i=0;i<jeu.getNbJoueurs();i++){
		//Initialisation 
		nom = "";
		c = ' ';
		win.clearLigne(4);
		win.clearLigne(5);
		curseur = 7;

		//Le code
		win.printString(2,4,"Entrer le pseudo du joueur " + to_string(i+1)
							+ ". (Entree pour valider)");
		win.printString(2,5,"--> ");
		win.draw();	
		do{
			c = win.getCh();
			//On limite le pseudo à 15 caractère (c-a-d curseur < 22)
			if((('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z')) && curseur < 22 ){
				nom.push_back(c);
				win.print(curseur++,5,c);
				win.draw();
			}
			//Touche supprimer (code ASCII 127) pour effacer un caractère
			if(c == 127 && nom!=""){
				nom.erase(nom.size() - 1);
				win.print(curseur-1,5,' ');
				curseur--;
				win.draw();	
			} 
		}while(c != '\r' || nom=="");
		jeu.ensembleFiches[i].setPseudo(nom);	
			
	}
}

void txtJeu::initPartietxt(){
	bool ok = true;
	char c;
	win.printString(win.getlargeur()/2 - 16,2,"Bonjour et bienvenue dans le jeu Qwixx");
	win.printString(2,4,"Avec combien de joueur souhaitez-vous jouer ? (Entrer 1,2,3 ou 4)");
	win.draw();
	
	do {		
		c = win.getCh();
		switch (c) {
			case '1':
				jeu.setNbJoueurs(c - '0'); //c-'0' pour convertir en int
				initPseudo();
				ok=false;
				break;
			case '2':
				jeu.setNbJoueurs(c - '0');	
				initPseudo();		
				ok=false;
				break;
			case '3':
				jeu.setNbJoueurs(c - '0');
				initPseudo();
				ok=false;
				break;
			case '4':
				jeu.setNbJoueurs(c - '0');	
				initPseudo();
				ok=false;	
				break;
		}
	}while(ok);	

	win.clear();
	win.printString(2,1,"Conseil pour jouer :");
	win.printString(2,3,"Pour choisir une ligne, saisissez uniquement l'initiale de la couleur [r,j,v,b]");
	win.printString(2,5,"Pour passer une action, saisissez la lettre : p");
	win.printString(2,7,"Pour quitter le jeu durant la partie, appuyer sur : Entree");
	win.printString(2,11,"Appuyer sur Entrée pour débuter le jeu...");
	win.draw();
	do{
		c = win.getCh();
	}while(c != '\r');
}

void txtJeu::txtBoucle(){
	bool fin = false;
	int indice = 0 ; 
	int numTour = 1;
	char c;

	//On efface le terminal
	win.termClear();

	//On déclare une fenêtre dans le terminale
	win.clear();		

	//On initialise la partie
	initPartietxt();

	//On agrandit la fenêtre si nbjoueur > 2
	if(jeu.getNbJoueurs()>2) win.sethauteur(28);
	win.clear();	

	//Boucle de jeu	
	do{
		usleep(100000);

		//Pseudo du joueur en cours
		win.printString(2,1,"Tour " + to_string(numTour));
		win.printString(10,1," : " + jeu.ensembleFiches[indice].getPseudo()
							+ " lance les des...");

		//Affichage du plateau de jeu (=fiches)
		affPlateau(2,6);	
		win.draw();

		//Action du joueur
		tourDeJeu(indice, fin); 
		indice = (indice + 1) % jeu.getNbJoueurs();
		numTour++;

	}while(!fin); // tant que fin est false le boucle va tourner ; 
	
	//Gestion de la FIN	
	win.clearLigne(0);
	win.clearLigne(1);
	win.clearLigne(2);
	win.clearLigne(3);
	win.clearLigne(4);
	win.clearLigne(5);
	win.printString(2,1,"FIN de la partie...");
	win.printString(2,3,"Appuyer sur 's' pour afficher les scores");
	win.printString(2,4,"Appuyer sur Entree pour quitter la partie");
	win.draw();
	do{
		c = win.getCh();
	}while(c != '\r' && c!='S' && c!='s');

	if(c =='s' || c=='S'){
		finDePartie();
	}
	
	//On efface le terminal
	win.termClear();
}