#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QMainWindow>
#include "ui_mainwindow.h"
class GameView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = 0);

    private slots:
        void showEditPlayersDialog();

    private:
        Ui::MainWindow ui;
        GameView *view;
};

#endif
