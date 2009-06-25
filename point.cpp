#include "point.h"
#include "board.h"
#include <QDragEnterEvent>
#include <QDebug>

const int Point::scalex = 53;
const int Point::scaley = 260;

Point::Point(Color color, Place place, QWidget* parent):
  QLabel(parent),
  color(color),
  place(place)
{
  changeStyle('a');

  setAcceptDrops(true);
}

// FIXME: use Q_ASSERT
void Point::removeChecker() {
  if (!checkers.isEmpty()) {
    checkers.pop();
  }
  else
    qDebug() << "hiba";
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
  if (!checkers.isEmpty()) {
    return checkers.top();
  }
  else {
    qDebug() << "hiba";
    return 0;
  }
}

void Point::clearCheckers() {
  checkers.clear();
}

void Point::addChecker(Checker * checker) {
  checkers.push(checker);
  int tmp = getCheckersNo();

  if (tmp<6)
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
      if ((getCheckersNo() == 1) && (thisCheckersColor != checkersColor())) { //hit
	emit killedChecker(topChecker());
	removeChecker();
      }
      addChecker(thisChecker);
    } else
      event->ignore();
  } else
    event->ignore();
}

void Point::changeStyle(const char codeletter) {
  if (place == END) {
    setPixmap(QString(":/images/semmi.png"));
    return;
  }

  QString direction;
  if (place == DOWN)
    direction = "d";
  else
    direction = "";

  QString colorstr;
  if (color == WHITE)
    colorstr = "w";
  else
    colorstr = "b";

  setPixmap(QPixmap(QString(":/images/") + colorstr + direction + "point" + codeletter + ".png").scaled(scalex, scaley));
}

int Point::myPlace() {
  return place;
}

