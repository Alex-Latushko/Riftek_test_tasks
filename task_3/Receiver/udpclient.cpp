#include "udpclient.h"

UdpClient::UdpClient(QWidget *parent) : QWidget(parent)
{
        m_pudp = new QUdpSocket(this);
        m_pudp->bind(2424);
        connect(m_pudp, SIGNAL(readyRead()), SLOT(slotProcessDatagrams()));
}

void UdpClient::slotProcessDatagrams(){
        QByteArray baDatagram;
        do {
                baDatagram.resize(m_pudp->pendingDatagramSize());
                m_pudp->readDatagram(baDatagram.data(), baDatagram.size());
        } while (m_pudp->hasPendingDatagrams());

        int value;
        QDataStream in(&baDatagram, QIODevice::ReadOnly);
        in.setVersion(QDataStream::Qt_5_3);
        in >> value;
        emit(value_received(value));
}

