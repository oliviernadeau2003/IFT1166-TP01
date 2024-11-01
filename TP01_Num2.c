// Olivier Nadeau - 20316525

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// --- --- --- --- --- --- --- --- ---
// --- NUMÉRO 02 ---

const int MAX_EMPLOYE = 30;
const char NOM_FICHIER[] = "Employes.dat\0";

struct Employe
{
    char nom[25];
    char poste;
    float nbHeures, tauxHoraire;
};

// Fonction pour lire le fichier et mémoriser les données dans un tableau de structures
int lireFichier(struct Employe employes[], const char *nomFichier)
{
    FILE *fichier = fopen(nomFichier, "r");
    char ligne[100]; // Buffer pour lire chaque ligne du fichier
    int nombreEmployes = 0;

    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return -1;
    }

    // Lecture ligne par ligne
    while (fgets(ligne, sizeof(ligne), fichier) && nombreEmployes < MAX_EMPLOYE)
    {
        // Utilisation de strtok pour découper la ligne par points-virgules
        char *nom = strtok(ligne, ";");
        char *poste = strtok(NULL, ";");
        char *nbHeures = strtok(NULL, ";");
        char *tauxHoraire = strtok(NULL, ";");

        if (nom && poste && nbHeures && tauxHoraire)
        {
            // Remplir les champs de la structure Employe
            strncpy(employes[nombreEmployes].nom, nom, 24);
            employes[nombreEmployes].nom[24] = '\0';                  // Assurer la terminaison de la chaîne
            employes[nombreEmployes].poste = poste[0];                // Prend le premier caractère
            employes[nombreEmployes].nbHeures = atof(nbHeures);       // Convertir en float
            employes[nombreEmployes].tauxHoraire = atof(tauxHoraire); // Convertir en float
            nombreEmployes++;
        }
    }

    fclose(fichier);
    return nombreEmployes; // Retourner le nombre d'employés lus
}

void compterEtAfficher(struct Employe employes[], int nombreEmployes, char posteRecherche, float heuresMin)
{
    int compteur = 0;

    for (int i = 0; i < nombreEmployes; i++)
    {
        // Vérifier si le poste correspond et si le nombre d'heures est supérieur au minimum requis
        if (employes[i].poste == posteRecherche && employes[i].nbHeures > heuresMin)
        {
            compteur++;
        }
    }

    // Affichage du résultat selon le poste recherché
    switch (posteRecherche)
    {
    case 'P':
        printf("Nombre de programmeurs travaillant plus de %.2f heures/semaine : %d\n", heuresMin, compteur);
        break;
    case 'O':
        printf("Nombre d'opérateurs travaillant plus de %.2f heures/semaine : %d\n", heuresMin, compteur);
        break;
    case 'A':
        printf("Nombre de secrétaires travaillant plus de %.2f heures/semaine : %d\n", heuresMin, compteur);
        break;
    default:
        printf("Poste inconnu.\n");
    }
}

void afficherSalaireHebdo(struct Employe employes[], int nombreEmployes, char poste)
{
    printf("\n--- Salaires hebdomadaires des %s ---\n",
           poste == 'P' ? "programmeurs" : poste == 'O' ? "opérateurs"
                                       : poste == 'A'   ? "secrétaires"
                                                        : "employés");

    for (int i = 0; i < nombreEmployes; i++)
    {
        // Vérifie si le poste correspond
        if (employes[i].poste == poste)
        {
            // Calcule le salaire hebdomadaire
            float salaireHebdo = employes[i].nbHeures * employes[i].tauxHoraire;
            printf("Nom : %s, Salaire hebdomadaire : %.2f\n", employes[i].nom, salaireHebdo);
        }
    }
}

// Fonction pour comparer deux noms (utilisée pour la recherche dichotomique)
int comparerNoms(const char *nom1, const char *nom2)
{
    return strcmp(nom1, nom2);
}

// Function to convert a string to lowercase and return it
char *toLowerCase(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        str[i] = tolower((unsigned char)str[i]); // Convert each character to lowercase
    }
    return str; // Return the modified string
}

// Fonction de recherche dichotomique
int rechercheDichotomique(struct Employe employes[], int nombreEmployes, char *nomRecherche)
{
    int debut = 0;
    int fin = nombreEmployes - 1;

    while (debut <= fin)
    {
        int milieu = (debut + fin) / 2;

        // Utiliser la fonction de comparaison
        char *lowerNomEmploye = toLowerCase(employes[milieu].nom);
        char *lowerNomRecherche = toLowerCase(nomRecherche);
        int comparaison = comparerNoms(lowerNomEmploye, lowerNomRecherche);

        if (comparaison == 0)
        {
            return milieu; // Retourne l'index de l'employé trouvé
        }
        else if (comparaison < 0)
        {
            debut = milieu + 1;
        }
        else
        {
            fin = milieu - 1;
        }
    }

    return -1;
}

