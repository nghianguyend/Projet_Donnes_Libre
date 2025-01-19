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

vector<vector<string>> tableauTest = {
    { "M", "2011", "Bubulle", "3"},
    { "F", "2012", "Bichette", "4"},
    { "F", "2011", "Babouche", "7"},
    { "F", "2011", "Ziboulette", "1"}
};

/** Affiche le contenu d'un tableau de chaînes à deux dimensions
 * @param tableau un tableau à deux dimensions
 **/
void afficheTableau(vector<vector<string>> tableau) {
    for(int i = 0; i < tableau.size(); i++){
        for(int j = 0; j < tableau[i].size(); j++){
            cout << tableau[i][j] << " ";
        }
    }
    cout << endl;
}

void testAfficheTableau() {
    afficheTableau(tableauTest);
}


/** Construction d'un tableau 2D de chaines de caractères lu depuis un fichier
 * @param fichier le nom d'un fichier contenant un nombre fixe
  * de colonnes séparées par des espaces
 * @param nb_colonnes le nombre de colonnes du fichier
 * @return un tableau de chaines de caractères à deux dimensions
 **/
vector<vector<string>> litTableau(string nom_fichier, int nb_colonnes) {
    ifstream flux(nom_fichier);
    if(!flux){
        throw runtime_error("Impossible d'ouvrir le ficier " + nom_fichier);
    }
    string line;
    vector<vector<string>> tab;

    while(getline(flux, line)){
        istringstream iss(line);
        vector<string> col;
        string mot;
        
        while(iss >> mot){
            col.push_back(mot);
        }
        if (col.size() != nb_colonnes){
            throw runtime_error("Nombre de colonnes inattendu dans le fichier " + nom_fichier);
        }
        tab.push_back(col);
    }
    flux.close();
    return tab;
}

/** Test de la fonction litTableau **/
void testLitTableau() {
    CHECK(litTableau("donnees/donnees-test.txt", 4) == tableauTest);
    vector<vector<string>> t = litTableau("donnees/liste_des_prenoms.txt", 4);
    CHECK(t.size() == 25465);
    CHECK(t[0][0] == "M");
    CHECK(t[3][2] == "Olivia");
    CHECK(t[5][3] == "71");
}

/** Extraction d'une colonne d'un tableau de données
 * @param t un tableau 2D de chaines de caractères
 * @param j un numéro de colonne
 * @return la colonne j, représentée par un vecteur de chaines de caractères
 **/
vector<string> colonne(vector<vector<string>> t, int j) {
    vector<string> tab;
    for(int i = 0; i < t.size(); i++){
        tab.push_back(t[i][j]);
    }
    return tab;
}

/** Test de la fonction colonne **/
void testColonne() {
    CHECK(colonne(tableauTest, 0) == vector<string>({"M","F","F","F"}));
    CHECK(colonne(tableauTest, 1) == vector<string>({"2011","2012","2011","2011"}));
    CHECK(colonne(tableauTest, 2) == vector<string>({"Bubulle","Bichette","Babouche","Ziboulette"}));
    CHECK(colonne(tableauTest, 3) == vector<string>({"3","4","7","1"}));
}

/** Convertit un tableau de chaines de caractères en un tableau d'entiers
 * @param t, un vecteur de chaines de caractères
 * @return un vecteur d'entiers
 **/
vector<int> conversionInt(vector<string> t) {
    vector<int> resultat = vector<int>(t.size());
    for(int i =0; i < t.size(); i++) {
        istringstream(t[i]) >> resultat[i];
    }
    return resultat;
}

void testConversionInt() {
    CHECK(conversionInt({}) == vector<int>({}));
    CHECK(conversionInt({"1","2","3"}) == vector<int>({1,2,3}));
}

/** copier la fonction somme déjà écrite **/
int somme(vector<int> t) {
    int sum = 0;
    for(auto valeur : t){
        sum += valeur;
    }
    return sum;
}


/** copier la fonction moyenne déjà écrite **/
int moyenne(vector<int> t) {
    if(t.empty()) return 0;
    return(somme(t) / t.size());
}


/** copier la fonction indiceMax déjà écrite **/
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


/** Sélection des lignes d'un tableau de données
 * Sélectionne un ensemble de lignes en fonction d'un critère donné
 * @param t, un tableau contenant des lignes de données
 * @param j, l'indice de la colonne à vérifier
 * @param valeur, une chaine de caractères correspondant au critère
 * @return un tableau de données ne contenant que les lignes de t telles
 *  que la colonne j ait la valeur correspondant au critère
 **/
vector<vector<string>> selectLignes(vector<vector<string>> t, int j, string valeur) {
    vector<vector<string>> tab;
    for(int i = 0; i < t.size(); i++){
        if(j < t[i].size() && t[i][j] == valeur){
            tab.push_back(t[i]);
        }
    }
    return tab;
}

/** Test de la fonction selectLignes **/
void testSelectLignes() {
    CHECK(selectLignes(tableauTest, 0, "M") == vector<vector<string>>({{ "M", "2011", "Bubulle", "3"}}));
    CHECK(selectLignes(tableauTest, 1, "2011") == vector<vector<string>>({{ "M", "2011", "Bubulle", "3"}, { "F", "2011", "Babouche", "7"}, { "F", "2011", "Ziboulette", "1"}}));
}

/** Lance les tests de litTableau, selectLignes et colonne puis
 * affiche le nombre total de naissances puis
 * demande à l'utilisateur un prénom et calcule et affiche
 * - le nombre de garçons et filles à qui l'on a donné ce prénom
 * - la meilleure année pour ce prénom pour les garçons et filles
 **/
int main() {
    // Lancement des tests
    testAfficheTableau();
    testColonne();
    testConversionInt();
    testLitTableau();
    testSelectLignes();

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

