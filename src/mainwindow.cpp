#include "mainwindow.h"
#include <QGraphicsScene>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
  ui.setupUi(this);

  view = new GameView(this);
  setCentralWidget(view);

  connect(ui.actionNew, SIGNAL(triggered()), view, SLOT(newGame()));
}
