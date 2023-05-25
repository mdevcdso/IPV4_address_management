#include <iostream>
#include <string>

using namespace std;

int main() {
    string nom;

    cout << "Veuillez saisir votre nom : ";
    getline(cin, nom);

    if (nom.empty()) {
         cout << "Erreur : aucun nom saisi." <<  endl;
    } else {
         cout << "Bonjour " << nom << " !" <<  endl;
    }

    cout << "test" <<  endl;

    return 0;
}