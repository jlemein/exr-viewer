#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <src/exposurecontrol.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMenu *fileMenu;
    QMenu *helpMenu;
    QImage image;

    ExposureControl m_exposureControl;

    QAction *saveFileAction;
    QAction *aboutAction;
    QAction *actionLoad_Image;

    QString openFileDialog();
    void loadFile(QString fileName);

    void syncImage();

private slots:
    void actionOpenLoadImageDialog();
    void actionChangeExposureSlider(int value);
    void actionExposureSliderReleased();
};
#endif // MAINWINDOW_H
