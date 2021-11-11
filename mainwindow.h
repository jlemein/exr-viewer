#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
//    QLabel *imageLabel;

    QAction *saveFileAction;
//    QAction *loadFileAction;
    QAction *aboutAction;
    QAction *actionLoad_Image;

//    void createActions();
//    void createMenus();

private slots:
    void loadFile();
//    void saveFile();
//    void about();
};
#endif // MAINWINDOW_H
