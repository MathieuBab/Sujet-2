/**
 * \file main.c
 * \brief Fichier main du deuxième TP noté - algorithmique procedurale - ING1 GM1A
 * \author Mathieu B.
 * \version 0.3
 * \date 10 décembre 2022
 *
 * Sujet 2 : Ordonnancement de processus
 *
*/

/***** les librairies *****/
#include "fonction.h"

/***** le main *****/
/**
 * \fn int main(int argc, char *argv[])
 * \brief Entrée du programme
 * \param argc argc est un entier contenant le nombre de paramètres envoyés au programme
 * \param argv *argv[] est un tableau de chaine de caractères contenant les paramètres envoyés au programme
 * \return 0 si tout c'est bien passé
*/
int main(int argc, char *argv[]) 
{
    int int_nbrProc = saisieNbrProc();
    proc proc_p;
    
    for(int i=0 ; i<int_nbrProc ; i++)
    { 
        proc_p = saisieProc();
        rajouterFile(proc_p);
    }

    choixMethode();

    return(0);
}