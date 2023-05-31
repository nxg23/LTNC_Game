#pragma once
#include <iostream>
#include <thread>
#include<chrono>
#include "../GameObjects/pacman.h"
#include "../GameObjects/ghost.h"
#include "../GameObjects/map.h"
#include "gameText.h"
#include "../GameObjects/fruit.h"
#include"menu.h"

using namespace std;
using namespace sf;


class Starter
{
 public:	 		 		 
	 Event sfEvt;
	 Maze maze;
	 Pacman<Starter>* pac;
	 Ghost<Starter> *Blinky, *Pinky, *Inky,*Clyde;	 
	 thread ghStatusThread;
	 thread loopThread;
	 int attackInterval=15; // 15 sec
	 int scaterInterval= 7; // 7 sec
	 int blueInterval = 6;	
	 int delay;
	 int curTime;
	 Texture backGroundText;
	 Texture backGroundFlashText;
	 
	 Sprite backGroundSpr;	 
	 bool intro = false;
	 bool isCollid = false;
	 bool lifeWin = false;
	 bool toNextLevel = false;
	 GameSound *gmSound;	
	 GameText *gameText;
	 Fruit* fruit;	
	 RenderWindow* window;	

	 void Run(RenderWindow* win, Texture* sprTexture)
	 {
		 window = win;
		 gmSound = GameSound::getInstance();
		 gameStatus = Demo;
		 backGroundText.loadFromFile("Data/texture/map1.png");
		 backGroundFlashText.loadFromFile("Data/texture/mapB.png");
		 backGroundSpr.setTexture(backGroundText);

		 maze.initMaze();
		 pac = new Pacman<Starter>(sprTexture, this);
		 Blinky = new Ghost<Starter>(sprTexture, 1, this);
		 Pinky = new Ghost<Starter>(sprTexture, 2, this);
		 Inky = new Ghost<Starter>(sprTexture, 3, this);
		 Clyde = new Ghost<Starter>(sprTexture, 4, this);
		 gameText = new GameText();
		 fruit = new Fruit(sprTexture);

		 loopThread = thread(&Starter::loop, this, win);
		 while (win->isOpen())
		 {
			 if (CntrGame::dotsEat == maze.dotsCount) { nextLevel(); }
			 while (win->pollEvent(sfEvt))
			 {
				 if (sfEvt.type == Event::Closed) { win->close(); }
				 else if (sfEvt.type == Event::KeyPressed)
				 {
					 if (gameStatus == Demo && sfEvt.key.code == Keyboard::Space)
					 {
						 startGame();
					 }
					 pac->rotation(sfEvt.key.code);
				 }
			 }
		 }
	 }
	
	 Starter()
	 {		
		
	 };

	~Starter() 
	{
		if (loopThread.joinable()) { loopThread.detach(); }
		if (ghStatusThread.joinable()) { ghStatusThread.detach(); }
		delete  Blinky; 
		delete Pinky;
		delete Inky;
		delete Clyde;
	}	

	void drawLife( RenderWindow *win)
	{		
		if (pac->pacLife < 0) { return; }
		Sprite spr;
		for (int i = 0; i < pac->pacLife; i++)
		{
			spr = pac->getLifeSpr();
			spr.setPosition( Vector2f(30*i, 24*30) );
			(*win).draw( spr );
		}
	}	
		
	// Call from Pacman class
	void setBlueGhost()
	{
		if (CntrGame::pacIsDead) { return; }				
		if (ghStatusThread.joinable()) { ghStatusThread.detach(); }		
		sleep(milliseconds(20));
		ghostStatus = Blue;
		creatGhostThr();
		gmSound->play(GameSound::PlSound::Blue);
		gmSound->stop(GameSound::PlSound::Siren);
	}

	// Call from Ghost class
	void collidToPac()
	{		
		CntrGame::pacIsDead = true;
		pac->pacLife--;
		isCollid = true;		
		stopAll();
		if (pac->pacLife < 0) 
		{	
			gameOver();
		}		
	}

	// Game pver 
	void gameOver()
	{		
		gameStatus = Demo;
		CntrGame::score = 0;
		CntrGame::level = 0;
		lifeWin = false;
		gameText->scoreTxt.setString("SCORE: 0");
		pac->stop();
		Blinky->stop();
		Pinky->stop();
		Inky->stop();
		Clyde->stop();	
		resetPacGhost();
		resetLevel();			
	}
	
	static inline int getScore()
	{
		return CntrGame::score;
	}
private:	

	void loop( RenderWindow* win)
	{				
		win->setActive(true);		
		while (win->isOpen())
		{			
			if (CntrGame::score >= 10000 && !lifeWin)
			{
				lifeWin = true;
				gmSound->play(GameSound::PlSound::WinnLife);
				pac->pacLife++;
			}
			win->clear();			
			if (gameStatus == Play)
			{				
				drawLife(win);
				maze.drawWall(win);
				win->draw(backGroundSpr);
				win->draw(gameText->gameOverTxt);
				win->draw(gameText->scoreTxt);
				win->draw(gameText->levelTxt);
				if (ghostStatus == Blue)
				{
					string dif = to_string(curTime - time(0));
					if (stoi(dif) == 0) { dif = ""; }
					gameText->countTxt.setString(dif);
					win->draw(gameText->countTxt);
				}				
				if (gameText->bonusTxt.getString() != "")
				{
					win->draw(gameText->bonusTxt);
				}
				if(fruit->getVisible() ){ win->draw(fruit->getSrpite());}
			}		
			else
			{
				win->draw(gameText->enterTxt);
				win->draw( Blinky->getNameTxt());
				win->draw(Pinky->getNameTxt());
				win->draw(Inky->getNameTxt());
				win->draw(Clyde->getNameTxt());
			}
			
			win->draw(pac->getSprite());
			win->draw(Blinky->getSprite());
			win->draw(Pinky->getSprite());
			win->draw(Inky->getSprite());
			win->draw(Clyde->getSprite());
			win->display();				
			
		}
	 }

