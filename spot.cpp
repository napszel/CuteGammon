#include "spot.h"

Spot::Spot(int num, QWidget * parent):
  QLabel(parent)
{
  changeStyle('a');
  switch (num){
  case 1:
    move(13,13);
    break;
  case 2:
    move(3,3);
    break;
  case 3:
    move(3,13);
    break;
  case 4:
    move(3,23);
    break;
  case 5:
    move(23,3);
    break;
  case 6:
    move(23,13);
    break;
  case 7:
    move(23,23);
    break;
  }
}

void Spot::changeStyle(const char codeletter) {
  setPixmap(QPixmap(QString(":/images/potty") + codeletter + ".png"));
}
