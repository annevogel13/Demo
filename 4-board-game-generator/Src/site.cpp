#include "site.hpp"

namespace MMaze {

Site type_site(Site s) {
  //recuperation de la dizaine
  return (Site) (((int) s / 10) * 10) ;
}

Couleur couleur_site(Site s) {
  //recuperation de l'unite
  return (Couleur) ((int) s % 10) ;
}

Site colorer_site(Site s, Couleur c) {
  //decalage de la couleur
  return (Site) ((int) s + (int) c) ;
}

} //end of namespace MMaze
