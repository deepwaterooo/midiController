#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGroupBox>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QPlainTextEdit>

/*
  namespace Ui {
  class MainWindow;
  }
*/

class MainWindow : public QMainWindow {
    Q_OBJECT
    QWidget *centralWidget;
    //QVBoxlayout *vbox;
 public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
 private:
    void open();
    void setHeight(QPlainTextEdit *edit, int nRows);
    
    enum { NumGridRows = 12, NumButtons = 6 };

    QAction *openAction;
    QAction *exitAction;
    QAction *openAction2;
    QAction *openAction3;
    QAction *openAction4;
    QAction *openAction5;
    QToolBar *toolBar;
    
    QPushButton *buttons[NumButtons];
    QGroupBox *horizontalGroupBox;
    QDialogButtonBox *buttonBox;

    // for layoutw
    QPushButton* topKeys[13];
    QPushButton* bottomKeys[15];
    
};

#endif
