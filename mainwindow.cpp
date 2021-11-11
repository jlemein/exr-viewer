#include <QMessageBox>
#include <QFileDialog>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QImageReader>
#include <exrloader.h>

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

    connect(ui->actionLoad_Image, SIGNAL(triggered()), this, SLOT(loadFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadFile() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load image"));
    try {
        auto image = ExrLoader::readExrImageFromFile(fileName.toStdString());
        ui->imageLabel->setPixmap(image);
    } catch (std::runtime_error& e) {
        QMessageBox::warning(this, tr("Load Image"), e.what());
    }
}
