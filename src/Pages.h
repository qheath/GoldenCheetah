#ifndef PAGES_H
#define PAGES_H
#include "GoldenCheetah.h"

#include <QtGui>
#include <QLineEdit>
#include <QComboBox>
#include <QCalendarWidget>
#include <QPushButton>
#include <QTreeWidget>
#include <QTableView>
#include <QModelIndex>
#include <QCheckBox>
#include <QList>
#include "Zones.h"
#include "HrZones.h"
#include <QLabel>
#include <QDateEdit>
#include <QCheckBox>
#include <QValidator>
#include <QGridLayout>
#include <QProgressDialog>
#include "DeviceTypes.h"
#include "DeviceConfiguration.h"
#include "RideMetadata.h"
#include "DataProcessor.h"
#include "Season.h"
#include "SeasonParser.h"

#ifdef GC_HAVE_LIBOAUTH
extern "C" {
#include <oauth.h>
}
#endif

class QGroupBox;
class QHBoxLayout;
class QVBoxLayout;
class ColorsPage;
class IntervalMetricsPage;
class ZonePage;
class HrZonePage;
class SummaryMetricsPage;
class MetadataPage;
class KeywordsPage;
class FieldsPage;
class MeasuresPage;
class Colors;
class RiderPage;
class SeasonsPage;

class GeneralPage : public QWidget
{
    Q_OBJECT
    G_OBJECT

    public:
        GeneralPage(MainWindow *main);
        void saveClicked();


    public slots:
        void browseWorkoutDir();

    private:
        MainWindow *main;

        QComboBox *langCombo;
        QComboBox *unitCombo;
        QComboBox *crankLengthCombo;
        QComboBox *wheelSizeCombo;
        QCheckBox *garminSmartRecord;
        QLineEdit *garminHWMarkedit;
        QLineEdit *hystedit;
        QLineEdit *workoutDirectory;
        QPushButton *workoutBrowseButton;

        QLabel *langLabel;
        QLabel *unitLabel;
        QLabel *warningLabel;
        QLabel *workoutLabel;

        QLabel *perfManSTSLabel;
        QLabel *perfManLTSLabel;
        QLineEdit *perfManSTSavg;
        QLineEdit *perfManLTSavg;
        QCheckBox *showSBToday;
        QIntValidator *perfManSTSavgValidator;
        QIntValidator *perfManLTSavgValidator;
};

class RiderPage : public QWidget
{
    Q_OBJECT
    G_OBJECT


    public:
        RiderPage(QWidget *parent, MainWindow *mainWindow);
        void saveClicked();

    public slots:
        void chooseAvatar();
        void unitChanged(int currentIndex);

    private:
        MainWindow *mainWindow;

        QLineEdit *nickname;
        QDateEdit *dob;
        QComboBox *sex;
        QLabel *weightlabel;
        QComboBox *unitCombo;
        QDoubleSpinBox *weight;
        QTextEdit  *bio;
        QPushButton *avatarButton;
        QPixmap     avatar;
};

class CredentialsPage : public QScrollArea
{
    Q_OBJECT
    G_OBJECT


    public:
        CredentialsPage(QWidget *parent, MainWindow *mainWindow);
        void saveClicked();
        void saveTwitter();

    public slots:
        void authoriseTwitter();

    private:
        MainWindow *mainWindow;

        QLineEdit *tpURL; // url for training peaks.com ... http://www.trainingpeaks.com
        QLineEdit *tpUser;
        QLineEdit *tpPass;
        QComboBox *tpType;
        QPushButton *tpTest;

        QLineEdit *gcURL; // url for gc racing (not available yet)
        QLineEdit *gcUser;
        QLineEdit *gcPass;

        QLineEdit *twitterURL; // url for twitter.com
        QPushButton *twitterAuthorise;
        QLineEdit *twitterPIN;
        char *t_key, *t_secret;

        QLineEdit *stravaURL; // url for strava ... http://www.strava.com
        QPushButton *stravaTest;
        QLineEdit *stravaUser;
        QLineEdit *stravaPass;

        QLineEdit *rideWithGPSUser;
        QLineEdit *rideWithGPSPass;

        QLineEdit *ttbUser;
        QLineEdit *ttbPass;

        QLineEdit *wiURL; // url for withings
        QLineEdit *wiUser;
        QLineEdit *wiPass;

        QLineEdit *zeoURL; // url for myzeo
        QLineEdit *zeoUser;
        QLineEdit *zeoPass;

        QLineEdit *webcalURL; // url for webcal calendar (read only, TP.com, Google Calendar)

        QLineEdit *dvURL; // url for calDAV calendar (read/write, e.g. Google, Hotmail)
        QLineEdit *dvUser;
        QLineEdit *dvPass;
};

class deviceModel : public QAbstractTableModel
{
    Q_OBJECT
    G_OBJECT


     public:
        deviceModel(QObject *parent=0);
        QObject *parent;

