#ifndef INFOPANEL_H
#define INFOPANEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QFrame>
#include <QVBoxLayout>

/**
 * @class InfoPanel
 * @brief Klasa odpowiedzialna za infopanel.
 */
class InfoPanel : public QFrame {
    Q_OBJECT

public:
    /**
 * @brief Metoda InfoPanel.
 */
    explicit InfoPanel(const QString &title = "", QWidget *parent = nullptr);

    /**
 * @brief Metoda setValue.
 */
    void setValue(const QString &valueText);
    /**
 * @brief Metoda setFontSize.
 */
    void setFontSize(int size);
    /**
 * @brief Metoda setTextColor.
 */
    void setTextColor(const QColor &color);
    /**
 * @brief Metoda setBackgroundColor.
 */
    void setBackgroundColor(const QColor &color);
    /**
 * @brief Metoda setBorderColor.
 */
    void setBorderColor(const QColor &color);
    /**
 * @brief Metoda setPanelSize.
 */
    void setPanelSize(int width, int height);

private:
    QLabel *titleLabel;
    QLabel *valueLabel;
};
#endif // INFOPANEL_H
