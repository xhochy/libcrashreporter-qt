/* === This file is part of Tomahawk Player - <http://tomahawk-player.org> ===
 * 
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *
 *   Tomahawk is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Tomahawk is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Tomahawk. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CRASHREPORTER_H
#define CRASHREPORTER_H

#include <QDialog>
#include <QFile>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QByteArray>

namespace Ui
{
    class CrashReporter;
}


class CrashReporter : public QDialog
{
    Q_OBJECT
    
public:
    CrashReporter( const QUrl& url, const QStringList& argv );
    virtual ~CrashReporter( );

    void setLogo(const QPixmap& logo);

    void setReportData(const QByteArray& name, const QByteArray& content);
    void setReportData(const QByteArray& name, const QByteArray& content, const QByteArray& contentType, const QByteArray& fileName);
    
private:
    Ui::CrashReporter* m_ui;

    QString m_minidump_file_path;
    QNetworkRequest* m_request;
    QNetworkReply* m_reply;
    QUrl m_url;

    QMap < QByteArray, QByteArray > m_formContents;
    QMap < QByteArray, QByteArray > m_formContentTypes;
    QMap < QByteArray, QByteArray > m_formFileNames;

    
public slots:
    void send();
    
private slots:
    void onDone();
    void onProgress( qint64 done, qint64 total );
    void onFail( int error, const QString& errorString );
    void onSendButton();
};

#endif // CRASHREPORTER_H
