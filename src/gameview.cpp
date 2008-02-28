#include <QDebug>

#include "gameview.h"
#include "itemtypes.h"

#define SPEED 0.4 //movement increase per keypress
#define FRICTION 0.98 //2% loss
#define WALL_BOUNCE_SPEED_REDUCE 0.85
#define PLAYER_BOUNCE_SPEED_REDUCE 0.80

GameView::GameView(QWidget *parent)
    : QGraphicsView(parent)
{  
  scene = new QGraphicsScene(this);
 // scene->setItemIndexMethod(QGraphicsScene::NoIndex);
  setScene(scene);
  scene->setBackgroundBrush(Qt::gray);

  //TBD: Add scaling.
  scene->setSceneRect(0, 0, 500, 500);
  scale(1, 1);
  
  // I'm not sure why I need to have it 506 when the scene only takes 500.
  // If i dont add those 6, I will get scrollbars.
  setFixedSize(506, 506);
    
  //Border frame of the game area
//  scene->addItem(new QGraphicsRectItem(0,0,500,500));
  
  wall = new Wall();
  QPainterPath path;
//  path.addRect(0, 0, 1, 100);
//  path.addRect(0, 0, 100, 1);
  path.addRect(100, 0, 1, 100);
//  path.addRect(0, 100, 100, 1);

  wall->setPath(path);
  scene->addItem(wall);
  wall->setPos(100,100);
  walls.append(wall);
  
  p1 = new Player();
  p1->setBrush(Qt::blue);
  scene->addItem(p1);
  players.append(p1);
  p1->left_key = Qt::Key_Left;
  p1->right_key = Qt::Key_Right;
  p1->up_key = Qt::Key_Up;
  p1->down_key = Qt::Key_Down;

  p2 = new Player();
  scene->addItem(p2);
  players.append(p2);
  p2->setPos(410, 410);
  p2->setBrush(Qt::green);

  p2->left_key = Qt::Key_A;
  p2->right_key = Qt::Key_D;
  p2->up_key = Qt::Key_W;
  p2->down_key = Qt::Key_S;

  p3 = new Player();
  scene->addItem(p3);
  players.append(p3);
  p3->setPos(250, 250);
  p3->setBrush(Qt::yellow);

  p3->left_key = Qt::Key_J;
  p3->right_key = Qt::Key_L;
  p3->up_key = Qt::Key_I;
  p3->down_key = Qt::Key_K;

//  newGame();
  startTimer(20);
}

void GameView::newGame()
{
  players.append(new Player());
  players.last()->setPos(300, 300);
  scene->addItem(players.last());
}

//Return true if hitting a wall
bool GameView::handleWallCollision(Player *player)
{
  QPointF point = player->scenePos();
  QRectF rect = player->rect();
  bool hit = false;
   //LEFT WALL
  if (point.x() + player->xspeed < 0)
  {  
    player->xspeed = player->xspeed * -1 * WALL_BOUNCE_SPEED_REDUCE;
    player->setPos(0, point.y());
    hit = true;
  }

  //RIGHT WALL  
  if (point.x() + rect.width() +  player->xspeed > scene->width())
  {  
    player->xspeed = player->xspeed * -1 * WALL_BOUNCE_SPEED_REDUCE;
    player->setPos(scene->width() - rect.width(), point.y());
    hit = true;
  }
  
  //TOP WALL
  if (point.y() + player->yspeed < 0)
  {  
    player->yspeed = player->yspeed * -1 * WALL_BOUNCE_SPEED_REDUCE;
    player->setPos(point.x(), 0);
    hit = true;
  }
  
  //BOTTOM WALL
  if (point.y() + rect.height() + player->yspeed > scene->height())
  {  
    player->yspeed = player->yspeed * -1 * WALL_BOUNCE_SPEED_REDUCE;
    player->setPos(point.x(), scene->height() - rect.height());
    hit = true;
  }  
  
  return hit;
}

bool GameView::isPlayerCollision(Player *a, Player *b)
{
  qreal deltaXSquared = a->x() - b->x(); // calc. delta X
  deltaXSquared *= deltaXSquared; // square delta X
  
  qreal deltaYSquared = a->y() - b->y(); // calc. delta Y
  deltaYSquared *= deltaYSquared; // square delta Y
  
  // Calculate the sum of the radii, then square it
  qreal sumRadiiSquared = (a->rect().width() / 2) + (b->rect().width() / 2);
  sumRadiiSquared *= sumRadiiSquared;
  
  return (deltaXSquared + deltaYSquared <= sumRadiiSquared);
}

