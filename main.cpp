#include<iostream>
#include<vector>
#include<string>
#include <random>
#include <time.h>
#include <iomanip>

using namespace std;

int distancia(vector<int> punto_1, vector<int> punto_2) {
    unsigned long long int result = 0;
    for (int i = 0; i < punto_1.size(); i++) {
        result += (punto_1[i] - punto_2[i]) * (punto_1[i] - punto_2[i]);
    }
    return sqrt(result);
}

vector<int> generador(int dim) {
    vector<int> result;
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    for (int i = 0; i < dim; i++) {
        std::uniform_int_distribution<> distrib(1, 100);
        result.push_back(distrib(gen));
    }
    return result;
}

int main() {
    srand(time(NULL));
    int dim;
    cout << "dimensiones: " << endl;
    cin >> dim;
    vector<vector<int>> puntos;
    for (int i = 0; i < 20000; i++) {
        puntos.push_back(generador(dim));
    }
    vector<int> dists;
    for (int i = 0; i < 20000; i++) {
        dists.push_back(distancia(puntos[0], puntos[i]));
    }

    for (int i = 0; i < puntos[0].size(); i++) {
        cout << puntos[10000][i] << " ";
    }
    cout << endl;
    vector<vector<int>> hist;
    int cont = 0;
    int aux = 0;
    for (int i = 0; i < dists.size(); i++) {
        if (dists[i] != -1) {
            aux = dists[i];
            for (int j = i; j < dists.size(); j++) {
                if (dists[j] == aux) {
                    cont += 1;
                    dists[j] = -1;
                }
            }
            hist.push_back({ aux,cont });
            cont = 0;
        }
    }
    for (int i = 0; i < hist.size(); i++) {
        cout << hist[i][0] << " " << hist[i][1] << endl;
    }
}