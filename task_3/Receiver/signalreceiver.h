#ifndef SIGNALRECEIVER_H
#define SIGNALRECEIVER_H

#include "udpclient.h"
#include "painterwidget.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QElapsedTimer>
#include <QGroupBox>
#include <QDial>
#include <QTimer>
#include <QCheckBox>

#include <cmath>
#include <deque>
#include <utility>


class SignalReceiver : public QWidget
{
    Q_OBJECT

public:
        SignalReceiver(QWidget *parent = nullptr);
protected:
        int time_scale_factor = 1;
        int value_scale_factor = 1;
        double time_price_of_unit;
        double value_price_of_unit;
        const int64_t history_duration = 10000; // 10 seconds

        int max_value = 0;
        int value_auto_scale_time = 1000; // 1 s
        QCheckBox* value_auto_scale_checkbox;
        QTimer* value_auto_scale_timer;

        UdpClient* client;
        QLabel* value_lbl;
        QLabel* time_lbl;
        QLabel* values_number_lbl;
        QElapsedTimer* main_time;
        std::deque<std::pair<int64_t, int>> dq_values;  // <time, value>

        QLabel* time_scale_factor_lbl;
        QLabel* value_scale_factor_lbl;
        QLabel* t_price_of_unit_lbl;
        QLabel* v_price_of_unit_lbl;
        QDial* time_scale_dial;
        QDial* value_scale_dial;
        PainterWidget* screen;

        void init_info_lbl(QHBoxLayout* h_layout);
        void init_screen(PainterWidget* screen);
        void init_scales(QHBoxLayout* scale_layout);
        void init_time_scale(QGroupBox* time_scale_gb);
        void init_value_scale(QGroupBox* value_scale_gb);
        void update_q_values();
        void find_max_value();
public slots:
        void get_value(int value);
        void set_time_scale_factor(int value);
        void set_value_scale_factor(int value);
        void calc_value_auto_scale_factor();
        void check_value_auto_scale_checkbox(int status);
};
#endif // SIGNALRECEIVER_H
