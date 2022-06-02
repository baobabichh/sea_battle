#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "DrawShipFriend.h"
#include "DrawShipEnemy.h"
#include "Animation.h"
#include "DrawField.h"
#include "DrawShipField.h"
#include "TextButton.h"
#include "ShipFieldConstructor.h"
#include <sstream>
#include "GameResources.h"
#include "GameStyles.h"
#include "GameVsBot.h"


#include "BotRandom.h"

#include "DrawShipFieldFriend.h"
#include "DrawShipFieldEnemy.h"
#include <math.h>

#include <iomanip>
#include "App.h"
 
namespace api
{
#include <Windows.h>
}
int main()
{
    namespace fs = std::filesystem;

    api::HWND myConsole = api::GetConsoleWindow(); //window handle
    api::ShowWindow(myConsole, 1); //handle window

    sbat::GameResources();
    sbat::GameStyles();


    int count = 0;
    for (auto& file : fs::directory_iterator(L""))
    {
        std::wstring str = file.path();
        if (str.rfind(L".h") != std::wstring::npos || str.rfind(L".cpp") != std::wstring::npos)
        {
            count++;
        }
    }
    std::cout << "Fiels : " << count << std::endl;
        


    srand(time(0));

    sbat::App app;

    app.render();

    exit(0);
    return 0;
}



