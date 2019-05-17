#include "stdafx.h"
#include "menu.h"

using namespace sf;
using namespace std;

void menu::lev1(int &start, int&lvl, RenderWindow &okno, vector<tekst> &teksty, dane &d, int &znak)
{

	for (int i = 0;i < teksty.size();i++)
	{
		teksty[i].m_txt.setCharacterSize(40);
		if (i == 0) teksty[i].m = "q:   Quickplay ";
		else if (i == 1) teksty[i].m = "1:    lvl 1- Wonderwall  ";
		else if (i == 2) teksty[i].m = "2:   lvl 2- Virus";
		else if (i == 3) teksty[i].m = "3:   lvl 3- Titans";
		else if (i == 4) teksty[i].m = "4:   lvl 4- hive";
		else if (i == 5) teksty[i].m = "enter:    next page";
		else if (i == 6) teksty[i].m = "esc:  back      I: info";

	if (i<5 && d.completion[i] == 1)teksty[i].m_txt.setFillColor(Color::Green);
	else if (i<5 && d.completion[i] == 2)teksty[i].m_txt.setFillColor(Color::Yellow);
	else teksty[i].m_txt.setFillColor(Color::White);
	}
	

	if (Keyboard::isKeyPressed(Keyboard::Key::Q))
	{
		d = da;
		znak = 0; start = 1;d.z_t = 1;d.level = 0;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num1))
	{
		d = da;d.ile_blokow = 100;d.sp = 1;d.blok_y = 50;d.zero = 100;d.blok_ax = d.blok_by = 60;d.ped_bl = 0;d.z_b = 1;
		znak = 0; start = 1;d.level = 1;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num2))
	{
		d = da;d.ile_blokow = 60;d.blok_y = 100; d.blok_outline = 100;
		znak = 0; start = 1;d.level = 2;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num3))
	{
		d = da;d.ile_blokow = 10;d.blok_y = 50; d.blok_ax = d.blok_by = 200;d.sp = 500;d.max_hp_blokow = 5;d.moc = 0.5; d.ped_kuli *= 1.5; d.zero = 7; d.z_b = 1;
		znak = 0; start = 1;d.level = 3;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num4))
	{
		d = da;
		d.ile_blokow = 330;d.blok_y = 50; d.blok_ax = d.blok_by = 40;d.player_ax = d.player_by = 80;  d.r = 5;d.zero = 4;
		d.z_kula_sterowanie = 1;	d.max_hp_blokow = 4;	d.ped_kuli -= 3; d.z_b = true; d.ped_bl = 0.005;
		znak = 0; start = 1;d.level = 4;
	}

	else if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
	{
		page = 0;lvl = 0;start = 0;d.level = 5;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Return))
	{
		page = 1;
	}//2ga strona
	else if (Keyboard::isKeyPressed(Keyboard::Key::I))
	{
		teksty[0].m = "Q: default level ";teksty[1].m = "1: defeat evil mage with special blocks ";teksty[2].m = "2: defeat virus corrupting your blocks";
		teksty[3].m = "3: beat big, bad, black, bouncy, baby blocks";teksty[4].m = "4: defeat wasps by steering your ball with W,S ";
	}

	if (page == 1)lev2(start, lvl, okno, teksty, d, znak);
}

