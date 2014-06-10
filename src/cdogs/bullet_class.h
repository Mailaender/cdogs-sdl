/*
    C-Dogs SDL
    A port of the legendary (and fun) action/arcade cdogs.
    Copyright (C) 1995 Ronny Wester
    Copyright (C) 2003 Jeremy Chin 
    Copyright (C) 2003-2007 Lucas Martin-King 

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    This file incorporates work covered by the following copyright and
    permission notice:

    Copyright (c) 2013-2014, Cong Xu
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.
    Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef __BULLET_CLASS
#define __BULLET_CLASS

#include "sounds.h"
#include "tile.h"

struct MobileObject;
typedef enum
{
	BULLET_NONE,
	BULLET_MG,
	BULLET_SHOTGUN,
	BULLET_FLAME,
	BULLET_LASER,
	BULLET_SNIPER,
	BULLET_FRAG,
	BULLET_GRENADE,
	BULLET_SHRAPNELBOMB,
	BULLET_MOLOTOV,
	BULLET_GASBOMB,
	BULLET_CONFUSEBOMB,
	BULLET_GAS,
	BULLET_RAPID,
	BULLET_HEATSEEKER,
	BULLET_BROWN,
	BULLET_PETRIFIER,
	BULLET_PROXMINE,
	BULLET_DYNAMITE,
	
	// Fireballs, gas etc
	BULLET_FIREBALL_WRECK,	// no-damage fireball, for effect only
	BULLET_FIREBALL1,	// fast, short lived fireball
	BULLET_FIREBALL2,	// mediocre fireball
	BULLET_FIREBALL3,	// slow, long lived fireball
	BULLET_MOLOTOV_FLAME,
	BULLET_GAS_CLOUD_POISON,
	BULLET_GAS_CLOUD_CONFUSE,

	// Pseudo-bullets
	BULLET_SPARK,
	BULLET_ACTIVEMINE,
	BULLET_TRIGGEREDMINE,

	BULLET_COUNT
} BulletType;
typedef bool (*BulletUpdateFunc)(struct MobileObject *, int);
typedef enum
{
	FALLING_TYPE_BOUNCE,
	FALLING_TYPE_DZ,
	FALLING_TYPE_Z
} BulletClassFallingType;
typedef struct
{
	BulletType Type;
	const char *Name;
	BulletUpdateFunc UpdateFunc;
	TileItemGetPicFunc GetPicFunc;
	TileItemDrawFunc DrawFunc;
	TileItemDrawFuncData DrawData;
	int SpeedLow;
	int SpeedHigh;
	bool SpeedScale;	// whether to scale X/Y speed based on perspective
	Vec2i Friction;	// Amount to subtract from velocity per tick
	// -1 is infinite range
	int RangeLow;
	int RangeHigh;
	int Power;
	Vec2i Size;
	special_damage_e Special;
	bool Persists;	// remains even after hitting walls/items
	BulletType SparkType;
	sound_e WallHitSound;
	bool WallBounces;
	bool HitsObjects;
	struct
	{
		bool Enabled;
		BulletClassFallingType Type;
		bool DestroyOnDrop;
		void(*DropFunc)(const struct MobileObject *);
	} Falling;
	void (*OutOfRangeFunc)(const struct MobileObject *);
	void (*HitFunc)(const struct MobileObject *);
	bool RandomAnimation;
	bool Seeking;
	bool Erratic;
	void (*ProximityFunc)(const struct MobileObject *);	// Mines
} BulletClass;
extern BulletClass gBulletClasses[BULLET_COUNT];

BulletType StrBulletType(const char *s);

void BulletInitialize(void);

void AddExplosion(Vec2i pos, int flags, int player);
void AddFireExplosion(Vec2i pos, int flags, int player);
void AddGasExplosion(
	Vec2i pos, int flags, const BulletClass *class, int player);
void BulletAdd(
	const BulletType bullet,
	const Vec2i muzzlePos, const int muzzleHeight,
	const double angle, const direction_e d,
	const int flags, const int playerIndex);

int UpdateMolotovFlame(struct MobileObject *obj, int ticks);
Pic *GetFlame(int id);
void DrawGasCloud(Vec2i pos, TileItemDrawFuncData *data);

#endif
