#include "signalsource.h"

SignalSource::SignalSource(QWidget *parent) : QWidget(parent){
        std::random_device r_dev;
        random_engine.seed(r_dev());

        setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint
                                  | Qt::WindowCloseButtonHint);
        server = new UdpServer;
        connect(this, SIGNAL(signal_changed_value(int)),
                server, SLOT(slotSendDatagram(int)));

        init_main_timer();

        QGroupBox* value_gb = new QGroupBox("Send value");
        init_value_gb(value_gb);

        QGroupBox* dials_gb = new QGroupBox("Value settings");
        init_dials_gb(dials_gb);

        QGroupBox* interval_gb = new QGroupBox("Interval between values");
        init_interval_gb(interval_gb);

        QGroupBox* mode_gb = new QGroupBox("Mode");
        init_mode_gb(mode_gb);

        QVBoxLayout* v_layout = new QVBoxLayout;
        v_layout->addWidget(value_gb);
        v_layout->addWidget(dials_gb);
        v_layout->addWidget(interval_gb);
        v_layout->addWidget(mode_gb);

        setLayout(v_layout);
}


void SignalSource::init_value_gb(QGroupBox* value_gb){
        value_lbl = new QLabel;
        value_lbl->resize(20, 20);
        QHBoxLayout* value_layout = new QHBoxLayout;
        value_layout->addWidget(value_lbl);
        value_gb->setLayout(value_layout);
}

void SignalSource::init_main_timer(){
        main_timer = new QTimer(this);
        main_timer->setInterval(init_speed);
        main_timer->start();

        connect(main_timer, SIGNAL(timeout()),
                this, SLOT(slot_change_value()));
}

void SignalSource::init_dials_gb(QGroupBox* dials_gb){

        QLabel* bvalue_caption_lbl = new QLabel("Base Value");
        base_value_dial = new QDial;
        base_value_dial->setRange(-50, 50);
        base_value_dial->setValue(init_value);
        base_value_dial->setNotchTarget(5);
        base_value_dial->setNotchesVisible(true);
        bvalue_value_lbl = new QLabel(QString::number(base_value));
        QVBoxLayout* bvalue_layout = new QVBoxLayout;
        bvalue_layout->addWidget(bvalue_caption_lbl);
        bvalue_layout->addWidget(base_value_dial);
        bvalue_layout->addWidget(bvalue_value_lbl);
        connect(base_value_dial, SIGNAL(valueChanged(int)),
                this, SLOT(set_base_value(int)));

        QLabel* vvalue_caption_lbl = new QLabel("Random Value");
        varied_value_dial = new QDial;
        varied_value_dial->setRange(0, 100);
        varied_value_dial->setValue(50);
        varied_value_dial->setNotchTarget(5);
        varied_value_dial->setNotchesVisible(true);
        vvalue_value_lbl = new QLabel(QString::number(varied_value/100.0));
        QVBoxLayout* vvalue_layout = new QVBoxLayout;
        vvalue_layout->addWidget(vvalue_caption_lbl);
        vvalue_layout->addWidget(varied_value_dial);
        vvalue_layout->addWidget(vvalue_value_lbl);
        connect(varied_value_dial, SIGNAL(valueChanged(int)),
                this, SLOT(set_varied_value(int)));

        QHBoxLayout* h_dials_layout = new QHBoxLayout;
        h_dials_layout->addLayout(bvalue_layout);
        h_dials_layout->addLayout(vvalue_layout);

        dials_gb->setLayout(h_dials_layout);
}

void SignalSource::init_interval_gb(QGroupBox* interval_gb){
        speed_sld = new QSlider(Qt::Horizontal);
        speed_sld->setRange(1, 100);
        speed_sld->setPageStep(1);
        speed_sld->setValue(init_speed);
        speed_sld->setTickInterval(10);
        speed_sld->setTickPosition(QSlider::TicksBelow);
        connect(speed_sld, SIGNAL(valueChanged(int)),
                this, SLOT(set_speed(int)));

        QLabel* speed_lbl = new QLabel(QString::number(init_speed));
        connect(speed_sld, SIGNAL(valueChanged(int)),
                speed_lbl, SLOT(setNum(int)));

        QLabel* speed_units_lbl = new QLabel("ms");

        QHBoxLayout* speed_layout = new QHBoxLayout;
        speed_layout->addWidget(speed_sld);
        speed_layout->addWidget(speed_lbl);
        speed_layout->addWidget(speed_units_lbl);

        interval_gb->setLayout(speed_layout);
}

void SignalSource::init_mode_gb(QGroupBox* mode_gb){
        manual_mode_button = new QRadioButton("Manual mode");
        manual_mode_button->setChecked(true);
        sinus_mode_button = new QRadioButton("Sinus mode");
        meander_mode_button = new QRadioButton("Meander mode");
        ramp_mode_button = new QRadioButton("Ramp mode");

        QGridLayout* mode_layout = new QGridLayout;
        mode_layout->addWidget(manual_mode_button, 0, 0);
        mode_layout->addWidget(sinus_mode_button, 0, 1);
        mode_layout->addWidget(meander_mode_button, 1, 0);
        mode_layout->addWidget(ramp_mode_button, 1, 1);
        mode_gb->setLayout(mode_layout);
}

void SignalSource::slot_change_value(){
        temp_value = 0;

        if (manual_mode_button->isChecked()){
            temp_value = base_value;

        } else if (sinus_mode_button->isChecked()){
            if (sinus_count > 360) {
                sinus_count = 0;
            }
            temp_value = base_value * std::sin( 2 * std::asin(1)  // 2 * std::asin(1) = pi
                                                  * sinus_count++
                                                  / 180.0);
        } else if (meander_mode_button->isChecked()){
            ++meander_count;
            if ((meander_count / 10) == 0){
                temp_value = base_value;
            } else if ((meander_count / 10) == 1){
                temp_value = -base_value;
            } else {
                meander_count =0 ;
            }
        } else if (ramp_mode_button->isChecked()){
            if (ramp_count < -abs_base_value ){
                ramp_count = abs_base_value;
            }
            temp_value = ramp_count--;
        }
        std::uniform_int_distribution<unsigned> u_distrib(0, base_value * varied_value / 100.0);
        temp_random = u_distrib(random_engine);
        sign = u_distrib(random_engine) % 2 ? 1 : -1;
        result_value = temp_value + sign * temp_random;

        value_lbl->setNum(result_value);
        emit(signal_changed_value(result_value));
}

void SignalSource::set_base_value(int value){
        base_value = value;
        abs_base_value = std::abs(base_value);
        bvalue_value_lbl->setNum(value);
}
void SignalSource::set_varied_value(int value){
        varied_value = value;
        vvalue_value_lbl->setNum(value/100.0);
}

void SignalSource::set_speed(int value){
        main_timer->setInterval(value);
}

