#include "checker.h"
#include "point.h"
#include <QDebug>
#include <QMouseEvent>
#include <QDataStream>
#include <QByteArray>

Checker::Checker(int player, QWidget * parent):
  QLabel(parent),
  myPlace(0),
  player(player)
{
  changeStyle('a');
}


int Checker::getMyColor() const {
  return player;
}

Point* Checker::getMyPlace() const {
  return myPlace;
}

void Checker::setPoint(Point * myPoint) {
  myPlace = myPoint;
}

void Checker::mousePressEvent(QMouseEvent * event) {
  // Ahelyett, hogy a megfogott this-t húznánk, megkeressük a this alatti Point
  // legfelső checkerjét és azt húzzuk.
  QLabel * top_checker = myPlace->topChecker();
  QDrag *drag = new QDrag(top_checker);
  QMimeData *dropMimeData = new QMimeData;
  dropMimeData->setData("application/x-backgammon-checkerdrop", QByteArray());
  drag->setMimeData(dropMimeData);
  drag->setPixmap(*top_checker->pixmap());
  drag->setHotSpot(event->pos());

  top_checker->hide();
  drag->exec(Qt::MoveAction, Qt::MoveAction);
  top_checker->show();
}

void Checker::changeStyle(const char codeletter) {
  if (player == WHITE)
    setPixmap(QPixmap(QString(":/images/white") + codeletter + QString(".png")));
  else
    setPixmap(QPixmap(QString(":/images/black") + codeletter + QString(".png")));
}
