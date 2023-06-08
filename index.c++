#include <iostream>

using namespace std;

void afficherMenu() {
    cout << "Menu :" << endl;
    cout << "1) Saisir une adresse IP d'un poste du réseau" << endl;
    cout << "2) Saisir un masque de sous-réseau en format adresse IPV4" << endl;
    cout << "3) Saisir un masque de sous-réseau en format CIDR" << endl;
    cout << "4) Afficher l'adresse IP en cours" << endl;
    cout << "5) Afficher le masque en cours" << endl;
    cout << "6) Afficher les infos réseau" << endl;
    cout << "7) Afficher l'adresse IP du poste en format binaire" << endl;
    cout << "8) Quitter" << endl;
}

void saisirAdresseIP() {
    string AfficheIP;
    cout << "Veuillez saisir une adresse IP : ";
    cin >> AfficheIP;

    cout << "L'adresse IP saisie est : " << AfficheIP << endl;
}

void saisirMasqueIPV4() {
    string AfficheMasque;
    cout << "Veuillez saisir un masque de sous-réseau : ";
    cin >> AfficheMasque;

    cout << "Le masque saisi est : " << AfficheMasque << endl;
}

void saisirMasqueCIDR() {
    string AfficheMasqueCIDR;
    cout << "Veuillez saisir un masque de sous-réseau en format CIDR : ";
    cin >> AfficheMasqueCIDR;
    
    cout << "Le masque CIDR saisie est : " << AfficheMasqueCIDR << endl;
}

void afficherAdresseIP() {
    cout << "L'adresse IP en cours est : " << endl;
}

void afficherMasque() {
    cout << "Le masque en cours est : " << endl;
}

void afficherInfosReseau() {
    cout << "Informations du réseau : " << endl;
}

void afficherAdresseIPBinaire() {
    cout << "L'adresse IP du poste en format binaire est : " << endl;
}

int main() {
    int choix = 0;

    while (choix != 8) {
        afficherMenu();
        cout << "Entrez votre choix : ";
        cin >> choix;

        switch (choix) {
            case 1:
                saisirAdresseIP();
                break;
            case 2:
                saisirMasqueIPV4();
                break;
            case 3:
                saisirMasqueCIDR();
                break;
            case 4:
                afficherAdresseIP();
                break;
            case 5:
                afficherMasque();
                break;
            case 6:
                afficherInfosReseau();
                break;
            case 7:
                afficherAdresseIPBinaire();
                break;
            case 8:
                cout << "Au revoir !" << endl;
                break;
            default:
                cout << "Choix invalide. Veuillez rééssayer." << endl;
                break;
          }
     }

     return 0;
}