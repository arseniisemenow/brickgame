#include "style_handler.h"

namespace s21::style_handler {
void SetSelectedTabButton(QPushButton *push_button) {
  push_button->setStyleSheet(
      "QPushButton { "
      "background-color: rgb(75, 75, 75); /* Background color */"
      "color: #FFF; /* Text color */"
      "border: 1px solid rgb(255, 136, 0);/* Border color when QLineEdit is "
      "focused */"
      "border-radius: 10px; /* Rounded corners */"
      "padding: 1px 1px; /* Padding inside the button */"
      "font-size: 10pt;"
      "}"
      "QPushButton:hover {"
      "background-color: rgb(85, 85, 85); /* Background color on hover */"
      "/*border: 2px solid rgb(147,112,219); /* Border color on hover */"
      "}"
      "QPushButton:pressed {"
      "background-color: rgb(65, 65, 65); /* Background color when pressed */"
      "/* border: 2px solid rgb(147,112,219); /* Border color on hover */"
      "}");
}

void SetUnselectedTabButton(QPushButton *push_button) {
  push_button->setStyleSheet(
      "QPushButton {"
      "background-color: rgb(75, 75, 75); /* Background color */"
      "color: #FFF; /* Text color */"
      "border: 1px solid rgb(100, 100, 100);/* Border color when QLineEdit is "
      "focused */"
      "border-radius: 10px; /* Rounded corners */"
      "padding: 1px 1px; /* Padding inside the button */"
      "font-size: 10pt;"
      "}"

      "QPushButton:hover {"
      "background-color: rgb(85, 85, 85); /* Background color on hover */"
      "/*border: 2px solid rgb(147,112,219); /* Border color on hover */"
      "}"
      "QPushButton:pressed {"
      "background-color: rgb(65, 65, 65); /* Background color when pressed */"
      "/* border: 2px solid rgb(147,112,219); /* Border color on hover */"
      "}");
}

void SetDefaultExpressionLineEdit(QLineEdit *line_edit) {
  line_edit->setStyleSheet(
      "QLineEdit {"
      "border: 1px solid rgb(100 ,100, 100); /* Border color and width */"
      "border-radius: 30px; /* Rounded corners */"
      "padding: 5px; /* Padding inside the QLineEdit */"
      "background-color: rgb(35,35,35); /* Background color */"
      "color: rgb(200, 200, 200); /* Text color */"
      "}"
      "QLineEdit:"
      "focus{"
      "border: 1px solid"
      "#ff8800; /* Border color when QLineEdit is focused */"
      "background-color: rgb(35, 35, 35); /* Background color when QLineEdit "
      "is focused */"
      "}");
}

void SetIncorrectExpressionLineEdit(QLineEdit *line_edit) {
  line_edit->setStyleSheet(
      "QLineEdit {"
      "border: 1px solid #ff2200; /* Border color and width */"
      "border-radius: 30px; /* Rounded corners */"
      "padding: 5px; /* Padding inside the QLineEdit */"
      "background-color: rgb(35,35,35); /* Background color */"
      "color: rgb(200, 200, 200); /* Text color */"
      "}"
      "QLineEdit:"
      "focus{"
      "border: 1px solid #ff2200; /* Border color when QLineEdit is focused */"
      "background-color: rgb(35, 35, 35); /* Background color when QLineEdit "
      "is focused */"
      "}");
}

void SetDefaultVariableLineEdit(QLineEdit *line_edit) {
  line_edit->setStyleSheet(
      "QLineEdit {"
      "border: 1px solid rgb(100 ,100, 100); /* Border color and width */"
      "border-radius: 10px; /* Rounded corners */"
      "padding: 1px; /* Padding inside the QLineEdit */"
      "background-color: rgb(35,35,35); /* Background color */"
      "color: rgb(200, 200, 200); /* Text color */"
      "font-size: 10pt;"
      "alignment: center; /* or left, right, justify */"
      "}"
      ""
      "QLineEdit:focus {"
      "border: 1px solid #ff8800; /* Border color when QLineEdit is focused */"
      "background-color: rgb(35, 35, 35); /* Background color when QLineEdit "
      "is focused */"
      "}");
}

void SetIncorrectVariableLineEdit(QLineEdit *line_edit) {
  line_edit->setStyleSheet(
      "QLineEdit {"
      "border: 1px solid #ff2200; /* Border color and width */"
      "border-radius: 10px; /* Rounded corners */"
      "padding: 1px; /* Padding inside the QLineEdit */"
      "background-color: rgb(35,35,35); /* Background color */"
      "color: rgb(200, 200, 200); /* Text color */"
      "font-size: 10pt;"
      "alignment: center; /* or left, right, justify */"
      "}"
      ""
      "QLineEdit:focus {"
      "border: 1px solid #ff2200; /* Border color when QLineEdit is focused */"
      "background-color: rgb(35, 35, 35); /* Background color when QLineEdit "
      "is focused */"
      "}");
}

void SetDefaultDomainLineEdit(QLineEdit *line_edit) {
  line_edit->setStyleSheet(
      ""
      "QLineEdit {"
      "    border: 1px solid rgb(100 ,100, 100); /* Border color and width */"
      "    border-radius: 10px; /* Rounded corners */"
      "    padding: 1px; /* Padding inside the QLineEdit */"
      "    background-color: rgb(35,35,35); /* Background color */"
      "    color: rgb(200, 200, 200); /* Text color */"
      "font-size: 10pt;"
      "    alignment: center; /* or left, right, justify */"
      "}"
      "QLineEdit:focus {"
      "    border: 1px solid #FF8800; /* Border color when QLineEdit is "
      "focused */"
      "    background-color: rgb(35, 35, 35); /* Background color when "
      "QLineEdit is focused */"
      "}");
}

void SetIncorrectDomainLineEdit(QLineEdit *line_edit) {
  line_edit->setStyleSheet(
      "QLineEdit {"
      "    border: 1px solid #ff2200; /* Border color and width */"
      "    border-radius: 10px; /* Rounded corners */"
      "    padding: 1px; /* Padding inside the QLineEdit */"
      "    background-color: rgb(35,35,35); /* Background color */"
      "    color: rgb(200, 200, 200); /* Text color */"
      "font-size: 10pt;n"
      "    alignment: center; /* or left, right, justify */"
      "}"
      ""
      "QLineEdit:focus {"
      "    border: 1px solid #ff2200; /* Border color when QLineEdit is "
      "focused */"
      "    background-color: rgb(35, 35, 35); /* Background color when "
      "QLineEdit is focused */"
      "}");
}

void SetDefaultCreditLineEdit(QLineEdit *line_edit) {
  line_edit->setStyleSheet(
      "QLineEdit {\n"
      "    border: 1px solid rgb(100 ,100, 100); /* Border color and width */\n"
      "    border-radius: 20px; /* Rounded corners */\n"
      "    padding: 1px; /* Padding inside the QLineEdit */\n"
      "    background-color: rgb(35,35,35); /* Background color */\n"
      "    color: rgb(200, 200, 200); /* Text color */\n"
      "}\n"
      "\n"
      "QLineEdit:focus {\n"
      "    border: 1px solid #FF8800; /* Border color when QLineEdit is "
      "focused */\n"
      "    background-color: rgb(35, 35, 35); /* Background color when "
      "QLineEdit is focused */\n"
      "}");
}

void SetIncorrectCreditLineEdit(QLineEdit *line_edit) {
  line_edit->setStyleSheet(
      "QLineEdit {\n"
      "    border: 1px solid #FF2200; /* Border color and width */\n"
      "    border-radius: 20px; /* Rounded corners */\n"
      "    padding: 1px; /* Padding inside the QLineEdit */\n"
      "    background-color: rgb(35,35,35); /* Background color */\n"
      "    color: rgb(200, 200, 200); /* Text color */\n"
      "}\n"
      "\n"
      "QLineEdit:focus {\n"
      "    border: 1px solid #FF2200; /* Border color when QLineEdit is "
      "focused */\n"
      "    background-color: rgb(35, 35, 35); /* Background color when "
      "QLineEdit is focused */\n"
      "}");
}

void SetDefaultLineEditWidget(QLineEdit *line_edit) {
  line_edit->setStyleSheet(
      "QLineEdit {"
      "border: 1px solid rgb(75, 75, 75); /* Border color and width */"
      "border-radius: 7px; /* Rounded corners */"
      "padding: 1px; /* Padding inside the QLineEdit */"
      "background-color: rgb(35,35,35); /* Background color */"
      "color: rgb(230, 230, 230); /* Text color */"
      "font-size: 8pt;"
      "} "
      "QLineEdit:focus {"
      "border: 1px solid #FF8800; /* Border color when QLineEdit is focused */"
      "background-color: rgb(35, 35, 35); /* Background color when QLineEdit "
      "is focused */"
      "}");
}

void SetIncorrectLineEditWidget(QLineEdit *line_edit) {
  line_edit->setStyleSheet(
      "QLineEdit {"
      "border: 1px solid #FF2200; /* Border color and width */"
      "border-radius: 7px; /* Rounded corners */"
      "padding: 1px; /* Padding inside the QLineEdit */"
      "background-color: rgb(35,35,35); /* Background color */"
      "color: rgb(230, 230, 230); /* Text color */"
      "font-size: 8pt;"
      "} "
      "QLineEdit:focus {"
      "border: 1px solid #FF2200; /* Border color when QLineEdit is focused */"
      "background-color: rgb(35, 35, 35); /* Background color when QLineEdit "
      "is focused */"
      "}");
}

void SetDefaultPushButtonWidget(QPushButton *push_button) {
  push_button->setStyleSheet(
      "QPushButton { "
      "background-color: rgb(75, 75, 75); /* Background color */"
      "color: #FFF; /* Text color */ "
      "border: 1px solid rgb(100, 100, 100); /* Border color and width */ "
      "border-radius: 7px; /* Rounded corners */ "
      "padding: 1px; /* Padding inside the button */ "
      "font-size: 11pt; "
      "}"
      "QPushButton:hover {"
      "background-color: rgb(85, 85, 85); /* Background color on hover */"
      "border: 1px solid #FF8800; /* Border color on hover */"
      "} "
      "QPushButton:pressed {"
      "background-color: rgb(65, 65, 65); /* Background color when pressed */"
      "border: 1px solid #FF8800; /* Border color on hover */"
      "}");
}

void SetIncorrectPushButtonWidget(QPushButton *push_button) {
  push_button->setStyleSheet(
      "QPushButton { "
      "background-color: rgb(75, 75, 75); /* Background color */"
      "color: #FFF; /* Text color */ "
      "border: 1px solid rgb(138, 47, 48); /* Border color and width */ "
      "border-radius: 7px; /* Rounded corners */ "
      "padding: 1px; /* Padding inside the button */ "
      "font-size: 11pt; "
      "}"
      "QPushButton:hover {"
      "background-color: rgb(85, 85, 85); /* Background color on hover */"
      "border: 1px solid #FF2200; /* Border color on hover */"
      "} "
      "QPushButton:pressed {"
      "background-color: rgb(65, 65, 65); /* Background color when pressed */"
      "border: 1px solid #FF2200; /* Border color on hover */"
      "}");
}

void SetDefaultWidgetComboBox(QComboBox *combo_box) {
  combo_box->setStyleSheet(
      "/* Apply the style to the QComboBox */ "
      "QComboBox {"
      "border: 1px solid rgb(100,100,100); /* Border style and color */"
      "border-radius: 7px; /* Rounded corners */"
      "/*padding: 0px ; /* Padding inside the combo box */"
      "background-color: rgb(35,35,35); /* Background color */"
      "color: rgb(230,230,230); /* Text color */"
      "selection-color: #FFF; /* Selected text color */"
      "selection-background-color: #FF8800; /* Selected background color */"
      "font-size: 10pt;"
      "}"

      "/* Dropdown button style */"
      "QComboBox::drop-down {"
      "width: 50px;"
      "border: none; /* Remove the drop-down button border */"
      "background-color: ; /* Transparent background */"
      "}"

      "/* Dropdown list style */"
      "QComboBox QAbstractItemView {"
      "border: 0px solid #ccc; /* Border style and color for the dropdown list "
      "*/"
      "border-radius: 5px; /* Rounded corners for the dropdown list */"
      "background-color: rgb(35,35,35); /* Background color for the dropdown "
      "list */"
      "color: rgb(230,230,230); /* Text color */"
      "selection-background-color: rgb(55,55,55); /* Selected item background "
      "color */"
      "}"

      "/* Hover effect for dropdown list items */"
      "QComboBox QAbstractItemView::item:hover {"
      "background-color: #FF8800; /* Background color when hovering over items "
      "*/"
      "}");
}

void SetDefaultDateEditWidget(QDateEdit *date_edit) {
  date_edit->setStyleSheet(
      "QDateEdit {"
      "border: 1px solid rgb(100 ,100, 100); /* Border color and width */"
      "border-radius: 7px; /* Rounded corners */"
      "padding: 1px; /* Padding inside the QLineEdit */"
      "background-color: rgb(35,35,35); /* Background color */"
      "color: rgb(230, 230, 230); /* Text color */"
      "font-size: 10pt;"
      "}"
      "QDateEdit:focus {"
      "border: 1px solid #FF8800; /* Border color when QLineEdit is focused */"
      "background-color: rgb(35, 35, 35); /* Background color when QLineEdit "
      "is focused */"
      "}");
}

void SetDefaultLineEditDeposit(QLineEdit *line_edit) {
  line_edit->setStyleSheet(
      "    QLineEdit {"
      "border: 1px solid rgb(100, 100, 100); /* Border color and width */"
      "border-radius: 10px; /* Rounded corners */"
      "padding: 1px; /* Padding inside the QLineEdit */"
      "background-color: rgb(35,35,35); /* Background color */"
      "color: rgb(200, 200, 200); /* Text color */"
      "}"
      "QLineEdit:focus {"
      "border: 1px solid #FF8800; /* Border color when QLineEdit is focused */"
      "background-color: rgb(35, 35, 35); /* Background color when QLineEdit "
      "is focused */"
      "}");
}

void SetIncorrectLineEditDeposit(QLineEdit *line_edit) {
  line_edit->setStyleSheet(
      "    QLineEdit {"
      "border: 1px solid #FF2200; /* Border color and width */"
      "border-radius: 10px; /* Rounded corners */"
      "padding: 1px; /* Padding inside the QLineEdit */"
      "background-color: rgb(35,35,35); /* Background color */"
      "color: rgb(200, 200, 200); /* Text color */"
      "}"
      "QLineEdit:focus {"
      "border: 1px solid #FF2200; /* Border color when QLineEdit is focused */"
      "background-color: rgb(35, 35, 35); /* Background color when QLineEdit "
      "is focused */"
      "}");
}

}  // namespace s21::style_handler
