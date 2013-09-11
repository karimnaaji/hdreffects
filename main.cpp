#include <stdexcept>

#include "app.h"

using namespace std;

int main(int argc, char *argv[]) {
    try {
        App app(640, 480);

        app.Init();
        app.DisplayGraphicInfo();
        app.MainLoop();
    } catch (const exception& e){
        cerr << "ERROR: " << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}