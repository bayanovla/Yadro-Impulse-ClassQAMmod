#include <iostream>
#include <vector>
#include <complex>

using namespace std;

class ClassQAMMod {
private:
    int M;
public:
    ClassQAMMod(int M) : M(M) {}

    vector<complex<double> > modulate(const vector<int> & bits) {
        int Ns = bits.size() / log2(M);
        vector<complex<double> > symbols(Ns);
        vector <int> table;
        int Eavg;

        if (M == 4) {
            table.push_back(-1);
            table.push_back(1);
            Eavg = 2;
        } else if (M == 16) {
            table.push_back(-3);
            table.push_back(-1);
            table.push_back(3);
            table.push_back(1);
            Eavg = 10;

        } else if (M == 64) {
            table.push_back(-7);
            table.push_back(-5);
            table.push_back(-1);
            table.push_back(-3);
            table.push_back(7);
            table.push_back(5);
            table.push_back(1);
            table.push_back(3);
            Eavg = 42;
        } else if (M == 256) {
            table.push_back(-15);
            table.push_back(-13);
            table.push_back(-9);
            table.push_back(-11);
            table.push_back(-1);
            table.push_back(-3);
            table.push_back(-7);
            table.push_back(-5);
            table.push_back(15);
            table.push_back(13);
            table.push_back(9);
            table.push_back(11);
            table.push_back(1);
            table.push_back(3);
            table.push_back(7);
            table.push_back(5);
            Eavg = 170;
        }
        for (int i = 0, k = 0; i < Ns; i++, k += log2(M)) {
            int I_idx = 0, Q_idx = 0;
            for (int j = 0; j < log2(M) / 2; j++) {
                I_idx += bits[k + j] * pow(2, (log2(M) / 2 - 1 - j));
                Q_idx += bits[k + log2(M) / 2 + j] * pow(2, (log2(M) / 2 - 1 - j));
            }
            symbols[i] = complex<double>(table[I_idx], table[Q_idx]) / sqrt(Eavg);
        }
        return symbols;
    }
};