        // sets up the headers
        QVariant headerData(int section, Qt::Orientation orientation, int role) const;

        // how much data do we have?
        int rowCount(const QModelIndex &parent) const;
        int columnCount(const QModelIndex &parent) const;

        // manipulate the data - data() gets and setData() sets (set/get might be better?)
        QVariant data(const QModelIndex &index, int role) const;
        bool setData(const QModelIndex &index, const QVariant &value, int role);

        // insert/remove and update
        void add(DeviceConfiguration &);   // add a new DeviceConfiguration
        void del();                        // add a new DeviceConfiguration
        bool insertRows(int position, int rows, const QModelIndex &index=QModelIndex());
        bool removeRows(int position, int rows, const QModelIndex &index=QModelIndex());


        QList<DeviceConfiguration> Configuration;  // the actual data
 };

class DevicePage : public QWidget
{
    Q_OBJECT
    G_OBJECT

    public:
        DevicePage(QWidget *, MainWindow *);
        void saveClicked();

        QTableView *deviceList;

    public slots:
        void devaddClicked();
        void devdelClicked();

    private:
        MainWindow *mainWindow;

        QList<DeviceType> devices;

        QPushButton *addButton;
        QPushButton *delButton;

        QGridLayout *leftLayout;
        QVBoxLayout *rightLayout;

        QGridLayout *inLayout;
        QVBoxLayout *mainLayout;

        deviceModel *deviceListModel;

        QCheckBox   *multiCheck;
};

class IntervalMetricsPage : public QWidget
{
    Q_OBJECT
    G_OBJECT


    public:

        IntervalMetricsPage(QWidget *parent = NULL);

    public slots:

        void upClicked();
        void downClicked();
        void leftClicked();
        void rightClicked();
        void availChanged();
        void selectedChanged();
        void saveClicked();

    protected:

        bool changed;
        QListWidget *availList;
        QListWidget *selectedList;
        QPushButton *upButton;
        QPushButton *downButton;
        QPushButton *leftButton;
        QPushButton *rightButton;
};

class SummaryMetricsPage : public QWidget
{
    Q_OBJECT

    public:

        SummaryMetricsPage(QWidget *parent = NULL);

    public slots:

        void upClicked();
        void downClicked();
        void leftClicked();
        void rightClicked();
        void availChanged();
        void selectedChanged();
        void saveClicked();

    protected:

        bool changed;
        QListWidget *availList;
        QListWidget *selectedList;
        QPushButton *upButton;
        QPushButton *downButton;
        QPushButton *leftButton;
        QPushButton *rightButton;
};


class KeywordsPage : public QWidget
{
    Q_OBJECT
    G_OBJECT


    public:
        KeywordsPage(MetadataPage *parent, QList<KeywordDefinition>);
        void getDefinitions(QList<KeywordDefinition>&);

    public slots:
        void addClicked();
        void upClicked();
        void downClicked();
        void renameClicked();
        void deleteClicked();

        void pageSelected(); // reset the list of fields when we are selected...
        void colorfieldChanged();

    private:

        QTreeWidget *keywords;

        QPushButton *upButton, *downButton, *addButton, *renameButton, *deleteButton;
        QLabel *fieldLabel;
        QComboBox *fieldChooser;

        MetadataPage *parent;
};

class ColorsPage : public QWidget
{
    Q_OBJECT
    G_OBJECT


    public:
        ColorsPage(QWidget *parent);
        void saveClicked();

    public slots:
        void resetClicked();

    private:

        // General stuff
        QCheckBox *antiAliased;
        QCheckBox *shadeZones;
        QDoubleSpinBox *lineWidth;

        // Fonts
        QFontComboBox *def,
                      *titles,
                      *chartmarkers,
                      *chartlabels,
                      *calendar,
                      *popup;

        QComboBox *defaultSize,
                  *titlesSize,
                  *chartmarkersSize,
                  *chartlabelsSize,
                  *calendarSize,
                  *popupSize;

        // Colors
        QTreeWidget *colors;
        const Colors *colorSet;
        QPushButton *reset;
};

class FieldsPage : public QWidget
{
    Q_OBJECT
    G_OBJECT


    public:
        FieldsPage(QWidget *parent, QList<FieldDefinition>);
        void getDefinitions(QList<FieldDefinition>&);

    public slots:
        void addClicked();
        void upClicked();
        void downClicked();
        void renameClicked();
        void deleteClicked();

    private:

        QTreeWidget *fields;

        QPushButton *upButton, *downButton, *addButton, *renameButton, *deleteButton;
};

class ProcessorPage : public QWidget
{
    Q_OBJECT
    G_OBJECT


    public:

        ProcessorPage(MainWindow *main);
        void saveClicked();

    public slots:

        //void upClicked();
        //void downClicked();

    protected:

        MainWindow *main;
        QMap<QString, DataProcessor*> processors;

        QTreeWidget *processorTree;
        //QPushButton *upButton, *downButton;

};

class MetadataPage : public QWidget
{
    Q_OBJECT
    G_OBJECT

