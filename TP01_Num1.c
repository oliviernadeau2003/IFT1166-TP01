// Olivier Nadeau - 20316525

#include <stdio.h>
#include <string.h>

// --- NUMÉRO 01 ---
// Fonction qui calcule et retourne la somme des diviseurs propres d’un entier donné
int calculerSommeDiviseur(int nombre)
{
    int somme = 0;

    // On boucle de 1 à n/2, car aucun diviseur propre n'est supérieur à n/2
    for (int i = 1; i <= nombre / 2; i++)
    {
        // Si i est un diviseur
        if (nombre % i == 0)
            somme += i;
    }
    return somme;
}

// --- Fonction qui utilise un pointeur pour retourner la somme des diviseurs propres ---
void calculerSommeDiviseurViaPointeur(int nombre, int *somme)
{
    *somme = 0;
    for (int i = 1; i <= nombre / 2; i++)
    {
        if (nombre % i == 0)
            *somme += i;
    }
}

// --- Fonction qui retourne une chaîne contenant tous les diviseurs d'un nombre ---
void obtenirDiviseurs(int nombre, char *diviseurs)
{
    char buffer[20];
    diviseurs[0] = '\0'; // Initialise la chaîne vide

    for (int i = 1; i <= nombre / 2; i++)
    {
        if (nombre % i == 0)
        {
            if (strlen(diviseurs) > 0)
            {
                strcat(diviseurs, " + ");
            }
            snprintf(buffer, sizeof(buffer), "%d", i); // Ensure buffer is declared appropriately
            strcat(diviseurs, buffer);
        }
    }
}

// --- Fonction qui retourne 1 si le nombre est parfait, sinon 0 ---
int estParfait(int nombre)
{
    return calculerSommeDiviseur(nombre) == nombre;
}

// --- Fonction qui affiche tous les nombres parfaits entre min et max ---
void afficherNombreParfait(int min, int max)
{
    int it = 1;
    char diviseurs[500]; // Pour stocker les diviseurs

    for (int i = min; i <= max; i++)
    {
        if (estParfait(i))
        {
            obtenirDiviseurs(i, diviseurs);
            printf("%d) %d = %s\n", it, i, diviseurs);
            it++;
        }
    }
}

void afficherNumeroA()
{
    const int NOMBRE_TEST_1 = 6;
    const int NOMBRE_TEST_2 = 28;
    const int NOMBRE_TEST_3 = 2004;
    int somme;

    printf("\n--- SOMME DES DIVISEURS PROPRES ---\n");

    // --- Utilisation de la fonction avec return ---
    printf("Somme des diviseurs propres de %d : %d\n", NOMBRE_TEST_1, calculerSommeDiviseur(NOMBRE_TEST_1));
    printf("Somme des diviseurs propres de %d : %d\n", NOMBRE_TEST_2, calculerSommeDiviseur(NOMBRE_TEST_2));
    printf("Somme des diviseurs propres de %d : %d\n", NOMBRE_TEST_3, calculerSommeDiviseur(NOMBRE_TEST_3));

    printf("\n--- SOMME DES DIVISEURS PROPRES VIA POINTEUR ---\n");

    // --- Utilisation de la fonction avec pointeur ---
    calculerSommeDiviseurViaPointeur(NOMBRE_TEST_1, &somme);
    printf("Somme des diviseurs propres de %d via pointeur : %d\n", NOMBRE_TEST_1, somme);

    calculerSommeDiviseurViaPointeur(NOMBRE_TEST_2, &somme);
    printf("Somme des diviseurs propres de %d via pointeur : %d\n", NOMBRE_TEST_2, somme);

    calculerSommeDiviseurViaPointeur(NOMBRE_TEST_3, &somme);
    printf("Somme des diviseurs propres de %d via pointeur : %d\n", NOMBRE_TEST_3, somme);

    printf("\n--- ENTIER PARFAIT OU NON ---\n");

    // --- Vérification si les nombres sont parfaits ---
    if (estParfait(NOMBRE_TEST_1))
        printf("%d est un nombre parfait\n", NOMBRE_TEST_1);
    else
        printf("%d n'est pas un nombre parfait\n", NOMBRE_TEST_1);

    if (estParfait(NOMBRE_TEST_2))
        printf("%d est un nombre parfait\n", NOMBRE_TEST_2);
    else
        printf("%d n'est pas un nombre parfait\n", NOMBRE_TEST_2);

    if (estParfait(NOMBRE_TEST_3))
        printf("%d est un nombre parfait\n", NOMBRE_TEST_3);
    else
        printf("%d n'est pas un nombre parfait\n", NOMBRE_TEST_3);

    printf("\n--- AFFICHER NOMBRES PARFAITS ENTRE 5 & 10000 ---\n");
    afficherNombreParfait(5, 10000);
}

// --- --- --- --- --- --- --- --- ---
// --- MAIN ---
int main()
{
    afficherNumeroA();
    return 0;
}

/*

--- SOMME DES DIVISEURS PROPRES ---
Somme des diviseurs propres de 6 : 6
Somme des diviseurs propres de 28 : 28
Somme des diviseurs propres de 2004 : 2700

--- SOMME DES DIVISEURS PROPRES VIA POINTEUR ---
Somme des diviseurs propres de 6 via pointeur : 6
Somme des diviseurs propres de 28 via pointeur : 28
Somme des diviseurs propres de 2004 via pointeur : 2700

--- ENTIER PARFAIT OU NON ---
6 est un nombre parfait
28 est un nombre parfait
2004 n'est pas un nombre parfait

--- AFFICHER NOMBRES PARFAITS ENTRE 5 & 10000 ---
1) 6 = 1 + 2 + 3
2) 28 = 1 + 2 + 4 + 7 + 14
3) 496 = 1 + 2 + 4 + 8 + 16 + 31 + 62 + 124 + 248
4) 8128 = 1 + 2 + 4 + 8 + 16 + 32 + 64 + 127 + 254 + 508 + 1016 + 2032 + 4064

*/