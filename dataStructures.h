#pragma once

enum objType
{
	 obgjTypePlayer,
	 objTypeMap,
	 objTypeEnemy,
	 objTypeProjectile,
	 objTypeDefault
};

struct hitBox
{
	int pos_x;
	int pos_y;
	int width;
	int height;
};

struct pos 
{
	int x, y;
};

enum projectileTypes
{
	bullet,
	plasma,
	twoBullets,
};