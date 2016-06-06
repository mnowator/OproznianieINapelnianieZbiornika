#include "mainwindow.h"
#include "ui_mainwindow.h"

#define PI 3.14159265
#define G 9.80665

#include <cmath>
#include "QGraphicsRectItem"

void MainWindow::drawTank()
{
    QGraphicsScene* scene = new QGraphicsScene();

    QGraphicsRectItem* item1 = new QGraphicsRectItem(0,60,20,300);
    item1->setBrush(QBrush(Qt::darkGreen));
    item1->setPen(QPen(Qt::NoPen));
    scene->addItem(item1);

    QGraphicsRectItem* item2 = new QGraphicsRectItem(320,60,20,300);
    item2->setBrush(QBrush(Qt::darkGreen));
    item2->setPen(QPen(Qt::NoPen));
    scene->addItem(item2);

    QGraphicsRectItem* item3 = new QGraphicsRectItem(20,340,300,20);
    item3->setBrush(QBrush(Qt::darkGreen));
    item3->setPen(QPen(Qt::NoPen));
    scene->addItem(item3);

    QGraphicsRectItem* item4 = new QGraphicsRectItem(20,340-280*(fluidHeight/tankHeight),300,280*(fluidHeight/tankHeight));
    item4->setBrush(QBrush(Qt::darkBlue));
    item4->setPen(QPen(Qt::NoPen));
    scene->addItem(item4);

    ui->graphicsView->setScene(scene);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    renderTimer = new QTimer(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_fluidIncomeValveSlider_sliderMoved(int position)
{
    ui->fluidIncomeValveLabel->setText(QString::number(position)+"%");
}

void MainWindow::on_tankHeightLineEdit_textEdited(const QString &arg1)
{
    tankHeight = arg1.toDouble();
}

void MainWindow::on_tankDiameterLineEdit_textEdited(const QString &arg1)
{
    tankDiameter = arg1.toDouble();
}

void MainWindow::on_simulationActiveRadioButton_clicked()
{
    tankVolume = PI * std::pow(tankDiameter/2,2) * tankHeight;
    outcomeValveArea = PI*std::pow(outcomeValveDiameter/2,2);

    connect(renderTimer,SIGNAL(timeout()),this,SLOT(render()));
    renderTimer->start(16);

    ui->tankDiameterLineEdit->setEnabled(false);
    ui->tankHeightLineEdit->setEnabled(false);
    ui->fluidIncomeLineEdit->setEnabled(false);
    ui->fluidOutcomeValveLineEdit->setEnabled(false);
}

void MainWindow::render()
{
    double incomeFlow = fluidIncome * (ui->fluidIncomeValveSlider->value()/(double)100) * (16/((double)1000));

    fluidVolume += incomeFlow;
    fluidHeight = fluidVolume/(PI * std::pow(tankDiameter/2,2));

    ui->incomeFlowLabel->setText(QString::number((incomeFlow*1000)*(1000.0/16.0))+" l/s");

    double outcomeFlow = outcomeValveArea*std::sqrt(2*G*fluidHeight) * (ui->fluidOutcomeValveSlider->value()/(double)100) * (16/((double)1000));

    ui->outcomeFlowLabel->setText(QString::number((outcomeFlow*1000)*(1000.0/16.0))+" l/s");

    fluidVolume -= outcomeFlow;
    fluidHeight = fluidVolume/(PI * std::pow(tankDiameter/2,2));

    ui->tankVoulumeInLitreLabel->setText(QString::number(fluidVolume*1000.0)+" l");
    ui->tankHeightLabel->setText(QString::number(fluidHeight)+" m");

    drawTank();
}

void MainWindow::on_fluidIncomeLineEdit_textEdited(const QString &arg1)
{
    fluidIncome = arg1.toDouble();
}

void MainWindow::on_simulationInactiveRadioButton_clicked()
{
    renderTimer->stop();
    disconnect(renderTimer,SIGNAL(timeout()),this,SLOT(render()));

    ui->tankDiameterLineEdit->setEnabled(true);
    ui->tankHeightLineEdit->setEnabled(true);
    ui->fluidIncomeLineEdit->setEnabled(true);
    ui->fluidOutcomeValveLineEdit->setEnabled(true);
}

void MainWindow::on_fluidOutcomeValveSlider_sliderMoved(int position)
{
    ui->fluidOutcomeValveLabel->setText(QString::number(position)+"%");
}

void MainWindow::on_fluidOutcomeValveLineEdit_textEdited(const QString &arg1)
{
    outcomeValveDiameter = arg1.toDouble();
}