void menu::lev2(int &start, int&lvl, RenderWindow &okno, vector<tekst> &teksty, dane &d, int &znak)
{

	for (int i = 0;i < teksty.size();i++)
	{
		teksty[i].m_txt.setCharacterSize(40);
		if (i == 0) teksty[i].m = "5:   lvl5- ball-ognese ";
		else if (i == 1) teksty[i].m = "6:    lvl 6- cleaning duty";
		else if (i == 2) teksty[i].m = "7:   lvl 7- goal!";
		else if (i == 3) teksty[i].m = "8:   lvl 8- boss";
		else if (i == 4) teksty[i].m = "9:   lvl 9- all-stars";
		else if (i == 5) teksty[i].m = "backspace:    last page";
		else if (i == 6) teksty[i].m = "esc:   back   I: info ";

		if (i<5 &&d.completion[i+5] == 1)teksty[i].m_txt.setFillColor(Color::Green);
		else if (i<5 && d.completion[i + 5] == 2)teksty[i].m_txt.setFillColor(Color::Yellow);
		else teksty[i].m_txt.setFillColor(Color::White);
	}

	int suma = 0;bool locked = true;
	for (auto e : d.completion) { suma += e; }
	if (d.completion[8] >0 || suma >= 5)
		locked = false;


	if (Keyboard::isKeyPressed(Keyboard::Key::Num5))
	{
		d = da;
		d.z_2 = 4;  d.blok_ax *= 0.7; d.blok_by *= 0.7;d.ile_blokow*=8;d.blok_y =-float(d.okno_y+d.ile_blokow+100);d.zero = 3;
		d.r *= 0.75; d.z_b = true; d.z_kula_sterowanie = 1;d.z_auto_graxz = 1; d.ped_bl;
		znak = 0; start = 1; d.level = 5;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num6))
	{
		d = da;
		d.r = 100; d.z_b = 1; d.blok_ax = 20; d.blok_by = 10; d.ile_blokow = 2500; d.zero = 3; d.blok_y -= 200; d.ped_bl = 5;d.moc = 2;d.z_kula_sterowanie = 1;
		znak = 0; start = 1;d.level = 6;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num7))
	{
		d = da;
		d.z_przeciwnik = 2;d.player_ax = 1000; d.ped_kuli += 5; d.zero = 3;d.blok_ax *= 0.75;d.blok_by *= 0.75;d.ile_blokow = 100;d.z_b = 1;d.ped_bl = 0.1;
		znak = 0; start = 1;d.level = 7;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num8))
	{
		d = da;
		d.z_b = 1;  d.z_kula_sterowanie = 1;d.z_boss = true; d.z_przeciwnik = 2;d.zero = 3; d.blok_ax /= 2; d.blok_by /= 2;
		d.ped_autobad = d.ped_kuli/3;	d.r = 25; d.hp = 5;d.max_hp_blokow--;
		d.kula_y = d.okno_y - 10;d.ile_blokow = 400; d.blok_y = 100; d.z_auto_graxz = 1;
		znak = 0; start = 1;d.level = 8;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num9))
	{		
		if(!locked || Keyboard::isKeyPressed(Keyboard::Key::L)){
			d = da;
			d.blok_outline *= 8; d.z_b = 1; d.z_kula_sterowanie = 1; d.z_cheats = 1;d.z_2 = 1; d.z_up_down = true; 
			d.blok_ax *= 0.5;d.blok_by *= 0.5;d.ile_blokow/=1.5;
			znak = 0; start = 1;d.level = 9;
		}
		else	teksty[4].m = "locked";
	}


	else if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
	{
		page = 0;	lvl = 0;start = 0;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::BackSpace))
	{
		page = 0;
	}//1sza strona

	else if (Keyboard::isKeyPressed(Keyboard::Key::I))
	{
		teksty[0].m = "5: with your ball's friends defeat falling blocks ";teksty[1].m = "6: you really should clean up this mess";teksty[2].m = "7: like cyberguy, but better";
		teksty[3].m = "8: defeat badguy Mcstupidface";
		if (locked) teksty[4].m = "to unlock defeat boss or complete 5 levels"; else teksty[4].m = "9: all the specials with reappearing blocks";
	}
}


//wlasxiwa zmiana wartosxi w ustawieniaxh
void menu::plus(float &value,float &val2,int delta)
{	if (zn == 0) { val2 = value+=delta; zn = 1; }}
void menu::minus(float&value, float &val2, int delta)
{	if (value>0)if (zn == 0) { val2 = value-=delta;zn = 1; }
	if (value<0) value = 0;}
void menu::plus(int &value, int &val2, int delta)
{	if (zn == 0) { val2 = value+=delta; zn = 1; }}
void menu::minus(int&value, int &val2, int delta)
{	if (value>0)if (zn == 0) { val2 = value-=delta;zn = 1; }
	if (value<0) value = 0;}


