#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <vector>
#include "board.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCardClicked();
    void onNewGameClicked();
    void onExitClicked();

private:
    Ui::MainWindow *ui;
    Board board;
    std::vector<std::vector<QPushButton*>> buttons;
    
    // Labels for hints
    std::vector<QLabel*> rowBombLabels;
    std::vector<QLabel*> rowSumLabels;
    std::vector<QLabel*> colBombLabels;
    std::vector<QLabel*> colSumLabels;

    void setupBoardUI();
    void updateBoardUI();
    void updateHints();
    void revealAll();
    void handleGameOver();
    void handleVictory();
    void updateStatusLabel(const QString &text);
    void updateSafeCountLabel();
};
#endif // MAINWINDOW_H
