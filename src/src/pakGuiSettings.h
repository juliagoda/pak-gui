// This file is generated by kconfig_compiler_kf5 from pakGuiSettings.kcfg.
// All changes you do to this file will be lost.
#ifndef PAKGUISETTINGS_H
#define PAKGUISETTINGS_H

#include <kconfigskeleton.h>
#include <QCoreApplication>
#include <QDebug>

class pakGuiSettings : public KConfigSkeleton
{
  public:

    static pakGuiSettings *self();
    ~pakGuiSettings() override;

    /**
      Set history_store_time_in_days
    */
    static
    void setHistory_store_time_in_days( int v )
    {
      if (!self()->isHistory_store_time_in_daysImmutable())
        self()->mHistory_store_time_in_days = v;
    }

    /**
      Get history_store_time_in_days
    */
    static
    int history_store_time_in_days()
    {
      return self()->mHistory_store_time_in_days;
    }

    /**
      Is history_store_time_in_days Immutable
    */
    static
    bool isHistory_store_time_in_daysImmutable()
    {
      return self()->isImmutable( QStringLiteral( "history_store_time_in_days" ) );
    }

    /**
      Set history_file_size_limit_in_Mb
    */
    static
    void setHistory_file_size_limit_in_Mb( int v )
    {
      if (!self()->isHistory_file_size_limit_in_MbImmutable())
        self()->mHistory_file_size_limit_in_Mb = v;
    }

    /**
      Get history_file_size_limit_in_Mb
    */
    static
    int history_file_size_limit_in_Mb()
    {
      return self()->mHistory_file_size_limit_in_Mb;
    }

    /**
      Is history_file_size_limit_in_Mb Immutable
    */
    static
    bool isHistory_file_size_limit_in_MbImmutable()
    {
      return self()->isImmutable( QStringLiteral( "history_file_size_limit_in_Mb" ) );
    }

    /**
      Set internet_reconnection_time_in_minutes
    */
    static
    void setInternet_reconnection_time_in_minutes( int v )
    {
      if (!self()->isInternet_reconnection_time_in_minutesImmutable())
        self()->mInternet_reconnection_time_in_minutes = v;
    }

    /**
      Get internet_reconnection_time_in_minutes
    */
    static
    int internet_reconnection_time_in_minutes()
    {
      return self()->mInternet_reconnection_time_in_minutes;
    }

    /**
      Is internet_reconnection_time_in_minutes Immutable
    */
    static
    bool isInternet_reconnection_time_in_minutesImmutable()
    {
      return self()->isImmutable( QStringLiteral( "internet_reconnection_time_in_minutes" ) );
    }

    /**
      Set update_check_time_in_days
    */
    static
    void setUpdate_check_time_in_days( int v )
    {
      if (!self()->isUpdate_check_time_in_daysImmutable())
        self()->mUpdate_check_time_in_days = v;
    }

    /**
      Get update_check_time_in_days
    */
    static
    int update_check_time_in_days()
    {
      return self()->mUpdate_check_time_in_days;
    }

    /**
      Is update_check_time_in_days Immutable
    */
    static
    bool isUpdate_check_time_in_daysImmutable()
    {
      return self()->isImmutable( QStringLiteral( "update_check_time_in_days" ) );
    }

    /**
      Set update_check_time_in_hours
    */
    static
    void setUpdate_check_time_in_hours( int v )
    {
      if (!self()->isUpdate_check_time_in_hoursImmutable())
        self()->mUpdate_check_time_in_hours = v;
    }

    /**
      Get update_check_time_in_hours
    */
    static
    int update_check_time_in_hours()
    {
      return self()->mUpdate_check_time_in_hours;
    }

    /**
      Is update_check_time_in_hours Immutable
    */
    static
    bool isUpdate_check_time_in_hoursImmutable()
    {
      return self()->isImmutable( QStringLiteral( "update_check_time_in_hours" ) );
    }

    /**
      Set update_check_time_in_minutes
    */
    static
    void setUpdate_check_time_in_minutes( int v )
    {
      if (!self()->isUpdate_check_time_in_minutesImmutable())
        self()->mUpdate_check_time_in_minutes = v;
    }