/*settings:

1audioviz:	effects,ok			music,ok				tekstury,ok			                 /
2ped:		ped_kuli,			ped_paletki,			ped_autobad,		ped_bl          /
3trudnosc:	hp					moc,					zero,				level,	    \  /
4rozmiar:	blok_ax/blok_by,	player_ax/player_by,	r,					ile_blokow,  \/
5:reset
*/
void menu::set0(int &start, int&lvl, RenderWindow &okno, vector<tekst> &teksty, dane &d, int &znak)
{

	for (int i = 0;i < teksty.size();i++)
	{
		teksty[i].m_txt.setCharacterSize(40);
			 if (i == 0) teksty[i].m = "1:  Audiovisual   ";
		else if (i == 1) teksty[i].m = "2:  Speed   ";
		else if (i == 2) teksty[i].m = "3:  Difficulty ";
		else if (i == 3) teksty[i].m = "4:  size  ";
		else if (i == 4) teksty[i].m = "5:  reset";
		else if (i == 5) teksty[i].m = "esc:   back ";
	}
	



	if (Keyboard::isKeyPressed(Keyboard::Key::Num1))
	{
		
		pa = 1;zn = 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Num2))
	{
		pa = 2;zn = 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Num3))
	{
		pa = 3;zn = 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Num4))
	{
		pa= 4;zn = 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Num5))
	{
		dane du;du.completion = d.completion;	 d = da = du;
		teksty[4].m = "5:  ok";zn = 1;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
	{
		page = 0;lvl = 0;start = 0;
	}
	if (zn == 0) { page = pa; }

}

void menu::set1(int &start, int&lvl, RenderWindow &okno, vector<tekst> &teksty, dane &d, int &znak, Sound &sound, Sound &sound2, Texture &txtk, vector<Texture> &kol_txt, sf::Texture &txtb, std::vector<sf::Texture> &bl_txt)
{
	/**/
	for (int i = 0;i < teksty.size();i++)
	{
		teksty[i].m_txt.setCharacterSize(40);
			 if (i == 0) teksty[i].m = "1,2:  Music Volume  ";
		else if (i == 1) teksty[i].m = "3,4:  Effects Volume  ";
		else if (i == 2) teksty[i].m = "5,6:  ball texture  ";
		else if (i == 3) teksty[i].m = "7,8:  bloxk texture  ";
		else if (i == 4) teksty[i].m = "backspace:    go back ";
		else if (i == 5) teksty[i].m = "esc:   back ";
	}

	
	
	if (Keyboard::isKeyPressed(Keyboard::Key::Num1))
	{
		minus(d.vol_mu, da.vol_mu ,1 );
		sound.setVolume(d.vol_mu);  teksty[0].m += to_string(d.vol_mu);
	}
	else	if (Keyboard::isKeyPressed(Keyboard::Key::Num2))
	{
		plus(d.vol_mu, da.vol_mu, 1);
		sound.setVolume(d.vol_mu);   teksty[0].m += to_string(d.vol_mu);
	}

	else if (Keyboard::isKeyPressed(Keyboard::Key::Num3))
	{
		minus(d.vol_ef, da.vol_ef, 1);
		sound2.setVolume(d.vol_ef);sound2.play();    teksty[1].m += to_string(d.vol_ef);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num4))
	{
		plus(d.vol_ef, da.vol_ef, 1);
		sound2.setVolume(d.vol_ef);sound2.play();   teksty[1].m += to_string(d.vol_ef);
		
	}
	
	
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num5))
	{
		if (zn == 0) { i--;zn = 1; }
		if (i  <0)	i = kol_txt.size() - 1;

		txtk = kol_txt[i]; Sprite kol(txtk);   okno.draw(kol);
		teksty[2].m += to_string(i + 1);
	}
	
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num6))
	{
		if (zn == 0) { i++;zn = 1; }
		if (i + 1 > kol_txt.size())	i = 0;

		txtk = kol_txt[i]; Sprite kol(txtk);   okno.draw(kol);
		teksty[2].m += to_string(i + 1);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num7))
	{
		if (zn == 0) { j--;zn = 1; }
		if (j  <0)	j = bl_txt.size() - 1;

		txtb = bl_txt[j]; Sprite blo(txtb);   okno.draw(blo);
		teksty[3].m += to_string(j + 1);
	}
	else	if (Keyboard::isKeyPressed(Keyboard::Key::Num8))
	{
		if (zn == 0) { j++;zn = 1; }
		if (j + 1 > bl_txt.size())	j = 0;

		txtb = bl_txt[j]; Sprite blo(txtb);   okno.draw(blo);
		teksty[3].m += to_string(j + 1);
	}

	else if (Keyboard::isKeyPressed(Keyboard::Key::BackSpace))
	{
		page = 0;pa = 0;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
	{
		page = 0;	lvl = 0;start = 0;
	}

	if (i == 6)easter_egg = 1;
	else if (j == 5)easter_egg = 2;
	else easter_egg = 0;

}

