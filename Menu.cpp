#include "Menu.h"
#include "AssetManager.h"
#include "TextureManager.h"
#include "Components.h"
#include <sstream>


SDL_Event Menu::event;
TTF_Font* fontMenu = NULL;
TTF_Font* fontTitle = NULL;


std::vector<FontLabel> managerMenu;
std::vector<FontLabel> managerGameOver;

void Menu::init()
{
    // backgroundText = TextureManager::LoadTexture("assets/menu.png");
    if (TTF_Init() == -1)
    {
        std::cout << "Error : SDL_TTF" << std::endl;
    }
    fontMenu = TTF_OpenFont("assets/arial.ttf", 30);
    fontTitle = TTF_OpenFont("assets/arial.ttf", 50);

    FontLabel dissneland(335, 130, "DISSNELAND");
    FontLabel start(430, 250, "START");
    FontLabel tutorial(405, 320, "TUTORIAL");
    FontLabel setting(415, 390, "SETTING");
    FontLabel quit(440, 460, "QUIT");

    dissneland.setColor(FontLabel::PINK_TEXT);
    dissneland.SetlabelText(fontTitle);

    start.setColor(FontLabel::WHITE_TEXT);
    start.SetlabelText(fontMenu);

    tutorial.setColor(FontLabel::WHITE_TEXT);
    tutorial.SetlabelText(fontMenu);

    setting.setColor(FontLabel::WHITE_TEXT);
    setting.SetlabelText(fontMenu);

    quit.setColor(FontLabel::WHITE_TEXT);
    quit.SetlabelText(fontMenu);

    managerMenu.push_back(dissneland);
    managerMenu.push_back(start);
    managerMenu.push_back(tutorial);
    managerMenu.push_back(setting);
    managerMenu.push_back(quit);

    FontLabel gameover(370, 200, "GAME OVER!");
    FontLabel returntomenu(450, 300, "MENU");
    FontLabel quitOver(455, 350, "QUIT");

    gameover.setColor(FontLabel::PINK_TEXT);
    gameover.SetlabelText(fontTitle);

    returntomenu.setColor(FontLabel::WHITE_TEXT);
    returntomenu.SetlabelText(fontMenu);

    quitOver.setColor(FontLabel::WHITE_TEXT);
    quitOver.SetlabelText(fontMenu);

    managerGameOver.push_back(gameover);
    managerGameOver.push_back(returntomenu);
    managerGameOver.push_back(quitOver);

}

Menu::Menu()
{}
Menu::~Menu()
{}

bool Menu::handleEvents()
{

    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_MOUSEMOTION:
        if (Game::openMenu)
        {
            for (int i = 1; i < managerMenu.size(); i++)
            {
                managerMenu[i].destroy();
                if (managerMenu[i].checkMotion(event.motion.x, event.motion.y))
                {
                    managerMenu[i].setColor(FontLabel::RED_TEXT);
                }
                else
                {
                    managerMenu[i].setColor(FontLabel::WHITE_TEXT);
                }
                managerMenu[i].SetlabelText(fontMenu);
            }
        }
        else
        {
            for (int i = 1; i < managerGameOver.size(); i++)
            {
                managerGameOver[i].destroy();
                if (managerGameOver[i].checkMotion(event.motion.x, event.motion.y))
                {
                    managerGameOver[i].setColor(FontLabel::RED_TEXT);
                }
                else
                {
                    managerGameOver[i].setColor(FontLabel::WHITE_TEXT);
                }
                managerGameOver[i].SetlabelText(fontMenu);
            }
        }
        break;
    case SDL_MOUSEBUTTONDOWN:

        if (Game::openMenu)
        {
            if (managerMenu[1].checkMotion(event.motion.x, event.motion.y))
            {
                Game::resetGame = 1;
                Game::isRunningMenu = 0;
            }
            if (managerMenu[4].checkMotion(event.motion.x, event.motion.y))
            {
                Game::isRunning = 0;
            }
        }
        else
        {
            if (managerGameOver[1].checkMotion(event.motion.x, event.motion.y))
            {
                std::cout << "kk";
                Game::openMenu = 1;
            }
            if (managerGameOver[2].checkMotion(event.motion.x, event.motion.y))
            {
                Game::isRunning = 0;
            }

        }
        break;
    case SDL_KEYDOWN:
        break;
    case SDL_QUIT:
        Game::isRunning = false;
        break;
    default:
        break;
    }
    return 1;
}

void Menu::render()
{
    SDL_RenderClear(Game::renderer);
	
    if (Game::openMenu)
    {
        for (auto i : managerMenu)
        {
            i.draw();
        }
    }
    else
    {
        for (auto i : managerGameOver)
        {
            i.draw();
        }
    }

    SDL_RenderPresent(Game::renderer);
}
