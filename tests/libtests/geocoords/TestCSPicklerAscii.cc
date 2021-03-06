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

#include "TestCSPicklerAscii.hh" // Implementation of class methods

#include "spatialdata/geocoords/CSPicklerAscii.hh" // USES CSPickleAscii

#include "spatialdata/geocoords/CoordSys.hh" // USES CoordSys
#include "spatialdata/geocoords/CSCart.hh" // USES CSCart
#include "spatialdata/geocoords/CSGeo.hh" // USES CSGeo
#include "spatialdata/geocoords/CSGeoProj.hh" // USES CSGeoProj
#include "spatialdata/geocoords/Projector.hh" // USES Projector

#include <sstream> // USES std::stringstream

// ----------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( spatialdata::geocoords::TestCSPicklerAscii );

// ----------------------------------------------------------------------
// Test pickle() and unpickle() for CSCart
void
spatialdata::geocoords::TestCSPicklerAscii::testPickleCSCart(void)
{ // testPickleCSCart
  CSCart cs;

  std::stringstream s;
  s << "coord-sys = ";
  CSPicklerAscii::pickle(s, &cs);

  CoordSys* pCS = 0;
  CSPicklerAscii::unpickle(s, &pCS);

  CPPUNIT_ASSERT(0 != dynamic_cast<CSCart*>(pCS));

  delete pCS; pCS = 0;
} // testPickleCSCart

// ----------------------------------------------------------------------
// Test pickle() and unpickle() for CSGeo
void
spatialdata::geocoords::TestCSPicklerAscii::testPickleCSGeo(void)
{ // testPickleCSGeo
  CSGeo cs;

  std::stringstream s;
  s << "coord-sys = ";
  CSPicklerAscii::pickle(s, &cs);

  CoordSys* pCS = 0;
  CSPicklerAscii::unpickle(s, &pCS);

  CPPUNIT_ASSERT(0 != dynamic_cast<CSGeo*>(pCS));

  delete pCS; pCS = 0;
} // testPickleCSGeo

// ----------------------------------------------------------------------
// Test pickle() and unpickle() for CSGeoProj
void
spatialdata::geocoords::TestCSPicklerAscii::testPickleCSGeoProj(void)
{ // testPickleCSGeoProj
  Projector proj;
  CSGeoProj cs;
  cs.projector(proj);

  std::stringstream s;
  s << "coord-sys = ";
  CSPicklerAscii::pickle(s, &cs);

  CoordSys* pCS = 0;
  CSPicklerAscii::unpickle(s, &pCS);

  CPPUNIT_ASSERT(0 != dynamic_cast<CSGeoProj*>(pCS));

  delete pCS; pCS = 0;
} // testPickleCSGeoProj


// End of file 
