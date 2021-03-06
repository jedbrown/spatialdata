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

// DO NOT EDIT THIS FILE
// This file was generated from python application simpledbquerydata3d.

#include "SimpleDBQueryData3D.hh"

const int spatialdata::spatialdb::SimpleDBQueryData3D::_numLocs = 5;

const int spatialdata::spatialdb::SimpleDBQueryData3D::_spaceDim = 3;

const int spatialdata::spatialdb::SimpleDBQueryData3D::_numVals = 2;

const int spatialdata::spatialdb::SimpleDBQueryData3D::_dataDim = 3;

const int spatialdata::spatialdb::SimpleDBQueryData3D::_numPts = 4;

const double spatialdata::spatialdb::SimpleDBQueryData3D::_dist2 =   9.86850000e+00;

const double spatialdata::spatialdb::SimpleDBQueryData3D::_area =   7.28666752e+00;

const double spatialdata::spatialdb::SimpleDBQueryData3D::_volume =   2.95458000e+00;

const double spatialdata::spatialdb::SimpleDBQueryData3D::_dbCoords[] = {
  0.00000000e+00,  0.00000000e+00,  0.00000000e+00,
  1.00000000e+00,  1.00000000e-01,  3.00000000e-01,
  2.00000000e+00,  2.00000000e-01,  2.00000000e-01,
  3.00000000e+00,  3.00000000e-01,  1.00000000e-01,
  4.00000000e+00,  4.00000000e-01,  9.00000000e-01,
};

const double spatialdata::spatialdb::SimpleDBQueryData3D::_dbData[] = {
  1.10000000e+00,  5.50000000e+00,
  2.20000000e+00,  6.60000000e+00,
  3.30000000e+00,  7.70000000e+00,
  4.40000000e+00,  8.80000000e+00,
  4.50000000e+00,  9.90000000e+00,
};

const char* spatialdata::spatialdb::SimpleDBQueryData3D::_names[] = {
"One",
"Two",
};

const char* spatialdata::spatialdb::SimpleDBQueryData3D::_units[] = {
"m",
"m",
};

const double spatialdata::spatialdb::SimpleDBQueryData3D::_coords[] = {
  2.95000000e+00,  4.48000000e+00,  3.44000000e+00,
  5.80000000e+00,  5.32000000e+00,  4.46000000e+00,
  7.97000000e+00,  1.06200000e+01,  7.00000000e+00,
  8.38000000e+00,  1.30100000e+01,  9.34000000e+00,
};

const double spatialdata::spatialdb::SimpleDBQueryData3D::_areaDir[] = {
 -2.24547092e-01, -3.44848999e-01,  9.11404285e-01,};

spatialdata::spatialdb::SimpleDBQueryData3D::SimpleDBQueryData3D(void)
{ // constructor
  numLocs = _numLocs;
  spaceDim = _spaceDim;
  numVals = _numVals;
  dataDim = _dataDim;
  numPts = _numPts;
  dist2 = _dist2;
  area = _area;
  volume = _volume;
  dbCoords = const_cast<double*>(_dbCoords);
  dbData = const_cast<double*>(_dbData);
  names = const_cast<char**>(_names);
  units = const_cast<char**>(_units);
  coords = const_cast<double*>(_coords);
  areaDir = const_cast<double*>(_areaDir);
} // constructor

spatialdata::spatialdb::SimpleDBQueryData3D::~SimpleDBQueryData3D(void)
{}


// End of file
