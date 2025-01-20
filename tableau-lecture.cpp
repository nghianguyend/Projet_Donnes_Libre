#include <stdexcept>
/** @file **/
#include <fstream>
#include <sstream>
#include "tableau-lecture.hpp"


vector<vector<string>> litTableau(string nom_fichier, int nb_colonnes) {
    ifstream flux(nom_fichier);
    if(!flux){
        throw runtime_error("Impossible d'ouvrir le fichier " + nom_fichier);
    }

    string line;
    vector<vector<string>> tab;
    while(getline(flux, line)){
        istringstream iss(line);
        string mot;
        vector<string> col;

        while(iss >> mot){
            col.push_back(mot);
        }

        if(col.size() != nb_colonnes){
            throw runtime_error("Nombre de colonnes inattendu dans le fichier " + nom_fichier);
        }
        tab.push_back(col);
    }

    flux.close();
    return tab;
}

