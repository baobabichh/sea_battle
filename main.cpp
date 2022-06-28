#include "App.h"
namespace api
{
#include <Windows.h>
}
int main()
{

    api::HWND myConsole = api::GetConsoleWindow(); //window handle
    api::ShowWindow(myConsole, 1); //handle window

    sbat::GameResources();
    sbat::GameStyles();

    size_t res =0;


    namespace fs = std::filesystem;

    for (auto it : fs::directory_iterator("C:\\Users\\goshan\\source\\repos\\sea_battle_sfml"))
    {
        auto path = it.path().string();
       
        if(path.rfind(".h") != std::string::npos)
        {
            std::cout << "path : " << path << "\n";
            std::ifstream file(path);

            std::string tmp;

            while (!file.eof())
            {
                std::getline(file, tmp, '\n');
                res++;
            }
        }
        else if (path.rfind(".cpp") != std::string::npos)
        {
            std::cout << "path : " << path << "\n";
            std::ifstream file(path);

            std::string tmp;

            while (!file.eof())
            {
                std::getline(file, tmp, '\n');
                res++;
            }
        }
    }

    std::cout << res;

    srand(time(0));

    sbat::App * app = new sbat::App();

    app->render();

    delete app;

    exit(0);
    return 0;
}



