//Librairies C++
#include <iostream>
#include <string>
#include <sstream>

//directive qui utilise tous les noms de l'espace de noms standard std
using namespace std;

//diviser une adresse IP sous forme de chaîne de caractères en octets individuels + stockage dans un tableau d'entiers octets
void diviseAdresseIP(const string& adresseIP, int* octets) {
    stringstream ss(adresseIP);
    string segment;
    int index = 0;
    while (getline(ss, segment, '.')) {
        int num = stoi(segment);
        octets[index++] = num;
    }
}

//convertir un préfixe CIDR en une masque de sous-réseau
void convertirCIDREnMasque(int prefix, int* masque) {
    for (int i = 0; i < 4; i++) {
        if (prefix >= 8) {
            masque[i] = 255;
            prefix -= 8;
        } else if (prefix > 0) {
            masque[i] = 256 - (1 << (8 - prefix));
            prefix = 0;
        } else {
            masque[i] = 0;
        }
    }
}

//génère l'adresse IP sous forme de chaîne de caractères
void genererAddressIP(const int* octets) {
    for (int i = 0; i < 4; i++) {
        cout << octets[i];
        if (i < 3) {
            cout << ".";
        }
    }
    cout << endl;
}

//génère l'adresse IP sous forme binaire
void genererAdresseIPBinaire(const int* octets) {
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

//imprimer le masque de sous-réseau
void genererMasque(const int* masque) {
    genererAddressIP(masque);
}

//imprimer différentes informations liées au réseau : adresse réseau, l'adresse de diffusion, les adresses minimale et maximale des hotes, et le nombre total d'hotes dans le réseau
void printNetworkInfo(const int* adresseIP, const int* masque) {
    int networkAddress[4];
    for (int i = 0; i < 4; i++) {
        networkAddress[i] = adresseIP[i] & masque[i];
    }

    cout << "Adresse réseau : ";
    genererAddressIP(networkAddress);

    cout << "Masque : ";
    genererMasque(masque);

    int broadcastAddress[4];
    for (int i = 0; i < 4; i++) {
        broadcastAddress[i] = adresseIP[i] | (255 - masque[i]);
    }

    cout << "Adresse de diffusion : ";
    genererAddressIP(broadcastAddress);

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

    int totalHosts = 1;
    for (int i = 0; i < 4; i++) {
        totalHosts *= (i == 3) ? (hostMaxAddress[i] - hostMinAddress[i] + 1) : 256;
    }

    cout << "Nombre total d'hotes : " << totalHosts << endl;
} 