#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include<iostream>
#include <random>
#include<string>
#include "dane.h"



class tekst {
public:

	std::string m = "error";
	sf::Vector2f poz_m;
	sf::Text m_txt;

	tekst()
	{
		sf::Font font;
		if (!font.loadFromFile("font1.otf"))std::cout << "error ";
		m_txt.setFont(font);
		m_txt.setPosition(poz_m);
		m_txt.setCharacterSize(50);
		m_txt.setOutlineThickness(5);
		m_txt.setOutlineColor(sf::Color::Black);
	}
};




class menu {
public:
	int page = 0;//znacznik do zmieniania strony
	dane da; //domyslne dane - zmieniane w settings
	int easter_egg = 0;// 1=gdy kula to c++, bloki to java, 2= mario


	void lev(int &start, int&lvl, sf::RenderWindow &okno, std::vector<tekst> &teksty, dane &d, int &znak)
	{
		if (page == 0)lev1(start, lvl, okno, teksty, d, znak);
		if (page == 1)lev2(start, lvl, okno, teksty, d, znak);
		da.completion = d.completion;
		
	}

	void lev1(int &start, int&lvl, sf::RenderWindow &okno, std::vector<tekst> &teksty, dane &d, int &znak);

	void lev2(int &start, int&lvl, sf::RenderWindow &okno, std::vector<tekst> &teksty, dane &d, int &znak);





	int pa = 0;//tymxzasowa page
	int i= 0,j=0, 
		zn = 0;//gdy 0 to klawisz nie naxisniety
	
	void plus(float &value, float &val2, int delta);	void plus(int &value, int &val2, int delta);

	void minus(float &value, float &val2, int delta);	void minus(int &value, int &val2, int delta);




	void settings(int &start, int&lvl, sf::RenderWindow &okno, std::vector<tekst> &teksty, dane &d, int &znak, sf::Sound &sound, sf::Sound &sound2, sf::Texture &txtk, std::vector<sf::Texture> &kol_txt, sf::Texture &txtb, std::vector<sf::Texture> &bl_txt)
	{
		//using namespace sf;	if (!Keyboard::isKeyPressed(Keyboard::Key::Num1) && !Keyboard::isKeyPressed(Keyboard::Key::Num2) && !Keyboard::isKeyPressed(Keyboard::Key::Num3) && !Keyboard::isKeyPressed(Keyboard::Key::Num4) && !Keyboard::isKeyPressed(Keyboard::Key::Num5) && !Keyboard::isKeyPressed(Keyboard::Key::Num6) && !Keyboard::isKeyPressed(Keyboard::Key::Num7) && !Keyboard::isKeyPressed(Keyboard::Key::Num8))
		sf::Event ev;		 okno.pollEvent(ev);		if (ev.type==sf::Event::KeyReleased)// lepsza metoda	
		zn = 0;//by nie bylo podwojnego naxiskania

		if (page == 0)set0(start, lvl, okno, teksty, d, znak);//lista ustawien	
		if (page == 1)set1(start, lvl, okno, teksty, d, znak, sound, sound2, txtk, kol_txt,txtb,bl_txt);//1audioviz
		if (page == 2)set2(start, lvl, okno, teksty, d, znak);//2ped 
		if (page == 3)set3(start, lvl, okno, teksty, d, znak);//3trudnosc 
		if (page == 4)set4(start, lvl, okno, teksty, d, znak);//3rozmiar
		
	}
 
	void set0(int &start, int&lvl, sf::RenderWindow &okno, std::vector<tekst> &teksty, dane &d, int &znak);

	void set1(int &start, int&lvl, sf::RenderWindow &okno, std::vector<tekst> &teksty, dane &d, int &znak, sf::Sound &sound, sf::Sound &sound2, sf::Texture &txtk, std::vector<sf::Texture> &kol_txt, sf::Texture &txtb, std::vector<sf::Texture> &bl_txt);
	
	void set2(int &start, int&lvl, sf::RenderWindow &okno, std::vector<tekst> &teksty, dane &d, int &znak);

	void set3(int &start, int&lvl, sf::RenderWindow &okno, std::vector<tekst> &teksty, dane &d, int &znak);

	void set4(int &start, int&lvl, sf::RenderWindow &okno, std::vector<tekst> &teksty, dane &d, int &znak);
	
};/**/