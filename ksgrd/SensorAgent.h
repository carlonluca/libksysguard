/*
    KSysGuard, the KDE System Guard
   
    Copyright (c) 1999, 2000 Chris Schlaeger <cs@kde.org>
    
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License as
 published by the Free Software Foundation; either version 2 of
 the License or (at your option) version 3 or any later version
 accepted by the membership of KDE e.V. (or its successor approved
 by the membership of KDE e.V.), which shall act as a proxy 
 defined in Section 14 of version 3 of the license.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef KSG_SENSORAGENT_H
#define KSG_SENSORAGENT_H

#include <QObject>
#include <QQueue>
#include <QPointer>


class QString;

namespace KSGRD {

class SensorClient;
class SensorManager;
class SensorRequest;

/**
  The SensorAgent depending on the type of requested connection
  starts a ksysguardd process or connects through a tcp connection to
  a running ksysguardd and handles the asynchronous communication. It
  keeps a list of pending requests that have not been answered yet by
  ksysguardd. The current implementation only allows one pending
  requests. Incoming requests are queued in an input FIFO.
*/
class Q_DECL_EXPORT SensorAgent : public QObject
{
  Q_OBJECT

  public:
    explicit SensorAgent( SensorManager *sm );
    ~SensorAgent() override;

    virtual bool start( const QString &host, const QString &shell,
                        const QString &command = QLatin1String(""), int port = -1 ) = 0;

    /**
      This function should only be used by the SensorManager and
      never by the SensorClients directly since the pointer returned by
      engaged is not guaranteed to be valid. Only the SensorManager knows
      whether a SensorAgent pointer is still valid or not.

      This function sends out a command to the sensor and notifies the
      agent to return the answer to 'client'. The 'id' can be used by the
      client to identify the answer. It is only passed through and never
      used by the SensorAgent. So it can be any value the client suits to
      use.
     */
    void sendRequest( const QString &req, SensorClient *client, int id = 0 );

    virtual void hostInfo( QString &sh, QString &cmd, int &port ) const = 0;

    void disconnectClient( SensorClient *client );

    QString hostName() const;

    bool daemonOnLine() const;
    QString reasonForOffline() const;
	
  Q_SIGNALS:
    void reconfigure( const SensorAgent* );

  protected:
    void processAnswer( const char *buf, int buflen );
    void executeCommand();

    SensorManager *sensorManager();

    void setDaemonOnLine( bool value );

    void setHostName( const QString &hostName );
    void setReasonForOffline(const QString &reasonForOffline);

  private:
    virtual bool writeMsg( const char *msg, int len ) = 0;
    QString mReasonForOffline;

    QQueue< SensorRequest* > mInputFIFO;
    QQueue< SensorRequest* > mProcessingFIFO;
    QList<QByteArray> mAnswerBuffer;  ///A single reply can be on multiple lines.  
    QString mErrorBuffer;
    QByteArray mLeftOverBuffer; ///Any data read in but not terminated is copied into here, awaiting the next load of data

    QPointer<SensorManager> mSensorManager;

    bool mDaemonOnLine;
    QString mHostName;
};

/**
  This auxiliary class is used to store requests during their processing.
*/
class SensorRequest
{
  public:
    SensorRequest( const QString &request, SensorClient *client, int id );
    ~SensorRequest();

    void setRequest( const QString& );
    QString request() const;

    void setClient( SensorClient* );
    SensorClient *client();

    void setId( int );
    int id();

  private:
    QString mRequest;
    SensorClient *mClient = nullptr;
    int mId;
};

}
	
#endif
