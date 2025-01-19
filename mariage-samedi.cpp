#include <stdexcept>
/** @file **/
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

/** Calcule et affiche le nombre de mariages un samedi entre 2010 et 2022 **/
void mariage_samedi(string fichier){
    ifstream flux(fichier);
    if(!flux){
        cerr << "Impossible d'ouvrir le fichier : " << fichier << endl;
        return;
    }

    string line;
    int nombre_mariage_samedi = 0;

    while(getline(flux, line)){
        istringstream iss(line);
        string annee, jour;
        int nombre;

        if(iss >> annee >> jour >> nombre){
            if(jour == "Samedi"){
                nombre_mariage_samedi += nombre;
            }
        }
        else
        {
            cerr << "Erreur de lecture de la ligne" << line << endl;
        }
    }
    flux.close();
    cout << "Nombre total de mariages célébrés un samedi à Paris est : " << nombre_mariage_samedi << endl;
}


int main() {
    mariage_samedi("donnees/statistiques-des-jours-des-mariages.txt");
    return 0;
}

