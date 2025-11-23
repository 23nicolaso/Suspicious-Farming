#include "Menu.h"

Menu::Menu()                                      : Scene { {0.0f}, nullptr   } {}
Menu::Menu(Vector2 origin, const char *bgHexCode) : Scene { origin, bgHexCode } {}

Menu::~Menu() { shutdown(); }

void Menu::initialise()
{
    mBGTexture = LoadTexture("assets/game/loginpage.png");
    mGameState.nextSceneID = 0;

    mGameState.bgm = LoadMusicStream("assets/audio/hummingbirdmornin.mp3");
    SetMusicVolume(mGameState.bgm, 0.33f);
    PlayMusicStream(mGameState.bgm);
}

void Menu::update(float deltaTime)
{
   UpdateMusicStream(mGameState.bgm);
}

void Menu::render()
{
    ClearBackground(ColorFromHex(mBGColourHexCode));

    // Whole texture (UV coordinates)
    Rectangle textureArea = {
        // top-left corner
        0.0f, 0.0f,

        // bottom-right corner (of texture)
        static_cast<float>(mBGTexture.width),
        static_cast<float>(mBGTexture.height)
    };

    // Destination rectangle – centred on gPosition
    Rectangle destinationArea = {
        0,
        0,
        static_cast<float>(GetScreenWidth()),
        static_cast<float>(GetScreenHeight())
    };

    // Origin inside the source texture (centre of the texture)
    Vector2 originOffset = {
        0,
        0
    };

    // Render the texture on screen
    DrawTexturePro(
        mBGTexture, 
        textureArea, destinationArea, originOffset,
        0, WHITE
    );
}

void Menu::shutdown()
{
    UnloadTexture(mBGTexture);
    UnloadMusicStream(mGameState.bgm);
}