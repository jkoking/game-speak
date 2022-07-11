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

    The code for translating QLocale to tesseract line (139 to 257) written by patrik08 (https://forum.qt.io/topic/81838/qlocale-request-from-country-language-to-language-name-from-this-country-german-de-become-deutsch/4)
*/

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      SW(new settingswindow),
      AW(new Aboutwindow)
{
    ui->setupUi(this);
    connect(ui->speakButton, &QPushButton::clicked, this, &MainWindow::Screenshot);
    connect(SW->SpeakHotkey, &QHotkey::activated, this, &MainWindow::Screenshot);
    connect(SW->m_speech, &QTextToSpeech::stateChanged, this, &MainWindow::stateChanged);
    connect(ui->pauseButton, &QPushButton::clicked, SW->m_speech, &QTextToSpeech::pause);
    connect(ui->playButton, &QPushButton::clicked, SW->m_speech, &QTextToSpeech::resume);
    connect(ui->StopButton, &QPushButton::clicked, SW->m_speech, &QTextToSpeech::stop);
    connect(ui->plainTextEdit, &QPlainTextEdit::textChanged, this, &MainWindow::speak);
    QSettings settings(QCoreApplication::applicationName());
    restoreGeometry(settings.value("MainWindow geometry").toByteArray());
    restoreState(settings.value("mainwindow state").toByteArray());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete SW;
    delete AW;
}

void MainWindow::Screenshot()
{
    ui->plainTextEdit->clear();
    QByteArray Timpgeometry = saveGeometry();
    bool usedButton = false;
    if (sender() == ui->speakButton) {
        usedButton = true;
    }
    hide();
    std::chrono::seconds dura(1);
    std::this_thread::sleep_for(dura);
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap Pixmap = screen->grabWindow(0);
    show();
    if (usedButton) {
        activateWindow();
        raise();
    }
    restoreGeometry(Timpgeometry);
    QLocale qlocale;
    QString qtesslang;
    set_language_native(qlocale.language(), qtesslang);
    QByteArray qba = qtesslang.toLocal8Bit();
    const char *tesslang = qba.data();
    qInfo() << "your language is " << tesslang;
    cv::Mat image = ASM::QPixmapToCvMat(Pixmap, true);
    //cv::imshow("test", image);
    auto *api = new tesseract::TessBaseAPI();
    api->Init(nullptr, tesslang, tesseract::OEM_LSTM_ONLY);
    api->SetPageSegMode(tesseract::PSM_AUTO);
    api->SetVariable("debug_file", "tesseract.log");
    api->SetImage(image.data, image.cols, image.rows, 3, image.step); // NOLINT(cppcoreguidelines-narrowing-conversions)
    std::string outText = api->GetUTF8Text();
    image.release();
    QString Qtexrout = QString::fromLocal8Bit(outText.c_str());
    api->End();
    delete api;
    ui->plainTextEdit->setPlainText(Qtexrout);
}

void MainWindow::stateChanged(QTextToSpeech::State state)
{
    ui->speakButton->setDisabled(state == QTextToSpeech::Speaking);
    ui->settingsButton->setDisabled(state == QTextToSpeech::Speaking);
    ui->aboutButton->setDisabled(state == QTextToSpeech::Speaking);
    SW->SpeakHotkey->blockSignals(state == QTextToSpeech::Speaking);
    ui->settingsButton->setDisabled(state == QTextToSpeech::Speaking);
    ui->StopButton->setEnabled(state == QTextToSpeech::Speaking || state == QTextToSpeech::Paused);
    ui->pauseButton->setEnabled(state == QTextToSpeech::Speaking);
    ui->playButton->setEnabled(state == QTextToSpeech::Paused);
    switch (state) {
        case QTextToSpeech::Ready:
            ui->statusbar->showMessage("Speech stopped...", 2000);
            break;
        case QTextToSpeech::Speaking:
            ui->statusbar->showMessage("Speech started...");
            break;
        case QTextToSpeech::Paused:
            ui->statusbar->showMessage("Speech paused...");
            break;
        case QTextToSpeech::BackendError:
            ui->statusbar->showMessage("Speech error!");
            break;
    }
}

void MainWindow::on_settingsButton_clicked() const
{
    SW->load();
    SW->show();
}

void MainWindow::speak()
{
    SW->m_speech->say(ui->plainTextEdit->toPlainText());
}

void MainWindow::on_aboutButton_clicked() const
{
    AW->show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings(QCoreApplication::applicationName());
    settings.setValue("MainWindow geometry", saveGeometry());
    settings.setValue("MainWindow state", saveState());
    QMainWindow::closeEvent(event);
}

/* int id = (int)QLocale::language()  QString ctess Tesseract dir */
void MainWindow::set_language_native(int id, QString &ctess)
{

    /*  Tesseract has unicode (UTF-8) support, and can recognize more than 100 languages "out of the box".
        download link generator (QString & ctess) */
    switch (id) {
        /* 8 - Arabic  الْعَرَبيّة  */
        case 8 :
            ctess = QStringLiteral("ara");
            break;
            /* 28 - Czech  čeština */
        case 28 :
            ctess = QStringLiteral("ces");
            break;
            /* 29 - Danish dansk */
        case 29 :
            ctess = QStringLiteral("dan");
            break;
            /* 42 - German  deusch */
        case 42 :
            ctess = QStringLiteral("deu");
            break;
            /* el - 43 - Greek Greece  ελληνική/*/
        case 43 :
            ctess = QStringLiteral("ell");
            break;
            /* 31 - English  */
        case 31 :
            ctess = QStringLiteral("eng");
            break;
            /* 111 - Spanish castellà */
        case 111 :
            ctess = QStringLiteral("spa");
            break;
            /* 36 - Finnish suomi */
        case 36 :
            ctess = QStringLiteral("fin");
            break;
            /* 37 - French français */
        case 37 :
            ctess = QStringLiteral("fra");
            break;
            /* he - 48 - Hebrew עִברִית heb */
        case 48 :
            ctess = QStringLiteral("heb");
            break;
            /* hi - 49 - Hindi - India हिन्दी/hin */
        case 49 :
            ctess = QStringLiteral("hin");
            break;
            /* id - 52 - Indonesian - Indonesia bahasa_indonesia/ind */
        case 52 :
            ctess = QStringLiteral("ind");
            break;
            /* it - 58 - Italian Italy taliano */
        case 58 :
            ctess = QStringLiteral("ita");
            break;
            /* ja - 59 - Japanese - Japan 日本語 */
        case 59 :
            ctess = QStringLiteral("jpn");
            break;
            /* ko - 66 - Korean - SouthKorea 한국어 */
        case 66 :
            ctess = QStringLiteral("kor");
            break;
            /*nb - 85 - NorwegianBokmal - Norway norsk */
        case 85 :
            ctess = QStringLiteral("nor");
            break;
            /*nl - 30 - Dutch - Netherlands  Nederlands/nld */
        case 30 :
            ctess = QStringLiteral("nld");
            break;
            /*pl - 90 - Polish - Poland    polski/pol */
        case 90 :
            ctess = QStringLiteral("pol");
            break;
            /*pt - 91 - Portuguese - Brazil+Portigal  português/por */
        case 91 :
            ctess = QStringLiteral("por");
            break;
            /*ro - 95 - Romanian - Romania  română/ron */
        case 95 :
            ctess = QStringLiteral("ron");
            break;
            /*ru - 96 - Russian - Russia   ру́сский/rus */
        case 96 :
            ctess = QStringLiteral("rus");
            break;
            /*sk - 108 - Slovak - Slovakia  slovenský/slk */
        case 108 :
            ctess = QStringLiteral("slk");
            break;
            /*sv - 114 - Swedish - Sweden   svenska/swe */
        case 114 :
            ctess = QStringLiteral("swe");
            break;
            /*th - 120 - Thai - Thailand   ภาษาไทย/tha */
        case 120 :
            ctess = QStringLiteral("tha");
            break;
            /*tr - 125 - Turkish - Turkey   Türkçe/tur */
        case 125 :
            ctess = QStringLiteral("tur");
            break;
            /*zh - 25 - Chinese - China   汉语/chi_sim  chi_vert chi_tra  chi_tra_vert */
        case 25 :
            ctess = QStringLiteral("chi_sim");
            break;
            /* hu - 50 - Hungarian - Hungary     magyar/hun */
        case 50 :
            ctess = QStringLiteral("hun");
            break;
        default:
            ctess = QStringLiteral("null"); //// not having dir

    }
}

#pragma clang diagnostic pop