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

MainWindow::MainWindow() : board(0), style('a') {
  setFixedSize(width, height);

/* MENU + TOOLBAR */
  QMenuBar *menuBar = new QMenuBar(this);
  QToolBar *toolBar = new QToolBar(this);
  toolBar->setMovable(false);

  QMenu *fileMenu = new QMenu("&File", this); {
    QAction *newGameAction = fileMenu->addAction(QIcon(":/images/new.png"), "&New", this, SLOT(newGame()));
    toolBar->addAction(newGameAction);
    toolBar->addSeparator();

    QAction *loadGameAction = fileMenu->addAction("&Open", this, SLOT(loadGame()));
    toolBar->addAction(loadGameAction);

    saveGameAction = fileMenu->addAction("&Save"); /* connection set in setBoard()*/
    toolBar->addAction(saveGameAction);

    fileMenu->addAction("E&xit", this, SLOT(close()));
  }

  QMenu *optionsMenu = new QMenu("&Options", this); {
    optionsMenu->addAction("funny style", this, SLOT(changeStyle()));
    optionsMenu->addAction("regular style", this, SLOT(changeBackStyle()));
  }

  QMenu *helpMenu = new QMenu("&Help", this); {
    helpMenu->addAction("About", this, SLOT(about()));
  }

  menuBar->addMenu(fileMenu);
  menuBar->addMenu(optionsMenu);
  menuBar->addMenu(helpMenu);

  setMenuBar(menuBar);
  addToolBar(toolBar);
/* MENU END */

/* STATUS BAR */
  QStatusBar *statusBar = new QStatusBar(this);
  setStatusBar(statusBar);
  statusBar->setSizeGripEnabled(false);
  statusBar->showMessage("Ready",60000);
/* STATUS BAR END */

  setWindowTitle(tr("Backgammon by Napszel"));
   Board * loadBoard;
  if (Board::loadFromFile(MainWindow::autosaveFilename, loadBoard))
    setBoard(loadBoard);
  else
    newGame();
  board->changeStyle(style);

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
  connect(saveGameAction, SIGNAL(triggered()), this, SLOT(saveGame()));
  board->changeStyle(style);
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

void MainWindow::changeStyle() {
  board->changeStyle('g');
  style = 'g';
}

void MainWindow::changeBackStyle() {
  board->changeStyle('a');
  style = 'a';
}

void MainWindow::autoSaveGame() {
  qDebug() << "Autosave: " << autosaveFilename;
  board->saveToFile(autosaveFilename);
}
