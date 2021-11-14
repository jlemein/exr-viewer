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
    /// Original source image. This is the backed read-only image.
    std::unique_ptr<Imf::Array2D<Imf::Rgba>> m_originalImage {nullptr};

    /// Image under active manipulation.
    std::unique_ptr<float[]> m_activeImage {nullptr};

    int m_width {0};            /// Width of both the original as well as the active image.
    int m_height{0};            /// Height of hoth the original as well as the active image.
    double m_exposure {0.0};    /// Current exposure.

public:
    ExposureControl() = default;

    /// Sets the exposure level.
    void setExposure(double exposure);

    /// @returns the last set value of the exposure level. Setting the exposure can be done via @see setExposure.
    double getExposure() const;

    /// Sets the original "backed" image.
    void setImage(std::unique_ptr<Imf::Array2D<Imf::Rgba>> originalImage);

    /// @returns the image with exposure applied to it.
    const uint8_t* getExposedImage() const;

    /// Returns the width of the underlying image.
    int getImageWidth() const;

    /// Returns the height of the underlying image..
    int getImageHeight() const;

private:
    double convertExposureToFactor(double exposure) const;

    /**
     * Updates the exposure controlled image.
     */
    void update();

};