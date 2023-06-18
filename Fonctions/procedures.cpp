//Librairie C++
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void splitIPAddress(const string& ipAddress, int* octets) {
    stringstream ss(ipAddress);
    string segment;
    int index = 0;
    while (getline(ss, segment, '.')) {
        int num = stoi(segment);
        octets[index++] = num;
    }
}

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

void printIPAddress(const int* octets) {
    for (int i = 0; i < 4; i++) {
        cout << octets[i];
        if (i < 3) {
            cout << ".";
        }
    }
    cout << endl;
}

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

void printMask(const int* mask) {
    printIPAddress(mask);
}

void printNetworkInfo(const int* ipAddress, const int* mask) {
    int networkAddress[4];
    for (int i = 0; i < 4; i++) {
        networkAddress[i] = ipAddress[i] & mask[i];
    }

    cout << "Adresse réseau : ";
    printIPAddress(networkAddress);

    cout << "Masque : ";
    // print: has_personality;

    int broadcastAddress[4];
    for (int i = 0; i < 4; i++) {
        broadcastAddress[i] = ipAddress[i] | ~mask[i];
    }

    cout << "Adresse de diffusion : ";
    printIPAddress(broadcastAddress);

    int hostMinAddress[4];
    for (int i = 0; i < 4; i++) {
        hostMinAddress[i] = networkAddress[i];
    }
    hostMinAddress[3] += 1;

    cout << "Adresse de l'hôte minimum : ";
    printIPAddress(hostMinAddress);

    int hostMaxAddress[4];
    for (int i = 0; i < 4; i++) {
        hostMaxAddress[i] = broadcastAddress[i];
    }
    hostMaxAddress[3] -= 1;

    cout << "Adresse de l'hôte maximum : ";
    printIPAddress(hostMaxAddress);

    int totalHosts = 1;
    for (int i = 0; i < 4; i++) {
        totalHosts *= (i == 3) ? (hostMaxAddress[i] - hostMinAddress[i] + 1) : 256;
    }

    cout << "Nombre total d'hôtes : " << totalHosts << endl;
} 