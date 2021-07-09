
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <stdio.h>

using namespace std;

class StaticGraphicElement
{
public:

	StaticGraphicElement();

	~StaticGraphicElement();

	bool loadFromFile(string path);

	
	void free();

	void render(int x, int y, SDL_Rect* clip = NULL);

	int getWidth();
	int getHeight();

private:
	
	SDL_Texture* mTexture;


	int mWidth;
	int mHeight;
};