	void changeGhostState()
	{		 			  
			   delay =  scaterInterval;
			   if (ghostStatus == Blue) 
			   {
				   delay = blueInterval; 
				   CntrGame::isBlueGhost = true;
			   }	  
			   changeStatus();
			   while ( ghStatusThread.joinable() )
			   {				   
				   curTime = time(0);
				   curTime += delay;			 
				  
				   while (true && ghStatusThread.joinable() )
				   {
					   if (curTime <= time(0))  { break; }
				   }// wait for change ghost status
				    
				   sleep(milliseconds(10));
				   if (ghostStatus == Blue) // end blue time
				   {	
					 CntrGame::isBlueGhost = false;
					 CntrGame::ghostBonus = 100;
					 gmSound->stop(GameSound::PlSound::Blue);
					 if(CntrGame::gameRun)gmSound->play(GameSound::PlSound::Siren);
				   }
				   if (ghostStatus == Attack)
				   {
					   ghostStatus = Scater;
					   delay = scaterInterval;

				   }
				   else 
				   {			 
					   ghostStatus =  Attack;
					   delay = attackInterval;
				   }
				   changeStatus();
				  
				   if (( maze.dotsCount - CntrGame::dotsEat) < 30)
				   {
					   gmSound->setPich(GameSound::Siren, 1.2);
				   }
				 
			   }
			  		   
	}

	void changeStatus()
	{
		Blinky->changeGhostState();
		Pinky->changeGhostState();
		Inky->changeGhostState();
		Clyde->changeGhostState();
	}	

	void stopAll()
	{					
		pac->stop();
		Blinky->stop();
		Pinky->stop();
		Inky->stop();
		Clyde->stop();	
	    CntrGame::gameRun = false;
		gameText->stopThread();
		fruit->stop();
		gmSound->stopAll();
		if (ghStatusThread.joinable() ){ ghStatusThread.detach(); }	
	    resetLevel();	
		wait(2);
	    if (pac->pacLife >= 0) { startLevel(); }				
	}

	void startGame()
	{				
		maze.redrawDot();
		gameText->gameOverTxt.setString("");
		pac->pacLife = 2;		
		gameStatus = Play;
		resetPacGhost();		
		intro = true;
		CntrGame::gameRun = true;
		CntrGame::level=1;
		CntrGame::score=0;
		CntrGame::dotsEat = 0;
		blueInterval = 7; 
		fruit->setLevel(CntrGame::level);
		gmSound->setPich(GameSound::Siren, 1);
		startLevel();
	}

	void startLevel()
	{		 
		if (intro)
		{
			intro = false;		 
			gmSound->play(GameSound::PlSound::Intro);	
		}
		isCollid = false;
		ghostStatus = Scater;
		gmSound->play(GameSound::PlSound::Siren);		
	    CntrGame::gameRun = true;
		resetPacGhost();		 
		pac->run();	
		creatGhostThr();
		fruit->start();
		gameText->levelTxt.setString("LEVEL: " + to_string(CntrGame::level));
	}

	 
	void nextLevel()
	{
		gmSound->setPich(GameSound::Siren, 1);
		toNextLevel = true;		
	    CntrGame::dotsEat = 0;
		stopAll();	
		maze.redrawDot();
		CntrGame::level++;		
		gameText->levelTxt.setString("LEVEL: " + to_string(CntrGame::level));
		fruit->setLevel(CntrGame::level);
		if (CntrGame::level > 2 && CntrGame::level < 6) { blueInterval = 4; }
		else if (CntrGame::level >= 6 && CntrGame::level < 10){blueInterval = 2; }
		else if (CntrGame::level >= 10) { blueInterval = 0; }
	}

	void creatGhostThr()
	{	
		while (ghStatusThread.joinable()) {}
		ghStatusThread = thread(&Starter::changeGhostState, this); 
	}

	void resetLevel()
	{		
		CntrGame::ghostBonus = 100;
		if(pac->pacLife<0)
		{		 
			gameText->gameOverTxt.setString("GAME OVER"); 
		}
	}

	void resetPacGhost()
	{
		pac->reset();
		Blinky->reset();
		Pinky->reset();
		Inky->reset();
		Clyde->reset();		
	}

	// wait for second 
	void wait(int delayInt)
	{
		auto curTime = time(0);
		int counter=0;
		curTime += delayInt;		
		while (true)
		{
			counter++;
			if (toNextLevel)
			{		
				if (counter % 30 == 0)
				{
				 backGroundSpr.setTexture(backGroundFlashText);
				}
				else if (counter % 30 == 15)
				{
				 backGroundSpr.setTexture(backGroundText);
				}				
			}
			if (curTime < time(0)) { break; }
			sleep(milliseconds(10));
		}
		toNextLevel = false;
		backGroundSpr.setTexture(backGroundText);
	}
	
};



