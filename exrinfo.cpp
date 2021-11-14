//
// Created by jeffrey on 13-11-21.
//
#include <openexrloader.h>
#include <iostream>
#include <filesystem>

#include <ImfRgba.h>
#include <ImfArray.h>
using namespace std;

int main(int argc, char** argv) {
    if (argc < 2) {
        cerr << "Please specify a single command line argument <filename>" << endl;
        return EXIT_FAILURE;
    }

    int width, height;
    filesystem::path path = argv[1];
    float* pOut;


    Imf::Array2D<Imf::Rgba> data;
    OpenExrLoader::readRgba(path, width, height, data);

    return 0;

}