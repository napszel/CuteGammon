#include "lineedit.h"
#include <QMouseEvent>
#include <QLabel>
#include <QPalette>

LineEdit::LineEdit(QString text, QWidget * parent):
  QLineEdit(parent)
{
  setText(text);
  adjustSize();
  setFrame(false);
  setReadOnly(true);

  QPalette myPalette;
  myPalette.setBrush(QPalette::Base, QColor(250,234,168));
  setPalette(myPalette);
  setAutoFillBackground(true);

  connect(this, SIGNAL(doubleClicked()),
	  this, SLOT(changeText()));
  connect(this, SIGNAL(editingFinished()),
	  this, SLOT(changeTextFinished()));
}


void LineEdit::mouseDoubleClickEvent(QMouseEvent * /*event*/)
{
  emit doubleClicked();
}

void LineEdit::changeText() {
  setReadOnly(false);
  selectAll();
}

void LineEdit::changeTextFinished() {
  setReadOnly(true);
}

void LineEdit::changeColor(QColor color) {
  QPalette myPalette;
  myPalette.setBrush(QPalette::Base, color);
  setPalette(myPalette);
}

