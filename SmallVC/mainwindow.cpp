#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    videoFolder = QStandardPaths::locate(
                QStandardPaths::MoviesLocation,
                QString(),
                QStandardPaths::LocateDirectory);

    connect (&commandProcess, SIGNAL(readyReadStandardOutput()),this, SLOT(outputCommand()));
    connect (&commandProcess, SIGNAL(readyReadStandardError()),this, SLOT(outputCommand()));
    connect (&commandProcess, SIGNAL(finished(int,QProcess::ExitStatus)),this, SLOT(on_processExit(int,QProcess::ExitStatus)));

    ui->setupUi(this);

    statusBar()->setStyleSheet("color: blue;");
    statusBar()->showMessage(tr(" Author: DimiG, 2015. Version: 1.0"), 6500);

    indicator = new QMovie(":/icons/images/loader_32x32_anim.gif");
    indicator->setSpeed(90);

    ui->labelIndicator->clear();
// Check if indicator is running well ;)
//    indicator->start();
//    ui->labelIndicator->setMovie(indicator);

    setMP4();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//  About Information CALL
void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, tr("Video Converter"),tr("Author: DimiG, 2015. Version: 1.0"));
}

void MainWindow::executeCommand()
{
//  Converting START
    QStringList args;

//  Check if input line is EMPTY
    QString input = ui->sourcePath->text();
    if(input.isEmpty()) {
        QMessageBox::information(this,
                     tr("Video Converter"),tr("Input file is not specified"));
        return;
    }

//  Check if output line is EMPTY
    QString output = ui->destPath->text();
    if(output.isEmpty()) {
        QMessageBox::information(this,
                     tr("Video Converter"),tr("Output file is not specified"));
        return;
    }

//  Check if destination file exist (not using)
    QString fileName = ui->destPath->text();

    if (QFile::exists(fileName)) {
                QFile::remove(fileName);
    }

//  Create the arguments string
    if (ui->radioBtn1->isChecked()) { // Convert to MP4

        args << "-i";

        args << ui->sourcePath->text();

        args << "-c:v"; args << ui->comboCodec->currentText();
        args << "-preset"; args << "slow";

        args << "-b:v"; args << ui->comboBitrate->currentText();

        if (ui->comboResolution->currentText() != "auto") {
            args << "-s"; args << ui->comboResolution->currentText();
        }

        args << "-aspect"; args << ui->comboAspect->currentText();

        args << ui->destPath->text();

    }

    if (ui->radioBtn2->isChecked()) { // Convert to DV-PAL/DV-NTSC

        args << "-i";

        args << ui->sourcePath->text();

        args << "-target"; args << ui->comboCodec->currentText();

        args << ui->destPath->text();

    }

    if (ui->radioBtn3->isChecked()) { // Convert to MOV

        args << "-i";

        args << ui->sourcePath->text();

        if (ui->comboCodec->currentText() == "auto") {
            args << "-c"; args << "copy";
        } else {
            args << "-c:v"; args << ui->comboCodec->currentText();
            args << "-qscale"; args << "1";
            args << "-b:v"; args << ui->comboBitrate->currentText();
        }

        args << ui->destPath->text();
    }

    if (ui->radioBtn4->isChecked()) { // Convert to audio MP3

        args << "-i";

        args << ui->sourcePath->text();

        args << "-vn";
        args << "-ar"; args << ui->comboSamplerate->currentText();
        args << "-ac"; args << ui->comboAChannel->currentText();
        args << "-ab"; args << ui->comboABitrate->currentText();
        args << "-f"; args << ui->comboACodec->currentText();

        args << ui->destPath->text();

    }

//  If arguments string is empty - error
    if(args.isEmpty()) {

        QMessageBox::warning(this,tr("Video Converter"),tr("Arguments are empty!"));
        return;

    }

//  Block some buttons
    ui->goBtn->setDisabled(true);
    ui->closeBtn->setDisabled(true);

//  Status BAR message
    statusBar()->setStyleSheet("color: red;");
    statusBar()->showMessage(tr(" Encoding in progress..."));

    indicator->start();
    ui->labelIndicator->setMovie(indicator);


//  Execute the command
    commandProcess.start("ffmpeg", args);
}


//  Diagnostic message output to text browser
void MainWindow::outputCommand()
{
    QByteArray cmdoutput = commandProcess.readAllStandardOutput();
    QString txtoutput = cmdoutput;

    ui->textBrowser->append(txtoutput);

    cmdoutput = commandProcess.readAllStandardError();
    txtoutput = cmdoutput;

    ui->textBrowser->append(txtoutput);
}

//  Set source PATH for file
void MainWindow::setSource()
{
    QString file = QFileDialog::getOpenFileName(
                this,
                tr("Select Source File"),
                videoFolder,
                tr("Video (*.mp4 *.mov *.avi *.dv)"));
    if(!file.isEmpty()) {
        ui->sourcePath->setText(file);
    }

}

