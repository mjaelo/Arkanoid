#include "stdafx.h"
#include "kula.h"

using namespace sf;
using namespace std;


kula::kula()
{
	c.setPosition(du.kula_x, du.kula_y);
	c.setRadius(r);
	c.setFillColor(Color::Black);
	c.setOutlineThickness(5);
	c.setOutlineColor(Color::Red);
	c.setOrigin(r, r);
}

void kula::specjalny_efekt_bloczka(dane &d, vector<blok> &bloki, int &i) {
	//zaimplementowane:  0,1:kulka zwalnia 2x / kulka przyspiesza 2x   2,3: +1 zycie/-1 zycie   4,5:wieksza/mniejsza kula  6,7:slabe bloczki/mocne bloczki
	//  8:malo widoczna kula   9,10: wolniejsza/szybsza paletka   11,12: wieksza/mniejsza paletka   reszta: powrot do normy        

	bloki[i].wytrzymalosc_bloczka = 0;
	int ra = rand() % 14;

	if (ra == 0)
	{
		if (d.level == 8)ped = d.ped_kuli; predkosc.x = predkosc.y = ped / 2;	kom = "Slower  ";c.setFillColor(Color::Green);d.z_t = 1;
	}
	else if (ra == 1)
	{
		if (d.level == 8)ped = d.ped_kuli;predkosc.x = predkosc.y = -ped * 2;	 kom = "Faster  ";c.setFillColor(Color::Red);d.z_t = 1;
	}
	else if (ra == 2)
	{
		/*strata--; punkty--;*/d.hp++;	 kom = "   + hp   ";
	}
	else if (ra == 3)
	{
		if (d.hp - strata >1 && d.hp - strata >1) { /*strata++; punkty++;*/d.hp--; } kom = "   - hp   ";
	}
	else  if (ra == 4) { r = d.r * 2; c.setRadius(r); 	 kom = "   r++   ";c.setOrigin(r, r); }
	else  if (ra == 5) { r = d.r / 2; c.setRadius(r); 	 kom = "   r--   ";c.setOrigin(r, r); }
	else  if (ra == 6) { moc = d.moc * 3; c.setRadius(r); 	 kom = "Fireball   ";c.setOutlineColor(Color::Yellow); }
	else  if (ra == 7) { moc = d.moc / 3; 	 kom = "Baloon   ";c.setOutlineColor(Color::Magenta); }
	else  if (ra == 8)
	{
		moc = d.moc / 3; 	 kom = "Invisible   ";c.setFillColor(Color::Transparent);c.setOutlineColor(Color::Black);c.setOutlineThickness(2); d.z_t = 0;
	}
	else  if (ra == 9) { pal_zn = 2;  kom = "Slime "; }
	else  if (ra == 10) { pal_zn = 1; kom = "      Ice "; }
	else  if (ra == 11) { pal_zn = 3;  kom = "Smaller  "; }
	else  if (ra == 12) { pal_zn = 4; kom = "Larger   "; }


	else { powrot_do_normy(d);   kom = "Normal    "; }/**/


	cout << kom << endl;

}

void kula::powrot_do_normy(dane  &d) {
	if (ped == 0)ped = d.ped_kuli;
	if (predkosc.x >= 0)predkosc.x = ped;else predkosc.x = -ped; pal_zn = 0;
	if (predkosc.y >= 0)predkosc.y = ped;else predkosc.y = -ped;

	r = d.r;c.setRadius(r);	c.setFillColor(Color::White);
	moc = d.moc;	 c.setOutlineColor(Color::Black);c.setOutlineThickness(5);c.setOrigin(r, r);   d.z_t = 1; pal_zn = 0;
	kom = "";
}

