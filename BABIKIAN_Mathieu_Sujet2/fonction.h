#ifndef FONCTION_H
#define FONCTION_H

/***** les librairies *****/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include "fonction.h"

/***** les structures et les énumérations *****/

/**
 * \struct bool
 * \brief énumération du type booléen
*/
typedef enum
{
	false,
	true
}bool;

/**
 * \struct proc
 * \brief structure d'un processus
 * 
 * Elle contient le nom ;
 * le temps d'éxecution en seconde ;
 * la priorité noté de 0 à 5, 5 étant la priorité maximale
 *
*/
typedef struct 
{
    char pchar_nom[25];
    int int_tpsExec;
    int int_prio;
}proc;

/**
 * \struct fileElement
 * \brief structure d'une file
 * 
 * Elle contient un processus
 * Elle pointe vers le processus suivant
*/
typedef struct fileElement
{
	proc valeur;
	struct fileElement *suivant;
}fileElement, *file;

/***** les paramètres static *****/
static fileElement *prem = NULL;
static fileElement *dern = NULL;
static int int_nbrElem = 0;

/***** les prototypes *****/
int saisieNbrProc(void);
proc saisieProc(void);
void afficherProc(proc proc_p);
void ajoutActivite(proc proc_p);
proc extraireActivite(void);
void executerActivite(proc proc_p);
void runstep(void);
void trierFilePrio(void);
void step(void);
void run(void);
void choixMethode(void);
bool estVideFile(void);
proc premierFile(void);
proc dernierFile(void);
void afficherFile(void);
void rajouterFile(proc proc_p);
void retirerFile(void);
void supprimerFile(void);

#endif // FONCTION_H_INCLUDED