/***************************************************************************
 *   Copyright (C) 2007 by Jean-Baptiste Mardelle (jb@kdenlive.org)        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA          *
 ***************************************************************************/


#ifndef MONITOR_H
#define MONITOR_H

#include <KIcon>
#include <KAction>
#include <KRestrictedLine>
#include <QDomElement>

#include "ui_monitor_ui.h"

class MonitorManager;
class Render;
class SmallRuler;
class DocClipBase;

class MonitorRefresh : public QWidget {
    Q_OBJECT
public:
    MonitorRefresh(QWidget* parent);
    virtual void paintEvent(QPaintEvent * event);
    void setRenderer(Render* render);
private:
    Render *m_renderer;
};

class Monitor : public QWidget {
    Q_OBJECT

public:
    Monitor(QString name, MonitorManager *manager, QWidget *parent = 0);
    Render *render;
    void resetProfile();
    QString name() const;
    void resetSize();

protected:
    virtual void mousePressEvent(QMouseEvent * event);
    virtual void wheelEvent(QWheelEvent * event);
//    virtual void resizeEvent(QResizeEvent * event);
//    virtual void paintEvent(QPaintEvent * event);

private:
    Ui::Monitor_UI ui;
    MonitorManager *m_monitorManager;
    MonitorRefresh *m_monitorRefresh;
    QString m_name;
    double m_scale;
    int m_length;
    int m_position;
    SmallRuler *m_ruler;
    KIcon m_playIcon;
    KIcon m_pauseIcon;
    bool m_isActive;
    KRestrictedLine *m_timePos;
    QAction *m_playAction;
    QMenu *m_contextMenu;
    DocClipBase *m_currentClip;

private slots:
    void adjustRulerSize(int length);
    void seekCursor(int pos);
    void rendererStopped(int pos);
    void slotExtractCurrentFrame();
    void slotSetThumbFrame();
    void slotSetSizeOneToOne();
    void slotSetSizeOneToTwo();

public slots:
    void slotOpenFile(const QString &);
    void slotSetXml(DocClipBase *clip, const int position = -1);
    void initMonitor();
    void refreshMonitor(bool visible);
    void slotSeek(int pos);
    void stop();
    void start();
    void activateMonitor();
    void slotPlay();
    void slotForward(double speed = 0);
    void slotRewind(double speed = 0);
    void slotRewindOneFrame();
    void slotForwardOneFrame();
    void saveSceneList(QString path, QDomElement info = QDomElement());
    void slotStart();
    void slotEnd();

signals:
    void renderPosition(int);
    void durationChanged(int);
    void refreshClipThumbnail(const QString &);
    void adjustMonitorSize();
};

#endif
