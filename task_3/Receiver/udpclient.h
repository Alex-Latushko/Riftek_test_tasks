#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QUdpSocket>
#include <QWidget>

class UdpClient : public QWidget
{
    Q_OBJECT
private:
        QUdpSocket* m_pudp;
public:
        UdpClient(QWidget *parent = nullptr);
private slots:
        void slotProcessDatagrams();
signals:
        void value_received(int value);
};
#endif // UDPCLIENT_H
