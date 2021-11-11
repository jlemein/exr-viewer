//
// Created by jeffrey on 11-11-21.
//
#include <exrloader.h>
//#include <fmt/format.h>

#define TINYEXR_IMPLEMENTATION
#include <tinyexr.h>
#include <iostream>

QPixmap ExrLoader::readExrImageFromFile(const std::filesystem::path &path) {
    float* out; //width*height *RGBA
    int width, height;
    const char* err = nullptr;

    EXRVersion exr_version;
    if (ParseEXRVersionFromFile(&exr_version, path.c_str()) != 0) {
        throw std::runtime_error("Invalid EXR file");
    }

    std::cout << (exr_version.multipart ?  "EXR image is multipart" : "Not multipart") << "\n";
    std::cout << (exr_version.tiled ?  "EXR image is tiled" : "Not tiled") << "\n";
    std::cout << "EXR version: " << exr_version.version << "\n";

    int ret = LoadEXR(&out, &width, &height, path.c_str(), &err);
    if (ret != TINYEXR_SUCCESS) {
//        auto message = fmt::format("ERROR: {}", err);
        FreeEXRErrorMessage(err);
        throw std::runtime_error("ERROR");
    }
    QImage image(reinterpret_cast<uchar*>(out), width, height, QImage::Format_RGBA32FPx4);
    auto pixmap = QPixmap::fromImage(image, Qt::AutoColor);
    free(out);
    return pixmap;
}
