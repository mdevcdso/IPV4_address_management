//Librairies C++
#include <iostream>
#include <string>
#include <sstream>

//Ajout des fichiers annexes
#include "Fonctions\fonctions.cpp"
#include "Fonctions\procedures.cpp"

//directive qui utilise tous les noms de l'espace de noms standard std
using namespace std;

int main() {
    //Déclaration de variables
    int choix, ipOctets[4] = {0}, maskOctets[4] = {0};
    string adresseIP, masqueSousReseaux;

    //Affichage du menu avec les differentes options
    do {
        choix = AfficheMenu();

        //Options
        switch (choix) {
            case 1:
                cout << "Saisir une adresse IP : ";
                cin >> adresseIP;
                if (AdresseIP(adresseIP)) {
                    splitIPAddress(adresseIP, ipOctets);
                } else {
                    cout << "Adresse IP invalide !" << endl;
                }
                break;
            case 2:
                cout << "Saisir un masque de sous-reseau en format adresse IPV4 : ";
                cin >> masqueSousReseaux;
                if (AdresseIP(masqueSousReseaux)) {
                    splitIPAddress(masqueSousReseaux, maskOctets);
                } else {
                    cout << "Masque invalide !" << endl;
                }
                break;
            case 3:
                cout << "Saisir un masque de sous-reseau en format CIDR : ";
                cin >> masqueSousReseaux;
                if (CIDR(masqueSousReseaux)) {
                    int prefix = stoi(masqueSousReseaux);
                    convertCIDRToMask(prefix, maskOctets);
                } else {
                    cout << "CIDR invalide !" << endl;
                }
                break;
            case 4:
                cout << "Adresse IP en cours : ";
                printIPAddress(ipOctets);
                break;
            case 5:
                cout << "Masque en cours : ";
                printMask(maskOctets);
                break;
            case 6:
                cout << "Infos reseau :" << endl;
                printNetworkInfo(ipOctets, maskOctets);
                break;
            case 7:
                cout << "Adresse IP du poste en format binaire : ";
                printBinaryIPAddress(ipOctets);
                break;
            case 8:
                cout << "Au revoir !" << endl;
                break;
            default:
                cout << "Choix invalide !" << endl;
        }
    
        cout << endl;

    } while (choix != 8); //la boucle se repete tant que choix != 8

    return 0;
}