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

#include <cmath>
#include <deque>
#include <utility>


class SignalReceiver : public QWidget
{
    Q_OBJECT

public:
        int time_scale_factor = 1;
        int value_scale_factor = 1;
        double time_price_of_unit;
        double value_price_of_unit;
        const int64_t history_duration = 10000; // 10 seconds

        UdpClient* client;
        QLabel* value_lbl;
        QLabel* time_lbl;
        QLabel* values_number_lbl;
        QElapsedTimer* main_time;
        std::deque<std::pair<int64_t, int>> dq_values;

        QLabel* time_scale_factor_lbl;
        QLabel* value_scale_factor_lbl;
        QLabel* v_price_of_unit_lbl;
        QLabel* t_price_of_unit_lbl;
        PainterWidget* screen;

        SignalReceiver(QWidget *parent = nullptr);
protected:
        void init_info_lbl(QHBoxLayout* h_layout);
        void init_screen(PainterWidget* screen);
        void init_scales(QHBoxLayout* scale_layout);
        void init_time_scale(QGroupBox* time_scale_gb);
        void init_value_scale(QGroupBox* value_scale_gb);
        void update_q_values();
public slots:
        void get_value(int value);
        void set_time_scale_factor(int value);
        void set_value_scale_factor(int value);
};
#endif // SIGNALRECEIVER_H
