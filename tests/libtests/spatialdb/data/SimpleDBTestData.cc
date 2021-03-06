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

#include "SimpleDBTestData.hh"

// ----------------------------------------------------------------------
// Constructor
spatialdata::spatialdb::SimpleDBTestData::SimpleDBTestData(void) :
  numLocs(0),
  spaceDim(0),
  numVals(0),
  dataDim(0),
  dbCoords(0),
  dbData(0),
  names(0),
  units(0),
  numQueries(0),
  queryNearest(0),
  queryLinear(0),
  errFlags(0)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
// Destructor
spatialdata::spatialdb::SimpleDBTestData::~SimpleDBTestData(void)
{ // destructor
} // destructor


// End of file
