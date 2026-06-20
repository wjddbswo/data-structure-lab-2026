#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QString>

class QComboBox;
class QPushButton;
class QTextEdit;
class QLabel;

// 그래프의 간선을 표현하는 구조체
// to: 연결된 음식 번호
// score: 궁합 점수
struct Edge {
    int to;
    int score;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    QVector<QString> foods; // 음식 이름 목록
    QVector<QVector<Edge>> graph; // 음식 궁합 그래프를 인접 리스트로 저장

    // GUI 구성 요소
    QComboBox *firstFoodBox;
    QComboBox *secondFoodBox;
    QPushButton *checkButton;
    QTextEdit *resultText;
    QLabel *graphLabel;

    // 데이터와 UI를 초기화
    void setupData();
    void setupUi();
    // 그래프 간선 추가 및 탐색
    void addUndirectedEdge(int from, int to, int score);
    int findCompatibilityScore(int from, int to);
     // 점수에 따른 평가 출력
    QString makeScoreLevel(int score);

private slots:
    void checkCompatibility(); // 버튼 클릭 시 실행
};

#endif
