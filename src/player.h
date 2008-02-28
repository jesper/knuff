#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsEllipseItem>
#include <QBrush>

class Player : public QGraphicsEllipseItem
{
public:
  Player(QGraphicsItem *parent=0);
  qreal xspeed;
  qreal yspeed;
  
  int type() const;

  Qt::Key up_key;
  Qt::Key down_key;
  Qt::Key left_key;
  Qt::Key right_key;
  
  bool up_pressed;
  bool down_pressed;
  bool left_pressed;
  bool right_pressed;
};
#endif
