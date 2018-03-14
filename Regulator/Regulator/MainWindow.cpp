#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include <QObject>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);
  	layout = new QFormLayout(this);
	SpinBox_w = new QSpinBox(this);
	LCD_y = new QLCDNumber(this);
	LCD_u = new QLCDNumber(this);
	reg = new rPID(2,2,2);
	int size = 50;
	//FIXED SIZE niepoprwnie ale skutecznie 
	/*	SpinBox_w->setFixedSize(size * 2, size);
	LCD_y->setFixedSize(size * 2, size);
	LCD_u->setFixedSize(size * 2, size);*/
	//¿eby sie Spinbox i reszta nie by³y stakowane w rogu
	window = new QWidget();
	w1 = new QWidget();
	layout->addRow("Wartsc zadana", SpinBox_w);
	layout->addRow("Sterowanie", LCD_u);
	layout->addRow("Wartosc", LCD_y);
	layout->addWidget(w1);
	window->setLayout(layout);
	// Set QWidget as the central layout of the main window
	setCentralWidget(window);
	//sygna³ zmiany wartoœci
	//connect(SpinBox_w,QOverload<int>::of(&QSpinBox::valueChanged),[=](int i){ SetW(); });
	timer = new QTimer;
	timer->setInterval(100); 
	connect(timer, SIGNAL(timeout()), this, SLOT(SetW()));
	timer->start(); 
	//parametry regulatora
	SpinBox_k = new QSpinBox(this);
	SpinBox_Ti = new QSpinBox(this);
	SpinBox_Td = new QSpinBox(this);
	layout->addRow("k", SpinBox_k);
	layout->addRow("Ti", SpinBox_Ti);
	layout->addRow("Td", SpinBox_Td);
	SpinBox_k->setValue(1);
	SpinBox_Ti->setValue(1);
	SpinBox_Td->setValue(0);
	//parametry elementów okna
	SpinBox_w->setRange(0, 9999);
	//reset
	Button_reset = new QPushButton("Reset",this);
	connect(Button_reset, SIGNAL(released()), this, SLOT(reset()));
	layout->addRow(Button_reset);
}

MainWindow::~MainWindow()
{
	delete Button_reset;
    delete ui;
	delete layout;
	delete SpinBox_w;
	delete LCD_y;
	delete reg;
	delete w1;
	delete window;
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
}
