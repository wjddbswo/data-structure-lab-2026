#include "mainwindow.h"

#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupData(); // 음식 데이터와 그래프 초기화
    setupUi(); 

    connect(checkButton, &QPushButton::clicked, this, &MainWindow::checkCompatibility);
}

void MainWindow::setupData()
{
    foods = { 
        // 음식 목록을 정점으로 사용
        "삼겹살",
        "소주",
        "맥주",
        "치킨",
        "치즈",
        "불닭볶음면",
        "김치",
        "라면",
        "계란",
        "마늘",
        "쌈장",
        "감자튀김"
    };

    graph.resize(foods.size());  // 음식 개수만큼 그래프 공간 생성

    // 음식 사이의 궁합 관계를 간선으로 추가
    // 0:삼겹살 1:소주 2:맥주 3:치킨 4:치즈 5:불닭볶음면 6:김치 7:라면 8:계란 9:마늘 10:쌈장 11:감튀
    addUndirectedEdge(0, 1, 95);
    addUndirectedEdge(0, 5, 90);
    addUndirectedEdge(0, 6, 90);
    addUndirectedEdge(0, 9, 85);
    addUndirectedEdge(0, 10, 88);

    addUndirectedEdge(3, 2, 96);
    addUndirectedEdge(3, 4, 80);
    addUndirectedEdge(3, 5, 75);

    addUndirectedEdge(5, 4, 94);
    addUndirectedEdge(5, 8, 82);

    addUndirectedEdge(6, 7, 89);
    addUndirectedEdge(7, 8, 87);
    addUndirectedEdge(7, 4, 78);

    addUndirectedEdge(2, 11, 92);
    addUndirectedEdge(4, 11, 84);
}

void MainWindow::addUndirectedEdge(int from, int to, int score)
{
    // 무방향 그래프이므로 양쪽 방향 모두 저장
    graph[from].push_back({to, score});
    graph[to].push_back({from, score});
}