//  Set destination PATH for file
void MainWindow::setDestination()
{
    if (ui->radioBtn1->isChecked()) {  // MP4
        QString file = QFileDialog::getSaveFileName(
                    this,
                    tr("Select Destination"),
                    videoFolder,
                    tr("Video (*.mp4)"));

        if (!file.isEmpty()) {
            ui->destPath->setText(file);
        }
    }

    if (ui->radioBtn2->isChecked()) {  // DV
        QString file = QFileDialog::getSaveFileName(
                    this,
                    tr("Select Destination"),
                    videoFolder,
                    tr("Video (*.dv)"));

        if (!file.isEmpty()) {
            ui->destPath->setText(file);
        }
    }

    if (ui->radioBtn3->isChecked()) {  // MOV
        QString file = QFileDialog::getSaveFileName(
                    this,
                    tr("Select Destination"),
                    videoFolder,
                    tr("Audio (*.mov)"));

        if (!file.isEmpty()) {
            ui->destPath->setText(file);
        }
    }

    if (ui->radioBtn4->isChecked()) {  // MP3
        QString file = QFileDialog::getSaveFileName(
                    this,
                    tr("Select Destination"),
                    videoFolder,
                    tr("Audio (*.mp3)"));

        if (!file.isEmpty()) {
            ui->destPath->setText(file);
        }
    }
}

//  If process complete DO
void MainWindow::on_processExit(int exitCode, QProcess::ExitStatus exitStatus)
{
    ui->goBtn->setDisabled(false);
    ui->closeBtn->setDisabled(false);

    indicator->stop();
    ui->labelIndicator->clear();

    if (exitCode) {
        qDebug() << "Process interrupted!!!" << exitCode << "\t" << exitStatus;
        statusBar()->setStyleSheet("color: red;");
        statusBar()->showMessage(tr(" Encoding interrupted..."), 6500);

        QMessageBox::warning(this, tr("Video Converter"),tr("Process interrupted!!!"));
    } else {
        statusBar()->setStyleSheet("color: green;");
        statusBar()->showMessage(tr(" Encoding complete..."), 6500);

        QMessageBox::information(this, tr("Video Converter"),tr("Encoding complete!!!"));
    }

}

//  If process Canceled DO
void MainWindow::on_processCancel()
{
    ui->goBtn->setDisabled(false);
    ui->closeBtn->setDisabled(false);
    commandProcess.kill();
}

// Set combobox params
void MainWindow::setMP4()
{
    ui->comboResolution->clear();
    ui->comboAspect->clear();
    ui->comboCodec->clear();
    ui->comboBitrate->clear();
    ui->comboSamplerate->clear();
    ui->comboAChannel->clear();
    ui->comboACodec->clear();
    ui->comboABitrate->clear();

    ui->comboResolution->addItem("auto");
    ui->comboResolution->addItem("1280x720");
    ui->comboResolution->addItem("1024x576");
    ui->comboResolution->addItem("720x576");
    ui->comboAspect->addItem("16:9");
    ui->comboAspect->addItem("4:3");
    ui->comboCodec->addItem("libx264");
    ui->comboBitrate->addItem("1800k");
    ui->comboSamplerate->addItem("44100");
    ui->comboAChannel->addItem("2");
    ui->comboACodec->addItem("aac");
    ui->comboABitrate->addItem("128");
}

void MainWindow::setDV()
{
    ui->comboResolution->clear();
    ui->comboAspect->clear();
    ui->comboCodec->clear();
    ui->comboBitrate->clear();
    ui->comboSamplerate->clear();
    ui->comboAChannel->clear();
    ui->comboACodec->clear();
    ui->comboABitrate->clear();

    ui->comboResolution->addItem("auto");
    ui->comboAspect->addItem("auto");
    ui->comboCodec->addItem("pal-dv");
    ui->comboCodec->addItem("ntsc-dv");
    ui->comboBitrate->addItem("30000k");
    ui->comboSamplerate->addItem("48000");
    ui->comboAChannel->addItem("2");
    ui->comboACodec->addItem("pcm");
    ui->comboABitrate->addItem("auto");
}

void MainWindow::setMOV()
{
    ui->comboResolution->clear();
    ui->comboAspect->clear();
    ui->comboCodec->clear();
    ui->comboBitrate->clear();
    ui->comboSamplerate->clear();
    ui->comboAChannel->clear();
    ui->comboACodec->clear();
    ui->comboABitrate->clear();

    ui->comboResolution->addItem("auto");
    ui->comboAspect->addItem("auto");
    ui->comboCodec->addItem("auto");
    ui->comboCodec->addItem("mjpeg");
    ui->comboBitrate->addItem("auto");
    ui->comboBitrate->addItem("30000k");
    ui->comboSamplerate->addItem("auto");
    ui->comboAChannel->addItem("auto");
    ui->comboACodec->addItem("auto");
    ui->comboABitrate->addItem("auto");
}

void MainWindow::setMP3()
{
    ui->comboResolution->clear();
    ui->comboAspect->clear();
    ui->comboCodec->clear();
    ui->comboBitrate->clear();
    ui->comboSamplerate->clear();
    ui->comboAChannel->clear();
    ui->comboACodec->clear();
    ui->comboABitrate->clear();

    ui->comboSamplerate->addItem("44100");
    ui->comboAChannel->addItem("2");
    ui->comboAChannel->addItem("1");
    ui->comboACodec->addItem("mp3");
    ui->comboABitrate->addItem("128");
}
