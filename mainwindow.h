#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QUdpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


protected:
     void keyPressEvent(QKeyEvent *event);
     void keyReleaseEvent(QKeyEvent *event);

private slots:
    void on_btnFront_pressed();

    void on_btnFront_released();

    void on_btnBack_pressed();

    void on_btnBack_released();

    void on_btnLeft_pressed();

    void on_btnLeft_released();

    void on_btnRight_pressed();

    void on_btnRight_released();

    void on_btnUpdateIP_clicked();

private:
    Ui::MainWindow *ui;

    void Send(QByteArray data);
    void SendByte(uint8_t data);

    bool udp_enable;
    uint8_t udp_command;
    uint8_t key_front;
    uint8_t key_back;
    uint8_t key_left;
    uint8_t key_right;

    QUdpSocket *socket;
    QHostAddress UdpIP;
    quint16 UdpPort;

    void UpdateCommand();
};

#endif // MAINWINDOW_H
