#include <stdexcept>
/** @file **/
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

/** Calcule et affiche le prénom le plus utilisé une année donnée
 * ainsi que le nombre de naissances cette année là **/
void max_prenom(string fichier){
    ifstream flux(fichier);
    if (!flux){
        cerr << "Impossible d'ouvrir le fichier " << fichier << endl;
        return;
    }

    int annee_input;

    cout << "Entrer une année entre 2004 et 2025 : ";
    cin >> annee_input;

    if(annee_input < 2004 || annee_input > 2025){
        cerr << "L'année doit être comprise entre 2004 et 2023." << endl;
        return;
    }

    string line;
    int total_naissance = 0;
    int max_naissance = 0;
    string max_nom_naissance;

    while(getline(flux, line)){

        istringstream iss(line);
        string sexe, nom;
        int annee, nombre_naissance;
        if(iss >> sexe >> annee >> nom >> nombre_naissance){
            if(annee == annee_input){
                total_naissance += nombre_naissance;
                if(nombre_naissance > max_naissance){
                    max_naissance = nombre_naissance;
                    max_nom_naissance = nom;
                }
            }
        }
    }
    if(max_naissance == 0){
        cout << "Aucune naissance enregistrée pour l'année " << annee_input << endl;
    }
    else{
        cout << "En " << annee_input << ", il y a eu " << total_naissance << " naissances" << endl;
        cout << "Le prénom le plus donné a été : " << max_nom_naissance << " (donné " << max_naissance << " fois)";
    }
}


int main() {
    max_prenom("donnees/liste_des_prenoms.txt");
    return 0;
}

