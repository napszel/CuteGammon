#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H
#include <QObject>
#include <QLabel>

class ClickableLabel : public QLabel
{
  Q_OBJECT

public:
  ClickableLabel(QWidget * parent = 0);
  void mousePressEvent(QMouseEvent * event);
  void mouseDoubleClickEvent(QMouseEvent * event);
signals:
  void clicked();
  void doubleClicked(ClickableLabel * what);
};
#endif
