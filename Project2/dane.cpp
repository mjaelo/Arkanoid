#include "stdafx.h"
#include "dane.h"

using namespace sf;
using namespace std;



//blok

blok::blok(float xi, float yi, dane d)
{
	x = xi;y = yi;
	if (d.level != 5)// zabespiexzenie przed poza plansza
		if (x > d.okno_x - d.blok_ax || x < 0 || y > d.okno_y || y < -10) 
		{
			int r = rand() % 1000;
				cout << "poza plansza\n";
				 x = rand() % int(d.okno_x - d.blok_ax);
				y = rand() % int(d.okno_y - d.blok_by);
			}
	if (d.level == 5)// zabespiexzenie przed poza plansza
		if ( y > 10 )
		{
			int r = rand() % 1000;
			cout << "poza plansza\n";
			x = rand() % int(d.okno_x - d.blok_ax);
			y =- rand() % int(d.okno_y*2 - d.blok_by);
		}
	
	if(d.level==2){//w virus losowe lokaxje blokow
		int r = rand() % 1000;
		x = rand() % int(d.okno_x - d.blok_ax);
		y = rand() % int(d.okno_y - d.blok_by-100);
	}

	if (d.level == 9 && rand() % 6 == 3)	wasp = true;
	if (d.level == 4 && rand()%3==2) { wasp = true; }


	Vector2f rozmiar{ d.blok_ax,d.blok_by };
	b.setPosition(x, y);
	b.setSize(rozmiar);
	b.setOutlineThickness(d.blok_outline);
	b.setOutlineColor(Color::White);
	b.setFillColor(Color::Transparent);

	 int lev = d.max_hp_blokow;
	wytrzymalosc_bloczka = rand() % (lev)+1;//deklaracja poziomu wytzrymalosxi bloczka
	int zero = rand() % (d.zero + 1);
	if (zero == 0 || zero == 1 || zero == 2)wytrzymalosc_bloczka = 0;// szansa na brak bloku

	int r = rand() % d.sp;if (r == d.sp - 1) special = true;

	
	if (rand() % 15 > 10)faster = true;
	

	
}

void blok::ruch(dane &d)
{	
	Vector2f po = b.getPosition();
	x = po.x;y = po.y;

	b.move(ped,ped2);



	if(d.level==1||d.level==6)
	{ 
if (lixz < 10) lixz = 3000; 
else
if (lixz >1000)lixz -= 10;
else
if (lixz < 25)lixz -= 0.0625;
else
if (lixz < 50)lixz -= 0.125;
else
if (lixz < 100)lixz -= 0.25;
else
if (lixz < 500)	lixz -= 0.5;
else
lixz--;
}

	//gdy blok pojawi sie za sxiana
	if(d.level!=5 )
if (po.x > d.okno_x - d.blok_ax || po.x < 0 || po.y > d.okno_y-d.blok_by || po.y < -10)
	b.setPosition(d.okno_x / 2, d.okno_y / 2);


	//kolizja ze sxianami
	if (po.x +20> d.okno_x - d.blok_ax )ped = -d.ped_bl;
		if(po.x - 20 < 0)ped = d.ped_bl;
	if(d.level!=5&&d.level!=4)
	{ 
		if (po.y +20> d.okno_y - d.blok_by && ped2>0)ped2 = -d.ped_bl;
		if(po.y - 20 < 0 && ped2<0)	  ped2 = d.ped_bl;  
	}

		if (zn == 0) 
	{ ped = d.ped_bl;	if (rand() % 2 == 1)ped = -ped;
	if (d.level == 6 || d.level == 9)ped2 = ped; 
	zn = 1; }


	//ustawienia do poziomow
	if (d.level == 5) 
		{
		ped2 = d.ped_bl / 1.5; if(faster && po.y>0)ped2 =d.ped_bl* 2.5; 
		if (b.getPosition().y > d.okno_y) { d.hp--;d.obrazenie = true; wytrzymalosc_bloczka = 0; }
		}
	if (d.level == 6|| d.level==9) 
		{ 
		if(!faster) ped2 = 0;
		}
	if (d.level == 1) 
		{ int r = rand() % int(lixz); 
		if (r == 1)ped = 50;	else  if (r == 2)ped = -50;	else if (r == 3)ped2 = 50;	else if (r == 4)ped2 = -50;
		else ped = ped2 = 0;
		
		}
	
		
	
	
	
	
	if (wasp)
			{
		int r; 
		if (d.level == 9)r = rand() % 100;
		else r = rand() % 10000;

		if ( r == 10)//wypuszxzenie osy
		{	ped2 = 5; std::cout << "\n osa wypuszczona   ";		}
			else if (r == 9)
			{ 	ped2 = -5;std::cout << "\n osa wypuszczona   ";    }
				
			 

			if (po.y > d.okno_y - 50 || po.y < 50)
			{
				x = rand() % int(d.okno_x - d.blok_ax);
				y = rand() % int(d.okno_y - d.blok_by*4) +d.blok_by*2;
				b.setPosition(x, y);ped2 = 0;
			}
		}


	
	/*int p1=0,p2 = 0;
	if (po.x > d.okno_x - d.blok_ax)p1=-100;if (po.x < 0)p1=100;
	if (po.y > d.okno_y - d.blok_by)p2 = 100;if (po.y < 0) p2 = 100;	
	b.move(p1, p2);*/
	
}




