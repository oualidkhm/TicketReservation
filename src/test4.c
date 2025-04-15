#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//menu manager et la structure Quantite : c'est une structure contenant les jours avec les quantit�s � preparer pour chaque plat
int b; // boolean


typedef struct {
    char Day[10];
	int QtepetDej1;    int QtepetDej2;

    int QteDej1;    int QteDej2;

    int QteDiner1;
    int QteDiner2;
} Quantite;

typedef struct {
    int J, M, A;
} Date;

typedef struct {
    char Mat[9];   // Matricule (8 chiffres + caractère nul)
    char NP[30];   // Nom et prénom
    char Gn[30];   // Génie
    char Mdp[30];  // Mot de passe
    int solde; // Solde
} Etudiant;

typedef struct {
    int Id;
    char NP[50];
    int Mdp;
} Manager;
typedef struct {
    char nomJour[100];
    char platPetitDejeuner1[100];
    char platPetitDejeuner2[100];
    char platDejeuner1[100];
    char platDejeuner2[100];
    char platDinner1[100];
    char platDinner2[100];
} Jour;
typedef struct {
    char Mat[10];
    char nomJour[10];
    int QtepetDej1;
    int QtepetDej2;
    int QteDej1;
    int QteDej2;
    int QteDiner1;
    int QteDiner2;
} Reservation;



int compterEtudiants(const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "r");

    if (fichier == NULL) {
        perror("Impossible d'ouvrir le fichier.");
        return -1;  // Erreur d'ouverture de fichier
    }

    Etudiant etd;

    int nombreDEtudiants = 0;

    // Lire chaque structure Etudiant dans le fichier
    while (fscanf(fichier, "%s %s %s %s %d", etd.Mat, etd.NP, etd.Gn, etd.Mdp, &etd.solde) != EOF) {
        nombreDEtudiants++;
    }

    fclose(fichier);

    return nombreDEtudiants;
}
void decrementerSolde(int matricule, int valeurADecrementer) {
    FILE *fichier;
    fichier = fopen("liste_etudiant.txt", "r+");

    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }

    Etudiant etudiants[100];  // Supposons qu'il y a au plus 100 étudiants dans le fichier
    int nombreEtudiants = 0;

    // Lire tous les étudiants du fichier et stocker en mémoire
    while (fscanf(fichier, "%s %s %s %s %d",
                  etudiants[nombreEtudiants].Mat, etudiants[nombreEtudiants].NP,
                  etudiants[nombreEtudiants].Gn, etudiants[nombreEtudiants].Mdp,
                  &etudiants[nombreEtudiants].solde) != EOF) {
        nombreEtudiants++;
    }

    // Rechercher l'étudiant dans la mémoire
    int i;
    for (i = 0; i < nombreEtudiants; i++) {
        int matriculeInt = atoi(etudiants[i].Mat);

        if (matriculeInt == matricule) {
            // Décrémente le solde de l'étudiant
            etudiants[i].solde -= valeurADecrementer;
            printf("Solde décrémenté.\n");

            // Retourner au début du fichier pour écrire les modifications
            rewind(fichier);

            // Écrire toutes les entrées modifiées dans le fichier
            for (int j = 0; j < nombreEtudiants; j++) {
                fprintf(fichier, "%s %s %s %s %d\n",
                        etudiants[j].Mat, etudiants[j].NP, etudiants[j].Gn,
                        etudiants[j].Mdp, etudiants[j].solde);
            }

            // Tronquer le fichier pour supprimer les anciennes données excédentaires
            ftruncate(fileno(fichier), ftell(fichier));

            printf("Solde mis à jour avec succès pour le matricule %d.\n", matricule);
            break;
        }
    }

    // Si l'étudiant n'est pas trouvé, afficher un message approprié
    if (i == nombreEtudiants) {
        printf("Étudiant non trouvé dans la liste.\n");
    }

    // Fermer le fichier
    fclose(fichier);
}

void incrementerPetitDejeuner1(char jourRecherche[10], int Qteaincrementer) {
    FILE *fichier;
        fichier = fopen("stats.txt", "a");
        fclose(fichier);

    fichier = fopen("stats.txt", "r+");

    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }

    Quantite quantites[100];
    int nbJours = 0;

    // Lire toutes les structures Quantite dans le fichier et stocker en mémoire
    while (fscanf(fichier, "%s %d %d %d %d %d %d",
                  quantites[nbJours].Day, &quantites[nbJours].QtepetDej1, &quantites[nbJours].QtepetDej2,
                  &quantites[nbJours].QteDej1, &quantites[nbJours].QteDej2,
                  &quantites[nbJours].QteDiner1, &quantites[nbJours].QteDiner2) != EOF) {
        nbJours++;
    }

    // Rechercher le jour dans la mémoire
    int i;
    for (i = 0; i < nbJours; i++) {
        if (strcmp(quantites[i].Day, jourRecherche) == 0) {
            // Jour trouvé, incrémenter la quantité de petit-déjeuner 1
            quantites[i].QtepetDej1 += Qteaincrementer;

            // Repositionner le curseur pour réécrire les données mises à jour
            fseek(fichier, 0, SEEK_SET);

            // Écrire toutes les entrées modifiées dans le fichier
            for (int j = 0; j < nbJours; j++) {
                fprintf(fichier, "%s %d %d %d %d %d %d\n",
                        quantites[j].Day, quantites[j].QtepetDej1, quantites[j].QtepetDej2,
                        quantites[j].QteDej1, quantites[j].QteDej2,
                        quantites[j].QteDiner1, quantites[j].QteDiner2);
            }

            // Tronquer le fichier pour supprimer les anciennes données excédentaires
            ftruncate(fileno(fichier), ftell(fichier));

            break; // Sortir de la boucle une fois que le jour est trouvé
        }
    }

    fclose(fichier);
}


