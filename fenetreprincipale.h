#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QProgressBar>
#include <QFileDialog>
#include <QLayout>
#include <QFormLayout>
#include <QLabel>
#include <QComboBox>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <cstdio>
#include <QProcess>
#include <QTextStream>
#include <QDebug>
#include <QMap>
#include <QProcess>
#include <QByteArray>
#include <QStringList>

class FenetrePrincipale : public QWidget
{
    Q_OBJECT
public:
    FenetrePrincipale();
    ~FenetrePrincipale();
signals:

public slots:
    void addMedia();
    void ChooseDestination();
    void ExecuteCommand();
    void Quit();

private:

    /* URL */
    QLineEdit *url;
    QLabel *urllabel;
    QHBoxLayout *layoutUrl;

    /* BROWSE */
    QLineEdit *browseEdit;
    QPushButton *browseButton;
    QHBoxLayout *layoutbrowse;

    /* Type */
    QLabel *typelabel;
    QHBoxLayout *layoutType;
    QComboBox *listeType;

    /* Fenêtre au milieu */
    QTextEdit *text;
    QHBoxLayout *layoutText;

    /* Layouts */
    QFormLayout *formLayout;
    QVBoxLayout *layoutPrincipal;

    /* Bottom Buttons */
    QPushButton *downloadButton;
    QPushButton *addButton;
    QPushButton *quitButton;
    QHBoxLayout *layoutbButtons;
    QHBoxLayout *layoutquitButtons;

    QMap<QString, QString> *mediasList;

    void Buttons_Init();
    void Window_Init();
};

#endif // FENETREPRINCIPALE_H
