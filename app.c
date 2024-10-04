#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXC   20
#define MAXRES 100
#define CLEAR  "cls"

typedef struct dat{   
    int jour;
    int mois;
    int annee;
} d;


typedef struct reservation{
    char nom[MAXC];
    char prenom[MAXC];
    char telephone[MAXC];
    int  age;
    char statut[MAXC];
    int  id;
    d date;
}RES;
int n =0 ;
int ID = 0;

RES reservations[MAXRES];

void toLowerCase(char tolwr[]) {
    for (int i = 0; tolwr[i] != '\0'; i++) {
        tolwr[i] = tolower((unsigned char)tolwr[i]);
    }
}

int validerTelephone(char tel[]) {
    if (strlen(tel) != 10) {
    return 0;
     }
    for (int i = 0; i < 10; i++) {
        if (!isdigit(tel[i]))
         return 0; 
    }
    return 1;
}

void ajouterReservation(){
    int choix;

    if (n >= MAXRES) {
        printf("Le repertoire de rendez vous est plein !\n");
        return;
    }

        printf("Nom du client : ");
        fgets(reservations[n].nom, sizeof(reservations[n].nom), stdin);
        reservations[n].nom[strcspn(reservations[n].nom, "\n")] = 0;
        toLowerCase(reservations[n].nom);

     printf("Prenom du client : ");
    fgets(reservations[n].prenom, sizeof(reservations[n].prenom), stdin);
    reservations[n].prenom[strcspn(reservations[n].prenom, "\n")] = 0;
    toLowerCase(reservations[n].prenom);

     do {
        printf("Telephone du client (10 chiffres) : ");
        fgets(reservations[n].telephone, sizeof(reservations[n].telephone), stdin);
        reservations[n].telephone[strcspn(reservations[n].telephone, "\n")] = 0;
    } while (!validerTelephone(reservations[n].telephone));

    printf("l' age de client :");
    scanf("%d",&reservations[n].age);
    getchar();

    printf("Choisissez le statut du rendez-vous :\n");
    printf("1. valide\n");
    printf("2. reporte\n");
    printf("3. annule\n");
    printf("4. traite\n");

    do {
        printf("Entrez votre choix (1-4) : ");
        scanf("%d", &choix);
        getchar();

        switch (choix) {
            case 1:
                strcpy(reservations[n].statut, "valide");
                break;
            case 2:
                strcpy(reservations[n].statut, "reporte");
                break;
            case 3:
                strcpy(reservations[n].statut, "annule");
                break;
            case 4:
                strcpy(reservations[n].statut, "traite");
                break;
            default:
                printf("Choix invalide. Veuillez entrer un nombre entre 1 et 4.\n");
                break;
        }
    } while (choix < 1 || choix > 4);

    printf("Entrez la date du redez vous (Jour/Mois/annee) : ");
    scanf("%d/%d/%d", &reservations[n].date.jour, &reservations[n].date.mois, &reservations[n].date.annee);
    while ( (reservations[n].date.mois <= 0 || reservations[n].date.mois > 12) || (reservations[n].date.jour <= 0 || reservations[n].date.jour > 31) || reservations[n].date.annee <= 0 )
    {
    
    if ( reservations[n].date.jour <= 0 || reservations[n].date.jour >= 32){
        printf("Entrez un nombre entre 1 et 31 pour les jour\n");
    } else if (reservations[n].date.mois <= 0 || reservations[n].date.mois >= 13){
        printf("ENTRER un nombre entre 1 et 12 pour les mois\n");
    } else if ( reservations[n].date.annee < 2024 ){
        printf("On est en 2024!!\n");
    } 
    scanf("%d/%d/%d", &reservations[n].date.jour, &reservations[n].date.mois, &reservations[n].date.annee);
    
    }
    reservations[n].id = ++ID;
    n++;
    printf("Rendez vous ajoute avec succes.\n");
    
}

