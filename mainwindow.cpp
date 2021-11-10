#include <QMessageBox>
#include <QFileDialog>
#include "mainwindow.h"
#include "./ui_mainwindow.h"

//#define TINYEXR_IMPLEMENTATION
//#include "tinyexr.h"

#include <fmt/format.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    ui->actionLoad_Image = new QAction(tr("&Lo"), this);
//    ui->actionLoad_Image->setShortcuts(QKeySequence::Open);
    ui->actionLoad_Image->setStatusTip(tr("Loads a new image"));

    connect(ui->actionLoad_Image, SIGNAL(triggered()), this, SLOT(loadFile()));
//    connect(ui->actionLoad_Image, &QAction::triggered, this, &MainWindow::loadFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadFile() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load image"));

    QMessageBox::information(this, tr("Load Image"), fileName);
}