void menu::set2(int &start, int&lvl, RenderWindow &okno, vector<tekst> &teksty, dane &d, int &znak)
{

	for (int i = 0;i < teksty.size();i++)
	{
		teksty[i].m_txt.setCharacterSize(40);
			 if (i == 0) teksty[i].m = "1,2:  npc speed  ";
		else if (i == 1) teksty[i].m = "3,4:  player speed  ";
		else if (i == 2) teksty[i].m = "5,6:  ball speed  ";
		else if (i == 3) teksty[i].m = "7,8:  blocks speed  "; 
		else if (i == 4) teksty[i].m = "backspace:   go back ";
		else if (i == 5) teksty[i].m = "esc:   back ";
	}


	



	if (Keyboard::isKeyPressed(Keyboard::Key::Num1))
	{
		minus(d.ped_autobad, da.ped_autobad, 1);
		teksty[0].m += to_string(int(d.ped_autobad));
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num2))
	{
		plus(d.ped_autobad, da.ped_autobad, 1);
		teksty[0].m += to_string(int(d.ped_autobad));
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num3))
	{
		minus(d.ped_paletki, da.ped_paletki, 1);
		teksty[1].m += to_string(int(d.ped_paletki));
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num4))
	{
		plus(d.ped_paletki, da.ped_paletki, 1);
		teksty[1].m += to_string(int(d.ped_paletki));
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num5))
	{
		minus(d.ped_kuli, da.ped_kuli, 1);
		teksty[2].m += to_string(int(d.ped_kuli));
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num6))
	{
		plus(d.ped_kuli, da.ped_kuli, 1);
		teksty[2].m += to_string(int(d.ped_kuli));
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num7))
	{
		minus(d.ped_bl, da.ped_bl, 1);
		teksty[3].m += to_string(int(d.ped_bl));
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num8))
	{
		plus(d.ped_bl, da.ped_bl, 1);
		teksty[3].m += to_string(int(d.ped_bl));	
	}

	else if (Keyboard::isKeyPressed(Keyboard::Key::BackSpace))
	{
		page=pa = 0;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
	{
		page=pa = 0;	lvl = 0;start = 0;
	}



}

void menu::set3(int &start, int&lvl, RenderWindow &okno, vector<tekst> &teksty, dane &d, int &znak)
{

	for (int i = 0;i < teksty.size();i++)
	{
		teksty[i].m_txt.setCharacterSize(40);
			 if (i == 0) teksty[i].m = "1,2:  hp  ";												
		else if (i == 1) teksty[i].m = "3,4:  ball power  ";
		else if (i == 2) teksty[i].m = "5,6:  block level   ";
		else if (i == 3) teksty[i].m = "7,8:  empty blocks  ";//zero
		else if (i == 4) teksty[i].m = "backspace:   go back ";
		else if (i == 5) teksty[i].m = "esc:   back       I: info";
	}

	

	

	if (Keyboard::isKeyPressed(Keyboard::Key::Num1))
	{
		minus(d.hp, da.hp, 1);
		if (d.hp < 1) { d.hp = 1; da.hp = 1; }
		teksty[0].m += to_string(int(d.hp));
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num2))
	{
		plus(d.hp, da.hp, 1);
		
		teksty[0].m += to_string(int(d.hp));
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num3))
	{
		minus(d.moc, da.moc, 1);
		if (d.moc <= 0)d.moc=da.moc = 1;
		teksty[1].m += to_string(int(d.moc));
	}

	else if (Keyboard::isKeyPressed(Keyboard::Key::Num4))
	{
		plus(d.moc, da.moc, 1);
		teksty[1].m += to_string(int(d.moc));
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num5))
	{
		minus(d.max_hp_blokow, da.max_hp_blokow, 1);
		if (d.max_hp_blokow <= 0)d.max_hp_blokow = da.max_hp_blokow = 1;
		teksty[2].m += to_string(int(d.max_hp_blokow));
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num6))
	{
		plus(d.max_hp_blokow, da.max_hp_blokow, 1);
		teksty[2].m += to_string(int(d.max_hp_blokow));
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num7))
	{
		minus(d.zero, da.zero, 1);
		if (d.zero <= 2)d.zero = da.zero = 1;
		teksty[3].m += to_string(int(d.zero));
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num8))
	{
		plus(d.zero, da.zero, 1);
		teksty[3].m += to_string(int(d.zero));
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::BackSpace))
	{
		page =pa= 0;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
	{
		page=pa = 0;lvl = 0;start = 0;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::I))
	{
		teksty[0].m = "1,2: your and your opponent's health points ";   teksty[1].m = "3,4: how good your ball is at breaking blocks";
		teksty[2].m = "5,6: how strong the block may be";		teksty[3].m = "7,8: propability of lack of blocks";
	}

}