    /**
      Get update_check_time_in_minutes
    */
    static
    int update_check_time_in_minutes()
    {
      return self()->mUpdate_check_time_in_minutes;
    }

    /**
      Is update_check_time_in_minutes Immutable
    */
    static
    bool isUpdate_check_time_in_minutesImmutable()
    {
      return self()->isImmutable( QStringLiteral( "update_check_time_in_minutes" ) );
    }

    /**
      Set overwrite_full_history_file
    */
    static
    void setOverwrite_full_history_file( bool v )
    {
      if (!self()->isOverwrite_full_history_fileImmutable())
        self()->mOverwrite_full_history_file = v;
    }

    /**
      Get overwrite_full_history_file
    */
    static
    bool overwrite_full_history_file()
    {
      return self()->mOverwrite_full_history_file;
    }

    /**
      Is overwrite_full_history_file Immutable
    */
    static
    bool isOverwrite_full_history_fileImmutable()
    {
      return self()->isImmutable( QStringLiteral( "overwrite_full_history_file" ) );
    }

    /**
      Set use_system_tray_icon
    */
    static
    void setUse_system_tray_icon( bool v )
    {
      if (!self()->isUse_system_tray_iconImmutable())
        self()->mUse_system_tray_icon = v;
    }

    /**
      Get use_system_tray_icon
    */
    static
    bool use_system_tray_icon()
    {
      return self()->mUse_system_tray_icon;
    }

    /**
      Is use_system_tray_icon Immutable
    */
    static
    bool isUse_system_tray_iconImmutable()
    {
      return self()->isImmutable( QStringLiteral( "use_system_tray_icon" ) );
    }

    /**
      Set background_preview_color
    */
    static
    void setBackground_preview_color( const QColor & v )
    {
      if (!self()->isBackground_preview_colorImmutable())
        self()->mBackground_preview_color = v;
    }

    /**
      Get background_preview_color
    */
    static
    QColor background_preview_color()
    {
      return self()->mBackground_preview_color;
    }

    /**
      Is background_preview_color Immutable
    */
    static
    bool isBackground_preview_colorImmutable()
    {
      return self()->isImmutable( QStringLiteral( "background_preview_color" ) );
    }

    /**
      Set preview_font_color
    */
    static
    void setPreview_font_color( const QColor & v )
    {
      if (!self()->isPreview_font_colorImmutable())
        self()->mPreview_font_color = v;
    }

    /**
      Get preview_font_color
    */
    static
    QColor preview_font_color()
    {
      return self()->mPreview_font_color;
    }

    /**
      Is preview_font_color Immutable
    */
    static
    bool isPreview_font_colorImmutable()
    {
      return self()->isImmutable( QStringLiteral( "preview_font_color" ) );
    }

    /**
      Set preview_font_family
    */
    static
    void setPreview_font_family( const QString & v )
    {
      if (!self()->isPreview_font_familyImmutable())
        self()->mPreview_font_family = v;
    }

    /**
      Get preview_font_family
    */
    static
    QString preview_font_family()
    {
      return self()->mPreview_font_family;
    }

    /**
      Is preview_font_family Immutable
    */
    static
    bool isPreview_font_familyImmutable()
    {
      return self()->isImmutable( QStringLiteral( "preview_font_family" ) );
    }

    /**
      Set preview_font_size
    */
    static
    void setPreview_font_size( int v )
    {
      if (!self()->isPreview_font_sizeImmutable())
        self()->mPreview_font_size = v;
    }

    /**
      Get preview_font_size
    */
    static
    int preview_font_size()
    {
      return self()->mPreview_font_size;
    }

    /**
      Is preview_font_size Immutable
    */
    static
    bool isPreview_font_sizeImmutable()
    {
      return self()->isImmutable( QStringLiteral( "preview_font_size" ) );
    }

    /**
      Set packages_info_available
    */
    static
    void setPackages_info_available( const QStringList & v )
    {
      if (!self()->isPackages_info_availableImmutable())
        self()->mPackages_info_available = v;
    }

    /**
      Get packages_info_available
    */
    static
    QStringList packages_info_available()
    {
      return self()->mPackages_info_available;
    }

    /**
      Is packages_info_available Immutable
    */
    static
    bool isPackages_info_availableImmutable()
    {
      return self()->isImmutable( QStringLiteral( "packages_info_available" ) );
    }