void incrementerPetitDejeuner2(char jourRecherche[10], int Qteaincrementer) {
    FILE *fichier;
    fichier = fopen("stats.txt", "r+");

    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }

    Quantite quantites[100];
    int nbJours = 0;

    while (fscanf(fichier, "%s %d %d %d %d %d %d",
                  quantites[nbJours].Day, &quantites[nbJours].QtepetDej1, &quantites[nbJours].QtepetDej2,
                  &quantites[nbJours].QteDej1, &quantites[nbJours].QteDej2,
                  &quantites[nbJours].QteDiner1, &quantites[nbJours].QteDiner2) != EOF) {
        nbJours++;
    }

    int i;
    for (i = 0; i < nbJours; i++) {
        if (strcmp(quantites[i].Day, jourRecherche) == 0) {
            quantites[i].QtepetDej2 += Qteaincrementer;
            fseek(fichier, 0, SEEK_SET);

            for (int j = 0; j < nbJours; j++) {
                fprintf(fichier, "%s %d %d %d %d %d %d\n",
                        quantites[j].Day, quantites[j].QtepetDej1, quantites[j].QtepetDej2,
                        quantites[j].QteDej1, quantites[j].QteDej2,
                        quantites[j].QteDiner1, quantites[j].QteDiner2);
            }

            ftruncate(fileno(fichier), ftell(fichier));
            break;
        }
    }

    fclose(fichier);
}

void incrementerDejeuner1(char jourRecherche[10], int Qteaincrementer) {
    FILE *fichier;
    fichier = fopen("stats.txt", "r+");

    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }

    Quantite quantites[100];
    int nbJours = 0;

    while (fscanf(fichier, "%s %d %d %d %d %d %d",
                  quantites[nbJours].Day, &quantites[nbJours].QtepetDej1, &quantites[nbJours].QtepetDej2,
                  &quantites[nbJours].QteDej1, &quantites[nbJours].QteDej2,
                  &quantites[nbJours].QteDiner1, &quantites[nbJours].QteDiner2) != EOF) {
        nbJours++;
    }

    int i;
    for (i = 0; i < nbJours; i++) {
        if (strcmp(quantites[i].Day, jourRecherche) == 0) {
            quantites[i].QteDej1 += Qteaincrementer;

            fseek(fichier, 0, SEEK_SET);

            for (int j = 0; j < nbJours; j++) {
                fprintf(fichier, "%s %d %d %d %d %d %d\n",
                        quantites[j].Day, quantites[j].QtepetDej1, quantites[j].QtepetDej2,
                        quantites[j].QteDej1, quantites[j].QteDej2,
                        quantites[j].QteDiner1, quantites[j].QteDiner2);
            }

            ftruncate(fileno(fichier), ftell(fichier));
            break;
        }
    }

    fclose(fichier);
}

void incrementerDejeuner2(char jourRecherche[10], int Qteaincrementer) {
    FILE *fichier;
    fichier = fopen("stats.txt", "r+");

    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }

    Quantite quantites[100];
    int nbJours = 0;

    while (fscanf(fichier, "%s %d %d %d %d %d %d",
                  quantites[nbJours].Day, &quantites[nbJours].QtepetDej1, &quantites[nbJours].QtepetDej2,
                  &quantites[nbJours].QteDej1, &quantites[nbJours].QteDej2,
                  &quantites[nbJours].QteDiner1, &quantites[nbJours].QteDiner2) != EOF) {
        nbJours++;
    }

    int i;
    for (i = 0; i < nbJours; i++) {
        if (strcmp(quantites[i].Day, jourRecherche) == 0) {
            quantites[i].QteDej2 += Qteaincrementer;

            fseek(fichier, 0, SEEK_SET);

            for (int j = 0; j < nbJours; j++) {
                fprintf(fichier, "%s %d %d %d %d %d %d\n",
                        quantites[j].Day, quantites[j].QtepetDej1, quantites[j].QtepetDej2,
                        quantites[j].QteDej1, quantites[j].QteDej2,
                        quantites[j].QteDiner1, quantites[j].QteDiner2);
            }

            ftruncate(fileno(fichier), ftell(fichier));
            break;
        }
    }

    fclose(fichier);
}

void incrementerDiner1(char jourRecherche[10], int Qteaincrementer) {
    FILE *fichier;
    fichier = fopen("stats.txt", "r+");

    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }

    Quantite quantites[100];
    int nbJours = 0;

    while (fscanf(fichier, "%s %d %d %d %d %d %d",
                  quantites[nbJours].Day, &quantites[nbJours].QtepetDej1, &quantites[nbJours].QtepetDej2,
                  &quantites[nbJours].QteDej1, &quantites[nbJours].QteDej2,
                  &quantites[nbJours].QteDiner1, &quantites[nbJours].QteDiner2) != EOF) {
        nbJours++;
    }

    int i;
    for (i = 0; i < nbJours; i++) {
        if (strcmp(quantites[i].Day, jourRecherche) == 0) {
            quantites[i].QteDiner1 += Qteaincrementer;

            fseek(fichier, 0, SEEK_SET);

            for (int j = 0; j < nbJours; j++) {
                fprintf(fichier, "%s %d %d %d %d %d %d\n",
                        quantites[j].Day, quantites[j].QtepetDej1, quantites[j].QtepetDej2,
                        quantites[j].QteDej1, quantites[j].QteDej2,
                        quantites[j].QteDiner1, quantites[j].QteDiner2);
            }

            ftruncate(fileno(fichier), ftell(fichier));
            break;
        }
    }

    fclose(fichier);
}

void incrementerDiner2(char jourRecherche[10], int Qteaincrementer) {
    FILE *fichier;
    fichier = fopen("stats.txt", "r+");

    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }

    Quantite quantites[100];
    int nbJours = 0;

    while (fscanf(fichier, "%s %d %d %d %d %d %d",
                  quantites[nbJours].Day, &quantites[nbJours].QtepetDej1, &quantites[nbJours].QtepetDej2,
                  &quantites[nbJours].QteDej1, &quantites[nbJours].QteDej2,
                  &quantites[nbJours].QteDiner1, &quantites[nbJours].QteDiner2) != EOF) {
        nbJours++;
    }

    int i;
    for (i = 0; i < nbJours; i++) {
        if (strcmp(quantites[i].Day, jourRecherche) == 0) {
            quantites[i].QteDiner2 += Qteaincrementer;

            fseek(fichier, 0, SEEK_SET);

            for (int j = 0; j < nbJours; j++) {
                fprintf(fichier, "%s %d %d %d %d %d %d\n",
                        quantites[j].Day, quantites[j].QtepetDej1, quantites[j].QtepetDej2,
                        quantites[j].QteDej1, quantites[j].QteDej2,
                        quantites[j].QteDiner1, quantites[j].QteDiner2);
            }

            ftruncate(fileno(fichier), ftell(fichier));
            break;
        }
    }

    fclose(fichier);
}




