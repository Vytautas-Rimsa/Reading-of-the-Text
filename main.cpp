/* Susirasti anglu kalba parasyta teksta (10 000 zodziu). Is jo perskaityti
visus zodzius. Kiekvienam perskaitytam zodziui suskaiciuoti raidziu skaiciu.
Duomenu pora (zodis ir raidziu skaicius) issaugoti MAP tipo konteineryje,
isdestant duomenis zodzio ilgio didejimo kryptimi. Gautus duomenis isvesti i
faila. Nuskaityti 100 dazniausiu zodziu. Naudoti biblioteka iostream, string,
map.*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

struct more_second { //naudojama elementu rikiavimui mazejanciai
    bool operator ()(pair<string, int> const& a, pair<string, int> const& b) const {
        return a.second > b.second;
    }
};

struct less_second { //naudojama elementu rikiavimui didejanciai
    bool operator ()(pair<string, int> const& a, pair<string, int> const& b) const {
        return a.second < b.second;
    }
};

class AngliskasVadovas {
private:
    vector<pair<string, int> > ilgisZodziuVektorius; //saugo zodzius ir ju ilgi
    vector<pair<string, int> > kiekZodziuVektorius; //saugo zodzius ir kiek kartu pasikartojo
public:
    void irasyti(string failas);
    void ivesti(string failas);
};

int main() {
    AngliskasVadovas dievas;
    dievas.ivesti("in.txt");
    dievas.irasyti("out.txt");
    system("pause");
    return EXIT_SUCCESS;
}

void AngliskasVadovas::irasyti(string failas)
{
    ofstream outf(failas.c_str());
    outf << "Zodziai ir ju ilgis" << endl;
    for (vector<pair<string, int> >::iterator iterator = ilgisZodziuVektorius.begin(); iterator != ilgisZodziuVektorius.end(); iterator++) {
        outf << iterator->first << " " << iterator->second << endl;
    }
    outf << "Dazniausi 100 zodziu ir ju pasikartojimu skaicius" << endl;
    int i = 1;
    for (vector<pair<string, int> >::iterator iterator = kiekZodziuVektorius.begin(); iterator != kiekZodziuVektorius.end(); iterator++) {
        outf << i<<". "<< iterator->first << " " << iterator->second << endl;
        if (i == 100)
            break;
        i++;
    }
    outf.close();
}

void AngliskasVadovas::ivesti(string failas)
{
    string ivedimoZodis;
    ifstream in(failas.c_str());
    map<string, int> kiekisZodziai;
    map<string, int> ilgisZodziai;
    while (!in.eof()) {
        in >> ivedimoZodis;
        transform(ivedimoZodis.begin(), ivedimoZodis.end(), ivedimoZodis.begin(), ::tolower); //zodi pavercia mazosomis raidemis
        ivedimoZodis.erase(std::remove(ivedimoZodis.begin(), ivedimoZodis.end(), ','), ivedimoZodis.end());//filtruoja simbolius simboliu eiluteje
        ivedimoZodis.erase(std::remove(ivedimoZodis.begin(), ivedimoZodis.end(), '.'), ivedimoZodis.end());
        ivedimoZodis.erase(std::remove(ivedimoZodis.begin(), ivedimoZodis.end(), '['), ivedimoZodis.end());
        ivedimoZodis.erase(std::remove(ivedimoZodis.begin(), ivedimoZodis.end(), ']'), ivedimoZodis.end());
        ivedimoZodis.erase(std::remove(ivedimoZodis.begin(), ivedimoZodis.end(), '('), ivedimoZodis.end());
        ivedimoZodis.erase(std::remove(ivedimoZodis.begin(), ivedimoZodis.end(), '?'), ivedimoZodis.end());
        ivedimoZodis.erase(std::remove(ivedimoZodis.begin(), ivedimoZodis.end(), '!'), ivedimoZodis.end());
        ivedimoZodis.erase(std::remove(ivedimoZodis.begin(), ivedimoZodis.end(), '!'), ivedimoZodis.end());
        ivedimoZodis.erase(std::remove(ivedimoZodis.begin(), ivedimoZodis.end(), '!'), ivedimoZodis.end());
        ilgisZodziai[ivedimoZodis] = ivedimoZodis.size();//issaugome zodi
        if (kiekisZodziai.count(ivedimoZodis) == 0) {
            kiekisZodziai[ivedimoZodis] = 1;
        }
        else {
            kiekisZodziai[ivedimoZodis] += 1;
        }
    }
    for (map<string, int>::iterator it = kiekisZodziai.begin(); it != kiekisZodziai.end(); ++it) { //perkopijuojam reiksmes is map i vektoriu kad galetumem isrikiuoti
        pair<string, int> pora(it->first, it->second);
        kiekZodziuVektorius.push_back(pora);
    }
    std::sort(kiekZodziuVektorius.begin(), kiekZodziuVektorius.end(), more_second()); //rikiuojam
    for (map<string, int>::iterator it = ilgisZodziai.begin(); it != ilgisZodziai.end(); ++it) {
        pair<string, int> pora(it->first, it->second);
        ilgisZodziuVektorius.push_back(pora);
    }
    std::sort(ilgisZodziuVektorius.begin(), ilgisZodziuVektorius.end(), less_second());
    in.close();
}
