#ifndef POINT_H
#define POINT_H
#include <QObject>
#include <QLabel>
#include <QStack>
#include "checker.h"

class Point : public QLabel
{
  Q_OBJECT

public:
  static const int scalex, scaley;
  enum Color{WHITE, BLACK};
  enum Place{UP, DOWN, END};
  Point(Color color, Place place, QWidget * parent = 0);
  void removeChecker();
  void addChecker(Checker * checker);
  void dragEnterEvent(QDragEnterEvent * event);
  void dropEvent(QDropEvent * event);
  int getCheckersNo();
  void clearCheckers();
  int checkersColor();
  Checker * topChecker();
  void changeStyle(const char codeletter);

signals:
  void killedChecker(Checker * checkerHit);

private:
  Color color;
  Place place;
  QStack<Checker*> checkers;
};

#endif
