#include "window.h"
#include "openGlWidget.h"
#include "ui_mainwindow.h"
#include <QScreen>
#include <QApplication>
#include <QVBoxLayout>

Window::Window(std::unique_ptr<QWidget>&& widget) :
    _layout(std::make_unique<Ui_MainWindow>()),
    _widget(std::move(widget))
{
    _layout->setupUi(this);

    QScreen* screen = QApplication::primaryScreen();
    if (screen) {
        QRect screenGeometry = screen->availableGeometry();
        QRect windowGeometry = this->frameGeometry();
        int x = (screenGeometry.width() - windowGeometry.width()) / 2 + screenGeometry.x();
        int y = (screenGeometry.height() - windowGeometry.height()) / 2 + screenGeometry.y();
        this->move(x, y);
    }

    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(_layout->centralwidget->layout());
    if (layout) {
        layout->addWidget(_widget.get(), 1);
    } else {
        _layout->centralwidget->layout()->addWidget(_widget.get());
    }

    OpenGLWidget* glWidget = dynamic_cast<OpenGLWidget*>(_widget.get());
    if (glWidget) {
        glWidget->_labelMs = _layout->labelMs;
    }
}

Window::~Window() = default;