void tickets_reservation(int matricule, char jourRecherche[10], int QtepetDej1, int QtepetDej2, int QteDej1, int QteDej2, int QteDiner1, int QteDiner2) {
    FILE *fichierTickets;
    fichierTickets = fopen("tickets.txt", "a+"); // Ouvrir le fichier en mode ajout et lecture

    if (fichierTickets == NULL) {
        printf("Impossible d'ouvrir le fichier tickets.txt.\n");
        return;
    }

    // Créer une structure Reservation pour stocker les informations de la réservation
    Reservation reservation;
    sprintf(reservation.Mat, "%d", matricule); // Convertir le matricule en chaîne de caractères
    strcpy(reservation.nomJour, jourRecherche);
    reservation.QtepetDej1 = QtepetDej1;
    reservation.QtepetDej2 = QtepetDej2;
    reservation.QteDej1 = QteDej1;
    reservation.QteDej2 = QteDej2;
    reservation.QteDiner1 = QteDiner1;
    reservation.QteDiner2 = QteDiner2;

    // Écrire les informations de la réservation dans le fichier
    fprintf(fichierTickets, "%s %s %d %d %d %d %d %d\n",
            reservation.Mat, reservation.nomJour,
            reservation.QtepetDej1, reservation.QtepetDej2,
            reservation.QteDej1, reservation.QteDej2,
            reservation.QteDiner1, reservation.QteDiner2);

    printf("Réservation confirmée avec succès.\n");

    fclose(fichierTickets);
}
int check_reserve(int matricule, char jourRecherche[10]) {
    FILE *fichierTickets;
    fichierTickets = fopen("tickets.txt", "r"); // Ouvrir le fichier en mode lecture

    if (fichierTickets == NULL) {
        printf("Impossible d'ouvrir le fichier tickets.txt.\n");
        return 0; // La réservation n'existe pas
    }

    // Vérifier si une réservation existe déjà pour cet étudiant et ce jour
    Reservation existingReservation;
    while (fscanf(fichierTickets, "%s %s %*d %*d %*d %*d %*d %*d",
                  existingReservation.Mat, existingReservation.nomJour) != EOF) {
        if (atoi(existingReservation.Mat) == matricule && strcmp(existingReservation.nomJour, jourRecherche) == 0) {
            // Une réservation existe déjà pour cet étudiant et ce jour
            printf("Vous avez déjà une réservation pour cet étudiant et ce jour.\n");
            fclose(fichierTickets);
            return 1; // Une réservation existe
        }
    }

    fclose(fichierTickets);
    return 0; // La réservation n'existe pas
}

void reserver(int mlesaisi) {
    char jourRecherche[10];
    printf("Entrez le jour pour lequel vous souhaitez réserver les plats : ");
    scanf("%s", jourRecherche);

    FILE *f = fopen("menu.txt", "r");
    Jour JOUR;
if (!check_reserve(mlesaisi,jourRecherche)){
    if (f == NULL) {
        printf("Impossible d'ouvrir le fichier menu.txt.\n");
        return;
    }

    while (fscanf(f, "%s %s %s %s %s %s %s", JOUR.nomJour, JOUR.platPetitDejeuner1, JOUR.platPetitDejeuner2, JOUR.platDejeuner1, JOUR.platDejeuner2, JOUR.platDinner1, JOUR.platDinner2) != EOF) {
        printf("\n\n%s", JOUR.nomJour);
        if (strcmp(JOUR.nomJour, jourRecherche) == 0) {
            printf("Le menu de ce jour est pour :\nPetit Déjeuner : \t%s \tet \t%s\nDéjeuner :       \t%s\t et \t%s \nDîner :          \t%s \tet \t%s\n",
                   JOUR.platPetitDejeuner1, JOUR.platPetitDejeuner2, JOUR.platDejeuner1, JOUR.platDejeuner2, JOUR.platDinner1, JOUR.platDinner2);
            break;
        }
    }
    fclose(f);

    int QtepetDej1, QteDej1, QteDiner1, QtepetDej2, QteDej2, QteDiner2; // Variables à déclarer pour la quantité de chaque plat
    printf("Entrez la quantité de petit déjeuner1 : ");
    scanf("%d", &QtepetDej1);
    printf("Entrez la quantité de petit déjeuner2 : ");
    scanf("%d", &QtepetDej2);
    printf("Entrez la quantité de petit déjeuner1 : ");
    scanf("%d", &QteDej1);
    printf("Entrez la quantité de petit déjeuner2 : ");
    scanf("%d", &QteDej2);
    printf("Entrez la quantité de dîner1 : ");
    scanf("%d", &QteDiner1);
    printf("Entrez la quantité de dîner2 : ");
    scanf("%d", &QteDiner2);
    printf("merci\n\n\n\n\n ");


    int prixtotal = (QtepetDej1 + QtepetDej2 + QteDej1 + QteDej2 + QteDiner1 + QteDiner2) * 2;
    printf("prix total = %d\n", prixtotal);

    FILE *fichEtudiant = fopen("liste_etudiant.txt", "r");
    Etudiant etd;

    if (fichEtudiant == NULL) {
        printf("Impossible d'ouvrir le fichier etudiants.txt.\n");
        return;
    }

    while (fscanf(fichEtudiant, "%s %s %s %s %d", etd.Mat, etd.NP, etd.Gn, etd.Mdp, &etd.solde) != EOF) {
        int matriculeInt = atoi(etd.Mat);
        if (matriculeInt == mlesaisi) {
            float soldeactuelle = etd.solde;
            int mledetudiant = matriculeInt;
            fclose(fichEtudiant);
{
            if (soldeactuelle >= prixtotal) {
                incrementerPetitDejeuner1(jourRecherche, QtepetDej1);
                incrementerDejeuner2(jourRecherche, QteDej2);
                incrementerDejeuner1(jourRecherche, QteDej1);
                incrementerDiner1(jourRecherche, QteDiner1);
                incrementerDiner2(jourRecherche, QteDiner2);
                incrementerPetitDejeuner2(jourRecherche, QtepetDej2);
                decrementerSolde(mledetudiant, prixtotal);
                tickets_reservation(mledetudiant, jourRecherche, QtepetDej1, QtepetDej2, QteDej1, QteDej2, QteDiner1, QteDiner2);
            } else {
                printf("Votre solde n'est pas suffisant pour cette opération. Vous devez minimaliser le prix de %d Dh\n", prixtotal - (int)soldeactuelle);
                printf("Souhaitez-vous continuer la réservation ? 0 si non, autre si oui\n ");
                scanf("%d", &b);
                if (b) {
                    // Réafficher les options de quantités des plats ou permettre à l'utilisateur de réajuster les quantités
                    printf("Vous êtes en train de rechoisir les quantités des plats...\n");
                    reserver(mlesaisi);
                } else {
                    exit(0);
                }
            }
            break;
        }
    }
}}}
void afficherReservationsJour(int matricule, char jourRecherche[10]) {
    FILE *fichierTickets;
    fichierTickets = fopen("tickets.txt", "r");

    if (fichierTickets == NULL) {
        printf("Impossible d'ouvrir le fichier tickets.txt.\n");
        return;
    }

    Reservation reservation;
    int found = 0;

    while (fscanf(fichierTickets, "%s %s %d %d %d %d %d %d",
                  reservation.Mat, reservation.nomJour,
                  &reservation.QtepetDej1, &reservation.QtepetDej2,
                  &reservation.QteDej1, &reservation.QteDej2,
                  &reservation.QteDiner1, &reservation.QteDiner2) != EOF) {
        int matriculeInt = atoi(reservation.Mat);

        if (matriculeInt == matricule && strcmp(reservation.nomJour, jourRecherche) == 0) {
            found = 1;

            // Affichage stylisé en forme de "ticket"
            printf("***************************************************\n");
            printf("*               TICKET RÉSERVATION               *\n");
            printf("***************************************************\n");
            printf("Matricule: %d\n", matricule);
            printf("Jour: %s\n", reservation.nomJour);
            printf("----------------------------------------------------\n");
            printf("Petit Déjeuner 1: %d\n", reservation.QtepetDej1);
            printf("Petit Déjeuner 2: %d\n", reservation.QtepetDej2);
            printf("Déjeuner 1: \t   %d\n", reservation.QteDej1);
            printf("Déjeuner 2: \t   %d\n", reservation.QteDej2);
            printf("Dîner 1:          %d\n", reservation.QteDiner1);
            printf("Dîner 2:          %d\n", reservation.QteDiner2);
            printf("---------------------------------------------------\n");
            printf("          Merci pour votre réservation!         \n");
            printf("**************************************************\n");
        }
    }

    fclose(fichierTickets);

    if (!found) {
        printf("Aucune réservation trouvée pour le matricule %d et le jour %s.\n", matricule, jourRecherche);
    }
}





