#include "window.h"

#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication* app = new QApplication(argc, argv);

    Window window;
    window.show();
    app->exec();

    return 0;
}