void kula::kolizja_z_blokiem(dane &d,dane d_domyslne,vector<blok> &bloki)
{
	for (int i = 0;i<bloki.size();i = i + 1) //blokpoz ma x i y po sobie wiec 1 blok = 2 pozyje w wektorze
	{
		bool dtk = false;
		float l, p, g, b;


		//1sza kolizja
		/**/{
			 l = bloki[i].x;			 //lewa	krawedz
			 g = bloki[i].y;			 //gorna krawedz
			 p = bloki[i].x + d.blok_ax;//prawa krawedz
			 b = bloki[i].y + d.blok_by;//dolna krawedz(bottom)


			if (poz_kuli_x() + r <= l && poz_kuli_x() + r + predkosc.x >= l)//lewa kr
			{	if (poz_kuli_y() - r + predkosc.x > g && poz_kuli_y() + r + predkosc.x < b || poz_kuli_y() - r > g && poz_kuli_y() + r < b)
				{	predkosc.x = -predkosc.x;
					dtk = true;
				}		}
			else if (poz_kuli_x() - r > p && poz_kuli_x() - r + predkosc.x < p) //prawa kr
			{	if (poz_kuli_y() - r + predkosc.x > g && poz_kuli_y() + r + predkosc.x < b || poz_kuli_y() - r > g && poz_kuli_y() + r < b)
				{	predkosc.x = -predkosc.x;
					dtk = true;
				}		}

			if (poz_kuli_y() + r <= g && poz_kuli_y() + r + predkosc.y >= g) //gorna kr
			{	if (poz_kuli_x() - r + predkosc.y < p && poz_kuli_x() + r + predkosc.y > l || poz_kuli_x() - r < p && poz_kuli_x() + r > l)
				{	predkosc.y = -predkosc.y;
					dtk = true;
				}		}
			else if (poz_kuli_y() - r > b && poz_kuli_y() - r + predkosc.y < b) //dolna kr
			{	if (poz_kuli_x() - r + predkosc.y < p && poz_kuli_x() + r + predkosc.y > l || poz_kuli_x() - r < p && poz_kuli_x() + r > l)
				{	predkosc.y = -predkosc.y;
					dtk = true;
				}		}

			if (poz_kuli_x() < p && poz_kuli_x() > l && poz_kuli_y() > g && poz_kuli_y() < b)
				dtk = true;
		}/**/

		//2ga kolizja
		/**/{
		float l = bloki[i].x - r, g = bloki[i].y - r;	//lewa/gorna krawedz = x/y bloku
		float p = bloki[i].x + d.blok_ax + r, b = bloki[i].y + d.blok_by + r;//prawa/bottom krawedz


		if (poz_kuli_x() <= l + 5 && poz_kuli_x() > l - 5)//lewa kr
		{
			if (poz_kuli_y() > g && poz_kuli_y() < b && predkosc.x > 0) {
				predkosc.x = -predkosc.x;
				dtk = true;
			}
		}
		else if (poz_kuli_x() >= p - 5 && poz_kuli_x() < p + 5) //prawa kr
		{
			if (poz_kuli_y() > g && poz_kuli_y() < b && predkosc.x < 0) {
				predkosc.x = -predkosc.x;
				dtk = true;
			}
		}

		else	if (poz_kuli_y() > g && poz_kuli_y() < b) //moze rozdziele na 2
		{
			if (poz_kuli_x() > l && poz_kuli_x() < p) {
				predkosc.y = -predkosc.y;
				dtk = true;
			}
		}
		}/**/


		//nieudany teleport
		/*if (dtk) 
		{
			int max=100,may = 100;Vector2f pozk = c.getPosition();
			if (-l + pozk.x < max)max = l;
			if (p - pozk.x < max)max = p;
			if (g - pozk.y < max)may = g;
			if (-b + pozk.y < max)may = b;

			if (max < may)
				c.setPosition(max,pozk.y);
			if (may < max)
				c.setPosition(pozk.x,may);
		}*/

		if (dtk && zn_kolizja_boss) { bloki[i].wytrzymalosc_bloczka -= moc; dtk2 = true; }// wlasciwe niszczenie
		if (dtk && d.z_boss)bloki[i].wytrzymalosc_bloczka = 0;
		

		//spexjalny efekt bloxzka
	if (dtk && bloki[i].special)
		{	specjalny_efekt_bloczka(d, bloki, i);
			sp_zn = true;		}
		else if (dtk) { kom = "   "; }


		//zniszcznie bloczka
		if (int(bloki[i].wytrzymalosc_bloczka) <=0)
		{
			bloki.erase(bloki.begin() + i);
			i--; continue;
		}



		//sterowanie kula z WS
		if (d.z_kula_sterowanie == 1)
		{
			if (moc != 0) temp = moc;
			if (Keyboard::isKeyPressed(Keyboard::Key::W)) { if(predkosc.x>0)predkosc.x = -predkosc.x; moc = 0; }//kula w lewo
			else if (Keyboard::isKeyPressed(Keyboard::Key::S)) { if (predkosc.x<0)predkosc.x = -predkosc.x;moc = 0; }//kula w prawo
			else moc = temp; //gdy sie steruje kula to nie niszczy blokow
		}


		//powrot do normy co jakis czas
		if (sp_zn || d.insanity)licznik=temp_l = 0;	if (predkosc.x != 0 || d.z_boss)licznik += 0.001;
		if (licznik > d.reset) {
			powrot_do_normy(d); licznik = 0; cout << "auto norma" << endl; temp_l = 0;
		}
		
		if (int(licznik)-temp_l==1)
		{ 
			temp_l = int(licznik);
		cout << temp_l<< "  ";
		}
	}


	//cheats klawisze      = wl / - wyl
	if (Keyboard::isKeyPressed(Keyboard::Key::Equal)) { d.z_cheats = 1; kom = "cheats"; }
	if (Keyboard::isKeyPressed(Keyboard::Key::Dash)) { d.z_cheats = 0; kom = "   "; }
}
 
