#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream> 
#include <random>
#include <string> 
#include"dane.h" 
#include"menu.h" 




// kula i jej ruchy
class kula :public sf::Drawable
{
public:
	sf::CircleShape c;		dane du;
	int r = du.r;//promien 
	float temp, moc = du.moc;
	int pal_zn = 0;//znacznik do zdarzen z paletka
	bool sp_zn = false;//znacznik do dzwieku specjalnego bloku
	float licznik = 0;int temp_l = 0;//timer do powrotu do normy
	
	int strata = 0, punkty = 0; //punkty gracza i przeiwnika
	float ped = du.ped_kuli;
	sf::Vector2f predkosc{ ped,-ped };//tempo poczatkowe				   
	std::string kom = "     ";//zapis komunikatu
	float poz_kuli_y() { return this->c.getPosition().y; }//pozyxja kuli y
	float poz_kuli_x() { return this->c.getPosition().x; }//pozyxja kulix
	bool dtk2 = false;//sprawdzanie xzy w tej klatxe by³o dotkniexie
	float ped2 = 0;// do sterowania W S
	bool zn_kolizja_boss = true;//znaxznik do kolizji z blokiem w bossie (ruxh_boss)
	bool glowna = false;

	kula();


	void specjalny_efekt_bloczka(dane &d, std::vector<blok> &bloki, int &i);
	void powrot_do_normy(dane  &d);
	void kolizja_z_blokiem(dane &d, dane d_domyslne, std::vector<blok> &bloki);

	 //to ruch i kolizja
	void ruch(std::vector <blok>&bloki, std::vector<float> poz_gracza, std::vector<float> poz_bad, dane &d, const dane da);
	//sterowanie kula w boss
	void ruch_boss(dane &d, std::vector <blok>&bloki);
	
	//klawisze do xheatow. by wlaxzyx naxisnij =
	void cheats(dane &d);
	
	
	//to by sie wyswietlilo 
	void draw(sf::RenderTarget& cel, sf::RenderStates stan)const override
	{		cel.draw(this->c, stan);	}

};