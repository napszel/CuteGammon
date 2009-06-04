#ifndef CHECKER_H
#define CHECKER_H
#include <QObject>
#include <QLabel>

class Point;

class Checker : public QLabel
{
  Q_OBJECT

public:
  enum Player{WHITE=0, BLACK=1};
  Checker(int player, QWidget * parent = 0);
  void mousePressEvent(QMouseEvent * event);
  void setPoint(Point * myPoint);
  Point * getMyPlace() const;
  int getMyColor() const;
  void changeStyle(const char codeletter);
private:
  Point * myPlace;
  int player;
};

#endif
