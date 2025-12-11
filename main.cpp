#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;


class Figura {
protected:
    sf::Shape* ksztaltBazowy;


public:
    void narysuj(sf::RenderWindow& okno) {
        okno.draw(*ksztaltBazowy);
    }
    sf::FloatRect pobierzGranice() {
        return ksztaltBazowy->getGlobalBounds();
    }

};

class Deska : public Figura{
public:
    sf::RectangleShape danaDeska;
    float predkosc;


    Deska(float szer, float pred) {
        danaDeska.setSize({szer, 20});
        danaDeska.setOrigin({szer/2, 20/2});
        danaDeska.setPosition({400,550});
        danaDeska.setFillColor({sf::Color::Red});

        ksztaltBazowy = &danaDeska;
        predkosc = pred;
    }

};

class Pilka : public Figura {
public:
    sf::CircleShape danaPilka;
    sf::Vector2f wektorPredkosci;

    Pilka(float start_x, float start_y, sf::Color kolor, float wX, float wY) {
        float promien = 10;
        danaPilka.setRadius(promien);
        danaPilka.setOrigin({promien, promien});
        danaPilka.setPosition({start_x, start_y});
        danaPilka.setFillColor(sf::Color::Blue);

        ksztaltBazowy = &danaPilka;
        reset(start_x, start_y);
    }

    void aktualizuj() {
        danaPilka.move(wektorPredkosci);
    }


    void odbijOdDeski() {
        wektorPredkosci.y = -std::abs(wektorPredkosci.y);
    }


};

void zapiszGre(int ilosc_pilek, float szer_deski, int zycia, Deska& gracz, Pilka& pil1, Pilka& pil2, Przeszkoda& przeszk) {
  ofstream plik("zapis.txt");
    if (plik.is_open()) {
        plik << ilosc_pilek << endl;
        plik << szer_deski << endl;
        plik << zycia << endl;

        plik << gracz.pobierzPozycje().x << endl;

        plik << pil1.pobierzPozycje().x << " " << pil1.pobierzPozycje().y << endl;
        plik << pil1.wektorPredkosci.x << " " << pil1.wektorPredkosci.y << endl;

        plik << pil2.pobierzPozycje().x << " " << pil2.pobierzPozycje().y << endl;
        plik << pil2.wektorPredkosci.x << " " << pil2.wektorPredkosci.y << endl;

        plik << przeszk.pobierzPozycje().x << " " << przeszk.pobierzPozycje().y << endl;
        plik << przeszk.wektorPredkosci.x << " " << przeszk.wektorPredkosci.y << endl;

        cout << "gra zapisana pomyslnie" << endl;
    } else {
        cout << "blad zapisu do pliku" << endl;
    }



}

void uruchomGre(bool czyWczytac) {
    int ilosc_pilek = 1;
    float szerokosc_deski = 200;
    int zycia = 6;

    float deskaX = 400;
    float p1X = 380, p1Y = 400, p1vX = -3, p1vY = -4;
    float p2X = 420, p2Y = 400, p2vX = 3, p2vY = -4;
    float przX = 400, przY = 250, przvX = 2, przvY = 1.5;

    if(czyWczytac) {
        ifstream plik("zapis.txt");
        if (plik.is_open()) {
            cout << "wczytywanie gry" << endl;

            plik >> ilosc_pilek;
            plik >> szerokosc_deski;
            plik >> zycia;
            plik >> deskaX;
            plik >> p1X >> p1Y >> p1vX >> p1vY;
            plik >> p2X >> p2Y >> p2vX >> p2vY;
            plik >> przX >> przY >> przvX >> przvY;

            plik.close();
        } else {
            cout << "brak pliku zapisu, uruchamiam gre" << endl;
        }
    } else {
        cout << "======WYBIERZ POZIOM======"<< endl;
        cout << "Poziom latwy (deska szeroka, 1 pilka) - wybierz (1)" << endl;
        cout << "Poziom sredni (deska normalna, 2 pilka) - wybierz (2)" << endl;
        cout << "Poziom trudny (deska waska, 2 pilki)- wybierz (3)" << endl;
        int poziom;
        cin >> poziom;

        if (poziom == 1) {
            ilosc_pilek = 1;
            szerokosc_deski = 200;
        } else if (poziom == 2) {
            ilosc_pilek = 2;
            szerokosc_deski = 100;
        } else if (poziom == 3) {
            ilosc_pilek = 2;
            szerokosc_deski = 50;
        }
    }

    sf::RenderWindow okno(sf::VideoMode({800 , 600}), "Gra");
    okno.setFramerateLimit(60);    // ustawienie limitu klatek na sekundę

    float predkosc_deski = 6;

    Deska gracz(szerokosc_deski, predkosc_deski);
    gracz.ustawPozcyje(deskaX, 550);

    Pilka pilka1(380,400,sf::Color::Blue,-3,-4);
    pilka1.ustawPozcyje(p1X,p1Y);
    pilka1.wektorPredkosci = {p1vX, p1vY};

    Pilka pilka2(420,400,sf::Color::White,3,-4);
    pilka2.ustawPozcyje(p2X,p2Y);
    pilka2.wektorPredkosci = {p2vX, p2vY};

    Przeszkoda przeszkoda;
    przeszkoda.ustawPozcyje(przX,przY);
    przeszkoda.wektorPredkosci = {przvX, przvY};
    przeszkoda.aktualizujZycia(zycia);

    while (okno.isOpen()) {
        while (auto event = okno.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        //sterowanie z klawiatury
        gracz.steruj();
        pilka1.aktualizuj();

        okno.clear();
        gracz.narysuj(okno);
        pilka1.narysuj(okno);
        przeszkoda.narysuj(okno);

        okno.display();
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
            cout << "Uruchamiam gre " << endl;
            uruchomGre(false);
        } else if (numer_menu == 2){
            cout << "Wczytuje gra" << endl;
            uruchomGre(true);
        }else if (numer_menu == 3) {
            cout << "Zamykam program" << endl;
            break;
        } else {
            cout << "Niepoprawny wybor" << endl;
        }
    }





    return 0;
}