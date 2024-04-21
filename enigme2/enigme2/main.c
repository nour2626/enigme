#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "enigme.h"
#include <stdbool.h>
#include <stdio.h>
#include <SDL/SDL_rotozoom.h>
void runGameLoop(Enigme *e, SDL_Surface *screen,SDL_Surface *horloge[]);

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    
    SDL_Surface *screen = SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE);
    if (!screen) {
        fprintf(stderr, "Impossible de définir le mode vidéo : %s\n", SDL_GetError());
        return 1;
    }


    
    Enigme e;
    InitEnigme(&e);
    Mix_Music *music = Mix_LoadMUS("enigme.mp3");
    Mix_PlayMusic(music, -1);
    SDL_Color textColor = {255, 255, 255};

    char reponse[1024] = {0};
    char question[1024] = {0};
    char bonnes_reponses[1024] = {0};

    // Ouverture et gestion de l'index de question

    FILE *fp = fopen("question_index.txt", "r+");
    e.questionIndex = 0;
    if (fp) {
        fscanf(fp, "%d", &(e.questionIndex));
        fclose(fp);
    }

    e.questionIndex = (e.questionIndex + 1) % e.totalQuestions;  // Incrémente et boucle de 0 à 2

    fp = fopen("question_index.txt", "w");
    if (fp) {
        fprintf(fp, "%d", e.questionIndex);
        fclose(fp);
    }
 SDL_Surface *horloge[10];
    inithorloge(horloge);
    genererEnigme(&e, reponse, question, bonnes_reponses, textColor, e.questionIndex);
    afficherEnigme(&e, screen);
   
 

    runGameLoop(&e, screen,horloge);

    freeEnigme(&e);
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
    return 0;
}

void runGameLoop(Enigme *e, SDL_Surface *screen,SDL_Surface *horloge[]) {
	
    bool running = true;
    int rep = 0;  // Pour stocker la réponse sélectionnée
    SDL_Event event;
	 
Uint32 lastAnimationTime = SDL_GetTicks();

    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastAnimationTime > 100) {  // Change frame every 100 ms
            lastAnimationTime = currentTime;
            animateHorloge(horloge, screen, 10);  // Mettez à jour l'animation de l'horloge
        }

       

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        running = false;
                    }
                    switch (event.key.keysym.sym) {
                        case SDLK_a:
                            rep = 0;
                            checkAnswer(e, rep, screen);
                            break;
                        case SDLK_b:
                            rep = 1;
                            checkAnswer(e, rep, screen);
                            break;
                        case SDLK_c:
                            rep = 2;
                            checkAnswer(e, rep, screen);
                            break;
                        case SDLK_SPACE:
                            running = false;
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.x > 100 && event.button.y > 300 && event.button.x < 925 && event.button.y < 415) {
                        rep = 0;
			checkAnswer(e, rep, screen);
			break;
                    } else if (event.button.x > 100 && event.button.y > 430 && event.button.x < 925 && event.button.y < 540) {
                        rep = 1;
			checkAnswer(e, rep, screen);
			break;
                    } else if (event.button.x > 100 && event.button.y > 560 && event.button.x < 925 && event.button.y < 675) {
                        rep = 2;
			checkAnswer(e, rep, screen);
			break;
                    }
                    
                    break;
            }
        }
	
        SDL_Delay(10);
    }
}

