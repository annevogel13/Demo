#include "console_pad.hpp"

#include <iostream>

namespace MMaze {

/* height est le nombre de lignes du pad */
ConsolePad::ConsolePad(int height) : std::ostream(&buf_), buf_(height) {}

/* récupération du contenu du pad sous forme d'une chaine */
std::string ConsolePad::lines() {
  return buf_.lines() ;
}

/* déplacement du curseur du pad */
void ConsolePad::moveto(unsigned int line, unsigned int column) {
  buf_.moveto(line, column) ;
}

/* height est le nombre de lignes gérées */
ConsolePad::Padbuf::Padbuf(int height) : lines_(height), line_(0), column_(0) {}

/* déplacement du curseur */
void ConsolePad::Padbuf::moveto(unsigned int l, unsigned int c) {
  sync() ;
  line_ = l ;
  column_ = c ;
  tabulate() ;
}

void ConsolePad::Padbuf::tabulate() {
  lines_[line_].seekp(0, std::ios_base::end) ;
  //ajout d'espaces si la ligne est trop courte pour ce curseur
  for(unsigned int i = lines_[line_].tellp(); i < column_; ++i) {
    lines_[line_] << " " ;
  }
  //placement du curseur sur le flux
  lines_[line_].seekp(column_) ;
}

/* récupération de toutes les lignes en une seule */
std::string ConsolePad::Padbuf::lines() {
  sync() ;
  std::stringstream ss ;
  unsigned int line = 0 ;
  unsigned int column = 0 ;
  for(auto& escape : escapes_) {
    //position de l'échappement
    unsigned int el = escape.first.first ;
    unsigned int ec = escape.first.second ;
    //envoi de tout le texte avant l'échappement
    while( line < el) {
      ss.write(lines_[line].str().c_str() + column, lines_[line].str().size() - column) ;
      ss << std::endl ;
      ++line ;
      column = 0 ;
    }
    ss.write(lines_[line].str().c_str() + column, ec - column) ;
    //envoi de l'échappement
    ss << escape.second ;
    column = ec ;
  }
  //envoi de tout le texte après le dernier échappement
  ss.write(lines_[line].str().c_str() + column, lines_[line].str().size() - column) ;
  ++line ;
  while(line < lines_.size()) {
    ss << std::endl ;
    ss << lines_[line].str() ;
    ++line ;
  }
  return ss.str() ;
}

/* surcharge pour la gestion de la fin de ligne */
int ConsolePad::Padbuf::sync() {
  if(str().size() > 0 && str().back() == '\n') {
    //la synchro a bien été appelée suite à une fin de ligne
    //transfert du flux vers sa ligne, en omettant le retour à la ligne
    lines_[line_].write(str().c_str(), str().size() - 1) ;
    lines_[line_].flush() ;
    //déplacement du curseur à la ligne suivant
    ++line_ ;
    tabulate() ;
  } else {
    //la synchro ne correspond pas à une fin de ligne
    //transfert du flux vers sa ligne
    lines_[line_] << str() ;
    lines_[line_].flush() ;
  }
  //remise à zéro du buffer
  str("") ;
  return 0 ;
}

int ConsolePad::Padbuf::overflow(char c) {
  std::cout << "overflow " << c << std::endl ;
  return std::stringbuf::overflow(c) ;
}

std::streamsize ConsolePad::Padbuf::xsputn(const char* s, std::streamsize n) {
  if(s[0] == '\x1b') {
    //séquence d'échappement
    //attention les séquences ne peuvent plus jamais être retirées
    //position de la séquence
    unsigned int c = (unsigned int) lines_[line_].tellp() + str().size() ;
    auto pos = std::make_pair(line_, c) ;
    //stockage de la séquence dans une structure annexe
    auto it = escapes_.find(pos) ;
    if(it == escapes_.end()) {
      //aucune séquence déjà à cet endroit
      escapes_[pos] = std::string(s, n) ;
    } else {
      //concaténation à une séquence existante
      escapes_[pos].append(s, n) ;
    }
    return n ;
  }
  return std::stringbuf::xsputn(s, n) ;
}

} //end of namespace MMaze
