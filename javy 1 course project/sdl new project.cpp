
#include "pch.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include<vector>
#include <math.h>
#include "TextWindow.h"
#include"Player.h"
#include "Timer.h"
#include <algorithm>
#include <iostream>
#include<fstream>

//заданные размеры окна
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* myWindow = NULL;//область окна

SDL_Renderer* myRenderer = NULL;

TTF_Font *myFont = NULL;


bool init();
bool startNewGame();
int endGameScreen();

bool loadResources();
void clearMemory();

void pauseScreen();

void writeRecord(int);
void splashScreen(int);//вывод заставки
void moveFireball(Entity *);
void readRecord();
void setDefaultObjectPosition();
void loadGameEnviroment();
void gameruleScreen();
vector<TextLabel*> textWindowVector;
const int MENU_COUNT = 4;
void sortRecords();
const int IMAGES_COUNT = 6;

vector<StaticGraphicElement*>graphicElementVector;

vector<Entity*>fireballVector;
Player player;
stringstream scopeTimerText;
TextLabel timerTextTexture;

vector< int> fireballShakerPosition;//позиция шара при сортировке
vector<string> fileStringsVector;
const int RECORDS_COUNT = 20;
string fileRecordsArray[RECORDS_COUNT];
void changePlayer();
enum menu
{
	START_GAME = 0,
	RECORDS,
	GAME_RULE,
	EXIT,
};

