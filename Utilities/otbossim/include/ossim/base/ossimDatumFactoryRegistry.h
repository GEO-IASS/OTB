//----------------------------------------------------------------------------
//
// License:  See top level LICENSE.txt file
//
// Author:  David Burken
//
// Description: Class declaration of Registry (singleton) for datum factories.
//
//----------------------------------------------------------------------------
// $Id$

#ifndef ossimDatumFactoryRegistry_HEADER
#define ossimDatumFactoryRegistry_HEADER

#include <vector>
#include <list>

#include <ossim/base/ossimConstants.h> /* for OSSIM_DLL macro */

// Forward class declarations.
class ossimDatumFactoryInterface;
class ossimString;
class ossimDatum;

class OSSIM_DLL ossimDatumFactoryRegistry
{
public:
   
   /** destructor */
   ~ossimDatumFactoryRegistry();

   /**
    * instance method
    *
    * @return Point to the instance of the registry.
    */
   static ossimDatumFactoryRegistry* instance();

   /**
    * Method to add factory to registry.
    * @param factory Factory to register.
    */
   void registerFactory(ossimDatumFactoryInterface* factory);
   
   /**
    * create method
    *
    * Implements pure virtual ossimDatumFactoryInterface::create.
    *
    * @return const pointer to a datum.
    */
   const ossimDatum* create(const ossimString& code)const;

   /**
    * getList method to return a combined list of all datums from registered
    * datum factories.
    *
    * @param list The list to add to.
    */
   void getList(std::list<ossimString>& list) const;
   
private:

   /** hidden from use default constructor */
   ossimDatumFactoryRegistry();

   /** hidden from use copy constructor */
   ossimDatumFactoryRegistry(const ossimDatumFactoryRegistry& obj);

   /** hidden from use assignment operator */
   const ossimDatumFactoryRegistry& operator=(
      const ossimDatumFactoryRegistry& rhs);

   /** Single static instance of this class. */
   static ossimDatumFactoryRegistry* theInstance;

   std::vector<ossimDatumFactoryInterface*> theFactoryList;
};

#endif /* #ifndef ossimDatumFactoryRegistry_HEADER */
