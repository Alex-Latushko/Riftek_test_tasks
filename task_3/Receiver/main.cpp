#include "signalreceiver.h"
#include "udpclient.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SignalReceiver receiver;
    receiver.setFixedSize(1020, 500);
    receiver.move(450, 10);
    receiver.show();

    return a.exec();
}
