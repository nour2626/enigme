#ifndef ENIGME_H_INCLUDED
#define ENIGME_H_INCLUDED
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL_mixer.h>

typedef struct Enigme {
    SDL_Surface *background;
    SDL_Surface *questionSurface;
    SDL_Surface *answerSurfaces[3];
    SDL_Surface *correct;
    SDL_Surface *wrong;
    SDL_Rect posQ;                // Position de la question
    SDL_Rect posReponses[3];      // Positions des réponses
    TTF_Font *questionFont;
    TTF_Font *answerFont;
    char r1[256], r2[256], r3[256];  // Réponses sous forme de texte
    int correctAnswerIndices[3];
    int questionIndex;    // Index de la question actuelle
    int totalQuestions;          // Nombre total de questions
} Enigme;

void InitEnigme(Enigme *e);
void afficherEnigme(Enigme *e, SDL_Surface *screen);
void blitEnigme(Enigme *e, SDL_Surface *screen);
void freeEnigme(Enigme *e);
void genererEnigme(Enigme *e, char *reponse, char *question, char *bonnes_reponses, SDL_Color color, int questionIndex);
void checkAnswer(Enigme *e, int rep, SDL_Surface *screen);
void inithorloge(SDL_Surface *horloge[]);
void animateHorloge(SDL_Surface *horloge[], SDL_Surface *screen, int duration);
#endif // ENIGME_H_INCLUDED

