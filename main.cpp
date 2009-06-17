#include <QtGui>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  srand ( time(NULL) );
  MainWindow *mainWindow = new MainWindow;
  mainWindow->show();

  QObject::connect(&app, SIGNAL(aboutToQuit()), mainWindow, SLOT(autoSaveGame()));
  return app.exec();
}