void kula::cheats(dane&d) {
	if (Keyboard::isKeyPressed(Keyboard::Key::Num1)) { powrot_do_normy(d); }//norma
	if (Keyboard::isKeyPressed(Keyboard::Key::Num0)) { predkosc.x = predkosc.y = 0; c.setFillColor(Color::Black); }//stop
	if (Keyboard::isKeyPressed(Keyboard::Key::Num2)) { predkosc.x = predkosc.y = ped * 2; c.setFillColor(Color::Red); }
	if (Keyboard::isKeyPressed(Keyboard::Key::Num3)) { predkosc.x = predkosc.y = -ped / 2; c.setFillColor(Color::Green); }
	if (Keyboard::isKeyPressed(Keyboard::Key::Add)) { d.hp++; }
	if (Keyboard::isKeyPressed(Keyboard::Key::Subtract)) { d.hp--; }
	if (Keyboard::isKeyPressed(Keyboard::Key::K)) { d.z_kula_sterowanie = 1; }
	if (Keyboard::isKeyPressed(Keyboard::Key::U)) { d.z_auto_graxz=1; }
	if (Keyboard::isKeyPressed(Keyboard::Key::Y)) { d.z_auto_graxz = 0; }
}



//to ruch i kolizja
void kula::ruch(vector <blok>&bloki, vector<float> poz_gracza, vector<float> poz_bad, dane &d,const dane d_domyslne)
{

	dtk2 = false;
	Vector2f poz;	poz.x = poz_kuli_x(); poz.y = poz_kuli_y();
	if (d.z_boss==false)
		c.move(predkosc);

	//to odbicie od krawedzi ekranu
	if (poz_kuli_x() < 0 + r)
	{		predkosc.x = -predkosc.x;  poz.x = 0 + r;	this->c.setPosition(poz);	}//lewo
	if (poz_kuli_x() > d.okno_x - r)
	{		predkosc.x = -predkosc.x; poz.x = d.okno_x - r;this->c.setPosition(poz);	}//prawo
	if (poz_kuli_y() < 0 + r)
	{
		predkosc.y = -predkosc.y;		if (d.z_przeciwnik > 0 && glowna) { punkty++;d.obrazenie = true; }	  poz.y = 0 + r;this->c.setPosition(poz);
		if (d_domyslne.z_boss) { c.setPosition(poz_gracza[0], d.okno_y - 50); zn_kolizja_boss = 0; }
	}//gora
	if (poz_kuli_y() > d.okno_y - r)
	{
		predkosc.y = -predkosc.y;		if (!d.z_boss && glowna) { strata++; if(glowna==true) d.obrazenie = true; }	poz.y = d.okno_y - r;this->c.setPosition(poz);
	}//dol





	 //kolizja z blokiem     
	kolizja_z_blokiem(d,d_domyslne,bloki);
	//zmiana wygladu bloczkow przy uderzeniu
	
	
	for(auto &bl:bloki)
	{ 
		int temp = bl.wytrzymalosc_bloczka;
	if (temp==1)bl.b.setFillColor(Color::Green);
	else if (temp == 2)bl.b.setFillColor(Color::Yellow);
	else if (temp == 3) bl.b.setFillColor(Color::Red);
	else if (temp > 3) bl.b.setFillColor(Color::Black);
	 if (bl.special) { bl.b.setFillColor(Color::Blue); bl.b.setOutlineColor(Color::Cyan); }  //special power
	}


	poz.x = poz_kuli_x(); poz.y = poz_kuli_y();
	//kolizja z graczem 
	if (poz_gracza[1] < poz_kuli_y() + r + 2 && poz_gracza[1] + d.player_by > poz_kuli_y())
	{
		if (poz_kuli_x() > poz_gracza[0] && poz_kuli_x() < poz_gracza[0] + d.player_ax)
		{
			if (predkosc.y>0)
			{
				predkosc.y = -predkosc.y;//odbixie
				c.setPosition(c.getPosition().x, poz_gracza[1]-r);

				if (d_domyslne.z_boss)d.z_boss=true;
			}//reset w bossie
		}
		if (poz_kuli_x() >= poz_gracza[0] && poz_kuli_x() - 5 < poz_gracza[0] + 15 && predkosc.x > 0)
		{	predkosc.x = -predkosc.x;predkosc.y = -predkosc.y;	}
		if (poz_kuli_x() <= poz_gracza[0] + d.player_ax + 5 && poz_kuli_x() > poz_gracza[0] + d.player_ax - 15 && predkosc.x < 0)
		{		predkosc.x = -predkosc.x;predkosc.y = -predkosc.y;	}//krawedzie to odbicie
		
	}



	//kolizja z przeviwnikiem
	if (poz_bad.size() != 0)
		if (poz_bad[1] > poz_kuli_y() - d.player_by - r - 2)
			if (poz_kuli_x() > poz_bad[0] && poz_kuli_x() < poz_bad[0] + d.player_ax)
			{
				if (predkosc.y < 0)
				{
					predkosc.y = -predkosc.y;
					c.setPosition(c.getPosition().x, poz_bad[1] + d.player_by+r);

					if (d_domyslne.z_boss) {c.setPosition(poz_gracza[0], d.okno_y - 200);predkosc.x = predkosc.y = d.ped_kuli;	d.z_boss=false; c.setFillColor(Color::Yellow); }//w bossie
				}
				//poz.y == wysokosc() - r - 1;this->c.setPosition(poz);

				if (poz_kuli_x() >= poz_bad[0] && poz_kuli_x() - 5 < poz_bad[0] + 15 && predkosc.x > 0)
				{			predkosc.x = -predkosc.x;predkosc.y = -predkosc.y;				}
				if (poz_kuli_x() <= poz_bad[0] + d.player_ax + 5 && poz_kuli_x() > poz_bad[0] + d.player_ax - 15 && predkosc.x < 0)
				{		predkosc.x = -predkosc.x;predkosc.y = -predkosc.y;			}
			}


	//kolizja gdy kosz-lvl7
	if (d.level == 7)
	{
		//kolizja z graczem2
		if (poz_gracza[1] < poz_kuli_y() + r + 2 && poz_gracza[1] + d.player_by > poz_kuli_y())
		{
			if (poz_kuli_x() > poz_gracza[0] + d.player_ax + 500 && poz_kuli_x() < poz_gracza[0] + d.player_ax * 2 + 500)
			{		if (predkosc.y>0)			predkosc.y = -predkosc.y;			}


			if (poz_kuli_x() >= poz_gracza[0] && poz_kuli_x() - 5 < poz_gracza[0] + 15 && predkosc.x>0)
				predkosc.x = -predkosc.x;
			if (poz_kuli_x() <= poz_gracza[0] + d.player_ax + 5 && poz_kuli_x() > poz_gracza[0] + d.player_ax - 15 && predkosc.x<0)
				predkosc.x = -predkosc.x;//krawedzie to odbicie
		}

		//kolizja z przeviwnikiem2
		if (poz_bad.size() != 0)
			if (poz_bad[1] > poz_kuli_y() - d.player_by - r - 2)
				if (poz_kuli_x() > poz_bad[0] + d.player_ax + 500 && poz_kuli_x() < poz_bad[0] + d.player_ax * 2 + 500)
				{
					if (predkosc.y < 0)
					{
						predkosc.y = -predkosc.y;
						poz.y == poz_kuli_y() - r - 1;this->c.setPosition(poz);
					}

					if (poz_kuli_x() >= poz_bad[0] && poz_kuli_x() - 5 < poz_bad[0] + 15 && predkosc.x>0)
						predkosc.x = -predkosc.x;
					if (poz_kuli_x() <= poz_bad[0] + d.player_ax + 5 && poz_kuli_x() > poz_bad[0] + d.player_ax - 15 && predkosc.x<0)
						predkosc.x = -predkosc.x;
				}

	}


	//cheaty
	if (d.z_cheats == 1)
	{
		cheats(d);
		
	}
}//koniec ruchu


 //sterowanie kula w boss
