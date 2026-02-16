#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_events.h>
#include <string.h>

int main(int argc, char *argv[]){
    if (argc < 2 || argc > 2){
        printf("Falta la imagen\n");
        return EXIT_FAILURE;
    }

    int sdl = SDL_Init(SDL_INIT_VIDEO);
    if (sdl < 0){
        printf("Error al inicializar SDL: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    int flags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_WEBP ;
    int img = IMG_Init(flags);
    if ((img & flags) != flags) {
        printf("Error al inicializar IMG: %s\n", IMG_GetError());
        return EXIT_FAILURE;
    }

    SDL_Surface* superficie = IMG_Load(argv[1]);
    if(superficie == NULL){
        printf("Error al cargar la imagen en memoria: %s\n", IMG_GetError());
        return EXIT_FAILURE;
    }


    SDL_Window* window = SDL_CreateWindow("Imagen", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, superficie ->w, superficie->h, SDL_WINDOW_HIDDEN);
    if (window == NULL) {
        printf("Error ventana: %s\n", SDL_GetError());
        SDL_FreeSurface(superficie);
        return EXIT_FAILURE;
    }

    SDL_Renderer* render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (render == NULL) {
        printf("Error creando renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_FreeSurface(superficie);
        return EXIT_FAILURE;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(render, superficie);
    SDL_FreeSurface(superficie);
    if (texture == NULL) {
        printf("Error cargando imagen: %s\n", SDL_GetError());
        SDL_DestroyRenderer(render);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_SetRenderDrawColor(render, 0,0,0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(render);
    SDL_RenderCopy(render, texture, NULL, NULL);
    SDL_RenderPresent(render);
    SDL_ShowWindow(window);


    SDL_Event event;
    int running = 1;

    while (running) {
        while(SDL_PollEvent(&event)){
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE){
                        running = 0;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    break;
            }
        }

        SDL_SetRenderDrawColor(render, 0,0,0, 255);
        SDL_RenderClear(render);
        SDL_RenderCopy(render, texture, NULL, NULL);
        SDL_RenderPresent(render);

    }

    
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

}