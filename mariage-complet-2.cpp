#include <stdexcept>
/** @file **/
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>
#include "tableau-donnees.hpp"
#include "tableau-lecture.hpp"
using namespace std;

/** Infrastructure minimale de test **/
#define CHECK(test) \
    if (!(test))    \
    cerr << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl

vector<string> annees = {"2010", "2011", "2012", "2013", "2014", "2015", "2016", "2017", "2018", "2019", "2020", "2021", "2022"};
vector<string> jours = {"Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi", "Dimanche"};

/** Construction du tableau des mariages par années à partir d'un
 * tableau de données 2D (de chaines de caractères)
 * Chaque ligne contient : l'année, le jour, puis le nombre de mariages
 * @param t un tableau de données 2D de chaines de caractère
 * @return un tableau d'entiers tel que dans chaque
 * case d'indice i, on trouve le nombre total de mariages de l'année 2010+i
 **/
vector<int> creeTableauAnnee(vector<vector<string>> data)
{

    // Extraction et conversion des tableaux
    vector<string> tab_annee_str = colonne(data, 0);
    vector<string> tab_nombremariages_str = colonne(data, 2);
    vector<int> tab_nombremariages_int = conversionInt(tab_nombremariages_str);
    vector<int> tab_annee_int = conversionInt(tab_annee_str);

    // Determiner max année et min année
    int min_year = 2010;
    int max_year = *max_element(tab_annee_int.begin(), tab_annee_int.end());

    // Creation du tableau avec des 0
    vector<int> result(max_year - min_year + 1, 0);

    // Accumulate the number of marriages for each year
    for (int i = 0; i < tab_annee_int.size(); i++)
    {
        int year = tab_annee_int[i];
        int marriage_count = tab_nombremariages_int[i];
        if (year >= min_year)
        {
            result[year - min_year] += marriage_count;
        }
    }

    return result;
}

/** Test de la fonction CreeTableauAnnee **/
void testCreeTableauAnnee()
{
    vector<vector<string>> data = litTableau("donnees/statistiques-des-jours-des-mariages.txt", 3);
    vector<int> t = creeTableauAnnee(data);
    CHECK(t[0] == 9195);  // Nombre de mariages en 2010
    CHECK(t[3] == 9443);  // Nombre de mariages en 2013
    CHECK(t[5] == 9046);  // Nombre de mariages en 2015
    CHECK(t[12] == 8484); // Nombre de mariages en 2022
}

/** Renvoie le numéro du jour correspondant à la chaîne de caractères
 * @param jour une chaine de caractères contenant un jour de la semaine (première lettre en majuscule)
 * @return un numéro entre 0 et 6 correspondant au jour de la semaine ou
 * -1 si le jour n'est pas valide
 **/
int indiceJour(string jour)
{
    for (int i = 0; i < jours.size(); i++)
    {
        if (jour == jours[i])
        {
            return i;
        }
    }
    return -1;
}

void testIndiceJour()
{
    CHECK(indiceJour("Lundi") == 0);
    CHECK(indiceJour("Samedi") == 5);
    CHECK(indiceJour("Dimanche") == 6);
    CHECK(indiceJour("samedi") == -1);
}

/** Construction du tableau des mariages à partir d'un
 * tableau de données 2D (de chaines de caractères)
 * suivi d'un jour, puis d'un nombre de mariages
 * Chaque ligne contient : l'année, le jour, puis le nombre de mariages
 * @param t un tableau de données 2D de chaines de caractère
 * @return un tableau d'entiers tel que dans chaque
 * case d'indice i, on trouve le nombre total de mariages célébrés le jour i
 **/
vector<int> creeTableauJours(vector<vector<string>> data)
{
    // Extraction et conversion des tableaux
    vector<string> jour_str = colonne(data, 1);
    vector<string> nb_mariages_str = colonne(data, 2);
    vector<int> nb_mariage_int = conversionInt(nb_mariages_str);

    // Création du tableau avec des 0
    int max_days = 7;
    vector<int> tab(max_days, 0);

    for (int i = 0; i < nb_mariage_int.size(); i++)
    {
        int indice_jour_mariage = indiceJour(jour_str[i]);
        if (indice_jour_mariage < tab.size())
        {
            tab[indice_jour_mariage] += nb_mariage_int[i];
        }
    }
    return tab;
}

/** Test de la fonction litTableauJours **/
void testCreeTableauJours()
{
    vector<vector<string>> data = litTableau("donnees/statistiques-des-jours-des-mariages.txt", 3);
    vector<int> t = creeTableauJours(data);
    CHECK(t[0] == 8211); // Nombre de mariages le lundi
    CHECK(t[3] == 9579); // Nombre de mariages le jeudi
    CHECK(t[6] == 3);    // Nombre de mariages le dimanche
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
    testCreeTableauAnnee();
    testCreeTableauJours();

    // Affichage
    vector<vector<string>> donnees = litTableau("donnees/statistiques-des-jours-des-mariages.txt", 3);

    // Le nombre total de mariages
    vector<string> naissance_str = colonne(donnees, 2);
    vector<int> naissace_int = conversionInt(naissance_str);
    int total_naissance = somme(naissace_int);
    cout << "Le nombre total de mariages est : " << total_naissance << endl;

    // Le nombre moyen de mariages célébrés par an
    vector<int> tab_annee = creeTableauAnnee(donnees);
    double naissance_moy = moyenne(tab_annee);
    cout << "Le nombre moyen de mariages célébrés par an est : " << naissance_moy << endl;

    // L'année où l'on a célébré le plus de mariages (et leur nombre)
    int ind_anne_max = indiceMax(tab_annee);
    cout << "L'année où l'on a célébré le plus de mariages est : " << annees[ind_anne_max] << "." << " Et il y a : " << tab_annee[ind_anne_max] << " mariages célébrés dans cette année." << endl;

    // Le jour de la semaine où l'on célèbre le plus de mariages (et leur nombre)
    vector<int> tab_jour = creeTableauJours(donnees);
    int ind_jour_max = indiceMax(tab_jour);
    cout << "L'année où l'on a célébré le plus de mariages est : " << jours[ind_jour_max] << "." << " Et il y a : " << tab_jour[ind_jour_max] << " mariages célébrés dans ce jour de la semaine." << endl;
    
    // Le pourcentage de mariages célébrés un samedi
    double pourcentage = (static_cast<double>(tab_jour[ind_jour_max]) / total_naissance) * 100;;
    cout << "Le pourcentage de mariages célébrés le samedi est : " << pourcentage << " %" << endl;
    return 0;
}
