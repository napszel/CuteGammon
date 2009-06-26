#include "lineedit.h"
#include <QMouseEvent>
#include <QLabel>

LineEdit::LineEdit(QString text, QWidget * parent):
  QLineEdit(parent)
{
  setText(text);
  setFrame(false);
  setReadOnly(true);
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
}

void LineEdit::changeTextFinished() {
  setReadOnly(true);
}

