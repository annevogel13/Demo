#ifndef MMAZE_DRAW_HPP
#define MMAZE_DRAW_HPP

#include "case.hpp"
#include "mur.hpp"
#include "site.hpp"
#include "couleurs.hpp"

#include <string>
#include <vector>
#include <array>
#include <utility>

namespace MMaze {

class PadPlateau {
  public :

    //initialisation
    PadPlateau() ;

    //ajout d'elements du plateau. Non reversible
    void ajouter_tuile(int ligne, int colonne) ;

    void ajouter_mur(int ligne, int colonne, Mur m) ;

    void ajouter_site(int ligne, int colonne, Case c, Site s) ;
    void ajouter_boutique(int ligne, int colonne, Case c) ;
    void ajouter_porte(int ligne, int colonne, Case c, Couleur couleur) ;
    void ajouter_objectif(int ligne, int colonne, Case c, Couleur couleur) ;
    void ajouter_sortie(int ligne, int colonne, Case c, Couleur couleur) ;
    void ajouter_vortex(int ligne, int colonne, Case c, Couleur couleur) ;

    //placement des joueurs, modifiable par la suite
    void placer_joueur(int ligne, int colonne, Case c, Couleur couleur) ;

    //export graphique
    
#ifndef NO_CAIRO
    //png ou svg
    //attention, il semble qu'il y ait parfois des bugs dans l'export svg
    void dessiner(const std::string& fichier, int unit = 64, float margin = 0.25) ;
#ifndef NO_IMAGICK
    std::string base64_png(int unit = 64, float margin = 0.25) ;
#endif
#endif

    //export console

    friend std::ostream& operator<<(std::ostream& out, const PadPlateau& plateau) ;

    //import / export json
    
    void save(const std::string& fichier) ;
    void load(const std::string& fichier) ;

  private :

    //tuiles actives
    std::vector<int> m_tuiles ;

    //murs sur les tuiles, 24 booleens par tuile
    std::vector<bool> m_murs ;

    //sites a ajouter sur les tuiles, 16 sites par tuile
    std::vector<Site> m_sites ;

    //joueurs
    //0 -> jaune
    //1 -> vert
    //2 -> orange
    //3 -> violet
    std::array<int, 8> m_tuiles_joueurs ;
    std::array<Case, 4> m_positions_joueurs ;
    std::array<bool, 4> m_presences_joueurs ;
} ;

std::ostream& operator<<(std::ostream& out, const PadPlateau& plateau) ;

} //end of namespace MMaze

#endif
