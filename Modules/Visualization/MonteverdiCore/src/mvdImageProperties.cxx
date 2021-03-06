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
#include "mvdImageProperties.h"


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

namespace mvd
{
/*
  TRANSLATOR mvd::ImageProperties

  Necessary for lupdate to be aware of C++ namespaces.

  Context comment for translator.
*/


/*****************************************************************************/
/* CONSTANTS                                                                 */

namespace
{
} // end of anonymous namespace.


/*****************************************************************************/
/* STATIC IMPLEMENTATION SECTION                                             */


/*****************************************************************************/
/* CLASS IMPLEMENTATION SECTION                                              */

/*******************************************************************************/
ImageProperties
#if IMAGE_PROPERTIES_IS_QOBJECT
::ImageProperties( QObject* p ) :
  QObject( p ),
#else
::ImageProperties() :
#endif
  m_Flags(),
  m_NoData( ComponentType( 0 ) )
{
  m_Flags.m_NoData = false;
}

/*******************************************************************************/
ImageProperties
::~ImageProperties()
{
}

/*******************************************************************************/
bool
ImageProperties
::operator == ( const ImageProperties & other ) const
{
  return
    other.m_Flags.m_NoData==m_Flags.m_NoData &&
    other.m_NoData==m_NoData;
}

/*******************************************************************************/
bool
ImageProperties
::operator != ( const ImageProperties & other ) const
{
  return !operator == ( other );
}

/*******************************************************************************/
/* SLOTS                                                                       */
/*******************************************************************************/

} // end namespace 'mvd'
