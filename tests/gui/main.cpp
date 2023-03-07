#include "actionsaccesscheckertest.h"
#include "availablepackagescolumntest.h"
#include "installedpackagescolumntest.h"
#include "mainwindowtest.h"
#include "packagestoupdatecolumntest.h"
#include "settingstest.h"
#include "checkcommandparsertest.h"
#include "checkpackagetest.h"
#include "choicewindowtest.h"
#include "downloadcommandparsertest.h"
#include "installcommandparsertest.h"
#include "loggertest.h"
#include "outputfiltertest.h"
#include "packagedownloadertest.h"
#include "packageinputwindowtest.h"
#include "packagesearchtest.h"
#include "pathconvertertest.h"
#include "previewdesigntest.h"
#include "processtest.h"
#include "progressviewtest.h"
#include "qicommandparsertest.h"
#include "qipackagetest.h"
#include "searchallcommandparsertest.h"
#include "sicommandparsertest.h"
#include "sipackagetest.h"
#include "sizeconvertertest.h"
#include "statisticscommandparsertest.h"
#include "statisticswindowtesttest.h"
#include "systemtraytest.h"
#include "timeconvertertest.h"
#include "defstest.h"

#include <QApplication>
#include <KCrash>
#include <KDBusService>


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    KLocalizedString::setApplicationDomain("pak-gui");
    KCrash::initialize();

    KDBusService appDBusService(KDBusService::Multiple | KDBusService::NoExitOnFailure);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, false);
    QLoggingCategory::defaultCategory()->setEnabled(QtInfoMsg, true);

    int status = 0;
    QTest::setMainSourcePath(__FILE__, QT_TESTCASE_BUILDDIR);
    auto ASSERT_TEST = [&status, argc, argv](QObject* obj) {
      status |= QTest::qExec(obj, argc, argv);
      delete obj;
    };

    ASSERT_TEST(new TestActionsAccessChecker());
    ASSERT_TEST(new TestAvailablePackagesColumn());
    ASSERT_TEST(new TestInstalledPackagesColumn());

    ASSERT_TEST(new TestMainWindow());
    ASSERT_TEST(new TestUpdatedPackagesColumn());
    ASSERT_TEST(new TestSettingsWindow());

    ASSERT_TEST(new TestCheckCommandParser());
    ASSERT_TEST(new TestCheckPackage());
    ASSERT_TEST(new TestChoiceWindow());

    ASSERT_TEST(new TestDefs());

    ASSERT_TEST(new TestDownloadCommandParser());
    ASSERT_TEST(new TestInstallCommandParser());
    ASSERT_TEST(new TestLogger());

    ASSERT_TEST(new TestOutputFilter());
    //ASSERT_TEST(new TestPackageDownloader()); //C
    ASSERT_TEST(new TestPackageInputWindow());

    //ASSERT_TEST(new TestPackageSearch()); //C
    ASSERT_TEST(new TestPathConverter());
    ASSERT_TEST(new TestPreviewDesign());

    //ASSERT_TEST(new TestProcess()); //C
    ASSERT_TEST(new TestProgressView());
    ASSERT_TEST(new TestQiCommandParser());

    ASSERT_TEST(new TestQiPackage());
    ASSERT_TEST(new TestSearchAllCommandParser());
    ASSERT_TEST(new TestSiCommandParser());

    ASSERT_TEST(new TestSiPackage());
    ASSERT_TEST(new TestSizeConverter());
    ASSERT_TEST(new TestStatisticsCommandParser());

    ASSERT_TEST(new TestStatisticsWindow());
    ASSERT_TEST(new TestSystemTray());
    ASSERT_TEST(new TestTimeConverter());



    qDebug() << "Status: " << status;
    return 0;
}

