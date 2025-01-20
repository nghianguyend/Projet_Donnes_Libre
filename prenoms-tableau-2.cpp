#include <stdexcept>
/** @file **/
#include <fstream>
#include <iostream>
#include "tableau-donnees.hpp"
#include "tableau-lecture.hpp"
using namespace std;


/**
 * Demande à l'utilisateur un prénom et calcule
 * - le nombre de garçons et filles à qui l'on a donné ce prénom
 * - la meilleure année pour ce prénom pour les garçons et filles
 **/
int main() {
// Chargement des données
    vector<vector<string>> donnees = litTableau("donnees/liste_des_prenoms.txt", 4);


    // Calcul du nombre total de naissance
    vector<string> naissance_str = colonne(donnees, 3);
    vector<int> naissace_int = conversionInt(naissance_str);
    int total_naissance = somme(naissace_int);
    cout << "Nombre total de naissance : " << total_naissance << endl;


    // Demander à l'utilisateur de choisir un prénom
    string prenom;
    cout << "Choisissez un prénom : ";
    cin >> prenom;


    // Sélection des lignes correspondant au prénom
    vector<vector<string>> prenom_ligne = selectLignes(donnees, 2, prenom);


    // Séparation des filles et garçons
    vector<vector<string>> prenom_gars = selectLignes(prenom_ligne, 0, "M");
    vector<vector<string>> prenom_filles = selectLignes(prenom_ligne, 0, "F");


    // Somme des prenoms garçons et meilleure année
    vector<string> num_prenom_gars_str = colonne(prenom_gars, 3);
    vector<int> num_prenom_gars_int = conversionInt(num_prenom_gars_str);
    // Meilleure années
    int meilleure_annees_gars = (num_prenom_gars_int.empty()) ? -1 : indiceMax(num_prenom_gars_int);
    // Somme
    int total_prenom_gars = somme(num_prenom_gars_int);


    // Somme des prenoms filles et meilleure année
    vector<string> num_prenom_filles_str = colonne(prenom_filles, 3);
    vector<int> num_prenom_filles_int = conversionInt(num_prenom_filles_str);
    // Meilleure année
    int meilleure_annees_filles = (num_prenom_filles_int.empty()) ? -1 : indiceMax(num_prenom_filles_int);
    // Somme
    int total_prenom_filles = somme(num_prenom_filles_int);


    // Affichage des résultats
    if(total_prenom_gars > 0){
        cout << "Le prénom " << prenom << " a été donné à " << total_prenom_gars << " garçons entre 2006 et 2023 " << endl;
        cout << "L'année la plus forte est " << prenom_gars[meilleure_annees_gars][1] << " avec " << prenom_gars[meilleure_annees_gars][3] << " enfants " << endl;
    }
    else {
        cout << "Le prénom " << prenom << " n'a été donné à aucun garçon entre 2006 et 2023" << endl;
    }

    if(total_prenom_filles > 0){
        cout << "Le prénom " << prenom << " a été donné à " << total_prenom_filles << " filles entre 2006 et 2023 " << endl;
        cout << "L'année la plus forte est " << prenom_filles[meilleure_annees_filles][1] << " avec " << prenom_filles[meilleure_annees_filles][3] << " enfants " << endl;
    }
    else {
        cout << "Le prénom " << prenom << " n'a été donné à aucun fille entre 2006 et 2023" << endl;
    }

    return 0;
}

