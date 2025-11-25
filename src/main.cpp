#include <QApplication>
#include <memory>

#include "window.h"
#include "openGlWidget.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    auto openGlWidget = std::make_unique<OpenGLWidget>();
    Window window(std::move(openGlWidget));

    window.show();

    return app.exec();
}