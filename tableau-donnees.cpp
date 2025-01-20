#include <stdexcept>
/** @file **/
#include <fstream>
#include <sstream>
#include "tableau-donnees.hpp"

void afficheTableau(vector<vector<string>> tableau) {
    for(int i = 0; i < tableau.size(); i++){
        for(int j = 0; j < tableau[i].size(); j++){
            cout << tableau[i][j] << " ";
        }
    }
    cout << endl;
}

int moyenne(vector<int> t) {
    if(t.empty()) return 0;
    return(somme(t) / t.size());
}

int somme(vector<int> t) {
    int sum = 0;
    for(auto valeur : t){
        sum += valeur;
    }
    return sum;
}


int indiceMax(vector<int> t) {
    int max_val = 0;
    int max_ind = -1;

    for(int i = 0; i < t.size(); i++){
        if(t[i] > max_val){
            max_val = t[i];
            max_ind = i;
        }
    }
    return max_ind;
}

vector<string> colonne(vector<vector<string>> t, int j) {
    vector<string> tab;
    for(int i = 0; i < t.size(); i++){
        tab.push_back(t[i][j]);
    }
    return tab;
}


vector<int> conversionInt(vector<string> t) {
    vector<int> tab = vector<int>(t.size());
    for(int i = 0; i < t.size(); i++){
        istringstream(t[i]) >> tab[i];
    }
    return tab;
}

vector<vector<string>> selectLignes(vector<vector<string>> t, int j, string valeur) {
    vector<vector<string>> tab;
    for(int i = 0; i < t.size(); i++){
        if(j < t[i].size() && t[i][j] == valeur){
            tab.push_back(t[i]);
        }
    }
    return tab;
}
