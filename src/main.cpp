#include <stdexcept>
#include <string>

#include "app.h"

#include "hdrcubemap.h"

using namespace std;

int main(int argc, char *argv[]) {
    int width = 1024;
    int height = 768;
    int c;
    bool fullscreen = false;

    while((c = getopt(argc, argv, "w:h:f:")) != -1) {
        switch(c) {
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
                cerr << "Usage " << argv[0] << " [-w width] [-h height] [-f fullscreen]" << endl;
                return EXIT_FAILURE;
        }
    }

    try {
        App app(width, height, fullscreen);

        app.Init();
        app.DisplayGraphicInfo();

		HDRCubeMap cubeMap;
		cubeMap.Load("media/uffizi_cross.hdr");

        app.MainLoop();
    } catch (const exception& e) {
        cerr << "ERROR: " << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
