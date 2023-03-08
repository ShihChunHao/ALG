#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ctime>
#include <cstdlib>
#include <QMessageBox>
#include <QChartView>
#include <QtCharts>
#include <QLineSeries>
#include <QPieSeries>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_8_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();

    void on_checkBox_clicked();

    void on_pushButton_9_clicked();

    void on_checkBox_2_clicked();

private:
    Ui::MainWindow *ui;
    QVector<int> v;
    QChartView *ChartView;
    int sort_check = 0;
    int dnp = 0;
};
#endif // MAINWINDOW_H
