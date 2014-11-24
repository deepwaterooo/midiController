#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGroupBox>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QPlainTextEdit>

static const QPointF points[3] = {
    QPointF(10.0, 80.0),
    QPointF(20.0, 10.0),
    QPointF(80.0, 30.0)
};

class MainWindow : public QMainWindow {
    Q_OBJECT
    QWidget *centralWidget;
    //QVBoxlayout *vbox;
 public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //void paintEvent( QPaintEvent* event );
    void setHeight(QPlainTextEdit *edit, int nRows);

 private:
    void open();
    
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
    QPushButton* topKeys[15];
    QPushButton* bottomKeys[15];
    
};

#endif
