#include "FramelessWindow.h"
#include <QApplication>
#include <QIcon>


int main(int argc, char *argv[])
{
    // High DPI scaling is enabled by default from Qt 6
#if (QT_VERSION < QT_VERSION_CHECK(6, 0, 0))
    // Windows: we are using the manifest file to get maximum compatibility
    // because some APIs are not supprted on old systems such as Windows 7
    // and Windows 8. And once we have set the DPI awareness level in the
    // manifest file, any attemptation to try to change it through API will
    // fail. In other words, Qt won't be able to enable or disable high DPI
    // scaling or change the DPI awareness level once we have set it in the
    // manifest file. So the following two lines are uesless actually (However,
    // they are still useful on other platforms).
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
    // Don't round the scale factor.
    // This will break QWidget applications because they can't render correctly.
    // Qt Quick applications won't have this issue.
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#endif
#endif

    QApplication a(argc, argv);

    //set font of application
    QFont font("Microsoft YaHei", 16);
    a.setFont(font);

    //create frameless window (and set windowState or title)
    FramelessWindow w;
    //w.setWindowIcon(a.style()->standardIcon(QStyle::SP_DesktopIcon));
    w.setWindowIcon(QIcon(":/img/images/windowIcon_1.png"));

    // create a custom type instance of QMainwindow
    // add the mainwindow to our custom frameless window
//    MainWindow *mainWindow = new MainWindow;
//    framelessWindow.setContentWidget(mainWindow);

    w.setWindowTitle("Test");
    w.show();

    return a.exec();
}























