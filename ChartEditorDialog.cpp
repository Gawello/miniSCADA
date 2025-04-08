#include "ChartEditorDialog.h"
#include "qlabel.h"
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QValueAxis>
#include <QColorDialog>

//using namespace QtCharts;

ChartEditorDialog::ChartEditorDialog(const QStringList &chartNames, QWidget *parent)
    : QDialog(parent) {
    setWindowTitle("Edytor wykresów");
    resize(600, 400);

    chartSelector = new QComboBox(this);
    chartSelector->addItems(chartNames);

    typeSelector = new QComboBox(this);
    typeSelector->addItems({"Line", "Scatter"});

    colorButton = new QPushButton("Wybierz kolor linii", this);
    connect(colorButton, &QPushButton::clicked, this, &ChartEditorDialog::chooseColor);

    minYSpin = new QDoubleSpinBox(this);
    maxYSpin = new QDoubleSpinBox(this);
    minYSpin->setRange(-1000, 1000);
    maxYSpin->setRange(-1000, 1000);
    minYSpin->setValue(0);
    maxYSpin->setValue(100);

    previewView = new QChartView(this);
    previewView->setMinimumHeight(200);

    QPushButton *applyBtn = new QPushButton("Zastosuj", this);
    connect(applyBtn, &QPushButton::clicked, this, &ChartEditorDialog::applyChanges);

    connect(chartSelector, &QComboBox::currentTextChanged,
            this, &ChartEditorDialog::previewChart);
    connect(typeSelector, &QComboBox::currentTextChanged, this, &ChartEditorDialog::updatePreview);
    connect(minYSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &ChartEditorDialog::updatePreview);
    connect(maxYSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &ChartEditorDialog::updatePreview);
    connect(lineStyleSelector, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ChartEditorDialog::updatePreview);
    connect(lineWidthSpin, QOverload<int>::of(&QSpinBox::valueChanged), this, &ChartEditorDialog::updatePreview);

    // Layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(new QLabel("Wybierz wykres:"));
    mainLayout->addWidget(chartSelector);
    mainLayout->addWidget(previewView);

    QHBoxLayout *formLayout = new QHBoxLayout;
    formLayout->addWidget(new QLabel("Typ wykresu:"));
    formLayout->addWidget(typeSelector);
    formLayout->addWidget(colorButton);
    formLayout->addWidget(new QLabel("Min Y:"));
    formLayout->addWidget(minYSpin);
    formLayout->addWidget(new QLabel("Max Y:"));
    formLayout->addWidget(maxYSpin);
    mainLayout->addLayout(formLayout);

    lineStyleSelector = new QComboBox(this);
    lineStyleSelector->addItem("Solid", static_cast<int>(Qt::SolidLine));
    lineStyleSelector->addItem("Dash", static_cast<int>(Qt::DashLine));
    lineStyleSelector->addItem("Dot", static_cast<int>(Qt::DotLine));
    lineStyleSelector->addItem("Dash Dot", static_cast<int>(Qt::DashDotLine));
    lineStyleSelector->addItem("Dash Dot Dot", static_cast<int>(Qt::DashDotDotLine));

    QPushButton *resetBtn = new QPushButton("Resetuj do domyślnych", this);
    connect(resetBtn, &QPushButton::clicked, this, [=]() {
        typeSelector->setCurrentIndex(0);
        selectedColor = Qt::blue;
        lineStyleSelector->setCurrentIndex(0);
        lineWidthSpin->setValue(2);
        minYSpin->setValue(0);
        maxYSpin->setValue(100);
        updatePreview();
    });

    lineWidthSpin = new QSpinBox(this);
    lineWidthSpin->setRange(1, 10);
    lineWidthSpin->setValue(2);


    mainLayout->addWidget(applyBtn);
    setLayout(mainLayout);

    previewChart(chartSelector->currentText());
}

void ChartEditorDialog::previewChart(const QString &chartName) {
    currentChart = chartName;
    updatePreview();
}

void ChartEditorDialog::chooseColor() {
    QColor color = QColorDialog::getColor(selectedColor, this, "Wybierz kolor linii");
    if (color.isValid()) {
        selectedColor = color;
    }
    updatePreview();
}

void ChartEditorDialog::updatePreview() {
    QChart *chart = new QChart();
    chart->setTitle(currentChart);

    QXYSeries *series = nullptr;
    if (typeSelector->currentText() == "Line") {
        series = new QLineSeries();
    } else {
        series = new QScatterSeries();
    }

    series->setColor(selectedColor);
    for (int i = 0; i < 20; ++i) {
        series->append(i, qSin(i / 3.0) * 10 + 50); // losowe dane demo
    }

    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(0, 20);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(minYSpin->value(), maxYSpin->value());

    chart->addSeries(series);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    int styleIndex = lineStyleSelector->currentIndex();
    Qt::PenStyle style = static_cast<Qt::PenStyle>(
        lineStyleSelector->itemData(styleIndex).toInt());
    int width = lineWidthSpin->value();

    QPen pen = series->pen();
    pen.setColor(selectedColor);
    pen.setStyle(style);
    pen.setWidth(width);
    series->setPen(pen);


    previewView->setChart(chart);
}

void ChartEditorDialog::applyChanges() {
    int styleIndex = lineStyleSelector->currentIndex();
    Qt::PenStyle style = static_cast<Qt::PenStyle>(lineStyleSelector->itemData(styleIndex).toInt());
    int width = lineWidthSpin->value();

    emit chartUpdated(currentChart,
                      typeSelector->currentText(),
                      selectedColor,
                      style,
                      width,
                      minYSpin->value(),
                      maxYSpin->value());

    accept(); // zamyka okno
}
