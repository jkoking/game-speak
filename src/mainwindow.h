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

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//QT Based includes
#include <QGuiApplication>
#include <QMainWindow>
#include <QScreen>
#include <QWindow>
#include <QTextToSpeech>
#include <QLocale>
#include <QDebug>

//standard library includes
#include <thread>
#include <string>
#include <iostream>

//misc library includes
#include <opencv2/opencv.hpp>
#include <leptonica/allheaders.h>
#include <tesseract/baseapi.h>

//project based includes
#include "settingswindow.h"
#include "include/asmOpenCV.h"
#include "aboutwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

    settingswindow *SW;
    Aboutwindow *AW;

private slots:

    void on_settingsButton_clicked() const;

    void stateChanged(QTextToSpeech::State state);

    void Screenshot();

    void speak();

    void on_aboutButton_clicked() const;

private:
    Ui::MainWindow *ui;

    void closeEvent(QCloseEvent *event) override;

    static void set_language_native(int id, QString &ctess);
};

#endif // MAINWINDOW_H

#pragma clang diagnostic pop