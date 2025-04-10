#include "SensorChart.h"
#include <QVBoxLayout>
#include <QTimer>
#include <QEvent>
#include <QWheelEvent>

SensorChart::SensorChart(const QString &title, double minY, double maxY, QWidget *parent)
    : QWidget(parent), dataCount(0), userInteracting(false) {

    series = new QLineSeries();

    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(title);
    chart->legend()->hide();

    axisX = new QValueAxis();
    axisX->setRange(0, 100);
    axisX->setLabelFormat("%d");
    axisX->setTitleText("Pomiar");

    axisY = new QValueAxis();
    axisY->setRange(minY, maxY);
    axisY->setTitleText(title);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
    setLayout(layout);

    autoScrollTimer = new QTimer(this);
    autoScrollTimer->setInterval(3000);
    autoScrollTimer->setSingleShot(true);
    connect(autoScrollTimer, &QTimer::timeout, this, [=]() {
        userInteracting = false;
    });

    chartView->viewport()->installEventFilter(this);
}

void SensorChart::addDataPoint(double value) {
    auto xySeries = qobject_cast<QXYSeries*>(series);
    if (!xySeries) return;

    dataCount++;
    xySeries->append(dataCount, value);

    const int maxPoints = 1000;
    if (xySeries->count() > maxPoints) {
        QList<QPointF> points = xySeries->points();
        points.removeFirst();
        xySeries->replace(points);
    }

    if (!userInteracting) {
        axisX->setMax(dataCount);
        axisX->setMin(qMax(0, dataCount - 100));
    }

    if (value > axisY->max()) axisY->setMax(value + 5);
    if (value < axisY->min()) axisY->setMin(value - 5);
}

void SensorChart::clearChart() {
    auto xySeries = qobject_cast<QXYSeries*>(series);
    if (xySeries) {
        xySeries->clear();
    }
    dataCount = 0;
}

QChartView* SensorChart::getChartView() const {
    return chartView;
}

QAbstractSeries* SensorChart::getSeries() const {
    return series;
}

QValueAxis* SensorChart::getAxisY() const {
    return axisY;
}

void SensorChart::changeType(ChartType newType) {
    QList<QPointF> oldPoints;
    if (auto line = qobject_cast<QLineSeries*>(series)) {
        oldPoints = line->points();
    } else if (auto scatter = qobject_cast<QScatterSeries*>(series)) {
        oldPoints = scatter->points();
    }

    chart->removeSeries(series);
    delete series;

    switch (newType) {
    case ChartType::Line:
        series = new QLineSeries();
        break;
    case ChartType::Scatter:
        series = new QScatterSeries();
        break;
    }

    for (const QPointF &point : oldPoints) {
        static_cast<QXYSeries*>(series)->append(point);
    }

    chart->addSeries(series);
    series->attachAxis(axisX);
    series->attachAxis(axisY);
}

void SensorChart::setSeriesColor(const QColor &color) {
    auto xy = qobject_cast<QXYSeries*>(series);
    if (xy) {
        QPen pen = xy->pen();
        pen.setColor(color);
        xy->setPen(pen);
    }
}

void SensorChart::setSeriesStyle(Qt::PenStyle style, int width) {
    auto xy = qobject_cast<QXYSeries*>(series);
    if (xy) {
        QPen pen = xy->pen();
        pen.setStyle(style);
        pen.setWidth(width);
        xy->setPen(pen);
    }
}

bool SensorChart::eventFilter(QObject *obj, QEvent *event) {
    if (obj == chartView->viewport()) {
        if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::Wheel) {
            userInteracting = true;
            autoScrollTimer->start();
        }
    }
    return QWidget::eventFilter(obj, event);
}

void SensorChart::setAxisRange(double minY, double maxY) {
    axisY->setRange(minY, maxY);
}

void SensorChart::applyEditorSettings(const QColor &color, Qt::PenStyle style, int width, double minY, double maxY, ChartType type) {
    setSeriesColor(color);
    setSeriesStyle(style, width);
    setAxisRange(minY, maxY);
    changeType(type);
}
