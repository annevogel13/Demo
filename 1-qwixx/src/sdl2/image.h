#ifndef _IMAGE
#define _IMAGE

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/**
 * @brief Classe permettant de gérer l'affichage d'image à l'écran (couple Surface/Texture)
 * 
 */
class Image {

private:

    SDL_Surface * surface;
    SDL_Texture * texture;
    bool has_changed;

public:
    /**
     * @brief Constructeur de la classe Image
     * 
     */
    Image () ;

    /**
     * @brief Chargement d'une image à partir d'un fichier
     * 
     * @param filename string : Chemin vers l'image
     * @param renderer SDL_Renderer : renderer SDL2
     */
    void loadFromFile (const char* filename, SDL_Renderer * renderer);

    /**
     * @brief Chargement d'une image à partir d'une surface SDL2
     * 
     * @param renderer SDL_Renderer : renderer SDL2
     */
    void loadFromCurrentSurface (SDL_Renderer * renderer);

    void changerSurface(SDL_Surface * surf, SDL_Renderer * renderer);

    /**
     * @brief Dessine l'image en mettant à jour la surface et la texture
     * 
     * @param renderer SDL_Renderer : renderer
     * @param x int : coordonnée en x
     * @param y int : coordonnée en y
     * @param w int : largeur de l'image
     * @param h int : hauteur de l'image
     */
    void draw (SDL_Renderer * renderer, int x, int y, int w=-1, int h=-1);

    /**
     * @brief Accesseur vers la texture de la classe
     * 
     * @return SDL_Texture* 
     */
    SDL_Texture * getTexture() const;
    
    /**
     * @brief Mutateur vers la donnée surface (SDL2) de la classe
     * 
     * @param surf SDL_Surface : surface SDL2
     */
    void setSurface(SDL_Surface * surf);
};


#endif