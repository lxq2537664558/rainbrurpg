

#include "Point.hpp"

#include "Logger.hpp"

Logger static_logger("graphic", LT_BOTH);

Point::Point(int vX, int vY):
  x(vX), y(vY)
{
  LOGI("Constructing a point" << this);
}
