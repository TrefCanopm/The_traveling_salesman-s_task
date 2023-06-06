#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <cmath>

struct Node
{
    int x,y;
};

int Peaks_Counter, increase,xCenter,yCenter,minS,len,s;
int draw = 0;
double deg=360;
int ways[9][9];
bool *was;
int *way, *minway;
Node *node;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    QPalette palette;
    this -> setPalette(palette);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Hide_Matrix(){
    QString temp;
    for (int i = 1; i<10; i++)
    {
        temp = "clh" + QString::number(i);
        this -> findChild<QWidget*>(temp) -> hide();
    }

   for (int i = 1; i < 10; i++)
   {
        temp = "clv" + QString::number(i);
        this -> findChild<QWidget*>(temp) -> hide();

        temp = "d" + QString::number(i);
        this -> findChild<QWidget*>(temp) -> hide();

        for (int e = i + 1; e < 10; e++)
        {
            temp = "p" + QString::number(i) + QString::number(e);
            this -> findChild<QWidget*>(temp) -> hide();
        }
    }

   for (int i = 9; i > 1; i--)
   {
        for (int e = i - 1; e > 0; e--)
        {
            temp = "p" + QString::number(i) + QString::number(e);
            this -> findChild<QWidget*>(temp) -> hide();
        }
   }
}

void MainWindow::Show_Matrix()
{
    QString temp;

    for (int i = 1; i < Peaks_Counter + 1; i++){
        temp = "clh" + QString::number(i);
        this -> findChild<QWidget*>(temp) -> show();
    }

   for (int i = 1; i < Peaks_Counter + 1; i++)
   {
        temp = "clv" + QString::number(i);
        this -> findChild<QWidget*>(temp) -> show();

        temp = "d" + QString::number(i);
        this -> findChild<QWidget*>(temp) -> show();

        for (int e = i + 1; e < Peaks_Counter + 1; e++)
        {
            temp="p" + QString::number(i) + QString::number(e);
            this -> findChild<QWidget*>(temp) -> show();
        }
   }

   for (int i = Peaks_Counter; i > 1; i--)
   {
       for (int e = i - 1; e > 0; e--)
       {
           temp = "p" + QString::number(i) + QString::number(e);
           this -> findChild<QWidget*>(temp) -> show();
       }
   }
}

void MainWindow::on_createPeaks_clicked()
{
        Peaks_Counter=ui -> CountLabel -> text().toInt();
        Show_Matrix();
        node = new Node[Peaks_Counter];

        xCenter = 500;
        yCenter = 200;

        draw = 1;
        this -> repaint();
}


void MainWindow::on_createRibs_clicked()
{
    QString searcher, buffer;

    for (int i = 0;i < Peaks_Counter;i++)
    {
        for (int e = 0;e < Peaks_Counter;e++)
        {
            if (i == e)
            {
                buffer = "0";
            }
            else
            {
            searcher="p"+QString::number(i+1) + QString::number(e+1);
            buffer=this->findChild<QLineEdit*>(searcher)->text();
            }
            ways[i][e] = buffer.toInt();
        }
    }
    draw = 2;
    this -> repaint();
}


void MainWindow::on_Answer_clicked()
{
    QString buffer;
    bool notway = 0;

    len = 0;    s = 0;    minS = 10000;

    was = new bool [Peaks_Counter];
    way = new int [Peaks_Counter];
    minway = new int [Peaks_Counter];

    for (int i = 0; i < Peaks_Counter; i++)
    {
        minway[i] = -1; way[i] = -1;
    }

    for (int i = 0; i < Peaks_Counter; i++)
    {
        Search(0,i);
    }

    for (int i = 0; i < Peaks_Counter; i++)
    {
        if (minway[i] == -1)
        {
            notway = 1;
        }
    }

    if (notway || minS == 9999)
    {
        ui->Answer_label->setText("Нельзя решить задачу");
    }
    else
    {
    buffer = "Кратчайший путь:\n" + QString::number(minway[0] + 1);

    for (int i = 1 ;i < Peaks_Counter; i++)
        {buffer += "->" + QString::number(minway[i] + 1);}

    buffer += "->" + QString::number(minway[0] + 1);
    buffer += "\nДлина пути: " + QString::number(minS);
    draw = 3;
    this -> repaint();
    ui->Answer_label->setText(buffer);
    }
}


void MainWindow::paintEvent(QPaintEvent *)
{
    if (draw)
    {
        int indent;
        increase = 360/Peaks_Counter;
        deg = 0;
        QPainter paint;
        QPen pen;
        QBrush brush;
        QString str;
        QFont font;
        pen.setColor(Qt::red);
        pen.setWidth(2);
        pen.setStyle(Qt::SolidLine);
        font.setPointSize(16);

        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::yellow);
        paint.begin(this);
        paint.setPen(pen);
        paint.setFont(font);
        paint.setBrush(brush);
        for (int i = 0;i < Peaks_Counter; i++)
            {
                indent = -10;
                if (deg > 180) indent = 40;
                str = QString::number(i + 1);
                node[i].x= xCenter + (150 * cos(deg / 57));
                node[i].y= yCenter+(150 * -sin(deg / 57));
                paint.drawEllipse(node[i].x, node[i].y, 40, 40);
                pen.setColor(Qt::blue);
                paint.setPen(pen);
                paint.drawText(node[i].x + 40, node[i].y + indent,str);
                pen.setColor(Qt::white);
                paint.setPen(pen);
                deg += increase;
            }
        if (draw > 1)
        {
            for (int i = 0; i < Peaks_Counter; i++)
            {
                for (int e = 0; e < Peaks_Counter; e++)
                {
                    if (ways[i][e] < 1000 && ways[i][e] > 0)
                    {
                        pen.setStyle(Qt::SolidLine);
                        pen.setWidth(2);
                        paint.setPen(pen);
                        paint.drawLine(node[i].x + 20, node[i].y + 20, node[e].x + 20, node[e].y + 20);
                    }
                }
            }
        }
        paint.end();
    }
}

void MainWindow::Search(int l, int i)
{
    len += l;
    was[i] = 1;
    bool b = 0;
    way[s] = i;
    s++;
    for (int e = 0; e < Peaks_Counter; e++)
    {
        if (!was[e])
        {
            if (ways[i][e]) Search(ways[i][e], e);
            b = 1;
        }
    }
    if(!b)
    {
        bool minus = 0;
        for (int k = 0; k < Peaks_Counter; k++) if (way[k] == -1) minus = 1;
        if (!minus&& len < minS)
        {
            minS = len;
            for (int z = 0; z < Peaks_Counter; z++)
            {
                minway[z] = way[z];
            }
        }
    }
    len -= l;
    s--;
    was[i] = 0;
    way[s] = -1;
}
