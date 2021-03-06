
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
#include"kula.h" 
   
   
using namespace sf;
using namespace std;  
  
//STEROWANIE:  A D pl 1     left right pl2    P O wl/wyl pl2  I auto pl2     (0stop 1normalne 2szybkie  3wolne) tempo   
//W S sterowanie kula w niektorych poziomach		9=xhange musix
  		

//PLANY:  
//?:
//	 fix auto norma,			goal: autobad,				lepsza kolizja?,		 problemy z insanity,			fix zmiany tekstur na poziomy i easter eggi?				
			



//napisy menu glownego
vector<tekst>menu_gl(Text &text,dane d)
{ 
	vector<tekst>teksty;
	for (int i = 0;i < 7;i++)
	{ 
		tekst t;
		if (i == 0)t.m = "1  Play";
		else if (i == 1) t.m = "2  Settings";
		else if (i == 2) t.m = "3  Quit";
		else t.m = " ";
		
		t.poz_m.y = i * 100 + 200;  t.poz_m.x = d.okno_x / 4;
		t.m_txt = text;
		t.m_txt.setPosition(t.poz_m);
		teksty.push_back(t);
		t.m_txt.setCharacterSize(100);
	}    
	return teksty; 
}

// robienie vectora blokow
void make_blok(vector <blok>&blokowisko, vector <float>&blokpoz, dane d)
{	
	bool pusty = true;
	vector<blok> b;blokowisko = b; //reset
	int j = 0; float y = d.blok_y; //daje pierwotna wartosc y
	cout << "stworzono bloki  \n";
	
	int przes_x = d.blok_ax*1.5, przes_y = d.blok_by*1.5;//automatyczne przesuniecie pozycji blokow
	for (int i = 0;i < d.ile_blokow;i++)
	{
		float x = d.blok_x + j * przes_x; //pozycja blokow w danym rzedzie 
		if (x > d.okno_x - d.blok_ax)
		{
			x = d.blok_x;	y = y + przes_y;	j = 0;
		}//kolejny rzad
		j++;

		blok Bl(x, y, d);
		    

		if (Bl.wytrzymalosc_bloczka >0)// jesli nie usuniety
		{
			pusty = false;
			blokowisko.push_back(Bl);
			blokpoz.push_back(x);   blokpoz.push_back(y);
		} 
	}   
	 
	//zabespieczenie przed pusta plansza	
	if (pusty) { cout << "pusty "; make_blok(blokowisko, blokpoz, d); }

}

//koniec gry 
bool game_over(dane &d, kula &Kula, int &start, vector <blok>&blokowisko, Text &kom, int &zn, badguy &bad)
{	int completion = 0;
	int wygrana = 1;
	if (d.z_przeciwnik == 0)// koniec gry w singleplayer
	{
		for (auto e : blokowisko) { if (e.wytrzymalosc_bloczka >0) wygrana = 0; }
		if (wygrana == 1)
		{
			start = 3;		d.kom = "You Won !";kom.setFillColor(Color::Cyan);
			d.text = " Press enter to exit";  completion = 1;
		}
		if (Kula.strata >= d.hp && start != 0)
		{
			start = 3;		d.kom = "Game Over"; kom.setFillColor(Color::Red);
			d.text = " Press enter to exit";
		} 
	}
	else//koniec gry w versus
	{
		
		for (auto e : blokowisko)
			if (e.wytrzymalosc_bloczka > 0) wygrana = 0;
		if (wygrana == 1 && zn == 1)
		{
			Kula.powrot_do_normy(d);
			Kula.predkosc.x *= 3; Kula.predkosc.y *= 3; bad.ped *= 2;
			Kula.c.setFillColor(Color::Magenta);  kom.setFillColor(Color::Red);zn = 0;
		}
		if (wygrana == 1) { d.kom = "Insanity";d.insanity = true; }

		if (Kula.strata >= d.hp)
		{
			start = 3;		d.kom = "Game Over ";  kom.setFillColor(Color::Green);
			d.text = "Player  2  is the Winner";wygrana = 0;
		}
		else if (Kula.punkty >= d.hp)
		{
			start = 3;		d.kom = "Game Over ";    kom.setFillColor(Color::Magenta);
			d.text = " Player  1  is the Winner";completion = 1;wygrana = 1;
		}
	}
	
	if (completion == 1 && Kula.strata == 0) { completion = 2; }
	if(completion>d.completion[d.level])
	d.completion[d.level] = completion;
	if (wygrana == 1)return true; else return false;
}
   
