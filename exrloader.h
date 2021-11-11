//
// Created by jeffrey on 11-11-21.
//
#pragma once

#include <filesystem>
#include <QPixmap>

/**
 * Simple EXR loader functions.
 */
class ExrLoader {
public:
    static QPixmap readExrImageFromFile(const std::filesystem::path& path);
};
