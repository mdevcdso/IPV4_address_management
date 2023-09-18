//Librairies de base en C++
#include <iostream>
#include <string>

//directive qui utilise tous les noms de l'espace de noms standard std
using namespace std;

//declaration de la variable menu avec enonciation des differentes options
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
bool AdresseIP(const string adressIP) {
    string segment;
    int count = 0;

    for (char i : adressIP) { //les caracteres de adresseIP seront associés à l'index i
        if (i == '.') {
            if (segment.empty() || !EstNumerique(segment)) { //cas où l'utilisateur ne met que des points
                return false;
            }
            int num = stoi(segment); //conversion de la chaine segment en entier
            if (num < 0 || num > 255) {
                return false;
            }
            segment.clear();
            count++;
        } else if (isdigit(i)) { //cas où i est un nombre decimal entre 0 et 9
            segment += i; //concaténation des chiffres rencontrés dans la chaine segment
        } else {
            return false;
        }
    }

    if (segment.empty() || !EstNumerique(segment)) {
        return false;
    }
    int num = stoi(segment); //conversion de la chaine segment en entier
    if (num < 0 || num > 255) {
        return false;
    }
    count++;

    return count == 4;
}

//vérifier si une chaîne de caractères cidr représente une notation CIDR valide
bool CIDR(const string cidr) {
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

//division d'une adresse ip en octets avec '.' en séparateur
void diviseAdresseIP(const string adresseIP, int octets[]) {
    string segment;
    int index = 0;

    for (char i : adresseIP) {
        if (i == '.') { //si un caractère est un point, segment terminé
            octets[index++] = stoi(segment);
            segment.clear(); //reinitialise le segment pour le prochain octet
        } else {
            segment += i; 
        }
    }
    octets[index] = stoi(segment);
}

//conversion du prefixe CIDR en un masque de sous-reseau
void convertirCIDREnMasque(int prefix, int masqueOctets[]) {
    int mask = 0xFFFFFFFF << (32 - prefix); //creation d'un masque avec les bits de prefixe à 1
    masqueOctets[0] = (mask >> 24) & 0xFF; //récupère les octets du masque de sous-réseau
    masqueOctets[1] = (mask >> 16) & 0xFF;
    masqueOctets[2] = (mask >> 8) & 0xFF;
    masqueOctets[3] = mask & 0xFF;
}

//verification de si la chaine contient uniquement des chiffres
bool EstNumerique(const string str) {
    for (char c : str) { //boucle de chaque caractères sur la chaine
        if (!isdigit(c)) { //retourne si un caractère n'est pas un chiffre
            return false;
        }
    }
    return true; //retourne si la chaine est composée de chiffres uniquement
}

//afficher adresse ip
void genererAddressIP(int octets[]) {
    cout << octets[0] << "." << octets[1] << "." << octets[2] << "." << octets[3] << endl;
}

//afficher masque de sous réseau
void genererMasque(int octets[]) {
    cout << octets[0] << "." << octets[1] << "." << octets[2] << "." << octets[3] << endl;
}

//afficher les informations concernant le réseau
void genererInfoReseau(int ipOctets[], int maskOctets[]) {
    int networkAddress[4];

    //stocker les octets de l'ip ET du masque dans la variable networkAddress pour l'adresse réseau
    for (int i = 0; i < 4; i++) {
        networkAddress[i] = ipOctets[i] & maskOctets[i]; 
    }

    cout << "Adresse réseau : ";
    genererAddressIP(networkAddress);

    cout << "Masque : ";
    genererMasque(maskOctets);

    int broadcastAddress[4];
    for (int i = 0; i < 4; i++) {
        broadcastAddress[i] = ipOctets[i] | (255 - maskOctets[i]); //récupérer les octets correspondant à l'adresse de broadcast
    }

    cout << "Adresse de diffusion : ";
    genererAddressIP(broadcastAddress);

    //generer la plage d'adresses ip
    int hostMinAddress[4];
    for (int i = 0; i < 4; i++) {
        hostMinAddress[i] = networkAddress[i];
    }
    hostMinAddress[3] += 1;

    cout << "Adresse de l'hote minimum : ";
    genererAddressIP(hostMinAddress);

    int hostMaxAddress[4];
    for (int i = 0; i < 4; i++) {
        hostMaxAddress[i] = broadcastAddress[i];
    }
    hostMaxAddress[3] -= 1;

    cout << "Adresse de l'hote maximum : ";
    genererAddressIP(hostMaxAddress);

    //calcul le nombre d'adresses hôte possibles
    int totalHosts = 1;
    for (int i = 0; i < 4; i++) {
        totalHosts *= (i == 3) ? (hostMaxAddress[i] - hostMinAddress[i] + 1) : 256;
    }

    cout << "Nombre total d'hotes : " << totalHosts << endl;
}

//conversion d'une ip décimale en binaire
void genererAdresseIPBinaire(int octets[]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 7; j >= 0; j--) {
            int bit = (octets[i] >> j) & 1;
            cout << bit;
        }
        if (i < 3) {
            cout << ".";
        }
    }
    cout << endl;
}