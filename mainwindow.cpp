#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QIcon>
#include <QPixmap>
#include <QDebug>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnNewGame, &QPushButton::clicked, this, &MainWindow::onNewGameClicked);
    connect(ui->btnExit, &QPushButton::clicked, this, &MainWindow::onExitClicked);

    setWindowIcon(QIcon(":/bomb.png"));

    setupBoardUI();
    
    // Debug: Check if resources exist
    if(!QFile::exists(":/back.png")) {
        qDebug() << "ERROR: :/back.png not found!";
    } else {
        qDebug() << "SUCCESS: :/back.png found.";
    }

    onNewGameClicked(); // Start a new game immediately
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupBoardUI()
{
    // Clear existing layout if any (though this runs once in constructor)
    // We need a 6x6 grid to include hints:
    //      C1 C2 C3 C4 C5
    // R1   [ ][ ][ ][ ][ ]  B:x S:y
    // R2   [ ][ ][ ][ ][ ]  B:x S:y
    // ...
    //      B  B  B  B  B
    //      S  S  S  S  S

    // Actually, let's put hints around the 5x5 grid.
    // Grid Layout:
    // Row 0: Column Headers (A, B, C...) or just empty
    // Rows 1-5: The buttons + Row Hints
    // Row 6: Column Bomb Hints
    // Row 7: Column Sum Hints

    QGridLayout *grid = ui->gridLayoutBoard;
    
    buttons.resize(5, std::vector<QPushButton*>(5));
    rowBombLabels.resize(5);
    rowSumLabels.resize(5);
    colBombLabels.resize(5);
    colSumLabels.resize(5);

    // Create Buttons (Rows 0-4, Cols 0-4)
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            QPushButton *btn = new QPushButton(this);
            btn->setFixedSize(60, 80); // Card size
            btn->setIconSize(QSize(50, 70));
            btn->setProperty("row", i);
            btn->setProperty("col", j);
            connect(btn, &QPushButton::clicked, this, &MainWindow::onCardClicked);
            grid->addWidget(btn, i, j);
            buttons[i][j] = btn;
        }
    }

    // Create Row Hints (Col 5 and 6)
    for(int i=0; i<5; i++){
        QString chipStyle = (i % 2 == 0) ? "QLabel { border-image: url(:/chip1.png); color: white; font-weight: bold; }" 
                                         : "QLabel { border-image: url(:/chip2.png); color: white; font-weight: bold; }";

        QLabel *lblBomb = new QLabel(this);
        lblBomb->setAlignment(Qt::AlignCenter);
        lblBomb->setStyleSheet(chipStyle);
        lblBomb->setFixedSize(50, 50); // Make them somewhat square/chip-like
        grid->addWidget(lblBomb, i, 5);
        rowBombLabels[i] = lblBomb;

        QLabel *lblSum = new QLabel(this);
        lblSum->setAlignment(Qt::AlignCenter);
        lblSum->setStyleSheet(chipStyle);
        lblSum->setFixedSize(50, 50);
        grid->addWidget(lblSum, i, 6);
        rowSumLabels[i] = lblSum;
    }

    // Create Column Hints (Row 5 and 6)
    for(int j=0; j<5; j++){
        QString chipStyle = (j % 2 == 0) ? "QLabel { border-image: url(:/chip1.png); color: white; font-weight: bold; }" 
                                         : "QLabel { border-image: url(:/chip2.png); color: white; font-weight: bold; }";

        QLabel *lblBomb = new QLabel(this);
        lblBomb->setAlignment(Qt::AlignCenter);
        lblBomb->setStyleSheet(chipStyle);
        lblBomb->setFixedSize(50, 50);
        grid->addWidget(lblBomb, 5, j);
        colBombLabels[j] = lblBomb;

        QLabel *lblSum = new QLabel(this);
        lblSum->setAlignment(Qt::AlignCenter);
        lblSum->setStyleSheet(chipStyle);
        lblSum->setFixedSize(50, 50);
        grid->addWidget(lblSum, 6, j);
        colSumLabels[j] = lblSum;
    }

    // Headers for hints
    grid->addWidget(new QLabel("Bombas", this), 5, 5);
    grid->addWidget(new QLabel("Suma", this), 6, 5);
}

void MainWindow::onNewGameClicked()
{
    board.reset();
    
    // Reset buttons
    QIcon backIcon(":/back.png");
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            buttons[i][j]->setIcon(backIcon);
            buttons[i][j]->setEnabled(true);
            buttons[i][j]->setStyleSheet(""); // Reset style
        }
    }

    updateHints();
    updateSafeCountLabel();
    updateStatusLabel("Elige una carta");
}

void MainWindow::onExitClicked()
{
    close();
}

void MainWindow::onCardClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if(!btn) return;

    int r = btn->property("row").toInt();
    int c = btn->property("col").toInt();

    if(board.isRevealed(r, c)) return;

    bool safe = board.revealCell(r, c);

    if(!safe) {
        // Bomb!
        handleGameOver();
    } else {
        // Safe
        int mult = board.getMultiplier(r, c);
        QString imgPath = QString(":/x%1.png").arg(mult);
        btn->setIcon(QIcon(imgPath));
        
        updateSafeCountLabel();

        if(board.getSafeRevealedCount() == board.getTotalSafeCells()){
            handleVictory();
        }
    }
}

void MainWindow::updateHints()
{
    for(int i=0; i<5; i++){
        rowBombLabels[i]->setText(QString("B: %1").arg(board.bombsInRow(i)));
        rowSumLabels[i]->setText(QString("S: %1").arg(board.sumInRow(i)));
    }
    for(int j=0; j<5; j++){
        colBombLabels[j]->setText(QString("B: %1").arg(board.bombsInCol(j)));
        colSumLabels[j]->setText(QString("S: %1").arg(board.sumInCol(j)));
    }
}

void MainWindow::revealAll()
{
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            if(board.isBomb(i, j)){
                buttons[i][j]->setIcon(QIcon(":/bomb.png"));
            } else {
                int mult = board.getMultiplier(i, j);
                buttons[i][j]->setIcon(QIcon(QString(":/x%1.png").arg(mult)));
            }
            buttons[i][j]->setEnabled(false);
        }
    }
}

void MainWindow::handleGameOver()
{
    revealAll();
    updateStatusLabel("GAME OVER");
    QMessageBox::critical(this, "Game Over", "¡Has encontrado una bomba!");
}

void MainWindow::handleVictory()
{
    revealAll();
    updateStatusLabel("¡VICTORIA!");
    QMessageBox::information(this, "Victoria", "¡Has revelado todas las casillas seguras!");
}

void MainWindow::updateStatusLabel(const QString &text)
{
    ui->labelStatus->setText(text);
}

void MainWindow::updateSafeCountLabel()
{
    ui->labelSafeCount->setText(QString("Seguras: %1 / %2")
                                .arg(board.getSafeRevealedCount())
                                .arg(board.getTotalSafeCells()));
}
