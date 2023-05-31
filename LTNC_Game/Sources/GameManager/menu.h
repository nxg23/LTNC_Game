#pragma once
#include<SFML/Graphics.hpp>
#include<fstream>



using namespace std;
using namespace sf;



class Menu
{
public:
	Text mainMenu[3];
	
	Menu() {};
	~Menu() {};

	void draw(RenderWindow* window)
	{
		for (int i = 0; i < 3; i++)
		{
			window->draw(mainMenu[i]);
		}
	}
	void MoveUp()
	{

		if (selected - 1 >= -1) // not play
		{
			mainMenu[selected].setFillColor(Color::White);
			selected--;
			if (selected == -1)
			{
				selected = 2;
			}

			mainMenu[selected].setFillColor(Color::Yellow);
		}
	}
	void MoveDown()
	{
		if (selected + 1 <= 3) // not exit
		{
			mainMenu[selected].setFillColor(Color::White);
			selected++;
			if (selected == 3)
			{
				selected = 0;
			}

			mainMenu[selected].setFillColor(Color::Yellow);
		}
	}
	void setSelected(int n)
	{
		selected = n;
	}
	int pressed() { return selected; }
	void setUp(float width, float height)
	{
		font.loadFromFile("Data/font/comic.ttf");

		//Set up menu game

		mainMenu[0].setFont(font);
		mainMenu[0].setFillColor(Color::White);
		mainMenu[0].setString("Play Game");
		mainMenu[0].setCharacterSize(90);
		mainMenu[0].setPosition(Vector2f(10, height / 2));


		mainMenu[1].setFont(font);
		mainMenu[1].setFillColor(Color::White);
		mainMenu[1].setString("History");
		mainMenu[1].setCharacterSize(90);
		mainMenu[1].setPosition(Vector2f(10, height / 2 + 150));

		mainMenu[2].setFont(font);
		mainMenu[2].setFillColor(Color::White);
		mainMenu[2].setString("Exit");
		mainMenu[2].setCharacterSize(90);
		mainMenu[2].setPosition(Vector2f(10, height / 2 + 300));

		selected = 0;
	}
	

private:
	int selected;
	Font font;

};

