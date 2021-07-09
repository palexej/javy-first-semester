
#include "pch.h"
#include "TextLabel.h"

extern  SDL_Window* myWindow;//������� ����

extern  SDL_Renderer* myRenderer;

extern TTF_Font *myFont;

TextLabel::TextLabel()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	mTextString = "";

}

//void TextLabel::setTextString(string myText)
//{
//	mTextString = myText;
//}
//
//string TextLabel::getTextString()
//{
//	return mTextString;
//}


TextLabel::~TextLabel()
{
	free();
	mTextString = "";
}

//
//void TextLabel::free()
//{
//	//������������ ������ ��� ��������, ���� ��� ����������
//	if (mTexture != NULL)
//	{
//		SDL_DestroyTexture(mTexture);
//		mTexture = NULL;
//		mWidth = 0;
//		mHeight = 0;
//		mTextString = "";
//
//	}
//}
//
//void TextLabel::setAlpha(Uint8 alpha)//��������� �����-������ ��������
//{
//	SDL_SetTextureAlphaMod(mTexture, alpha);
//}
//
//
//
//void TextLabel::render(int x, int y)
//{
//	//Set rendering space and render to screen
//	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
//	SDL_RenderCopy(myRenderer, mTexture, NULL, &renderQuad);
//}
//
//int TextLabel::getWidth()
//{
//	return mWidth;
//}
//
//int TextLabel::getHeight()
//{
//	return mHeight;
//}



bool TextLabel::setTextAndColor(string textStr, int r, int g, int b)
{

//	free();//������������ ������ ���������� ��������
	SDL_Color textColor = { r, g, b };


	SDL_Surface* textSurface = TTF_RenderText_Solid(myFont, textStr.c_str(), textColor);
	if (textSurface == NULL)
	{
		cout << "���������� ����������� ����������� ��� ������: " << TTF_GetError() << endl;
	}
	else
	{
		//�������� �������� �� �����������
		mTexture = SDL_CreateTextureFromSurface(myRenderer, textSurface);
		if (mTexture == NULL)
		{
			cout << "���������� ������� �������� �� ������: "<< SDL_GetError() <<endl;
		}
		else
		{
			//��������� �������� �����������
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//������������ ������ ��� ������ ��������
		SDL_FreeSurface(textSurface);
	}

	return mTexture != NULL;
}
