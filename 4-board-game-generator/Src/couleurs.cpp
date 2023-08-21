#include "couleurs.hpp"

namespace MMaze {

  const Couleur couleurs[4] = {Couleur::JAUNE, Couleur::VERT, Couleur::ORANGE, Couleur::VIOLET} ;

  const char* TXT_CLEAR = "\x1B[0m" ;
  const char* TXT_BOLD = "\x1B[1m" ;
  const char* TXT_DEFAULT = "\x1B[39m" ;
  const char* TXT_VIOLET = "\x1B[38;5;135m" ;
  const char* TXT_ORANGE = "\x1B[38;5;208m" ;
  const char* TXT_JAUNE = "\x1B[38;5;11m" ;
  const char* TXT_VERT = "\x1B[38;5;10m" ;
  const char* BG_DEFAULT = "\x1B[49m" ;
  //const char* BG_BOUTIQUE = BG_DEFAULT ;//"\x1B[100m" ;
  const char* BG_VIOLET = "\x1B[48;5;135m" ;
  const char* BG_ORANGE = "\x1B[48;5;208m" ;
  const char* BG_JAUNE = "\x1B[48;5;11m" ;
  const char* BG_VERT = "\x1B[48;5;10m" ;

  const char* txt_colors[5] = {TXT_DEFAULT, TXT_JAUNE, TXT_VERT, TXT_ORANGE, TXT_VIOLET} ;
  const char* bg_colors[5] = {BG_DEFAULT, BG_JAUNE, BG_VERT, BG_ORANGE, BG_VIOLET} ;

} //end of namespace MMaze