// Fonction pour rechercher un employé par son nom
void rechercherParNom(struct Employe employes[], int nombreEmployes)
{
    char nomRecherche[25];

    printf("Entrez le nom de l'employé à rechercher : ");
    scanf(" %[^\n]", nomRecherche); // Lecture du nom (avec espaces)

    // Recherche dichotomique
    int index = rechercheDichotomique(employes, nombreEmployes, nomRecherche);

    if (index != -1)
    {
        printf("\nEmployé trouvé : %s, Poste : %c\n", employes[index].nom, employes[index].poste);
    }
    else
    {
        printf("\nL'employé \"%s\" n'a pas été trouvé.\n", nomRecherche);
    }
}

// Fonction pour trier les employés par ordre alphabétique (Bubble Sort)
void trierEmployesParNom(struct Employe employes[], int nombreEmployes)
{
    for (int i = 0; i < nombreEmployes - 1; i++)
    {
        for (int j = 0; j < nombreEmployes - i - 1; j++)
        {
            // Comparer les noms de deux employés
            if (strcmp(employes[j].nom, employes[j + 1].nom) > 0)
            {
                // Échanger les employés si nécessaire
                struct Employe temp = employes[j];
                employes[j] = employes[j + 1];
                employes[j + 1] = temp;
            }
        }
    }
}

// --- Fonction pour afficher le menu et obtenir le choix de l'utilisateur ---
char afficherMenu()
{
    printf("\n====== Menu ======\n");
    printf("1. Afficher le nombre de programmeurs qui travaillent plus de 45 heures / semaine\n");
    printf("2. Afficher le nombre d'opérateurs qui travaillent plus de 40.50 heures / semaine\n");
    printf("3. Afficher le nombre de secrétaires qui travaillent plus de 35.00 heures / semaine\n");
    printf("4. Afficher les noms et les salaires hebdomadaires des opérateurs\n");
    printf("5. Afficher les noms et les salaires hebdomadaires des programmeurs\n");
    printf("6. Rechercher un employé par son nom\n");
    printf("0. Quitter\n");
    printf("\nVeuillez entrer votre choix : ");

    char choix;
    scanf(" %c", &choix); // Prend l'entrée de l'utilisateur et la retourne
    printf("==================\n\n");
    return choix;
}

void afficherNumeroB()
{
    struct Employe employes[MAX_EMPLOYE];

    int nombreEmployes = lireFichier(employes, NOM_FICHIER);

    // Trier les employés par nom
    trierEmployesParNom(employes, nombreEmployes);

    if (nombreEmployes > 0)
    {
        printf("Nombre total d'employés traités : %d\n", nombreEmployes);
    }

    char choix = afficherMenu();
    while (choix != '0')
    {
        switch (choix)
        {
        case '1':
            compterEtAfficher(employes, nombreEmployes, 'P', 45.0); // Pour les programmeurs
            break;
        case '2':
            compterEtAfficher(employes, nombreEmployes, 'O', 40.50); // Pour les opérateurs
            break;
        case '3':
            compterEtAfficher(employes, nombreEmployes, 'A', 35.0); // Pour les secrétaires
            break;
        case '4':
            afficherSalaireHebdo(employes, nombreEmployes, 'O'); // Pour les opérateurs
            break;
        case '5':
            afficherSalaireHebdo(employes, nombreEmployes, 'P'); // Pour les programmeurs
            break;
        case '6':
            rechercherParNom(employes, nombreEmployes);
            break;
        case '0':
            printf("Quitter le programme.\n");
            break;
        default:
            printf("Choix invalide. Veuillez réessayer.\n");
        }
        choix = afficherMenu();
    }
}

// --- --- --- --- --- --- --- --- ---
// --- MAIN ---
int main()
{
    afficherNumeroB();
    return 0;
}