void menu::set4(int &start, int&lvl, RenderWindow &okno, vector<tekst> &teksty, dane &d, int &znak)
{

	for (int i = 0;i < teksty.size();i++)
	{
		teksty[i].m_txt.setCharacterSize(40);
			 if (i == 0) teksty[i].m = "1,2:   ball radius  ";		
		else if (i == 1) teksty[i].m = "3,4:  block scale  ";	
		else if (i == 2) teksty[i].m = "5,6:  number of blocks  ";
		else if (i == 3) teksty[i].m = "7,8:  player scale  ";
		else if (i == 4) teksty[i].m = "backspace:  go back ";
		else if (i == 5) teksty[i].m = "esc:   back ";
	}



	
	


	if (Keyboard::isKeyPressed(Keyboard::Key::Num1))
	{
		minus(d.r, da.r, 1);
		 teksty[0].m += to_string(int(d.r));
		 sf::CircleShape kolo;kolo.setRadius(d.r);kolo.setPosition({ 50,50 });   okno.draw(kolo);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num2))
	{
		plus(d.r, da.r, 1);
		teksty[0].m += to_string(int(d.r));	
		sf::CircleShape kolo;kolo.setRadius(d.r);kolo.setPosition({ 50,50 });   okno.draw(kolo);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num3))
	{
		if (zn == 0) 
		{	minus(d.blok_ax, da.blok_ax, 5);zn = 0;		}
		minus(d.blok_by, da.blok_by, 5);
		teksty[1].m += to_string(int(d.blok_ax));
		sf::RectangleShape re;re.setSize({ d.blok_ax,d.blok_by });re.setPosition({ 50,50 });   okno.draw(re);
	}

	else if (Keyboard::isKeyPressed(Keyboard::Key::Num4))
	{
		if (zn == 0)
		{	plus(d.blok_ax, da.blok_ax, 5);zn = 0;	}
		plus(d.blok_by, da.blok_by, 5);
		teksty[1].m += to_string(int(d.blok_ax));
		sf::RectangleShape re;re.setSize({ d.blok_ax,d.blok_by });re.setPosition({ 50,50 });   okno.draw(re);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num5))
	{
		minus(d.ile_blokow, da.ile_blokow, 5);
		teksty[2].m += to_string(int(d.ile_blokow));
		
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num6))
	{
		plus(d.ile_blokow, da.ile_blokow, 5);
		teksty[2].m += to_string(int(d.ile_blokow));
		
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num7))
	{
		minus(d.player_ax, da.player_ax, 10);
		teksty[3].m += to_string(int(d.player_ax));
		sf::RectangleShape re;re.setSize({ d.player_ax,d.player_by });re.setPosition({ 50,50 });   okno.draw(re);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Num8))
	{
		plus(d.player_ax, da.player_ax, 10);
		teksty[3].m += to_string(int(d.player_ax));
		sf::RectangleShape re;re.setSize({ d.player_ax,d.player_by });re.setPosition({ 50,50 });   okno.draw(re);
	}


	else if (Keyboard::isKeyPressed(Keyboard::Key::BackSpace))
	{
		page=pa = 0;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
	{
		page=pa = 0;	lvl = 0;start = 0;
	}




}