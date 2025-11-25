#pragma once

#include <QMainWindow>
#include <memory>

class Ui_MainWindow;

class Window : public QMainWindow {
public:
    Window(std::unique_ptr<QWidget>&& widget);
    ~Window();

private:
    std::unique_ptr<Ui_MainWindow> _layout;
    std::unique_ptr<QWidget> _widget;
};