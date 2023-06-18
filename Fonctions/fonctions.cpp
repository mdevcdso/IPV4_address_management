//Librairie de base en C++
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

string menu[] = {
    "1) Saisir une adresse IP d'un poste du réseau",
    "2) Saisir un masque de sous-réseau en format adresse IPV4",
    "3) Saisir un masque de sous-réseau en format CIDR",
    "4) Afficher l'adresse IP en cours",
    "5) Afficher le masque en cours",
    "6) Afficher les infos réseau",
    "7) Afficher l'adresse IP du poste en format binaire",
    "8) Quitter"
};

//Afficher un menu à l'utilisateur, permettant de faire un choix parmi plusieurs options
int AfficheMenu() {
    int choix;
    for (string item : menu) { //variable item qui stocke chaque élément de la chaine menu
        cout << item << endl;
    }
    cout << "Choix : ";
    cin >> choix;
    return choix;
}

bool AdresseIP(const string& ipAddress) {
    stringstream ss(ipAddress);
    string segment;
    int count = 0;
    while (getline(ss, segment, '.')) {
        if (segment.empty() || segment.find_first_not_of("0123456789") != string::npos) {
            return false;
        }
        int num = stoi(segment);
        if (num < 0 || num > 255) {
            return false;
        }
        count++;
    }
    return count == 4;
}

bool CIDR(const string& cidr) {
    stringstream ss(cidr);
    int prefix;
    char delimiter;
    return (ss >> prefix && prefix >= 0 && prefix <= 32 && !(ss >> delimiter));
}