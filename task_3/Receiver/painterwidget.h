#ifndef PAINTERWIDGET_H
#define PAINTERWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QElapsedTimer>
#include <QTimer>

#include <deque>
#include <utility>

class PainterWidget : public QWidget
{
    Q_OBJECT
public:

    QTimer* screen_timer;
    QPainter* painter;
    const QElapsedTimer* main_time;
    const std::deque<std::pair<int64_t, int>>* dq_values;
    int* p_time_scale_factor;
    int* p_value_scale_factor;

    explicit PainterWidget(QWidget *parent = nullptr);

    void set_dq_values(std::deque<std::pair<int64_t, int>>* dq_v);
    void set_main_time(QElapsedTimer* m_t);
    void set_time_scale_factor(int* x);
    void set_value_scale_factor(int* x);

protected:
    void init_form();
    void init_screen_timer();
    void paint_grid();
    void paint_line();
    void virtual paintEvent(QPaintEvent*);
};

#endif // PAINTERWIDGET_H
