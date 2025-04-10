#include "SensorChart.h"
#include <QVBoxLayout>

SensorChart::SensorChart(const QString &title, double minY, double maxY, QWidget *parent)
    : QWidget(parent), dataCount(0) {

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
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(chartView);
    setLayout(layout);

    chartView->setRubberBand(QChartView::HorizontalRubberBand); // przeciąganie
    chartView->setDragMode(QGraphicsView::ScrollHandDrag);       // scroll myszką
    chartView->setInteractive(true);                             // aktywacja interakcji

    connect(axisX, &QValueAxis::rangeChanged, this, [this](qreal min, qreal max) {
        if (!userXRangeActive) {
            qDebug() << "[SensorChart] Użytkownik przesunął wykres. Auto-scroll off.";
        }
        userXRangeActive = true;
        autoScrollResetTimer->start(3000); // 3 sekundy
    });
    autoScrollResetTimer = new QTimer(this);
    autoScrollResetTimer->setSingleShot(true); // tylko raz

    connect(autoScrollResetTimer, &QTimer::timeout, this, [this]() {
        userXRangeActive = false;
        qDebug() << "[SensorChart] Auto-scroll przywrócony automatycznie po 3 sekundach.";
    });


}

void SensorChart::resetAutoScroll() {
    userXRangeActive = false;
}


void SensorChart::addDataPoint(double value) {
    auto xySeries = qobject_cast<QXYSeries*>(series);
    if (!xySeries) return;

    dataCount++;

    // Dodaj nowy punkt
    xySeries->append(dataCount, value);

    // Usuń nadmiar danych
    const int maxPoints = 1000;
    if (xySeries->count() > maxPoints) {
        QList<QPointF> points = xySeries->points();
        points.removeFirst(); // usuwa najstarszy punkt
        xySeries->replace(points);
    }

    // Auto-przewijanie tylko jeśli użytkownik nie przesunął wykresu
    if (!userXRangeActive) {
        int visiblePoints = 100;
        axisX->setMax(dataCount);
        axisX->setMin(qMax(0, dataCount - visiblePoints));
    }

    // Dynamiczne skalowanie osi Y
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
    // 1. Skopiuj dane z obecnej serii
    QList<QPointF> oldPoints;
    if (auto line = qobject_cast<QLineSeries*>(series)) {
        oldPoints = line->points();
    } else if (auto scatter = qobject_cast<QScatterSeries*>(series)) {
        oldPoints = scatter->points();
    }

    // 2. Usuń starą serię z wykresu
    chart->removeSeries(series);
    delete series;

    // 3. Utwórz nową serię wybranego typu
    switch (newType) {
    case ChartType::Line:
        series = new QLineSeries();
        break;
    case ChartType::Scatter:
        series = new QScatterSeries();
        break;
    }

    // 4. Dodaj punkty do nowej serii
    for (const QPointF &point : oldPoints) {
        static_cast<QXYSeries*>(series)->append(point);
    }

    // 5. Podłącz serię do wykresu i osi
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

void SensorChart::enableAutoScroll() {
    userXRangeActive = false;
}
