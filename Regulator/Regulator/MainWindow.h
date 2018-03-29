#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTextStream>
#include "rPID.h"
#include <QtCharts>
#include <qchart.h>
#include "qcustomplot.h"

#include <unistd.h>
#include <termios.h>
namespace Ui {
class MainWindow;
}
//using namespace QtCharts;
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
	void SetW(int);
	void reset();
	void Run();
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
	QTabWidget *tabWidget;
	QFormLayout* layout_main, *layout_settings;
	QGridLayout *layout_plot;
	QWidget *tab1, *tab2, *tab3;
	QTimer *timer, *dataTimer;
	float y=0, u=0,w=0;
	QSpinBox *SpinBox_k;
	QSpinBox *SpinBox_Ti;
	QSpinBox *SpinBox_Td;
	void setlayout();
	void setControls();
	void Lsettings(QFormLayout*);
	void Lmain(QFormLayout*);
	void Lplot(QGridLayout*);
	
	//wykres
	QCustomPlot *customPlot;
	void setPlot();
	void plot(float,float);
// komunikacja
	void *buff; //bufor seriala
	int fd; //indetyfikator portu
	unsigned long *bytesreaded;
};

	
	
#endif // MAINWINDOW_H

