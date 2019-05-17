#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream> 
#include <random>
#include <string> 



class dane {
public:

	int fps = 60;
	unsigned int okno_x = 1600, okno_y = 900;	//wymiary okna
	float blok_ax = 100, blok_by = 50;			// wymiary bloku
	float player_ax = 200, player_by = 30;	//wymiary paletki	
	float r = 50;							//promien kulki
	float blok_outline = 5;  //grubosc krawedzi bloku

	int z_przeciwnik = 0;//znacznik do wlaczania przeciwnika   0=brak	1=2gi graxz		2=komputer steruje przexiwnikiem
	int z_auto_graxz = 0;//zaxznik do autopilota 1=wl
	int z_kula_sterowanie = 0;//znacznik do poruszania kula		0=kula sama leci,	1=W,S lewo prawo,	
	bool z_b = 0;//znaczik ruchomych blokow
	bool z_cheats = false;//znacznik do uzywania cheatow
	int z_2 = 0;//ilosx dodatkowyxh kulek
	bool z_boss = false;
	bool z_up_down = false; //znacznik do ruchow paletka
	int z_t = 1;//tekstury kuli		0=nic,1=domyslne,...
	bool insanity = false;
	

	float kula_x = okno_x / 2, kula_y = okno_y / 2;		// polozenie pierwotne kuli
	float blok_x = 50, blok_y = okno_y / 3.3;			// polozenie pierwszego bloku

	int ile_blokow = 55;		//ile miejc na mozliwe bloki  55
	float max_hp_blokow = 5;	//max poziom trudnosci bloczkow
	int hp = 6;			//ile razy mozna chybic
	int sp = 3;			//prawd specjalnego bloku   im mniejszy numer, tym wiecej sp
	int zero = 13;  //prawd na brak bloku. im mniej tym mniej blokow  0,1,2=zero blokow
	float moc = 1;//moc kuli do niszczenia blokow domyslnie 1
	float reset = 20;// xzas do resetu sp efektow (od niebieskixh blokow)  20= ok. 20s

	float ped_paletki = 20;
	float ped_kuli = 6;
	float ped_autobad = 9;
	float ped_bl = 0.5;

	std::string text = "press 1";
	std::string kom = " Arkanoid ";

	int vol_mu = 5; //glosnosc muzyki w tle
	int vol_ef = 5; //glosnosc efektow dzwiekowych

	bool obrazenie = false;
	int level = 0;
	 std::vector<int> completion;
	
};



class blok :public sf::Drawable
{
public:
	sf::RectangleShape b;
	float x, y;
	blok(float xi, float yi, dane d);

	float wytrzymalosc_bloczka = 0;// 0= nie ma   >0 = poziomy trudnosci bloczka
	bool special = false;
	bool faster = false;//do m.in lvl 5
	bool wasp = false;//do lvl 4
	float lixz = 3000;//do lvl1 i lvl6


	float ped = 0.5, ped2 = 0; 
	int zn = 0;// znaxznik do poxzatkowego tempa bloku

	void ruch(dane &d);

	void draw(sf::RenderTarget& cel, sf::RenderStates stan)const override
	{	cel.draw(this->b, stan);	}

};


//gracz
class player :public sf::Drawable {
public:
	sf::RectangleShape p;	dane da;
	float ax = da.player_ax;
	float by = da.player_by;
	sf::Vector2f rozmiar{ ax,by };
	sf::Vector2f poz{ (da.okno_x - da.player_ax) / 2, da.okno_y - da.player_by - 30 };
	player()
	{
		p.setPosition(poz);
		p.setSize(rozmiar);
		p.setFillColor(sf::Color::Black);
		p.setOutlineThickness(4);
		p.setOutlineColor(sf::Color::Magenta);
	}



	float ped = 3;float ped2 = 0;
	void ruch(dane d);
	sf::Vector2f predkosc2{ 0,0 };
	void ruch_auto(float pedk_x, float pozk_x, dane d);


	void draw(sf::RenderTarget& cel, sf::RenderStates stan)const override
	{		cel.draw(this->p, stan);	}
	

};


//przeciwnik
class badguy :public sf::Drawable {
public:
	sf::RectangleShape p;	dane da;
	float ax = da.player_ax, by = da.player_by;
	sf::Vector2f rozmiar{ ax,by };
	sf::Vector2f poz{ (da.okno_x - da.player_ax) / 2, 50 };
	badguy(dane d)
	{
		p.setPosition(poz);
		p.setSize(rozmiar);
		p.setFillColor(sf::Color::Black);
		p.setOutlineThickness(4);
		p.setOutlineColor(sf::Color::Green);
	}

	float ped = da.ped_autobad;
	float ped2 = 0;
	void ruch(dane d);

	sf::Vector2f predkosc2{ 0,0 };// poza void by dzialalo
	void ruch_auto(float pedk_x, float pozk_x, dane d);

	void draw(sf::RenderTarget& cel, sf::RenderStates stan)const override
	{		cel.draw(this->p, stan);	}

};


