//
// Created by jeffrey on 14-11-21.
//
#pragma once

#include <ImfArray.h>
#include <ImfRgba.h>
#include <filesystem>
#include <memory>

/**
 * Controller in the model view controller paradigma.
 *
 * Exposure control controls the exposure of an image. It keeps the original and
 * public facing image in memory, until a new image is set.
 */
class ExposureControl {
private:
  int m_width{0};  /// Width of both the original as well as the active image.
  int m_height{0}; /// Height of hoth the original as well as the active image.
  double m_exposure{0.0}; /// Current exposure.

  /// Original source HDR image. This is the read-only image.
  std::unique_ptr<Imf::Array2D<Imf::Rgba>> m_originalImage{nullptr};

  /// Image under active manipulation.
  std::unique_ptr<float[]> m_activeImage{nullptr};

public:
  ExposureControl() = default;

  /**
   * @brief Sets the exposure level.
   * @param exposure     Exposure value in F-stops. Usually this ranges between
   * -2 and 2. Where 0 does not scale the HDR pixel values.
   */
  void setExposure(double exposure);

  /**
   * @returns the current value of the exposure level. Setting the exposure can
   * be done via @see setExposure.
   */
  double getExposure() const;

  /**
   * @brief Sets the HDR unmodified input image. This is the HDR image that will
   * be controlled using the exposure control.
   * @param originalImage     Input image for the exposure control.
   */
  void setImage(std::unique_ptr<Imf::Array2D<Imf::Rgba>> originalImage);

  /**
   * @returns a pointer to the raw bytes of the image with exposure applied to
   * it.
   */
  const uint8_t *getExposedImage() const;

  /**
   * @eturns the width of the HDR image.
   */
  int getImageWidth() const;

  /**
   * @returns the height of the HDR image.
   */
  int getImageHeight() const;

private:
  /**
   * Converts the exposure (in f-stops) to a multiplication factor that can be
   * used to scale pixel values, corresponding to the exposure level.
   * @param exposure Exposure level in F-stops.
   * @return Scaling factor corresponding to the F-stop.
   */
  double convertExposureToFactor(double exposure) const;

  /**
   * Updates the exposure controlled image.
   */
  void update();
};