void afficherReservation(){

    if (n == 0) {  
    printf("Le repertoire de rendez vous est vide.\n");
    return ;
    }

    printf("| %-5s | %-10s | %-10s | %-12s | %-3s | %-8s | %-10s |\n", "ID", "Nom", "Prenom", "Telephone", "Age", "Statut", "Date");
    printf("|-------|------------|------------|--------------|-----|----------|------------|\n");
    for ( int i = 0; i < n; i++)
    {
    printf("| %-5d | %-10s | %-10s | %-12s | %-3d | %-8s | %02d/%02d/%d |\n",   reservations[i].id, reservations[i].nom,
                                                                                reservations[i].prenom,reservations[i].telephone,
                                                                                reservations[i].age, reservations[i].statut,
                                                                                reservations[i].date.jour, reservations[i].date.mois,
                                                                                reservations[i].date.annee);         
    }
       
}

void rechercherParNom() {

    if (n == 0) {  
        printf("Le repertoire de rendez vous est vide.\n");
        return ;
    }

    char nomRecherche[MAXC];
    
    printf("Entrez le nom du client : ");
    
    fgets(nomRecherche, sizeof(nomRecherche), stdin);
    nomRecherche[strcspn(nomRecherche, "\n")] = 0;
    
    int indices[MAXRES];
    int nbrTRV = 0;

    printf("| %-5s | %-10s | %-10s | %-12s | %-3s | %-8s | %-10s |\n", "ID", "Nom", "Prenom", "Telephone", "Age", "Statut", "Date");
    printf("|-------|------------|------------|--------------|-----|----------|------------|\n");

    
    for (int i = 0; i < n; i++) {
        if (strcmp(reservations[i].nom, nomRecherche) == 0) {
            
            printf("| %-5d | %-10s | %-10s | %-12s | %-3d | %-8s | %02d/%02d/%d |\n", reservations[i].id, reservations[i].nom,
                                                                                          reservations[i].prenom,reservations[i].telephone,
                                                                                          reservations[i].age, reservations[i].statut,
                                                                                          reservations[i].date.jour, reservations[i].date.mois,
                                                                                          reservations[i].date.annee);
            indices[nbrTRV] = i;  
            nbrTRV++;
        }
    }
    printf("|-------|------------|------------|--------------|-----|----------|------------|\n");
    if (nbrTRV > 1) {
        int idChoisi;
        printf("\nIl y a plusieurs reservations avec ce nom. Entrez l'ID de la reservation a selectionner : ");
        scanf("%d", &idChoisi);
       

        for (int i = 0 ; i < nbrTRV; i++) {
            if (reservations[i].id == idChoisi) {
                printf("| %-5s | %-10s | %-10s | %-12s | %-3s | %-8s | %-10s |\n", "ID", "Nom", "Prenom", "Telephone", "Age", "Statut", "Date");
                printf("|-------|------------|------------|--------------|-----|----------|------------|\n");
                printf("| %-5d | %-10s | %-10s | %-12s | %-3d | %-8s | %02d/%02d/%d |\n", reservations[i].id, reservations[i].nom,
                                                                                          reservations[i].prenom,reservations[i].telephone,
                                                                                          reservations[i].age, reservations[i].statut,
                                                                                          reservations[i].date.jour, reservations[i].date.mois,
                                                                                          reservations[i].date.annee);
                printf("|-------|------------|------------|--------------|-----|----------|------------|\n");                                                                      
            }
        }

        printf("--------\nAucune reservation trouve avec l'ID %d.\n--------\n", idChoisi);
        return ;  
    }

    
}


