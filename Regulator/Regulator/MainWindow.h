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
	void reset();
protected:
	QSpinBox *SpinBox_w;
	QLCDNumber *LCD_y;
	QLCDNumber *LCD_u;
	QLCDNumber *LCD_k;
	QLCDNumber *LCD_Ti;
	QLCDNumber *LCD_Td;
	QPushButton *Button_reset;

private:
    Ui::MainWindow *ui;
	rPID *reg;
	QFormLayout* layout;
	QWidget *window;
	QWidget *w1;
	QTimer *timer;
	float y=0, u=0;
	QSpinBox *SpinBox_k;
	QSpinBox *SpinBox_Ti;
	QSpinBox *SpinBox_Td;
};

	
	
#endif // MAINWINDOW_H
