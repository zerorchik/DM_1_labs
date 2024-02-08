#include <iostream>
#include <windows.h>
#include <random>
#include <string>
using namespace std;

float n, m;
int a[20][20], sum[20][20], d[20], d_plus[20], d_minus[20], izo[20], vus[20]; // massiv for sum in row and colmn, izolated and hangigng peaks
int sumr, sumc, od, c_izo, c_vus; // sum of ell in row and colmn, definder of odnor, couter of izolated and hangigng peaks
string str;
char t;

void generate() {
    random_device random_device; // entropy sourse
    mt19937 generator(random_device()); // initialise randimizer
    cout << "Âåðøèí: ";
    cin >> n;
    if (n <= 0 || (n - int(n)) != 0) {
        cout << "\n----------------------------\nN - íå óäîâëåòâîðÿåò óñëîâèå\n----------------------------\n";
        exit(0);
    }
    uniform_int_distribution<> distribution(1, n);
    cout << "Ðåáåð: ";
    cin >> m;
    if (m <= 0 || (m - int(m)) != 0) {
        cout << "\n----------------------------\nM - íå óäîâëåòâîðÿåò óñëîâèå\n----------------------------\n";
        exit(0);
    }
    cout << "\n";
    // define work type
    cout << "Ñãåíåðèððîâàòü ãðàô èëè çàäàòü âðó÷íóþ (0/1): ";
    cin >> t;
    switch (t) {
    case '0':
        t = '0';
        break;
    case '1':
        cout << "\n\nÑÏÈÑÎÊ ÐÅÁÅÐ:";
        cout << "\n-------------\n";
        for (int i = 0; i < m; i++) {
            if (i + 1 > 9) {
                cout << "e" << i + 1 << " = ";
            }
            else {
                cout << "e" << i + 1 << "  = ";
            }
            for (int j = 0; j < 2; j++) {
                cin >> a[i][j];
                if (a[i][j] >= 1 && a[i][j] <= n) {
                    continue;
                }
                else {
                    cout << "\n------------------------------\nV" << a[i][j] << " - ÍÅ ÿâëÿåòñÿ òî÷êîé ãðàôà\n------------------------------\n";
                    exit(0);
                }
            }
        }
        cout << "\n\n";
        break;
    default:
        cerr << "\n----------------------------------------------\n";
        cerr << "Íåïðàâèëüíûé òèï ðàáîòû ïðîãðàììû, ââåäèòå:\n0 - ÷òîá ñãåíåðèðîâàòü ãðàô\n1 - ÷òîá çàäàòü åãî âðó÷íóþ";
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
        cout << "\nÑÏÈÑÎÊ ÐÅÁÅÐ:";
        cout << "\n----------------\n";
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
void sumizhna_matr() {
    cout << "ÑÌÅÆÍÀß ÌÀÒÐÈÖÀ \nÈ ÏÎËÓÑÒÅÏÅÍÈ ÂÅÐØÈÍ (âõîäà+ è âûõîäà-):\n";
    for (int i = 0; i < m; i++) {
        sum[a[i][0]][a[i][1]] = 1;
    }
    // to define -degree of peaks
    for (int i = 0; i <= m; i++) {
        sumr = 0;
        for (int j = 0; j <= m; j++) {
            sumr += sum[i][j];
        }
        d_minus[i] = sumr;
    }
    // to define +degree of peaks
    for (int i = 0; i <= m; i++) {
        sumc = 0;
        for (int j = 0; j <= m; j++) {
            sumc += sum[j][i];
        }
        d_plus[i] = sumc;
    }
    // to define full degree of peaks
    for (int i = 0; i <= n; i++) {
        d[i] = d_plus[i] + d_minus[i];
    }
    // print
    for (int b = 0; b <= n; b++) {
        if (b == 0) {
            cout << "----------";
            cout << "----------";
        }
        else {
            cout << "----------";
        }
    }
    cout << "\n";
    for (int s = 0; s <= n; s++) {
        // first interpr
        if (s == 0) {
            // names of tables
            for (int f = 0; f <= n; f++) {
                // first interpr
                if (f == 0) {
                    cout << "         |";
                }
                // last interpr
                if (f == n) {
                    cout << "  d-(vi) |";
                    continue;
                }
                // 10-99 numbs
                if (f >= 9) {
                    cout << "    v" << f + 1 << "  |";
                }
                // 1-9 numbs
                else {
                    cout << "    v" << f + 1 << "   |";
                }
            }
            cout << "\n";
        }
        // skelet of the tabl
        for (int l = 0; l <= n; l++) {
            if (l == 0) {
                cout << "----------";
                cout << "----------";
            }
            else {
                cout << "----------";
            }
        }
        cout << "\n";
        for (int k = 0; k <= n; k++) {
            // first interpr
            if (k == 0) {
                if (s == n) {
                    cout << "  d+(vi) |";
                    continue;
                }
                // 10-99 numbs
                if (s + 1 > 9) {
                    cout << "   v" << s + 1 << "   |";
                }
                // 1-9 numbs
                else {
                    cout << "    v" << s + 1 << "   |";
                }
            }
            // print degree- of peaks
            if (k == n && s!=n) {
                cout << "    " << d_minus[s + 1] << "    |";
            }
            // print degree+ of peaks
            else if (s == n) {
                cout << "    " << d_plus[k] << "    |";
            }
            // print matrix el
            else {
                cout << "    " << sum[s + 1][k + 1] << "    |";
            }
        }
        cout << "\n";
    }
}
void pecksFullDegree() {
    cout << "\n\nÑÒÅÏÅÍÈ ÂÅÐØÈÍ:\n---------------\n";
    for (int i = 0; i < n; i++) {
        // define odnor
        // prev deg = curr deg
        if (i > 0 && d_minus[i] == d_plus[i] && od != -1) {
            od = 1;
        }
        // first interpr
        else if (i == 0) {
            od = 0;
        }
        // prev deg != curr deg
        else {
            od = -1;
        }
        // define izol
        if (d[i + 1] == 0) {
            izo[c_izo] = i + 1;
            c_izo++;
        }
        // define vusyacha
        else if (d[i + 1] == 1) {
            vus[c_vus] = i + 1;
            c_vus++;
        }
        // print full degrees
        // 10-99 numbs 
        if (i + 1 > 9) {
            cout << "d(v" << i + 1 << ") = " << d[i + 1] << "\n";
        }
        // 1-9 numbs
        else {
            cout << "d(v" << i + 1 << ")  = " << d[i + 1] << "\n";
        }
    }
    cout << "\n\n";
}
void peaksHalfDegree() {
    cout << "\n\nÏÎËÓÑÒÅÏÅÍÈ ÂÕÎÄÀ:\n------------------\n";
    for (int i = 0; i < n; i++) {
        // 10-99 numbs
        if (i + 1 > 9) {
            cout << "d+(v" << i + 1 << ") = " << d_plus[i + 1] << "\n";
        }
        // 1-9 numbs
        else {
            cout << "d+(v" << i + 1 << ")  = " << d_plus[i + 1] << "\n";
        }
    }
    cout << "\n\nÏÎËÓÑÒÅÏÅÍÈ ÂÛÕÎÄÀ:\n-------------------\n";
    for (int i = 0; i < n; i++) {
        // 10-99 numbs
        if (i + 1 > 9) {
            cout << "d-(v" << i + 1 << ") = " << d_minus[i + 1] << "\n";
        }
        // 1-9 numbs
        else {
            cout << "d-(v" << i + 1 << ")  = " << d_minus[i + 1] << "\n";
        }
    }
}
void odnor() {
    // odnorodniy
    if (od == 1) {
        cout << "ÃÐÀÔ - ÎÄÍÎÐÎÄÍÛÉ ÑÎ ÑÒÅÏÅÍÜÞ " << d_minus[1] << "\n\n\n";
    }
    // nope
    else {
        cout << "ÃÐÀÔ - ÍÅ ÎÄÍÎÐÎÄÍÛÉ\n\n\n";
    }
}
void izol_vus() {
    // exist izol 
    if (c_izo != 0) {
        cout << "ÈÇÎËÈÐÎÂÀÍÛÅ ÂÅÐØÈÍÛ:\n---------------------\n";
        for (int i = 0; i < c_izo; i++) {
            cout << "v" << izo[i] << "\n";
        }
        cout << "\n\n";
    }
    // nope 
    else {
        cout << "ÈÇÎËÈÐÎÂÀÍÛÕ ÂÅÐØÈÍ - ÍÅÒ\n\n\n";
    }
    // exist vusyach
    if (c_vus != 0) {
        cout << "ÂÈÑß×ÈÅ ÂÅÐØÈÍÛ:\n----------------\n";
        for (int i = 0; i < c_vus; i++) {
            cout << "v" << vus[i] << "\n";
        }
        cout << "\n\n";
    }
    // nope
    else {
        cout << "ÂÈÑß×ÈÕ ÂÅÐØÈÍ - ÍÅÒ\n\n\n";
    }
}
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    generate();
    output();
    sumizhna_matr();
    peaksHalfDegree();
    pecksFullDegree();
    odnor();
    izol_vus();
}