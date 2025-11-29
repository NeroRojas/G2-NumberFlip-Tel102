#include "intro_dialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFont>

IntroDialog::IntroDialog(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Bienvenido a NumberFlip");
    setFixedSize(600, 500);

    // Dark theme for this dialog
    setStyleSheet("background-color: #2E2E2E; color: white;");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(20);
    layout->setContentsMargins(30, 30, 30, 30);

    // Title
    QLabel *title = new QLabel("NumberFlip", this);
    QFont titleFont = title->font();
    titleFont.setPointSize(20);
    titleFont.setBold(true);
    title->setFont(titleFont);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("color: #FFD700;"); // Gold color
    layout->addWidget(title);

    // Body Text
    QLabel *text = new QLabel(this);
    text->setWordWrap(true);
    QFont textFont = text->font();
    textFont.setPointSize(12);
    text->setFont(textFont);
    text->setText(
        "<h3>Teoría: Probabilidad Condicional</h3>"
        "<p>El núcleo matemático de este juego se basa en la <b>Probabilidad Condicional</b>. "
        "Esta teoría estudia cómo cambia la probabilidad de un evento cuando obtenemos nueva información.</p>"
        
        "<p><b>La Fórmula:</b><br>"
        "La probabilidad de un evento A, dado que sabemos que ocurrió B, se define como:</p>"
        
        "<p align='center' style='font-size:14pt'><b>P(A|B) = P(A &cap; B) / P(B)</b></p>"
        
        "<p>Donde:</p>"
        "<ul>"
        "<li><b>P(A|B):</b> Probabilidad de A dado B (lo que queremos saber).</li>"
        "<li><b>P(A &cap; B):</b> Probabilidad de que pasen ambos.</li>"
        "<li><b>P(B):</b> Probabilidad de la condición (la pista).</li>"
        "</ul>"

        "<p><b>En el Juego:</b><br>"
        "Imagina una fila de 5 casillas con una pista de '2 Bombas'.<br>"
        "Inicialmente, la probabilidad de bomba es <b>2/5 (40%)</b>.<br>"
        "Si volteas una carta y es segura (Evento B), la probabilidad de que las restantes sean bombas (Evento A) cambia a <b>2/4 (50%)</b>.</p>"
        
        "<p>¡Usa cada pista para actualizar tus probabilidades y minimizar el riesgo!</p>"
    );
    layout->addWidget(text);

    // Spacer
    layout->addStretch();

    // Button
    QPushButton *btnStart = new QPushButton("Comenzar Juego", this);
    btnStart->setFixedSize(200, 50);
    btnStart->setStyleSheet(
        "QPushButton { "
        "   background-color: #4CAF50; "
        "   color: white; "
        "   font-size: 16px; "
        "   font-weight: bold; "
        "   border-radius: 10px; "
        "} "
        "QPushButton:hover { background-color: #45a049; }"
    );
    connect(btnStart, &QPushButton::clicked, this, &QDialog::accept);
    
    // Center button
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addStretch();
    btnLayout->addWidget(btnStart);
    btnLayout->addStretch();
    layout->addLayout(btnLayout);
}
