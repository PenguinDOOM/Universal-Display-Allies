/*
--------------------------------------------------------------------------------
UDA License
--------------------------------------------------------------------------------

MIT License

Copyright (c) 2020-2022 Penguin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

--------------------------------------------------------------------------------
BCSUtils License
--------------------------------------------------------------------------------

MIT License

Copyright (c) 2016-2017 Alexander Korshun and the ACSUtils contributors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

ACSUtils uses code from ACS-X:	
	
	Copyright Ben Moir 2016
	Distributed under the Boost Software License, Version 1.0.

	Boost Software License - Version 1.0 - August 17th, 2003

	Permission is hereby granted, free of charge, to any person or organization
	obtaining a copy of the software and accompanying documentation covered by
	this license (the "Software") to use, reproduce, display, distribute,
	execute, and transmit the Software, and to prepare derivative works of the
	Software, and to permit third-parties to whom the Software is furnished to
	do so, all subject to the following:

	The copyright notices in the Software and this entire statement, including
	the above license grant, this restriction and the following disclaimer,
	must be included in all copies of the Software, in whole or in part, and
	all derivative works of the Software, unless such copies or derivative
	works are solely in the form of machine-executable object code generated by
	a source language processor.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
	SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
	FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
	ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
	DEALINGS IN THE SOFTWARE.

--------------------------------------------------------------------------------
*/

// 09/06/22

#ifndef UDA_HEADER
#define UDA_HEADER

#define DEADFONT "BIGFONT"
#define DEADMESSEAGE "Dead"
#define ALLYMARK "allya0"
#define DEADALLYMARK "UDADEADM"
#define AAPTR_PLAYER_GETCAMERA 0x8000000

fixed PX[MAX_PLAYERS][MAX_PLAYERS+65], PY[MAX_PLAYERS][MAX_PLAYERS+65], PZ[MAX_PLAYERS][MAX_PLAYERS+65];

fixed VectorLength3DReal (fixed x, fixed y, fixed z) //x, y 32 units = 1 m / z 48 units = 1m (Speed is not considered)
{
	x = FixedDiv(x, 32.0);
	y = FixedDiv(y, 32.0);
	z = FixedDiv(z, 48.0);
	fixed len = VectorLength(x, y);
	len = VectorLength(z, len);
	return len;
}

fixed ActorDistanceReal (int pn1, int pn2)
{
	fixed p1x, p1y, p1z, p2x, p2y, p2z;
	p1x = GetActorX(0);
	p1y = GetActorY(0);
	p1z = GetActorZ(0);
	SetActivatorToPlayer(pn2);
	p2x = GetActorX(0);
	p2y = GetActorY(0);
	p2z = GetActorZ(0);
	SetActivatorToPlayer(pn1);
	
	return VectorLength3DReal(p2x - p1x,
	                          p2y - p1y,
	                          p2z - p1z);
}

fixed NonTIDActorDistance (int pn1, int pn2)
{
	fixed p1x, p1y, p1z, p2x, p2y, p2z;
	p1x = GetActorX(0);
	p1y = GetActorY(0);
	p1z = GetActorZ(0);
	SetActivatorToPlayer(pn2);
	p2x = GetActorX(0);
	p2y = GetActorY(0);
	p2z = GetActorZ(0);
	SetActivatorToPlayer(pn1);
	
	return VectorLength3D(p2x - p1x,
	                      p2y - p1y,
	                      p2z - p1z);
}

int GetPlayerSpyPN (int PN)
{
	int SpyPN;
	SetActivator(0, AAPTR_PLAYER_GETCAMERA);
	SpyPN = PlayerNumber();
	SetActivatorToPlayer(PN);
	
	return SpyPN;
}

void IIIDHudMessageOnActor(int PN, int i, bool Spy, str font, str text, fixed holdtics, bool autoscale, bool distance)
{
	fixed tic, temp, height;
	int AD;
	str color ;
	
	if(holdtics <= 0.0)
		tic = 0.0;
	else
		tic = FixedDiv(holdtics, 35.0);
		
	PX[PN][i] = GetActorX(0);
	PY[PN][i] = GetActorY(0);
	PZ[PN][i] = GetActorZ(0);
	height = GetActorProperty(0, APROP_Height);
	SetActivatorToPlayer(PN);
	
	if(GetCVar("UDA_Meter"))
	{
		temp = ActorDistanceReal(pn, i);
		AD = itrunc(temp);
	}
	else
	{
		temp = NonTIDActorDistance(pn, i);
		AD = itrunc(temp);
	}
	
	if(GetCVar("UDA_Meter"))
	{
		if(50 >= AD)
			color = "\cd";
		else if(100 >= AD && AD > 50)
			color = "\ck";
		else if(150 >= AD && AD > 100)
			color = "\ci";
		else if(AD > 150)
			color = "\cg";
	}
	else
	{
		if(1600 >= AD)
			color = "\cd";
		else if(3200 >= AD && AD > 1600)
			color = "\ck";
		else if(4800 >= AD && AD > 3200)
			color = "\ci";
		else if(AD > 4800)
			color = "\cg";
	}
	
	HudResetState();
		
		if(Spy)
		{
			SetActivator(0, AAPTR_PLAYER_GETCAMERA);
			HudSetCameraActor(0);
			SetActivatorToPlayer(PN);
		}
		else
			HudSetCameraActor(0);
		
		HudSetPoint3D(PX[PN][i], PY[PN][i], PZ[PN][i] + height);
		HudSetAutoDistanceScale(autoscale);
		HudSetShowOnFullAutomap(false);
		HudSetCenterText(true);
		HudSetStayTime(tic);
		HudSetFont(font);
		HudSetLayer(HUDMSG_LAYER_UNDERHUD);
		
		if(distance)
		{
			if(GetCVar("UDA_Meter"))
				HudDrawText(i+1000, StrParam(s:color, d:AD, s:"m\n\c-", s:text));
			else
				HudDrawText(i+1000, StrParam(s:color, d:AD, s:"units\n\c-", s:text));
		}
		else
			HudDrawText(i+1000, text);
}

#endif
