#ifndef INFOPANEL_H
#define INFOPANEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QFrame>
#include <QVBoxLayout>

class InfoPanel : public QFrame {
    Q_OBJECT

public:
    explicit InfoPanel(const QString &title = "", QWidget *parent = nullptr);

    void setValue(const QString &valueText);
    void setFontSize(int size);
    void setTextColor(const QColor &color);
    void setBackgroundColor(const QColor &color);
    void setBorderColor(const QColor &color);
    void setPanelSize(int width, int height);

private:
    QLabel *titleLabel;
    QLabel *valueLabel;
};
#endif // INFOPANEL_H
