/*
    KSysGuard, the KDE System Guard

	Copyright (c) 1999, 2000 Chris Schlaeger <cs@kde.org>
	Copyright (c) 2006 John Tapsell <john.tapsell@kdemail.net>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.

*/

#ifndef PROCESSFILTER_H_
#define PROCESSFILTER_H_

#include <QSortFilterProxyModel>
#include <QObject>

class QModelIndex;

#ifdef Q_OS_WIN
// this workaround is needed to make krunner link under msvc
// please keep it this way even if you port this library to have a _export.h header file
#define KSYSGUARD_EXPORT
#else
#define KSYSGUARD_EXPORT Q_DECL_EXPORT
#endif

class KSYSGUARD_EXPORT ProcessFilter : public QSortFilterProxyModel
{
	Q_OBJECT
	Q_ENUMS(State)

  public:
	enum State {AllProcesses=0,AllProcessesInTreeForm, SystemProcesses, UserProcesses, OwnProcesses, ProgramsOnly};
    explicit ProcessFilter(QObject *parent=nullptr) : QSortFilterProxyModel(parent) {mFilter = AllProcesses;}
	~ProcessFilter() override {}
	bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
	State filter() const {return mFilter; }


  public Q_SLOTS:
	void setFilter(State index);

  protected:
	bool filterAcceptsRow( int source_row, const QModelIndex & source_parent ) const override;

	State mFilter;
};

#endif