void rechercherParID() {

    if (n == 0) {  
        printf("Le repertoire de rendez vous est vide.\n");
        return ;
    }

    int idRecherche;
    printf("Entrez l'ID de la reservation a rechercher : ");
    scanf("%d", &idRecherche);
    for (int i = 0 ; i < n; i++) {
            if (reservations[i].id == idRecherche) {
                printf("| %-5s | %-10s | %-10s | %-12s | %-3s | %-8s | %-10s |\n", "ID", "Nom", "Prenom", "Telephone", "Age", "Statut", "Date");
                printf("|-------|------------|------------|--------------|-----|----------|------------|\n");
                printf("| %-5d | %-10s | %-10s | %-12s | %-3d | %-8s | %02d/%02d/%d |\n", reservations[i].id, reservations[i].nom,
                                                                                          reservations[i].prenom,reservations[i].telephone,
                                                                                          reservations[i].age, reservations[i].statut,
                                                                                          reservations[i].date.jour, reservations[i].date.mois,
                                                                                          reservations[i].date.annee);
                printf("|-------|------------|------------|--------------|-----|----------|------------|\n");                                                                      
                return ;
            }
        }
        printf("--------\nAucune reservation trouve avec l'ID %d.\n--------\n", idRecherche);
}

void supprimerReservation() {

    if (n == 0) {  
        printf("Le repertoire de rendez vous est vide.\n");
        return ;
    }

    int idRecherche;
    printf("Entrez l'ID de la reservation a supprimer : ");
    scanf("%d", &idRecherche);

    int resTRV = 0;  

    for (int i = 0; i < n; i++) {
        if (reservations[i].id == idRecherche) {
            resTRV = 1; 
            
            for (int j = i; j < n - 1; j++) {
                reservations[j] = reservations[j + 1];
            }
            n--;  
            printf("Reservation avec ID %d supprimee avec succes.\n", idRecherche);
            break; 
        }
    }

    if (!resTRV) {
        printf("--------\nAucune reservation trouve avec l'ID %d.\n--------\n", idRecherche);
    }
}

