#ifndef __GAMEVIEW_H__
#define __GAMEVIEW_H__

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>

#include "player.h"
#include "wall.h"

class GameView : public QGraphicsView
{
  Q_OBJECT

  public:
    GameView(QWidget *parent = 0);
    
  public slots:
    void newGame();
  
  private:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);
    bool handleWallCollision(Player *player);
    bool isPlayerCollision(Player *a, Player *b);

    QGraphicsScene *scene;
    Wall *wall;
    Player *p1;
    Player *p2;
    Player *p3;

    QList<Player *> players;
    QList<Wall *> walls;
};


#endif