int main() {
    int choix;

    do {printf("\n\n\t\t\t\t\t\t\t----------------\n");
        printf("\t\t\t\t\t\t\t1.MENU PRINCIPAL \n");
        printf("\t\t\t\t\t\t\t----------------\n\n\n\n\n");
        printf("\t\t\t1. Créer un compte\t\t\t\t\t");
        printf("2. Se connecter\n\n");
        printf("\t\t\t\t\t\t\t3. Quitter\n\n\n");
        printf("\t\t\t\t\tEntrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                creercompte();
                break;
            case 2:
                log_in();
                break;
            case 3:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }

    } while (choix != 3);

    return 0;
}
void creercompte() {
    FILE *P;
    Etudiant etd;
    char matricule[30];

    // Ouvrir le fichier en mode "a" (append)
    P = fopen("liste_etudiant.txt", "a");
    if (P == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }
    fclose(P);  // Fermer le fichier après l'ouverture en mode append

    // Ouvrir le fichier en mode "r+" (lecture et écriture)
    P = fopen("liste_etudiant.txt", "r+");
    if (P == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }

    int matriculeExiste = 0;

    // Vérifier si le matricule a bien 8 chiffres
    do {
        printf("Entrez votre matricule (8 chiffres) : ");
        scanf("%s", matricule);

        if (strlen(matricule) != 8) {
            printf("Le matricule doit être un nombre de 8 chiffres. Veuillez réessayer.\n");

        }}while(strlen(matricule) != 8);

        // Rembobiner le fichier au début pour effectuer la vérification
        rewind(P);

        // Vérifier si le matricule existe déjà
        while (fscanf(P, "%s %s %s %s %d", etd.Mat, etd.NP, etd.Gn, etd.Mdp, &etd.solde) != EOF) {
            if (strcasecmp(etd.Mat, matricule) == 0) {
                printf("Le matricule existe déjà. Veuillez en choisir un autre.\n");
                matriculeExiste = 1;
                break;  // Sortir de la boucle dès qu'on trouve une correspondance
            }
        }



    while (!matriculeExiste){

    // Saisir les informations de l'étudiant
    printf("\nEntrer vos informations :\n");
    printf("Nom et prénom : ");
    scanf("%s", etd.NP);
    printf("Génie : ");
    scanf("%s", etd.Gn);
    printf("Mot de passe : ");
    scanf("%s", etd.Mdp);
    printf("Solde initial : ");
    scanf("%d", &etd.solde);

    // Écrire les informations dans le fichier
    fprintf(P, "%s %s %s %s %d\n", matricule, etd.NP, etd.Gn, etd.Mdp, etd.solde);
    printf("Vous avez créé votre compte avec succès.\n");

    fclose(P);  // Fermer le fichier après l'écriture
break;
}}




