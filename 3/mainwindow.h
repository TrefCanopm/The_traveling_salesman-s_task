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
    void on_createPeaks_clicked();

    void on_createRibs_clicked();

    void on_Answer_clicked();

    void Hide_Matrix();

    void Show_Matrix();

    void Search(int l, int i);
private:
    Ui::MainWindow *ui;
protected:
    void paintEvent(QPaintEvent*) override;
};
#endif // MAINWINDOW_H
