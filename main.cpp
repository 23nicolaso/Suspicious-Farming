#include "CS3113/ShaderProgram.h"
#include "CS3113/Menu.h"
#include "CS3113/House.h"
#include "CS3113/StoryScene.h"

// Global Constants
constexpr int SCREEN_WIDTH     = 1920,
              SCREEN_HEIGHT    = 1080,
              FPS              = 120,
              NUMBER_OF_LEVELS = 2;
            
constexpr float FIXED_TIMESTEP              = 1.0f / 60.0f,
                INVENTORY_SLOT_SIZE         = 100.0f,
                INVENTORY_BAR_BOTTOM_OFFSET = 100.0f;

constexpr Vector2 ORIGIN = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 },
                  ITEM_SCALE = { INVENTORY_SLOT_SIZE * 0.8f, INVENTORY_SLOT_SIZE * 0.8f };

// Global Variables
AppStatus gAppStatus   = RUNNING;
float gPreviousTicks   = 0.0f,
      gTimeAccumulator = 0.0f;

Scene *gCurrentScene = nullptr;
std::vector<Scene*> gLevels = {};

LevelA *gLevelA = nullptr;
House  *gHouse  = nullptr;
StoryScene   *gStoryScene   = nullptr;
Menu   *gMenu   = nullptr;
Inventory *gInventory = nullptr;

Item *item1 = nullptr;
Item *item2 = nullptr;
Item *item3 = nullptr;

Effects *gEffects = nullptr;

ShaderProgram gShader;
DialogueHandler * mDHandler = nullptr;
int gMoney = 0;

Vector2 gLightPosition = { 0.0f, 0.0f };

// Function Declarations
void switchToScene(Scene *scene);
void initialise();
void processInput();
void update();
void render();
void shutdown();

void switchToScene(Scene *scene)
{   
    gCurrentScene = scene;
    gCurrentScene->initialise();
}

void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Effects & Shaders");
    InitAudioDevice();

    gShader.load("shaders/vertex.glsl", "shaders/fragment.glsl");

    gLevelA = new LevelA(ORIGIN, "#1f8259");
    gMenu   = new Menu(ORIGIN, "#FFFFFF");
    gHouse  = new House(ORIGIN, "#011627");
    gStoryScene = new StoryScene(ORIGIN, "#000000");

    mDHandler = new DialogueHandler(Vector2{ORIGIN.x, ORIGIN.y + SCREEN_HEIGHT / 2 - INVENTORY_BAR_BOTTOM_OFFSET * 2}, Vector2{0.0f, 0.0f}, Vector2{1280.0f, 320.0f}, "assets/game/dialog.png");

    gInventory = new Inventory(
      {ORIGIN.x - 4.5 * INVENTORY_SLOT_SIZE, ORIGIN.y + SCREEN_HEIGHT / 2 - INVENTORY_BAR_BOTTOM_OFFSET},             // Position
      {INVENTORY_SLOT_SIZE, INVENTORY_SLOT_SIZE},    // Scale
      "assets/game/inventoryslots.png"
    );

    item1 = new Item(
        GUN,                                        // Item Type
        GUN_ITEM,                                   // ITEM_ID
        ITEM_SCALE,                                 // Scale
        1,                                          // Quantity
        "assets/game/gun.png"                       // Texture Filepath
    );

    item2 = new Item(
        HOE,                                        // Item Type
        HOE_ITEM,                                   // ITEM_ID
        ITEM_SCALE,                                 // Scale
        1,                                          // Quantity
        "assets/game/hoe.png"                       // Texture Filepath
    );

    item3 = new Item(
        CONSUMABLE,                                 // Item Type
        PEANUT_SEED,                                // ITEM ID
        ITEM_SCALE,                                 // Scale
        5,                                          // Quantity
        "assets/game/peanut_seed.png"               // Texture Filepath
    );

    gInventory->addItem(item1);
    gInventory->addItem(item2);
    gInventory->addItem(item3);

    gLevels.push_back(gMenu);
    gLevels.push_back(gStoryScene);
    gLevels.push_back(gHouse);
    gLevels.push_back(gLevelA);

    mDHandler -> loadCharacterTexture("assets/game/veteranjoe.png", VETERAN_JOE);
    mDHandler -> loadCharacterTexture("assets/game/suspicioussalesman.png", SUSPICIOUS_SALESMAN);
    mDHandler -> loadCharacterTexture("assets/game/dish_to_please_the_gods.png", DISH);
    mDHandler -> loadCharacterTexture("assets/game/grandmabesleepin.png", GRANDMAW);
    mDHandler -> loadCharacterTexture("assets/game/mystery_man.png", MYSTERY);

    switchToScene(gMenu);

    gEffects = new Effects(ORIGIN, (float) SCREEN_WIDTH * 1.5f, (float) SCREEN_HEIGHT * 1.5f);

    // gEffects->start(SHRINK);
    // gEffects->setEffectSpeed(2.0f);

    SetTargetFPS(FPS);
    DisableCursor();
}