void log_in() {
    int Matr, mdp, choix;
    FILE *P;
    Etudiant etd;

    printf("Entrez votre matricule: ");
    scanf("%d", &Matr);
    printf("Entrez votre mot de passe: ");
    scanf("%d", &mdp);

    int matriculeManager = 123450;  // Remplacez par le matricule souhaité
    int mdpManager = 0000;

    if (Matr >= 10000000 && Matr <= 99999999) {
        P = fopen("liste_etudiant.txt", "a");
        fclose(P);
        P = fopen("liste_etudiant.txt", "r");
        if (P == NULL) {
            fprintf(stderr, "Impossible d'ouvrir le fichier.\n");
            return;
        }


        // Utilisation de fscanf pour lire à la fois le matricule et le mot de passe
        while (fscanf(P, "%s %s %s %s %d", etd.Mat, etd.NP,etd.Gn,etd.Mdp,&etd.solde) !=EOF) {
            int matriculeInt = atoi(etd.Mat);
            int MdpInt = atoi(etd.Mdp);
            if (matriculeInt == Matr && MdpInt == mdp) {
                do {
                    menu_etudiant();
                    printf("Entrez votre choix : ");
                    scanf("%d", &choix);
                    switch (choix) {
                        case 1:
                            reserver(Matr);
                            break;
                        case 2:
                            printf("Entrez le jour pour afficher les réservations : ");
                            char jourRecherche[10];
                            scanf("%s", jourRecherche);
                            afficherReservationsJour(Matr, jourRecherche);
                            break;

                        case 3:
                            annulerReservation(Matr);
                            break;
                        case 0:
                            break;
                        default:
                            printf("Choix invalide. Veuillez réessayer.\n");
                    }
                } while (choix != 0);
                  // Sortir de la boucle après avoir trouvé une correspondance
            }};


        fclose(P);}
     else if (Matr >= 100000 && Matr <= 999999) {
        // Vérification directe pour le manager
        if (Matr == matriculeManager && mdp == mdpManager) {
            // Vous devez définir la fonction jutos()
            jutos();
        } else if (Matr == 112200 && mdp == 0000) {
            menu_SOLDEmanager();
        } else {
            printf("Matricule ou mot de passe incorrect.\n");
        }
    } else {
        printf("Le matricule doit être un nombre de 8 chiffres si vous êtes un étudiant\n");
        printf("ou un nombre de 6 chiffres si vous êtes un employé. Veuillez réessayer.\n");
    }
}

 void menu_SOLDEmanager() {
    int choix;

    do {
        printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t-----------------\n");
        printf("\t\t\t\t\t\t\tmenu_SOLDE_manager \n");
        printf("\t\t\t\t\t\t\t-----------------\n\n\n\n\n");
        printf("\t\t\t1. Amplifier un solde\t\t\t");
        printf("\t\t\t0. Quitter\n\n\n");

        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                suparo();  // Appel de la fonction pour amplifier le solde
                break;
            case 0:
                printf("Sortie du menu.\n\n\n\n\n\n\n\n\n\n");
                break;
            default:
                printf("Choix invalide. Veuillez entrer un choix valide.\n");
        }
    } while (choix != 0);
}


void menu_etudiant() {
    printf("\n\t\t\t\t\t\t\t-------------\n");
    printf("\t\t\t\t\t\t\tMENU ETUDIANT \n");
    printf("\t\t\t\t\t\t\t-------------\n\n\n\n\n");
    printf("\t\t\t1. Reserver\t\t\t\t\t");
    printf("2. liste des reservations\n\n");
    printf("\t\t\t\t\t\t3. Annuler la reservation\n\n\n");
    printf("\t\t\t\t\t\t\t0. Quitter\n");
}

// Définir la structure Jour


