#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include <QObject>
#include <QtCharts> 
#include "serial.cpp" 


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	//regulator
	reg = new rPID();
	reg->SetURange(0, 1000);
	//okres próbkowania
	timer = new QTimer(this);
	timer->setInterval(100);  //100ms
	connect(timer, SIGNAL(timeout()), this, SLOT(Run()));
	
	setControls();
	setPlot();
	setlayout();

	//serial con
	int fd;
	bytesreaded = new unsigned long;
	char *ch="/dev/ttyACM0";
	fd=open(fd,ch);
	read(buff,bytesreaded,4);
	
	timer->start(); 
}

MainWindow::~MainWindow()
{
	delete Button_reset;
    delete ui;
	delete layout_main;
	delete SpinBox_w;
	delete LCD_y;
	delete reg;
	delete tab1;
	delete timer;
		}

void MainWindow::SetW(int i)
{
	w = i;
	}

void MainWindow::Run()
{
	//read(buff, bytesreaded, 4); //serial read
	u = reg->ObliczSterowanie(SpinBox_w->value(), y);
	//niby obiekt
	y =.1*(u - sqrt(y));
	LCD_y->display(y);
	LCD_u->display(u);
	reg->Setk(SpinBox_k->value());
	reg->SetTi(SpinBox_Ti->value());
	reg->SetTd(SpinBox_Td->value());
	plot(y, SpinBox_w->value());
}

void MainWindow::reset()
{
	u = 0;
	y = 0;
	SpinBox_w->setValue(0);
	LCD_y->display(0);
	LCD_u->display(0);
	reg->Reset();
}


void MainWindow::setlayout()
{
	QTabWidget *tabWidget = new QTabWidget(this);
	layout_main = new QFormLayout(this);
	layout_settings = new QFormLayout(this);
	layout_plot = new QGridLayout(this);
	tab1 = new QWidget(this);
	tab2 = new QWidget(this);
	tab3 = new QWidget(this);

	tab1->setLayout(layout_main);
	tab2->setLayout(layout_plot);
	tab3->setLayout(layout_settings);
	Lmain(layout_main);
	Lsettings(layout_settings);
	Lplot(layout_plot);
	setCentralWidget(tabWidget);
	tabWidget->addTab(tab1, "Main");
	tabWidget->addTab(tab2, "Plot");
	tabWidget->addTab(tab3, "Settings");
}

void MainWindow::Lplot(QGridLayout *layout)
{
	layout->addWidget(customPlot);
}

void MainWindow::Lmain(QFormLayout* layout)
{
	layout->addRow("Wartsc zadana", SpinBox_w);
	layout->addRow("Sterowanie", LCD_u);
	layout->addRow("Wartosc", LCD_y);
	layout->addRow(Button_reset);
	int size = 50;
	SpinBox_w->setFixedSize(size*5 , size);
	LCD_y->setFixedSize(size * 5, size);
	LCD_u->setFixedSize(size * 5, size); 
}

void MainWindow::Lsettings(QFormLayout* layout)
{
	layout->addRow("k", SpinBox_k);
	layout->addRow("Ti", SpinBox_Ti);
	layout->addRow("Td", SpinBox_Td);
}


void MainWindow::setPlot()
{
	customPlot = new QCustomPlot(this);
	customPlot->addGraph();  // blue line
	customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
	customPlot->addGraph();  // red line
	customPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));
 
	QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
	timeTicker->setTimeFormat("%h:%m:%s");
	customPlot->xAxis->setTicker(timeTicker);
	customPlot->axisRect()->setupFullAxesBox();
	//customPlot->yAxis->setRange(0, 10);
 
	// make left and bottom axes transfer their ranges to right and top axes:
	connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
	connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
}

void MainWindow::plot(float y, float w)
{
	static QTime time(QTime::currentTime());
	double now = time.msecsSinceStartOfDay()/1000.0;
	// calculate two new data points:
	double key = now + time.elapsed() / 1000.0;//*60*60;   // time elapsed since start of demo, in sec//hours
	static double lastPointKey = 0;
	
			// add data to lines:
			customPlot->graph(0)->addData(key, y);
			customPlot->graph(1)->addData(key, w);
			// rescale value (vertical) axis to fit the current data:
			customPlot->graph(0)->rescaleValueAxis();
			customPlot->graph(1)->rescaleValueAxis(false,true);
			lastPointKey = key;
	
	// make key axis range scroll with the data (at a constant range size of 8):
	customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
	customPlot->replot();
}

void MainWindow::setControls()
{SpinBox_w = new QSpinBox(this);
	LCD_y = new QLCDNumber(this);
	LCD_u = new QLCDNumber(this);
	LCD_u->segmentStyle();
	//sygna³ zmiany wartoœci W
	connect(SpinBox_w, QOverload<int>::of(&QSpinBox::valueChanged), [=](int i){ SetW(i); });
	//parametry regulatora
	SpinBox_k = new QSpinBox(this);
	SpinBox_Ti = new QSpinBox(this);
	SpinBox_Td = new QSpinBox(this);
	SpinBox_k->setValue(1);
	SpinBox_Ti->setValue(1);
	SpinBox_Td->setValue(0);
	//parametry elementów okna
	SpinBox_w->setRange(0, 9999);
	//reset button
	Button_reset = new QPushButton("Reset", this);
	connect(Button_reset, SIGNAL(released()), this, SLOT(reset()));
	
}
