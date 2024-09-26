#include <QApplication>

#include "View.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::View view;
  view.show();
  return a.exec();
}
