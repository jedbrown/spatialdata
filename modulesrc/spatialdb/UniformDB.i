// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// <LicenseText>
//
// ----------------------------------------------------------------------
//

/** @file modulesrc/spatialdb/UniformDB.i
 *
 * @brief SWIG interface to C++ UniformDB object.
 */

namespace spatialdata {
  namespace spatialdb {

    class UniformDB : public SpatialDB
    { // class UniformDB

    public :
      // PUBLIC METHODS /////////////////////////////////////////////////

      /// Default constructor.
      UniformDB(void);
  
      /** Constructor with label.
       *
       * @param label Label of database
       */
      UniformDB(const char* label);
      
      /// Default destructor.
      ~UniformDB(void);
      
      /** Set values in database.
       *
       * @param names Array of names of values in database.
       * @param values Array of values in database.
       * @param numValues Number of values in database.
       */
      %apply(const char** string_list) {
	(const char** names)
	  };
      %apply(double* IN_ARRAY1, int DIM1) {
	(const double* values,
	 const int numValues)
	  };
      void setData(const char** names,
		   const double* values,
		   const int numValues);
      %clear(const double* values, const int numValues);
      
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
      %apply(const char** string_list, const int list_len){
	(const char** names,
	 const int numVals)
	  };
      void queryVals(const char** names,
		     const int numVals);
      %clear(const char** names, const int numVals);
      
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
      
    }; // class UniformDB
    
  } // spatialdb
} // spatialdata


// End of file 