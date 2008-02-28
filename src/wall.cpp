#include "wall.h"

Wall::Wall( QGraphicsItem *parent ) 
  : QGraphicsPathItem(parent)
{
}

int Wall::type() const
{
  return WallType;
}
