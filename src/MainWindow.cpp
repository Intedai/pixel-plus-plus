#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      cView(new CanvasView(this)),
      cs(new ColorSelector(this))
{   
    createActions();
    createMenus();
    createToolBarAndMenus();

    setCentralWidget(cView);

    connect(cs, &ColorSelector::closed, this, [=] {
        colorSelectorAct->setChecked(false);
    });

    setWindowTitle(tr("Pixel++ - Untitled"));
    resize(800, 600);
}

void MainWindow::newFile()
{
    
}

void MainWindow::openFile()
{

}

void MainWindow::undo()
{

}

void MainWindow::redo()
{

}

void MainWindow::setColorSelectorOn(bool on)
{
    cs->setVisible(on);
}

void MainWindow::createActions()
{
    newFileAct = new QAction(tr("&New"), this);
    newFileAct->setShortcuts(QKeySequence::New);
    connect(newFileAct, &QAction::triggered, this, &MainWindow::newFile);

    openFileAct = new QAction(tr("&Open"), this);
    openFileAct->setShortcuts(QKeySequence::Open);
    connect(openFileAct, &QAction::triggered, this, &MainWindow::openFile);

    quitAct = new QAction(tr("&Quit"), this);
    quitAct->setShortcuts(QKeySequence::Quit);
    connect(quitAct, &QAction::triggered, this, &MainWindow::close);

    undoAct = new QAction(tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    connect(undoAct, &QAction::triggered, this, &MainWindow::undo);

    redoAct = new QAction(tr("&Redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    connect(redoAct, &QAction::triggered, this, &MainWindow::redo);

    colorSelectorAct = new QAction(tr("&Color Selector"), this);
    colorSelectorAct->setCheckable(true);
    connect(colorSelectorAct, &QAction::toggled, this, &MainWindow::setColorSelectorOn);
}

void MainWindow::createMenus()
{
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(newFileAct);
    fileMenu->addAction(openFileAct);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);

    editMenu = new QMenu(tr("&Edit"), this);
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();

    viewMenu = new QMenu(tr("&View"), this);

    adjustmentsMenu = new QMenu(tr("&Adjustments"), this);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(editMenu);
    menuBar()->addMenu(viewMenu);
    menuBar()->addMenu(adjustmentsMenu);
}

void MainWindow::createToolBarAndMenus()
{
    toolbar = new QToolBar();
    toolbar->setMovable(false);
    toolbar->addAction(newFileAct);
    toolbar->addAction(openFileAct);
    toolbar->addSeparator();
    toolbar->addAction(undoAct);
    toolbar->addAction(redoAct);

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    toolbar->addWidget(spacer);

    toolbar->addAction(colorSelectorAct);

    addToolBar(toolbar);
}
