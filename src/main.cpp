#include "stdafx.h"


int main()
{
    try {

    }
    catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        return -1;
    }
    catch (...) {
        std::cerr << "Caught unknown exception." << std::endl;
        return -1;
    }

    return 0;
}
