#pragma once

#include <QDialog>
#include <glm/glm.hpp>

QT_BEGIN_NAMESPACE
class QSpinBox;
QT_END_NAMESPACE

namespace Ui {
    class Form;
}

class ColorWidget : public QDialog {
    Q_OBJECT

public:
    explicit ColorWidget(QWidget *parent = nullptr);
    ~ColorWidget();

    void setColor(const glm::vec4& color);
    glm::vec4 getColor() const;

signals:
    void colorChanged(const glm::vec4& color);

private slots:
    void onOkClicked();

private:
    Ui::Form *ui;
    void updateColor();
};

