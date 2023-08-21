#ifndef MMAZE_MELANGEUR_HPP
#define MMAZE_MELANGEUR_HPP

#include <vector>
#include <random>

namespace MMaze {

namespace MelangeurOptions {
  void imprevisible() ;
  void initialiser(std::size_t graine) ;
  extern std::default_random_engine semeur ;
}

template<typename T>
class Melangeur {

  public :

    Melangeur() {
      alea.seed(MelangeurOptions::semeur()) ;
    }

    template<typename ...Args> 
    void inserer(Args&& ...args) {
      //transfert au vector sous-jacent
      data.emplace_back(std::forward<Args>(args)...) ;
    }

    T retirer() {
      //piocher une position au hasard dans le tableau
      std::uniform_int_distribution<std::size_t> rand_index(0, data.size()-1) ;
      std::size_t pick = rand_index(alea) ;
      //recuperer l'element à cet endroit
      T t = std::move(data[pick]) ;
      //le remplacer par le dernier element
      data[pick] = std::move(data.back()) ;
      //retirer le dernier element
      data.pop_back() ;
      return t ;
    }

    void vider() {
      //transfert au vector sous-jacent
      data.clear() ;
    }

    std::size_t taille() {
      //transfert au vector sous-jacent
      return data.size() ;
    }

    //public pour se simplifier la vie
    std::vector<T> data ;
    std::default_random_engine alea ;
} ;

} //end of namespace MMaze

#endif
