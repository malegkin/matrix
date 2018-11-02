#include "stdafx.h"
#include "matrix.h"

int main()
{
    try {

        Matrix<uint32_t, 55, 3, 3>::Index index;

        auto a = index.toTuple();


        for (auto i =  std::begin(index); i != std::end(index); ++i){
            std::cout << i.toString() << std::endl;


        }

        //std::cout << index.toString() << std::endl;
        //std::cout << index.next().toString() << std::endl;


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
