/*=========================================================================

  Program:   Monteverdi
  Language:  C++


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See Copyright.txt for details.

  Monteverdi is distributed under the CeCILL licence version 2. See
  Licence_CeCILL_V2-en.txt or
  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt for more details.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef mvdQuicklookViewManipulator_h
#define mvdQuicklookViewManipulator_h

//
// Configuration include.
//// Included at first position before any other ones.
#include "ConfigureMonteverdi.h"


/*****************************************************************************/
/* INCLUDE SECTION                                                           */

//
// Qt includes (sorted by alphabetic order)
//// Must be included before system/custom includes.
#include <QtGui>

//
// System includes (sorted by alphabetic order)

//
// ITK includes (sorted by alphabetic order)

//
// OTB includes (sorted by alphabetic order)
#include "OTBMonteverdiGUIExport.h"
//
// Monteverdi includes (sorted by alphabetic order)
#include "mvdImageViewManipulator.h"


/*****************************************************************************/
/* PRE-DECLARATION SECTION                                                   */

//
// External classes pre-declaration.
namespace
{
}

namespace mvd
{
//
// Internal classes pre-declaration.


/*****************************************************************************/
/* CLASS DEFINITION SECTION                                                  */

/**
 * \class QuicklookViewManipulator
 *
 * \ingroup OTBMonteverdiGUI
 *
 *  \brief TODO.
 */
class OTBMonteverdiGUI_EXPORT QuicklookViewManipulator :
    public ImageViewManipulator
{

  /*-[ QOBJECT SECTION ]-----------------------------------------------------*/

  Q_OBJECT;

  /*-[ PUBLIC SECTION ]------------------------------------------------------*/

//
// Public methods.
public:

  /** \brief Constructor. */
#if USE_VIEW_SETTINGS_SIDE_EFFECT
  QuicklookViewManipulator( const otb::ViewSettings::Pointer& viewSettings,
                            QObject* p =NULL );
#else // USE_VIEW_SETTINGS_SIDE_EFFECT
  QuicklookViewManipulator( QObject* p =NULL );
#endif // USE_VIEW_SETTINGS_SIDE_EFFECT

  /** \brief Destructor. */
  ~QuicklookViewManipulator() ITK_OVERRIDE;

  //
  // ImageViewManipulator overloads.

  ZoomType GetFixedZoomType() const ITK_OVERRIDE;

  
    void
    SetupRenderingContext(
      AbstractImageViewRenderer::RenderingContext * const ) const ITK_OVERRIDE;


  void MousePressEvent( QMouseEvent* event ) ITK_OVERRIDE;

  void MouseMoveEvent( QMouseEvent* event ) ITK_OVERRIDE;

  // virtual void MousePressEvent( QMouseEvent* event );

  // virtual void MouseReleaseEvent( QMouseEvent* event );

  void MouseDoubleClickEvent( QMouseEvent * ) ITK_OVERRIDE {};

  void WheelEvent( QWheelEvent* event) ITK_OVERRIDE;

  void ResizeEvent( QResizeEvent * event ) ITK_OVERRIDE;

  void KeyPressEvent( QKeyEvent* event ) ITK_OVERRIDE;

  void KeyReleaseEvent( QKeyEvent* event ) ITK_OVERRIDE;

  /*-[ PUBLIC SLOTS SECTION ]-----------------------------------------------**/

//
// Public SLOTS.
public slots:

  /*-[ SIGNALS SECTION ]-----------------------------------------------------*/

//
// Signals.
signals:

  /*-[ PROTECTED SECTION ]---------------------------------------------------*/

//
// Protected methods.
protected:

//
// Protected attributes.
protected:

  /*-[ PRIVATE SECTION ]-----------------------------------------------------*/

//
// Private types.
private:

//
// Private methods.
private:

//
// Private attributes.
private:
  /**
   */
  PointType m_RoiOrigin;
  /**
   */
  SpacingType m_RoiSpacing;
  /**
   */
  SizeType m_RoiSize;

  /*-[ PRIVATE SLOTS SECTION ]-----------------------------------------------*/

//
// Slots.
private slots:
  /**
   */
  void OnRoiChanged( const PointType& origin,
                     const SizeType& size,
                     const SpacingType& spacing,
                     const PointType& center );
};

} // end namespace 'mvd'

/*****************************************************************************/
/* INLINE SECTION                                                            */

namespace mvd
{
} // end namespace 'mvd'

#endif // mvdQuicklookViewManipulator_h
