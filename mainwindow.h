#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    double tankHeight = 0;
    double tankDiameter = 0;
    double tankVolume = 0;
    double fluidHeight = 0;
    double fluidVolume = 0;
    double fluidIncome = 0;
    double outcomeValveDiameter = 0;
    double outcomeValveArea = 0;

    QTimer* renderTimer;

    void drawTank();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_fluidIncomeValveSlider_sliderMoved(int position);

    void on_tankHeightLineEdit_textEdited(const QString &arg1);

    void on_tankDiameterLineEdit_textEdited(const QString &arg1);

    void on_simulationActiveRadioButton_clicked();

    void render();

    void on_fluidIncomeLineEdit_textEdited(const QString &arg1);

    void on_simulationInactiveRadioButton_clicked();

    void on_fluidOutcomeValveSlider_sliderMoved(int position);

    void on_fluidOutcomeValveLineEdit_textEdited(const QString &arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
