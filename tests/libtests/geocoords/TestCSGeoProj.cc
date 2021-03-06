// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2017 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "TestCSGeoProj.hh" // Implementation of class methods

#include "spatialdata/geocoords/CoordSys.hh" // USES CSGeoProj
#include "spatialdata/geocoords/CSGeo.hh" // USES CSGeoProj
#include "spatialdata/geocoords/CSGeoProj.hh" // USES CSGeoProj
#include "spatialdata/geocoords/Projector.hh" // USES Projector

#include <math.h> // USES M_PI
#include <string.h> // USES memcpy()
#include <strings.h> // USES strcasecmp()
#include <sstream> // USES std::stringstream

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::geocoords::TestCSGeoProj );

// ----------------------------------------------------------------------
#include "data/TestCSGeoProj.dat"

// ----------------------------------------------------------------------
// Test constructor
void
spatialdata::geocoords::TestCSGeoProj::testConstructor(void)
{ // testConstructor
  CSGeoProj cs;
} // testConstructor

// ----------------------------------------------------------------------
// Test initialize()
void
spatialdata::geocoords::TestCSGeoProj::testInitialize(void)
{ // testInitialize
  Projector proj;
  proj.projection(_PROJECTION);
  proj.units(_UNITS);
  proj.projOptions(_PROJOPTIONS);

  CSGeoProj cs;
  cs.ellipsoid(_ELLIPSOID);
  cs.datumHoriz(_DATUMHORIZ);
  cs.datumVert(_DATUMVERT);
  cs.projector(proj);

  cs.initialize();
} // testLocalOrigin

// ----------------------------------------------------------------------
// Test toProjForm()
void
spatialdata::geocoords::TestCSGeoProj::testToProjForm(void)
{ // testToProjForm
  Projector proj;
  proj.projection(_PROJECTION);
  proj.units(_UNITS);
  proj.projOptions(_PROJOPTIONS);

  CSGeoProj cs;
  cs.ellipsoid(_ELLIPSOID);
  cs.datumHoriz(_DATUMHORIZ);
  cs.datumVert(_DATUMVERT);
  cs.projector(proj);

  cs.initialize();

  const int numDims = 3;
  const int size = _NUMLOCS * numDims;
  double* vals = new double[size];
  memcpy(vals, _XYZ, size*sizeof(double));
  cs.toProjForm(vals, _NUMLOCS, numDims);
  const double degToRad = M_PI / 180.0;
  const double tolerance = 1.0e-5;
  for (int i=0; i < size; i+=3) {
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, 
				 vals[i  ]/(_LONLATNAD27ELEV[i  ]*degToRad),
				 tolerance);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, 
				 vals[i+1]/(_LONLATNAD27ELEV[i+1]*degToRad),
				 tolerance);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, vals[i+2]/_LONLATNAD27ELEV[i+2],
				 tolerance);
  } // for
  delete[] vals; vals = 0;
} // testToProjForm

// ----------------------------------------------------------------------
// Test fromProjForm()
void
spatialdata::geocoords::TestCSGeoProj::testFromProjForm(void)
{ // testFromProjForm
  Projector proj;
  proj.projection(_PROJECTION);
  proj.units(_UNITS);
  proj.projOptions(_PROJOPTIONS);

  CSGeoProj cs;
  cs.ellipsoid(_ELLIPSOID);
  cs.datumHoriz(_DATUMHORIZ);
  cs.datumVert(_DATUMVERT);
  cs.projector(proj);

  cs.initialize();

  const int numDims = 3;
  const int size = _NUMLOCS * numDims;
  double* vals = new double[size];
  memcpy(vals, _LONLATNAD27ELEV, size*sizeof(double));
  const double degToRad = M_PI / 180.0;
  for (int i=0; i < size; i+=3) {
    vals[i  ] *= degToRad;
    vals[i+1] *= degToRad;
  } // for
  
  cs.fromProjForm(vals, _NUMLOCS, numDims);

  const double tolerance = 1.0e-6;
  for (int i=0; i < size; ++i)
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, vals[i]/_XYZ[i], tolerance);
  delete[] vals; vals = 0;
} // testFromProjForm

// ----------------------------------------------------------------------
// Test pickle() and unpickle()
void
spatialdata::geocoords::TestCSGeoProj::testPickle(void)
{ // testPickle
  Projector projA;
  projA.projection(_PROJECTION);
  projA.units(_UNITS);
  projA.projOptions(_PROJOPTIONS);

  CSGeoProj csA;
  csA.ellipsoid(_ELLIPSOID);
  csA.datumHoriz(_DATUMHORIZ);
  csA.datumVert(_DATUMVERT);
  csA.projector(projA);

  csA.initialize();

  std::stringstream s;
  csA.pickle(s);

  CSGeoProj csB;
  csB.unpickle(s);

  const double tolerance = 1.0e-6;
  CPPUNIT_ASSERT(0 == strcasecmp(_ELLIPSOID, csB.ellipsoid()));
  CPPUNIT_ASSERT(0 == strcasecmp(_DATUMHORIZ, csB.datumHoriz()));
  CPPUNIT_ASSERT(0 == strcasecmp(_DATUMVERT, csB.datumVert()));
  CPPUNIT_ASSERT_DOUBLES_EQUAL(_ORIGINLON, csB._originLon, tolerance);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(_ORIGINLAT, csB._originLat, tolerance);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(_ROTANGLE, csB.rotationAngle(), tolerance);
} // testPickle


// End of file 