void wydarzenia_z_paletka(dane &d,dane &d_domyslne,player &Player,badguy &bad,kula Kula,Sprite &pl,Sprite &bd )
{
	Player.p.setSize({ d.player_ax,d.player_by });bad.p.setSize({ d.player_ax,d.player_by });
	
	Vector2f skala4{ d.player_ax / 540 ,   d.player_by / 360 };pl.setScale(skala4);bd.setScale(skala4);
	if (Kula.pal_zn == 0)//norma
	{

		d.ped_paletki = d_domyslne.ped_paletki;d.ped_autobad = d_domyslne.ped_autobad;	 Player.p.setFillColor(Color::Black);
		bad.p.setFillColor(Color::Black);    d.player_ax = d_domyslne.player_ax;d.player_by = d_domyslne.player_by;
	}
	else {
		if (Kula.pal_zn == 1)
		{
			d.ped_paletki = d_domyslne.ped_paletki * 2;  Player.p.setFillColor(Color::Cyan);bad.p.setFillColor(Color::Cyan);
			d.ped_autobad = d_domyslne.ped_autobad * 2;
		}
		else if (Kula.pal_zn == 2)
		{
			d.ped_paletki = d_domyslne.ped_paletki / 2; Player.p.setFillColor(Color::Green);bad.p.setFillColor(Color::Green);
			d.ped_autobad = d_domyslne.ped_autobad / 2;
		}

		else if (Kula.pal_zn == 3)
		{
			d.player_ax = d_domyslne.player_ax / 2;d.player_by = d_domyslne.player_by / 2;  Player.p.setOrigin(0, 0);
		}
		else if (Kula.pal_zn == 4)
		{
			d.player_ax = d_domyslne.player_ax * 2;d.player_by = d_domyslne.player_by * 2;		Player.p.setOrigin(0, 0);
		}
	}
}





void menu_gry(RenderWindow &okno,dane &d,vector<tekst> &teksty,Text &text,Text &kom,Vector2f &poz_kom,int &lvl) {
	//napisy menu
	for (auto t : teksty)
	{
		t.m_txt.setString(t.m);
		okno.draw(t.m_txt);
	}
	auto poz = poz_kom;  poz.y -= 300;      kom.setPosition(poz);
	kom.setString("Arkanoid");  kom.setFillColor(Color::White);  okno.draw(kom);


	if (lvl == 0)//menu glowne
	{
		teksty = menu_gl(text, d);
		if (Keyboard::isKeyPressed(Keyboard::Key::Num1)) { lvl = 1; }//wlaczenie planszy
		else if (Keyboard::isKeyPressed(Keyboard::Key::Num2)) { lvl = 3; }//ustawienia
		else if (Keyboard::isKeyPressed(Keyboard::Key::Num3)) { lvl = -1; }
	}
	else	if (lvl == 1)
	{
		if (!Keyboard::isKeyPressed(Keyboard::Key::Num1)) lvl = 2;
	} //aby nie bylo podwojnego nacisniecia num1
		

	else	if (lvl == 3)
	{
		if (!Keyboard::isKeyPressed(Keyboard::Key::Num2))lvl = 4;
	}
	
}

