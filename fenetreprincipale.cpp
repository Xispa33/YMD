#include "fenetreprincipale.h"

/**
 * Window dimensions
*/
#define WIDTH (650)
#define HEIGHT (500)

/**
 * @brief FenetrePrincipale::FenetrePrincipale
 * Constructor
 */
FenetrePrincipale::FenetrePrincipale() : QWidget()
{
        Window_Init();
        Buttons_Init();

        /* adding URL */
        connect(addButton, SIGNAL(clicked()), this, SLOT(addMedia()));

        /* Clicking on Browse button */
        /* This button will pop up a window to select the destination of
        the downloaded files */
        connect(browseButton, SIGNAL(clicked()), this, SLOT(ChooseDestination()));

        /* Clicking on Download button */
        /* This button starts the download of the files */
        connect(downloadButton, SIGNAL(clicked()), this, SLOT(ExecuteCommand()));

        /* Clicking on Quit button */
        connect(quitButton, SIGNAL(clicked()), this, SLOT(Quit()));
}

/**
 * @brief FenetrePrincipale::Buttons_Init
 * Service to initialize of all buttons and layouts
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
 * @brief FenetrePrincipale::Window_Init
 * Service to initialize the main window title
 */
void FenetrePrincipale::Window_Init()
{
    this->setWindowTitle(QApplication::translate("toplevel", "MusicDownloader"));
}

/**
 * @brief FenetrePrincipale::addMedia
 * Service to add a media to the list of medias to download
 */
void FenetrePrincipale::addMedia()
{
    QString song;
    song = url->text();

    /* Adding the song to the media list */
    (void) mediasList->insert(mediasList->end(), song, listeType->currentText());
    /*
    listeType->currentText() == "MP3" ? (void) mediasList->insert(mediasList->end(), song, "MP3") :\
                                        (void) mediasList->insert(mediasList->end(), song, "MP4");
    */
    /* Clearing the message in the middle box when at least 1 media has to be downloaded */
    if (mediasList->size() == 1) {
        text->clear();
    }
    /* Add the url of the song/video in the middle box */
    text->append(song);

    /* Clearing the url text box */
    url->clear();
    this->repaint();
}

/**
 * @brief FenetrePrincipale::ChooseDestination
 * Service to setting the files' future location
 */
void FenetrePrincipale::ChooseDestination()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/Users", QFileDialog::ShowDirsOnly);
    browseEdit->setText(dir);
}

/**
 * @brief FenetrePrincipale::ExecuteCommand
 * Service to download the list of medias
 */
void FenetrePrincipale::ExecuteCommand()
{
    QProcess process;
    QMap<QString, QString>::iterator media;
    QString command_string = "";
    //Chemin en dur ici, à modifier surement
    QString media_path = "cd " + browseEdit->text() + "; PATH=${PATH}:/usr/local/bin:/usr/local/bin/; ";

    //int k = 0;
    /* Loop in the medias list */
    for (media = mediasList->begin(); media != mediasList->end(); ++media){
        //qDebug() << "Element numero " << k << " = [" << media.key() << ", " << media.value() << "] \n"<< endl;
        //k++;
        /* Executing the youtube-dl command inside a shell process */
        process.start("sh");

        command_string = media_path;
        command_string += media.value() == "MP3" ? "youtube-dl --extract-audio --audio-format mp3 \"" : "youtube-dl -f mp4 \"";
        command_string += media.key() + "\" ";
        command_string += ">> logs.txt 2>&1";

        /* Convert QString to *char */
        QByteArray command_byte_array = command_string.toLocal8Bit();
        const char *command_char_ptr = command_byte_array.data();
        process.write(command_char_ptr);

        process.closeWriteChannel();
        process.waitForFinished();

        //qDebug() << command_char_ptr;
        QByteArray output = process.readAll();
        process.close();

        command_string = "";
    }

    /* Clearing the medias list to download in the middle box */
    text->clear();

    this->repaint();
}

/**
 * @brief FenetrePrincipale::Quit
 * Service to exit the application
 */
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
