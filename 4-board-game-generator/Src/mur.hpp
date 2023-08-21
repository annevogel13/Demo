#ifndef MMAZE_MUR_HPP
#define MMAZE_MUR_HPP

#include "case.hpp"

namespace MMaze {

/* +---+---+---+---+
 * |   12  16  20  |
 * + 0 + 1 + 2 + 3 +
 * |   13  17  21  |
 * + 4 + 5 + 6 + 7 +
 * |   14  18  22  |
 * + 8 + 9 + 10+ 11+
 * |   15  19  23  |
 * +---+---+---+---+
 */

class Mur {

  public :

    //construction a partir des deux cases adjacentes
    Mur(Case c0, Case c1) ;

    //construction implicite a partir d'un entier dans [0,23], voir ci-dessus
    explicit Mur(unsigned int index) ;

    //conversion implicite vers un entier dans [0,23], voir ci-dessus
    unsigned int index() const ;

    //comparaison de murs
    bool operator==(Mur rhs) const ;

    //cases adjacentes
    //  * 0 : gauche ou haut
    //  * 1 : droite ou bas
    Case operator[](unsigned int i) const ;

    //rotation
    Mur tourne(int rotation) const ;

  private :

    //stockage sous forme d'un entier, voir ci-dessus
    unsigned int index_ ;
} ;

} //end of namespace MMaze

#endif