void player:: ruch(dane d)
{
	Vector2f predkosc{ ped,ped2 };
	p.move(predkosc);

	//sterowanie
	Vector2f po = p.getPosition();
	if (d.level != 7)
	{
		if (Keyboard::isKeyPressed(Keyboard::Key::D) && po.x< d.okno_x - d.player_ax - 10)
			ped = d.ped_paletki;

		else	if (Keyboard::isKeyPressed(Keyboard::Key::A) && po.x - 10 > 0)
			ped = -d.ped_paletki;
		else
			ped = 0;
	}



	else
	{
		if (Keyboard::isKeyPressed(Keyboard::Key::D) && po.x + d.player_ax + 500 + 100< d.okno_x)	ped = d.ped_paletki;
		else	if (Keyboard::isKeyPressed(Keyboard::Key::A) && po.x>0 - d.player_ax + 100)ped = -d.ped_paletki;
		else   ped = 0;
	}




	if (d.z_up_down)
	{
		if (Keyboard::isKeyPressed(Keyboard::Key::S) && po.y< d.okno_y-d.player_by-10 ){
			if(!Keyboard::isKeyPressed(Keyboard::Key::A) && !Keyboard::isKeyPressed(Keyboard::Key::D))//bynie bylo na ukos
			ped2 = d.ped_paletki;
			}
		else if (Keyboard::isKeyPressed(Keyboard::Key::W) && po.y > 0)
		{ 
			if (!Keyboard::isKeyPressed(Keyboard::Key::A) && !Keyboard::isKeyPressed(Keyboard::Key::D))
			ped2 = -d.ped_paletki;
		}
		else ped2 = 0;
		// if(!Keyboard::isKeyPressed(Keyboard::Key::S)&&!Keyboard::isKeyPressed(Keyboard::Key::W))	ped2 = 0;
		
	}
	else ped2 = 0;
}

void player::ruch_auto(float pedk_x, float pozk_x, dane d)
{
	float po_x = p.getPosition().x + d.player_ax / 2;
	ped = d.ped_autobad;

	if (pedk_x>0)predkosc2.x = ped;
	else if (pedk_x<0)predkosc2.x = -ped;

	//if(pedk_x>predkosc2.x) pozk_x*=pedk_x/ped;//  cos by byl lepszy powinienem dodac

	if (d.level != 7)//xzyli w normalnyxh okolixznosxiaxh
	{
		if (po_x  > pozk_x && pedk_x > 0)
			predkosc2.x = 0;
		else if (po_x  < pozk_x && pedk_x < 0)
			predkosc2.x = 0;
	}

	if (pedk_x == 0)
	{
		if (pozk_x < po_x)predkosc2.x = -ped;		else if (pozk_x > po_x)predkosc2.x = ped;		else predkosc2.x = 0;
	}


	if (d.level == 7)
	{
		if (pozk_x < d.okno_x / 2)
		{
			if (po_x > pozk_x && pedk_x > 0)
				predkosc2.x = 0;
			else if (po_x  < pozk_x && pedk_x < 0)
				predkosc2.x = 0;
		}
		else
		{
			//do pozyxji dodaje 500+100 na dziore

			if (pedk_x>0)predkosc2.x = ped;
			else if (pedk_x<0)predkosc2.x = -ped;

			if (po_x + 500 + 100 + d.player_ax > pozk_x && pedk_x > 0)
				predkosc2.x = 0;
			else if (po_x + 500 + 100 + d.player_ax < pozk_x && pedk_x < 0)
				predkosc2.x = 0;/**/

			if (pedk_x == 0)
			{
				if (pozk_x < po_x + 500 + 100)predkosc2.x = -ped;		else if (pozk_x > po_x + 500 + 100)predkosc2.x = ped;		else predkosc2.x = 0;
			}
		}
		//else predkosc2.x=ped

		if (po_x + d.player_ax + 500 + 100 >= d.okno_x && predkosc2.x>0)
			predkosc2.x = 0;

		if (po_x <= 0 - d.player_ax + 100 && predkosc2.x<0)
			predkosc2.x = 0;

	}

	p.move(predkosc2);

}