void modifierReservation() {

    int id, choix3;

    printf("Entrez l'ID de la reservation a modifier : ");
    scanf("%d", &id);
    getchar();

    // Recherche de la réservation par ID
    int index = -1;
    for (int i = 0; i < n; i++) {
        if (reservations[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Aucune reservation trouvee avec cet ID.\n");
        return;
    }

    
    printf("Nom du client (actuel : %s) : ", reservations[index].nom);
    fgets(reservations[index].nom, sizeof(reservations[index].nom), stdin);
    reservations[index].nom[strcspn(reservations[index].nom, "\n")] = 0;
    toLowerCase(reservations[index].nom);

    

    printf("Prenom du client (actuel : %s) : ", reservations[index].prenom);
    fgets(reservations[index].prenom, sizeof(reservations[index].prenom), stdin);
    reservations[index].prenom[strcspn(reservations[index].prenom, "\n")] = 0;
    toLowerCase(reservations[index].prenom);
    
     do {
        printf("Telephone du client (actuel : %s) 10 chiffres : ", reservations[index].telephone);
        fgets(reservations[index].telephone, sizeof(reservations[index].telephone), stdin);
        reservations[index].telephone[strcspn(reservations[index].telephone, "\n")] = 0;
    } while (!validerTelephone(reservations[n].telephone));

    printf("Telephone du client (actuel : %s) : ", reservations[index].telephone);
    fgets(reservations[index].telephone, sizeof(reservations[index].telephone), stdin);
    reservations[index].telephone[strcspn(reservations[index].telephone, "\n")] = 0;

    printf("L'age du client (actuel : %d) : ", reservations[index].age);
    getchar();

    
    printf("Choisissez le statut du rendez-vous (actuel : %s) :\n", reservations[index].statut);
    printf("1. valide\n");
    printf("2. reporte\n");
    printf("3. annule\n");
    printf("4. traite\n");

    do {
        printf("Entrez votre choix (1-4) : ");
        scanf("%d", &choix3);
        getchar();

        switch (choix3) {
            case 1:
                strcpy(reservations[index].statut, "valide");
                break;
            case 2:
                strcpy(reservations[index].statut, "reporte");
                break;
            case 3:
                strcpy(reservations[index].statut, "annule");
                break;
            case 4:
                strcpy(reservations[index].statut, "traite");
                break;
            default:
                printf("Choix invalide. Veuillez entrer un nombre entre 1 et 4.\n");
                break;
        }
    } while (choix3 < 1 || choix3 > 4);

    
    printf("Entrez la date du rendez-vous (actuelle : %02d/%02d/%d) : ", 
           reservations[index].date.jour, 
           reservations[index].date.mois, 
           reservations[index].date.annee);
    scanf("%d/%d/%d", &reservations[index].date.jour, &reservations[index].date.mois, &reservations[index].date.annee);

    
    while ((reservations[index].date.mois <= 0 || reservations[index].date.mois > 12) || 
           (reservations[index].date.jour <= 0 || reservations[index].date.jour > 31) || 
           reservations[index].date.annee < 2024) 
    {
        if (reservations[index].date.jour <= 0 || reservations[index].date.jour >= 32) {
            printf("Entrez un nombre entre 1 et 31 pour les jours.\n");
        } else if (reservations[index].date.mois <= 0 || reservations[index].date.mois >= 13) {
            printf("Entrez un nombre entre 1 et 12 pour les mois.\n");
        } else if (reservations[index].date.annee < 2024) {
            printf("L'année doit être 2024 ou plus.\n");
        } 
        printf("Entrez la date du rendez-vous (Jour/Mois/Annee) : ");
        scanf("%d/%d/%d", &reservations[index].date.jour, 
              &reservations[index].date.mois, 
              &reservations[index].date.annee);
    }

    printf("Reservation modifiee avec succes.\n");
}


void triParNom() {
    for(int i = 0 ;i < n - 1;i++){
          for(int j = i + 1; j < n  ; j++){
                if (strcmp(reservations[i].nom, reservations[j].nom) > 0){

                RES temp = reservations[i]; 
                reservations[i] = reservations[j];
                reservations[j] = temp;
                
            }
            }
        }
        printf("trie par nom effectuer.");
}
    


int ordreStatut(char statut[MAXC]) {
    if (strcmp(statut, "valide") == 0) return 1;
    if (strcmp(statut, "reporte") == 0) return 2;
    if (strcmp(statut, "annule") == 0) return 3;
    if (strcmp(statut, "traite") == 0) return 4;
    return 5;
}
void triParStatut() {

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {

            if (ordreStatut(reservations[i].statut) > ordreStatut(reservations[j].statut)) {
                RES temp = reservations[i]; 
                reservations[i] = reservations[j];
                reservations[j] = temp;
            }
        }
    }
    printf("Tri par statut effectue.\n");
}


void afficherToutesStatistiques() {
    if (n == 0) {
        printf("Aucune reservation enregistree.\n");
        return;
    }

   
    int sommeAg = 0;
    for (int i = 0; i < n; i++) {
        sommeAg += reservations[i].age;
    }
    double moyenneAg = (double)sommeAg / n;
    printf("Moyenne d'age des patients : %.2f ans\n", moyenneAg);

    
    int tr1 = 0, tr2 = 0, tr3 = 0;
    for (int i = 0; i < n; i++) {
        if (reservations[i].age <= 18) {
            tr1++;
        } else if (reservations[i].age <= 35) {
            tr2++;
        } else {
            tr3++;
        }
    }
    printf("Nombre de patients par tranche d'age :\n");
    printf("0-18 ans  : %d\n", tr1);
    printf("19-35 ans : %d\n", tr2);
    printf("36+ ans   : %d\n", tr3);

    
    int valide = 0, annule = 0, reporte = 0, traite = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(reservations[i].statut, "valide") == 0) {
            valide++;
        } else if (strcmp(reservations[i].statut, "annule") == 0) {
            annule++;
        } else if (strcmp(reservations[i].statut, "reporte") == 0) {
            reporte++;
        } else if (strcmp(reservations[i].statut, "traite") == 0) {
            traite++;
        }
    }
    printf("Statistiques des reservations par statut :\n");
    printf("Valide  : %d\n", valide);
    printf("Annule  : %d\n", annule);
    printf("Reporte : %d\n", reporte);
    printf("Traite  : %d\n", traite);
}


