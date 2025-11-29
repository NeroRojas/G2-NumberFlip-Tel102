#ifndef INTRO_DIALOG_H
#define INTRO_DIALOG_H

#include <QDialog>

class IntroDialog : public QDialog {
    Q_OBJECT
public:
    explicit IntroDialog(QWidget *parent = nullptr);
};

#endif // INTRO_DIALOG_H
