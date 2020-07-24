#include "signalreceiver.h"

SignalReceiver::SignalReceiver(QWidget *parent) : QWidget(parent){
        setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint
                                  | Qt::WindowCloseButtonHint);
        client = new UdpClient;
        connect(client, SIGNAL(value_received(int)),
                this, SLOT(get_value(int)));

        main_time = new QElapsedTimer;
        main_time->start();

        QHBoxLayout* h_layout = new QHBoxLayout;
        init_info_lbl(h_layout);

        screen = new PainterWidget;
        init_screen(screen);

        QHBoxLayout* scale_layout = new QHBoxLayout;
        init_scales(scale_layout);

        QVBoxLayout* v_layout = new QVBoxLayout;
        v_layout->addLayout(h_layout, 0);
        v_layout->addWidget(screen, 1);
        v_layout->addLayout(scale_layout, 0);

        setLayout(v_layout);
}

void SignalReceiver::init_info_lbl(QHBoxLayout* h_layout){
        QLabel* name_value_lbl = new QLabel("Value: ");
        value_lbl = new QLabel("No signal");

        QLabel* name_time_lbl = new QLabel("Time: ");
        time_lbl = new QLabel("0");
        QLabel* name_values_number_lbl = new QLabel("Values number: ");
        values_number_lbl = new QLabel("0");

        h_layout->addStretch(1);
        h_layout->addWidget(name_value_lbl);
        h_layout->addWidget(value_lbl);
        h_layout->addWidget(name_time_lbl);
        h_layout->addWidget(time_lbl);
        h_layout->addWidget(name_values_number_lbl);
        h_layout->addWidget(values_number_lbl);
        h_layout->setContentsMargins(5, 5, 5, 5);
}


void SignalReceiver::init_screen(PainterWidget* screen){
        screen->set_dq_values(&dq_values);
        screen->set_main_time(main_time);
        screen->set_time_scale_factor(&time_scale_factor);
        screen->set_value_scale_factor(&value_scale_factor);
        time_price_of_unit = 10 * screen->width() / 20.0;
        value_price_of_unit = screen->height() / 25.0;
}

void SignalReceiver::init_scales(QHBoxLayout* scale_layout){
        QGroupBox* time_scale_gb = new QGroupBox("Time scale");
        init_time_scale(time_scale_gb);

        QGroupBox* value_scale_gb = new QGroupBox("Value scale");
        init_value_scale(value_scale_gb);

        scale_layout->addStretch(1);
        scale_layout->addWidget(time_scale_gb);
        scale_layout->addStretch(1);
        scale_layout->addWidget(value_scale_gb);
        scale_layout->addStretch(1);
}

void SignalReceiver::init_time_scale(QGroupBox* time_scale_gb){
        QLabel* t_caption_p_of_u_lbl = new QLabel ("Price of unit (ms): ");
        t_price_of_unit_lbl = new QLabel (QString::number(time_price_of_unit));
        QHBoxLayout* time_p_of_u_layout = new QHBoxLayout;
        time_p_of_u_layout->addWidget(t_caption_p_of_u_lbl);
        time_p_of_u_layout->addWidget(t_price_of_unit_lbl);
        time_p_of_u_layout->addStretch(1);

        QDial* time_scale_dial = new QDial;
        time_scale_dial->setRange(1, 10);
        time_scale_dial->setValue(time_scale_factor);
        time_scale_dial->setNotchTarget(1);
        time_scale_dial->setNotchesVisible(true);

        QLabel* time_scale_factor_caption_lbl = new QLabel("Time scale factor: ");
        time_scale_factor_lbl = new QLabel(QString::number(time_scale_factor));
        connect(time_scale_dial, SIGNAL(valueChanged(int)),
                this, SLOT(set_time_scale_factor(int)));
        QHBoxLayout* time_scale_factor_layout = new QHBoxLayout;
        time_scale_factor_layout->addWidget(time_scale_factor_caption_lbl);
        time_scale_factor_layout->addWidget(time_scale_factor_lbl);
        time_scale_factor_layout->addStretch(1);

        QVBoxLayout* time_scale_layout = new QVBoxLayout;
        time_scale_layout->addLayout(time_p_of_u_layout);
        time_scale_layout->addWidget(time_scale_dial);
        time_scale_layout->addLayout(time_scale_factor_layout);

        time_scale_gb->setLayout(time_scale_layout);
}

void SignalReceiver::init_value_scale(QGroupBox* value_scale_gb){

        QLabel* v_caption_p_of_u_lbl = new QLabel ("Price of unit: ");
        v_price_of_unit_lbl = new QLabel (QString::number(value_price_of_unit));
        QHBoxLayout* value_p_of_u_layout = new QHBoxLayout;
        value_p_of_u_layout->addWidget(v_caption_p_of_u_lbl);
        value_p_of_u_layout->addWidget(v_price_of_unit_lbl);
        value_p_of_u_layout->addStretch(1);

        QDial* value_scale_dial = new QDial;
        value_scale_dial->setRange(1, 10);
        value_scale_dial->setValue(value_scale_factor);
        value_scale_dial->setNotchTarget(1);
        value_scale_dial->setNotchesVisible(true);

        QLabel* value_scale_factor_caption_lbl = new QLabel("Value scale factor: ");
        value_scale_factor_lbl = new QLabel(QString::number(value_scale_factor));
        connect(value_scale_dial, SIGNAL(valueChanged(int)),
                this, SLOT(set_value_scale_factor(int)));
        QHBoxLayout* value_scale_factor_layout = new QHBoxLayout;
        value_scale_factor_layout->addWidget(value_scale_factor_caption_lbl);
        value_scale_factor_layout->addWidget(value_scale_factor_lbl);
        value_scale_factor_layout->addStretch(1);

        QVBoxLayout* value_scale_layout = new QVBoxLayout;
        value_scale_layout->addLayout(value_p_of_u_layout);
        value_scale_layout->addWidget(value_scale_dial);
        value_scale_layout->addLayout(value_scale_factor_layout);

        value_scale_gb->setLayout(value_scale_layout);
}

void SignalReceiver::get_value(int value){
        update_q_values();
        value_lbl->setNum(value);
        time_lbl->setText(QString::number(main_time->elapsed()));
        dq_values.push_back({main_time->elapsed(), value});
        values_number_lbl->setNum((int)dq_values.size());
}


void SignalReceiver::update_q_values(){
        int64_t border_time = main_time->elapsed() - history_duration;
        while (!dq_values.empty() && border_time > dq_values.front().first){
                dq_values.pop_front();
        }
}

void SignalReceiver::set_time_scale_factor(int value){
        time_scale_factor_lbl->setNum(value);
        time_scale_factor = value;
        time_price_of_unit = (10 * screen->width() / 20.0) / value;
        time_price_of_unit = std::round(time_price_of_unit * 100) / 100;
        t_price_of_unit_lbl->setNum(time_price_of_unit);
}

void SignalReceiver::set_value_scale_factor(int value){
        value_scale_factor_lbl->setNum(value);
        value_scale_factor = value;
        value_price_of_unit = (screen->height() / 25.0) / value;
        value_price_of_unit = std::round(value_price_of_unit * 100) / 100;
        v_price_of_unit_lbl->setNum(value_price_of_unit);
}





