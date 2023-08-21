#ifndef MMAZE_PAD_HPP
#define MMAZE_PAD_HPP

#include <sstream>
#include <vector>
#include <map>

namespace MMaze {

/* utilitaire pour gérer un bloc de lignes et écrire dedans via les outils de
 * flux standard de la librairie standard
 */

class ConsolePad: public std::ostream {
  public :

    /* height est le nombre de lignes du pad */
    ConsolePad(int height) ;

    /* récupération du contenu du pad sous forme d'une chaine */
    std::string lines() ;

    /* déplacement du curseur du pad */
    void moveto(unsigned int line, unsigned int column) ;

  private :
  
    /* buffer spécifique pour gérer les retours à la ligne */
    class Padbuf : public std::stringbuf {

      public :

        /* height est le nombre de lignes gérées */
        Padbuf(int height) ;

        /* déplacement du curseur */
        void moveto(unsigned int l, unsigned int c) ;

        /* récupération de toutes les lignes en une seule */
        std::string lines() ;

      protected :

        /* surcharge pour la gestion de la fin de ligne */
        int sync() ;

        /* surcharges pour la gestion des carractères */
        int overflow(char c = EOF) ;
        std::streamsize xsputn(const char* s, std::streamsize n) ;

      private :

        void tabulate() ;

        /* lignes stockées */
        std::vector<std::stringstream> lines_ ;
        std::map<std::pair<unsigned int, unsigned int>, std::string> escapes_ ;
        /* curseur */
        unsigned int line_ ;
        unsigned int column_ ;
    } ;

    Padbuf buf_ ;
} ;

} //end of namespace MMaze

#endif
