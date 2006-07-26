/*  -*- C -*-  */
/*
 * ======================================================================
 *
 *                           Brad T. Aagaard
 *                        U.S. Geological Survey
 *
 * {LicenseText}
 *
 * ======================================================================
 */

#if !defined(spatialdata_spatialdb_testf77query_h)
#define spatialdata_spatialdb_testf77query_h

/** Fortran name mangling */
#define testf77query \
  FC_FUNC_(testf77query, TESTF77QUERY)
/** Call spatialdb_query_f().
 *
 * @param db Pointer to SpatialDB
 * @param pVals Pointer to computed values (output from query)
 * @param numVals Number of values expected (size of pVals array)
 * @param x C coordinate of location for query
 * @param y Y coordinate of location for query
 * @param z Z coordinate of location for query
 * @param cs Pointer to CoordSys
 *
 * @returns 0 on success, 1 on failure (i.e., values not set)
 */
int testf77query(void* db,
		 double** pVals,
		 int numVals,
		 double x,
		 double y,
		 double z,
		 void* cs);

#endif /* spatialdata_spatialdb_testf77query_h */

/* End of file  */
