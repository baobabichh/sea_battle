#include "App.h"
namespace api
{
#include <Windows.h>
}
int main()
{

    api::HWND myConsole = api::GetConsoleWindow(); //window handle
    api::ShowWindow(myConsole, 0); //handle window

    sbat::GameResources();
    sbat::GameStyles();

    srand(time(0));

    sbat::App * app = new sbat::App();

    app->render();

    delete app;

    exit(0);
    return 0;
}



