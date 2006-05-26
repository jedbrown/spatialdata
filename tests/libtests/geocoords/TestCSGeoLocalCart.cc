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

#include <portinfo>

#include "TestCSGeoLocalCart.hh" // Implementation of class methods

#include "spatialdata/geocoords/CoordSys.hh" // USES CSGeoLocalCart
#include "spatialdata/geocoords/CSGeo.hh" // USES CSGeoLocalCart
#include "spatialdata/geocoords/CSGeoLocalCart.hh" // USES CSGeoLocalCart

#include <sstream> // USES std::stringstream

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::geocoords::TestCSGeoLocalCart );

// ----------------------------------------------------------------------
#include "data/TestCSGeoLocalCart.dat"

// ----------------------------------------------------------------------
// Test constructor
void
spatialdata::geocoords::TestCSGeoLocalCart::testConstructor(void)
{ // testConstructor
  CSGeoLocalCart cs;
} // testConstructor

// ----------------------------------------------------------------------
// Test origin()
void
spatialdata::geocoords::TestCSGeoLocalCart::testOrigin(void)
{ // testOrigin
  CSGeoLocalCart cs;
  
  cs.origin(_ORIGINLON, _ORIGINLAT, _ORIGINELEV);
  const double tolerance = 1.0e-06;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(_ORIGINLON, cs._originLon, tolerance);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(_ORIGINLAT, cs._originLat, tolerance);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(_ORIGINELEV, cs._originElev, tolerance);
} // testOrigin

// ----------------------------------------------------------------------
// Test initialize()
void
spatialdata::geocoords::TestCSGeoLocalCart::testInitialize(void)
{ // testInitialize
  CSGeoLocalCart cs;

  cs.origin(_ORIGINLON, _ORIGINLAT, _ORIGINELEV);
  cs.ellipsoid(_ELLIPSOID);
  cs.datumHoriz(_DATUMHORIZ);
  cs.datumVert(_DATUMVERT);
  cs.initialize();

  const double tolerance = 1.0e-06;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(_ORIGINX, cs._originX, tolerance*1e+4);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, cs._originY/_ORIGINY, tolerance);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, cs._originZ/_ORIGINZ, tolerance);  
} // testLocalOrigin

// ----------------------------------------------------------------------
// Test toProjForm()
void
spatialdata::geocoords::TestCSGeoLocalCart::testToProjForm(void)
{ // testToProjForm
  CSGeoLocalCart cs;
 
  cs.origin(_ORIGINLON, _ORIGINLAT, _ORIGINELEV);
  cs.ellipsoid(_ELLIPSOID);
  cs.datumHoriz(_DATUMHORIZ);
  cs.datumVert(_DATUMVERT);
  cs.initialize();

  const int numCoords = 3;
  const int size = _NUMLOCS * numCoords;
  double* pVals = new double[size];
  memcpy(pVals, _XYZLOCAL, size*sizeof(double));
  cs.toProjForm(&pVals, _NUMLOCS);
  const double tolerance = 1.0e-6;
  for (int i=0; i < size; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pVals[i]/_XYZECEF[i], tolerance);
  delete[] pVals; pVals = 0;
} // testToProjForm

// ----------------------------------------------------------------------
// Test fromProjForm()
void
spatialdata::geocoords::TestCSGeoLocalCart::testFromProjForm(void)
{ // testFromProjForm
  CSGeoLocalCart cs;

  cs.origin(_ORIGINLON, _ORIGINLAT, _ORIGINELEV);
  cs.ellipsoid(_ELLIPSOID);
  cs.datumHoriz(_DATUMHORIZ);
  cs.datumVert(_DATUMVERT);
  cs.initialize();

  const int numCoords = 3;
  const int size = _NUMLOCS * numCoords;
  double* pVals = new double[size];
  memcpy(pVals, _XYZECEF, size*sizeof(double));
  cs.fromProjForm(&pVals, _NUMLOCS);
  const double tolerance = 1.0e-6;
  for (int i=0; i < size; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, pVals[i]/_XYZLOCAL[i], tolerance);
  delete[] pVals; pVals = 0;
} // testFromProjForm

// ----------------------------------------------------------------------
// Test pickle() and unpickle()
void
spatialdata::geocoords::TestCSGeoLocalCart::testPickle(void)
{ // testPickle
  const double toMeters = 4.5;

  CSGeoLocalCart csA;
  csA.ellipsoid(_ELLIPSOID);
  csA.datumHoriz(_DATUMHORIZ);
  csA.datumVert(_DATUMVERT);
  csA.origin(_ORIGINLON, _ORIGINLAT, _ORIGINELEV);
  csA.toMeters(toMeters);

  std::stringstream s;
  csA.pickle(s);

  CSGeoLocalCart csB;
  csB.unpickle(s);

  const double tolerance = 1.0e-6;
  CPPUNIT_ASSERT(0 == strcasecmp(_ELLIPSOID, csB.ellipsoid()));
  CPPUNIT_ASSERT(0 == strcasecmp(_DATUMHORIZ, csB.datumHoriz()));
  CPPUNIT_ASSERT(0 == strcasecmp(_DATUMVERT, csB.datumVert()));
  CPPUNIT_ASSERT_DOUBLES_EQUAL(_ORIGINLON, csB._originLon, tolerance);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(_ORIGINLAT, csB._originLat, tolerance);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(_ORIGINELEV, csB._originElev, tolerance);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(toMeters, csB.toMeters(), tolerance);
} // testPickle

// version
// $Id$

// End of file 