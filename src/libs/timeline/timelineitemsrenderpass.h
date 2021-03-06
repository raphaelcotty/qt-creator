/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://www.qt.io/licensing.  For further information
** use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file.  Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#ifndef TIMELINEITEMSRENDERPASS_H
#define TIMELINEITEMSRENDERPASS_H

#include "timelineabstractrenderer.h"
#include "timelinerenderpass.h"
#include <QSGMaterial>

namespace Timeline {

class TimelineItemsMaterial : public QSGMaterial
{
public:
    TimelineItemsMaterial();
    QVector2D scale() const;
    void setScale(QVector2D scale);

    float selectedItem() const;
    void setSelectedItem(float selectedItem);

    QColor selectionColor() const;
    void setSelectionColor(QColor selectionColor);

    QSGMaterialType *type() const;
    QSGMaterialShader *createShader() const;

private:
    QVector2D m_scale;
    float m_selectedItem;
    QColor m_selectionColor;
};

class OpaqueColoredPoint2DWithSize
{
public:
    void set(float nx, float ny, float nw, float nh, float nid, uchar nr, uchar ng, uchar nb);
    float top() const;
    void setTop(float top);

    static const QSGGeometry::AttributeSet &attributes();
    static OpaqueColoredPoint2DWithSize *fromVertexData(QSGGeometry *geometry);

private:
    float x, y, w, h, id;
    unsigned char r, g, b, a;
};

class TIMELINE_EXPORT TimelineItemsRenderPass : public TimelineRenderPass
{
public:
    static const TimelineItemsRenderPass *instance();
    State *update(const TimelineAbstractRenderer *renderer, const TimelineRenderState *parentState,
                  State *state, int firstIndex, int lastIndex, bool stateChanged,
                  qreal spacing) const;
protected:
    TimelineItemsRenderPass();
};

} // namespace Timeline

#endif // TIMELINEITEMSRENDERPASS_H
