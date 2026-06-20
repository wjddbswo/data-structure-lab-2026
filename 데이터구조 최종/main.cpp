#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // Qt GUI 프로그램을 실행하기 위한 애플리케이션 객체 생성
    QApplication app(argc, argv);

    // 메인 윈도우 객체 생성 및 화면 출력
    MainWindow window;
    window.show();

    // 이벤트 루프 실행
    return app.exec();
}
