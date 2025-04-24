#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool lireFichier(const string& nomFichier, vector<string>& mots) {
    ifstream fichier(nomFichier);
    if (!fichier) {
        cout << "Impossible d'ouvrir le fichier : " << nomFichier << endl;
        return false;
    }

    string mot;
    while (fichier >> mot) {
        mots.push_back(mot);
    }

    return !mots.empty();
}

void sauvegarderMotsTries(const vector<string>& mots, const string& nomFichier) {
    ofstream fichierSortie(nomFichier);
    if (!fichierSortie) {
        cout << "Erreur lors de l'écriture dans le fichier : " << nomFichier << endl;
        return;
    }

    for (const auto& mot : mots) {
        fichierSortie << mot << endl;
    }

    cout << "Les mots triés ont été sauvegardés dans : " << nomFichier << endl;
}

bool rechercheMot(const vector<string>& mots, const string& motRecherche) {
    int gauche = 0;
    int droite = mots.size() - 1;

    while (gauche <= droite) {
        int milieu = (gauche + droite) / 2;
        if (mots[milieu] == motRecherche) {
            return true;
        }
        else if (motRecherche < mots[milieu]) {
            droite = milieu - 1;
        }
        else {
            gauche = milieu + 1;
        }
    }

    return false;
}

int main() {
    vector<string> listeMots;

    if (!lireFichier("mots.txt", listeMots)) {
        return 1;
    }

    sort(listeMots.begin(), listeMots.end());

    cout << "Voici la liste des mots triés :\n";
    for (const auto& mot : listeMots) {
        cout << mot << endl;
    }

    sauvegarderMotsTries(listeMots, "mots_Trie.txt");

    string motARechercher;
    cout << "\nEntrez un mot à rechercher : ";
    cin >> motARechercher;

    if (rechercheMot(listeMots, motARechercher)) {
        cout << "Le mot '" << motARechercher << "' se trouve dans la liste !" << endl;
    }
    else {
        cout << "Désolé, le mot '" << motARechercher << "' ne figure pas dans la liste." << endl;
    }

    return 0;
}
