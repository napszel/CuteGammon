#ifndef LINEEDIT_H
#define LINEEDIT_H
#include <QObject>
#include <QLineEdit>

class LineEdit : public QLineEdit
{
  Q_OBJECT

public:
  LineEdit(QString text, QWidget * parent = 0);
  void mouseDoubleClickEvent(QMouseEvent * event);
  void changeColor(QColor color);
public slots:
  void changeText();
  void changeTextFinished();
signals:
  void doubleClicked();
};
#endif
