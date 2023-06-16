#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

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
    void createPeaks();

    void createRibs();

    void Answer();

    void HMatrix();

    void SMatrix();

    void Search(int l, int i);
private:
    Ui::MainWindow *ui;
protected:
    void paintEvent(QPaintEvent*) override;
};
#endif // MAINWINDOW_H
