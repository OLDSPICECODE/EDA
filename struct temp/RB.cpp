#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void RB(string name_file, vector<vector<string>>& tb, int& state, char& state_aux) {
    ifstream in_file(name_file + to_string(state) + state_aux + ".txt");
    vector<vector<string>> n_tb;
    string a, b, c;
    if (in_file.is_open()) {
        while (!in_file.eof()) {
            in_file >> a >> b >> c;
            n_tb.push_back({ a,b,c });
        }
    }
    in_file.close();
    tb = n_tb;
    state += 1;
    state_aux = 'a';
}

void savepoint(string namefile, int& state, char& state_aux, vector<vector<string>> tb) {
    ofstream out_fi(namefile + to_string(state) + state_aux + ".txt");
    if (out_fi.is_open()) {
        for (int i = 0; i < tb.size(); i++) {
            out_fi << tb[i][0] << " " << tb[i][1] << " " << tb[i][2] << endl;
        }
    }
    out_fi.close();
    cout << "stado guardado en :";
    cout << state << " " << state_aux << endl;
    state_aux += 1;
}

int main() {
    cout << "nombre de tu tabla: ";
    string nm_file;
    vector<vector<string>> tabla;
    string c, d, f;
    int state = 0;
    char state_aux = 'a';
    cin >> nm_file;
    int op;
    cout << "opciones:" << endl << "1.- add" << endl << "2.- savepoint" << endl << "3.- rollback" << endl << "4.- imprimir tabla" << endl;
    cin >> op;
    while (op != 5) {
        if (op == 1) {
            cout << "ingresar nombre || edad || numero" << endl;
            cin >> c >> d >> f;
            tabla.push_back({ c,d,f });
        }
        else if (op == 2) {
            savepoint(nm_file, state, state_aux, tabla);
        }
        else if (op == 3) {
            int st_req;
            char st_req_a;
            cout << "que estado quiere cargar:";
            cin >> st_req >> st_req_a;
            RB(nm_file, tabla, st_req, st_req_a);
        }
        else if (op = 4) {
            for (int i = 0; i < tabla.size(); i++) {
                cout << tabla[i][0] << " " << tabla[i][1] << " " << tabla[i][2] << endl;
            }
        }
        cout << "opciones:" << endl << "1.- add" << endl << "2.- savepoint" << endl << "3.- rollback" << endl << "4.- imprimir tabla" << endl;
        cin >> op;
    }

}