/*=========================================================================

  Program:   Monteverdi2
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See Copyright.txt for details.

  Monteverdi2 is distributed under the CeCILL licence version 2. See
  Licence_CeCILL_V2-en.txt or
  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt for more details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "Gui/mvdApplicationsToolBox.h"
#include "Gui/ui_mvdApplicationsToolBox.h"


/*****************************************************************************/
/* INCLUDE SECTION                                                           */

//
// Qt includes (sorted by alphabetic order)
//// Must be included before system/custom includes.

//
// System includes (sorted by alphabetic order)

//
// ITK includes (sorted by alphabetic order)

//
// OTB includes (sorted by alphabetic order)

//
// Monteverdi includes (sorted by alphabetic order)
#include "mvdAlgorithm.h"

namespace mvd
{
/*
  TRANSLATOR mvd::ApplicationsToolBox

  Necessary for lupdate to be aware of C++ namespaces.

  Context comment for translator.
*/


/*****************************************************************************/
/* CONSTANTS                                                                 */


/*****************************************************************************/
/* STATIC IMPLEMENTATION SECTION                                             */


/*****************************************************************************/
/* CLASS IMPLEMENTATION SECTION                                              */

/*******************************************************************************/
ApplicationsToolBox
::ApplicationsToolBox( QWidget* parent, Qt::WindowFlags flags  ):
  QWidget( parent, flags ),
  m_UI( new mvd::Ui::ApplicationsToolBox() )
{
  m_UI->setupUi( this );

  //
  // connect search box changed
  QObject::connect(m_UI->m_SearchLine,
                   SIGNAL( textChanged(const QString &) ),
                   this,
                   SLOT( OnSearchBoxChanged(const QString &) )
    );

  //
  // connect double click on the tree Widget
  QObject::connect(GetAlgorithmsTree(),
                   SIGNAL( itemDoubleClicked(QTreeWidgetItem* ,int) ),
                   this,
                   SLOT( OnAlgorithmTreeDoubleClick(QTreeWidgetItem* ,int) )
    );
}

/*******************************************************************************/
ApplicationsToolBox
::~ApplicationsToolBox()
{
}

/*******************************************************************************/
QTreeWidget *
ApplicationsToolBox
::GetAlgorithmsTree()
{
  return m_UI->m_AlgorithmsTree;
}

/*******************************************************************************/
void
ApplicationsToolBox
::FillTreeUsingTags()
{
  //
  // clear algorithms tree
  GetAlgorithmsTree()->clear();
  
  // 
  // main item (title)
  QTreeWidgetItem * mainItem = new QTreeWidgetItem( GetAlgorithmsTree() );
  mainItem->setText(0, "Orfeo Toolbox Algorithms");

  //
  // Fill the  map as following
  // - key   -> tag
  // - value -> list of applications having this tag
  ApplicationsTagContainer::const_iterator itTag = m_AppTags.begin();
  while( itTag != m_AppTags.end() )
    {
    //
    // step # 1 -> Tag as a main item
    QTreeWidgetItem * cmainItem = new QTreeWidgetItem( mainItem );
    QString  qcurrentMainItem( (*itTag).first.c_str() );
    cmainItem->setText(0,  qcurrentMainItem );

    //
    // TODO : add category icon
    // step #2 -> Applications name are secondary items
    StringVector::const_iterator itApps = (*itTag).second.begin();
    while( itApps != (*itTag).second.end() )
      {
      // 
      // set current application name as secondary item
      QTreeWidgetItem * secItem = new QTreeWidgetItem( cmainItem );
      QString  qcurrentSecItem( (*itApps).c_str() );
      secItem->setText(0, qcurrentSecItem);

      //
      // TODO : add algorithm icon

      ++itApps;
      }

    ++itTag;
    }
}

/*******************************************************************************/
void
ApplicationsToolBox
::ExecuteAlgorithm( const QString& appName )
{
  std::cout <<"ApplicationsToolBox::ExecuteAlgorithm - "<< ToStdString( appName )<< "- WIP."<< std::endl;
}

/*******************************************************************************/
/* SLOTS                                                                       */
/*******************************************************************************/
void
ApplicationsToolBox
::OnAvailableApplicationsTagsChanged(const ApplicationsTagContainer& appsTags )
{
  // rememeber the map
  m_AppTags = appsTags;
  
  // fill the tree with the application
  FillTreeUsingTags();  
}

/*******************************************************************************/
void
ApplicationsToolBox
::OnSearchBoxChanged(const QString & search)
{
  // 
  // get the search text
  m_SearchText = search;
  
  // fill the tree with the application
  FillTreeUsingTags();  
}

/*******************************************************************************/
void
ApplicationsToolBox
::OnAlgorithmTreeDoubleClick( QTreeWidgetItem * item , int column )
{
  std::cout <<"Algorithm name "<< ToStdString( item->text( column ) ) << std::endl;
  QString appName = item->text( column );

  // 
  // Execute the algorithm
  if ( !appName.isEmpty() )
    {
    ExecuteAlgorithm( appName );
    }
}

/*******************************************************************************/

} // end namespace 'mvd'
