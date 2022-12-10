/**
 * \file fonction.c
 * \brief Fichier contenant les fonctions et procédures du deuxième TP noté - algorithmique procedurale - ING1 GM1A
 * \author Mathieu B.
 * \version 0.3
 * \date 10 décembre 2022
 *
 * Sujet 2 : Ordonnancement de processus
 *
*/

/***** les librairies *****/
#include "fonction.h"

/***** fonctions et procédures *****/

/**
 * \fn int saisieNbrProc(void)
 * \brief Fonction de saisie du nombre de processus à inserer dans la file
 * \return Retourne le nombre de processus saisie
*/
int saisieNbrProc(void)
{
    int int_nbrProc;

	do 
    {
		printf("Veuillez saisir le nombre de processus voulu :\n");
		scanf("%d", &int_nbrProc);
	}while(int_nbrProc<0);
	printf("\n");

    return(int_nbrProc);
}

/**
 * \fn proc saisieProc(void)
 * \brief Fonction de recupération des données sur le processus à inserer dans la file
 * \return Retourne le processus avec les données saisies 
*/
proc saisieProc(void)
{
    proc proc_p;
	int int_temps = -1;
    int int_priorite = -1;
	
    printf("Veuillez saisir le nom du processus :\n");
    scanf("%s", proc_p.pchar_nom);
	do 
    {
		printf("Veuillez saisir le temps d'éxécution en seconde du processus :\n");
		scanf("%d", &int_temps);
	}while(int_temps<0);
	proc_p.int_tpsExec = int_temps;
    do 
    {
        printf("Veuillez saisir la priorité d'éxécution du processus (de 0 à 5, 0 étant la plus forte priorité) :\n");
        scanf("%d", &int_priorite);
    }while(int_priorite<0 || int_priorite>5);
    proc_p.int_prio = int_priorite;
	printf("\n");

    return(proc_p);
}

/**
 * \fn proc afficherProc(void)
 * \brief Procédure d'affichage d'un processus
 * \param proc_p Le processus à afficher
*/
void afficherProc(proc proc_p)
{
    printf("   * Le nom du processus est : %s\n", proc_p.pchar_nom);
    printf("   * Le temps d'éxécution du processus vaut : %ds\n", proc_p.int_tpsExec);
    printf("   * La priorité du processus vaut : %d\n", proc_p.int_prio);
}

/**
 * void ajoutActivite(proc proc_p)
 * \brief Procédure qui ajoute une activité passée en paramètre à la file de processus de l’ordonnanceur
 * \param proc_p Le processus à ajouter
*/
void ajoutActivite(proc proc_p)
{
	rajouterFile(proc_p);
}

/**
 * proc extraireActivite(void)
 * \brief Fonction qui supprime et retourne la première activité de la file de processus de l’ordonnanceur
 * \return Retourne le processus qui vient d'être retiré de la file
*/
proc extraireActivite(void)
{
	proc proc_p = premierFile();
	retirerFile();

	return(proc_p);
}

/**
 * void executerActivite(proc proc_p)
 * \brief Procédure qui exécute une activité passée en paramètre
 * en affichant son nom et sa durée et en attendant le temps correspondant à la durée de l’activité
 * \param proc_p Le processus à exécuter
*/
void executerActivite(proc proc_p)
{
	printf("Traitement du processus :\n");
	afficherProc(proc_p);
	printf("Exécution en cours...\n");
	sleep(proc_p.int_tpsExec);
	printf("Le processus [%s] a été exécuté avec succès !\n\n", proc_p.pchar_nom);
}

/**
 * void runstep(void)
 * \brief Procédure qui effectue l’ordonnancement comme suit : 
 * si la file est vide, on le dit et on ne fait rien. 
 * s’il y a au moins une activité dans la file, on la défile
 * si elle possède la bonne piorité, on l'exécute
 * sinon on la rajoute dans la file
*/
void runstep(void)
{
	if(estVideFile())
	{
		printf("La file de processus est vide.\n");
	} else {
		proc proc_p;
		int int_nbrProc;
		for(int cptPrio=0 ; cptPrio<=5 ; cptPrio++)
		{
			int_nbrProc = int_nbrElem;
			for(int i=0; i<int_nbrProc ; i++)
			{
				proc_p = extraireActivite();
				if(proc_p.int_prio == cptPrio)
				{
					executerActivite(proc_p);
				} else {
					ajoutActivite(proc_p);
				}
			}
		}
	}
}

