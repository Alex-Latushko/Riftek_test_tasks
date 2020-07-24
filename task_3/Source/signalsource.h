#ifndef SIGNALSOURCE_H
#define SIGNALSOURCE_H

#include "UdpServer.h"

#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iostream>

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QDial>
#include <QTimer>
#include <QSlider>
#include <QGroupBox>
#include <QRadioButton>


class SignalSource : public QWidget
{
    Q_OBJECT

public:
        const int init_speed = 1; // 1 ms
        const int init_value = 10;
        int result_value = 0;
        int base_value = init_value;
        int varied_value = 51;

        int meander_count = 0;
        int sinus_count = 0;
        int ramp_count = 50;

        UdpServer* server;
        QLabel* value_lbl;
        QTimer* main_timer;

        QDial* base_value_dial;
        QLabel* bvalue_value_lbl;
        QDial* varied_value_dial;
        QLabel* vvalue_value_lbl;
        QSlider* speed_sld;

        QRadioButton* manual_mode_button;
        QRadioButton* sinus_mode_button;
        QRadioButton* meander_mode_button;
        QRadioButton* ramp_mode_button;


        SignalSource(QWidget *parent = nullptr);
protected:
        void init_value_gb(QGroupBox* value_gb);
        void init_main_timer();
        void init_dials_gb(QGroupBox* dials_gb);
        void init_interval_gb(QGroupBox* interval_gb);
        void init_mode_gb(QGroupBox* mode_gb);
public slots:
        void slot_change_value();
        void set_base_value(int value);
        void set_varied_value(int value);
        void set_speed(int value);
signals:
        void signal_changed_value(int send_value);
};
#endif // SIGNALSOURCE_H