int inGameTime;
Timer scopeTimer;//таймер очков
TextLabel gameOnPause;
string gameOnPauseText;
using namespace std;
int main(int argc, char* args[])
{
	setlocale(LC_ALL, "rus");

	if (!init())
	{
		cout << "Ошибка инициализации" << endl;
	}
	else
	{
		//Load media
		if (!loadResources())
		{
			cout << "Ошибка загрузки ресурсов" << endl;
		}
		else
		{
			player.setXSpeed(10);
			player.setXpos(SCREEN_WIDTH / 2);
			player.setYpos(SCREEN_HEIGHT - 100);
			player.loadFromFile("images/new roman player.png");

			bool quit = false;


			for (int i = 0; i < 10; i++)
			{
				fireballShakerPosition.push_back(i);//заполнение значениями позиций от 0 до 8
			}
			SDL_Event e;
			TextLabel menuArray[MENU_COUNT];

			string menuNameArray[MENU_COUNT] = { "Начать игру", "Рекорды","Правила игры","Выход" };

			string imagesNameArray[IMAGES_COUNT] = { "images/nice volcano screen.png" ,"images/game background.png" ,"images/fireball.png",
				"images/Roman build.png","images/Roman colomn.png","images/my volcano.png" };

			for (int i = 0; i < 8; i++)//цикл задаёт начальные значения для огненных шаров
			{
				int randomFireballXPos = rand() % 7;
				Entity *newFireball = new Entity(randomFireballXPos * 100, 0, 0, 5);
				newFireball->loadFromFile("images/fireball.png");
				fireballVector.push_back(newFireball);
			}


			for (int i = 0; i < IMAGES_COUNT; i++)//загрузка всех картинок в массив и загрузка из файла
			{
				StaticGraphicElement *myElement = new StaticGraphicElement();
				graphicElementVector.push_back(myElement);
				graphicElementVector[i]->loadFromFile(imagesNameArray[i]);
			}


			for (int i = 0; i < MENU_COUNT; i++)
			{
				TextLabel *menuPtr = new TextLabel();
				textWindowVector.push_back(menuPtr);
			}

			bool isGameStart = false, isMenu = false, isPause = false, isGameRules = false, isGameOver = false, isRecords = false, isFileReadOneTime = false;
			bool isFileWriteOneTime = false;

			short selectInMenu_W_S = 0;
			int alphaColor = 0;//альфа-канал для прозрачность заставки
			bool playSplashScreen = true;

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)//пока не вышли из программы и очередь событий не пуста
				{

					if (e.type == SDL_QUIT)
					{
						quit = true;
						break;
					}

					if (e.type == SDL_KEYDOWN)
					{
						switch (e.key.keysym.sym)
						{

						case SDLK_s://управление нажатиями клавиш при перемещении в меню
							if (selectInMenu_W_S >= 0 && selectInMenu_W_S < MENU_COUNT - 1)
							{
								selectInMenu_W_S++;
							}
							break;

						case SDLK_ESCAPE://если нажат ескейп, то переходим в главное меню

							isGameStart = false;
							isMenu = true;
							isGameRules = false;

							setDefaultObjectPosition();
							break;

						case SDLK_w:
							if (selectInMenu_W_S >= 1 && selectInMenu_W_S < MENU_COUNT)
							{
								selectInMenu_W_S--;
							}
							//selectedFromMenu[1] = true;
							break;


						case SDLK_SPACE:

							if (selectInMenu_W_S == EXIT)//если нажат пробел
							{
								quit = true;
								break;
							}
							if (selectInMenu_W_S == START_GAME)//при выборе определённого пункта меню сбрасываем все флаги
							{
								isGameStart = true;
								isMenu = false;

								isGameRules = false;
								isGameOver = false;
								isRecords = false;
								isFileWriteOneTime = false;
								scopeTimer.stop();
								scopeTimer.start();
								break;

							}
							if (selectInMenu_W_S == GAME_RULE)
							{
								isGameStart = false;
								isMenu = false;
								isRecords = false;
								isGameRules = true;
								isGameOver = false;
								break;
							}
							if (selectInMenu_W_S == RECORDS)
							{
								isGameStart = false;
								isMenu = false;
								isGameRules = false;
								isGameOver = false;
								isRecords = true;
								isFileReadOneTime = false;
								scopeTimer.stop();
								scopeTimer.start();
								break;
							}
							break;
						case SDLK_p:
						{
							if (scopeTimer.isPaused())
							{
								scopeTimer.unpause();
							}
							else
							{
								scopeTimer.pause();
							}


						}
						default:
							break;
						}
					}

					if (!scopeTimer.isPaused())
					{
						player.getKeybordEvent(e);
					}

				}

				SDL_RenderClear(myRenderer);

				if (isRecords)
				{
					graphicElementVector[1]->render(0, 0);
					TextLabel recordsText[RECORDS_COUNT + 1];
					TextLabel myRecordText;
					recordsText[0].setTextAndColor("Рекорды", 255, 255, 255);
					recordsText[0].render(SCREEN_WIDTH / 2 - recordsText[0].getWidth() / 2, 0);

					if (!isFileReadOneTime)
					{
						sortRecords();
						readRecord();

						isFileReadOneTime = true;
					}

					int textNumerationCounter = 1;
					for (int i = 0; i < RECORDS_COUNT; i++)
					{
						if (i % 2 != 0)
						{
							recordsText[i].setTextAndColor(to_string(textNumerationCounter) + ". " + fileRecordsArray[i], 255, 255, 255);
							recordsText[i].render(SCREEN_WIDTH / 2 - recordsText[i].getWidth() / 2, 20 * (i + 1));
							textNumerationCounter++;
						}

					}

				}
				if (isGameOver)
				{

					int playerRecord = endGameScreen();
					if (!isFileWriteOneTime)
					{
						writeRecord(playerRecord);

						isFileWriteOneTime = true;
					}

				}

				if (isGameStart && !scopeTimer.isPaused())
				{
					if (!startNewGame())
					{
						isGameOver = true;
						isGameStart = false;
						isMenu = false;
						isGameRules = false;
						//setDefaultObjectPosition();
					}

				}
				if (scopeTimer.isPaused() && !isGameOver)
				{
					pauseScreen();
				}

				if (playSplashScreen)
				{
					if (alphaColor < 175)
					{
						alphaColor += 5;
					}
					else
					{
						playSplashScreen = false;
						isMenu = true;
					}
					splashScreen(alphaColor);
					SDL_Delay(50);
				}

				if (isMenu)
				{
					SDL_SetRenderDrawColor(myRenderer, 255, 255, 255, 255);
					graphicElementVector[1]->render(0, 0);
					int menuCoef = 50;

					for (int i = 0; i < textWindowVector.size(); i++)
					{
						int menuWidth = (SCREEN_WIDTH - textWindowVector[i]->getWidth()) / 2;
						int menuHeight = (i + 1) * 50;
						if (i == selectInMenu_W_S)//если совпадают пункты меню, то перерисовываем его в другом цвете
						{
							textWindowVector[i]->setTextAndColor(menuNameArray[i], 70, 130, 180);
							textWindowVector[i]->render(menuWidth, menuHeight);
						}
						else
						{
							textWindowVector[i]->setTextAndColor(menuNameArray[i], 255, 255, 255);
							textWindowVector[i]->render(menuWidth, menuHeight);
						}

					}

				}


				if (isGameRules)
				{
					gameruleScreen();
				}
				SDL_RenderPresent(myRenderer);
			}
		}
	}

	//Free resources clearMemory SDL
	clearMemory();
	system("pause");
	return 0;
}


