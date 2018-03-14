#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "qcustomplot.h"
#include "rPID.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void ButtonClicked();
	void SetW();
protected:
	QSpinBox *SpinBox_w;
	QLCDNumber *LCD_y;
	QLCDNumber *LCD_u;

private:
    Ui::MainWindow *ui;
	rPID *reg;
	QFormLayout* layout;
	QWidget *window;
	QWidget *w1;
	QTimer *timer;
	float y=0, u=0;
};

#endif // MAINWINDOW_H
