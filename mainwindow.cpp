#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsRectItem>
//#include <QGraphicsEllipseItem>
#include <QDebug>
#include <QColorDialog>
#include <QColor>

QColor pClr = QColor(Qt::red);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QGraphicsRectItem * room = new QGraphicsRectItem();
    room->setRect( QRectF( 0, 0, ui->spinBox->value(), ui->spinBox_2->value() ) );
    scene->addItem(room);
    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::on_pushButton_3_clicked()
{
    QString ct = ui->comboBox->currentText();
    int dw = ui->spinBox_4->value();
    int dot = ui->spinBox_3->value();
    int H = ui->spinBox_2->value();
    int W = ui->spinBox->value();

    QGraphicsRectItem * door = new QGraphicsRectItem();

    if (ct == "B")
    {
        door->setRect( QRectF( dot, 0, dw, 2 ) );
    }
    else if (ct == "D")
    {
       door->setRect( QRectF( dot, H, dw, 2 ) );
    }
    else if (ct == "A")
    {
        door->setRect( QRectF( 0, dot, 2, dw ) );
    }
    else if (ct == "C")
    {
        door->setRect( QRectF( W, dot, 2, dw ) );

    }
    door->setBrush( QBrush( Qt::cyan ) );
    scene->addItem(door);
}

void MainWindow::on_pushButton_4_clicked()
{
    int H = ui->spinBox_2->value();
    int W = ui->spinBox->value();
    int pw = ui->spinBox_5->value();

//    -----A
    int pot_a = ui->spinBox_6->value();
    int Apokw = H - pot_a;
    int AcelCnt = Apokw / pw;
    int Aostatok = Apokw - (AcelCnt * pw);
    qDebug() << "Wall A celyh polos: " << AcelCnt;
    qDebug() << "Wall A ostatok: " << Aostatok;

    for(int a = 0; a < AcelCnt + 1; a++)
    {
        QGraphicsRectItem * pa = new QGraphicsRectItem();
        pa->setRect( QRectF( 0, pot_a + a*pw, 4, 1 ) );
        pa->setPen(QPen(QColor(Qt::red)));
        points.append(pa);
    }

//    ----- D
    int pot_d = pw - Aostatok;
    int Dpokw = W - pot_d;
    int DcelCnt = Dpokw / pw;
    int Dostatok = Dpokw - (DcelCnt * pw);
    qDebug() << "Wall D celyh polos: " << DcelCnt;
    qDebug() << "Wall D ostatok: " << Dostatok;

    for(int d = 0; d < DcelCnt+1; d++)
    {
        QGraphicsRectItem * pd = new QGraphicsRectItem();
        pd->setRect( QRectF( pot_d + d*pw, H, 1, 4 ) );
        pd->setPen(QPen(QColor(Qt::red)));
        points.append(pd);
    }

//    ----- C
    int pot_c = pw - Dostatok;
    int Cpokw = H - pot_c;
    int CcelCnt = Cpokw / pw;
    int Costatok = Cpokw - (CcelCnt * pw);
    qDebug() << "Wall C celyh polos: " << CcelCnt;
    qDebug() << "Wall C ostatok: " << Costatok;

    for(int c = 0; c < CcelCnt+1; c++)
    {
        QGraphicsRectItem * pc = new QGraphicsRectItem();
        pc->setRect( QRectF( W, H - (pot_c + c*pw), 4, 1 ) );
        pc->setPen(QPen(QColor(Qt::red)));
        points.append(pc);
    }
//    ----- B
    int pot_b = pw - Costatok;
    int Bpokw = W - pot_b;
    int BcelCnt = Bpokw / pw;
    int Bostatok = Bpokw - (BcelCnt * pw);
    qDebug() << "Wall B celyh polos: " << BcelCnt;
    qDebug() << "Wall B ostatok: " << Bostatok;

    for(int b = 0; b < BcelCnt+1; b++)
    {
        QGraphicsRectItem * pb = new QGraphicsRectItem();
        pb->setRect( QRectF( W - (pot_b + b*pw), 0, 1, 4 ) );
        pb->setPen(QPen(QColor(Qt::red)));
        points.append(pb);
    }
    showPoints();
}

void MainWindow::on_pushButton_2_clicked()
{
    qDebug() << points.length();
    for (auto p : points)
    {
        scene->removeItem(p);
    }
    points.clear();
    qDebug() << points.length();
}

void MainWindow::showPoints()
{
    for (auto p : points)
    {
        scene->addItem(p);
    }
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    ui->pushButton_2->click();
    ui->pushButton_4->click();
}