void rysowanie_poziomu(dane&d,RenderWindow &okno,player & Player,badguy &Bad, kula &Kula,vector<kula>&kulki,vector<float>&poz_gracza, vector<float>&poz_bad,Sprite& kol, Sprite&pl, Sprite&bd) {
	
	okno.draw(Kula);
	
	if (d.z_t == 1) {
		Vector2f skala5{ (float)Kula.r / 145,(float)Kula.r / 145 };kol.setScale(skala5);
		auto poz_k = Kula.c.getPosition();kol.setPosition(poz_k.x - Kula.r, poz_k.y - Kula.r);okno.draw(kol);
	}//tekstura kuli

	if (d.z_2 > 0)for (auto &k : kulki) {
		k.c.setFillColor(Color::Blue); okno.draw(k);
		Vector2f skala5{ (float)k.r / 145,(float)k.r / 145 };kol.setScale(skala5);
		auto poz_k = k.c.getPosition();kol.setPosition(poz_k.x - k.r, poz_k.y - k.r);okno.draw(kol);
	}//rysowanie dodatkowyxh kul

	okno.draw(Player);
	pl.setPosition(poz_gracza[0], poz_gracza[1]);		okno.draw(pl); //tekstura graxza

	if (d.z_przeciwnik > 0)
	{		okno.draw(Bad);		   bd.setPosition(poz_bad[0], poz_bad[1]); okno.draw(bd);	}//przeciwnik
}

void start_gry(dane&d,dane&d_domyslne, player & Player, badguy &Bad, kula &Kula,vector<blok>&blokowisko, vector<float>&poz_gracza, vector<float>&poz_bad)
{
	if (d.z_boss)   Kula.ruch_boss(d, blokowisko);
	for (auto&Bl : blokowisko)	if (d.z_b == 1) Bl.ruch(d);
	Kula.glowna = true;//to glowna kula
	Kula.ruch(blokowisko, poz_gracza, poz_bad, d, d_domyslne);

	

	//lixzenie ile aktywnyxh blokow na planszy
	int s = 0;
	for (auto e : blokowisko)
	{
		if (e.wytrzymalosc_bloczka > 0)
			s++;
	}

	//ustawienia do poziomow
	for (auto &e : blokowisko)
	{
		if (d.level == 3 && e.wytrzymalosc_bloczka < d.max_hp_blokow)//regeneraxja blokow
			if (rand() % 8000< 10)e.wytrzymalosc_bloczka++;

		if (e.wasp)//kolizja z osa
		{
			auto po = e.b.getPosition();
			if (po.y >= poz_gracza[1] && po.x >= poz_gracza[0] && po.x <= poz_gracza[0] + d.player_ax)
			{
				Kula.strata++;d.obrazenie = true;std::cout << "ouxh!\n";e.wytrzymalosc_bloczka = 0;
			}
			if (d.z_przeciwnik&&po.y <= poz_bad[1] && po.x >= poz_bad[0] && po.x <= poz_bad[0] + d.player_ax)
			{
				Kula.punkty++;d.obrazenie = true;std::cout << "ouxh!\n";e.wytrzymalosc_bloczka = 0;
			}

		}
	}
	if (d.level == 5) { Kula.kom = "       " + to_string(s); }
	if (d.level == 9)
	{
		int r = rand() % 2000;
		if (s<d.ile_blokow / 2 && r<10)
		{
			cout << "za malo";
			int xb = rand() % int(d.okno_x - d.blok_ax);
			int yb = rand() % int(d.okno_y - d.blok_by);
			blok b(xb, yb, d);
			blokowisko.push_back(b);//dodawanie bloku
		}
	}

	
}