void readRecord()
{
	int i = 0;
	string recordStr;
	ifstream in("records.bin", ios::binary);          // поток для записи
	//in.open; // окрываем файл для дозаписи

	if (in.is_open())
	{

		//while (!in.eof())
		while (!in.eof() && i < RECORDS_COUNT)//считывание, пока не конце файла и пока не считали 10 рекордов
		{
			getline(in, recordStr);

			fileRecordsArray[i] = recordStr;
			i++;
		}
	}
	else
	{
		cout << "Ошибка чтения файла records.bin" << endl;
	}

	in.close();


}

void sortRecords()
{
	int fileStringsCount = 0;//счётчик строк всего в файле

	string recordStr;
	int recordValue;
	ifstream in("records.bin", ios::binary);          // поток для записи
	vector <int> recordsIntegerVector;
	ofstream out;          // поток для записи
	fstream inOut;

	if (in.is_open())
	{

		while (!in.eof())//считывание, пока не конце файла и пока не считали 10 рекордов
		{
			in >> recordValue;
			recordsIntegerVector.push_back(recordValue);
			fileStringsCount++;
		}

		in.close();
		out.open("records.bin", ios::binary); // окрываем файл для перезаписи всех рекордов
		sort(recordsIntegerVector.begin(), recordsIntegerVector.end());//отсортировать вектор и развернуть в обратном порядке

		reverse(recordsIntegerVector.begin(), recordsIntegerVector.end());


		for (int i = 0; i < fileStringsCount; i++)
		{
			if (recordsIntegerVector[i] >= 0)
			{
				out << recordsIntegerVector[i] << endl;

			}

		}
	}
	else
	{
		cout << "Ошибка чтения файла records.bin" << endl;
	}

	in.close();
	out.close();


}

void changePlayer()
{
	TextLabel gameRulesText[5];
	string gameRulesStringText[5] = { "Правила игры","Вулкан Везувий проснулся...","Продержитесь как можно дольше...","Используйте 'A' и 'D' для движения...","...и 'p' для паузы.\nУдачи! " };
	for (int i = 0; i < 5; i++)
	{
		gameRulesText[i].setTextAndColor(gameRulesStringText[i], 255, 255, 255);
		gameRulesText[i].render(SCREEN_WIDTH / 2 - gameRulesText[i].getWidth() / 2, 60 * i);
	}

}



void writeRecord(int recordValue)
{
	ofstream out;          // поток для записи
	out.open("records.bin", ios_base::app, ios::binary); // окрываем файл для дозаписи

	if (out.is_open())
	{
		out << recordValue << endl;
	}
	else
	{
		cout << "Ошибка записи в файл records.bin" << endl;
	}

	out.close();
}

