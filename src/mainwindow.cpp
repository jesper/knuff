#include "mainwindow.h"
#include <QGraphicsScene>
#include "gameview.h"
#include "editPlayersDialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
  ui.setupUi(this);

  view = new GameView(this);
  setCentralWidget(view);

  connect(ui.actionNew, SIGNAL(triggered()), view, SLOT(newGame()));
  connect(ui.editPlayersAction, SIGNAL(triggered()), this, SLOT(showEditPlayersDialog()));
}

void MainWindow::showEditPlayersDialog()
{
    EditPlayersDialog dlg;
    dlg.exec();
}