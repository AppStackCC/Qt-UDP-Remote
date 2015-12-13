#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QKeyEvent"
#include <QDebug>
#include <QUdpSocket>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFocus();
    key_front = 0;
    key_back = 0;
    key_left = 0;
    key_right =0;
    udp_enable = 0;

    socket = new QUdpSocket(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::UpdateCommand()
{
    if (!udp_enable) return;

    QString css_press = "background-color:red";
    QString css_release = "";

    // Key Front
    if (key_front)
        ui->btnFront->setStyleSheet(css_press);
    else
        ui->btnFront->setStyleSheet(css_release);

    // Key Back
    if (key_back)
        ui->btnBack->setStyleSheet(css_press);
    else
        ui->btnBack->setStyleSheet(css_release);

    // Key Left
    if (key_left)
        ui->btnLeft->setStyleSheet(css_press);
    else
        ui->btnLeft->setStyleSheet(css_release);

    // Key Right
    if (key_right)
        ui->btnRight->setStyleSheet(css_press);
    else
        ui->btnRight->setStyleSheet(css_release);

    udp_command = (key_front << 3) | (key_back << 2) | (key_left << 1) | key_right;

    qDebug("Command Update[%d] -- %d : %d : %d : %d",udp_command,key_front,key_back,key_left,key_right);

    this->SendByte(udp_command);
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up : key_front = 1; break;
        case Qt::Key_Down : key_back = 1; break;
        case Qt::Key_Left : key_left = 1; break;
        case Qt::Key_Right :key_right = 1; break;
    }
    event->accept();
    UpdateCommand();
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up :key_front = 0; break;
        case Qt::Key_Down : key_back = 0; break;
        case Qt::Key_Left : key_left= 0; break;
        case Qt::Key_Right :key_right = 0; break;
    }
    //event->accept();
    UpdateCommand();
}

void MainWindow::on_btnFront_pressed()
{
    key_front = 1;
    UpdateCommand();
}

void MainWindow::on_btnFront_released()
{
    key_front = 0;
    UpdateCommand();
}

void MainWindow::on_btnBack_pressed()
{
    key_back = 1;
    UpdateCommand();
}

void MainWindow::on_btnBack_released()
{
    key_back = 0;
    UpdateCommand();
}

void MainWindow::on_btnLeft_pressed()
{
    key_left = 1;
    UpdateCommand();
}

void MainWindow::on_btnLeft_released()
{
    key_left = 0;
    UpdateCommand();
}

void MainWindow::on_btnRight_pressed()
{
    key_right = 1;
    UpdateCommand();
}

void MainWindow::on_btnRight_released()
{
    key_right = 0;
    UpdateCommand();
}

void MainWindow::on_btnUpdateIP_clicked()
{
    if (ui->btnUpdateIP->text() == "Edit")
    {
        ui->btnUpdateIP->setText("Save");
        ui->txtIP->setEnabled(true);
        ui->txtPort->setEnabled(true);
        udp_enable = 0;
    }
    else
    {
        ui->btnUpdateIP->setText("Edit");
        ui->txtIP->setEnabled(false);
        ui->txtPort->setEnabled(false);

        this->UdpIP = QHostAddress(ui->txtIP->text());
        this->UdpPort = ui->txtPort->text().toInt();
        this->setFocus();
        udp_enable = 1;
    }

}

void MainWindow::SendByte(uint8_t data)
{
    QByteArray buffer;
    buffer.append(data);

    this->Send(buffer);
}

void MainWindow::Send(QByteArray data)
{
    socket->writeDatagram(data, UdpIP , UdpPort);
}
