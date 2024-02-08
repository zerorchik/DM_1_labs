#include <iostream>
#include <windows.h>
#include <random>
#include <string>
using namespace std;

float n, m;
int a[20][20], inz[20][20], sum[20][20];
string str;
char t;

void generate() {
    random_device random_device; // entropy sourse
    mt19937 generator(random_device()); // initialise randimizer
    cout << "Вершин: ";
    cin >> n;
    if (n <= 0 || (n - int(n)) != 0) {
        cout << "\n----------------------------\nN - не удовлетворяет условие\n----------------------------\n";
        exit(0);
    }
    uniform_int_distribution<> distribution(1, n);
    cout << "Ребер: ";
    cin >> m;
    if (m <= 0 || (m - int(m)) != 0) {
        cout << "\n----------------------------\nM - не удовлетворяет условие\n----------------------------\n";
        exit(0);
    }
    cout << "\n";
    // define work type
    cout << "Сгенерирровать граф или задать вручную (0/1): ";
    cin >> t;
    switch (t) {
        case '0':
            t = '0';
            break;
        case '1':
            cout << "\n\nСПИСОК РЕБЕР:";
            cout << "\n-------------\n";
            for (int i = 0; i < m; i++) {
                cout << "e" << i + 1 << " = ";
                for (int j = 0; j < 2; j++) {
                    cin >> a[i][j];
                    if (a[i][j] >= 1 && a[i][j] <= n) {
                        continue;
                    }
                    else {
                        cout << "\n------------------------------\nV"<<a[i][j]<<" - НЕ является точкой графа\n------------------------------\n";
                        exit(0);
                    }
                }
            }
            cout << "\n\n";
            break;
        default:
            cerr << "\n----------------------------------------------\n";
            cerr << "Неправильный тип работы программы, введите:\n0 - чтоб сгенерировать граф\n1 - чтоб задать его вручную";
            cerr << "\n----------------------------------------------\n";
            exit(0);
    }
    if (t == '0') {
        // generate
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < 2; j++) {
                a[i][j] = distribution(generator);
            }
        }
    }
}
void output() {
    if (t == '0') {
        cout << "СПИСОК РЕБЕР:";
        cout << "\n-----------------\n";
        for (int i = 0; i < m; i++) {
            str = "   ";
            // 10-99 numbs
            if (i >= 9) {
                cout << "e" << i + 1 << " = (";
            }
            // 1-9 numbs
            else {
                cout << "e" << i + 1 << "  = (";
            }
            for (int j = 0; j < 2; j++) {
                if (j < 1) {
                    // 10-99 numbs
                    if (((a[i][j] / 10) != 0) && (a[i][j] / 10) <= 9) {
                        str = "  ";
                    }
                    // 100-999 numbs
                    else if (((a[i][j] / 10) != 0) && (a[i][j] / 10) > 9 && (a[i][j] / 10) <= 99) {
                        str = " ";
                    }
                    cout << "v" << a[i][j] << "," << str;
                }
                else {
                    cout << "v" << a[i][j] << ")\n";
                }
            }
        }
        cout << "\n\n";
    }
}
void inz_matr() {
    cout << "ИНЦИДЕНТНАЯ МАТРИЦА:\n";
    cout << "-----";
    for (int i = 0; i < m; i++) {
        cout << "--------";
        if (a[i][0] != a[i][1]) {
            inz[a[i][0]][i] = -1;
            inz[a[i][1]][i] = 1;
        }
        else {
            inz[a[i][0]][i] = 2;
        }
    }
    cout << "\n";
    // print inz matr
    for (int t = 0; t < m; t++) {
        // first interpr
        if (t == 0) {
            cout << "     |\t";
        }
        // 10-99 numbs
        if (t + 1 > 9) {
            cout << "e" << t + 1 << " |\t";
        }
        // 1-9 numbs
        else {
            cout << "e" << t + 1 << "  |\t";
        }
    }
    cout << "\n";
    for (int s = 0; s < n; s++) {
        // skelet of the tabl
        for (int l = 0; l < m; l++) {
            if (l == 0) {
                cout << "-----";
                cout << "--------";
            }
            else {
                cout << "--------";
            }
        }
        cout << "\n";
        for (int k = 0; k < m; k++) {
            // first interpr
            if (k == 0) {
                // 10-99 numbs
                if (s + 1 > 9) {
                    cout << " v" << s + 1 << " |\t";
                }
                // 1-9 numbs
                else {
                    cout << "  v" << s + 1 << " |\t";
                }
            }
            // 10-99 numbs
            if (inz[s + 1][k] >= 0) {
                cout << inz[s + 1][k] << "   |\t";
            }
            // 1-9 numbs
            else {
                cout << inz[s + 1][k] << "  |\t";
            }
        }
        cout << "\n";
    }
    cout << "\n\n";
}
void sum_matr() {
    cout << "СМЕЖНАЯ МАТРИЦА:\n";
    for (int i = 0; i < m; i++) {
        sum[a[i][0]][a[i][1]] = 1;
    }
    // print
    for (int b = 0; b < n; b++) {
        if (b == 0) {
            cout << "-----";
            cout << "--------";
        }
        else {
            cout << "--------";
        }
    }
    cout << "\n";
    for (int s = 0; s < n; s++) {
        // first interpr
        if (s == 0) {
            // names of tables
            for (int f = 0; f < n; f++) {
                // first interpr
                if (f == 0) {
                    cout << "     |\t";
                }
                // 10-99 numbs
                if (f >= 9) {
                    cout << "v" << f + 1 << " |\t";
                }
                // 1-9 numbs
                else {
                    cout << "v" << f + 1 << "  |\t";
                }
            }
            cout << "\n";
        }
        // skelet of the tabl
        for (int l = 0; l < n; l++) {
            if (l == 0) {
                cout << "-----";
                cout << "--------";
            }
            else {
                cout << "--------";
            }
        }
        cout << "\n";
        for (int k = 0; k < n; k++) {
            // first interpr
            if (k == 0) {
                // 10-99 numbs
                if (s + 1 > 9) {
                    cout << " v" << s + 1 << " |\t";
                }
                // 1-9 numbs
                else {
                    cout << "  v" << s + 1 << " |\t";
                }
            }
            cout << sum[s+1][k+1] << "   |\t";
        }
        cout << "\n";
    }
}
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    generate();
    output();
    inz_matr();
    sum_matr();
}