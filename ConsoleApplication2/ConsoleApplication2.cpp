#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>

#include <boost/multiprecision/cpp_int.hpp>
using boost::multiprecision::cpp_int;

using namespace std;

class Rsa {
public:
    unsigned p;
    unsigned q;
    unsigned n;
    unsigned phi_n;
    unsigned e;
    unsigned d;
    unsigned m;
    boost::multiprecision::cpp_int c;
    // encrypt m^e mod(n) = c
    // decrypt c^d mod(n) = m_0
    boost::multiprecision::cpp_int m_0;

    void prompt();
    void prime_check();
    unsigned calculate_n();
    unsigned calculate_phi_n();
    unsigned calculate_d();

    boost::multiprecision::cpp_int encrypt();
    boost::multiprecision::cpp_int decrypt();

};

void Rsa::prompt() {
    cout << "Enter the p: " << endl;
    cin >> p;
    cout << "Enter the q: " << endl;
    cin >> q;
    cout << "Enter the e: " << endl;
    cin >> e;
    cout << "To encrypt, enter the message: " << endl;
    cin >> m;
}

void Rsa::prime_check() {
    vector<unsigned> p_check;
    for (unsigned i = 2; i <= static_cast<unsigned>(sqrt(p)); i++) {
        if (p % i == 0) {
            p_check.push_back(i);
            p_check.push_back(p / i);
        }
    }
    vector<unsigned> q_check;
    for (unsigned i = 2; i <= static_cast<unsigned>(sqrt(q)); i++) {
        if (q % i == 0) {
            q_check.push_back(i);
            q_check.push_back(q / i);
        }
    }
    if (p_check.size() != 0 || q_check.size() != 0) {
        throw (runtime_error("not a primery number"));
    }
}

unsigned Rsa::calculate_n() {
    n = p * q;
    return n;
}

unsigned Rsa::calculate_phi_n() {
    phi_n = (p - 1) * (q - 1);
    return phi_n;
}

unsigned Rsa::calculate_d() {
    // (e*d) mod phi_n = 1
    // 17d mod (60*52 = 3120) = 1
    // 3120 + 1 or x (e*2 || e*3 || e*4...) + 1 mod 3120 = 1 then x = 1
    unsigned x = 1;
    while (((x * phi_n) + 1) % e != 0) { // find x in order to find d
        x++;
    }
    d = ((x * phi_n) + 1) / e;
    return d;
}

boost::multiprecision::cpp_int Rsa::encrypt() {
    c = (boost::multiprecision::cpp_int(boost::multiprecision::pow(boost::multiprecision::cpp_int(m), e))) % n;

    return c;
}

boost::multiprecision::cpp_int Rsa::decrypt() {
    m_0 = (boost::multiprecision::cpp_int(boost::multiprecision::pow(boost::multiprecision::cpp_int(c), d))) % n;

    return m_0;
}

int main(int argc, const char* argv[])
{
    try {
        Rsa en_d;
        en_d.prompt();
        en_d.prime_check();
        cout << "The n: " << en_d.calculate_n() << endl;
        cout << "The phi_n: " << en_d.calculate_phi_n() << endl;
        cout << "The d: " << en_d.calculate_d() << endl;
        cout << "Encrypted: " << en_d.encrypt() << endl;
        cout << "Decrypted: " << en_d.decrypt() << endl;
    }
    catch (runtime_error& s) {
        cout << s.what() << endl;
    }

    return 0;
}
