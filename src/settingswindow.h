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

#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QHotkey>
#include <QSettings>
#include <QDialog>
#include <QMessageBox>
#include <QTextToSpeech>

namespace Ui {
    class settingswindow;
}

class settingswindow : public QDialog {
Q_OBJECT

public:
    explicit settingswindow(QWidget *parent = nullptr);

    ~settingswindow();

    QHotkey *SpeakHotkey;
    QTextToSpeech *m_speech;

public slots:

    void load();

    void save();

private slots:

    [[maybe_unused]] void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::settingswindow *ui;

    void hideEvent(QHideEvent *event);;

    void showEvent(QShowEvent *event);
};

#endif // SETTINGSWINDOW_H
