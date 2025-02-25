#include <stdexcept>
/** @file **/
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

/** Infrastructure minimale de test **/
#define CHECK(test) if (!(test)) cerr << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl

vector<string> jours = {"Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche"};


/** Construction du tableau des mariages par années
 * On suppose que le fichier contient sur chaque ligne une année entre 2010 et 2022
 * suivi d'un jour, puis d'un nombre de mariages
 * @param nom_fichier, le nom du fichier de données
 * @return un tableau d'entiers tel que dans chaque
 * case d'indice i, on trouve le nombre total de mariages de l'année 2010+i
 **/
vector<int> litTableauAnnee(string nom_fichier) {
    ifstream flux(nom_fichier);
    if(!flux){
        throw runtime_error("Impossible d'ouvrir le fichier : " + nom_fichier);
    }
    string line;
    vector<int> tab(13, 0);
    int annee_debut = 2010;

    while(getline(flux, line)){
        istringstream iss(line);
        string jour;
        int annee, nombre_de_mariages;

        if(iss >> annee >> jour >> nombre_de_mariages){
            tab[annee - annee_debut]  += nombre_de_mariages;
        }
        else{
            cerr << "Année hors plage détectée : " << annee << endl;
        }

    }
    flux.close();
    return tab;

}

/** Test de la fonction litTableauAnnee **/
void testLitTableauAnnee() {
    vector<int> t = litTableauAnnee("donnees/statistiques-des-jours-des-mariages.txt");
    CHECK(t[0] == 9195); // Nombre de mariages en 2010
    CHECK(t[3] == 9443); // Nombre de mariages en 2013
    CHECK(t[5] == 9046); // Nombre de mariages en 2015
    CHECK(t[12] == 8484); // Nombre de mariages en 2022
}

/** Renvoie le numéro du jour correspondant à la chaîne de caractères
 * @param jour une chaine de caractère contenant un jour de la semaine (première lettre en majuscule)
 * @return un numéro entre 0 et 6 correspondant au jour de la semaine ou
 * -1 si le jour n'est pas valide
 **/
int indiceJour(string jour) {
    for(int i=0; i < jours.size(); i++) {
        if (jour == jours[i]) {
            return i;
        }
    }
    return -1;
}

void testIndiceJour() {
    CHECK(indiceJour("Lundi") == 0);
    CHECK(indiceJour("Samedi") == 5);
    CHECK(indiceJour("Dimanche") == 6);
    CHECK(indiceJour("samedi") == -1);
}

/** Construction du tableau des mariages par jour
 * On suppose que le fichier contient sur chaque ligne une année entre 2010 et 2022
 * suivie d'un jour, puis d'un nombre de mariages
 * @param nom_fichier, le nom du fichier de données
 * @return un tableau d'entiers tel que dans chaque
 * case d'indice i, on trouve le nombre total de mariages célébrés le jour i
 **/
vector<int> litTableauJours(string nom_fichier) {
    ifstream flux(nom_fichier);
    if (!flux){
        throw runtime_error("Impossible d'ouvrir le fichier : " + nom_fichier);
    }

    vector<int> tab1(7,0);
    string line;
    while(getline(flux, line)){
        istringstream iss(line);
        string jour;
        int annee, nombre_de_mariages;

        if(iss >> annee >> jour >> nombre_de_mariages){
            tab1[indiceJour(jour)] += nombre_de_mariages;
        }
    }
    flux.close();
    return tab1;
}

/** Test de la fonction litTableauJours **/
void testLitTableauJours() {
    vector<int> t = litTableauJours("donnees/statistiques-des-jours-des-mariages.txt");
    CHECK(t[0] == 8211); // Nombre de mariages le lundi
    CHECK(t[3] == 9579); // Nombre de mariages le jeudi
    CHECK(t[6] == 3); // Nombre de mariages le dimanche
}

