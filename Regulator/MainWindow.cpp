#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);
  	layout = new QFormLayout(this);
	SpinBox_w = new QSpinBox(this);
	LCD_y = new QLCDNumber(this);
	LCD_u = new QLCDNumber(this);
	reg = new rPID();
	int size = 50;
	//FIXED SIZE niepoprwnie ale skutecznie
	SpinBox_w->setFixedSize(size * 2, size);
	LCD_y->setFixedSize(size * 2, size);
	LCD_u->setFixedSize(size * 2, size);
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
}

MainWindow::~MainWindow()
{
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
}


