#include "ChartEditorDialog.h"
#include "qpushbutton.h"
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QColorDialog>
#include <QDialogButtonBox>
#include <QtMath>


ChartEditorDialog::ChartEditorDialog(const QStringList &chartNames, QWidget *parent)
    : QDialog(parent) {
    setWindowTitle("Edytor wykresów");
    resize(600, 400);

    chartSelector = new QComboBox(this);
    chartSelector->addItems(chartNames);

    typeSelector = new QComboBox(this);
    typeSelector->addItems({"Line", "Scatter"});

    lineStyleSelector = new QComboBox(this);
    lineStyleSelector->addItem("Solid", static_cast<int>(Qt::SolidLine));
    lineStyleSelector->addItem("Dash", static_cast<int>(Qt::DashLine));
    lineStyleSelector->addItem("Dot", static_cast<int>(Qt::DotLine));
    lineStyleSelector->addItem("Dash Dot", static_cast<int>(Qt::DashDotLine));
    lineStyleSelector->addItem("Dash Dot Dot", static_cast<int>(Qt::DashDotDotLine));

    lineWidthSpin = new QSpinBox(this);
    lineWidthSpin->setRange(1, 10);
    lineWidthSpin->setValue(2);

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

    // Layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(new QLabel("Wybierz wykres:"));
    mainLayout->addWidget(chartSelector);
    mainLayout->addWidget(previewView);

    QHBoxLayout *options = new QHBoxLayout();
    options->addWidget(new QLabel("Typ:"));
    options->addWidget(typeSelector);
    options->addWidget(colorButton);
    options->addWidget(new QLabel("Styl linii:"));
    options->addWidget(lineStyleSelector);
    options->addWidget(new QLabel("Grubość:"));
    options->addWidget(lineWidthSpin);
    options->addWidget(new QLabel("Y min:"));
    options->addWidget(minYSpin);
    options->addWidget(new QLabel("Y max:"));
    options->addWidget(maxYSpin);
    mainLayout->addLayout(options);

    auto *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ChartEditorDialog::applyChanges);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ChartEditorDialog::reject);
    mainLayout->addWidget(buttonBox);

    connect(chartSelector, &QComboBox::currentTextChanged, this, &ChartEditorDialog::previewChart);
    connect(typeSelector, &QComboBox::currentTextChanged, this, &ChartEditorDialog::updatePreview);
    connect(lineStyleSelector, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ChartEditorDialog::updatePreview);
    connect(lineWidthSpin, QOverload<int>::of(&QSpinBox::valueChanged), this, &ChartEditorDialog::updatePreview);
    connect(minYSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &ChartEditorDialog::updatePreview);
    connect(maxYSpin, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &ChartEditorDialog::updatePreview);

    previewChart(chartSelector->currentText());
}

void ChartEditorDialog::previewChart(const QString &chartName) {
    currentChart = chartName;
    updatePreview();
}

void ChartEditorDialog::chooseColor() {
    QColor color = QColorDialog::getColor(selectedColor, this, "Wybierz kolor");
    if (color.isValid()) selectedColor = color;
    updatePreview();
}

void ChartEditorDialog::updatePreview() {
    QChart *chart = new QChart();
    chart->setTitle(currentChart);

    QXYSeries *series = nullptr;
    if (typeSelector->currentText() == "Line") {
        series = static_cast<QXYSeries*>(new QLineSeries());
    } else {
        series = static_cast<QXYSeries*>(new QScatterSeries());
    }
    series->setColor(selectedColor);

    for (int i = 0; i < 20; ++i)
        series->append(i, qSin(i / 3.0) * 10 + 50);

    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(0, 20);
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(minYSpin->value(), maxYSpin->value());

    chart->addSeries(series);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    QPen pen = series->pen();
    pen.setColor(selectedColor);
    pen.setStyle(static_cast<Qt::PenStyle>(lineStyleSelector->currentData().toInt()));
    pen.setWidth(lineWidthSpin->value());
    series->setPen(pen);

    previewView->setChart(chart);
}

void ChartEditorDialog::applyChanges() {
    emit chartUpdated(
        currentChart,
        typeSelector->currentText(),
        selectedColor,
        static_cast<Qt::PenStyle>(lineStyleSelector->currentData().toInt()),
        lineWidthSpin->value(),
        minYSpin->value(),
        maxYSpin->value()
        );
    accept();
}
