//
// Created by mathieu on 12/10/2022.
//

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "filters.h"
#include "transformation.h"
#include "lign_detection.h"
#include "sobel.h"
#include "display.h"

/*void saveTMPimage(SDL_Surface* surface, SDL_Renderer* renderer, char *path)
{
    SDL_Texture* newtexture = SDL_CreateTextureFromSurface(renderer,surface);
    if (newtexture == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    printf("<--💾 Saving output to %s\n", path);

    if (IMG_SavePNG(image_surface, path) != 0)
        errx(EXIT_FAILURE, "could not save the image to '%s': %s.\n", path,
             SDL_GetError());

    SDL_DestroyTexture(newtexture);
}*/

void transformation(SDL_Surface* surface)
{

    /// ------ INITIALIZE VARIABLES ------
    int w = surface->w;
    int h = surface->h;
    int len = w * h;
    /// ----------------------------------


    /// ------ SET IMAGE ------
    Uint32* pixels = surface->pixels;
    if (pixels == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    SDL_PixelFormat* format = surface->format;
    if (format == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
    SDL_LockSurface(surface);

    Uint32* pixels1 = malloc(len*sizeof(Uint32));
    if (pixels1 == NULL)
        errx(EXIT_FAILURE, "C'est de la faute de pixels1 pendant le malloc");

    Uint32* pixels2 = malloc(len*sizeof(Uint32));
    if (pixels2 == NULL)
        errx(EXIT_FAILURE, "C'est de la faute de pixels2 pendant le malloc");
    /// -----------------------


    /// ------ GRAYSCALE & CONTRASTE -------
    for(int i = 0;i<len;i++)
    {
        Uint32 tmp = pixel_to_grayscale(pixels[i],format);
        pixels[i] = contrastefilter(tmp,format);
    }
    save_image(surface,"test_grayscale_contrast.png");

    /// ------------------------------------


    /// ------ LIGHT NORMALIZATION ------
    Uint8 max = get_max(pixels,len,format);
    NormLight(pixels, format, len, max);
    save_image(surface,"test_light_normalisation.png");
    /// ---------------------------------


    /// ------ MEDIAN FILTER ------
    medianfilter(pixels,pixels1,format,w,h);
    for (int i = 0; i < len ; ++i)
    {
        pixels[i] = pixels1[i];
    }
    save_image(surface,"test_median_filter.png");
    /// ---------------------------


    /// ------ GAUSSIAN BLUR ------
    GaussianFlou(pixels,pixels1,format,w,h);
    for (int i = 0; i < len ; ++i)
    {
        pixels[i] = pixels1[i];
    }
    save_image(surface,"test_gaussian_blur.png");
    /// ---------------------------


    /// ------ BINARISATION ------
    //global noise of the picture
    float noise = noiseLevel(pixels,w,h, format);
    double seuil;
    //seuil adaptatif
    if(noise>300)
        seuil = 0.5;
    else
        seuil = 0.5;
    adaptativeThreshold(pixels,seuil,w,h, format);
    save_image(surface,"test_binarisation.png");
    /// -------------------------


    /// ------ SMOOTHING ------
    lissage(pixels,pixels1,w,h,format);
    for (int i = 0; i < len ; ++i)
    {
        pixels[i] = pixels1[i];
    }
    save_image(surface,"test_smoothing.png");
    /// -----------------------


    /// ------ SOBEL ------
    SobelEdgeDetection(surface);
    save_image(surface,"test_sobel.png");
    /// -------------------


    /// ------ HOUGH TRANSFORM ------
    double *max_Theta = malloc(sizeof(double));
    int *lenliste = malloc(sizeof(int));
    int** allLines = houghtransform(pixels,w, h, format,1,max_Theta,lenliste);
    save_image(surface,"test_hough_transform.png");
    /// -----------------------------


    free(pixels1);
    free(pixels2);
    SDL_UnlockSurface(surface);
}
