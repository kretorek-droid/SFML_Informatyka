#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
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

    Pilka(float start_x, float start_y) {
        float promien = 10;
        danaPilka.setRadius(promien);
        danaPilka.setOrigin({promien, promien});
        danaPilka.setPosition({start_x, start_y});
        danaPilka.setFillColor(sf::Color::Blue);

        ksztaltBazowy = &danaPilka;
        wektorPredkosci = {3,3};
    }

    void aktualizuj() {
        danaPilka.move(wektorPredkosci);
    }



};



void uruchomGre(float predkosc_ruchu, float szer_kw) {
    sf::RenderWindow okno(sf::VideoMode({800 , 600}), "Gra");
    okno.setFramerateLimit(60);    // ustawienie limitu klatek na sekundę

    float predkosc = predkosc_ruchu;

    Deska gracz(szer_kw, predkosc);
    Pilka pilka1(400,300);



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
            cout << "Uruchamiam gre - poziom latwy" << endl;
            uruchomGre(10, 200);
        } else if (numer_menu == 2){
            cout << "Uruchamiam gre - poziom sredni" << endl;
            uruchomGre(10, 100);
        } else if (numer_menu == 3) {
            cout << "Uruchamiam gre - poziom trudny" << endl;
            uruchomGre(10, 50);
        } else if (numer_menu == 4) {
            cout << "Zamykam program" << endl;
            break;
        } else {
            cout << "Niepoprawny wybor" << endl;
        }
    }





    return 0;
}