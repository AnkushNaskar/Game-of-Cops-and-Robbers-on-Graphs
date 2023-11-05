#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

void grid(vector<pair<int, int>>& c, pair<int, int> r, int copCnt);
void tori(vector<pair<int, int>>& c, pair<int, int> r, pair<int, int> lastRpos, int copCnt, int m, int n);
void cylinder(vector<pair<int, int>>& c, pair<int, int> r, int copCnt, int m, int n);

int main()
{
    cout << "Enter number of rows and columns respectively : ";
    int n, m;       // m rows, n col
    cin >> m >> n;
    
    cout << "Enter 1 for GRID graph or 2 for CYLINDER graph and 3 for TORI graph : ";
    
    int option;
    cin >> option; 
    while (option != 1 && option != 2 && option != 3) {
        cout << "Enter valid option : ";
        cin >> option;
    }
    sf::RenderWindow window(sf::VideoMode(100 * (n + 1), 100 * (m + 1)), "Game of Cops and Robbers");

    vector<vector<sf::Vertex>> linesX(m, vector<sf::Vertex>());
    vector<vector<sf::Vertex>> linesY(n, vector<sf::Vertex>());
    for (int i = 0; i < m; i++) {
        linesX[i].push_back(sf::Vertex(sf::Vector2f(100.f, 100 * (i + 1))));
        linesX[i].push_back(sf::Vertex(sf::Vector2f(100 * n, 100 * (i + 1))));
    }
    for (int i = 0; i < n; i++) {
        linesY[i].push_back(sf::Vertex(sf::Vector2f(100 * (i + 1), 100.f)));
        linesY[i].push_back(sf::Vertex(sf::Vector2f(100 * (i + 1), 100*m))); 
    }
     
    vector<vector<sf::CircleShape>> nodesX(m, vector<sf::CircleShape>(n, sf::CircleShape(20.f)));
    //vector<vector<sf::CircleShape>> nodesY(m, vector<sf::CircleShape>(n, sf::CircleShape(20.f)));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            nodesX[i][j].setPosition(100 * (j + 1) - nodesX[i][j].getRadius(), 100 * (i + 1) - nodesX[i][j].getRadius());
            nodesX[i][j].setFillColor(sf::Color(0, 0, 0));
            nodesX[i][j].setOutlineThickness(2.f);
            nodesX[i][j].setOutlineColor(sf::Color(255, 255, 255));
            //(sf::Vertex(sf::Vector2f(100 * (j + 1), 100 * (i + 1))));
            //linesY[j].push_back(sf::Vertex(sf::Vector2f(100 * (i + 1), 100 * (j + 1))));
        }   
    }

    int copCnt;
    if (option == 1 || option == 2) {
        copCnt = 2;
    }else if(option == 3){
        copCnt = 3;
    }

    vector<pair<int, int>> c(copCnt, pair<int, int>());

    pair <int, int> r;
    pair<int, int> lastRpos;

    bool gameOver = false;

    /*vector<sf::Vertex> g;
    for (int j = 0; j < n; j++) {
        g.push_back(sf::Vertex(sf::Vector2f(10 * (j + 1),10)));
    }*/

    int cops = 0;
    int robbers = 0;
    while (window.isOpen())
    {   
        sf::Event event;


        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if(!gameOver) {
                        if (robbers < 1 && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                            // transform the mouse position from window coordinates to world coordinates
                            sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                            if (cops < copCnt) {
                                if (abs(mouse.x / 100 - round(mouse.x / 100)) <= 0.2 && abs(mouse.y / 100 - round(mouse.y / 100)) <= 0.2) {
                                    c[cops] = { round(mouse.x / 100) - 1, round(mouse.y / 100) - 1 };
                                    nodesX[round(mouse.y / 100) - 1][round(mouse.x / 100) - 1].setFillColor(sf::Color(255, 255, 0));
                                    cops++;
                                }
                            }
                            else if (robbers < 1) {

                                if (abs(mouse.x / 100 - round(mouse.x / 100)) <= 0.2 && abs(mouse.y / 100 - round(mouse.y / 100)) <= 0.2) {
                                    r = { round(mouse.x / 100) - 1, round(mouse.y / 100) - 1 };
                                    nodesX[round(mouse.y / 100) - 1][round(mouse.x / 100) - 1].setFillColor(sf::Color(250, 50, 50));
                                    robbers++;
                                }
                            }
                        }
                    }
                    
                    break;
                case sf::Event::KeyPressed:
                    if (gameOver == true || robbers == 0) {
                        break;
                    }
                    if (option == 1) {
                        if (r.first > 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                            nodesX[r.second][r.first].setFillColor(sf::Color(0, 0, 0));
                            r.first--;
                            nodesX[r.second][r.first].setFillColor(sf::Color(250, 50, 50));
                        }
                        else if (r.second > 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                            nodesX[r.second][r.first].setFillColor(sf::Color(0, 0, 0));
                            r.second--;
                            nodesX[r.second][r.first].setFillColor(sf::Color(250, 50, 50));
                        }
                        else if (r.first < n - 1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                            nodesX[r.second][r.first].setFillColor(sf::Color(0, 0, 0));
                            r.first++;
                            nodesX[r.second][r.first].setFillColor(sf::Color(250, 50, 50));
                        }
                        else if (r.second < m - 1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                            nodesX[r.second][r.first].setFillColor(sf::Color(0, 0, 0));
                            r.second++;
                            nodesX[r.second][r.first].setFillColor(sf::Color(250, 50, 50));
                        }
                    }else if (option == 2) {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                            nodesX[(r.second + m) % m][(r.first + n) % n].setFillColor(sf::Color(0, 0, 0));
                            r.first--;
                            nodesX[(r.second + m) % m][(r.first + n) % n].setFillColor(sf::Color(250, 50, 50));
                        }
                        else if (r.second > 0 && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                            nodesX[(r.second + m) % m][(r.first + n) % n].setFillColor(sf::Color(0, 0, 0));
                            r.second--;
                            nodesX[(r.second + m) % m][(r.first + n) % n].setFillColor(sf::Color(250, 50, 50));
                        }
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                            nodesX[(r.second + m) % m][(r.first + n) % n].setFillColor(sf::Color(0, 0, 0));
                            r.first++;
                            nodesX[(r.second + m) % m][(r.first + n) % n].setFillColor(sf::Color(250, 50, 50));
                        }
                        else if (r.second < m - 1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                            nodesX[(r.second + m) % m][(r.first + n) % n].setFillColor(sf::Color(0, 0, 0));
                            r.second++;
                            nodesX[(r.second + m) % m][(r.first + n) % n].setFillColor(sf::Color(250, 50, 50));
                        }
                    }
                    else if(option == 3){
                        lastRpos = r;
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                            nodesX[(r.second + m) % m][(r.first + n) % n].setFillColor(sf::Color(0, 0, 0));
                            r.first--;
                            nodesX[(r.second + m) % m][(r.first + n) % n].setFillColor(sf::Color(250, 50, 50));
                        }
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                            nodesX[(r.second + m) % m][(r.first + n) % n].setFillColor(sf::Color(0, 0, 0));
                            r.second--;
                            nodesX[(r.second + m) % m][(r.first + n) % n].setFillColor(sf::Color(250, 50, 50));
                        }
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                            nodesX[(r.second + m) % m][(r.first + n) % n].setFillColor(sf::Color(0, 0, 0));
                            r.first++;
                            nodesX[(r.second + m) % m][(r.first + n) % n].setFillColor(sf::Color(250, 50, 50));
                        }
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                            nodesX[(r.second + m) % m][(r.first + n) % n].setFillColor(sf::Color(0, 0, 0));
                            r.second++;
                            nodesX[(r.second + m) % m][(r.first + n) % n].setFillColor(sf::Color(250, 50, 50));
                        }
                    }



                    if (cops >= copCnt && robbers > 0) {
                        for (int i = 0; i < copCnt; i++) {
                            nodesX[(c[i].second + m) % m][(c[i].first + n) % n].setFillColor(sf::Color(0, 0, 0));
                        }
                        if (option == 1) {
                            grid(c, r, copCnt);
                        }else if (option == 2) {
                            cylinder(c, r, copCnt, m, n);
                        }
                        else if (option == 3) {
                            tori(c, r, lastRpos, copCnt, m, n);
                        }
                            
                        for (int i = 0; i < copCnt; i++) {
                            nodesX[(c[i].second + m) % m][(c[i].first + n) % n].setFillColor(sf::Color(255, 255, 0));
                        }
                        
                    }
                    
                    
                    break;

                default:
                    break;
            }
        }

        window.clear();
        for (int i = 0; i < m; i++) {
            window.draw(&linesX[i][0], linesX[i].size(), sf::Lines);
        }
        for (int i = 0; i < n; i++) {
            window.draw(&linesY[i][0], linesY[i].size(), sf::Lines);
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                window.draw(nodesX[i][j]);
            }
        }
        

        window.display();
        for (int i = 0; i < copCnt; i++) {
            if (robbers > 0 && cops == copCnt && (c[i].first + n)%n == (r.first + n)%n && (c[i].second + m)%m == (r.second + m)%m) {
                gameOver = true;
                break;
            }
        }
    }

    return 0;
}
