#pragma once

#include "packageinputwindow.h"
#include "downloadcommandparser.h"
#include "qobjectdefs.h"

#include <QString>
#include <QSharedPointer>
#include <QMessageBox>


class DownloaderWindow : public QObject {

    Q_OBJECT

 public:
  virtual DownloaderWindow* setNext(DownloaderWindow* new_window) = 0;
  virtual bool handle(const QStringList& new_answer) = 0;
};


class PackageDownloader : public DownloaderWindow {

    Q_OBJECT

 private:
  DownloaderWindow* next_window;

 public:
  PackageDownloader() :
      next_window(nullptr)
  {
      bool answer = true;
      int answer_gui = QMessageBox::information(new QWidget, tr("Downloader's option"),
                                            tr("Do you want to install chosen package automatically after download?"),
                                            QMessageBox::Yes | QMessageBox::No);

      if (static_cast<QMessageBox::StandardButton>(answer_gui) == QMessageBox::No)
          answer = false;

      download_command_parser.reset(new DownloadCommandParser("", answer));
  }

  DownloaderWindow* setNext(DownloaderWindow* new_window) override {
    this->next_window = new_window;
    return new_window;
  }

  bool handle(const QStringList& new_answer) override {
    if (this->next_window) {
      return this->next_window->handle(new_answer);
    }

    return false;
  }

protected:
   QSharedPointer<DownloadCommandParser> download_command_parser;
};


class PackageInput : public PackageDownloader {

    Q_OBJECT

public:
  bool handle(const QStringList& new_answer) override
  {
      Q_UNUSED(new_answer)
      QSharedPointer<PackageInputWindow> package_input_window(new PackageInputWindow());
      auto result = connect(package_input_window.data(), &PackageInputWindow::packageNameInserted, [this](const QString& new_package_name)
      {
          download_command_parser->updatePackageName(new_package_name);
          return PackageDownloader::handle(download_command_parser->getPaths());
      });

      return result;
  }
};
class PathsChoiceInput : public PackageDownloader {

    Q_OBJECT

public:
  bool handle(const QStringList& new_answer) override
  {
      QSharedPointer<QWidget> widget(createWindow(new_answer));
      // TODO
      return PackageDownloader::handle(new_answer);
  }

signals:
  void accepted();

private:
  QWidget* createWindow(const QStringList& paths_list)
  {
     QWidget* widget = new QWidget;
     // TODO
     return widget;
  }
};

class ReposChoiceInput : public PackageDownloader {

    Q_OBJECT

public:
  bool handle(const QStringList& new_answer) override
  {
      QSharedPointer<QWidget> widget(createWindow(new_answer));
      // TODO
      return PackageDownloader::handle(new_answer);
  }

signals:
  void accepted();

private:
  QWidget* createWindow(const QStringList& repos_list)
  {
      QWidget* widget = new QWidget;
      // TODO
      return widget;
  }
};


