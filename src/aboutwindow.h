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

#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QDialog>

namespace Ui {
    class Aboutwindow;
}

class Aboutwindow : public QDialog {
Q_OBJECT

public:
    explicit Aboutwindow(QWidget *parent = nullptr);

    ~Aboutwindow() override;

private:
    Ui::Aboutwindow *ui;

    void hideEvent(QHideEvent *event) override;;

    void showEvent(QShowEvent *event) override;

};

#endif // ABOUTWINDOW_H