void randReservations() {
    
    RES tempReservations[12] = {
        {"Ahmed", "Ali", "0123456789", 30, "valide", 0, {15, 11, 2024}},
        {"Fatima", "Mohamed", "0676543210", 25, "reporte", 0, {20, 11, 2024}},
        {"Ahmed", "El-Hajj", "0776655443", 45, "annule", 0, {1, 12, 2024}},
        {"Omar", "Salah", "0555678901", 35, "traite", 0, {30, 12, 2024}},
        {"Samira", "Mounir", "0523456789", 33, "traite", 0, {30, 12, 2024}},
        {"Ilyas", "Dahmani", "0745678901", 29, "valide", 0, {5, 12, 2024}},
        {"Leila", "Bensalem", "0789101112", 28, "valide", 0, {5, 12, 2024}},
        {"Zohra", "Chakir", "0661122334", 35, "valide", 0, {10, 12, 2024}},
        {"Ahmed", "Touhami", "0756677889", 40, "reporte", 0, {22, 12, 2024}},
        {"Salma", "Rifi", "0623456789", 25, "annule", 0, {8, 1, 2025}},
        {"Tariq", "El-Ouafi", "0789123456", 38, "traite", 0, {12, 1, 2025}},
        {"Imane", "Bouabid", "0712345678", 31, "valide", 0, {25, 1, 2025}}
    };

    
    for (int i = 0; i < 12; i++) {
        reservations[n + i] = tempReservations[i];
        reservations[n + i].id = ++ID;
        toLowerCase(reservations[n + i].nom);
        toLowerCase(reservations[n + i].prenom);
    }
    n += 12; 
}

int main() {
    
    
    int choix, choix2;
    
    
    randReservations();
    
    printf("\n-- Systeme de Gestion de rendez-vous dentaires -- \n");

    do{ 
         do
        {
            printf("\n1. Ajouter un rendez-vou.\n");
            printf("2. Afficher tous les rendez-vous.\n");
            printf("3. Rechercher un rendez-vous.\n");
            printf("4. Modifier un rendez-vous.\n");
            printf("5. Supprimer un rendez-vous.\n");
            printf("6. Trier les rendez-vous.\n");
            printf("7. Statistiques .\n");
            printf("0. Quitter\n");
            printf("Choisissez une option : ");
            scanf("%d", &choix);
            getchar();
            system(CLEAR);

            if (choix > 5 || choix < 0){
                printf("-choix invalide \n");
            }
        } while (choix > 8 || choix < 0);
       
            switch (choix)
            {
            case 1:
                ajouterReservation();
            
                break;
            case 2:
                afficherReservation();
                break;
            case 3:
                system(CLEAR);
                printf("1. Recherche d'une reservation par nom.\n");
                printf("2. Recherche d'une reservation par reference unique.\n");
                printf("0. Retour.\n");
                scanf("%d", &choix2);
                getchar();
                
                switch (choix2){  
                    case 1:
                        rechercherParNom();
                        break;
                    case 2:
                        rechercherParID();
                        break;
                    case 0:
                        break;
                }
                break;
            case 4:
                modifierReservation();
                break;
            case 5:
                supprimerReservation();
                break;
            case 6:
                system(CLEAR);
                printf("1. Trier par nom.\n");
                printf("2. Trier par statut.\n");
                printf("0. Retour.\n");
                scanf("%d", &choix2);
                
                switch (choix2){  
                    case 1:
                        triParNom();
                        afficherReservation();
                        break;
                    case 2:
                        triParStatut();
                        afficherReservation();
                        break;
                    case 0:
                        break;
                }
                break;
            case 7:
                afficherToutesStatistiques();
                break;
            

            case 0:
                break;
    
            default:
            printf("-choix invalide \n");
            
            }

        } while (choix != 0);

        

    return 0;

}



