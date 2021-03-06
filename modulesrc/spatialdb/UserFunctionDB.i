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

/** @file modulesrc/spatialdb/UserFunctionDB.i
 *
 * @brief SWIG interface to C++ UserFunctionDB object.
 */

namespace spatialdata {
    namespace spatialdb {
	
	class UserFunctionDB : public SpatialDB {
	    
	public :
	    // PUBLIC TYPEDEF//////////////////////////////////////////////////////
	    
	    /** User function prototype in 1-D.
	     *
	     * @param x X coordinate.
	     * @returns Value of user-defined function.
	     */
	    typedef double (*userfn1D_type)(const double x);
	    
	    /** User function prototype in 2-D.
	     *
	     * @param x X coordinate.
	     * @param y Y coordinate.
	     * @returns Value of user-defined function.
	     */
	    typedef double (*userfn2D_type)(const double x,
					    const double y);
	    
	    /** User function prototype in 3-D.
	     *
	     * @param x X coordinate.
	     * @param y Y coordinate.
	     * @param z Z coordinate.
	     * @returns Value of user-defined function.
	     */
	    typedef double (*userfn3D_type)(const double x,
					    const double y,
					    const double z);

	    // PUBLIC MEMBERS ///////////////////////////////////////////////////////
	public :
	    
	    /// Constructor
	    UserFunctionDB(void);
	    
	    /// Destructor
	    ~UserFunctionDB(void);
	    
	    /** Add function/value to database in 1-D.
	     *
	     * @param name Name of value for function.
	     * @param fn User function for value.
	     * @param units Units associated with function value.
	     */
	    void addValue(const char* name,
			  userfn1D_type fn,
			  const char* units);
	    
	    /** Add function/value to database in 2-D.
	     *
	     * @param name Name of value for function.
	     * @param fn User function for value.
	     * @param units Units associated with function value.
	     */
	    void addValue(const char* name,
			  userfn2D_type fn,
			  const char* units);
	    
	    /** Add function/value to database in 3-D.
	     *
	     * @param name Name of value for function.
	     * @param fn User function for value.
	     * @param units Units associated with function value.
	     */
	    void addValue(const char* name,
			  userfn3D_type fn,
			  const char* units);
  
	    /// Open the database and prepare for querying.
	    void open(void);
	    
	    /// Close the database.
	    void close(void);
	    
	    /** Set values to be returned by queries.
	     *
	     * @pre Must call open() before queryVals()
	     *
	     * @param names Names of values to be returned in queries
	     * @param numVals Number of values to be returned in queries
	     */
	    %apply(const char* const* string_list, const int list_len){
		(const char* const* names,
		 const int numVals)
		    };
	    void queryVals(const char* const* names,
			   const int numVals);
	    %clear(const char* const* names, const int numVals);
	    
	    /** Query the database.
	     *
	     * @pre Must call open() before query()
	     *
	     * @param vals Array for computed values (output from query), vals
	     *   must be allocated BEFORE calling query().
	     * @param numVals Number of values expected (size of pVals array)
	     * @param coords Coordinates of point for query
	     * @param numDims Number of dimensions for coordinates
	     * @param pCSQuery Coordinate system of coordinates
	     *
	     * @returns 0 on success, 1 on failure (i.e., could not interpolate
	     *   so values set to 0)
	     */
	    %apply(double* INPLACE_ARRAY1, int DIM1) {
		(double* vals,
		 const int numVals)
		    };
	    %apply(double* IN_ARRAY1, int DIM1) {
		(const double* coords,
		 const int numDims)
		    };
	    int query(double* vals,
		      const int numVals,
		      const double* coords,
		      const int numDims,
		      const spatialdata::geocoords::CoordSys* pCSQuery);
	    %clear(double* vals, const int numVals);
	    %clear(const double* coords, const int numDims);
	    
	    /** Set coordinate system associated with user functions.
	     *
	     * @param cs Coordinate system.
	     */
	    void coordsys(const geocoords::CoordSys& cs);
	    
	}; // class UserFunctionDB
	
    } // spatialdb
} // spatialdata


// End of file 
