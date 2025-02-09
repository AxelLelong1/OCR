#ifndef FILTERS_H
#define FILTERS_H

Uint32 pixel_to_grayscale(Uint32 pixel_color, SDL_PixelFormat* format);
Uint32 negativefilter(Uint32 pixel_color, SDL_PixelFormat* format);
Uint32 contrastefilter(Uint32 pixel_color, SDL_PixelFormat* format);
void NormLight(Uint32* pixels, SDL_PixelFormat* format, int len, Uint8 m);
void medianfilter(Uint32* pixels,Uint32* pixels1,SDL_PixelFormat* format,int w, int h);
Uint8 get_max(Uint32* pixels, int len, SDL_PixelFormat* format);
void GaussianFlou(Uint32* pixels, Uint32* pixels1,SDL_PixelFormat* format,int w, int h);
void adaptativeThreshold(Uint32* pixels,double seuil, int w ,int h, SDL_PixelFormat* format);
float noiseLevel(Uint32* pixels,int w, int h, SDL_PixelFormat* format);
void lissage(Uint32* pixels,Uint32* pixels1,int w, int h,SDL_PixelFormat* format);
#endif
