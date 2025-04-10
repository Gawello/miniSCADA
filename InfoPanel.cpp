#include "InfoPanel.h"

InfoPanel::InfoPanel(const QString &title, QWidget *parent)
    : QFrame(parent) {
    setFrameShape(QFrame::Box);
    setLineWidth(2);

    titleLabel = new QLabel(title, this);
    titleLabel->setAlignment(Qt::AlignCenter);

    valueLabel = new QLabel("-", this);
    valueLabel->setAlignment(Qt::AlignCenter);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addWidget(valueLabel);
    setLayout(layout);

    // Domyślne style
    setFontSize(16);
    setTextColor(Qt::black);
    setBackgroundColor(Qt::white);
    setBorderColor(Qt::black);
    setPanelSize(120, 80);
}

void InfoPanel::setValue(const QString &valueText) {
    valueLabel->setText(valueText);
}

void InfoPanel::setFontSize(int size) {
    QString style = QString("font-size: %1pt;").arg(size);
    titleLabel->setStyleSheet(style);
    valueLabel->setStyleSheet(style);
}

void InfoPanel::setTextColor(const QColor &color) {
    QString colorName = color.name();
    titleLabel->setStyleSheet(titleLabel->styleSheet() + QString("color: %1;").arg(colorName));
    valueLabel->setStyleSheet(valueLabel->styleSheet() + QString("color: %1;").arg(colorName));
}

void InfoPanel::setBackgroundColor(const QColor &color) {
    QString style = QString("background-color: %1;").arg(color.name());
    setStyleSheet(style);
}

void InfoPanel::setBorderColor(const QColor &color) {
    QString style = QString("border: 2px solid %1;").arg(color.name());
    setStyleSheet(style + styleSheet());
}

void InfoPanel::setPanelSize(int width, int height) {
    setMinimumSize(width, height);
    setMaximumSize(width, height);
}