    friend class ::KeywordsPage;

    public:

        MetadataPage(MainWindow *);
        void saveClicked();

    public slots:


    protected:

        MainWindow *main;
        bool changed;

        QTabWidget *tabs;
        KeywordsPage *keywordsPage;
        FieldsPage *fieldsPage;
        ProcessorPage *processorPage;

        // local versions for modification
        QList<KeywordDefinition> keywordDefinitions;
        QList<FieldDefinition>   fieldDefinitions;
        QString colorfield;
};

class SchemePage : public QWidget
{
    Q_OBJECT
    G_OBJECT


    public:
        SchemePage(ZonePage *parent);
        ZoneScheme getScheme();
        void saveClicked();

    public slots:
        void addClicked();
        void deleteClicked();
        void renameClicked();

    private:
        ZonePage *zonePage;
        QTreeWidget *scheme;
        QPushButton *addButton, *renameButton, *deleteButton;
};

class CPPage : public QWidget
{
    Q_OBJECT
    G_OBJECT


    public:
        CPPage(ZonePage *parent);

    public slots:
        void addClicked();
        void deleteClicked();
        void defaultClicked();
        void rangeSelectionChanged();
        void addZoneClicked();
        void deleteZoneClicked();
        void zonesChanged();

    private:
        bool active;

        QDateEdit *dateEdit;
        QDoubleSpinBox *cpEdit;

        ZonePage *zonePage;
        QTreeWidget *ranges;
        QTreeWidget *zones;
        QPushButton *addButton, *deleteButton, *defaultButton;
        QPushButton *addZoneButton, *deleteZoneButton;
};

class ZonePage : public QWidget
{
    Q_OBJECT
    G_OBJECT


    public:

        ZonePage(MainWindow *);
        void saveClicked();

        //ZoneScheme scheme;
        Zones zones;

        // Children talk to each other
        SchemePage *schemePage;
        CPPage *cpPage;

    public slots:


    protected:

        MainWindow *main;
        bool changed;

        QTabWidget *tabs;

        // local versions for modification
};

class HrSchemePage : public QWidget
{
    Q_OBJECT
    G_OBJECT


public:
    HrSchemePage(HrZonePage *parent);
    HrZoneScheme getScheme();
    void saveClicked();

    public slots:
    void addClicked();
    void deleteClicked();
    void renameClicked();

private:
    HrZonePage *zonePage;
    QTreeWidget *scheme;
    QPushButton *addButton, *renameButton, *deleteButton;
};


class LTPage : public QWidget
{
    Q_OBJECT
    G_OBJECT


public:
    LTPage(HrZonePage *parent);

    public slots:
    void addClicked();
    void deleteClicked();
    void defaultClicked();
    void rangeSelectionChanged();
    void addZoneClicked();
    void deleteZoneClicked();
    void zonesChanged();

private:
    bool active;

    QDateEdit *dateEdit;
    QDoubleSpinBox *ltEdit;
    QDoubleSpinBox *restHrEdit;
    QDoubleSpinBox *maxHrEdit;

    HrZonePage  *zonePage;
    QTreeWidget *ranges;
    QTreeWidget *zones;
    QPushButton *addButton, *deleteButton, *defaultButton;
    QPushButton *addZoneButton, *deleteZoneButton;
};

class HrZonePage : public QWidget
{
    Q_OBJECT
    G_OBJECT


public:

    HrZonePage(MainWindow *);
    void saveClicked();

    //ZoneScheme scheme;
    HrZones zones;

    // Children talk to each other
    HrSchemePage *schemePage;
    LTPage *ltPage;

    public slots:


protected:

    MainWindow *main;
    bool changed;

    QTabWidget *tabs;

    // local versions for modification
};

class SeasonsPage : public QWidget
{
    Q_OBJECT
    G_OBJECT


    public:
        SeasonsPage(QWidget *parent, MainWindow *main);
        void getDefinitions(QList<Season>&);

    public slots:
        void addClicked();
        void upClicked();
        void downClicked();
        void renameClicked();
        void deleteClicked();
        void clearEdit();
        void saveClicked();

    private:

        QTreeWidget *seasons;
        MainWindow *mainWindow;

        QLineEdit *nameEdit;
        QComboBox *typeEdit;
        QDateEdit *fromEdit, *toEdit;

        QPushButton *upButton, *downButton, *addButton, *renameButton, *deleteButton;

        QList<Season> array;
};

class MeasuresPage : public QWidget
{
    Q_OBJECT
    G_OBJECT


    public:
        MeasuresPage(MainWindow *main);
        void getDefinitions(QList<FieldDefinition>&);

    public slots:
        void addClicked();
        void upClicked();
        void downClicked();
        void renameClicked();
        void deleteClicked();
        void saveClicked();

    private:

        MainWindow *main;
        QTreeWidget *fields;
        QPushButton *upButton, *downButton, *addButton, *renameButton, *deleteButton;
};

#endif
