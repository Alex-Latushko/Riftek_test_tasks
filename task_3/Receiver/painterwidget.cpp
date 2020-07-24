#include "painterwidget.h"

PainterWidget::PainterWidget(QWidget *parent) : QWidget(parent)
{
        painter = new QPainter();
        init_form();
        init_screen_timer();
}

void PainterWidget::init_form(){
        QPalette pal = palette();
        pal.setColor(QPalette::Background, Qt::black);
        setAutoFillBackground(true);
        setPalette(pal);
        setFixedSize(1000, 250);
}
void PainterWidget::init_screen_timer(){
        screen_timer = new QTimer;
        screen_timer->setInterval(40);
        screen_timer->start();

        connect(screen_timer, SIGNAL(timeout()),
                this, SLOT(update()));
}

void PainterWidget::paintEvent(QPaintEvent*){
        painter->begin(this);
        paint_grid();

        if (dq_values->empty()){  // if deq is empty we cannot paint line
            painter->end();
            return;
        }

        paint_line();
        painter->end();
}

void PainterWidget::set_dq_values(std::deque<std::pair<int64_t, int>>* dq_v){
        dq_values = dq_v;
}
void PainterWidget::set_main_time(QElapsedTimer* m_t){
        main_time = m_t;
}

void PainterWidget::set_time_scale_factor(int* x){
        p_time_scale_factor = x;
}
void PainterWidget::set_value_scale_factor(int* x){
        p_value_scale_factor = x;
}

void PainterWidget::paint_grid(){
        painter->setPen(QPen(Qt::gray, 1, Qt::DotLine));
        for (int i = 0; i < 20; i++){    // vertical lines
                if (i % 5 == 0){ painter->setPen(QPen(Qt::gray, 1, Qt::DashDotLine)); }
                painter->drawLine(QPointF(i * width() / 20, 0),
                                  QPointF(i * width() / 20, height()));
                if (i % 5 == 0){ painter->setPen(QPen(Qt::gray, 1, Qt::DotLine)); }
        }

        int zero_level = height() / 2;
        for (int i = -12; i < 23; i++){  // horizontal lines
                if (i % 5 == 0){ painter->setPen(QPen(Qt::gray, 1, Qt::DashDotLine)); }
                painter->drawLine(QPointF(0, zero_level + i * height() / 25),
                                  QPointF(width(),zero_level + i * height() / 25));
                if (i % 5 == 0){ painter->setPen(QPen(Qt::gray, 1, Qt::DotLine)); }
        }
        painter->setPen(QPen(Qt::gray, 1, Qt::SolidLine));  // main lines
        painter->drawLine(QPointF(width() / 2, 0),
                          QPointF(width() / 2, height()));
        painter->drawLine(QPointF(0, height() / 2),
                          QPointF(width(), height() / 2));
}

void PainterWidget::paint_line(){
        int64_t current_time = main_time->elapsed();
        painter->setPen(QPen(Qt::yellow, 1));
        int zero_level = height() / 2;
        zero_level = height() / 2;

        QPointF first_point;
        QPointF second_point;
        first_point = QPointF( *p_time_scale_factor * (current_time - dq_values->back().first) / 10,
                               zero_level - (*p_value_scale_factor * dq_values->back().second));
        for(auto p = dq_values->rbegin(); p != dq_values->rend(); p++){
                second_point = QPointF(*p_time_scale_factor * (current_time - p->first) / 10,
                                        zero_level - (*p_value_scale_factor * p->second));
                painter->drawLine(first_point, second_point);
                first_point = second_point;
        }
    }
