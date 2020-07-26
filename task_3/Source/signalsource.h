#ifndef SIGNALSOURCE_H
#define SIGNALSOURCE_H

#include "UdpServer.h"

#include <cmath>
#include <random>

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
        SignalSource(QWidget *parent = nullptr);
protected:
        const int init_speed = 1; // 1 ms
        const int init_value = 10;

        int result_value = 0;
        int base_value = init_value;
        int abs_base_value = std::abs(base_value);
        int varied_value = 50;
        int sign = 0;
        int temp_value = 0;
        int temp_random = 0;

        int meander_count = 0;
        int sinus_count = 0;
        int ramp_count = 50;

        std::mt19937 random_engine;

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