/** Renvoie la somme d'un tableau d'entiers
 * @param t, un tableau d'entier
 * @return la somme des valeurs du tableau
 **/
int somme(vector<int> t) {
    int sum = 0;
    for(auto valeur : t){
        sum += valeur;
    }
    return sum;
}

/** Test de la fonction somme **/
void testSomme() {
    CHECK(somme({1,2,3}) == 6);
    CHECK(somme({}) == 0);
    CHECK(somme({2,2,4,8}) == 16);
}

/** Renvoie la moyenne d'un tableau d'entier
 * @param t, un tableau d'entiers
 * @return la moyenne (entière) des valeurs
 * (on arrondit à l'entier inférieur)
 **/
int moyenne(vector<int> t) {
    if(t.empty()) return 0;
    return(somme(t) / t.size());
}

/** Test de la fonction moyenne **/
void testMoyenne() {
    CHECK(moyenne({1,2,3}) == 2);
    CHECK(moyenne({1}) == 1);
    CHECK(moyenne({2,2,4,8}) == 4);
}


/** Renvoie l'indice de la valeur maximale du tableau
 * @param t, un tableau d'entier
 * @return l'indice de la valeur maximale ou -1 si le tableau est vide
 **/
int indiceMax(vector<int> t) {
    if(t.empty()) return -1;
    int indice_max = -1;
    int max_val = 0;
    for(int i = 0; i < t.size(); i++){
        if(t[i] > max_val){
            max_val = t[i];
            indice_max = i;
        }
    }
    return indice_max;
}

/** Test de la fonction IndiceMax **/
void testIndiceMax() {
    CHECK(indiceMax({}) == -1);
    CHECK(indiceMax({1,2,3}) == 2);
    CHECK(indiceMax({1,3,2}) == 1);
    CHECK(indiceMax({1}) == 0);
    CHECK(indiceMax({2,8,4,4}) == 1);
}

/** Lance les fonctions de test puis affiche :
 * - le nombre total de mariages
 * - le nombre moyen de mariages célébrés par an
 * - l'année où l'on a célébré le plus de mariages (et leur nombre)
 * - le jour de la semaine où l'on célèbre le plus de mariages (et leur nombre)
 * - le pourcentage de mariages célébrés un samedi
 **/
int main()
{
    try
    {
        // Tests des fonctions
        testLitTableauAnnee();
        testIndiceJour();
        testLitTableauJours();
        testSomme();
        testMoyenne();
        testIndiceMax();

        // Lecture des tableaux
        vector<int> mariagesParAn = litTableauAnnee("donnees/statistiques-des-jours-des-mariages.txt");
        vector<int> mariagesParJour = litTableauJours("donnees/statistiques-des-jours-des-mariages.txt");

        // Calculs principaux
        int totalMariages = somme(mariagesParAn);
        int moyenneAnnuelle = moyenne(mariagesParAn);
        int anneeMax = indiceMax(mariagesParAn);
        int jourMax = indiceMax(mariagesParJour);
        int samediMariages = mariagesParJour[5];
        float pourcentageSamedi = (samediMariages * 100.0) / totalMariages;

        // Affichage des résultats
        cout << "Nombre total de mariages de mariages célébrés entre 2010 et 2022 est de : " << totalMariages << endl;
        cout << "Le nombre de mariages célébrés en moyenne par an est de : " << moyenneAnnuelle << endl;
        cout << "L'année où l'on a célébré le plus de mariages est : " << 2010 + anneeMax << " (" << mariagesParAn[anneeMax] << " mariages)" << endl;
        cout << "Jour avec le plus de mariages : " << jours[jourMax] << " (" << mariagesParJour[jourMax] << " mariages)" << endl;
        cout << "Pourcentage de mariages célébrés un samedi : " << pourcentageSamedi << "%" << endl;
    }
    catch (const exception &e)
    {
        cerr << "Erreur : " << e.what() << endl;
    }
    return 0;
}

