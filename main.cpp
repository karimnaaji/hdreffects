#include <stdexcept>
#include <string>

#include "app.h"

using namespace std;

void exit(char *name) {
    cerr << "Usage " << name << " [-w width] [-h height] [-f fullscreen]" << endl;
    exit(1);
}

int main(int argc, char *argv[]) {
    int width = 1024;
    int height = 768;
    bool fullscreen = false;

    int c;
    while((c = getopt(argc, argv, "w:h:f:")) != -1)
    {
        switch(c)
        {
            case 'w':
                width = atoi(optarg);
                break;
            case 'h':
                height = atoi(optarg);
                break;
            case 'f':
                fullscreen = atoi(optarg);
                break;
            case '?':
                exit(argv[0]);
                break;
        }
    }

    try {
        App app(width, height, fullscreen);

        app.Init();
        app.DisplayGraphicInfo();
        app.MainLoop();
    } catch (const exception& e){
        cerr << "ERROR: " << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}