void badguy::ruch(dane d)
{
	Vector2f predkosc{ ped,ped2 };
	p.move(predkosc);

	//sterowanie

	Vector2f po = p.getPosition();
	if (d.level != 7)
	{
		if (Keyboard::isKeyPressed(Keyboard::Key::Right) && po.x< d.okno_x - d.player_ax - 10)
			ped = d.ped_paletki;

		else	if (Keyboard::isKeyPressed(Keyboard::Key::Left) && po.x - 10 > 0)
			ped = -d.ped_paletki;
		else
			ped = 0;
	}


	else {
		if (Keyboard::isKeyPressed(Keyboard::Key::Right) && po.x + d.player_ax + 500 + 100< d.okno_x)	ped = d.ped_paletki;
		else	if (Keyboard::isKeyPressed(Keyboard::Key::Left) && po.x>0 - d.player_ax + 100)ped = -d.ped_paletki;
		else   ped = 0;
	}

	if (d.z_up_down)
	{
		if (Keyboard::isKeyPressed(Keyboard::Key::Down) && po.y< d.okno_y - d.player_by - 10) {
			if (!Keyboard::isKeyPressed(Keyboard::Key::Right) && !Keyboard::isKeyPressed(Keyboard::Key::Left))//bynie bylo na ukos
				ped2 = d.ped_paletki;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Key::Up) && po.y > 0)
		{
			if (!Keyboard::isKeyPressed(Keyboard::Key::Right) && !Keyboard::isKeyPressed(Keyboard::Key::Left))
				ped2 = -d.ped_paletki;
		}
		else ped2 = 0;
		
	}
	else ped2 = 0;


}

void badguy::ruch_auto(float pedk_x, float pozk_x, dane d)
{
	float po_x = p.getPosition().x + d.player_ax / 2;
	ped = d.ped_autobad;

	if (pedk_x>0)predkosc2.x = ped;
	else if (pedk_x<0)predkosc2.x = -ped;

	//if(pedk_x>predkosc2.x) pozk_x*=pedk_x/ped;//  cos by byl lepszy powinienem dodac

	if(d.level != 7)//xzyli w normalnyxh okolixznosxiaxh
	{
	if (po_x  > pozk_x && pedk_x > 0)
		predkosc2.x = 0;
	else if (po_x  < pozk_x && pedk_x < 0)
		predkosc2.x = 0;}

	if (pedk_x == 0) 
	{	if (pozk_x < po_x)predkosc2.x = -ped;		else if (pozk_x > po_x)predkosc2.x = ped;		else predkosc2.x = 0;	}


	if (d.level == 7)
	{ 
		if (pozk_x < d.okno_x / 2)
		{
			if (po_x > pozk_x && pedk_x > 0)
				predkosc2.x = 0;
			else if (po_x  < pozk_x && pedk_x < 0)
				predkosc2.x = 0;
		}
		else
		{
			//do pozyxji dodaje 500+100 na dziore

			if (pedk_x>0)predkosc2.x = ped;
			else if (pedk_x<0)predkosc2.x = -ped;
			
			if (po_x +500+100+d.player_ax > pozk_x && pedk_x > 0)
				predkosc2.x = 0;
			else if (po_x+500+100 +d.player_ax < pozk_x && pedk_x < 0)
				predkosc2.x = 0;/**/

			if (pedk_x == 0)
			{
				if (pozk_x < po_x+500+100)predkosc2.x = -ped;		else if (pozk_x > po_x+500+100)predkosc2.x = ped;		else predkosc2.x = 0;
			}
		}
		//else predkosc2.x=ped

		if (po_x + d.player_ax + 500 + 100 >= d.okno_x && predkosc2.x>0) 
			predkosc2.x= 0;

		if (po_x <= 0 - d.player_ax + 100 && predkosc2.x<0)
			predkosc2.x = 0;
		
	}

	p.move(predkosc2);

}