//to robienie okna, deklaracja waznych rzeczy, itp
int main()
{ 
	// to deklaracje danyvh
	menu m;dane d;	kula Kula; player Player;badguy Bad(d);
	player Player2;badguy Bad2(d);//do kosza - lvl7
	dane d_domyslne;//dane reset
	int start = 0; //znacznik do poczatku gry   0 menu, 1 wczytanie poziomu,2 gra, 3 koniec gry
	int lvl = 0;//sterowanie w menu		1=level,	2=settings
	 
	int zn = 1;   //znacznik przy koncu gry versus
	int znak = 0; //znacznik do generacji blokow
	int z_kulki = 0;
	
	kula Kula2; kula Kula3;  kula Kula4; kula Kula5;// do ozdoby menu
	 
	RenderWindow okno{ VideoMode{ d.okno_x,d.okno_y },"Arkanoid" };
	okno.setFramerateLimit(d.fps);
	Event ev;
	  
	for (int i = 0;i < 10;i++)d.completion.push_back(0); d_domyslne.completion = d.completion;
	

	  
	//dane tekstu
	Vector2f poz_txt;	poz_txt.x = d.okno_x / 2 - 120;	poz_txt.y = 0;
	sf::Font font;	if (!font.loadFromFile("font1.otf"))cout << "error ";
	sf::Text text;
	text.setFont(font);	text.setPosition(poz_txt);	
	text.setCharacterSize(50); 	text.setOutlineThickness(1);	text.setOutlineColor(Color::Black);

	//dane kounikatu
	Vector2f poz_kom;	poz_kom.x = d.okno_x / 3;	poz_kom.y = d.okno_y / 3;
	sf::Text kom;	kom.setFont(font);		kom.setPosition(poz_kom);
	kom.setCharacterSize(100);		kom.setFillColor(Color::Cyan);
	text.setOutlineThickness(1);	text.setOutlineColor(Color::Black);
	
	// dane tekstury tla
	float ox = d.okno_x,oy=d.okno_y; 
	sf::Texture txt;
	if (d.okno_x >= d.okno_y) { if (!txt.loadFromFile("dane/blue_geo_bg.png"))	cout << " error bg "; }
	else	if (!txt.loadFromFile("dane/blue_geo_bg2.png"))	cout << " error bg ";
	sf::Sprite bg(txt); 
	Vector2f skala{ 1600 / ox,950 / oy };bg.setScale(skala);
	
	sf::Texture txt_boss;
	 if (!txt_boss.loadFromFile("dane/boss.png"))	cout << " error bg "; 
	sf::Sprite bg_boss(txt_boss);
	Vector2f skala_boss{ 1600 / ox,950 / oy };bg_boss.setScale(skala_boss);

	    
	// dane tekstury menu
	sf::Texture txt2;
	if (!txt2.loadFromFile("dane/menu.png"))	cout << " error bg ";
	sf::Sprite menu(txt2); 
	Vector2f skala2{1600/ox,950/oy};	menu.setScale(skala2);

	//dane tekstury blokow
	sf::Texture txt3;   vector<Texture> bl_txt;
	for (int i = 1;i <= 7;i++)
	{	if (!txt3.loadFromFile("blok_overlay/blok_overlay" + to_string(i) + ".png"))	cout << " error bl ";
		bl_txt.push_back(txt3);
	}
	txt3 = bl_txt[0];
	sf::Sprite bl(txt3);//domyslna tekstura

	Texture txt_java;txt_java.loadFromFile("blok_overlay/java.png");//easter egg
	Texture txt_mario;txt_mario.loadFromFile("blok_overlay/mario.png");//easter egg


	// dane tekstury paletek
	Sprite bd = bl;// graxz i przexiwnik
	Sprite bd2,pl2 = bl;//do kosza - lvl7
	Sprite pl = bl;//blok
	     
	//dane tekstury kola
	sf::Texture txtk;   vector<Texture> kol_txt;
	for(int i=1;i<=9;i++)
	{ 	if (!txtk.loadFromFile("kula_overlay/kolo_overlay"+to_string(i)+".png"))	cout << " error kol ";	
	kol_txt.push_back(txtk);
	}
	txtk = kol_txt[0];sf::Sprite kol(txtk);//domyslna tekstura

	Texture txt_mar;txt_mar.loadFromFile("kula_overlay/mario.png");//easter egg
	

	//tworzenie vectora do przechowywania blokow
	vector <blok>blokowisko;vector <float>blokpoz;
	make_blok(blokowisko, blokpoz, d);

	//napisy menu
	vector<tekst> teksty=menu_gl(text, d);
	//dodatkowe kulki w lvl
	vector<kula>kulki;
	


	//muzyka
	SoundBuffer buffer;
	vector<SoundBuffer>buf_sg;// 1=menu dalej poziom
	for (int i = 1;i <= 5;i++)
	{
		if (!buffer.loadFromFile("dane/song" + to_string(i) + ".Ogg"))	cout << " error kol ";
		buf_sg.push_back(buffer);
	}
	sf::Sound sound,slvl;
	sound.setBuffer(buf_sg[0]);
	sound.setVolume(d.vol_mu);slvl.setVolume(d.vol_mu);

	sf::SoundBuffer bufboss;
	if (!bufboss.loadFromFile("dane/songboss.ogg"))
		cout << "error boss";
	sf::Sound sboss;
	sboss.setBuffer(bufboss);
	sboss.setVolume(d.vol_mu);



	sf::SoundBuffer buf;
	Sound sp, damage,win, lose;
vector<SoundBuffer>buf_ef;// 1=sp,2=damage,3=win,4=lose

if (!buf.loadFromFile("dane/sound1.Ogx"))	cout << " error kol ";
buf_ef.push_back(buf);
for (int i = 2;i <= 4;i++)
{
	if (!buf.loadFromFile("dane/sound" + to_string(i) + ".Ogg"))	cout << " error kol ";
	buf_ef.push_back(buf);
}
		sp.setBuffer(buf_ef[0]);		sp.setVolume(d.vol_ef);
		damage.setBuffer(buf_ef[1]);		damage.setVolume(d.vol_ef+5);
		win.setBuffer(buf_ef[2]);		win.setVolume(d.vol_ef);
		lose.setBuffer(buf_ef[3]);		lose.setVolume(d.vol_ef);
		
















		
	while (true)
	{
		okno.clear();//reset okna
		d.obrazenie = false;

		
		 //pozycje graczy
		if (Keyboard::isKeyPressed(Keyboard::Key::P))d.z_przeciwnik = 1; //przeciwnik sterowanie reczne
		if (Keyboard::isKeyPressed(Keyboard::Key::I))d.z_przeciwnik = 2; //przeciwnik autopilot
		if (Keyboard::isKeyPressed(Keyboard::Key::O))d.z_przeciwnik = 0; //przeciwnik wylaczony

		vector<float>  poz_gracza{ Player.p.getPosition().x,Player.p.getPosition().y };
		vector<float> poz_bad;
		if (d.z_przeciwnik > 0) {	poz_bad.push_back(Bad.p.getPosition().x);		poz_bad.push_back(Bad.p.getPosition().y);   }


		   
		//menu 
		if (start == 0) {
			okno.draw(menu);//tlo
			vector<kula>temp;kulki = temp; z_kulki = 0;//reset kulek w poziomie
			 
			//kule latajace po ekranie menu dla ozdoby 
			okno.draw(Kula2);  Kula2.ruch(blokowisko, poz_gracza, poz_bad,d, d_domyslne); Kula2.c.setRadius(50); Kula2.c.setFillColor(Color::Transparent);Kula2.c.setOutlineColor(Color::Green);Kula2.c.setOutlineThickness(10);
			okno.draw(Kula3); Kula3.predkosc.x = -Kula2.predkosc.x - 4; Kula3.ruch(blokowisko, poz_gracza, poz_bad,d, d_domyslne); Kula3.c.setRadius(30); Kula3.c.setFillColor(Color::Transparent);Kula3.c.setOutlineColor(Color::Magenta);Kula3.c.setOutlineThickness(10);
			okno.draw(Kula4); Kula4.predkosc.x = rand() % 100 - 50; Kula4.predkosc.y = rand() % 100 - 50; Kula4.ruch(blokowisko, poz_gracza, poz_bad,d, d_domyslne); Kula4.c.setRadius(20); Kula4.c.setFillColor(Color::Transparent);Kula4.c.setOutlineColor(Color::Blue);Kula4.c.setOutlineThickness(10);
			okno.draw(Kula5); Kula5.predkosc.y = -Kula2.predkosc.y * 3; Kula5.predkosc.x = -Kula2.predkosc.x * 3; Kula5.ruch(blokowisko, poz_gracza, poz_bad,d, d_domyslne); Kula5.c.setRadius(70); Kula5.c.setFillColor(Color::Transparent); Kula5.c.setOutlineColor(Color::Cyan);Kula5.c.setOutlineThickness(10);
			

			menu_gry(okno, d, teksty, text, kom, poz_kom, lvl);

			if (lvl == -1)return 0;

			if (lvl == 4)
				m.settings(start, lvl, okno, teksty, d, znak, sound, sp, txtk, kol_txt, txt3, bl_txt);	//ustawienia

			if (lvl == 2)
				m.lev(start, lvl, okno, teksty, d, znak); //wybor poziomow - kazdy poziom ma swoje dane wejsxiowe d

		}  
		//zaladowanie poziomu
		else	
		{   //reset  
			if (start == 1)
			{ 
				//dane z lvl jako domyslne
				d_domyslne = d;
				
				//kule 
				Kula.powrot_do_normy(d);
				Kula.c.setPosition(d.kula_x, d.kula_y);
				Kula.c.setRadius(d.r);Kula.ped = d.ped_kuli;
				if (d.z_2 > 0 && z_kulki == 0) for (int i = 0;i < d.z_2;i++)	{ Kula2 = Kula;Kula2.c.setPosition(d.kula_x, d.kula_y);  kulki.push_back(Kula2); z_kulki = 1; }
				if (m.easter_egg == 2)kol.setTexture(txt_mar);
				else if (d.level == 7)kol.setTexture(kol_txt[2]);
				else kol.setTexture(txtk);

				//texty
				kom.setFillColor(Color::Cyan); d.kom = "Start!"; d.text = "press enter";
				poz_txt.y = d.okno_y / 2;		text.setPosition(poz_txt);kom.setPosition(poz_kom);
				   
				//bloki 
				bool pusty = true;
				for (auto &Bl : blokowisko) { if (Bl.wytrzymalosc_bloczka > 0)pusty = false; }
				if (pusty)make_blok(blokowisko, blokpoz, d);
				sf::Vector2f skala3{  d.blok_ax/540 ,  d.blok_by/ 360 };
				if (m.easter_egg==1)bl.setTexture(txt_java);
				else if (d.level == 1)bl.setTexture(bl_txt[1]);
				else if (d.level == 2)bl.setTexture(bl_txt[2]);
				else		bl.setTexture(txt3);
				
				//graxze
				Vector2f s{ d.player_ax, d.player_by };				Player.p.setSize(s);	Bad.p.setSize(s);// w menu=2 i tak by to sie unormalnlo, ale po xo xzekax
				
				if (znak == 0)
				{ 	bl.setScale(skala3);    make_blok(blokowisko, blokpoz, d); 		znak = 1; 	}
				
				//paletka 
				Kula.pal_zn = 0;  Player.p.setPosition(Player.poz); Bad.p.setPosition(Bad.poz);	
				sf::Vector2f skala4{ d.player_ax / 540 ,   d.player_by / 360 };
				pl.setScale(skala4);bd.setScale(skala4);
				if (d.level == 7) { Player2 = Player; Player.p.setPosition(Player.poz.x-1000,Player.poz.y); Bad.p.setPosition(Bad.poz.x - 1000, Bad.poz.y);}
				
			
				
			} 



			if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) 
			{start = 0; Kula.strata = 0; Kula.punkty = 0;    make_blok(blokowisko, blokpoz, d);	}//powrot do menu
		 
			//rysowanie planszy
			if (d.z_boss)	okno.draw(bg_boss);
			else			okno.draw(bg);
			rysowanie_poziomu(d, okno,Player,  Bad,  Kula,kulki, poz_gracza, poz_bad,	kol, pl, bd);
			
			for (auto &Bl : blokowisko)  if (Bl.wytrzymalosc_bloczka > 0) {		  //rysowanie blokow
				
				if (Bl.wasp) {	 bl.setTexture(bl_txt[6]);		}

				else if (m.easter_egg == 2) {		if (Bl.special == false) bl.setTexture(txt_mario);else bl.setTexture(bl_txt[5]);		}

				else bl.setTexture(txt3);

				okno.draw(Bl); 			bl.setPosition(Bl.x, Bl.y);		 okno.draw(bl);
			} //tekstury blokow
			
			if (d.level == 7)
			{
				Player2 = Player; Player2.p.setPosition(poz_gracza[0] + d.player_ax + 500, poz_gracza[1]); pl2 = pl;
				pl2.setPosition(Player2.p.getPosition());		okno.draw(Player2);        okno.draw(pl2);
			
			if (d.z_przeciwnik>0)
				{	Bad2 = Bad;		Bad2.p.setPosition(poz_bad[0] + d.player_ax + 500, poz_bad[1]);bd2 = bd;
					bd2.setPosition(Bad2.p.getPosition());		okno.draw(Bad2);		okno.draw(bd2);			}
			}//kosz
			okno.draw(text);
			okno.draw(kom);

			  
			

			//ruxhy
			if (d.z_auto_graxz)
				Player.ruch_auto(Kula.predkosc.x, Kula.c.getPosition().x, d);
			else  Player.ruch(d); 

			if (d.z_przeciwnik == 1)
				Bad.ruch(d); 
			if (d.z_przeciwnik >1)
				Bad. ruch_auto(Kula.predkosc.x, Kula.c.getPosition().x,d);
			

			
			  
			if (Keyboard::isKeyPressed(Keyboard::Key::Return))	start = 2;//poczatek gry
			  //uruchamianie gry
			if (start == 2) 
			{
				if (d.z_2 > 0)	for (auto &k : kulki) { k.glowna = false; k.ruch(blokowisko, poz_gracza, poz_bad, d, d_domyslne); }
				d.kom = "    ";poz_txt.y = 0;text.setPosition(poz_txt);

				start_gry(d, d_domyslne, Player, Bad, Kula, blokowisko,poz_gracza,poz_bad);

				wydarzenia_z_paletka(d, d_domyslne, Player, Bad, Kula, pl, bd);
			}
				
			


			//koniec gry
			bool wygrana = game_over(d, Kula, start, blokowisko, kom, zn, Bad);

			//wyjscie
			if (start == 3)
			{
			if(wygrana&& win.getStatus()!=2)win.play();
			if(!wygrana&& lose.getStatus() != 2 )lose.play();

				if (Keyboard::isKeyPressed(Keyboard::Key::Return)) //powrot do menu
				{
					start = 0; Kula.strata = 0; Kula.punkty = 0;    make_blok(blokowisko, blokpoz, d);znak = 1; //poczatkowe dla menu
				}
				poz_txt.y = d.okno_y / 2;		text.setPosition(poz_txt);
			}

			//tablica wynikow
			if (start == 2)
			{
				d.text = "hp:  " + to_string(d.hp - Kula.strata);
				if (d.z_przeciwnik>0)
					d.text = d.text + "  :  " + to_string(d.hp - Kula.punkty);
			}
			text.setString(d.text);

			if (start == 2 && !wygrana)d.kom = Kula.kom;
			kom.setString(d.kom);
		} 


		if(Keyboard::isKeyPressed(Keyboard::Key::Num9))slvl.setBuffer(buf_sg[rand() % 5]);

		//dzwiek
		if (start == 0 && sound.getStatus() != 2) { sound.play(); sboss.stop();slvl.stop();  }
		else 	if (d.level != 8 && slvl.getStatus() != 2 && start != 0) { slvl.setBuffer(buf_sg[rand() % 5]); slvl.play(); sound.stop(); }
		else 	if (d.level == 8 && sboss.getStatus() != 2&& start!=0) {sboss.play(); sound.stop();  }
	
		if (Kula.sp_zn)
		{	sp.play();		Kula.sp_zn = false;		}
		if (d.obrazenie == true && start==2) { damage.play(); cout << "ouxh\n"; }
		 
		
		//dodatkowe ustawienia
		kom.setOutlineThickness(1);
		sp.setVolume(d.vol_ef);		damage.setVolume(d.vol_ef + 5);		win.setVolume(d.vol_ef);
		lose.setVolume(d.vol_ef);	sboss.setVolume(d.vol_mu);			slvl.setVolume(d.vol_mu-2);
		 

		//zdarzenia w programie
		okno.pollEvent(ev);
		if (ev.type == Event::Closed) { okno.close();	break; }
		okno.display();
	}


	return 0;
}




