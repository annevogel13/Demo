#include "case.hpp"

#include <cassert>
#include <stdexcept>
#include<iostream>

namespace MMaze {

Case::Case(unsigned int l, unsigned int c) {
  assert(l < 4 && c < 4) ;
  index_ = 4*l + c ;
}

//creation a partir de l'indice 
Case::Case()
{
  index_ = 24;
}


Case::Case(unsigned int index) : index_(index) 
{
  if(index >= 16)
  std::cout<<index<<std::endl;
  else
  {
    assert(index < 16) ;
  }
}

unsigned int Case::index() const {
  return index_ ;
}

bool Case::operator==(Case rhs) const {
  return index_ == rhs.index_ ;
}

Case Case::haut() const {
  if(index_ < 4) {
    throw std::domain_error("la case n'a pas de voisine haute") ;
  }
  return Case(index_ - 4);
}

Case Case::bas() const {
  if(index_ > 11) {
    throw std::domain_error("la case n'a pas de voisine basse") ;
  }
  return Case(index_ + 4) ;
}

Case Case::gauche() const {
  if(index_%4 == 0) {
    throw std::domain_error("la case n'a pas de voisine gauche") ;
  }
  return Case(index_ - 1) ;
}

Case Case::droite() const {
  if(index_%4 == 3) {
    throw std::domain_error("la case n'a pas de voisine droite") ;
  }
  return Case(index_ + 1) ;
}

//pour fais crees la case de voisine  
//creation a partir de l'ndice 
//bas Case 
Case Case::basCase() const
{
  if(index_ > 11) {
    //throw std::domain_error("la case n'a pas de voisine basse") ;
    Case C(0);
    C.index_ = 24 ;
    return C ;
  }
  return Case(index_ + 4) ;
}

//droite Case 
Case Case::droiteCase() const {
  if(index_%4 == 3) {
    //throw std::domain_error("la case n'a pas de voisine droite") ;
    Case C(0);
    C.index_ = 24 ;
    return C;
  }
  return Case(index_ + 1) ;
}

//haut Case 
Case Case::hautCase() const
{
  if(index_ < 4) {
    //throw std::domain_error("la case n'a pas de voisine haute") ;
    Case C(0);
    C.index_=24;
    return C;
  }
  return Case(index_ - 4);
}

//gauche Case 
Case Case::gaucheCase() const {
  if(index_%4 == 0) {
    //throw std::domain_error("la case n'a pas de voisine gauche") ;
    Case C(0);
    C.index_=24 ;
    return C;
  }
  return Case(index_ - 1) ;
}



Case Case::voisine(Direction d) const {
  switch(d) {
    case Direction::BAS : return bas() ;
    case Direction::DROITE : return droite() ;
    case Direction::HAUT : return haut() ;
    case Direction::GAUCHE : return gauche() ;
    default : assert(false) ;
  }
}

unsigned int Case::operator[](unsigned int i) const {
  assert(i < 2) ;
  if(i == 0) return index_ / 4 ;
  return index_ % 4 ;
}

unsigned int Case::ligne() const {
  return index_ / 4 ;
}

unsigned int Case::colonne() const {
  return index_ % 4 ;
}

Case Case::tourne(int rotation) const {
  unsigned int l = index_ / 4 ;
  unsigned int c = index_ % 4 ;
  if(rotation & 2) {
    l = 3 - l ;
  }
  if((rotation + 1) & 2) {
    c = 3 - c ;
  }
  if(rotation & 1) {
    return Case(4 * c + l) ;
  } else {
    return Case(4 * l + c) ;
  }
}

} //end of namespace MMaze
