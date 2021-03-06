/***************************************************************************
**
** Copyright (C) 2015 Jochen Becher
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
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file.  Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, The Qt Company gives you certain additional
** rights.  These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#include "diagramsview.h"

#include "qmt/diagram_ui/diagramsmanager.h"
#include "qmt/diagram_widgets_ui/diagramview.h"
#include "qmt/diagram_scene/diagramscenemodel.h"
#include "qmt/model_ui/treemodel.h"

#include "qmt/diagram_controller/diagramcontroller.h"

#include "qmt/model/mdiagram.h"

namespace qmt {

DiagramsView::DiagramsView(QWidget *parent)
    : QTabWidget(parent),
      _diagrams_manager(0)
{
    setTabsClosable(true);
    setMovable(true);
    setDocumentMode(false);
    connect(this, SIGNAL(currentChanged(int)), this, SLOT(onCurrentChanged(int)));
    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(onTabCloseRequested(int)));
}

DiagramsView::~DiagramsView()
{
}

void DiagramsView::setDiagramsManager(DiagramsManager *diagrams_manager)
{
    _diagrams_manager = diagrams_manager;
}

void DiagramsView::openDiagram(MDiagram *diagram)
{
    QMT_CHECK(diagram);
    DiagramView *diagram_view = _diagram_views.value(diagram->getUid());
    if (!diagram_view) {
        DiagramSceneModel *diagram_scene_model = _diagrams_manager->bindDiagramSceneModel(diagram);
        DiagramView *diagram_view = new DiagramView(this);
        diagram_view->setDiagramSceneModel(diagram_scene_model);
        int tab_index = addTab(diagram_view, diagram->getName());
        setCurrentIndex(tab_index);
        _diagram_views.insert(diagram->getUid(), diagram_view);
    } else {
        setCurrentWidget(diagram_view);
    }
    emit someDiagramOpened(!_diagram_views.isEmpty());
}

void DiagramsView::closeDiagram(const MDiagram *diagram)
{
    if (!diagram) {
        return;
    }

    DiagramView *diagram_view = _diagram_views.value(diagram->getUid());
    if (diagram_view) {
        removeTab(indexOf(diagram_view));
        delete diagram_view;
        _diagram_views.remove(diagram->getUid());
    }
    emit someDiagramOpened(!_diagram_views.isEmpty());
}

void DiagramsView::closeAllDiagrams()
{
    for (int i = count() - 1; i >= 0; --i) {
        DiagramView *diagram_view = dynamic_cast<DiagramView *>(widget(i));
        if (diagram_view) {
            removeTab(i);
            delete diagram_view;
        }
    }
    _diagram_views.clear();
    emit someDiagramOpened(!_diagram_views.isEmpty());
}

void DiagramsView::onCurrentChanged(int tab_index)
{
    emit currentDiagramChanged(getDiagram(tab_index));
}

void DiagramsView::onTabCloseRequested(int tab_index)
{
    emit diagramCloseRequested(getDiagram(tab_index));
}

void DiagramsView::onDiagramRenamed(const MDiagram *diagram)
{
    if (!diagram) {
        return;
    }
    DiagramView *diagram_view = _diagram_views.value(diagram->getUid());
    if (diagram_view) {
        setTabText(indexOf(diagram_view), diagram->getName());
    }
}

MDiagram *DiagramsView::getDiagram(int tab_index) const
{
    DiagramView *diagram_view = dynamic_cast<DiagramView *>(widget(tab_index));
    return getDiagram(diagram_view);
}

MDiagram *DiagramsView::getDiagram(DiagramView *diagram_view) const
{
    if (!diagram_view || diagram_view->getDiagramSceneModel()) {
        return 0;
    }
    return diagram_view->getDiagramSceneModel()->getDiagram();
}

}
