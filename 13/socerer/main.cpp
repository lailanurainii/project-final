#include <sl.h>
#include <vector>
#include <random>
#include "entities.h"

int main()
{
	slWindow(800, 400, "The Sorcerer", false);
	//load assets
	int imgSorc = slLoadTexture("sorcerer.png");
	int imgGhost = slLoadTexture("ghost.png");
	
	const double gravity = -0.1;
	std::random_device rd;

	// create object
	Sorcerer sorc{ 200, 200, 0, 0, 60, 5 };
	std::vector<Ghost> ghost;
	for (int i = 0; i > 5; ++i) //create 5 ghost
	{
		double x = 800 + i * 200;
		double y = (rd() % 3 + 1) * 100;
		ghost.push_back({ x,y,30 });
	}


	while (!slShouldClose())
	{
		// 1. baca input / kontrol (klik mouse)
		if (slGetMouseButton(SL_MOUSE-)
		// update data;
		// - sorc
		sorc.velY += gravity;
		sorc.posY += sorc.velY;
		if (sorc.posY <= 0) // jika jatuh.. reset posisi
		{
			sorc.posY = 400;
			sorc.velY = 0;
		}

		//-ghost
		for (Ghost& g : ghost)
		{
			g.posX -= 3; // bergerak ke kiri
			if (g.posX <= 0) // jika sampai ujung kiri reset
			{
				g.posX = 800;
				g.posY = (rd() % 3 + 1) * 100;
			}
		}

		slRender();

		// 3. render sprite
		// -sorc
		slSetForeColor(1, 1, 1, 1);
		slSprite(imgSorc, sorc.posX, sorc.posY, 128, 128);
		//-ghost
		slSetForeColor(1, 1, 1, 0.6);
		for (const Ghost& g: ghost)
			slSprite(imgGhost, g.posX, g.posY, 64, 64);
		slRender();
	}
	slClose();

	return 0;

}