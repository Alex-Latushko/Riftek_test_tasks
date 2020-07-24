#include "signalsource.h"
#include "UdpServer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SignalSource source;
    source.setFixedSize(350, 450);
    source.move(1510, 10);
    source.show();

    return a.exec();
}
