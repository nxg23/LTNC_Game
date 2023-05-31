#pragma once
#include"Sources/GameManager/starter.h"


Texture sprTexture;
Texture backTexture;
Starter* starter;
int winW = 23 * 30;
int winH = 25 * 30;

int pagenum = 1000;
string name;
int Score = 0;
Event event;

// Input player name
void playerName(RenderWindow& window, string& name);

// History of player
void  history(RenderWindow& window);

// Get score from file history.txt 
void getScore(string name);

// Loop Game
void loop(Event event);


Starter game;
Menu menu;

int main()
{
    loop(event);

    return 0;
};


void playerName(RenderWindow& window, string& name)
{
    if (name.empty())  {name.clear();}

    // Initialize
    Texture tutorial;
    tutorial.loadFromFile("Data/texture/tutorial.png");
    Sprite bg2;
    bg2.setTexture(tutorial);

    Font font;
    font.loadFromFile("Data/font/comic.ttf");
    Text t1;
    Text t2;
  

    t1.setFont(font);
    t1.setString("Enter your name");
    t1.setCharacterSize(70);
    t1.setPosition(500, 400);

    t2.setFont(font);
    t2.setCharacterSize(70);
    t2.setPosition(500, 500);



    t1.setFillColor(Color::Yellow);
    t2.setFillColor(Color::Yellow);


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed()) { window.close(); }
            if (event.type == Event::TextEntered)
            {
                name += static_cast<char>(event.text.unicode);
            }
            if (Keyboard::isKeyPressed(Keyboard::BackSpace) && name.size() > 0)
            {
                name.resize(name.size() - 1);
            }
            if (Keyboard::isKeyPressed(Keyboard::Return) && name.size() > 1)
            {
                pagenum = 3; //win game
                return;
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                pagenum = 1000; //win game
                return;
            }
            t2.setString(name);
            window.clear();
            // Draw 
            window.draw(bg2);
            window.draw(t1);
            window.draw(t2);
            window.display();
        }
    }
}

 
void getScore(string name)
{
    Score = game.getScore();
    ofstream offile;
    offile.open("history.txt", ios::app);
    offile << name << "       " << Score << "*" << endl;
}

void loop(Event event)
{
    // Initialize
    RenderWindow window(VideoMode(1920, 1080), "Pacman");
    menu.setUp(1920, 1080);
    Texture mainMenuBg;
    mainMenuBg.loadFromFile("Data/texture/bg.jpg");
    Sprite bg;
    bg.setTexture(mainMenuBg);

    //Loop
    while (true)
    {
        // Check page number
        if (pagenum == 1000)
        {

            while (window.isOpen())
            {

                while (window.pollEvent(event))
                {
                    if (event.type == Event::Closed) {
                        window.close();
                    }
                    if (event.type == Event::KeyPressed)
                    {
                        if (event.key.code == Keyboard::Up) menu.MoveUp();
                        if (event.key.code == Keyboard::Down) menu.MoveDown();
                        if (event.key.code == Keyboard::Return)
                        {
                            if (menu.pressed() == 0) pagenum = 0;
                            if (menu.pressed() == 1) pagenum = 1;
                            if (menu.pressed() == 2) pagenum = -1;
                        }
                    }
                    window.clear();
                    if (pagenum != 1000) break;

                    // Draw 
                    window.draw(bg);
                    menu.draw(&window);
                    window.display();
                }
                if (pagenum == -1)
                {
                    window.close();
                    break;
                }
                if (pagenum == 0) { playerName(window, name); }

                if (pagenum == 1) { history(window); }

                if (pagenum == 3)
                {
                    while (!sprTexture.loadFromFile("Data/texture/PMSprites.png")) {};
                    window.setActive(false);
                    game.Run(&window, &sprTexture);
                    getScore(name);
                }
            }
        }
    }
}

void history(RenderWindow& window)
{
    Texture scoreBg;
    scoreBg.loadFromFile("Data/texture/score.png");

    Font font1;
    font1.loadFromFile("Data/font/comic.ttf");

    // Load history from file
    vector<string> lines;
    ifstream infile("history.txt");
    string line;
    while (getline(infile, line, '*'))
    {
        lines.push_back(line);
    }

    // Create dynamic array 
    Text* text = new Text[lines.size()];
    for (int i = 0; i < lines.size(); i++)
    {
        text[i].setFont(font1);
        text[i].setCharacterSize(50);
        text[i].setFillColor(Color::Green);
        text[i].setString(lines[i]);
        text[i].setPosition(Vector2f(40, 100 * i));
    }

    // Main loop
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
                delete[] text; // delete dynamic memory
                return;
            }

            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                pagenum = 1000;
                delete[] text; // delete dynamic memory
                return;
            }

            if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                if (text[0].getPosition().y <= 5)
                {
                    for (int i = 0; i < lines.size(); i++)
                    {
                        text[i].move(0, 20);
                    }
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::Down))
            {
                if (text[lines.size() - 1].getPosition().y > window.getPosition().y + 1000)
                {
                    for (int i = 0; i < lines.size(); i++)
                    {
                        text[i].move(0, -20);
                    }
                }
            }
        }

        // Draw 
        window.clear();
        window.draw(Sprite(scoreBg));
        for (int i = 0; i < lines.size(); i++)
        {
            window.draw(text[i]);
        }
        window.display();
    }

    // delete dynamic memory
    delete[] text;
}