void setDefaultObjectPosition()
{
	player.setXSpeed(10);
	player.setXpos(SCREEN_WIDTH / 2);
	player.setYpos(SCREEN_HEIGHT - 100);
	player.loadFromFile("images/new roman player.png");

	for (int i = 0; i < fireballVector.size(); i++)
	{
		int randomFireballXPos = rand() % 7;
		fireballVector[i]->setYSpeed(5);
		fireballVector[i]->setXpos(randomFireballXPos * 50);
		fireballVector[i]->setYpos(0);
	}

}

bool init()//проверка на то, что все подсистемы SDL загружены
{

	bool successLoad = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "Окно не инициализировано: " << SDL_GetError() << endl;
		successLoad = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			cout << "Cоздание линейной текстуры недоступно" << endl;
		}


		myWindow = SDL_CreateWindow("I508B Petrov A.V The last day of Pompei", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (myWindow == NULL)
		{


			cout << "Ошибка! Окно не может быть создано: " << SDL_GetError() << endl;
			successLoad = false;
		}
		else
		{
			myRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED);
			if (myRenderer == NULL)
			{
				cout << "Невозможно создать рендерер: " << SDL_GetError() << endl;
				successLoad = false;
			}
			else
			{

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					cout << "SDL_image не может инициализироваться" << IMG_GetError() << endl;
					successLoad = false;
				}
				if (TTF_Init() == -1)
				{
					cout << "SDL_ttf не может инициализироваться" << TTF_GetError() << endl;
					successLoad = false;
				}
			}
		}
	}

	return successLoad;
}

void pauseScreen()
{
	loadGameEnviroment();

	SDL_SetRenderDrawColor(myRenderer, 255, 255, 255, 10);
	gameOnPause.setTextAndColor("Пауза", 255, 255, 255);
	gameOnPause.render(SCREEN_WIDTH / 2 - gameOnPause.getWidth() / 2, SCREEN_HEIGHT / 2 - gameOnPause.getHeight() / 2);

	player.render(player.getXpos(), player.getYpos());

}

void gameruleScreen()
{
	graphicElementVector[1]->render(0, 0);
	TextLabel gameRulesText[5];
	string gameRulesStringText[5] = { "Правила игры","Вулкан Везувий проснулся...","Продержитесь как можно дольше...","Используйте 'A' и 'D' для движения...","...и 'p' для паузы.\nУдачи! " };
	for (int i = 0; i < 5; i++)
	{
		gameRulesText[i].setTextAndColor(gameRulesStringText[i], 255, 255, 255);
		gameRulesText[i].render(SCREEN_WIDTH / 2 - gameRulesText[i].getWidth() / 2, 60 * i);
	}

}

void loadGameEnviroment()//загрузка всех текстур окружения на экран
{
	graphicElementVector[1]->render(0, 0);

	SDL_Rect roadRect = { 0,300,SCREEN_WIDTH,SCREEN_HEIGHT };//рисуем дорогу коричневого цвета
	SDL_SetRenderDrawColor(myRenderer, 160, 82, 45, 130);
	SDL_RenderFillRect(myRenderer, &roadRect);

	graphicElementVector[3]->render(350, 150);//рендерим колонны и горящие дома
	graphicElementVector[3]->render(60, 150);
	graphicElementVector[4]->render(50, 280);
	graphicElementVector[4]->render(190, 340, 0, 90);
	graphicElementVector[4]->render(540, 340, 0, 90);
}

int endGameScreen()//если конец игры, то рисуем игрока в горизонтальном положении, выводим счёт игры
{
	loadGameEnviroment();

	TextLabel endGameTime;
	gameOnPause.setTextAndColor("Вы погибли", 255, 255, 255);
	gameOnPause.render(SCREEN_WIDTH / 2 - gameOnPause.getWidth() / 2, SCREEN_HEIGHT / 2 - gameOnPause.getHeight() / 2);
	player.render(player.getXpos(), player.getYpos(), 0, 90, 0, SDL_FLIP_HORIZONTAL);

	scopeTimer.pause();
	inGameTime = scopeTimer.getTicks() / 1.000;

	endGameTime.setTextAndColor("Ваш счёт: " + to_string(inGameTime), 255, 255, 255);
	endGameTime.render(SCREEN_WIDTH / 2 - endGameTime.getWidth() / 2, SCREEN_HEIGHT / 2 - endGameTime.getHeight() / 2 + 50);

	return inGameTime;

}

