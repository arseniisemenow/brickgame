/********************************************************************************
** Form generated from reading UI file 'View.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEW_H
#define UI_VIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>
#include "QWidget"

QT_BEGIN_NAMESPACE

class Ui_View
{
public:
    QWidget *centralwidget;
    QStackedWidget *stacked_widget;
    QWidget *stacked_widget_tetris;
    GridWidget *widget_tetris;
    NextPlayerGridWidget *widget_tetris_next_player;
    QLabel *label_score_tetris;
    QLabel *label_level_tetris;
    QLabel *label_records;
    QLabel *label_records_1;
    QLabel *label_records_2;
    QLabel *label_records_3;
    QLabel *label_records_4;
    QLabel *label_records_5;
    QLabel *label_score_tetris_value;
    QLabel *label_level_tetris_value;
    QLabel *label_records_1_value;
    QLabel *label_records_2_value;
    QLabel *label_records_3_value;
    QLabel *label_records_4_value;
    QLabel *label_records_5_value;
    QLabel *label_state_tetris;
    QWidget *stacked_widget_snake;
    GridWidget *widget_snake;
    QLabel *label_records_snake_4_value;
    QLabel *label_records_snake_4;
    QLabel *label_score_snake;
    QLabel *label_score_snake_value;
    QLabel *label_records_snake_2_value;
    QLabel *label_records_snake_3;
    QLabel *label_level_snake;
    QLabel *label_records_snake_5;
    QLabel *label_records_snake_5_value;
    QLabel *label_level_snake_value;
    QLabel *label_state_snake;
    QLabel *label_records_snake_3_value;
    QLabel *label_records_snake_1;
    QLabel *label_records_snake;
    QLabel *label_records_snake_1_value;
    QLabel *label_records_snake_2;
    QWidget *stacked_widget_car_racing;
    QLabel *label_3;
    GridWidget *widget_car_racing;
    QWidget *stacked_widget_tank_classic;
    QLabel *label;
    GridWidget *widget_tank_classic;
    QPushButton *push_button_tetris;
    QPushButton *push_button_snake;
    QPushButton *push_button_car_racing;
    QPushButton *push_button_tank_classic;

    void setupUi(QMainWindow *View)
    {
        if (View->objectName().isEmpty())
            View->setObjectName("View");
        View->resize(370, 480);
        View->setMinimumSize(QSize(370, 480));
        View->setMaximumSize(QSize(370, 480));
        View->setStyleSheet(QString::fromUtf8("background-color: rgb(50,50,50);"));
        centralwidget = new QWidget(View);
        centralwidget->setObjectName("centralwidget");
        stacked_widget = new QStackedWidget(centralwidget);
        stacked_widget->setObjectName("stacked_widget");
        stacked_widget->setGeometry(QRect(10, 50, 351, 420));
        stacked_widget_tetris = new QWidget();
        stacked_widget_tetris->setObjectName("stacked_widget_tetris");
        widget_tetris = new GridWidget(stacked_widget_tetris);
        widget_tetris->setObjectName("widget_tetris");
        widget_tetris->setGeometry(QRect(0, 0, 210, 420));
        widget_tetris_next_player = new NextPlayerGridWidget(stacked_widget_tetris);
        widget_tetris_next_player->setObjectName("widget_tetris_next_player");
        widget_tetris_next_player->setGeometry(QRect(230, 0, 84, 84));
        widget_tetris_next_player->setMinimumSize(QSize(84, 84));
        widget_tetris_next_player->setMaximumSize(QSize(84, 84));
        label_score_tetris = new QLabel(stacked_widget_tetris);
        label_score_tetris->setObjectName("label_score_tetris");
        label_score_tetris->setGeometry(QRect(230, 110, 58, 16));
        label_score_tetris->setStyleSheet(QString::fromUtf8("font-size: 20pt"));
        label_level_tetris = new QLabel(stacked_widget_tetris);
        label_level_tetris->setObjectName("label_level_tetris");
        label_level_tetris->setGeometry(QRect(230, 140, 58, 16));
        label_level_tetris->setStyleSheet(QString::fromUtf8("font-size: 20pt"));
        label_records = new QLabel(stacked_widget_tetris);
        label_records->setObjectName("label_records");
        label_records->setGeometry(QRect(230, 170, 81, 16));
        label_records->setStyleSheet(QString::fromUtf8("font-size: 20pt"));
        label_records_1 = new QLabel(stacked_widget_tetris);
        label_records_1->setObjectName("label_records_1");
        label_records_1->setGeometry(QRect(230, 200, 21, 16));
        label_records_1->setStyleSheet(QString::fromUtf8("font-size: 20pt"));
        label_records_2 = new QLabel(stacked_widget_tetris);
        label_records_2->setObjectName("label_records_2");
        label_records_2->setGeometry(QRect(230, 220, 21, 16));
        label_records_2->setStyleSheet(QString::fromUtf8("font-size: 20pt"));
        label_records_3 = new QLabel(stacked_widget_tetris);
        label_records_3->setObjectName("label_records_3");
        label_records_3->setGeometry(QRect(230, 240, 21, 16));
        label_records_3->setStyleSheet(QString::fromUtf8("font-size: 20pt"));
        label_records_4 = new QLabel(stacked_widget_tetris);
        label_records_4->setObjectName("label_records_4");
        label_records_4->setGeometry(QRect(230, 260, 21, 16));
        label_records_4->setStyleSheet(QString::fromUtf8("font-size: 20pt"));
        label_records_5 = new QLabel(stacked_widget_tetris);
        label_records_5->setObjectName("label_records_5");
        label_records_5->setGeometry(QRect(230, 280, 21, 16));
        label_records_5->setStyleSheet(QString::fromUtf8("font-size: 20pt"));
        label_score_tetris_value = new QLabel(stacked_widget_tetris);
        label_score_tetris_value->setObjectName("label_score_tetris_value");
        label_score_tetris_value->setGeometry(QRect(290, 110, 58, 16));
        label_score_tetris_value->setStyleSheet(QString::fromUtf8("font-size: 20pt"));
        label_level_tetris_value = new QLabel(stacked_widget_tetris);
        label_level_tetris_value->setObjectName("label_level_tetris_value");
        label_level_tetris_value->setGeometry(QRect(280, 140, 58, 16));
        label_level_tetris_value->setStyleSheet(QString::fromUtf8("font-size: 20pt"));
        label_records_1_value = new QLabel(stacked_widget_tetris);
        label_records_1_value->setObjectName("label_records_1_value");
        label_records_1_value->setGeometry(QRect(250, 200, 91, 16));
        label_records_1_value->setStyleSheet(QString::fromUtf8("font-size: 20pt"));
        label_records_2_value = new QLabel(stacked_widget_tetris);
        label_records_2_value->setObjectName("label_records_2_value");
        label_records_2_value->setGeometry(QRect(250, 220, 91, 16));
        label_records_2_value->setStyleSheet(QString::fromUtf8("font-size: 20pt"));
        label_records_3_value = new QLabel(stacked_widget_tetris);
        label_records_3_value->setObjectName("label_records_3_value");
        label_records_3_value->setGeometry(QRect(250, 240, 91, 16));
        label_records_3_value->setStyleSheet(QString::fromUtf8("font-size: 20pt"));
        label_records_4_value = new QLabel(stacked_widget_tetris);
        label_records_4_value->setObjectName("label_records_4_value");
        label_records_4_value->setGeometry(QRect(250, 260, 91, 16));
        label_records_4_value->setStyleSheet(QString::fromUtf8("font-size: 20pt"));
        label_records_5_value = new QLabel(stacked_widget_tetris);
        label_records_5_value->setObjectName("label_records_5_value");
        label_records_5_value->setGeometry(QRect(250, 280, 91, 16));
        label_records_5_value->setStyleSheet(QString::fromUtf8("font-size: 20pt"));
        label_state_tetris = new QLabel(stacked_widget_tetris);
        label_state_tetris->setObjectName("label_state_tetris");
        label_state_tetris->setGeometry(QRect(290, 400, 58, 16));
        stacked_widget->addWidget(stacked_widget_tetris);
        stacked_widget_snake = new QWidget();
        stacked_widget_snake->setObjectName("stacked_widget_snake");
        widget_snake = new GridWidget(stacked_widget_snake);
        widget_snake->setObjectName("widget_snake");
        widget_snake->setGeometry(QRect(0, 0, 210, 420));
        label_records_snake_4_value = new QLabel(stacked_widget_snake);
        label_records_snake_4_value->setObjectName("label_records_snake_4_value");
        label_records_snake_4_value->setGeometry(QRect(250, 170, 91, 16));
        label_records_snake_4_value->setStyleSheet(QString::fromUtf8("font-size: 20pt"));
        label_records_snake_4 = new QLabel(stacked_widget_snake);
        label_records_snake_4->setObjectName("label_records_snake_4");
        label_records_snake_4->setGeometry(QRect(230, 170, 21, 16));
        label_records_snake_4->setStyleSheet(QString::fromUtf8("font-size: 20pt"));
        label_score_snake = new QLabel(stacked_widget_snake);
        label_score_snake->setObjectName("label_score_snake");
        label_score_snake->setGeometry(QRect(230, 20, 58, 16));
        label_score_snake->setStyleSheet(QString::fromUtf8("font-size: 20pt"));
        label_score_snake_value = new QLabel(stacked_widget_snake);
        label_score_snake_value->setObjectName("label_score_snake_value");
        label_score_snake_value->setGeometry(QRect(290, 20, 58, 16));
        label_score_snake_value->setStyleSheet(QString::fromUtf8("font-size: 20pt"));
        label_records_snake_2_value = new QLabel(stacked_widget_snake);
        label_records_snake_2_value->setObjectName("label_records_snake_2_value");
        label_records_snake_2_value->setGeometry(QRect(250, 130, 91, 16));
        label_records_snake_2_value->setStyleSheet(QString::fromUtf8("font-size: 20pt"));
        label_records_snake_3 = new QLabel(stacked_widget_snake);
        label_records_snake_3->setObjectName("label_records_snake_3");
        label_records_snake_3->setGeometry(QRect(230, 150, 21, 16));
        label_records_snake_3->setStyleSheet(QString::fromUtf8("font-size: 20pt"));
        label_level_snake = new QLabel(stacked_widget_snake);
        label_level_snake->setObjectName("label_level_snake");
        label_level_snake->setGeometry(QRect(230, 50, 58, 16));
        label_level_snake->setStyleSheet(QString::fromUtf8("font-size: 20pt"));
        label_records_snake_5 = new QLabel(stacked_widget_snake);
        label_records_snake_5->setObjectName("label_records_snake_5");
        label_records_snake_5->setGeometry(QRect(230, 190, 21, 16));
        label_records_snake_5->setStyleSheet(QString::fromUtf8("font-size: 20pt"));
        label_records_snake_5_value = new QLabel(stacked_widget_snake);
        label_records_snake_5_value->setObjectName("label_records_snake_5_value");
        label_records_snake_5_value->setGeometry(QRect(250, 190, 91, 16));
        label_records_snake_5_value->setStyleSheet(QString::fromUtf8("font-size: 20pt"));
        label_level_snake_value = new QLabel(stacked_widget_snake);
        label_level_snake_value->setObjectName("label_level_snake_value");
        label_level_snake_value->setGeometry(QRect(280, 50, 58, 16));
        label_level_snake_value->setStyleSheet(QString::fromUtf8("font-size: 20pt"));
        label_state_snake = new QLabel(stacked_widget_snake);
        label_state_snake->setObjectName("label_state_snake");
        label_state_snake->setGeometry(QRect(290, 400, 58, 16));
        label_records_snake_3_value = new QLabel(stacked_widget_snake);
        label_records_snake_3_value->setObjectName("label_records_snake_3_value");
        label_records_snake_3_value->setGeometry(QRect(250, 150, 91, 16));
        label_records_snake_3_value->setStyleSheet(QString::fromUtf8("font-size: 20pt"));
        label_records_snake_1 = new QLabel(stacked_widget_snake);
        label_records_snake_1->setObjectName("label_records_snake_1");
        label_records_snake_1->setGeometry(QRect(230, 110, 21, 16));
        label_records_snake_1->setStyleSheet(QString::fromUtf8("font-size: 20pt"));
        label_records_snake = new QLabel(stacked_widget_snake);
        label_records_snake->setObjectName("label_records_snake");
        label_records_snake->setGeometry(QRect(230, 80, 81, 16));
        label_records_snake->setStyleSheet(QString::fromUtf8("font-size: 20pt"));
        label_records_snake_1_value = new QLabel(stacked_widget_snake);
        label_records_snake_1_value->setObjectName("label_records_snake_1_value");
        label_records_snake_1_value->setGeometry(QRect(250, 110, 91, 16));
        label_records_snake_1_value->setStyleSheet(QString::fromUtf8("font-size: 20pt"));
        label_records_snake_2 = new QLabel(stacked_widget_snake);
        label_records_snake_2->setObjectName("label_records_snake_2");
        label_records_snake_2->setGeometry(QRect(230, 130, 21, 16));
        label_records_snake_2->setStyleSheet(QString::fromUtf8("font-size: 20pt"));
        stacked_widget->addWidget(stacked_widget_snake);
        stacked_widget_car_racing = new QWidget();
        stacked_widget_car_racing->setObjectName("stacked_widget_car_racing");
        label_3 = new QLabel(stacked_widget_car_racing);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(100, 110, 58, 16));
        widget_car_racing = new GridWidget(stacked_widget_car_racing);
        widget_car_racing->setObjectName("widget_car_racing");
        widget_car_racing->setGeometry(QRect(0, 0, 210, 420));
        stacked_widget->addWidget(stacked_widget_car_racing);
        stacked_widget_tank_classic = new QWidget();
        stacked_widget_tank_classic->setObjectName("stacked_widget_tank_classic");
        label = new QLabel(stacked_widget_tank_classic);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 210, 58, 16));
        widget_tank_classic = new GridWidget(stacked_widget_tank_classic);
        widget_tank_classic->setObjectName("widget_tank_classic");
        widget_tank_classic->setGeometry(QRect(0, 0, 210, 420));
        stacked_widget->addWidget(stacked_widget_tank_classic);
        push_button_tetris = new QPushButton(centralwidget);
        push_button_tetris->setObjectName("push_button_tetris");
        push_button_tetris->setGeometry(QRect(10, 10, 81, 32));
        push_button_snake = new QPushButton(centralwidget);
        push_button_snake->setObjectName("push_button_snake");
        push_button_snake->setGeometry(QRect(100, 10, 81, 32));
        push_button_car_racing = new QPushButton(centralwidget);
        push_button_car_racing->setObjectName("push_button_car_racing");
        push_button_car_racing->setGeometry(QRect(190, 10, 81, 32));
        push_button_tank_classic = new QPushButton(centralwidget);
        push_button_tank_classic->setObjectName("push_button_tank_classic");
        push_button_tank_classic->setGeometry(QRect(280, 10, 81, 32));
        View->setCentralWidget(centralwidget);

        retranslateUi(View);

        stacked_widget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(View);
    } // setupUi

    void retranslateUi(QMainWindow *View)
    {
        View->setWindowTitle(QCoreApplication::translate("View", "View", nullptr));
        label_score_tetris->setText(QCoreApplication::translate("View", "Score:", nullptr));
        label_level_tetris->setText(QCoreApplication::translate("View", "Level:", nullptr));
        label_records->setText(QCoreApplication::translate("View", "Records:", nullptr));
        label_records_1->setText(QCoreApplication::translate("View", "1.", nullptr));
        label_records_2->setText(QCoreApplication::translate("View", "2.", nullptr));
        label_records_3->setText(QCoreApplication::translate("View", "3.", nullptr));
        label_records_4->setText(QCoreApplication::translate("View", "4.", nullptr));
        label_records_5->setText(QCoreApplication::translate("View", "5.", nullptr));
        label_score_tetris_value->setText(QCoreApplication::translate("View", "Score:", nullptr));
        label_level_tetris_value->setText(QCoreApplication::translate("View", "Level:", nullptr));
        label_records_1_value->setText(QCoreApplication::translate("View", "1.", nullptr));
        label_records_2_value->setText(QCoreApplication::translate("View", "2.", nullptr));
        label_records_3_value->setText(QCoreApplication::translate("View", "3.", nullptr));
        label_records_4_value->setText(QCoreApplication::translate("View", "4.", nullptr));
        label_records_5_value->setText(QCoreApplication::translate("View", "5.", nullptr));
        label_state_tetris->setText(QString());
        label_records_snake_4_value->setText(QCoreApplication::translate("View", "4.", nullptr));
        label_records_snake_4->setText(QCoreApplication::translate("View", "4.", nullptr));
        label_score_snake->setText(QCoreApplication::translate("View", "Score:", nullptr));
        label_score_snake_value->setText(QCoreApplication::translate("View", "Score:", nullptr));
        label_records_snake_2_value->setText(QCoreApplication::translate("View", "2.", nullptr));
        label_records_snake_3->setText(QCoreApplication::translate("View", "3.", nullptr));
        label_level_snake->setText(QCoreApplication::translate("View", "Level:", nullptr));
        label_records_snake_5->setText(QCoreApplication::translate("View", "5.", nullptr));
        label_records_snake_5_value->setText(QCoreApplication::translate("View", "5.", nullptr));
        label_level_snake_value->setText(QCoreApplication::translate("View", "Level:", nullptr));
        label_state_snake->setText(QString());
        label_records_snake_3_value->setText(QCoreApplication::translate("View", "3.", nullptr));
        label_records_snake_1->setText(QCoreApplication::translate("View", "1.", nullptr));
        label_records_snake->setText(QCoreApplication::translate("View", "Records:", nullptr));
        label_records_snake_1_value->setText(QCoreApplication::translate("View", "1.", nullptr));
        label_records_snake_2->setText(QCoreApplication::translate("View", "2.", nullptr));
        label_3->setText(QCoreApplication::translate("View", "car_racing", nullptr));
        label->setText(QCoreApplication::translate("View", "Tank classic", nullptr));
        push_button_tetris->setText(QCoreApplication::translate("View", "Tetris", nullptr));
        push_button_snake->setText(QCoreApplication::translate("View", "Snake", nullptr));
        push_button_car_racing->setText(QCoreApplication::translate("View", "Car Racing", nullptr));
        push_button_tank_classic->setText(QCoreApplication::translate("View", "Tank Classic", nullptr));
    } // retranslateUi

};

namespace Ui {
    class View: public Ui_View {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEW_H
