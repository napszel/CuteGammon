#include "point.h"
#include <QDragEnterEvent>
#include <QDebug>

const int Point::scalex = 53;
const int Point::scaley = 260;

Point::Point(Color color, Place place, QWidget* parent):
  QLabel(parent),
  place(place),
  color(color)
{
  changeStyle('a');

  setAcceptDrops(true);
}

void Point::removeChecker() {
  if (!checkers.isEmpty()) {
    checkers.pop();
  }
  else qDebug() << "hiba";
}

int Point::getCheckersNo() {
  return checkers.size();
}

int Point::checkersColor() {
  if (getCheckersNo()!=0)
    return topChecker()->getMyColor();
  else return 2;
}

Checker* Point::topChecker() {
  return checkers.top();
}

void Point::clearCheckers() {
  if (!checkers.isEmpty()) 
    checkers.clear() ;
}

void Point::addChecker(Checker * checker) {
  checkers.push(checker);
  int tmp = getCheckersNo();

  if (getCheckersNo()<6)
    if (place == UP)
      checker->move(QPoint(0,tmp*50-50));
    else
      checker->move(-QPoint(0,tmp*50-260));
  else
    if ((tmp>=6) && (tmp<10))
      if (place == UP)
	checker->move(QPoint(0,tmp*50-280));
      else
	checker->move(-QPoint(0,tmp*50-490));
    else
      if ((tmp>=10) && (tmp<13))
	if (place == UP)
	  checker->move(QPoint(0,tmp*50-460));
	else
	  checker->move(-QPoint(0,tmp*50-670));
      else
	if ((tmp>=13) && (tmp<15))
	  if (place == UP)
	    checker->move(QPoint(0,tmp*50-580));
	  else
	    checker->move(-QPoint(0,tmp*50-795));
	else
	  checker->move(QPoint(0,tmp*50-630));

  checker->setPoint(this);
  checker->setParent(this);
  checker->show();
}


void Point::dragEnterEvent(QDragEnterEvent * event) {
  if (event->mimeData()->hasFormat("application/x-backgammon-checkerdrop")) {
    int thisCheckersColor = ((Checker*) event->source())->getMyColor();
    if ((getCheckersNo() < 2) || (thisCheckersColor == checkersColor())) {
      event->acceptProposedAction();
    } else
      event->ignore();
  } else
    event->ignore();
}

void Point::dropEvent(QDropEvent * event) {
  if (event->mimeData()->hasFormat("application/x-backgammon-checkerdrop")) {
    int thisCheckersColor = ((Checker*) event->source())->getMyColor();
    if ((getCheckersNo() < 2) || (thisCheckersColor == checkersColor())) {
      event->acceptProposedAction();
      Checker *thisChecker = (Checker*) event->source();
      thisChecker->getMyPlace()->removeChecker();
      if ((getCheckersNo() == 1) && (thisCheckersColor != checkersColor())) {
	removeChecker();
      }
      addChecker(thisChecker);
    } else
      event->ignore();
  } else
    event->ignore();
}

void Point::changeStyle(const char codeletter) {
  if (color == WHITE) {
    if (place == DOWN)
      setPixmap(QPixmap(QString(":/images/wdpoint") + codeletter + QString(".png")).scaled(scalex,scaley));
    else
      if (place == UP)
	setPixmap(QPixmap(QString(":/images/wpoint") + codeletter + QString(".png")).scaled(scalex,scaley));
      else
	setPixmap(QPixmap(":/images/semmi.png").scaled(scalex,scaley));
  }else
    if (place == DOWN)
      setPixmap(QPixmap(QString(":/images/bdpoint") + codeletter + QString(".png")).scaled(scalex,scaley));
    else
      if (place == UP)
	setPixmap(QPixmap(QString(":/images/bpoint") + codeletter + QString(".png")).scaled(scalex,scaley));
      else
	setPixmap(QPixmap(":/images/semmi.png").scaled(scalex,scaley));
}
