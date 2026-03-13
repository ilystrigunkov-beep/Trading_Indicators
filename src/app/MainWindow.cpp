#include "app/MainWindow.hpp"

#include <QAction>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QStatusBar>

#include <type_traits>
#include <variant>

namespace app {

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent){
    setWindowTitle("OurProject - Data Analyzer");
    resize(1100, 700);




    create_menu();
    statusBar()->showMessage("Open a CSV file to analyze.");
}

void MainWindow::create_menu() {
    auto* file_menu = menuBar()->addMenu("&File");

    auto* open_action = new QAction("&Open CSV...", this);
    open_action->setShortcut(QKeySequence::Open);
    connect(open_action, &QAction::triggered, this, &MainWindow::on_open_file);
    file_menu->addAction(open_action);

    file_menu->addSeparator();

    auto* exit_action = new QAction("E&xit", this);
    exit_action->setShortcut(QKeySequence::Quit);
    connect(exit_action, &QAction::triggered, this, &QWidget::close);
    file_menu->addAction(exit_action);
}

void MainWindow::on_open_file() {
    //todo;
}

void MainWindow::open_csv(const std::string& path) {
    //todo;
}

} // namespace app
