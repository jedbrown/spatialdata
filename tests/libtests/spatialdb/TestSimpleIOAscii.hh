// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// {LicenseText}
//
// ----------------------------------------------------------------------
//

/** @file tests/libtests/spatialdb/TestSimpleIOAscii.hh
 *
 * @brief C++ TestSimpleIOAscii object
 *
 * C++ unit testing for SimpleIOAscii.
 */

#if !defined(spatialdata_spatialdb_testsimpleioascii_hh)
#define spatialdata_spatialdb_testsimpleioascii_hh

#include <cppunit/extensions/HelperMacros.h>

/// Namespace for spatialdata package
namespace spatialdata {
  namespace spatialdb {
    class TestSimpleIOAscii;
    class SimpleIOAscii; // USES SimpleIOAscii
  } // spatialdb
} // spatialdata

/// C++ unit testing for SimpleIO
class spatialdata::spatialdb::TestSimpleIOAscii : public CppUnit::TestFixture
{ // class TestSimpleIOAscii

  // CPPUNIT TEST SUITE /////////////////////////////////////////////////
  CPPUNIT_TEST_SUITE( TestSimpleIOAscii );
  CPPUNIT_TEST( testIO );
  CPPUNIT_TEST( testReadComments );
  CPPUNIT_TEST_SUITE_END();

  // PUBLIC METHODS /////////////////////////////////////////////////////
public :

  /// Test filename(), read(), write().
  void testIO(void);

  /// Test filename(), read() with spatial database file that contains
  /// comments.
  void testReadComments(void);

}; // class TestSimpleIOAscii

#endif // spatialdata_spatialdb_testsimpleioascii_hh

// version
// $Id$

// End of file 
