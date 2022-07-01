/**
Copyright  (c) 2021-2022 Jacob Osborne

  this file is part of game speak game speak is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QCoreApplication::setApplicationVersion("0.1");
    QApplication::setApplicationName("game speak");
    qInfo() << "Using Qt" << qVersion();
    QSettings settings(QCoreApplication::applicationName());
    MainWindow w;
    w.show();
    return QApplication::exec();
}
