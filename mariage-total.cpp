#include <stdexcept>
/** @file **/
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

/** Calcule et affiche le nombre total de mariages célébrés entre 2010 et 2022 **/
void lecture_fichier(string fichier)
{
    ifstream flux(fichier);
    if (!flux)
    {
        cerr << "Impossible d'ouvrir le fichier" << fichier << endl;
        return;
    }
    string line;
    int total_mariages = 0;

    while (getline(flux, line))
    {
        istringstream iss(line);
        string year, jour;
        int nombre;

        if (iss >> year >> jour >> nombre)
        {
            total_mariages += nombre;
        }
        else
        {
            cerr << "Erreur de lecture de la ligne" << line << endl;
        }
    }
    flux.close();
    cout << "Nombre total de mariages célébrés entre 2010 et 2022 : " << total_mariages << endl;
    
}
int main()
{
    lecture_fichier("donnees/statistiques-des-jours-des-mariages.txt");
    return 0;
}