void remplirMenu() {
    FILE *fichierMenu;
    Jour jour;
    char jourExistant[100];

    // Ouvrir le fichier en mode lecture ("r")
    fichierMenu = fopen("menu.txt", "a");
    fclose(fichierMenu);
        fichierMenu = fopen("menu.txt", "r");


    // Vérifier si le fichier est ouvert avec succès
    if (fichierMenu == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    // Demander à l'utilisateur de saisir les informations pour chaque jour
    printf("Remplir le menu :\n");

    // Demander à l'utilisateur de saisir le nom du jour
    printf("Nom du jour : ");
    scanf("%s", jourExistant);

    // Convertir le nom du jour en minuscules (ignorer la casse)
    strncpy(jourExistant, strlwr(jourExistant), sizeof(jourExistant));

    // Vérifier si le jour existe déjà dans le fichier
    while (fscanf(fichierMenu, "%s %s %s %s %s %s %s",
                  jour.nomJour, jour.platPetitDejeuner1, jour.platPetitDejeuner2,
                  jour.platDejeuner1, jour.platDejeuner2, jour.platDinner1, jour.platDinner2) != EOF) {
        // Convertir le nom du jour dans le fichier en minuscules (ignorer la casse)
        if (strcasecmp(jour.nomJour, jourExistant) == 0) {
            printf("Le menu pour le jour %s existe deja. Veuillez choisir une autre action.\n", jourExistant);

            // Fermer le fichier et retourner sans ajouter d'entrée
            fclose(fichierMenu);
            return;
        }
    }

    // Fermer le fichier
    fclose(fichierMenu);

    // Si le jour n'existe pas, ouvrir le fichier en mode ajout ("a") pour ajouter à la fin
    fichierMenu = fopen("menu.txt", "a");

    // Vérifier si le fichier est ouvert avec succès
    if (fichierMenu == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    // Demander à l'utilisateur de saisir les plats sans espaces, sous forme de composantes
    printf("Plat petit dejeuner 1 (composante1+composante2) : ");
    scanf("%s", jour.platPetitDejeuner1);

    printf("Plat petit dejeuner 2 (composante1+composante2) : ");
    scanf("%s", jour.platPetitDejeuner2);

    printf("Plat dejeuner 1 (composante1+composante2) : ");
    scanf("%s", jour.platDejeuner1);

    printf("Plat dejeuner 2 (composante1+composante2) : ");
    scanf("%s", jour.platDejeuner2);

    printf("Plat diner 1 (composante1+composante2) : ");
    scanf("%s", jour.platDinner1);

    printf("Plat diner 2 (composante1+composante2) : ");
    scanf("%s", jour.platDinner2);

    // Écrire la structure Jour dans le fichier
    fprintf(fichierMenu, "%s %s %s %s %s %s %s\n",
            jourExistant, jour.platPetitDejeuner1, jour.platPetitDejeuner2,
            jour.platDejeuner1, jour.platDejeuner2, jour.platDinner1, jour.platDinner2);

    // Fermer le fichier
    fclose(fichierMenu);

    printf("Menu enregistre avec succes dans le fichier menu.txt.\n");
}

void modifierMenu() {
    FILE *fichierMenu;
    Jour jours[100];  // Supposons qu'il y a au plus 100 jours dans le fichier
    char jourRecherche[100];

    // Ouvrir le fichier en mode lecture ("r+")
    fichierMenu = fopen("menu.txt", "r+");

    // Vérifier si le fichier est ouvert avec succès
    if (fichierMenu == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    // Demander à l'utilisateur de saisir le jour à rechercher
    printf("Entrer le nom du jour a rechercher : ");
    scanf("%s", jourRecherche);

    int nbJours = 0;

    // Lire tous les jours du fichier et stocker en mémoire
    while (fscanf(fichierMenu, "%s %s %s %s %s %s %s",
                  jours[nbJours].nomJour, jours[nbJours].platPetitDejeuner1,
                  jours[nbJours].platPetitDejeuner2, jours[nbJours].platDejeuner1,
                  jours[nbJours].platDejeuner2, jours[nbJours].platDinner1,
                  jours[nbJours].platDinner2) != EOF) {
        nbJours++;
    }

    // Rechercher le jour dans la mémoire
    int i;
    for (i = 0; i < nbJours; i++) {
        if (strcmp(jours[i].nomJour, jourRecherche) == 0) {
            // Jour trouvé, demander à l'utilisateur de saisir les nouvelles informations
            printf("Jour trouve. Entrez les nouvelles informations pour le jour %s :\n", jourRecherche);

            printf("Plat petit dejeuner 1 (composante1+composante2) : ");
            scanf("%s", jours[i].platPetitDejeuner1);

            printf("Plat petit dejeuner 2 (composante1+composante2) : ");
            scanf("%s", jours[i].platPetitDejeuner2);

            printf("Plat dejeuner 1 (composante1+composante2) : ");
            scanf("%s", jours[i].platDejeuner1);

            printf("Plat dejeuner 2 (composante1+composante2) : ");
            scanf("%s", jours[i].platDejeuner2);

            printf("Plat diner 1 (composante1+composante2) : ");
            scanf("%s", jours[i].platDinner1);

            printf("Plat diner 2 (composante1+composante2) : ");
            scanf("%s", jours[i].platDinner2);

            // Retourner au début du fichier pour écrire les modifications
            rewind(fichierMenu);

            // Écrire toutes les entrées modifiées dans le fichier
            for (int j = 0; j < nbJours; j++) {
                fprintf(fichierMenu, "%s %s %s %s %s %s %s\n",
                        jours[j].nomJour, jours[j].platPetitDejeuner1,
                        jours[j].platPetitDejeuner2, jours[j].platDejeuner1,
                        jours[j].platDejeuner2, jours[j].platDinner1,
                        jours[j].platDinner2);
            }

            // Tronquer le fichier pour supprimer les anciennes données excédentaires

            printf("Menu mis à jour avec succes pour le jour %s.\n", jourRecherche);
            break;
        }
    }

    // Si le jour n'est pas trouvé, afficher un message approprié
    if (i == nbJours) {
        printf("Jour non trouve dans le menu.\n");
    }

    // Fermer le fichier
    fclose(fichierMenu);
}
void afficherStats() {
    FILE *fichier;
    fichier = fopen("stats.txt", "r");

    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }

    Quantite quantites[100];
    int nbJours = 0;

    while (fscanf(fichier, "%s %d %d %d %d %d %d",
                  quantites[nbJours].Day, &quantites[nbJours].QtepetDej1, &quantites[nbJours].QtepetDej2,
                  &quantites[nbJours].QteDej1, &quantites[nbJours].QteDej2,
                  &quantites[nbJours].QteDiner1, &quantites[nbJours].QteDiner2) != EOF) {
        nbJours++;
    }

    fclose(fichier);

    // Demander au gestionnaire quel jour afficher
    char jourRecherche[10];
    printf("Entrer le jour a afficher : ");
    scanf("%s", jourRecherche);

    // Rechercher le jour dans la mémoire
    int i;
    for (i = 0; i < nbJours; i++) {
        if (strcmp(quantites[i].Day, jourRecherche) == 0) {
            // Jour trouvé, afficher les résultats
            printf("\t\t\t\t\t\tStatistiques des reservations pour le jour %s :\n", jourRecherche);
            printf("\t\t\t\t\tpetit Dejeuner  1 :    %d plats a preparer\n\n", quantites[i].QtepetDej1);
            printf("\t\t\t\t\tpetit Dejeuner  2 :    %d plats a preparer\n\n", quantites[i].QtepetDej2);
            printf("\t\t\t\t\tDejeuner  1 :           %d plats a preparer\n\n", quantites[i].QteDej1);
            printf("\t\t\t\t\tDejeuner  2 :           %d plats a preparer\n\n", quantites[i].QteDej2);
            printf("\t\t\t\t\tdiner 1 :               %d plats a preparer\n\n", quantites[i].QteDiner1);
            printf("\t\t\t\t\tdiner 2 :               %d plats a preparer\n\n", quantites[i].QteDiner2);
            // Ajouter d'autres affichages pour chaque plat et choix...
            break;
        }
    }
    int choixOption;
    printf("Choisissez une option :\n");
    printf("1. Reinitialiser les compteurs pour ce jour\n");
    printf("2. Ne rien faire\n");
    scanf("%d", &choixOption);

    switch (choixOption) {
        case 1:
            resetCompteurs(jourRecherche);
            break;
        case 2:
            // Ne rien faire
            break;
        default:
            printf("Option invalide\n");
    }


    // Si le jour n'est pas trouvé, afficher un message approprié
    if (i == nbJours) {
        printf("Jour non trouve dans les statistiques.\n");
    }
}

void resetCompteurs() {
    FILE *fichier;
    fichier = fopen("stats.txt", "r");

    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }

    Quantite quantites[100];
    int nbJours = 0;

    while (fscanf(fichier, "%s %d %d %d %d %d %d",
                  quantites[nbJours].Day, &quantites[nbJours].QtepetDej1, &quantites[nbJours].QtepetDej2,
                  &quantites[nbJours].QteDej1, &quantites[nbJours].QteDej2,
                  &quantites[nbJours].QteDiner1, &quantites[nbJours].QteDiner2) != EOF) {
        nbJours++;
    }

    fclose(fichier);

    // Demander au gestionnaire quel jour réinitialiser
    char jourRecherche[10];
    printf("Entrer le jour a reinitialiser : ");
    scanf("%s", jourRecherche);

    // Rechercher le jour dans la mémoire
    int i;
    for (i = 0; i < nbJours; i++) {
        if (strcmp(quantites[i].Day, jourRecherche) == 0) {
            // Jour trouvé, réinitialiser les compteurs
            quantites[i].QtepetDej1 = 0;
            quantites[i].QtepetDej2 = 0;
            quantites[i].QteDej1 = 0;
            quantites[i].QteDej2 = 0;
            quantites[i].QteDiner1 = 0;
            quantites[i].QteDiner2 = 0;
            printf("Compteurs réinitialisés avec succès pour le jour %s.\n", jourRecherche);
            break;
        }
    }

    // Si le jour n'est pas trouvé, afficher un message approprié
    if (i == nbJours) {
        printf("Jour non trouvé dans les statistiques.\n");
    }

    // Réécrire les données dans le fichier après réinitialisation
    fichier = fopen("stats.txt", "w");

    for (int j = 0; j < nbJours; j++) {
        fprintf(fichier, "%s %d %d %d %d %d %d\n",
                quantites[j].Day, quantites[j].QtepetDej1, quantites[j].QtepetDej2,
                quantites[j].QteDej1, quantites[j].QteDej2,
                quantites[j].QteDiner1, quantites[j].QteDiner2);
    }

    fclose(fichier);
}
void Menu_Manager() {
    int choix;
    printf("\n\n\t\t\t\t\t\t\t--------------\n");
    printf("\t\t\t\t\t\t\t1.MENU Manager \n");
    printf("\t\t\t\t\t\t\t--------------\n\n\n\n\n");
    printf("\t\t\t1. Remplir le menu\t\t\t\t");
    printf("2. Modifier le menu pour un jour specifique\n\n");
    printf("\t\t\t3. Afficher les statistiques \t\t");

    printf("\t4.Afficher Menu \n\n\n\n\n\n");
    printf("\t\t\t\t\t\t\t0.Quitter \n");

    // Demander à l'utilisateur de faire un choix
        printf("Faites votre choix (0, 1 ,2 ou 3) : ");
        scanf("%d", &choix);
}
void afficher_menu() {
    FILE *fichierMenu;
    Jour jour;
    char jourRecherche[100];

    // Ouvrir le fichier en mode lecture ("r")
    fichierMenu = fopen("menu.txt", "r");

    // Vérifier si le fichier est ouvert avec succès
    if (fichierMenu == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    // Demander à l'utilisateur de saisir le jour à afficher
    printf("Entrez le nom du jour dont vous voulez afficher le menu : ");
    scanf("%s", jourRecherche);

    // Convertir le nom du jour en minuscules (ignorer la casse)
    strncpy(jourRecherche, strlwr(jourRecherche), sizeof(jourRecherche));

    // Rechercher le jour dans le fichier
    while (fscanf(fichierMenu, "%s %s %s %s %s %s %s",
                  jour.nomJour, jour.platPetitDejeuner1, jour.platPetitDejeuner2,
                  jour.platDejeuner1, jour.platDejeuner2, jour.platDinner1, jour.platDinner2) != EOF) {
        // Convertir le nom du jour dans le fichier en minuscules (ignorer la casse)
        if (strcasecmp(jour.nomJour, jourRecherche) == 0) {
            // Jour trouvé, afficher le menu
            printf("\nMenu pour le jour %s :\n", jourRecherche);
            printf("Petit Déjeuner 1: %s\n", jour.platPetitDejeuner1);
            printf("Petit Déjeuner 2: %s\n", jour.platPetitDejeuner2);
            printf("Déjeuner 1: %s\n", jour.platDejeuner1);
            printf("Déjeuner 2: %s\n", jour.platDejeuner2);
            printf("Dîner 1: %s\n", jour.platDinner1);
            printf("Dîner 2: %s\n", jour.platDinner2);

            // Fermer le fichier
            fclose(fichierMenu);
            return;
        }
    }

    // Si le jour n'est pas trouvé, afficher un message approprié
    printf("Jour non trouvé dans le menu.\n");

    // Fermer le fichier
    fclose(fichierMenu);
}

void jutos() {
    int choix;

    while (1) {
        // Demander à l'utilisateur de faire un choix à l'intérieur de la boucle
        printf("\n\n\t\t\t\t\t\t\t--------------\n");
        printf("\t\t\t\t\t\t\t1.MENU Manager \n");
        printf("\t\t\t\t\t\t\t--------------\n\n\n\n\n");
        printf("\t\t\t1. Remplir le menu\t\t\t\t");
        printf("2. Modifier le menu pour un jour specifique\n\n");
        printf("\t\t\t3. Afficher les statistiques \t\t");
        printf("\t4.Afficher menu\n\n");
        printf("\t\t\t\t\t\t\t0.Quitter \n\n\n\n");

        printf("\t\t\t\t\tFaites votre choix (0, 1 ,2,3 ou 4) : ");
        scanf("%d", &choix);

        // Traiter le choix de l'utilisateur
        switch (choix) {
            case 1:
                remplirMenu();
                break;
            case 2:
                modifierMenu();
                break;
            case 3:
                afficherStats();
                break;
            case 4:
                afficher_menu();
                break;
            case 0:
                printf("Au revoir !\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                return;
            default:
                printf("Choix invalide.\n");
                break;
        }
    }
}



void suparo() {
    FILE *P;
    P = fopen("liste_etudiant.txt", "r+");

    if (P == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
        return;
    }

    int matricule;
    float VAsolde;

    // Saisie du matricule
    printf("Saisir le matricule de l'etudiant : ");
    scanf("%d", &matricule);

    // Saisie de la solde à ajouter
    printf("Saisir la solde a ajouter : ");
    scanf("%f", &VAsolde);

    Etudiant etudiants[1500];  // Supposons qu'il y a au plus 100 étudiants dans le fichier
    int nombreEtudiants = 0;

    // Lire tous les étudiants du fichier et stocker en mémoire
    while (fscanf(P, "%s %s %s %s %d",
                  etudiants[nombreEtudiants].Mat, etudiants[nombreEtudiants].NP,
                  etudiants[nombreEtudiants].Gn, etudiants[nombreEtudiants].Mdp,
                  &etudiants[nombreEtudiants].solde) != EOF) {
        nombreEtudiants++;
    }

    // Rechercher l'étudiant dans la mémoire
    int i;
    for (i = 0; i < nombreEtudiants; i++) {
        int matriculeInt = atoi(etudiants[i].Mat);

        if (matriculeInt == matricule) {
            // Incrémenter la solde de l'étudiant
            etudiants[i].solde += VAsolde;

            // Retourner au début du fichier pour écrire les modifications
            rewind(P);

            // Écrire toutes les entrées modifiées dans le fichier
            for (int j = 0; j < nombreEtudiants; j++) {
                fprintf(P, "%s %s %s %s %d\n",
                        etudiants[j].Mat, etudiants[j].NP, etudiants[j].Gn,
                        etudiants[j].Mdp, etudiants[j].solde);
            }

            // Tronquer le fichier pour supprimer les anciennes données excédentaires
            ftruncate(fileno(P), ftell(P));

            printf("Solde mis à jour avec succès pour le matricule %d.\n", matricule);
            break;
        }
    }

    // Si l'étudiant n'est pas trouvé, afficher un message approprié
    if (i == nombreEtudiants) {
        printf("Étudiant non trouvé dans la liste.\n");
    }

    // Fermer le fichier
    fclose(P);
}




void annulerReservation(int matricule) {
    char jourRecherche[10];
    printf("Entrez le jour de la réservation à annuler : ");
    scanf("%s", jourRecherche);

    FILE *fichierEtudiants = fopen("liste_etudiant.txt", "r");
    if (fichierEtudiants == NULL) {
        printf("Impossible d'ouvrir le fichier liste_etudiant.txt.\n");
        return;
    }

    // Calculer le nombre d'étudiants dans le fichier
    int nbEtudiants = 0;
    while (fscanf(fichierEtudiants, "%*s %*s %*s %*s %*d") != EOF) {
        nbEtudiants++;
    }

    fclose(fichierEtudiants);

    FILE *fichierTickets = fopen("tickets.txt", "r");
    if (fichierTickets == NULL) {
        printf("Impossible d'ouvrir le fichier tickets.txt.\n");
        return;
    }

    Reservation reservations[100];
    int nbReservations = 0;
    while (fscanf(fichierTickets, "%s %s %d %d %d %d %d %d",
                  reservations[nbReservations].Mat, reservations[nbReservations].nomJour,
                  &reservations[nbReservations].QtepetDej1, &reservations[nbReservations].QtepetDej2,
                  &reservations[nbReservations].QteDej1, &reservations[nbReservations].QteDej2,
                  &reservations[nbReservations].QteDiner1, &reservations[nbReservations].QteDiner2) != EOF) {
        nbReservations++;
    }

    fclose(fichierTickets);

    FILE *fichierStats = fopen("stats.txt", "r+");
    if (fichierStats == NULL) {
        printf("Impossible d'ouvrir le fichier stats.txt.\n");
        return;
    }

    Quantite quantites[100];
    int nbJours = 0;
    while (fscanf(fichierStats, "%s %d %d %d %d %d %d",
                  quantites[nbJours].Day, &quantites[nbJours].QtepetDej1, &quantites[nbJours].QtepetDej2,
                  &quantites[nbJours].QteDej1, &quantites[nbJours].QteDej2,
                  &quantites[nbJours].QteDiner1, &quantites[nbJours].QteDiner2) != EOF) {
        nbJours++;
    }

    int reservationTrouvee = 0;
    for (int i = 0; i < nbReservations; i++) {
        if (atoi(reservations[i].Mat) == matricule && strcmp(reservations[i].nomJour, jourRecherche) == 0) {
            float prixTotal = (reservations[i].QtepetDej1 + reservations[i].QtepetDej2 +
                               reservations[i].QteDej1 + reservations[i].QteDej2 +
                               reservations[i].QteDiner1 + reservations[i].QteDiner2) * 2;

            FILE *fichEtudiant = fopen("liste_etudiant.txt", "r+");
            if (fichEtudiant != NULL) {
                Etudiant etudiant;
                long int position = 0;

                for (int k = 0; k < nbEtudiants; k++) {
                    if (fscanf(fichEtudiant, "%s %s %s %s %d", etudiant.Mat, etudiant.NP, etudiant.Gn, etudiant.Mdp, &etudiant.solde) != EOF) {
                        if (atoi(etudiant.Mat) == matricule) {
                            fseek(fichEtudiant, position, SEEK_SET);
                            int l=etudiant.solde + (int)prixTotal;
                            fprintf(fichEtudiant, "\n%s %s %s %s %d\n", etudiant.Mat, etudiant.NP, etudiant.Gn, etudiant.Mdp, l);

                            break;
                        }

                        position = ftell(fichEtudiant);
                    }
                }

                fclose(fichEtudiant);
            }

            for (int j = 0; j < nbJours; j++) {
                if (strcmp(quantites[j].Day, jourRecherche) == 0) {
                    quantites[j].QtepetDej1 -= reservations[i].QtepetDej1;
                    quantites[j].QtepetDej2 -= reservations[i].QtepetDej2;
                    quantites[j].QteDej1 -= reservations[i].QteDej1;
                    quantites[j].QteDej2 -= reservations[i].QteDej2;
                    quantites[j].QteDiner1 -= reservations[i].QteDiner1;
                    quantites[j].QteDiner2 -= reservations[i].QteDiner2;
                    break;
                }
            }

            for (int k = i; k < nbReservations - 1; k++) {
                reservations[k] = reservations[k + 1];
            }
            nbReservations--;

            reservationTrouvee = 1;
            break;
        }
    }

    fclose(fichierStats);

    fichierStats = fopen("stats.txt", "w");
    for (int i = 0; i < nbJours; i++) {
        fprintf(fichierStats, "%s %d %d %d %d %d %d\n",
                quantites[i].Day, quantites[i].QtepetDej1, quantites[i].QtepetDej2,
                quantites[i].QteDej1, quantites[i].QteDej2,
                quantites[i].QteDiner1, quantites[i].QteDiner2);
    }
    fclose(fichierStats);

    fichierTickets = fopen("tickets.txt", "w");
    for (int i = 0; i < nbReservations; i++) {
        fprintf(fichierTickets, "%s %s %d %d %d %d %d %d\n",
                reservations[i].Mat, reservations[i].nomJour,
                reservations[i].QtepetDej1, reservations[i].QtepetDej2,
                reservations[i].QteDej1, reservations[i].QteDej2,
                reservations[i].QteDiner1, reservations[i].QteDiner2);
    }
    fclose(fichierTickets);

    if (reservationTrouvee) {
        printf("Réservation annulée avec succès.\n");
    } else {
        printf("Aucune réservation trouvée pour cet étudiant et ce jour.\n");
    }
}
