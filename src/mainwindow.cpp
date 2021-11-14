#include <QMessageBox>
#include <QFileDialog>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QImageReader>
#include <src/openexrloader.h>
#include <iostream>

#include <ImfArray.h>
#include <ImfRgba.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->imageLabel->setBackgroundRole(QPalette::Base);
    ui->imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->imageLabel->setScaledContents(true);
    ui->imageLabel->setContentsMargins(0, 0, 0, 0);
    ui->actionLoad_Image->setStatusTip(tr("Loads a new image"));

    QStringList arguments = qApp->arguments();
    if (arguments.size() > 1) {
        qInfo("Specified argument: %s", arguments.at(1).toStdString().c_str());
        loadFile(arguments.at(1));
    }

    connect(ui->actionLoad_Image, SIGNAL(triggered()), this, SLOT(actionOpenLoadImageDialog()));
    connect(ui->exposureSlider, SIGNAL(valueChanged(int)), this, SLOT(actionChangeExposureSlider(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actionOpenLoadImageDialog() {
    loadFile(openFileDialog());
}

QString MainWindow::openFileDialog() {
    return QFileDialog::getOpenFileName(this, tr("Load image"));
}

void MainWindow::loadFile(QString fileName) {
    try {
        auto exrData = std::make_unique<Imf::Array2D<Imf::Rgba>>();
        int width, height;
        OpenExrLoader::readRgba(fileName.toStdString(), width, height, *exrData);
        m_exposureControl.setImage(std::move(exrData));
        syncImage();

    } catch (std::runtime_error& e) {
        QMessageBox::warning(this, tr("Load Image"), e.what());
    }
}

void MainWindow::actionChangeExposureSlider(int value) {
    m_exposureControl.setExposure(value*0.01);
    syncImage();
}

void MainWindow::syncImage() {
    auto w = m_exposureControl.getImageWidth();
    auto h = m_exposureControl.getImageHeight();

    QImage image(reinterpret_cast<const uchar*>(m_exposureControl.getExposedImage()), w, h, QImage::Format_RGBA8888);
    auto pixmap = QPixmap::fromImage(image, Qt::AutoColor);
    ui->imageLabel->setPixmap(pixmap);
}
