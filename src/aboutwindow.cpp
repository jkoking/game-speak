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

#include <QSettings>
#include "aboutwindow.h"
#include "ui_aboutwindow.h"

Aboutwindow::Aboutwindow(QWidget *parent)
        :
        QDialog(parent),
        ui(new Ui::Aboutwindow) {
    ui->setupUi(this);
}

Aboutwindow::~Aboutwindow() {
    delete ui;
}

void Aboutwindow::hideEvent(QHideEvent *event) {
    QSettings settings(QCoreApplication::applicationName());
    settings.setValue("Aboutwindow geometry", saveGeometry());
    QDialog::hideEvent(event);
}

void Aboutwindow::showEvent(QShowEvent *event) {
    QSettings settings(QCoreApplication::applicationName());
    restoreGeometry(settings.value("Aboutwindow geometry").toByteArray());
    QDialog::showEvent(event);
}