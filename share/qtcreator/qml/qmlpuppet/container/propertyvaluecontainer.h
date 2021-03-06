/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company.  For licensing terms and
** conditions see http://www.qt.io/terms-conditions.  For further information
** use the contact form at http://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
****************************************************************************/

#ifndef PROPERTYVALUECONTAINER_H
#define PROPERTYVALUECONTAINER_H

#include <QDataStream>
#include <QMetaType>
#include <QVariant>
#include <QString>

#include "nodeinstanceglobal.h"

namespace QmlDesigner {

class PropertyValueContainer
{
    friend QDataStream &operator>>(QDataStream &in, PropertyValueContainer &container);
    friend bool operator ==(const PropertyValueContainer &first, const PropertyValueContainer &second);
    friend bool operator <(const PropertyValueContainer &first, const PropertyValueContainer &second);

public:
    PropertyValueContainer();
    PropertyValueContainer(qint32 instanceId, const PropertyName &name, const QVariant &value, const TypeName &dynamicTypeName);

    qint32 instanceId() const;
    PropertyName name() const;
    QVariant value() const;
    bool isDynamic() const;
    TypeName dynamicTypeName() const;

private:
    qint32 m_instanceId;
    PropertyName m_name;
    QVariant m_value;
    TypeName m_dynamicTypeName;
};

QDataStream &operator<<(QDataStream &out, const PropertyValueContainer &container);
QDataStream &operator>>(QDataStream &in, PropertyValueContainer &container);

bool operator ==(const PropertyValueContainer &first, const PropertyValueContainer &second);
bool operator <(const PropertyValueContainer &first, const PropertyValueContainer &second);
QDebug operator <<(QDebug debug, const PropertyValueContainer &container);

} // namespace QmlDesigner

Q_DECLARE_METATYPE(QmlDesigner::PropertyValueContainer)

#endif // PROPERTYVALUECONTAINER_H
