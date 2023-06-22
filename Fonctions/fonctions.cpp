//Librairies de base en C++
#include <iostream>
#include <string>
#include <sstream>

//directive qui utilise tous les noms de l'espace de noms standard std
using namespace std;

//declaration de la variable menu
string menu[] = {
    "1) Saisir une adresse IP d'un poste du reseau",
    "2) Saisir un masque de sous-reseau en format adresse IPV4",
    "3) Saisir un masque de sous-reseau en format CIDR",
    "4) Afficher l'adresse IP en cours",
    "5) Afficher le masque en cours",
    "6) Afficher les infos reseau",
    "7) Afficher l'adresse IP du poste en format binaire",
    "8) Quitter"
};

//afficher un menu à l'utilisateur, permettant de faire un choix parmi plusieurs options
int AfficheMenu() {
    int choix;
    for (string item : menu) { //itération de la variable item qui stocke chaque élément de la chaine menu
        cout << item << endl;
    }
    cout << "Choix : ";
    cin >> choix;
    return choix;
}

//vérifier si une chaîne de caractères AdresseIP représente une adresse IP valide
bool AdresseIP(const string& adressIP) {
    string segment;
    int count = 0;

    for (char i : adressIP) //itération de chaque caractere dans la chaine adressIP
    {
        if (i == '.') //condition si un caractère est un '.'
        {
            if (segment.empty() || segment.find_first_not_of("0123456789") != string::npos) //si la chaine est vide ou ne contient pas de chiffres
            {
                return false;
            }
            int num = stoi(segment); //convertie une chaîne de caractères (segment) en un entier num
            if (num < 0 || num > 255) //si un chiffre est inférieur à 0 et supérieur à 255
            {
                return false;
            }
            segment.clear(); //effacer les éléments rentrés dans la variable segment
            count++;
        } 
        else if (isdigit(i)) { //vérifie si i est un nombre décimal entre 0 et 9
            segment = segment + i; //ajout du caractère dans la chaine
        } 
        else {
            return false;
        }
    }

    //si la chaine est tapée sans '.'
    if (segment.empty() || segment.find_first_not_of("0123456789") != string::npos) {
        return false;
    }
    int num = stoi(segment);
    if (num < 0 || num > 255) {
        return false;
    }
    count++;

    return count == 4; //vérification des 4 segments valides
}

//vérifier si une chaîne de caractères cidr représente une notation CIDR valide
bool CIDR(const string& cidr) {
    int prefix = 0; //initialisation de la variable prefix
    for (char c : cidr) { //itération de chaque caractere c de la chaine cidr
        if (c >= '0' && c <= '9') {
            prefix = prefix * 10 + (c - '0'); //si c est un chiffre, il est converti en un nombre en soustrayant le code ASCII de '0' et prefix mis à jour en étant multiplié par 10
        } else {
            return false;
        }
    }
    return (prefix >= 0 && prefix <= 32); //vérifie si prefix est entre 0 et 32 ; si c'est le cas, la fonction renvoie true sinon false
}