void kula::ruch_boss(dane &d, vector <blok>&bloki)
{
	predkosc.x = ped;predkosc.y = ped2;
	c.move(predkosc);

	//sterowanie
	Vector2f po = c.getPosition();

	if (Keyboard::isKeyPressed(Keyboard::Key::D) && po.x< d.okno_x - r - 10)
		ped = d.ped_kuli;
	else	if (Keyboard::isKeyPressed(Keyboard::Key::A) && po.x - 10 > 0)
		ped = -d.ped_kuli;
	else	ped = 0;

	if (Keyboard::isKeyPressed(Keyboard::Key::S) && po.y< d.okno_y - r - 10)
		ped2 = d.ped_kuli;

	else	if (Keyboard::isKeyPressed(Keyboard::Key::W) && po.y - 10 > 0)
		
		ped2 = -d.ped_kuli;
	else			ped2 = 0;

	//kolizja z blokiem 
	
	if (dtk2 && d.z_boss && zn_kolizja_boss) { strata++;d.obrazenie = true;cout << " jest "; zn_kolizja_boss = false; }
	if (!zn_kolizja_boss)ped=ped2 = 0;

	if (!Keyboard::isKeyPressed(Keyboard::Key::W) && !Keyboard::isKeyPressed( Keyboard::Key::S)&&!Keyboard::isKeyPressed(Keyboard::Key::A)&&!Keyboard::isKeyPressed(Keyboard::Key::D))
		zn_kolizja_boss = true;
}
