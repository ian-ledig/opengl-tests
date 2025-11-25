#include "widgetColor.h"
#include "ui_widgetColor.h"
#include <QSpinBox>
#include <QPushButton>

ColorWidget::ColorWidget(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Form)
{
    ui->setupUi(this);
    
    connect(ui->pushButtonCancel, &QPushButton::clicked, this, &ColorWidget::close);
    connect(ui->pushButtonOk, &QPushButton::clicked, this, &ColorWidget::onOkClicked);
}

ColorWidget::~ColorWidget()
{
    delete ui;
}

void ColorWidget::setColor(const glm::vec4& color)
{
    ui->spinBoxR->setValue(static_cast<int>(color.r * 255.0f));
    ui->spinBoxG->setValue(static_cast<int>(color.g * 255.0f));
    ui->spinBoxB->setValue(static_cast<int>(color.b * 255.0f));
}

glm::vec4 ColorWidget::getColor() const
{
    float r = ui->spinBoxR->value() / 255.0f;
    float g = ui->spinBoxG->value() / 255.0f;
    float b = ui->spinBoxB->value() / 255.0f;
    return glm::vec4(r, g, b, 1.0f);
}

void ColorWidget::onOkClicked()
{
    emit colorChanged(getColor());
    accept();
}
