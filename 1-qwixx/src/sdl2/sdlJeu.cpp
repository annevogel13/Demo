#include <cassert>
#include <iostream>
#include "sdlJeu.h"
#include "image.h"

using namespace std;


sdlJeu::sdlJeu () : jeu() {
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if( !(IMG_Init(imgFlags) & imgFlags)) {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (TTF_Init() != 0) {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    

	
    // Creation de la fenetre
    window = SDL_CreateWindow("Projet AnLoVi : Qwixx", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 900, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl; 
        SDL_Quit(); 
        exit(1);
    }

    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);   

    

    // IMAGES
    fiche.loadFromFile("data/fiche.png",renderer);
    croix.loadFromFile("data/Croix.png",renderer);
    bande.loadFromFile("data/bande.jpg",renderer);
    fond.loadFromFile("data/fond.jpg",renderer);

    tabDeBlanc = new Image[6];
    tabDeRouge = new Image[6];
    tabDeJaune = new Image[6];
    tabDeVert = new Image[6];
    tabDeBleu = new Image[6];

    tabDeBlanc[0].loadFromFile("data/De1.png",renderer);
    tabDeBlanc[1].loadFromFile("data/De2.png",renderer);
    tabDeBlanc[2].loadFromFile("data/De3.png",renderer);
    tabDeBlanc[3].loadFromFile("data/De4.png",renderer);
    tabDeBlanc[4].loadFromFile("data/De5.png",renderer);
    tabDeBlanc[5].loadFromFile("data/De6.png",renderer);

    tabDeRouge[0].loadFromFile("data/DeRouge1.png",renderer);
    tabDeRouge[1].loadFromFile("data/DeRouge2.png",renderer);
    tabDeRouge[2].loadFromFile("data/DeRouge3.png",renderer);
    tabDeRouge[3].loadFromFile("data/DeRouge4.png",renderer);
    tabDeRouge[4].loadFromFile("data/DeRouge5.png",renderer);
    tabDeRouge[5].loadFromFile("data/DeRouge6.png",renderer);

    tabDeJaune[0].loadFromFile("data/DeJaune1.png",renderer);
    tabDeJaune[1].loadFromFile("data/DeJaune2.png",renderer);
    tabDeJaune[2].loadFromFile("data/DeJaune3.png",renderer);
    tabDeJaune[3].loadFromFile("data/DeJaune4.png",renderer);
    tabDeJaune[4].loadFromFile("data/DeJaune5.png",renderer);
    tabDeJaune[5].loadFromFile("data/DeJaune6.png",renderer);

    tabDeVert[0].loadFromFile("data/DeVert1.png",renderer);
    tabDeVert[1].loadFromFile("data/DeVert2.png",renderer);
    tabDeVert[2].loadFromFile("data/DeVert3.png",renderer);
    tabDeVert[3].loadFromFile("data/DeVert4.png",renderer);
    tabDeVert[4].loadFromFile("data/DeVert5.png",renderer);
    tabDeVert[5].loadFromFile("data/DeVert6.png",renderer);

    tabDeBleu[0].loadFromFile("data/DeBleu1.png",renderer);
    tabDeBleu[1].loadFromFile("data/DeBleu2.png",renderer);
    tabDeBleu[2].loadFromFile("data/DeBleu3.png",renderer);
    tabDeBleu[3].loadFromFile("data/DeBleu4.png",renderer);
    tabDeBleu[4].loadFromFile("data/DeBleu5.png",renderer);
    tabDeBleu[5].loadFromFile("data/DeBleu6.png",renderer);

    //Initialisation FONT 
    fontstandard = TTF_OpenFont("data/DejaVuSansCondensed.ttf",55);
    if (fontstandard == NULL)
        fontstandard = TTF_OpenFont("../data/DejaVuSansCondensed.ttf",50);
    if (fontstandard == NULL) {
            cout << "Failed to load DejaVuSansCondensed.ttf! SDL_TTF Error: " << TTF_GetError() << endl; 
            SDL_Quit(); 
            exit(1);
	}  
        
    fontPseudo = TTF_OpenFont("data/androgyne.ttf",55);
    if (fontPseudo == NULL)
        fontPseudo = TTF_OpenFont("../data/androgyne.ttf",50);
    if (fontPseudo == NULL) {
            cout << "Failed to load androgyne.ttf! SDL_TTF Error: " << TTF_GetError() << endl; 
            SDL_Quit(); 
            exit(1);
	}


    tabFontPseudo = new Image[4];
    tabFontPseudoRouge = new Image[4];
    tabFontNbJoueur = new Image[3];

    //Texte Titre
    couleurPolice = {31, 0, 166};
    TTF_SetFontStyle(fontstandard, TTF_STYLE_BOLD);
	titre_im.setSurface(TTF_RenderText_Solid(fontstandard,"Plateau de Jeu : Qwixx",couleurPolice));    
    titre_im.loadFromCurrentSurface(renderer);



    //Texte Deroulement
    couleurPolice = {0, 0, 0};
    
    deroulement.setSurface(TTF_RenderText_Solid(fontstandard,"Deroulement :",couleurPolice)); 
    deroulement.loadFromCurrentSurface(renderer);

    joueurActif.setSurface(TTF_RenderText_Solid(fontstandard,"Joueur Principal : ",couleurPolice)); 
    joueurActif.loadFromCurrentSurface(renderer);

    //Texte Choix du Joueur
    choixJoueur.setSurface(TTF_RenderText_Solid(fontstandard,"Avec combien de joueurs voulez-vous jouer ?",couleurPolice));
    choixJoueur.loadFromCurrentSurface(renderer);

    for(int i=0;i<3;i++){
        tabFontNbJoueur[i].setSurface(TTF_RenderText_Solid(fontstandard,
                                        to_string(i+2).c_str(),
                                        couleurPolice));
        tabFontNbJoueur[i].loadFromCurrentSurface(renderer);
    }

    //Texte boutin Fin
    txtbtnFin.setSurface(TTF_RenderText_Solid(fontstandard,"Fin",couleurPolice));
    txtbtnFin.loadFromCurrentSurface(renderer);

    //Texte Joueur en rouge
    couleurPolice = {150, 0, 0}; 
    string tmp = "Joueur ";  
    for(int i=0;i<4;i++){
        tabFontPseudoRouge[i].setSurface(TTF_RenderText_Solid(fontstandard,
                                    (tmp + to_string(i+1)).c_str(),
                                    couleurPolice));
        tabFontPseudoRouge[i].loadFromCurrentSurface(renderer);       	
    }

    //Classement
    classement.setSurface(TTF_RenderText_Solid(fontstandard,"Classement :",couleurPolice)); 
    classement.loadFromCurrentSurface(renderer);

    //Texte Joueur en marron
    couleurPolice = {166, 108, 0};  
    for(int i=0;i<4;i++){
        tabFontPseudo[i].setSurface(TTF_RenderText_Solid(fontstandard,
                                    (tmp + to_string(i+1)).c_str(),
                                    couleurPolice));
        tabFontPseudo[i].loadFromCurrentSurface(renderer);	        
    }

    //Texte Tour de jeu
    couleurTour = {222, 74, 0,255};
    tourBlanc.setSurface(TTF_RenderText_Solid(fontstandard,"- Somme des blancs",couleurTour)); 
    tourBlanc.loadFromCurrentSurface(renderer);

    couleurTour = {86, 86, 86,255};
    tourCouleur.setSurface(TTF_RenderText_Solid(fontstandard,"- Somme blanc + couleur",couleurTour)); 
    tourCouleur.loadFromCurrentSurface(renderer);

    //Texte des scores   
	police_score.setSurface(TTF_RenderText_Solid(fontstandard,"0",couleurPolice));
    police_score.loadFromCurrentSurface(renderer);

    //Initilaisation tableau position
    posBouton = new SDL_Rect[3];

    posBouton[0] = {150,300,150,60};
    posBouton[1] = {50,400,150,60};
    posBouton[2] = {250,400,150,60};

}

sdlJeu::~sdlJeu () {
    TTF_CloseFont(fontstandard);
    TTF_CloseFont(fontPseudo);    
    TTF_Quit();    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    delete [] tabDeBlanc;
    delete [] tabDeRouge;
    delete [] tabDeJaune;
    delete [] tabDeVert;
    delete [] tabDeBleu;
    delete [] tabFontPseudo;
    delete [] tabFontPseudoRouge;
    delete [] tabFontNbJoueur;
    delete [] posBouton;
}

bool sdlJeu::determineNbJoueur(int mouseX, int mouseY){
    bool retour = false;

    for(int i=0; i<3; i++){
        if(cliqueDansRect(mouseX,mouseY,posBouton[i])){
            jeu.setNbJoueurs(i+2);
            retour = true;
        }
    }

    return retour;   
}

void sdlJeu::changerCouleurTexteDeroulement(bool blanc){
    if(blanc){
        couleurTour = {222, 74, 0,255};
        tourBlanc.changerSurface(
        TTF_RenderText_Solid(
            fontstandard,
            "- Somme des blancs",
            couleurTour),
        renderer);

        couleurTour = {86, 86, 86,255};
        tourCouleur.changerSurface(
        TTF_RenderText_Solid(
            fontstandard,
            "- Somme blanc + couleur",
            couleurTour),
        renderer);
    }
    else{
        couleurTour = {86, 86, 86,255};
        tourBlanc.changerSurface(
        TTF_RenderText_Solid(
            fontstandard,
            "- Somme des blancs",
            couleurTour),
        renderer);

        couleurTour = {222, 74, 0,255};
        tourCouleur.changerSurface(
        TTF_RenderText_Solid(
            fontstandard,
            "- Somme blanc + couleur",
            couleurTour),
        renderer);
    }
}

bool sdlJeu::cliqueDansRect(int mouseX, int mouseY, int x, int y, int w, int h) const{
    return mouseX >= x && mouseX <= x+w && mouseY >= y && mouseY <= y+h;
}

bool sdlJeu::cliqueDansRect(int mouseX, int mouseY, const SDL_Rect &r) const{
    return mouseX >= r.x && mouseX <= r.x + r.w && mouseY >= r.y && mouseY <= r.y + r.h;
}

bool sdlJeu::trouverCase(int mouseX, int mouseY, const SDL_Rect &posFiche ,int numJoueur, bool blanc){
    //Dimension {200,500,500,350};
    bool reussi;

    //Si clique en dehors de la fiche, on retourne directement false
    if(!cliqueDansRect(mouseX,mouseY,posFiche.x,posFiche.y,posFiche.w,posFiche.h)) return false;
    
    //Calcul des positions en fonction de la fiche
    int case_w = float(posFiche.w)/18.51 + 0.5; //27
    int case_h = float(posFiche.h)/12 + 0.5;    //29

    int marge_x = posFiche.x+float(posFiche.w)/16.12 + 0.5; //31
    float decalage_x = float(posFiche.w)/14.8;   //34

    int marge_y = posFiche.y+float(posFiche.h)/20.59 + 0.5; //17
    float decalage_y = float(posFiche.h)/6.80;  //51

    //Grille de jeu
    for(int i=0;i<12;i++){
       //Test sur ligne rouge
       if(cliqueDansRect(mouseX,mouseY,marge_x + i*decalage_x,marge_y,case_w,case_h)){
           jeu.partieTour('r',i+2,jeu.ensembleFiches[numJoueur],reussi,blanc);
       }
       else if(cliqueDansRect(mouseX,mouseY,marge_x + i*decalage_x,marge_y+decalage_y,case_w,case_h)){
           jeu.partieTour('j',i+2,jeu.ensembleFiches[numJoueur],reussi,blanc);
       }
       else if(cliqueDansRect(mouseX,mouseY,marge_x + i*decalage_x,marge_y+2*decalage_y,case_w,case_h)){
           jeu.partieTour('v',12-i,jeu.ensembleFiches[numJoueur],reussi,blanc);
       }
       else if(cliqueDansRect(mouseX,mouseY,marge_x + i*decalage_x,marge_y+3*decalage_y,case_w,case_h)){
           jeu.partieTour('b',12-i,jeu.ensembleFiches[numJoueur],reussi,blanc);
       }

    } 
    return reussi;
}

void sdlJeu::sdlDes(int x,int y) const{

    tabDeBlanc[jeu.des.getBlanc1()-1].draw(renderer,x,y,90,90);
    tabDeBlanc[jeu.des.getBlanc2()-1].draw(renderer,x+120,y,90,90);

    tabDeRouge[jeu.des.getRouge()-1].draw(renderer,x+280,y,90,90);
    tabDeJaune[jeu.des.getJaune()-1].draw(renderer,x+400,y,90,90);
    tabDeVert[jeu.des.getVert()-1].draw(renderer,x+520,y,90,90);
    tabDeBleu[jeu.des.getBleu()-1].draw(renderer,x+640,y,90,90);

}


void sdlJeu::sdlScore(const SDL_Rect &pos, int numJoueur){
    //Toutes les rapports ont été déduits après un premier affichage
    //avec des valeurs fixes.
    //+0.5 pour arrondir au plus proche

    int decalage_x1 = float(pos.w)/2.16 + 0.5;
    int decalage_x2 = float(pos.w)/2.195 + 0.5;
    int decalage_y  = float(pos.h)/1.148 + 0.5;

    int score_x1 = float(pos.w)/27.0 + 0.5;
    int score_x2 = float(pos.w)/18.0 + 0.5;
    int score_y  = float(pos.h)/11.33 + 0.5;

    //On met à jour le score
    police_score.changerSurface(
        TTF_RenderText_Solid(fontPseudo,
        to_string(
            jeu.ensembleFiches[numJoueur].compterNbPointsTotal()).c_str(),
            couleurPolice
        ),
        renderer);
    if(jeu.ensembleFiches[numJoueur].compterNbPointsTotal()>0 && jeu.ensembleFiches[numJoueur].compterNbPointsTotal()<10)
        police_score.draw(renderer,pos.x+decalage_x1,pos.y+decalage_y,score_x1,score_y);
    else
        police_score.draw(renderer,pos.x+decalage_x2,pos.y+decalage_y,score_x2,score_y);

}




void sdlJeu::sdlCroix(const SDL_Rect &pos, int numJoueur){
    //Toutes les rapports ont été déduits après un premier affichage
    //avec des valeurs fixes.
    //+0.5 pour arrondir au plus proche
    int croix_x = float(pos.w)/18.51 + 0.5;
    int croix_y = float(pos.h)/12 + 0.5; 

    int marge_x = pos.x + float(pos.w)/16.12 + 0.5;
    float decalage_x = float(pos.w)/14.8;

    int marge_y = pos.y + float(pos.h)/20.59 + 0.5;
    float decalage_y = float(pos.h)/6.80;

    //Grille de jeu
    for(int i=0;i<12;i++){
        //Si la case est cochée, alors on affiche une croix
		if(jeu.ensembleFiches[numJoueur].ligneRouge.tabCase[i]){
			croix.draw(renderer,marge_x + i*decalage_x,marge_y,croix_x,croix_y);
		}

        if(jeu.ensembleFiches[numJoueur].ligneJaune.tabCase[i]){
			croix.draw(renderer,marge_x + i*decalage_x,marge_y + 1*decalage_y,croix_x,croix_y);
		}

        if(jeu.ensembleFiches[numJoueur].ligneVerte.tabCase[i]){
			croix.draw(renderer,marge_x + i*decalage_x,marge_y + 2*decalage_y,croix_x,croix_y);
		}

        if(jeu.ensembleFiches[numJoueur].ligneBleue.tabCase[i]){
			croix.draw(renderer,marge_x + i*decalage_x,marge_y + 3*decalage_y,croix_x,croix_y);
		}
    }


    //Prise en compte ligne fermé
    int centrer_y = pos.h/17;
    int ligne_w = 11*croix_x + 10*(decalage_x - croix_x);
    int ligne_h = croix_y - centrer_y;

    if(jeu.ensembleFiches[numJoueur].ligneRouge.fermer){
        bande.draw(renderer,marge_x, marge_y+centrer_y/2, ligne_w, ligne_h);
    }
    if(jeu.ensembleFiches[numJoueur].ligneJaune.fermer){
        bande.draw(renderer, marge_x, marge_y+decalage_y+centrer_y/2, ligne_w, ligne_h);
    }
    if(jeu.ensembleFiches[numJoueur].ligneVerte.fermer){
        bande.draw(renderer,marge_x, marge_y +2*decalage_y+centrer_y/2, ligne_w, ligne_h);
    }
    if(jeu.ensembleFiches[numJoueur].ligneBleue.fermer){
        bande.draw(renderer,marge_x, marge_y + 3*decalage_y+centrer_y/2, ligne_w, ligne_h);
    }



    //Coup manqué
    marge_x = pos.x + float(pos.w)/1.094 + 0.5;
    marge_y = pos.y + float(pos.h)/3.84 + 0.5;
    decalage_y = float(pos.h)/5.93;
    
    for(int i=0;i<jeu.ensembleFiches[numJoueur].coupsManques;i++){
        croix.draw(renderer,marge_x,marge_y + i*decalage_y,croix_x,croix_y);
    }
}

void sdlJeu::sdlFicheAutres(SDL_Rect &pos,int numPriveJoueur){
    int blocImage;
    int marge;
    int nbrPetiteFiche;
    int numJoueur;

    //Nombre de fiche à afficher
    nbrPetiteFiche = jeu.getNbJoueurs() - 1;

    //Taille du bloc pour 1 fiche
    blocImage = (900 - pos.x) / nbrPetiteFiche;

    //Calcul des marges pour 1 bloc, pos.w = largeur fiche
    marge = (blocImage-pos.w)/2;

    //Initialisation joueur à afficher
    numJoueur = (numPriveJoueur + 1) % jeu.getNbJoueurs(); 
   

    for(int i=0;i<nbrPetiteFiche;i++){
        //Calcul position x de la fiche (affichage de droite à gauche)
        pos.x = (nbrPetiteFiche-1-i)*blocImage+marge;

        //Si le joueur est celui "actif", on affiche le suivant
        if(numJoueur == numPriveJoueur){
            numJoueur = (numJoueur + 1) % jeu.getNbJoueurs();
        }

        //Affichage de la fiche + croix
        fiche.draw(renderer,pos.x,pos.y,pos.w,pos.h);
        sdlCroix(pos,numJoueur);

        //Affichage score
        sdlScore(pos,numJoueur);


        //+95 car milieu d'une fiche = 270/2 = 135.
        //Largeur moitie texte = 80/2 = 40
        //135-40 = 95
        tabFontPseudo[numJoueur].draw(renderer,pos.x + 95, pos.y+174,80,25);

        //On incrémente l'indice pour la joueur
        numJoueur = (numJoueur + 1) % jeu.getNbJoueurs();
    }   
}

void sdlJeu::sdlFicheActive(const SDL_Rect &posFiche, int numJoueur){

    //Affichage de la fiche
    fiche.draw(renderer,posFiche.x,posFiche.y,posFiche.w,posFiche.h);

    //Affichage des croix
    sdlCroix(posFiche,numJoueur);
    
    //Affichage des dés
    sdlDes(100,340);

    //Affichage score
    sdlScore(posFiche,numJoueur);

    //On affiche le pseudo du joueur
    tabFontPseudo[numJoueur].draw(renderer,400,860,100,30); 

}


void sdlJeu::sdlAff(const SDL_Rect &posFiche, const SDL_Rect &boutonFin, int numJoueur, int joueurPrincipal, bool blanc){

    SDL_Rect posPetiteFiche = {0,60,270,170};
    

    SDL_SetRenderDrawColor(renderer,200,200,200,255);
    SDL_RenderClear(renderer);

    //Affichage de la fiche    
    sdlFicheActive(posFiche,numJoueur);
    sdlFicheAutres(posPetiteFiche,numJoueur);

    //----------
    //Les textes
    //----------
    //Affichage du titre
    titre_im.draw(renderer,325,3,250,42);

    //Affichage tour de jeu
    deroulement.draw(renderer,10,630,155,30); 
    tourBlanc.draw(renderer,10,670,145,30);
    tourCouleur.draw(renderer,10,710,175,30);

    //Affichage Joueur Actif
    joueurActif.draw(renderer,10,520,170,30);
    tabFontPseudoRouge[joueurPrincipal].draw(renderer,10,560,90,27); 

    //Bouton Fin de partie
    SDL_SetRenderDrawColor(renderer, 50, 209, 40, 255);
    SDL_RenderFillRect(renderer,&boutonFin);

    txtbtnFin.draw(renderer,795,840,50,30);

}

void sdlJeu::sdlAffFin(){
    SDL_SetRenderDrawColor(renderer,200,200,200,255);
    SDL_RenderClear(renderer);

    //Affichage image de fond
    fond.draw(renderer,0,0,900,900);    

    //Affichage Classement
    classement.draw(renderer,50,170,160,40);
    for(int i=0;i<jeu.getNbJoueurs();i++){
        tabFontPseudo[i].draw(renderer,50,230 + 80*i,180,40);
        tabFontPseudoRouge[i].draw(renderer,240,230 + 80*i,110,40);
    }

}

void sdlJeu::majPseudoFinJoueur(string tabResultat[4], int tabScore[4]){   

    //On récupère le classement de la partie
    jeu.resultatpartie(tabResultat,tabScore);

    //On met à jour le texte pour l'affichage
    for(int i=0;i<jeu.getNbJoueurs();i++){
        couleurPolice = {166, 108, 0};  
        tabFontPseudo[i].changerSurface(TTF_RenderText_Solid(fontstandard,
            (to_string(i+1)+ ") " + tabResultat[i] + "  -->").c_str(),
            couleurPolice),
            renderer);
        
        couleurPolice = {150, 0, 0}; 
        tabFontPseudoRouge[i].changerSurface(TTF_RenderText_Solid(fontstandard,
            (to_string(tabScore[i]) + " points").c_str(),
            couleurPolice),
            renderer);
    }
}

void sdlJeu::sdlAffDebut(){
    SDL_SetRenderDrawColor(renderer,200,200,200,255);
    SDL_RenderClear(renderer);

    //Affichage image de fond
    fond.draw(renderer,0,0,900,900);    

    //Affichage des boutons
    SDL_SetRenderDrawColor(renderer, 240, 204, 35, 255);
    SDL_RenderFillRect(renderer,&posBouton[0]);

    SDL_SetRenderDrawColor(renderer, 50, 209, 40, 255);
    SDL_RenderFillRect(renderer,&posBouton[1]);

    SDL_SetRenderDrawColor(renderer, 47, 88, 197, 255);
    SDL_RenderFillRect(renderer,&posBouton[2]);

    //Affichage Texte    
    choixJoueur.draw(renderer,30,250,400,30);
    tabFontNbJoueur[0].draw(renderer,215,315,20,30);
    tabFontNbJoueur[1].draw(renderer,115,415,20,30);
    tabFontNbJoueur[2].draw(renderer,315,415,20,30);
}

void sdlJeu::initPartie(){    
    jeu.des.lanceLesDes();
    for(int i=0;i<jeu.getNbJoueurs();i++){
        jeu.ensembleFiches[i].setPseudo("Joueur " + to_string(i+1));
    }
}

void sdlJeu::sdlBoucle () {
    //Variable servant au SDL2
    SDL_Event events;
    SDL_Rect posFiche = {200,500,500,350};  
    SDL_Rect boutonFin = {770,830,100,50};  
	bool quit = false;
    

    //Variable servant à gérer les tours de jeu
    bool retour;
    bool blanc = true;
    int numJoueur = 0;
    int joueurPrincipal = 0;
    int manque = 0;
    //etat = 0 --> Debut du jeu
    //etat = 1 --> Tour de jeu
    //etat = 2 --> Fin de jeu
    int etat = 0;

    //Tableau pour le classement de fin
    string tabResultat[4];
	int tabScore[4];

	// tant que ce n'est pas la fin ...
	while (!quit) {   
        retour = false;               
		while (SDL_PollEvent(&events)) {
			if (events.type == SDL_QUIT) quit = true;           // Si l'utilisateur a clique sur la croix de fermeture
            else if(events.type == SDL_MOUSEBUTTONDOWN && etat !=2){        //Si un bouton de la souris est pressé
                if(events.button.button == SDL_BUTTON_LEFT && etat == 0){ // etat = 0 --> Choix des joueurs
                    if(determineNbJoueur(events.motion.x,events.motion.y)){
                        etat++;
                        initPartie();
                    }                        
                }
                else if(events.button.button == SDL_BUTTON_LEFT && etat == 1){ //etat = 1 --> Tour de jeu
                    if(cliqueDansRect(events.motion.x,events.motion.y,boutonFin)){
                        majPseudoFinJoueur(tabResultat,tabScore);
                        etat = 2;
                    }
                    else
                        retour = trouverCase(events.motion.x,events.motion.y,posFiche,numJoueur,blanc);

                }
                else if(events.button.button == SDL_BUTTON_RIGHT && etat == 1){    //Clique droit pour passer son tour     
                    if(numJoueur == joueurPrincipal){
                        manque++;
                        if(manque == 2){
                            jeu.ensembleFiches[joueurPrincipal].coupsManques++;
                        }
                    }
                    retour = true;
                }
            }
		}  

        //On regarde si jeu terminé
        if(etat < 2 && jeu.finPartie(joueurPrincipal)){
            majPseudoFinJoueur(tabResultat,tabScore);
            etat = 2;
        }  
        
		// on affiche le jeu sur le buffer caché en fonction de l'etat
        if(etat == 0){
            sdlAffDebut();
        }else if(etat == 1){
		    sdlAff(posFiche,boutonFin,numJoueur,joueurPrincipal,blanc);
        }else{
            sdlAffFin();
        }      

		// on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(renderer);
        

        //GESTION DU JEU EN CAS DE CASE COCHEE ou TOUR PASSE
        if(retour && etat < 2){
            numJoueur = (numJoueur + 1) % jeu.getNbJoueurs();
            SDL_Delay(400); //Delay pour voir la coche à l'écran            

            //Si on revient au joueur principal, il faut cocher les couleurs
            if(numJoueur==joueurPrincipal){
                blanc = !blanc;
                changerCouleurTexteDeroulement(blanc);
            } 
            else if(!blanc){ //Si on vient de cocher une couleur, 
                blanc = !blanc;
                changerCouleurTexteDeroulement(blanc);  

                joueurPrincipal = (joueurPrincipal + 1) % jeu.getNbJoueurs();
                jeu.des.lanceLesDes();
                manque = 0;
                
            }
        } 
	}
}
