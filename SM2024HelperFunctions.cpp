#include <iostream>
#include <fstream>
#include <vector>

#include "SM2024HelperFunctions.h"
#include "SM2024KeyFunctions.h"
#include "SM2024Variables.h"
#include "SM2024CoreFunctions.h"

using namespace std;

int normalizacja(int wartosc, int minimum, int maximum){

    int wynik = wartosc;
    if(wynik < minimum)wynik = minimum;
    if(wynik > maximum)wynik = maximum;

    return wynik;
}

bool porownajKolory(SDL_Color kolor1, SDL_Color kolor2){
    if(kolor1.r != kolor2.r)
        return false;
    if(kolor1.g != kolor2.g)
        return false;
    if(kolor1.b != kolor2.b)
        return false;

    return true;
}

Uint8 shiftByte(Uint8 b, Uint8 shiftAmount) {
    b = b << 8 - shiftAmount;
    return b;
}

float calculateSaturation(float minimum, float maximum, float luminance){
    if (minimum == maximum) return 0;

    if (luminance <= 0.5) return (maximum - minimum) / (maximum + minimum);

    if (luminance  > 0.5) return (maximum - minimum) / (2.0 - maximum - minimum);

    cout << "ERROR: Unexpected event when calculating saturation!\n";
    return 0;
}

float calculateHue(float r, float g, float b, float minimum, float maximum){

    if(r == maximum) return ((g - b) / (maximum - minimum)) * 60;

    if(g == maximum) return (2.0 + (b - r) / (maximum - minimum)) * 60;

    if(b == maximum) return (4.0 + (r - g) / (maximum - minimum)) * 60;

    cout << "ERROR: Unexpected event when calculating hue!\n";
    return 0;
}

int calculateHSLtoRGBMethod(float x){
    if ( (6.0 * x) < 1.0 ) return 1;
    if ( (2.0 * x) < 1.0 ) return 2;
    if ( (3.0 * x) < 2.0 ) return 3;
    return 4;
}

//kompresje
void ByteRunKompresja(const uint8_t wejscie[], int dlugosc, const char* nazwaPlikuWyjsciowego) {
    ofstream wyjscie(nazwaPlikuWyjsciowego, ios_base::binary);
    if (!wyjscie.is_open()) {
        cerr << "Nie mozna otworzyc pliku wyjsciowego!" << endl;
        return;
    }

    int i = 0;

    while (i < dlugosc) {
        if ((i < dlugosc - 1) && (wejscie[i] == wejscie[i + 1])) {
            // Sekwencja powtarzających się bajtów
            int j = 0;
            while ((i + j < dlugosc - 1) && (wejscie[i + j] == wejscie[i + j + 1]) && (j < 127)) {
                j++;
            }
            wyjscie.put(-j);             // Zapisz długość powtarzających się bajtów
            wyjscie.put(wejscie[i]);     // Zapisz wartość powtarzającego się bajtu
            i += (j + 1);
        } else {
            // Sekwencja różnych bajtów
            int j = 0;
            while ((i + j < dlugosc - 1) && (wejscie[i + j] != wejscie[i + j + 1]) && (j < 128)) {
                j++;
            }
            if ((i + j == dlugosc - 1) && (j < 128)) j++;

            wyjscie.put(j - 1);  // Zapisz długość unikalnych bajtów
            for (int k = 0; k < j; k++) {
                wyjscie.put(wejscie[i + k]); // Zapisz unikalne bajty
            }
            i += j;
        }
    }

    wyjscie.close();
    cout << "Kompresja zakonczona. Wynik zapisano w pliku: " << nazwaPlikuWyjsciowego << endl;
}

int rozmiarPliku(const char* nazwaPliku) {
    ifstream wejscie;
    wejscie.open(nazwaPliku, ios_base::binary);
    if (!wejscie.is_open()) {
        cerr << "Nie można otworzyc pliku!" << endl;
        return -1;
    }
    wejscie.seekg(0, ios_base::end);
    int rozmiar = wejscie.tellg();
    wejscie.close();
    return rozmiar;

}

std::vector<uint8_t> ByteRunDekompresja(const char* nazwaPlikuWejsciowego) {
    ifstream wejscie(nazwaPlikuWejsciowego, ios_base::binary);
    if (!wejscie.is_open()) {
        cerr << "Nie można otworzyc pliku wejsciowego!" << endl;
        return {};
    }

    std::vector<uint8_t> zdekompresowane;
    int byte;
    while ((byte = wejscie.get()) != EOF) {
        if (byte < 0) {
            // Sekwencja powtarzających się bajtów
            uint8_t wartosc = wejscie.get();
            for (int i = 0; i < -byte + 1; ++i) {
                zdekompresowane.push_back(wartosc);
            }
        } else {
            // Sekwencja unikalnych bajtów
            for (int i = 0; i < byte + 1; ++i) {
                zdekompresowane.push_back(wejscie.get());
            }
        }
    }
    wejscie.close();
    return zdekompresowane;
}

void rysujObraz(std::vector<uint8_t>& dane) {
    int index = 0; // Indeks w wektorze danych
    for (int y = 0; y < wysokosc/2; ++y) {
        for (int x = 320; x < szerokosc; ++x) {
            uint8_t szary = dane[index++];
            setPixel(x, y, szary, szary, szary); // Odcień szarości
        }
    }
}
