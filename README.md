# Shooty-Dungeon
Technical Game Development - Project 3

---------------------------------------------------
PROJECT TITLE:     SHOOTY DUNGEON

---------------------------------------------------
Team Members:
        Surya Srinivasan    (ssrinivasan1@wpi.edu)
        Bharat Monavarthi   (bmonavarthi@wpi.edu)

---------------------------------------------------
File Structure:
    Shooty Dungeon
        |
        DragonFly engine
                |
                -------------Engine .cpp and .h files
        Shooty Dungeon
                |
                -------------sprites
                -------------x64
                -------------Game .cpp Files (Bullet.cpp, Player.cpp, Reticle.cpp, Enemy.cpp, game.cpp)
                -------------Game .h Files  (Bullet.h, Player.h, Reticle.h, Enemy.h, game.h)
        x64
        README
        Shooty Dungeon.sln
    SFML 2.5

--------------------------------------------------------
How to Compile:

    1. Open Shooty Dungeon Folder
    2. Open Shoot Dungeon.sln       (Visual Studio Required)
    3. Build Project    (ctrl + shift + B)
    4. Run project

---------------------------------------------------------
Implementation Details:

    1) Player Class Created     - Controllable through keyboard (Movement all 4 directions) and Mouse (Aim and shoot)
    2) Enemy Class Created      - Follows Player and Shoots at players direction
    3) Bullet Class Created     - Common for both Player and Enemy 
    4) Reticle Class Created    - Shows mouse location on Screen (Player Aim)

    GAME STILL USES PLACEHOLDER ART