/*
 * ComputerMonitoringView.h - provides a view with computer monitor thumbnails
 *
 * Copyright (c) 2017-2020 Tobias Junghans <tobydox@veyon.io>
 *
 * This file is part of Veyon - https://veyon.io
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */

#pragma once

#include "ComputerControlInterface.h"

class ComputerMonitoringModel;
class VeyonMaster;

// clazy:excludeall=copyable-polymorphic

class ComputerMonitoringView
{
public:
	static constexpr int MinimumComputerScreenSize = 50;
	static constexpr int MaximumComputerScreenSize = 1000;
	static constexpr int DefaultComputerScreenSize = 150;

	ComputerMonitoringView();
	virtual ~ComputerMonitoringView() = default;

	void initializeView();

	void saveConfiguration();

	virtual ComputerControlInterfaceList selectedComputerControlInterfaces() const = 0;
	ComputerControlInterfaceList filteredComputerControlInterfaces() const;

	QString searchFilter() const;
	void setSearchFilter( const QString& searchFilter );

	void setFilterPoweredOnComputers( bool enabled );

	QStringList groupFilter() const;
	void setGroupFilter( const QStringList& groups );

	void setComputerScreenSize( int size );
	int computerScreenSize() const;

	virtual void alignComputers() = 0;

protected:
	virtual void setColors( const QColor& backgroundColor, const QColor& textColor ) = 0;
	virtual QJsonArray saveComputerPositions() = 0;
	virtual bool useCustomComputerPositions() = 0;
	virtual void loadComputerPositions( const QJsonArray& positions ) = 0;
	virtual void setUseCustomComputerPositions( bool enabled ) = 0;
	virtual void setIconSize( const QSize& size ) = 0;

	VeyonMaster* master() const
	{
		return m_master;
	}

	void runFeature( const Feature& feature );

	ComputerMonitoringModel* listModel() const;

	FeatureUidList activeFeatures( const ComputerControlInterfaceList& computerControlInterfaces );

private:
	VeyonMaster* m_master{nullptr};
	int m_computerScreenSize{DefaultComputerScreenSize};

};
