#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "rPID.h"
#include <QtCharts>
#include <qchart.h>
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
	QTabWidget *tabWidget;
	QFormLayout* layout_main, *layout_settings, *layout_plot;
	QWidget *tab1, *tab2, *tab3;
	QTimer *timer;
	float y=0, u=0;
	QSpinBox *SpinBox_k;
	QSpinBox *SpinBox_Ti;
	QSpinBox *SpinBox_Td;
	void Setlayout();
	void Lsettings(QFormLayout*);
	void Lmain(QFormLayout*);
	void Lplot(QFormLayout*);
	
	 QLineSeries *series;
	void setPlot();
	QChartView *chartView;
	QChart *chart; 
	
};

	
	
#endif // MAINWINDOW_H
