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

#include "settingswindow.h"
#include "ui_settingswindow.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

settingswindow::settingswindow(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::settingswindow),
      SpeakHotkey(new QHotkey(this)),
      m_speech(new QTextToSpeech(nullptr))
{
    ui->setupUi(this);
    load();
}

settingswindow::~settingswindow()
{
    delete ui;
    delete m_speech;
    delete SpeakHotkey;
}

void settingswindow::save()
{
    QSettings settings(QCoreApplication::applicationName());

    QString newSpeakHotkey = ui->SpeakhotkeyEdit->keySequence().toString();
    settings.setValue("Speak hotky", newSpeakHotkey);

    int newRate = ui->rate->value();
    settings.setValue("rate", newRate);

    int newPitch = ui->pitch->value();
    settings.setValue("pitch", newPitch);

    int newVolume = ui->volume->value();
    settings.setValue("volume", newVolume);
}

void settingswindow::load()
{
    QSettings settings(QCoreApplication::applicationName());
    int rate = settings.value("rate", 0).toInt();
    m_speech->setRate(rate / 10.0);
    ui->rate->setValue(rate);

    int pitch = settings.value("pitch", 0).toInt();
    m_speech->setPitch(pitch / 10.0);
    ui->pitch->setValue(pitch);

    int volume = settings.value("volume", 70).toInt();
    m_speech->setVolume(volume / 100.0);
    ui->volume->setValue(volume);

    QString StrSpeakHotkey = settings.value("Speak hotky", "`").toString();
    ui->SpeakhotkeyEdit->setKeySequence(StrSpeakHotkey);
    if (ui->SpeakhotkeyEdit->keySequence().isEmpty()) {
        this->SpeakHotkey->setShortcut(QKeySequence("`"));
    }
    this->SpeakHotkey->setShortcut(ui->SpeakhotkeyEdit->keySequence(), true);
}

void settingswindow::on_buttonBox_accepted()
{
    if (ui->SpeakhotkeyEdit->keySequence().isEmpty()) {
        QMessageBox::warning(this, "no hotky chosen", "no hotky chosen for speak");
        return;
    }
    save();
    hide();
    load();
}

void settingswindow::on_buttonBox_rejected()
{
    load();
    hide();
}

#pragma clang diagnostic pop