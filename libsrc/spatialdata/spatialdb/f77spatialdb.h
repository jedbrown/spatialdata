/*  -*- C -*-  */
/*
 * ======================================================================
 *
 * Brad T. Aagaard, U.S. Geological Survey
 *
 * This code was developed as part of the Computational Infrastructure
 * for Geodynamics (http://geodynamics.org).
 *
 * Copyright (c) 2010-2017 University of California, Davis
 *
 * See COPYING for license information.
 *
 * ======================================================================
 */

#if !defined(spatialdata_spatialdb_f77spatialdb_h)
#define spatialdata_spatialdb_f77spatialdb_h


// ----------------------------------------------------------------------
/** Fortran name mangling */
#define spatialdb_query_f \
  FC_FUNC_(spatialdb_query_f, SPATIALDB_QUERY_F)
/** Call SpatialDB:Query().
 *
 * @param db Pointer to SpatialDB
 * @param vals Array for computed values (output from query)
 * @param numVals Number of values expected (size of pVals array)
 * @param coords Coordinates of point for query
 * @param numDims Number of dimensions for coordinates
 * @param cs Pointer to CS
 * @param ok Set to 0 on success, 1 on failure (i.e., values not set)
 */
extern "C"
void spatialdb_query_f(void* db,
		       double* vals,
		       const int* numVals,
		       const double* coords,
		       const int* numDims,
		       const void* cs,
		       int* ok);

#endif /* spatialdata_spatialdb_f77spatialdb_h */

// End of file