/*

Nombre total d'employés traités : 16

====== Menu ======
1. Afficher le nombre de programmeurs qui travaillent plus de 45 heures / semaine
2. Afficher le nombre d'opérateurs qui travaillent plus de 40.50 heures / semaine
3. Afficher le nombre de secrétaires qui travaillent plus de 35.00 heures / semaine
4. Afficher les noms et les salaires hebdomadaires des opérateurs
5. Afficher les noms et les salaires hebdomadaires des programmeurs
6. Rechercher un employé par son nom
0. Quitter

Veuillez entrer votre choix : 1
==================

Nombre de programmeurs travaillant plus de 45.00 heures/semaine : 0

====== Menu ======
1. Afficher le nombre de programmeurs qui travaillent plus de 45 heures / semaine
2. Afficher le nombre d'opérateurs qui travaillent plus de 40.50 heures / semaine
3. Afficher le nombre de secrétaires qui travaillent plus de 35.00 heures / semaine
4. Afficher les noms et les salaires hebdomadaires des opérateurs
5. Afficher les noms et les salaires hebdomadaires des programmeurs
6. Rechercher un employé par son nom
0. Quitter

Veuillez entrer votre choix : 2
==================

Nombre d'opérateurs travaillant plus de 40.50 heures/semaine : 0

====== Menu ======
1. Afficher le nombre de programmeurs qui travaillent plus de 45 heures / semaine
2. Afficher le nombre d'opérateurs qui travaillent plus de 40.50 heures / semaine
3. Afficher le nombre de secrétaires qui travaillent plus de 35.00 heures / semaine
4. Afficher les noms et les salaires hebdomadaires des opérateurs
5. Afficher les noms et les salaires hebdomadaires des programmeurs
6. Rechercher un employé par son nom
0. Quitter

Veuillez entrer votre choix : 3
==================

Nombre de secrétaires travaillant plus de 35.00 heures/semaine : 5

====== Menu ======
1. Afficher le nombre de programmeurs qui travaillent plus de 45 heures / semaine
2. Afficher le nombre d'opérateurs qui travaillent plus de 40.50 heures / semaine
3. Afficher le nombre de secrétaires qui travaillent plus de 35.00 heures / semaine
4. Afficher les noms et les salaires hebdomadaires des opérateurs
5. Afficher les noms et les salaires hebdomadaires des programmeurs
6. Rechercher un employé par son nom
0. Quitter

Veuillez entrer votre choix : 4
==================


--- Salaires hebdomadaires des opérateurs ---
Nom : Clinclin Stephane, Salaire hebdomadaire : 830.00
Nom : Lachance Carl, Salaire hebdomadaire : 675.00
Nom : Lapalme Justin, Salaire hebdomadaire : 630.00
Nom : St-germain Guy, Salaire hebdomadaire : 562.50

====== Menu ======
1. Afficher le nombre de programmeurs qui travaillent plus de 45 heures / semaine
2. Afficher le nombre d'opérateurs qui travaillent plus de 40.50 heures / semaine
3. Afficher le nombre de secrétaires qui travaillent plus de 35.00 heures / semaine
4. Afficher les noms et les salaires hebdomadaires des opérateurs
5. Afficher les noms et les salaires hebdomadaires des programmeurs
6. Rechercher un employé par son nom
0. Quitter

Veuillez entrer votre choix : 5
==================


--- Salaires hebdomadaires des programmeurs ---
Nom : Desautels Maryse, Salaire hebdomadaire : 910.00
Nom : Desbiens Robert, Salaire hebdomadaire : 875.00
Nom : Deschenes Sylvie, Salaire hebdomadaire : 875.00
Nom : Desjardins Alex, Salaire hebdomadaire : 875.00
Nom : Labonte Chantal, Salaire hebdomadaire : 800.00
Nom : St-amour Flavie, Salaire hebdomadaire : 1000.00

====== Menu ======
1. Afficher le nombre de programmeurs qui travaillent plus de 45 heures / semaine
2. Afficher le nombre d'opérateurs qui travaillent plus de 40.50 heures / semaine
3. Afficher le nombre de secrétaires qui travaillent plus de 35.00 heures / semaine
4. Afficher les noms et les salaires hebdomadaires des opérateurs
5. Afficher les noms et les salaires hebdomadaires des programmeurs
6. Rechercher un employé par son nom
0. Quitter

Veuillez entrer votre choix : 6
==================

Entrez le nom de l'employé à rechercher : Desjardins alex

Employé trouvé : desjardins alex, Poste : P

====== Menu ======
1. Afficher le nombre de programmeurs qui travaillent plus de 45 heures / semaine
2. Afficher le nombre d'opérateurs qui travaillent plus de 40.50 heures / semaine
3. Afficher le nombre de secrétaires qui travaillent plus de 35.00 heures / semaine
4. Afficher les noms et les salaires hebdomadaires des opérateurs
5. Afficher les noms et les salaires hebdomadaires des programmeurs
6. Rechercher un employé par son nom
0. Quitter

Veuillez entrer votre choix : 0
==================

*/