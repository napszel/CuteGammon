#include <QtGui>
#include "board.h"
#include "mainwindow.h"
#include <stdio.h>
#include <QDebug>
#include <QToolBar>
#include <QMenu>
#include <QStatusBar>
#include <QPalette>
#include <QIcon>
#include <QString>
#include <QFileDialog>
#include <QTimer>

const QString MainWindow::autosaveFilename(QFSFileEngine::homePath() +
				      QDir::separator() +
				      ".autosave.bgm");

const unsigned int MainWindow::width = 970;
const unsigned int MainWindow::height = 770;

MainWindow::MainWindow() : board(0) {
  setFixedSize(width, height);

/* MENU  */
  menuBar = new QMenuBar(this);

  fileMenu = new QMenu("&File", this);
    newgame = fileMenu->addAction("&New");
    connect(newgame, SIGNAL(triggered()), this, SLOT(newGame()));

    loadgame = fileMenu->addAction("&Open");
    connect(loadgame, SIGNAL(triggered()), this, SLOT(loadGame()));

    savegame = fileMenu->addAction("&Save");
    /* connection set in setBoard()*/

    exitAction = fileMenu->addAction("E&xit");
    connect(exitAction, SIGNAL(triggered()), this, SLOT(exit()));

  optionsMenu = new QMenu("&Options", this);
    changeStyleAction = optionsMenu->addAction("Gergo Style");
    connect(changeStyleAction, SIGNAL(triggered()), this, SLOT(changeStyle()));

  helpMenu = new QMenu("&Help", this);
    aboutAction = helpMenu->addAction(tr("About"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

  menuBar->addMenu(fileMenu);
  menuBar->addMenu(optionsMenu);
  menuBar->addMenu(helpMenu);

  setMenuBar(menuBar);
/* MENU END */


/* STATUS BAR */
  statusBar = new QStatusBar(this);
  setStatusBar(statusBar);
  statusBar->setSizeGripEnabled(false);
  statusBar->showMessage("Ready",60000);
/* STATUS BAR END */


/* TOOL BAR */
  toolBar = new QToolBar(this);

  newgamebar = new QAction(QIcon(":/images/new.png"), "&New", this);
  toolBar->addAction(newgamebar);
  connect(newgamebar, SIGNAL(triggered()), this, SLOT(newGame()));
  toolBar->addSeparator();

  savegamebar = toolBar->addAction("Save");
  /* connection set in setBoard()*/
  toolBar->addSeparator();

  loadgamebar = toolBar->addAction("Open");
  connect(loadgamebar, SIGNAL(triggered()), this, SLOT(loadGame()));

  toolBar->setMovable(false);

  addToolBar(toolBar);
/*TOOL BAR END */

  setWindowTitle(tr("Backgammon by Napszel"));
   Board * loadBoard;
  if (Board::loadFromFile(MainWindow::autosaveFilename, loadBoard))
    setBoard(loadBoard);
  else
    newGame();

  autosaveTimer = new QTimer(this);
  connect(autosaveTimer, SIGNAL(timeout()), this, SLOT(autoSaveGame()));
  autosaveTimer->start(60000);   //auto save every 1 minute
}

void MainWindow::setBoard(Board * newBoard) {
  delete board;
  board = newBoard;
  setCentralWidget(board);
  board->move(200,200);
  board->setParent(this);
  connect(savegamebar, SIGNAL(triggered()), this, SLOT(saveGame()));
  connect(savegame, SIGNAL(triggered()), this, SLOT(saveGame()));
}

void MainWindow::newGame() {
  setBoard(new Board(this));
}

void MainWindow::loadGame() {
  QString fileName = QFileDialog::getOpenFileName(this, "Load game",
		     QFSFileEngine::homePath()+"/mybackgammongame.bgm",
		     "Backgammon games (*.bgm);;All files (*)");
  if (!fileName.isEmpty()) {
    Board * loadedBoard = 0;
    if (Board::loadFromFile(fileName, loadedBoard)) {
      setBoard(loadedBoard);
    }
    else QMessageBox::warning(this, "Bad file", "Can't open this file.");
  }
}

void MainWindow::saveGame() {
  QString fileName = QFileDialog::getSaveFileName(this, "Save game",
	QFSFileEngine::homePath()+"/mybackgammongame.bgm",
	     "Backgammon games (*.bgm);;All files (*)");
  if (!fileName.isEmpty()) {
    if (!fileName.endsWith(".bgm"))
      fileName += ".bgm";
    board->saveToFile(fileName);
  }
};

void MainWindow::about() {
  QMessageBox::information(this, "About", "Made by Szadeczky-Karodoss Eva and Risko Gergely \n2009");
}

void MainWindow::exit() {
  autoSaveGame();
  QMessageBox::information(this, "FYI",
	 "The current game have been saved and will be reloded the next time you start this program.");
  close();
}

void MainWindow::changeStyle() {
  board->changeStyle('g');
}

void MainWindow::autoSaveGame() {
  qDebug() << "Autosave: " << autosaveFilename;
  board->saveToFile(autosaveFilename);
}