bool startNewGame()
{
	SDL_SetRenderDrawColor(myRenderer, 250, 128, 114, 255);
	scopeTimerText.str(" ");//обнуление строки
	scopeTimerText << "Счёт: " << (scopeTimer.getTicks() / 1.000);//количество очков
	timerTextTexture.setTextAndColor(scopeTimerText.str().c_str(), 255, 255, 255);
	loadGameEnviroment();

	int randomFireballXPos;

	for (int i = 0; i < fireballVector.size(); i++)
	{

		if (fireballVector[i]->checkCollision(player))//хитбокс обнаружен
		{
			return false;
		}

		random_shuffle(fireballShakerPosition.begin(), fireballShakerPosition.end());//перемешивание для рандомного метоположения

		int playingTime = scopeTimer.getTicks() / 1.000;

		if (playingTime % 100 == 0)//увеличиваем скорость шаров в зависимости от очков
		{
			fireballVector[i]->setYSpeed(fireballVector[i]->getYSpeed() + 1);
		}

		fireballVector[i]->move();
		fireballVector[i]->render(fireballVector[i]->getXpos(), fireballVector[i]->getYpos());

		if (fireballVector[i]->getYpos() > SCREEN_HEIGHT - fireballVector[i]->getHeight())//ограничение размером экрана и размером шара
		{
			for (vector<int>::iterator itr = fireballShakerPosition.begin(); itr != fireballShakerPosition.end(); ++itr)
			{
				randomFireballXPos = *itr;
			}


			fireballVector[i]->setYpos(0);//возвращаем шар обратно, если он достиг нижней части экрана
			fireballVector[i]->setXpos(fireballVector[i]->getWidth() * randomFireballXPos);
			fireballVector[i]->setYpos(10 * i);//немного меняем позиции
		}
	}

	player.move();
	player.render(player.getXpos(), player.getYpos());
	if (player.getXpos() > SCREEN_WIDTH - player.getWidth())//ограничение размером экрана и размером 
	{
		player.setXpos(0);//возвращаем  обратно
	}
	if (player.getXpos() < 0)
	{
		player.setXpos(SCREEN_WIDTH - player.getWidth());//возвращаем  обратно
	}

	timerTextTexture.render(SCREEN_WIDTH / 2 - timerTextTexture.getWidth() / 2, 0);

	SDL_SetRenderDrawColor(myRenderer, 250, 128, 114, 255);
	SDL_Delay(50);
	return true;

}

bool loadResources()
{
	bool successLoad = true;
	myFont = TTF_OpenFont("fonts/Pixel.ttf", 28);
	if (myFont == NULL)
	{
		cout << "Ошибка загрузки шрифта: " << TTF_GetError() << endl;
		successLoad = false;
	}

	return successLoad;
}

void clearMemory()
{
	TTF_CloseFont(myFont);
	myFont = NULL;

	SDL_DestroyRenderer(myRenderer);
	SDL_DestroyWindow(myWindow);
	myWindow = NULL;
	myRenderer = NULL;


	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

void splashScreen(int alphaColor)
{

	TextLabel myFIO, gameName;

	graphicElementVector[1]->render(0, 0);



	myFIO.setTextAndColor("И508Б Петров А.В", 255, 255, 255);
	myFIO.setAlpha(alphaColor);
	myFIO.render((SCREEN_WIDTH - myFIO.getWidth()), (SCREEN_HEIGHT - myFIO.getHeight()));


	gameName.setTextAndColor("Последний день Помпеи", 255, 255, 255);
	gameName.setAlpha(alphaColor);
	gameName.render((SCREEN_WIDTH - gameName.getWidth()) / 2, (SCREEN_HEIGHT - gameName.getHeight()) / 2);

}

