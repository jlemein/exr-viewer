//
// Created by jeffrey on 13-11-21.
//

#include <src/openexrloader.h>
#include <ImfRgbaFile.h>
#include <ImfArray.h>
#include <ImathBox.h>
#include <ImfMatrixAttribute.h>
#include <ImfChannelList.h>
#include <cstdint>

using namespace Imf;
using namespace Imath;

void OpenExrLoader::readRgba(std::filesystem::path path, int &width, int &height, Array2D<Rgba>& imageData) {
    RgbaInputFile file(path.c_str());
    Box2i dw = file.dataWindow();

    width = dw.max.x - dw.min.x + 1;
    height = dw.max.y - dw.min.y + 1;
    imageData.resizeErase(height, width);

    file.setFrameBuffer(&imageData[0][0] - dw.min.x - dw.min.y * width, 1, width);
    file.readPixels(dw.min.y, dw.max.y);
}