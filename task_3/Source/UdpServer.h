#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTimer>
#include <QUdpSocket>

class UdpServer : public QWidget
{
    Q_OBJECT
private:
        QUdpSocket* m_pudp;
public:
        UdpServer(QWidget *parent = nullptr);
private slots:
        void slotSendDatagram(int value);
};
#endif // MAINWINDOW_H
