#include "melangeur.hpp"

namespace MMaze {
  namespace MelangeurOptions {
    std::default_random_engine semeur ;

    void imprevisible() {
      std::random_device rd ;
      semeur.seed(rd()) ;
    }

    void initialiser(std::size_t graine) {
      semeur.seed(graine) ;
    }

  }
}
