#include <stdexcept>
#include <string>

#include "app.h"
#include "HDRImage.h"

using namespace std;

int main(int argc, char *argv[]) {
    int width = 1024;
    int height = 768;
    bool fullscreen = false;
	
	HDRImage image;
	image.Load("media/uffizi_cross.hdr");
	
    int c;
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
        app.MainLoop();
    } catch (const exception& e) {
        cerr << "ERROR: " << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
