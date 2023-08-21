#ifndef MMAZE_SITE_HPP
#define MMAZE_SITE_HPP

#include "case.hpp"
#include "couleurs.hpp"

namespace MMaze {

enum struct Site {
  AUCUN = 0,

  BOUTIQUE = 10,

  DEPART = 20,
  DEPART_JAUNE = 21,
  DEPART_VERTE = 22,
  DEPART_ORANGE = 23,
  DEPART_VIOLETTE = 24,

  PORTE = 30,
  PORTE_JAUNE = 31,
  PORTE_VERTE = 32,
  PORTE_ORANGE = 33,
  PORTE_VIOLETTE = 34,

  OBJECTIF = 40,
  OBJECTIF_JAUNE = 41,
  OBJECTIF_VERT = 42,
  OBJECTIF_ORANGE = 43,
  OBJECTIF_VIOLET = 44,

  SORTIE = 50,
  SORTIE_JAUNE = 51,
  SORTIE_VERTE = 52,
  SORTIE_ORANGE = 53,
  SORTIE_VIOLETTE = 54,

  VORTEX = 60,
  VORTEX_JAUNE = 61,
  VORTEX_VERT = 62,
  VORTEX_ORANGE = 63,
  VORTEX_VIOLET = 64
} ;

Site type_site(Site s) ;
Couleur couleur_site(Site s) ;
Site colorer_site(Site s, Couleur c) ;

} //end of namespace MMaze

#endif
