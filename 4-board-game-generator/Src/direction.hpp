#ifndef MMAZE_DIRECTION_HPP
#define MMAZE_DIRECTION_HPP

namespace MMaze {

enum struct Direction {
  BAS,
  DROITE,
  HAUT,
  GAUCHE
} ;

extern const Direction directions[4] ;

Direction tourne(Direction d, int r) ;

Direction opposee(Direction d) ;

const char* nom(Direction d) ;

} //end of namespace MMaze

#endif
