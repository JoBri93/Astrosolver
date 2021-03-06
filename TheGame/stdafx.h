// stdafx.h: dołącz plik do standardowych systemowych plików dołączanych,
// lub specyficzne dla projektu pliki dołączane, które są często wykorzystywane, ale
// są rzadko zmieniane
//

#pragma once
#pragma comment(lib, "winmm.lib")

using namespace std;

#include "targetver.h"
#include "Windows.h"
#include <mmsystem.h>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <tchar.h>

#include "GL\freeglut.h"
#include "FreeImage.h"

#include <vector>
#include <math.h>
#include <map>


#include "vec3.h"
#include "TextureManager.h"
#include "Camera.h"
#include "SceneObject.h"
#include "Scene.h"
#include "Menu.h"
#include "Crystal.h"
#include "Panel.h"
#include "Player.h"
#include "Background.h"
#include "Level.h"
#include "CreateGame.h"

// TODO: W tym miejscu odwołaj się do dodatkowych nagłówków wymaganych przez program