void MainWindow::setupUi()
{
    setWindowTitle("음식 궁합 점수 확인 프로그램");
    resize(850, 620);

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    QLabel *titleLabel = new QLabel("음식 궁합 점수 확인 프로그램");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet(
        "font-size: 24px;"
        "font-weight: bold;"
        "color: #222222;"
        "padding: 10px;"
    );
    mainLayout->addWidget(titleLabel);

    QLabel *descriptionLabel = new QLabel(
        "음식 두 개를 선택하면 두 음식 사이의 궁합 점수를 확인할 수 있습니다."
    );
    descriptionLabel->setAlignment(Qt::AlignCenter);
    descriptionLabel->setWordWrap(true);
    descriptionLabel->setStyleSheet(
        "font-size: 14px;"
        "color: #444444;"
        "padding: 5px;"
    );
    mainLayout->addWidget(descriptionLabel);

    graphLabel = new QLabel;
    // 그래프 데이터셋을 화면에 텍스트로 표시
    graphLabel->setText(
        "음식 궁합 그래프 데이터셋\n\n"
        "  삼겹살 ------ 소주        치킨 ------ 맥주 ------ 감자튀김\n"
        "   |                       |                          |\n"
        "   |                       |                          |\n"
        "   |                       |                          |\n"
        "   김치 ------ 라면 ------ 계란        치즈 ------ 불닭볶음면\n"
        "               |           |           |              |\n"
        "               |           |           |              |\n"
        "               |           |           |              |\n"
        "              치즈 --------+          치킨 -----------+\n\n"
        "삼겹살 ------ 마늘 / 삼겹살 ------ 쌈장 / 삼겹살 ----- 불닭볶음면"
    );
    graphLabel->setAlignment(Qt::AlignCenter);
    graphLabel->setStyleSheet(
        "font-family: Consolas;"
        "font-size: 14px;"
        "background-color: #FFF7E6;"
        "border: 2px solid #E0B86E;"
        "border-radius: 8px;"
        "padding: 15px;"
    );
    mainLayout->addWidget(graphLabel);

    // 음식 선택 영역
    QGroupBox *inputGroup = new QGroupBox("음식 두 개 선택");
    inputGroup->setStyleSheet(
        "QGroupBox {"
        "font-size: 15px;"
        "font-weight: bold;"
        "border: 1px solid #D6A84F;"
        "border-radius: 6px;"
        "margin-top: 10px;"
        "padding: 10px;"
        "}"
    );

    QHBoxLayout *inputLayout = new QHBoxLayout(inputGroup);

    QLabel *firstLabel = new QLabel("첫 번째 음식:");
    firstLabel->setStyleSheet("font-size: 14px;");

    firstFoodBox = new QComboBox;
    firstFoodBox->addItems(foods);
    firstFoodBox->setStyleSheet(
        "font-size: 14px;"
        "padding: 5px;"
    );

    QLabel *secondLabel = new QLabel("두 번째 음식:");
    secondLabel->setStyleSheet("font-size: 14px;");

    secondFoodBox = new QComboBox;
    secondFoodBox->addItems(foods);
    secondFoodBox->setCurrentIndex(1);
    secondFoodBox->setStyleSheet(
        "font-size: 14px;"
        "padding: 5px;"
    );

    checkButton = new QPushButton("궁합 점수 확인");
    checkButton->setStyleSheet(
        "QPushButton {"
        "font-size: 14px;"
        "font-weight: bold;"
        "background-color: #F28C28;"
        "color: white;"
        "border-radius: 6px;"
        "padding: 8px 16px;"
        "}"
        "QPushButton:hover {"
        "background-color: #D8741F;"
        "}"
    );

    inputLayout->addWidget(firstLabel);
    inputLayout->addWidget(firstFoodBox);
    inputLayout->addWidget(secondLabel);
    inputLayout->addWidget(secondFoodBox);
    inputLayout->addWidget(checkButton);

    mainLayout->addWidget(inputGroup);

    // 결과 출력창
    resultText = new QTextEdit;
    resultText->setReadOnly(true);
    resultText->setPlaceholderText("궁합 점수 결과가 여기에 출력됩니다.");
    resultText->setStyleSheet(
        "font-size: 14px;"
        "background-color: #FFFFFF;"
        "border: 1px solid #D6A84F;"
        "border-radius: 6px;"
        "padding: 8px;"
    );
    mainLayout->addWidget(resultText);

    QLabel *bottomLabel = new QLabel("두 음식 사이에 연결된 간선의 가중치를 궁합 점수로 출력합니다.");
    bottomLabel->setAlignment(Qt::AlignCenter);
    bottomLabel->setStyleSheet(
        "font-size: 13px;"
        "color: #666666;"
        "padding: 5px;"
    );
    mainLayout->addWidget(bottomLabel);
}

int MainWindow::findCompatibilityScore(int from, int to)
{   
    // 첫 번째 음식의 인접 리스트에서 두 번째 음식을 탐색
    for (const Edge &edge : graph[from]) {
        if (edge.to == to) {
            return edge.score;
        }
    }

    return -1; // 연결된 간선이 없으면 -1 반환
}

void MainWindow::checkCompatibility()
{
    int first = firstFoodBox->currentIndex();
    int second = secondFoodBox->currentIndex();

    // 같은 음식을 선택한 경우 예외 처리
    if (first == second) {
        QMessageBox::warning(this, "선택 오류", "서로 다른 음식을 선택하세요.");
        return;
    }

    int score = findCompatibilityScore(first, second);

    QString output;
    QTextStream stream(&output);

    stream << "[음식 궁합 점수 결과]\n\n";
    stream << "선택한 음식:\n";
    stream << foods[first] << " + " << foods[second] << "\n\n";

    // 간선이 없으면 등록된 정보가 없다고 출력
    if (score == -1) {
        stream << "등록된 직접 궁합 정보가 없습니다.\n";
    } else {
        stream << "궁합 점수: " << score << "점\n";
        stream << "평가: " << makeScoreLevel(score) << "\n";
    }

    resultText->setText(output);
}

QString MainWindow::makeScoreLevel(int score)
{
    // 점수 범위에 따라 평가
    if (score >= 90) {
        return "매우 잘 어울림";
    }

    if (score >= 80) {
        return "잘 어울림";
    }

    if (score >= 70) {
        return "무난한 조합";
    }

    return "실험적인 조합";
}
