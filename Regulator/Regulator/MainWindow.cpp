#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include <QObject>
#include <QtCharts> 


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	SpinBox_w = new QSpinBox(this);
	LCD_y = new QLCDNumber(this);
	LCD_u = new QLCDNumber(this);
	LCD_u->segmentStyle();
	reg = new rPID();
	reg->SetURange(0, 1000);
	
	//sygna³ zmiany wartoœci
	//connect(SpinBox_w,QOverload<int>::of(&QSpinBox::valueChanged),[=](int i){ SetW(); });
	timer = new QTimer;
	timer->setInterval(100);  //100ms
	connect(timer, SIGNAL(timeout()), this, SLOT(SetW()));
	//parametry regulatora
	SpinBox_k = new QSpinBox(this);
	SpinBox_Ti = new QSpinBox(this);
	SpinBox_Td = new QSpinBox(this);
	SpinBox_k->setValue(1);
	SpinBox_Ti->setValue(1);
	SpinBox_Td->setValue(0);
	//parametry elementów okna
	SpinBox_w->setRange(0, 9999);
	//reset
	Button_reset = new QPushButton("Reset", this);
	connect(Button_reset, SIGNAL(released()), this, SLOT(reset()));
	//setPlot();
	
	Setlayout();
	timer->start(); 
	
	//PLOT
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

void MainWindow::ButtonClicked()
{
    QMessageBox msgBox;
    msgBox.setText("Hello, World!");
    msgBox.setWindowTitle("VisualGDB Qt Demo");
    msgBox.exec();
}
void MainWindow::SetW()
{
	u=reg->ObliczSterowanie(SpinBox_w->value(),y);
	//niby obiekt
	y = .1*(u - sqrt(y));
	LCD_y->display(y);
	LCD_u->display(u);
	reg->Setk(SpinBox_k->value());
	reg->SetTi(SpinBox_Ti->value());
	reg->SetTd(SpinBox_Td->value());
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


void MainWindow::Setlayout()
{
	QTabWidget *tabWidget = new QTabWidget(this);
	layout_main = new QFormLayout(this);
	layout_settings = new QFormLayout(this);
	layout_plot = new QFormLayout(this);
	tab1 = new QWidget();
	tab2 = new QWidget();
	tab3 = new QWidget();

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

void MainWindow::Lplot(QFormLayout*layout)
{
	//layout->addRow(chartView);
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
	
	
	

}