    /**
      Set packages_info_selected
    */
    static
    void setPackages_info_selected( const QStringList & v )
    {
      if (!self()->isPackages_info_selectedImmutable())
        self()->mPackages_info_selected = v;
    }

    /**
      Get packages_info_selected
    */
    static
    QStringList packages_info_selected()
    {
      return self()->mPackages_info_selected;
    }

    /**
      Is packages_info_selected Immutable
    */
    static
    bool isPackages_info_selectedImmutable()
    {
      return self()->isImmutable( QStringLiteral( "packages_info_selected" ) );
    }

    /**
      Set save_logs_into_file
    */
    static
    void setSave_logs_into_file( bool v )
    {
      if (!self()->isSave_logs_into_fileImmutable())
        self()->mSave_logs_into_file = v;
    }

    /**
      Get save_logs_into_file
    */
    static
    bool save_logs_into_file()
    {
      return self()->mSave_logs_into_file;
    }

    /**
      Is save_logs_into_file Immutable
    */
    static
    bool isSave_logs_into_fileImmutable()
    {
      return self()->isImmutable( QStringLiteral( "save_logs_into_file" ) );
    }

    /**
      Set logs_filename
    */
    static
    void setLogs_filename( const QString & v )
    {
      if (!self()->isLogs_filenameImmutable())
        self()->mLogs_filename = v;
    }

    /**
      Get logs_filename
    */
    static
    QString logs_filename()
    {
      return self()->mLogs_filename;
    }

    /**
      Is logs_filename Immutable
    */
    static
    bool isLogs_filenameImmutable()
    {
      return self()->isImmutable( QStringLiteral( "logs_filename" ) );
    }

    /**
      Set logs_filepath
    */
    static
    void setLogs_filepath( const QString & v )
    {
      if (!self()->isLogs_filepathImmutable())
        self()->mLogs_filepath = v;
    }

    /**
      Get logs_filepath
    */
    static
    QString logs_filepath()
    {
      return self()->mLogs_filepath;
    }

    /**
      Is logs_filepath Immutable
    */
    static
    bool isLogs_filepathImmutable()
    {
      return self()->isImmutable( QStringLiteral( "logs_filepath" ) );
    }

    /**
      Set show_debug
    */
    static
    void setShow_debug( bool v )
    {
      if (!self()->isShow_debugImmutable())
        self()->mShow_debug = v;
    }

    /**
      Get show_debug
    */
    static
    bool show_debug()
    {
      return self()->mShow_debug;
    }

    /**
      Is show_debug Immutable
    */
    static
    bool isShow_debugImmutable()
    {
      return self()->isImmutable( QStringLiteral( "show_debug" ) );
    }

    /**
      Set hide_info_logs
    */
    static
    void setHide_info_logs( bool v )
    {
      if (!self()->isHide_info_logsImmutable())
        self()->mHide_info_logs = v;
    }

    /**
      Get hide_info_logs
    */
    static
    bool hide_info_logs()
    {
      return self()->mHide_info_logs;
    }

    /**
      Is hide_info_logs Immutable
    */
    static
    bool isHide_info_logsImmutable()
    {
      return self()->isImmutable( QStringLiteral( "hide_info_logs" ) );
    }

  protected:
    pakGuiSettings();
    friend class pakGuiSettingsHelper;


    // General
    int mHistory_store_time_in_days;
    int mHistory_file_size_limit_in_Mb;
    int mInternet_reconnection_time_in_minutes;
    int mUpdate_check_time_in_days;
    int mUpdate_check_time_in_hours;
    int mUpdate_check_time_in_minutes;
    bool mOverwrite_full_history_file;
    bool mUse_system_tray_icon;

    // ConsolesPreview
    QColor mBackground_preview_color;
    QColor mPreview_font_color;
    QString mPreview_font_family;
    int mPreview_font_size;

    // PackageInfo
    QStringList mPackages_info_available;
    QStringList mPackages_info_selected;

    // Logs
    bool mSave_logs_into_file;
    QString mLogs_filename;
    QString mLogs_filepath;
    bool mShow_debug;
    bool mHide_info_logs;

  private:
};

#endif
