#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
using namespace std;


class Figura {
protected:
    sf::Shape* ksztaltBazowy;
    float predkosc;

public:
    void narysuj(sf::RenderWindow& okno) {
        okno.draw(*ksztaltBazowy);
    }

    void steruj() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            ksztaltBazowy->move({ -predkosc, 0});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            ksztaltBazowy->move({predkosc, 0});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
             ksztaltBazowy->move({0, -predkosc});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
             ksztaltBazowy->move({0, predkosc});
        }
    }
};

class Kwadrat : public Figura{
public:
    sf::RectangleShape danyKwadrat;



    Kwadrat(float szer, float wys, float pred) {
        danyKwadrat.setSize({szer, wys});
        danyKwadrat.setOrigin({szer/2, wys/2});
        danyKwadrat.setPosition({400,300});
        danyKwadrat.setFillColor({sf::Color::Red});

        ksztaltBazowy = &danyKwadrat;
        predkosc = pred;
    }

};

class Kolo : public Figura {
public:
    sf::CircleShape daneKolo;

    Kolo(float promien, float pred) {
        daneKolo.setRadius(promien);
        daneKolo.setPosition({300,300});
        daneKolo.setOrigin({promien, promien});
        daneKolo.setFillColor(sf::Color::Green);

        ksztaltBazowy = &daneKolo;
        predkosc = pred * 0.5f;
    }
};


void uruchomGre(float predkosc_ruchu, float wys_kw, float szer_kw) {
    sf::RenderWindow window(sf::VideoMode({800 , 600}), "Gra");
    window.setFramerateLimit(60);    // ustawienie limitu klatek na sekundę

    float predkosc = predkosc_ruchu;

    Kwadrat kwadrat(szer_kw, wys_kw, predkosc);
    Kolo kolo(20,predkosc);

    sf::CircleShape koloAnimowane;
    koloAnimowane.setRadius(40);
    koloAnimowane.setOrigin({40,40});
    koloAnimowane.setFillColor(sf::Color::Yellow);

    sf::Clock zegar;


    float zasieg = 150.f;
    float baza_x = 200.f;
    float baza_y = 150.f;
    float szybkosc = 2.f;

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        //sterowanie z klawiatury
        kwadrat.steruj();
        kolo.steruj();

        float t = zegar.getElapsedTime().asSeconds();
        float x = baza_x + std::sin(t*szybkosc)*zasieg;
        float y = baza_y;
        koloAnimowane.setPosition({x, y});


        window.clear();
        window.draw(koloAnimowane);
        kwadrat.narysuj(window);
        kolo.narysuj(window);
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
            float szerokosc, wysokosc, predkosc_ruchu;
            cout << "Wybrano opcje 1" << endl;
            cout << "Podaj szerokosc : " << endl;
            cin >> szerokosc;
            cout << "Podaj wysokosc : " << endl;
            cin >> wysokosc;
            cout << "Podaj predkosc ruch : " << endl;
            cin >> predkosc_ruchu;
            cout << "Uruchamiam gre" << endl;
            uruchomGre(predkosc_ruchu, wysokosc, szerokosc);
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