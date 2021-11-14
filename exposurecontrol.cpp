//
// Created by jeffrey on 14-11-21.
//
#include <exposurecontrol.h>
#include <iostream>
#include <algorithm>
#include <cmath>

namespace {
    struct Rgba8888 {
        uint8_t r{0}, g {0}, b {0}, a {255};
    };
}

double ExposureControl::convertExposureToFactor(double exposure) const {
    return .5 * std::pow(2.0, exposure + 1.0);
}

void ExposureControl::setImage(std::unique_ptr<Imf::Array2D<Imf::Rgba>> originalImage) {
    m_originalImage = move(originalImage);

    // controlled image gets the same size as the original image
    // float is used, to represent rgba8888.
    m_width = m_originalImage->width();
    m_height = m_originalImage->height();
    m_activeImage = std::make_unique<float[]>(m_width * m_height);

    update();
}

void ExposureControl::update() {
    if (m_originalImage == nullptr) {
        return;
    }

    float exposureFactor = convertExposureToFactor(m_exposure);
    std::cout << "Exposure is : " << m_exposure << " (" << exposureFactor << ")" << std::endl;

    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            float* pData = m_activeImage.get();

            auto *pPixel = reinterpret_cast<Rgba8888*>(pData + (y * m_width + x));
            pPixel->r = static_cast<uint8_t>(std::clamp(exposureFactor * (*m_originalImage)[y][x].r * 255.0F, .0F, 255.F));
            pPixel->g = static_cast<uint8_t>(std::clamp(exposureFactor * (*m_originalImage)[y][x].g * 255.0F, .0F, 255.F));
            pPixel->b = static_cast<uint8_t>(std::clamp(exposureFactor * (*m_originalImage)[y][x].b * 255.0F, .0F, 255.F));
            pPixel->a = static_cast<uint8_t>(std::clamp((*m_originalImage)[y][x].a * 255.0F, .0F, 255.F));

        }
    }
}

void ExposureControl::setExposure(double exposure, bool shouldUpdate) {
    m_exposure = exposure;
    if (shouldUpdate) {
        update();
    }
}

double ExposureControl::getExposure() const {
    return m_exposure;
}

const uint8_t* ExposureControl::getExposedImage() const {
    return reinterpret_cast<const uint8_t*>(m_activeImage.get());
}

int ExposureControl::getImageWidth() const {
    return m_width;
}

int ExposureControl::getImageHeight() const {
    return m_height;
}