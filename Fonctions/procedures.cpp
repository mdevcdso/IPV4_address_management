//Librairies C++
#include <iostream>
#include <string>
#include <sstream>

//directive qui utilise tous les noms de l'espace de noms standard std
using namespace std;

//diviser une adresse IP sous forme de chaîne de caractères en octets individuels + stockage dans un tableau d'entiers octets
void splitIPAddress(const string& ipAddress, int* octets) {
    stringstream ss(ipAddress);
    string segment;
    int index = 0;
    while (getline(ss, segment, '.')) {
        int num = stoi(segment);
        octets[index++] = num;
    }
}

//convertir un préfixe CIDR en une masque de sous-réseau
void convertCIDRToMask(int prefix, int* mask) {
    for (int i = 0; i < 4; i++) {
        if (prefix >= 8) {
            mask[i] = 255;
            prefix -= 8;
        } else if (prefix > 0) {
            mask[i] = 256 - (1 << (8 - prefix));
            prefix = 0;
        } else {
            mask[i] = 0;
        }
    }
}

//imprimer l'adresse IP sous forme de chaîne de caractères
void printIPAddress(const int* octets) {
    for (int i = 0; i < 4; i++) {
        cout << octets[i];
        if (i < 3) {
            cout << ".";
        }
    }
    cout << endl;
}

//imprimer l'adresse IP sous forme binaire
void printBinaryIPAddress(const int* octets) {
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
void printMask(const int* mask) {
    printIPAddress(mask);
}

//imprimer différentes informations liées au réseau : adresse réseau, l'adresse de diffusion, les adresses minimale et maximale des hotes, et le nombre total d'hotes dans le réseau
void printNetworkInfo(const int* ipAddress, const int* mask) {
    int networkAddress[4];
    for (int i = 0; i < 4; i++) {
        networkAddress[i] = ipAddress[i] & mask[i];
    }

    cout << "Adresse réseau : ";
    printIPAddress(networkAddress);

    cout << "Masque : ";
    printMask(mask);

    int broadcastAddress[4];
    for (int i = 0; i < 4; i++) {
        broadcastAddress[i] = ipAddress[i] | (255 - mask[i]);
    }

    cout << "Adresse de diffusion : ";
    printIPAddress(broadcastAddress);

    int hostMinAddress[4];
    for (int i = 0; i < 4; i++) {
        hostMinAddress[i] = networkAddress[i];
    }
    hostMinAddress[3] += 1;

    cout << "Adresse de l'hote minimum : ";
    printIPAddress(hostMinAddress);

    int hostMaxAddress[4];
    for (int i = 0; i < 4; i++) {
        hostMaxAddress[i] = broadcastAddress[i];
    }
    hostMaxAddress[3] -= 1;

    cout << "Adresse de l'hote maximum : ";
    printIPAddress(hostMaxAddress);

    int totalHosts = 1;
    for (int i = 0; i < 4; i++) {
        totalHosts *= (i == 3) ? (hostMaxAddress[i] - hostMinAddress[i] + 1) : 256;
    }

    cout << "Nombre total d'hotes : " << totalHosts << endl;
} 