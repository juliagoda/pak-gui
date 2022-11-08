#pragma once

#include "packageinputwindow.h"
#include "choicewindow.h"
#include "downloadcommandparser.h"

#include <QString>
#include <QSharedPointer>
#include <QMessageBox>


class DownloaderWindow : public QObject
{
    Q_OBJECT

public:
  virtual QSharedPointer<DownloaderWindow>& setNext(QSharedPointer<DownloaderWindow>& new_window) = 0;
  virtual bool handle(const QStringList& new_answer) = 0;
};


class PackageDownloader : public DownloaderWindow
{
    Q_OBJECT

 private:
  QSharedPointer<DownloaderWindow> next_window;

 public:
  PackageDownloader() :
      next_window(nullptr)
  {}

  QSharedPointer<DownloaderWindow>& setNext(QSharedPointer<DownloaderWindow>& new_window) override
  {
    this->next_window.reset(new_window.get());
    return this->next_window;
  }

  bool handle(const QStringList& new_answer) override
  {
    if (this->next_window)
      return this->next_window->handle(new_answer);

    return true;
  }
};


class AutomaticInstallation : public PackageDownloader
{
    Q_OBJECT

public:
  AutomaticInstallation(QSharedPointer<DownloadCommandParser>& new_download_command_parser) :
      PackageDownloader(),
      download_command_parser(new_download_command_parser.get())
  {}

  bool handle(const QStringList& new_answer) override
  {
      Q_UNUSED(new_answer)
      bool answer = true;
      int answer_gui = QMessageBox::information(new QWidget, tr("Downloader's option"),
                                            tr("Do you want to install chosen package automatically after download?"),
                                            QMessageBox::Yes | QMessageBox::No);

      if (static_cast<QMessageBox::StandardButton>(answer_gui) == QMessageBox::No)
          answer = false;

      download_command_parser->updateParameter(answer ? QString("pak -GB") : QString("pak -G"));
      return PackageDownloader::handle(QStringList());
  }

private:
  QSharedPointer<DownloadCommandParser> download_command_parser;
};


class PackageInput : public PackageDownloader
{
    Q_OBJECT

public:
    PackageInput(QSharedPointer<DownloadCommandParser>& new_download_command_parser) :
        PackageDownloader(),
        download_command_parser(new_download_command_parser.get())
    {}

  bool handle(const QStringList& new_answer) override
  {
      Q_UNUSED(new_answer)
      QSharedPointer<PackageInputWindow> package_input_window(new PackageInputWindow(), &QObject::deleteLater);
      auto result = connect(package_input_window.data(), &PackageInputWindow::packageNameInserted, [this](const QString& new_package_name)
      {
          download_command_parser->updatePackageName(new_package_name);
          return PackageDownloader::handle(download_command_parser->getPaths());
      });

      // TODO - Stop flow

      return result;
  }

private:
  QSharedPointer<DownloadCommandParser> download_command_parser;
};


class PathsChoiceInput : public PackageDownloader
{
    Q_OBJECT

public:
    PathsChoiceInput(QSharedPointer<DownloadCommandParser>& new_download_command_parser) :
        PackageDownloader(),
        download_command_parser(new_download_command_parser.get())
    {}

  bool handle(const QStringList& new_answer) override
  {
      QSharedPointer<ChoiceWindow> choice_window(new ChoiceWindow(tr("Choose path for package save"), new_answer), &QObject::deleteLater);
      auto result = connect(choice_window.data(), &ChoiceWindow::choiceDefined, [this](int new_index)
      {
          download_command_parser->inputAnswer(QString::number(new_index));
          return PackageDownloader::handle(download_command_parser->retrieveInfo());
      });

      // TODO - Stop flow

      return result;
  }

private:
  QSharedPointer<DownloadCommandParser> download_command_parser;
};


class ReposChoiceInput : public PackageDownloader
{
    Q_OBJECT

public:
    ReposChoiceInput(QSharedPointer<DownloadCommandParser>& new_download_command_parser) :
        PackageDownloader(),
        download_command_parser(new_download_command_parser.get())
    {}

  bool handle(const QStringList& new_answer) override
  {
      QSharedPointer<ChoiceWindow> choice_window(new ChoiceWindow(tr("Choose repo for package download"), new_answer), &QObject::deleteLater);
      auto result = connect(choice_window.data(), &ChoiceWindow::choiceDefined, [this](int new_index)
      {
          download_command_parser->inputAnswer(QString::number(new_index));
          return true;
      });

      // TODO - Stop flow

      return result;
  }

private:
  QSharedPointer<DownloadCommandParser> download_command_parser;
};
