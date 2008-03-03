#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QMainWindow>

#include "gameview.h"
#include "ui_mainwindow.h"
#include "managePlayersDialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = 0);

    private slots:
        void showManagePlayersDialog();

    private:
        Ui::MainWindow ui;
        GameView *view;
};

#endif
