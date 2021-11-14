//
// Created by jeffrey on 14-11-21.
//
#pragma once

#include <ImfArray.h>
#include <ImfRgba.h>
#include <memory>
#include <filesystem>

/**
 * Controller in the model view controller paradigma.
 *
 * Exposure control controls the exposure of an image. It keeps the original and public facing image in memory,
 * until a new image is set.
 */
class ExposureControl {
private:
    /// Original source image.
    std::unique_ptr<Imf::Array2D<Imf::Rgba>> m_originalImage {nullptr};

    /// Image under active manipulation
    std::unique_ptr<float[]> m_activeImage {nullptr};
    int m_width {0}, m_height{0};

    /// Current exposure
    double m_exposure {0.0};

public:
    ExposureControl() = default;

    void setExposure(double exposure, bool shouldUpdate = false);
    double getExposure() const;

    void setImage(std::unique_ptr<Imf::Array2D<Imf::Rgba>> originalImage);

    /**
     * @Returns the image with exposure applied to it.
     */
    const uint8_t* getExposedImage() const;

    int getImageWidth() const;
    int getImageHeight() const;

private:
    double convertExposureToFactor(double exposure) const;

    /**
     * Updates the exposure controlled image.
     */
    void update();

};