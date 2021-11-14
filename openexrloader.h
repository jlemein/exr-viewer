//
// Created by jeffrey on 13-11-21.
//
#pragma once

#include <filesystem>
#include <ImfRgba.h>
#include <ImfForward.h>

/**
 * Exr file loader, but using OpenExr behind the scenes.
 */
class OpenExrLoader {
public:
    /**
     * Reads the image at file system path, and fills the width, height and image data with the contents from the file.
     * The path should be an EXR image.
     * @param path Path to an existing image on the file system.
     * @param width Reference to width, that will be set to the width of the read image if image read is successful.
     * @param height Reference to height, that will be set to the height of the read image if image read is successful.
     * @param exrPixelData Reference to an existing Array2D that will hold the resulting image data.
     *
     * @throws runtime_error When image is not a valid EXR file, or when specified path does not exist or path is invalid.
     */
    static void readRgba(std::filesystem::path path, int& width, int& height, Imf::Array2D<Imf::Rgba>& exrPixelData);
};
