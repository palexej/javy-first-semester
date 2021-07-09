
#include <SDL.h>
#include <SDL_image.h>
#include<string>
#include "AbstractGraphicElement.h"
using namespace std;
class StaticGraphicElement:public GraphicElement
{
public:
	StaticGraphicElement();
	~StaticGraphicElement();

	bool loadFromFile(string path);

};

