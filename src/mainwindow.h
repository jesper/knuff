#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QMainWindow>

#include "gameview.h"
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
  public:
    MainWindow(QWidget *parent = 0);
  private:
    Ui::MainWindow ui;
    GameView *view;
};

#endif
