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

#if !defined(spatialdata_spatialdb_simplegriddbtestdatavolume3d_hh)
#define spatialdata_spatialdb_simplegriddbtestdatavolume3d_hh

#include "SimpleGridDBTestData.hh"

namespace spatialdata {
  namespace spatialdb {
     class SimpleGridDBTestDataVolume3D;
  } // spatialdata
} // spatialdb

class spatialdata::spatialdb::SimpleGridDBTestDataVolume3D : public SimpleGridDBTestData
{

public: 

  /// Constructor
  SimpleGridDBTestDataVolume3D(void);

  /// Destructor
  ~SimpleGridDBTestDataVolume3D(void);

private:

  static const int _numX;

  static const int _numY;

  static const int _numZ;

  static const int _spaceDim;

  static const int _numVals;

  static const int _dataDim;

  static const int _numQueries;

  static const double _dbX[];

  static const double _dbY[];

  static const double _dbZ[];

  static const double _dbData[];

  static const char* _names[];

  static const char* _units[];

  static const double _queryNearest[];

  static const double _queryLinear[];

  static const int _errFlags[];

  static const char* _filename;

};

#endif // spatialdata_spatialdb_simplegriddbtestdatavolume3d_hh

// End of file