void sellAll(){
    gMoney += gInventory->sellAll();
}

void processInput() 
{
    if (gCurrentScene == gMenu){
        if (IsKeyDown(KEY_ENTER)){
            mDHandler->activate();
            switchToScene(gStoryScene); 
        }
    }

    else if (gCurrentScene == gStoryScene){
        if (IsMouseButtonPressed(0)){
            mDHandler->jumpToNextText();
            gStoryScene->updateDialogNumber(mDHandler->getCurrentLine());
        }
    }

    else {
        gCurrentScene->getState().xochitl->resetMovement();

        Vector2 mousePosition = GetMousePosition() - ORIGIN;
        Vector2 playerPosition = gCurrentScene->getState().xochitl->getPosition();
        Vector2 mouseWorld = {
            mousePosition.x + playerPosition.x,
            mousePosition.y + playerPosition.y
        };
        
        // 6. Apply the new mouse position
        if (gInventory -> getItemType() == GUN || gInventory -> getItemType() == AIR)
            { gCurrentScene->getState().crosshair -> setPosition(mouseWorld); }
        else 
            { gCurrentScene->getState().crosshair -> snapPositionToGrid(gCurrentScene->getState().map, mouseWorld); }

        gCurrentScene->getState().xochitl -> lookAtMouse(gInventory -> getItemType(), mousePosition);

        if      (IsKeyDown(KEY_A)) gCurrentScene->getState().xochitl->moveLeft  (gInventory -> getItemType());
        else if (IsKeyDown(KEY_D)) gCurrentScene->getState().xochitl->moveRight (gInventory -> getItemType());
        if      (IsKeyDown(KEY_W)) gCurrentScene->getState().xochitl->moveUp    (gInventory -> getItemType());
        else if (IsKeyDown(KEY_S)) gCurrentScene->getState().xochitl->moveDown  (gInventory -> getItemType());
        if      (IsKeyPressed(KEY_U)) gCurrentScene->getState().plantMap->growAll();
        
        // LEFT CLICK TO USE ITEM
        if (IsMouseButtonPressed(0)) {
            if (mDHandler->isActive()){
                mDHandler->jumpToNextText();
            }
            else 
            {
                if (gCurrentScene -> getState().crosshair->getCrosshairState() == 4) { sellAll();             }
                else if (gCurrentScene -> getState().crosshair->getCrosshairState() == 3) { switchToScene(gHouse); }
                gCurrentScene -> getState().xochitl -> 
                    useItem(
                        gCurrentScene -> getState().monsterManager,
                        gCurrentScene -> getState().bulletManager,
                        gCurrentScene -> getState().map, 
                        gCurrentScene -> getState().plantMap,
                        gInventory,
                        gInventory -> getItemType(), 
                        gCurrentScene -> getState().crosshair,
                        mDHandler,
                        mousePosition
                    );
            }
        }

        if (IsKeyDown(KEY_ONE))        gInventory -> SetCurrentSlot(0);
        else if (IsKeyDown(KEY_TWO))   gInventory -> SetCurrentSlot(1);
        else if (IsKeyDown(KEY_THREE)) gInventory -> SetCurrentSlot(2);
        else if (IsKeyDown(KEY_FOUR))  gInventory -> SetCurrentSlot(3);
        else if (IsKeyDown(KEY_FIVE))  gInventory -> SetCurrentSlot(4);
        else if (IsKeyDown(KEY_SIX))   gInventory -> SetCurrentSlot(5);
        else if (IsKeyDown(KEY_SEVEN)) gInventory -> SetCurrentSlot(6);
        else if (IsKeyDown(KEY_EIGHT)) gInventory -> SetCurrentSlot(7);
        else if (IsKeyDown(KEY_NINE))  gInventory -> SetCurrentSlot(8);

        gInventory -> UpdateSlotWithScroll(GetMouseWheelMove());

        if (GetLength(gCurrentScene->getState().xochitl->getMovement()) > 1.0f) 
            gCurrentScene->getState().xochitl->normaliseMovement();
    }

    if (IsKeyPressed(KEY_Q) || WindowShouldClose()) gAppStatus = TERMINATED;
}

