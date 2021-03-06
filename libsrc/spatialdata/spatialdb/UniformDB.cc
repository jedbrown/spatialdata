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

#include "UniformDB.hh" // Implementation of class methods

// Include ios here to avoid some Python/gcc issues
#include <ios>

#include "spatialdata/units/Parser.hh" // USES Parser

#include <vector> // USES std::vector
#include <stdexcept> // USES std::runtime_error

#include <sstream> // USES std::ostringsgream
#include <strings.h> // USES strcasecmp()
#include <assert.h> // USES assert()

// ----------------------------------------------------------------------
/// Default constructor
spatialdata::spatialdb::UniformDB::UniformDB(void) :
  _names(0),
  _values(0),
  _queryVals(0),
  _numValues(0),
  _querySize(0)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
/// Constructor with label
spatialdata::spatialdb::UniformDB::UniformDB(const char* label) :
  SpatialDB(label),
  _names(0),
  _values(0),
  _queryVals(0),
  _numValues(0),
  _querySize(0)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
/// Default destructor
spatialdata::spatialdb::UniformDB::~UniformDB(void)
{ // destructor
  delete[] _names; _names = 0;
  delete[] _values; _values = 0;
  delete[] _queryVals; _queryVals = 0;
  _numValues = 0;
  _querySize = 0;
} // destructor

// ----------------------------------------------------------------------
// Set values in database.
void
spatialdata::spatialdb::UniformDB::setData(const char* const* names,
					   const char* const* units,
					   const double* values,
					   const int numValues)
{ // setData
  assert( (0 < numValues && 0 != names && 0 != units && 0 != values) ||
	  (0 == numValues && 0 == names && 0 == units && 0 == values) );

  // clear out old data
  delete[] _names; _names = 0;
  delete[] _values; _values = 0;
  _numValues = numValues;

  spatialdata::units::Parser parser;

  if (0 < numValues) {
    _names = new std::string[numValues];
    for (int i=0; i < numValues; ++i)
      _names[i] = names[i];

    std::vector<double> scales(numValues);
    for (int i=0; i < numValues; ++i) {
      if (strcasecmp(units[i], "none") != 0)
	scales[i] = parser.parse(units[i]);
      else
	scales[i] = 1.0;
    } // for

    _values = new double[numValues];
    for (int i=0; i < numValues; ++i)
      _values[i] = values[i]*scales[i];
  } // if
} // setData

// ----------------------------------------------------------------------
// Set values to be returned by queries.
void
spatialdata::spatialdb::UniformDB::queryVals(const char* const* names,
					     const int numVals)
{ // queryVals
  if (0 == numVals) {
    std::ostringstream msg;
    msg
      << "Number of values for query in spatial database " << label()
      << "\n must be positive.\n";
    throw std::runtime_error(msg.str());
  } // if
  assert(0 != names && 0 < numVals);
  
  _querySize = numVals;
  delete[] _queryVals; _queryVals = new int[numVals];
  for (int iVal=0; iVal < numVals; ++iVal) {
    int iName = 0;
    while (iName < _numValues) {
      if (0 == strcasecmp(names[iVal], _names[iName].c_str()))
	break;
      ++iName;
    } // while
    if (iName >= _numValues) {
      std::ostringstream msg;
      msg
	<< "Could not find value '" << names[iVal] << "' in spatial database '"
	<< label() << "'. Available values are:";
      for (int iName=0; iName < _numValues; ++iName)
	msg << "\n  " << _names[iName];
      msg << "\n";
      throw std::runtime_error(msg.str());
    } // if
    _queryVals[iVal] = iName;
  } // for
} // queryVals

// ----------------------------------------------------------------------
// Query the database.
int
spatialdata::spatialdb::UniformDB::query(
			      double* vals,
			      const int numVals,
			      const double* coords,
			      const int numDims,
			      const spatialdata::geocoords::CoordSys* pCSQuery)
{ // query
  if (0 == _querySize) {
    std::ostringstream msg;
    msg
      << "Values to be returned by spatial database " << label() << "\n"
      << "have not been set. Please call queryVals() before query().\n";
    throw std::runtime_error(msg.str());
  } // if
  else if (numVals != _querySize) {
    std::ostringstream msg;
    msg
      << "Number of values to be returned by spatial database "
      << label() << "\n"
      << "(" << _querySize << ") does not match size of array provided ("
      << numVals << ").\n";
    throw std::runtime_error(msg.str());
  } // if

  for (int iVal=0; iVal < _querySize; ++iVal)
    vals[iVal] = _values[_queryVals[iVal]];

  return 0;
} // query


// End of file 
