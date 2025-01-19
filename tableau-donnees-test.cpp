#include <stdexcept>
/** @file **/
#include <iostream>
#include "tableau-donnees.hpp"
using namespace std;

/** Infrastructure minimale de test **/
#define CHECK(test) if (!(test)) cerr << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl

vector<vector<string>> tableauTest = {
    { "M", "2011", "Bubulle", "3"},
    { "F", "2012", "Bichette", "4"},
    { "F", "2011", "Babouche", "7"},
    { "F", "2011", "Ziboulette", "1"}
};

vector<int> c = { 1, 5, 3, 5, 1 };
vector<vector<int>> t = { {1, 2}, {2,4}, {3,1}, {0,0} };

void testAfficheTableau() {
    afficheTableau(tableauTest);
}

void testMoyenne() {
    CHECK( moyenne(c) == 3 );
}

void testSomme() {
    // Remplacez cette ligne et la suivante par le code adéquat
    throw runtime_error("Fonction testSomme non implantée ligne 30");
}

void testIndiceMax() {
    // Remplacez cette ligne et la suivante par le code adéquat
    throw runtime_error("Fonction testIndiceMax non implantée ligne 35");
}

void testColonne() {
    CHECK(colonne(tableauTest, 0) == vector<string>({"M","F","F","F"}));
    CHECK(colonne(tableauTest, 1) == vector<string>({"2011","2012","2011","2011"}));
    CHECK(colonne(tableauTest, 2) == vector<string>({"Bubulle","Bichette","Babouche","Ziboulette"}));
    CHECK(colonne(tableauTest, 3) == vector<string>({"3","4","7","1"}));
}

void testConversionInt() {
    CHECK(conversionInt({}) == vector<int>({}));
    CHECK(conversionInt({"1","2","3"}) == vector<int>({1,2,3}));
}

void testSelectLignes() {
    CHECK(selectLignes(tableauTest, 0, "M") == vector<vector<string>>({{ "M", "2011", "Bubulle", "3"}}));
    CHECK(selectLignes(tableauTest, 1, "2011") == vector<vector<string>>({{ "M", "2011", "Bubulle", "3"}, { "F", "2011", "Babouche", "7"}, { "F", "2011", "Ziboulette", "1"}}));
}


int main() {
    cerr << "Test affichage du tableau" << endl;
    testAfficheTableau();
    cout << "Lancement des tests de moyenne" << endl;
    testMoyenne();
    cout << "Lancement des tests de somme" << endl;
    testSomme();
    cout << "Lancement des tests de indiceMax" << endl;
    testIndiceMax();
    cout << "Lancement des tests de colonne" << endl;
    testColonne();
    cout << "Lancement des tests de conversionInt" << endl;
    testConversionInt();
    cout << "Lancement des tests de selectLignes" << endl;
    testSelectLignes();
}

