#include "UdpServer.h"

UdpServer::UdpServer(QWidget *parent) : QWidget(parent) {
    m_pudp = new QUdpSocket(this);
}

void UdpServer::slotSendDatagram(int value){
   QByteArray baDatagram;
   QDataStream out(&baDatagram, QIODevice::WriteOnly);
   out.setVersion(QDataStream::Qt_5_3);
   out << value;
   m_pudp->writeDatagram(baDatagram, QHostAddress::LocalHost, 2424);
}
