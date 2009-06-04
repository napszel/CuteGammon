#include <QMouseEvent>
#include <QLabel>
#include "spot.h"

Spot::Spot(int num, QWidget * parent):
  QLabel(parent)
{
  changeStyle('a');
  switch (num){
  case 1:
    move(15,15);
    break;
  case 2:
    move(5,5);
    break;
  case 3:
    move(5,15);
    break;
  case 4:
    move(5,25);
    break;
  case 5:
    move(25,5);
    break;
  case 6:
    move(25,15);
    break;
  case 7:
    move(25,25);
    break;
  }
}

void Spot::changeStyle(const char codeletter) {
  setPixmap(QPixmap(QString(":/images/potty") + codeletter + QString(".png")));
}