/**
 * void trierFilePrio(void)
 * \brief Procédure qui trie la file des processus en fonction des priorités
*/
void trierFilePrio(void)
{
	proc* pproc = (proc*)malloc(int_nbrElem*sizeof(proc));
	int int_nbrProc = int_nbrElem;

	for(int i=0 ; i<int_nbrProc ; i++)
	{
		pproc[i] = extraireActivite();
	}

	for(int cptPrio=0 ; cptPrio<=5 ; cptPrio++)
	{
		for(int j=0 ; j<int_nbrProc ; j++)
		{
			if(pproc[j].int_prio == cptPrio)
			{
				ajoutActivite(pproc[j]);
				pproc[j].int_prio = -1;
			}
		}
	}

	free(pproc);
}

/**
 * void step(void)
 * \brief Procédure qui effectue un “tour” d’ordonnancement comme suit : 
 * si la file est vide, on le dit et on ne fait rien. 
 * s’il y a au moins une activité dans la file, on défile et on exécute l’activité 
 * (en affichant son nom et sa durée et en attendant le temps correspondant à la durée de l’activité)
*/
void step(void)
{
	if(estVideFile())
	{
		printf("La file de processus est vide.\n");
	} else {
		proc proc_p = extraireActivite();
		executerActivite(proc_p);
	}
}

/**
 * void run(void)
 * \brief Procédure qui itère step jusqu’à obtenir une file de processus vide
*/
void run(void)
{
	do
	{
		step();
	} while(!estVideFile());
}


/**
 * \fn void choixMethode(void)
 * \brief Procédure de choix de la méthode d'exécution de l'ordonnancement
*/
void choixMethode(void)
{
    int int_choix = -1;

    do {
        printf("Veuillez choisir la méthode :\n   [1] trier la file avant d'effectuer l'ordonnancement\n   [2] effectuer l'ordonnancement tout en triant\n");
        scanf("%d", &int_choix);
        printf("\n");
    } while(int_choix!=1 && int_choix!=2);

    switch(int_choix)
    {
        case 1:
            trierFilePrio();
			run();
            break;
        default :
            runstep();
            break;
    }
}

/**
 * \fn bool estVideFile(void)
 * \brief Fonction qui regarde si une file est vide
 * \return Retourne true si elle ne contient pas d'élements, false sinon
*/
bool estVideFile(void)
{
	if(prem == NULL && dern == NULL)
		return(true);

	return(false);
}

/**
 * \fn proc premierFile(void)
 * \brief Fonction qui retourne le premier élément de la file
 * \return Retourne le processus de début de file
*/
proc premierFile(void)
{
	if(estVideFile())
		exit(1);

	return(prem->valeur);
}

/**
 * proc dernierFile(void)
 * \brief Fonction qui retourne le dernier élément de la file
 * \return Retourne le processus de fin de file
*/
proc dernierFile(void)
{
	if(estVideFile())
		exit(1);

	return(dern->valeur);
}

/**
 * void afficherFile(void)
 * \brief Procédure qui affiche les processus de la file
*/
void afficherFile(void)
{
	if(estVideFile())
	{
		printf("Aucun processus à afficher, il n'y a pas de processus dans la file.\n");
		return;
	}

	fileElement *tmp = prem;

	while(tmp != NULL)
	{
        printf("%s, ", tmp->valeur.pchar_nom);
		printf("%d, ", tmp->valeur.int_tpsExec);
        printf("%d\n", tmp->valeur.int_prio);
		tmp = tmp->suivant;
	}
	printf("\n");
}

/**
 * void rajouterFile(proc p)
 * \brief Procédure d'ajout d'un processus à la file
 * \param p Le processus à ajouter
*/
void rajouterFile(proc proc_p)
{
	fileElement *element;

	element = malloc(sizeof(*element));

	if(element == NULL)
	{
		fprintf(stderr, "Problème d'allocation dynamique.\n");
		exit(EXIT_FAILURE);
	}

	element->valeur = proc_p;
	element->suivant = NULL;

	if(estVideFile())
	{
		prem = element;
		dern = element;
	}
	else
	{
		dern->suivant = element;
		dern = element;
	}

	int_nbrElem++;
}

/**
 * void retirerFile(void)
 * \brief Procédure pour retirer un processus de la file
*/
void retirerFile(void)
{
	if(estVideFile())
	{
		printf("Aucun processus à éxécuter, il n'y a pas de processus dans la file.\n");
		return;
	}

	fileElement *tmp = prem;

	if(prem == dern)
	{
		prem = NULL;
		dern = NULL;
	}
	else
		prem = prem->suivant;

	free(tmp);
	int_nbrElem--;
}

/**
 * void supprimerFile(void)
 * \brief Supprime tous les processus de la file
*/
void supprimerFile(void)
{
	if(estVideFile())
	{
		printf("Il n'y a pas de processus dans la file.\n");
		return;
	}

	while(!estVideFile())
		retirerFile();
}