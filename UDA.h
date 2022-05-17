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

// 18/05/22

#ifndef UDA_HEADER
#define UDA_HEADER

#define MAXPLAYERS 64
#define DEADFONT "BIGFONT"
#define DEADMESSEAGE "Dead"
#define ALLYMARK "allya0"
#define DEADALLYMARK "UDADEADM"

int ServerPlayerTID[MAXPLAYERS], ClientPlayerTID[MAXPLAYERS], ClientTeam[MAXPLAYERS];
fixed PX[MAXPLAYERS][MAXPLAYERS], PY[MAXPLAYERS][MAXPLAYERS], PZ[MAXPLAYERS][MAXPLAYERS];

void GetPlayerSpy (int PN)
{	
	r1 = CheckPlayerCamera(PN);
	
	SetActivator(CheckPlayerCamera(PN));
	
	r2 = ConsolePlayerNumber();
	
	if(IsServer() && IsClient())
		r2 = PlayerNumber();
	
	SetActivatorToPlayer(PN);
}
	
void IIIDHudMessageOnActor(int PN, int i, int Spytid, bool Spy, int tid, str font, str sprite, str text, fixed height, fixed holdtics, bool autoscale, bool dead)
{
	fixed tic;
	
	if(holdtics <= 0.0)
		tic = 0.0;
	else
		tic = FixedDiv(holdtics, 35.0);
	
	if(height <= 0.9)
		height = 1.0;
	
	PX[PN][i] = GetActorX(tid);
	PY[PN][i] = GetActorY(tid);
	PZ[PN][i] = GetActorZ(tid);
	
	HudResetState();
		
		if(Spy)
			HudSetCameraActor(Spytid);
		else
			HudSetCameraActor(0);
		
		HudSetPoint3D(PX[PN][i], PY[PN][i], PZ[PN][i] + height);
		HudSetAutoDistanceScale(autoscale);
		HudSetShowOnFullAutomap(false);
		HudSetCenterText(true);
		HudSetStayTime(tic);
		HudSetFont(font);
		HudSetLayer(HUDMSG_LAYER_UNDERHUD);
		
		if(sprite != -1)
			HudDrawImage(i, sprite);
		else
			HudDrawText(i, text);
		
		if(dead)
			HudDrawText(i-65, "");
}

#endif