void update() 
{
    float ticks = (float) GetTime();
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks  = ticks;

    deltaTime += gTimeAccumulator;

    if (deltaTime < FIXED_TIMESTEP)
    {
        gTimeAccumulator = deltaTime;
        return;
    }

    
    if (gCurrentScene == gMenu || gCurrentScene == gStoryScene){
        gCurrentScene->update(deltaTime);
        return;
    }

    while (deltaTime >= FIXED_TIMESTEP)
    {
        gCurrentScene->update(FIXED_TIMESTEP);

        Vector2 cameraTarget = gCurrentScene->getState().xochitl->getPosition();
        gEffects->update(FIXED_TIMESTEP, &cameraTarget);
        gInventory->redeemMonsterDrops(gCurrentScene->getState().monsterManager);

        gLightPosition = gCurrentScene->getState().xochitl->getPosition();

        deltaTime -= FIXED_TIMESTEP;
    }
}

void render()
{
    if (gCurrentScene == gMenu){
        BeginDrawing();
        gCurrentScene->render();
        EndDrawing();
        return;
    }

    else if (gCurrentScene == gStoryScene){
        BeginDrawing();
        gCurrentScene->render();
        mDHandler  -> render();
        EndDrawing();
        return;
    }

    BeginDrawing();
    BeginMode2D(gCurrentScene->getState().camera);
    // gShader.begin();

    // gShader.setVector2("lightPosition", gLightPosition);
    gCurrentScene->render();

    // gShader.end();
    gEffects->render();
    EndMode2D();

    gInventory -> render();
    DrawText(TextFormat("Money: %i", gMoney), ORIGIN.x+SCREEN_WIDTH*0.4, ORIGIN.y-0.4*SCREEN_HEIGHT, 30, BLACK);
    mDHandler  -> render();
    EndDrawing();
}

void shutdown() 
{
    delete gLevelA;
    delete gStoryScene;
    delete gInventory;
    delete gHouse;
    delete item1;
    delete item2;
    delete item3;

    for (int i = 0; i < NUMBER_OF_LEVELS; i++) gLevels[i] = nullptr;

    delete gEffects;
    gEffects = nullptr;

    gShader.unload();

    CloseAudioDevice();
    CloseWindow();
}

int main(void)
{
    initialise();

    while (gAppStatus == RUNNING)
    {
        processInput();
        update();

        if (gCurrentScene->getState().nextSceneID > 0)
        {
            int id = gCurrentScene->getState().nextSceneID;
            switchToScene(gLevels[id]);
        }

        render();
    }

    shutdown();

    return 0;
}