void GameView::timerEvent(QTimerEvent *)
{
  for (int i=0; i < players.size(); ++i)
  {
    Player *player = players.at(i);
    QPointF point = player->scenePos();
    QRectF rect = player->rect();
    
    if (player->left_pressed)
      player->xspeed = (player->xspeed * FRICTION) - SPEED;

    if (player->right_pressed)
      player->xspeed = (player->xspeed * FRICTION) +SPEED;

    if (player->up_pressed)
      player->yspeed = (player->yspeed * FRICTION) - SPEED;

    if (player->down_pressed)
      player->yspeed = (player->yspeed * FRICTION) + SPEED;

    //qDebug() << "Speed x:" << players.at(i)->xspeed << " and y:" << players.at(i)->yspeed;
    //qDebug() << "Pos x:" << point.x() << " and y:" << point.y();
  
    handleWallCollision(players.at(i));
    player->setPos(point.x() + player->xspeed, point.y() + player->yspeed);    


//Walls
    QList<QGraphicsItem *> collisions = player->collidingItems();

    for (int k=0; k < collisions.size(); ++k)
    {
      if (collisions.at(k)->type() != WallType)
        continue;
      
      qDebug() << "Player hit a wall";
      player->yspeed = player->yspeed * -1 * WALL_BOUNCE_SPEED_REDUCE;
      player->xspeed = player->xspeed * -1 * WALL_BOUNCE_SPEED_REDUCE;

      player->setPos(point.x() + player->xspeed, point.y() + player->yspeed);
    }
//\Walls


    for (int j=0; j < players.size(); ++j)
    {
      Player *collider = players.at(j);
      
      if (player == collider)
        continue;

      if (!isPlayerCollision(player, collider))
        continue;

/*     QList<QGraphicsItem *> collisions = player->collidingItems();

     for (int j=0; j < collisions.size(); ++j)
     {
      if (collisions.at(j)->type() != PlayerType)
        continue;
      
      Player *collider = (Player *)collisions.at(j);
*/
      qreal x = collider->xspeed;
      qreal y = collider->yspeed;

      collider->xspeed = (x * -.2) + (player->xspeed * PLAYER_BOUNCE_SPEED_REDUCE);
      collider->yspeed = (y * -.2) + (player->yspeed * PLAYER_BOUNCE_SPEED_REDUCE);

      player->xspeed = (player->xspeed * -.2) + (x * PLAYER_BOUNCE_SPEED_REDUCE);
      player->yspeed = (player->yspeed * -.2) + (y * PLAYER_BOUNCE_SPEED_REDUCE);

      player->setPos(point.x() + player->xspeed, point.y() + player->yspeed);    
      collider->setPos(collider->pos().x() + collider->xspeed, collider->pos().y() + collider->yspeed);    
  
      while (handleWallCollision(player) || handleWallCollision(collider))
        ;

      break;
    }
  }
}

void GameView::keyPressEvent(QKeyEvent *event)
{ 
  //qDebug() << "KEYPRESS:" << event->key();

  for (int i=0; i < players.size(); ++i)
  {
     int key = event->key();
     
     if (key == players.at(i)->left_key)
       players.at(i)->left_pressed = true;
       
     if (key == players.at(i)->right_key)
       players.at(i)->right_pressed = true;

     if (key == players.at(i)->up_key)
       players.at(i)->up_pressed = true;
       
     if (key == players.at(i)->down_key)
       players.at(i)->down_pressed = true;
   }
}

void GameView::keyReleaseEvent(QKeyEvent *event)
{ 
  //qDebug() << "KEYRELEASE:" << event->key();

  for (int i=0; i < players.size(); ++i)
  {
     int key = event->key();
     
     if (key == players.at(i)->left_key)
       players.at(i)->left_pressed = false;
       
     if (key == players.at(i)->right_key)
       players.at(i)->right_pressed = false;

     if (key == players.at(i)->up_key)
       players.at(i)->up_pressed = false;
       
     if (key == players.at(i)->down_key)
       players.at(i)->down_pressed = false;
  }
}
