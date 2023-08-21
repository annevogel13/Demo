#include "draw.hpp"
#include "console_pad.hpp"
#include "json.hpp"

#include <vector>
#include <exception>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>

#define _USE_MATH_DEFINES
#include <cmath>

#ifndef NO_GRAPHICS
  #include <librsvg-2.0/librsvg/rsvg.h>
  #include <cairo/cairo.h>
  #include <cairo/cairo-svg.h>
  #include <Magick++.h>
#endif

namespace MMaze {

enum struct SiteAddition {
  JOUEUR = 100,
  JOUEUR_JAUNE = 101,
  JOUEUR_VERT = 102,
  JOUEUR_ORANGE = 103,
  JOUEUR_VIOLET = 104,

  MUR = 110
} ;

union drawable {
  drawable(Site s_in) : s(s_in) {}
  drawable(SiteAddition add_in) : add(add_in) {}

  Site s ;
  SiteAddition add ;
} ;

//traduction des sites en id dans le svg de style
static constexpr const char* site_names[] = {
  "background", "shop", "start", "door", "objective", "exit", "vortex", "", "", "", "player", "wall"
} ;

static constexpr const char* color_names[] = {
  "yellow", "green", "orange", "purple"
} ;

//traduction des sites en texte pour l'affichage console
static constexpr const char* site_symbols[] = {
  " ", "#", "", "" , "{$}", "[->", "(@)", "", "", "", "\\o/", ""
} ;

static std::size_t index_tuile(const std::vector<int>& t, int ligne, int colonne) {
  //on commence par la fin
  //ajouter des murs et des sites sur la derniere tuile ajoutee est efficace
  //la condition d'arret ci-dessous fonctionne car size_t est non signe
  for(std::size_t i = t.size() - 2; i < t.size(); i -= 2) {
    if(t[i] == ligne && t[i+1] == colonne) {
      return i/2 ;
    }
  }
  throw std::invalid_argument("aucune tuile a cette position") ;
}

void PadPlateau::ajouter_site(
    int ligne, int colonne, Case c, 
    Site site
    ) {
  //index de la tuile dans le tableau
  std::size_t index = index_tuile(m_tuiles, ligne, colonne) ;
  //placement du site
  m_sites[16 * index + c.index()] = site ;
}

PadPlateau::PadPlateau() : 
  m_positions_joueurs{Case(0), Case(0), Case(0), Case(0)}, m_presences_joueurs{false, false, false, false}
{}

void PadPlateau::ajouter_tuile(int ligne, int colonne) {
  //enregistrement de la position
  m_tuiles.push_back(ligne) ;
  m_tuiles.push_back(colonne) ;

  //allocation des murs et des sites, aucun mur et aucun site
  m_murs.resize(m_murs.size() + 24, false) ;
  m_sites.resize(m_sites.size() + 16, (Site) Site::AUCUN) ;
}

void PadPlateau::ajouter_mur(int ligne, int colonne, Mur m) {
  //index de la tuile dans le tableau
  std::size_t index = index_tuile(m_tuiles, ligne, colonne) ;
  //activation du mur
  m_murs[24 * index + m.index()] = true ;
}

void PadPlateau::ajouter_boutique(int ligne, int colonne, Case c) {
  ajouter_site(ligne, colonne, c, Site::BOUTIQUE) ;
}

void PadPlateau::ajouter_porte(int ligne, int colonne, Case c, Couleur couleur) {
  //site colore a inserer
  Site site = colorer_site(Site::PORTE, couleur) ;
  //insertion
  ajouter_site(ligne, colonne, c, site) ;
}

void PadPlateau::ajouter_objectif(int ligne, int colonne, Case c, Couleur couleur) {
  //site colore a inserer
  Site site = colorer_site(Site::OBJECTIF, couleur) ;
  //insertion
  ajouter_site(ligne, colonne, c, site) ;
}

void PadPlateau::ajouter_sortie(int ligne, int colonne, Case c, Couleur couleur) {
  //site colore a inserer
  Site site = colorer_site(Site::SORTIE, couleur) ;
  //insertion
  ajouter_site(ligne, colonne, c, site) ;
}

void PadPlateau::ajouter_vortex(int ligne, int colonne, Case c, Couleur couleur) {
  //site colore a inserer
  Site site = colorer_site(Site::VORTEX, couleur) ;
  //insertion
  ajouter_site(ligne, colonne, c, site) ;
}

void PadPlateau::placer_joueur(int ligne, int colonne, Case c, Couleur couleur) {
  //index du joueur dans les tableaux
  int index_joueur = (int) couleur - 1 ;
  //activation du joueur si necessaire
  m_presences_joueurs[index_joueur] = true ;
  //tuile du joueur
  m_tuiles_joueurs[2*index_joueur] = ligne ;
  m_tuiles_joueurs[2*index_joueur + 1] = colonne ;
  //position dans la tuile
  m_positions_joueurs[index_joueur] = c ;
}

template<typename DessineElt>
static void dessiner_generique(
    const std::vector<int>& tuiles,
    const std::vector<bool>& murs,
    const std::vector<Site>& sites,
    const std::array<int, 8>& tuiles_joueurs,
    const std::array<Case, 4>& positions_joueurs,
    const std::array<bool, 4>& presences_joueurs,
    DessineElt& dessine_elt
    ) {
  //fond des tuiles
  for(unsigned int i = 0; i < tuiles.size(); i+= 2) {
    //parcours des 16 cases
    for(unsigned int ci = 0; ci < 16; ++ci) {
      //position pour dessiner
      Case c(ci) ;
      //fond ou boutique
      Site site = sites[8*i + ci] ;
      if(site == Site::BOUTIQUE) {
        //boutique
        dessine_elt(site, tuiles[i], tuiles[i+1], c, 0) ;
      } else {
        //fond
        dessine_elt(Site::AUCUN, tuiles[i], tuiles[i+1], c, 0) ;
      }
    }
  }
  //decor sur les tuiles
  for(unsigned int i = 0; i < tuiles.size(); i+= 2) {
    //parcours des 16 cases
    for(unsigned int ci = 0; ci < 16; ++ci) {
      //position pour dessiner
      Case c(ci) ;
      //site de la tuile
      Site site = sites[8*i + ci] ;
      //carracteristiques du site
      Site type = type_site(site) ;
      if(site != Site::AUCUN && site != Site::BOUTIQUE && type != Site::DEPART) {
        if(type == Site::PORTE) {
          try {
            //recherche d'une tuile voisine
            switch(ci) {
              case 2 :
                index_tuile(tuiles, tuiles[i]-1, tuiles[i+1]) ;
                break ;
              case 4 :
                index_tuile(tuiles, tuiles[i], tuiles[i+1]-1) ;
                break ;
              case 11 :
                index_tuile(tuiles, tuiles[i], tuiles[i+1]+1) ;
                break ;
              case 13 :
                index_tuile(tuiles, tuiles[i]+1, tuiles[i+1]) ;
                break ;
            }
            //si pas d'exception ici, pas de porte a afficher
          } catch(std::exception& a) {
            //une porte requiert une rotation selon sa case
            int rotation = 0 ;
            switch(ci) {
              case 2 :
                rotation = 1 ;
                break ;
              case 4 :
                rotation = 2 ;
                break ;
              case 13 :
                rotation = 3 ;
                break ;
            }
            dessine_elt(site, tuiles[i], tuiles[i+1], c, rotation) ;
          }
        } else {
          //site ne necessitant pas de rotation
          dessine_elt(site, tuiles[i], tuiles[i+1], c, 0) ;
        }
      }
      //bords
      if(type != Site::PORTE) {
        if(c.ligne() == 0) {
          dessine_elt(SiteAddition::MUR, tuiles[i], tuiles[i+1], c, 1) ;
        }
        if(c.ligne() == 3) {
          dessine_elt(SiteAddition::MUR, tuiles[i], tuiles[i+1], c, 3) ;
        }
        if(c.colonne() == 0) {
          dessine_elt(SiteAddition::MUR, tuiles[i], tuiles[i+1], c, 2) ;
        }
        if(c.colonne() == 3) {
          dessine_elt(SiteAddition::MUR, tuiles[i], tuiles[i+1], c, 0) ;
        }
      }
    }

    //murs
    for(unsigned int mi = 0; mi < 24; ++mi) {
      if(murs[12*i + mi]) {
        //un mur est pesent, position pour dessiner
        Mur m(mi) ;
        Case c = m[0] ;
        if(mi < 12) {
          //mur horizontal, rotation necessaire
          dessine_elt(SiteAddition::MUR, tuiles[i], tuiles[i+1], c, 3) ;
        } else {
          //mur vertical sans rotation
          dessine_elt(SiteAddition::MUR, tuiles[i], tuiles[i+1], c, 0) ;
        }
      }
    }
  }

  //dessin des joueurs
  
  for(unsigned int j = 0; j < 4; ++j) {
    if(presences_joueurs[j]) {
      dessine_elt(
          (SiteAddition) (((int) SiteAddition::JOUEUR) + j + 1), 
          tuiles_joueurs[2*j], 
          tuiles_joueurs[2*j+1], 
          positions_joueurs[j], 
          0
          ) ;
    }
  }
}

#ifndef NO_CAIRO

static double img_x(int ligne, int colonne, Case c) {
  return 4*colonne - ligne + (int) c.colonne() ;
}

static double img_y(int ligne, int colonne, Case c) {
  return 4*ligne + colonne + (int) c.ligne() ;
}

static void rotate(cairo_t* cr, double cx, double cy, int rotation) {
  cairo_translate(cr, cx + 0.5, cy + 0.5) ;
  cairo_rotate(cr, - rotation * M_PI/2) ;
  cairo_translate(cr, -cx - 0.5, -cy - 0.5) ;
}

static cairo_surface_t* dessiner_cairo(
    const std::string& style_file,
    const std::vector<int>& tuiles,
    const std::vector<bool>& murs,
    const std::vector<Site>& sites,
    const std::array<int, 8>& tuiles_joueurs,
    const std::array<Case, 4>& positions_joueurs,
    const std::array<bool, 4>& presences_joueurs
    ) {

  //chargement du fichier de style svg
  GError* svg_error = nullptr ;
  RsvgHandle* style = rsvg_handle_new_from_file(style_file.c_str(), &svg_error) ;
  if(svg_error) {
    throw std::invalid_argument("fichier de style introuvable") ;
  }

  //creation d'une surface cairo pour enregistrer le dessin
  cairo_surface_t* surface = cairo_recording_surface_create(CAIRO_CONTENT_COLOR_ALPHA, nullptr) ;

  //contexte de dessin
  cairo_t* cr = cairo_create(surface) ;

  //dessin d'site
  auto dessiner_site = [cr, style] (drawable elt, int tl, int tc, Case c, int rot) {
    //fenetre a dessiner
    double x = img_x(tl, tc, c) ;
    double y = img_y(tl, tc, c) ;
    RsvgRectangle rect({x, y, 1, 1}) ;

    //sauvegarde de la transformation initiale
    cairo_save(cr) ;

    //application de la rotation
    rotate(cr, x, y, rot) ;

    //id dans le fichier de style svg
    int site_index = (int) elt.s / 10 ;
    std::stringstream svg_id ;
    svg_id << "#" << site_names[site_index] ;
    if((int) elt.s % 10) {
      //le site a une couleur
      int site_color = (((int) elt.s % 10) - 1) % 4 ;
      svg_id << "_" << color_names[site_color] ;
    }

    //dessin
    //GError* error = nullptr ;
    rsvg_handle_render_layer(style, cr, svg_id.str().c_str(), &rect, /*&error*/ nullptr) ;
    //if(error) {
    //  std::cout << "got an error : " << svg_id.str() << " " << x << " " << y << " " << rot << std::endl ;
    //}

    //restauration de la transformation initiale
    cairo_restore(cr) ;
  } ;

  //dessin generique
  dessiner_generique(
        tuiles,
        murs,
        sites,
        tuiles_joueurs,
        positions_joueurs,
        presences_joueurs,
        dessiner_site
      ) ;

  cairo_surface_flush(surface) ;


  //finalisation
  cairo_destroy(cr) ;
  g_object_unref(style) ;

  return surface ;
}

void PadPlateau::dessiner(const std::string& fichier, int unit, float margin) {
  //dessin generique
  cairo_surface_t* record = dessiner_cairo(
      "mmaze.svg",
      m_tuiles,
      m_murs,
      m_sites,
      m_tuiles_joueurs,
      m_positions_joueurs,
      m_presences_joueurs
      ) ;

  double x0, y0, largeur, hauteur ;
  cairo_recording_surface_ink_extents(record, &x0, &y0, &largeur, &hauteur) ;

  //il semble qu'il y ait un bug dans le calcul des largeur, hauteur, et origine
  largeur -= 2 ;
  hauteur -= 2 ;
  x0 += 1 ;
  y0 += 1 ;

  //ouvrir une surface pour l'export
  int umargin = margin * unit ;
  cairo_surface_t* img ;
  const std::string& extension = fichier.substr(fichier.find_last_of(".") + 1) ;
  if(extension == "svg") {
     img = cairo_svg_surface_create(
         fichier.c_str(), unit*largeur + 2*umargin, unit*hauteur + 2*umargin
         ) ;
  } else if(extension == "png") {
    img = cairo_image_surface_create(
        CAIRO_FORMAT_ARGB32, unit*largeur + 2*umargin, unit*hauteur + 2*umargin
        ) ;
  } else {
    throw std::invalid_argument("seul l'export svg ou png est possible") ;
  }

  //creer un contexte pour l'export
  cairo_t* cr = cairo_create(img) ;
  cairo_translate(cr, umargin, umargin) ;
  cairo_scale(cr, unit, unit) ;

  //rejouer l'enregistrement
  cairo_set_source_surface(cr, record, -x0, -y0) ;
  cairo_paint(cr) ;
  cairo_show_page(cr) ;

  //finalisation de l'image
  cairo_surface_flush(img) ;

  //ecriture du png si besoin
  if(extension == "png") {
    cairo_surface_write_to_png(img, fichier.c_str()) ;
  }

  //destruction du contexte
  cairo_destroy(cr) ;

  //destruction de la surface d'export
  cairo_surface_finish(img) ;
  cairo_surface_destroy(img) ;
  cairo_surface_finish(record) ;
  cairo_surface_destroy(record) ;
}

#ifndef NO_IMAGICK

//encodage base 64 avec ImageMagick
static std::string base64_encode(const unsigned char* buf, unsigned int size) {
  Magick::Blob b(buf, size) ;
  return b.base64() ;
}

//recuperation des octets d'un png cairo dans un vector
static cairo_status_t render_base64(
    void* target, 
    const unsigned char* data,
    unsigned int length
    ) {
  std::vector<unsigned char>* output = (std::vector<unsigned char>*) target ;
  output->insert(output->end(), data, data + length) ;
  return CAIRO_STATUS_SUCCESS ;
}

std::string PadPlateau::base64_png(int unit, float margin) {
  //dessin generique
  cairo_surface_t* record = dessiner_cairo(
      "mmaze.svg",
      m_tuiles,
      m_murs,
      m_sites,
      m_tuiles_joueurs,
      m_positions_joueurs,
      m_presences_joueurs
      ) ;

  double x0, y0, largeur, hauteur ;
  cairo_recording_surface_ink_extents(record, &x0, &y0, &largeur, &hauteur) ;

  //il semble qu'il y ait un bug dans le calcul des largeur, hauteur, et origine
  largeur -= 2 ;
  hauteur -= 2 ;
  x0 += 1 ;
  y0 += 1 ;

  //ouvrir une surface pour l'export
  int umargin = margin * unit ;
  cairo_surface_t* img = cairo_image_surface_create(
      CAIRO_FORMAT_ARGB32, unit*largeur + 2*umargin, unit*hauteur + 2*umargin
      ) ;

  //creer un contexte pour l'export
  cairo_t* cr = cairo_create(img) ;
  cairo_translate(cr, umargin, umargin) ;
  cairo_scale(cr, unit, unit) ;

  //rejouer l'enregistrement
  cairo_set_source_surface(cr, record, -x0, -y0) ;
  cairo_paint(cr) ;

  //destruction du contexte
  cairo_destroy(cr) ;

  //finalisation de l'image
  cairo_surface_flush(img) ;

  //export des octets du png
  std::vector<unsigned char> octets ;
  cairo_surface_write_to_png_stream(
      img,
      render_base64,
      &octets
      ) ;

  //destruction de la surface d'export
  cairo_surface_finish(img) ;
  cairo_surface_destroy(img) ;
  cairo_surface_destroy(record) ;

  //encodage base 64
  return base64_encode(octets.data(), octets.size()) ;
}

#endif //NO_IMAGICK
#endif //NO_CAIRO

std::ostream& operator<<(std::ostream& out, const PadPlateau& plateau) {
  //pas de tuile pas de chocolat
  if(plateau.m_tuiles.size() == 0) return out ;

  //dimensions du plateau
  int lmin, lmax, cmin, cmax ;
  lmin = lmax = plateau.m_tuiles[0] ;
  cmin = cmax = plateau.m_tuiles[1] ;
  for(unsigned int i = 2; i < plateau.m_tuiles.size(); i+=2) {
    lmin = plateau.m_tuiles[i] < lmin ? plateau.m_tuiles[i] : lmin ;
    lmax = plateau.m_tuiles[i] > lmax ? plateau.m_tuiles[i] : lmax ;
    cmin = plateau.m_tuiles[i+1] < cmin ? plateau.m_tuiles[i+1] : cmin ;
    cmax = plateau.m_tuiles[i+1] > cmax ? plateau.m_tuiles[i+1] : cmax ;
  }

  //creation d'un buffer de suffisamment de lignes
  ConsolePad pad((lmax - lmin + 1) * 8 + 1 + 2 * (cmax - cmin)) ;

  //dessin d'site
  auto dessiner_site = [lmin, lmax, cmin, cmax, &pad] (drawable elt, int tl, int tc, Case ca, int rot) {
    //coordonnees tuile -> ligne et colonne dans le pad
    unsigned int labs = tl - lmin ;
    unsigned int cabs = tc - cmin ;

    //position de base de la case
    unsigned int l = 2 * ( 4 * labs + cabs + ca.ligne()) ;
    unsigned int c = 4 * ( 4 * cabs + (lmax - labs - lmin) + ca.colonne()) ;

    if((int) elt.s <= (int) Site::BOUTIQUE) {
      //dessin du fond
      const char* e = site_symbols[(int) elt.s / 10] ;
      pad.moveto(l, c) ;
      pad 
        << "+" << e << e << e << "+" << std::endl
        << e << e << e << e << e << std::endl
        << "+" << e << e << e << "+" ;
      return ;
    }

    if(elt.add == SiteAddition::MUR) {
      //dessin d'un mur
      switch(rot) {
        case 0:
          pad.moveto(l+1, c+4) ;
          pad << "|" ;
          break ;
        case 1:
          pad.moveto(l, c+1) ;
          pad << "---" ;
          break ;
        case 2:
          pad.moveto(l+1, c) ;
          pad << "|" ;
          break ;
        case 3:
          pad.moveto(l+2, c+1) ;
          pad << "---" ;
          break ;
      }
      return ;
    }

    //couleur du site s'il y en a une
    unsigned int site_color = (int) elt.s % 10 ;

    if((int) elt.s / 10 == (int) Site::PORTE / 10) {
      //dessin d'une porte
      switch(rot) {
        case 0:
          pad.moveto(l+1, c+4) ;
          pad << txt_colors[site_color] << ">" << TXT_CLEAR ;
          break ;
        case 1:
          pad.moveto(l, c+1) ;
          pad << txt_colors[site_color] << " ^ " << TXT_CLEAR ;
          break ;
        case 2:
          pad.moveto(l+1, c) ;
          pad << txt_colors[site_color] << "<" << TXT_CLEAR ;
          break ;
        case 3:
          pad.moveto(l+2, c+1) ;
          pad << txt_colors[site_color] << " v " << TXT_CLEAR ;
          break ;
      }
      return ;
    }

    //dessin du contenu d'une case
    pad.moveto(l+1, c+1) ;
    pad << txt_colors[site_color] << site_symbols[(int) elt.s / 10] << TXT_CLEAR ;
    
  } ;

  //dessin generique
  dessiner_generique(
        plateau.m_tuiles,
        plateau.m_murs,
        plateau.m_sites,
        plateau.m_tuiles_joueurs,
        plateau.m_positions_joueurs,
        plateau.m_presences_joueurs,
        dessiner_site
      ) ;

  out << pad.lines() ;
  return out ;
}

//export json

void PadPlateau::save(const std::string& fichier) {
  using json = nlohmann::json ;

  json bkp ;

  //tableau des tuiles
  bkp["tuiles"] = json::array() ;
  for(unsigned int i = 0; i < m_tuiles.size(); i+=2) {
    json tuile ;
    //tableau de deux entiers pour la position
    tuile["position"] = {m_tuiles[i], m_tuiles[i+1]} ;
    tuile["murs"] = json::array() ;
    //tableau de booleens pour les murs
    for(int m = 0; m < 24; ++m) {
      tuile["murs"].push_back((bool) m_murs[12*i + m]) ;
    }
    //tableau d'entiers pour les sites
    tuile["sites"] = json::array() ;
    for(int c = 0; c < 16; ++c) {
      tuile["sites"].push_back((int) m_sites[8*i + c]) ;
    }
    bkp["tuiles"].push_back(tuile) ;
  }

  //tableau des joueurs
  bkp["joueurs"] = json::array() ;
  for(unsigned int i = 0; i < 4; ++i) {
    if(m_presences_joueurs[i]) {
      json joueur ;
      //tableau de deux entiers pour la tuile du joueur
      joueur["tuile"] = {m_tuiles_joueurs[2*i], m_tuiles_joueurs[2*i+1]} ;
      //entier pour la case du joueur dans la tuile
      joueur["position"] = m_positions_joueurs[i].index() ;
      //couleur du joueur
      joueur["couleur"] = couleurs[i] ;
      bkp["joueurs"].push_back(joueur) ;
    }
  }

  std::ofstream f(fichier) ;
  f << std::setw(4) << bkp << std::endl ;
}

//import json

void PadPlateau::load(const std::string& fichier) {
  using json = nlohmann::json ;

  //reinitialisation
  m_tuiles.clear() ;
  m_murs.clear() ;
  m_sites.clear() ;
  m_presences_joueurs.fill(false) ;

  //chargement du json
  json input ;
  std::ifstream f(fichier) ;
  f >> input ;

  //recuperation des tuiles
  for(unsigned int i = 0; i < input["tuiles"].size(); ++i) {
    const json& tuile = input["tuiles"][i] ;
    //position de la tuile
    ajouter_tuile(tuile["position"][0], tuile["position"][1]) ;
    //murs
    for(int m = 0; m < 24; ++m) {
      m_murs[24*i + m] = tuile["murs"][m] ;
    }
    //sites
    for(int s = 0; s < 16; ++s) {
      m_sites[16*i + s] = (Site) tuile["sites"][s] ;
    }
  }

  //recuperation des joueurs
  for(unsigned int i = 0; i < input["joueurs"].size(); ++i) {
    const json& joueur = input["joueurs"][i] ;
    //index du joueur
    int index = (int) joueur["couleur"] - 1 ;
    m_presences_joueurs[index] = true ;
    m_positions_joueurs[index] = Case(joueur["position"]) ;
    m_tuiles_joueurs[2*index] = joueur["tuile"][0] ;
    m_tuiles_joueurs[2*index + 1] = joueur["tuile"][1] ;
  }

}

} //end of namespace MMaze
