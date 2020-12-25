#include "fenetreprincipale.h"
#define WIDTH (650)
#define HEIGHT (500)
//#define BASE_MP3 ("youtube-dl --extract-audio --audio-format mp3")
//#define BASE_MP4 ("youtube-dl -f mp4")

/**
 * Constructeur
*/
FenetrePrincipale::FenetrePrincipale() : QWidget()
{
        Window_Init();
        Buttons_Init();

        /* adding URL */
        connect(addButton, SIGNAL(clicked()), this, SLOT(addMedia()));

        /* Clicking on Browse button */
        connect(browseButton, SIGNAL(clicked()), this, SLOT(ChooseDestination()));

        /* Clicking on Download button */
        connect(downloadButton, SIGNAL(clicked()), this, SLOT(ExecuteCommand()));

        /* Clicking on Quit button */
        connect(quitButton, SIGNAL(clicked()), this, SLOT(Quit()));
}

/**
 * Initialise tous les boutons
*/
void FenetrePrincipale::Buttons_Init()
{
    layoutPrincipal = new QVBoxLayout;

    /* URL */
    urllabel    = new QLabel("URL",this);
    url         = new QLineEdit;
    layoutUrl   = new QHBoxLayout;

    layoutUrl->addWidget(urllabel);
    layoutUrl->addWidget(url);
    layoutPrincipal->addLayout(layoutUrl);

    /* Browse */
    browseEdit      = new QLineEdit;
    browseButton    = new QPushButton("Browse", this);
    layoutbrowse    = new QHBoxLayout;

    layoutbrowse->addWidget(browseButton);
    layoutbrowse->addWidget(browseEdit);
    layoutPrincipal->addLayout(layoutbrowse);

    /* Type */
    typelabel       = new QLabel("Type:",this);
    listeType       = new QComboBox(this);
    layoutType      = new QHBoxLayout;

    listeType->addItem("MP3");
    listeType->addItem("MP4");
    layoutType->addWidget(typelabel);
    layoutType->addWidget(listeType);
    layoutPrincipal->addLayout(layoutType);

    /* Fenêtre au milieu */
    text        = new QTextEdit("Links to download ... \n");
    layoutText  = new QHBoxLayout;

    layoutText->addWidget(text);
    layoutPrincipal->addLayout(layoutText);

    /* Bottom Buttons */
    downloadButton  = new QPushButton("Download");
    addButton       = new QPushButton("Add");
    layoutbButtons  = new QHBoxLayout;

    layoutbButtons->addWidget(downloadButton);
    layoutbButtons->addWidget(addButton);
    layoutPrincipal->addLayout(layoutbButtons);

    /* Quit Button*/
    quitButton = new QPushButton("Close");
    layoutquitButtons  = new QHBoxLayout;
    layoutquitButtons->addWidget(quitButton);
    layoutPrincipal->addLayout(layoutquitButtons);

    setLayout(layoutPrincipal);

    mediasList = new QMap<QString, QString>;
}

/**
 * Initialise la fenêtre principale
*/
void FenetrePrincipale::Window_Init()
{
    this->setWindowTitle(QApplication::translate("toplevel", "MusicDownloader"));
}


void FenetrePrincipale::addMedia()
{
    QString song;
    song = url->text();

    listeType->currentText() == "MP3" ? (void) mediasList->insert(mediasList->end(), song, "MP3") :\
                                        (void) mediasList->insert(mediasList->end(), song, "MP4");

    if (mediasList->size() == 1) {
        text->clear();
    }
    text->append(song);

    this->repaint();
}

void FenetrePrincipale::ChooseDestination()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/Users", QFileDialog::ShowDirsOnly);
    browseEdit->setText(dir);
}

void FenetrePrincipale::ExecuteCommand()
{
    QProcess process;
    QMap<QString, QString>::iterator media;
    QString command_string = "";
    //Chemin en dur ici, à modifier surement
    QString media_path = "cd " + browseEdit->text() + "; PATH=${PATH}:/usr/local/bin:/usr/local/bin/; ";

    int k = 0;
    for (media = mediasList->begin(); media != mediasList->end(); ++media){
        qDebug() << "Element numero " << k << " = [" << media.key() << ", " << media.value() << "] \n"<< endl;
        k++;

        process.start("sh");
        command_string = media_path;

        //Chemin en dur ici, à modifier surement
        command_string += media.value() == "MP3" ? "youtube-dl --extract-audio --audio-format mp3 \"" : "/usr/local/bin/youtube-dl -f mp4 \"";
        command_string += media.key() + "\" ";

        command_string += ">> logs.txt 2>&1";

        /* Convert QString to *char */
        QByteArray command_byte_array = command_string.toLocal8Bit();
        const char *command_char_ptr = command_byte_array.data();
        process.write(command_char_ptr);

        process.closeWriteChannel();
        process.waitForFinished();

        qDebug() << command_char_ptr;
        QByteArray output = process.readAll();
        process.close();

        command_string = "";
    }
    text->clear();

    this->repaint();
}

void FenetrePrincipale::Quit()
{
    QApplication::quit();
}

FenetrePrincipale::~FenetrePrincipale()
{
    delete url;
    delete urllabel;
    delete layoutUrl;

    /* BROWSE */
    delete browseEdit;
    delete browseButton;
    delete layoutbrowse;

    /* Type */
    delete typelabel;
    delete layoutType;
    delete listeType;

    /* Fenêtre au milieu */
    delete text;
    delete layoutText;

    /* Layouts */
    delete formLayout;
    delete layoutPrincipal;

    /* Bottom Buttons */
    delete downloadButton;
    delete addButton;
    delete quitButton;
    delete layoutbButtons;
    delete layoutquitButtons;
}
