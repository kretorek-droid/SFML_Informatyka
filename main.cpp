#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

void uruchomGre(string tytul_okna, unsigned int wysokosc, unsigned int szerokosc) {
    sf::RenderWindow window(sf::VideoMode({szerokosc, wysokosc}), tytul_okna);

    while (window.isOpen()) {

        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.display();
    }
}


int main() {
    while (true) {
        cout << "======MENU======"<< endl;
        cout << "Aby rozpoczac gre: wybierz (1)" << endl;
        cout << "Aby zamknac program: wybierz (2)" << endl;
        int numer_menu;
        cin >> numer_menu;
        if (numer_menu == 1) {
            int szerokosc, wysokosc;
            string tytul_okna;
            cout << "Wybrano opcje 1" << endl;
            cout << "Podaj szerokosc : " << endl;
            cin >> szerokosc;
            cout << "Podaj wysokosc : " << endl;
            cin >> wysokosc;
            cout << "Podaj tytul okna : " << endl;
            cin >> tytul_okna;
            cout << "Uruchamiam gre" << endl;
            uruchomGre(tytul_okna, wysokosc, szerokosc);
        } else if (numer_menu == 2){
            cout << "Wybrano opcje 2" << endl;
            cout << "Zamykam program" << endl;
            break;
        } else {
            cout << "Niepoprawny wybor" << endl;
        }
    }





    return 0;
}