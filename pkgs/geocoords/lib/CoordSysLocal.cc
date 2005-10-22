// -*- C++ -*-
//
// ======================================================================
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// {LicenseText}
//
// ======================================================================
//

#include <portinfo>

#include "CoordSys.h" // ISA CoordSysGeo
#include "CoordSysLocal.h" // implementation of class methods

extern "C" {
#include "proj_api.h" // USES PROJ4
}

#include "Geoid.h" // USES Geoid

#include <math.h> // USES M_PI, sin(), cos()
#include <stdexcept> // USES std::runtime_error, std::exception
#include <sstream> // USES std::ostringsgream

#if !defined(NO_PYTHIA)
#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#else
#define FIREWALL assert
#endif

#include <iostream>

// ----------------------------------------------------------------------
// Default constructor
spatialdata::geocoords::CoordSysLocal::CoordSysLocal(void) :
  _originLon(0),
  _originLat(0),
  _originElev(0),
  _originX(0),
  _originY(0),
  _originZ(0),
  _xyzToMeters(1.0),
  _localOrientation(0),
  _ellipsoid("WGS84"),
  _datumHoriz("WGS84"),
  _datumVert("WGS84 ellipsoid")
{ // constructor
} // constructor

// ----------------------------------------------------------------------
// Default destructor
spatialdata::geocoords::CoordSysLocal::~CoordSysLocal(void)
{ // destructor
  delete[] _localOrientation; _localOrientation = 0;
} // destructor


#include<iostream>
// ----------------------------------------------------------------------
// Set origin of local cartesian coordinate system.
void
spatialdata::geocoords::CoordSysLocal::localOrigin(const double lon,
						   const double lat,
						   const double elev,
						   const std::string& ellipsoid,
						   const std::string& datumHoriz,
						   const std::string& datumVert)
{ // localOrigin
  _originLon = lon;
  _originLat = lat;
  _originElev = elev;
  _ellipsoid = ellipsoid;
  _datumHoriz = datumHoriz;
  _datumVert = datumVert;

  const double degToRad = M_PI / 180.0;

  // convert local origin to WGS84
  double lonWGS84 = 0;
  double latWGS84 = 0;
  _geoToWGS84(&lonWGS84, &latWGS84, lon*degToRad, lat*degToRad,
	      ellipsoid.c_str(), datumHoriz.c_str());

  double originElev = elev;
  if (0 != strcasecmp(datumVert.c_str(), "WGS84 ellipsoid"))
    if (0 == strcasecmp(datumVert.c_str(), "mean sea level")) {
      // change vertical datum to WGS84 ellipsoid
      Geoid geoid;
      geoid.initialize();
      const double geoidHt = geoid.elevation(lonWGS84, latWGS84);
      originElev += geoidHt;
    } else {
      std::ostringstream msg;
      msg << "Do not know how to convert from vertical datum '"
	  << datumVert << "' to 'WGS84 ellipsoid'.";
      throw std::runtime_error(msg.str());	
    } // else

  // convert origin and point above origin to ECEF
  double originECEFX = 0;
  double originECEFY = 0;
  double originECEFZ = 0;
  _wgs84ToECEF(&originECEFX, &originECEFY, &originECEFZ,
	       lonWGS84, latWGS84, originElev);
  double aboveOriginECEFX = 0;
  double aboveOriginECEFY = 0;
  double aboveOriginECEFZ = 0;
  const double elevAbove = 25.0e+3;
  _wgs84ToECEF(&aboveOriginECEFX, &aboveOriginECEFY, &aboveOriginECEFZ,
	       lonWGS84, latWGS84, originElev+elevAbove);

  // Create unit vector for local +z direction; local +z direction is
  // normal to Earth's surface at origin; use point above origin to
  // find normal to Earth's surface at origin; make unit vector
  const double dx = aboveOriginECEFX - originECEFX;
  const double dy = aboveOriginECEFY - originECEFY;
  const double dz = aboveOriginECEFZ - originECEFZ;
  const double mag = sqrt(dx*dx + dy*dy + dz*dz);
  const double z0 = dx / mag;
  const double z1 = dy / mag;
  const double z2 = dz / mag;

  // Create unit vector for local +x direction; local +x direction is
  // in ECEF xy plane, parallel to lines of equal latitude
  const double x0 = -sin(lonWGS84);
  const double x1 = cos(lonWGS84);
  const double x2 = 0.0;

  // Create unit vector for local +y direction; local +y direction is
  // cross product of z and x directions
  const double y0 = z1*x2 - x1*z2;
  const double y1 = z2*x0 - x2*z0;
  const double y2 = z0*x1 - x0*z1;

  delete[] _localOrientation; _localOrientation = new double[9];
  _localOrientation[0] = x0;
  _localOrientation[1] = x1;
  _localOrientation[2] = x2;
  _localOrientation[3] = y0;
  _localOrientation[4] = y1;
  _localOrientation[5] = y2;
  _localOrientation[6] = z0;
  _localOrientation[7] = z1;
  _localOrientation[8] = z2;

  _originX = 
    _localOrientation[0]*originECEFX +
    _localOrientation[1]*originECEFY +
    _localOrientation[2]*originECEFZ;
  _originY = 
    _localOrientation[3]*originECEFX +
    _localOrientation[4]*originECEFY +
    _localOrientation[5]*originECEFZ;
  _originZ =
    _localOrientation[6]*originECEFX +
    _localOrientation[7]*originECEFY +
    _localOrientation[8]*originECEFZ;
} // localOrigin

// ----------------------------------------------------------------------
// Convert coordinates to PROJ4 useable form.
void
spatialdata::geocoords::CoordSysLocal::toProjForm(double** ppCoords,
						  const int numLocs,
						  bool is2D) const
{ // toProjForm
  for (int iLoc=0, index=0; iLoc < numLocs; ++iLoc) {
    // add origin to old to invert
    const double xOld = (*ppCoords)[index  ] + _originX;
    const double yOld = (*ppCoords)[index+1] + _originY;
    const double zOld = (*ppCoords)[index+2] + _originZ;
    // multiply by transpose of direction cosines to invert
    (*ppCoords)[index++] = 
      _localOrientation[0]*xOld +
      _localOrientation[3]*yOld +
      _localOrientation[6]*zOld;
    (*ppCoords)[index++] = 
      _localOrientation[1]*xOld +
      _localOrientation[4]*yOld +
      _localOrientation[7]*zOld;
    (*ppCoords)[index++] = 
      _localOrientation[2]*xOld +
	_localOrientation[5]*yOld +
      _localOrientation[8]*zOld;
  } // for
} // toProjForm
  
// ----------------------------------------------------------------------
// Convert coordinates from PROJ4 form to form associated w/coordsys.
void
spatialdata::geocoords::CoordSysLocal::fromProjForm(double** ppCoords,
						    const int numLocs,
						    bool is2D) const
{ // fromProjForm
  for (int iLoc=0, index=0; iLoc < numLocs; ++iLoc) {
    const double xOld = (*ppCoords)[index  ];
    const double yOld = (*ppCoords)[index+1];
    const double zOld = (*ppCoords)[index+2];
    (*ppCoords)[index++] = 
      _localOrientation[0]*xOld +
      _localOrientation[1]*yOld +
      _localOrientation[2]*zOld - _originX;
    (*ppCoords)[index++] = 
      _localOrientation[3]*xOld +
      _localOrientation[4]*yOld +
      _localOrientation[5]*zOld - _originY;
    (*ppCoords)[index++] = 
      _localOrientation[6]*xOld +
      _localOrientation[7]*yOld +
      _localOrientation[8]*zOld - _originZ;
  } // for
} // fromProjForm
  
// ----------------------------------------------------------------------
// Convert coordinates to WGS84.
void
spatialdata::geocoords::CoordSysLocal::_geoToWGS84(double* pLonWGS84,
						   double* pLatWGS84,
						   const double lon,
						   const double lat,
						   const char* ellipsoid,
						   const char* datumHoriz) const
{ // _geoToWGS84
  FIREWALL(0 != pLonWGS84);
  FIREWALL(0 != pLatWGS84);

  // convert lon/lat in rad to lon/lat in rad in WGS84
  if (0 != strcasecmp(datumHoriz, "WGS84") ||
      0 != strcasecmp(ellipsoid, "WGS84")) {      
    std::ostringstream projString;
    projString
      << "+proj=latlong"
      << " +ellps=" << ellipsoid
      << " +datum=" << datumHoriz
      << " +units=m";
    projPJ csSrc = 
      pj_init_plus(projString.str().c_str());
    if (0 == csSrc) {
      std::ostringstream msg;
      msg << "Error while initializing source coordinate system:\n"
	  << "  " << pj_strerrno(pj_errno) << "\n";
      throw std::runtime_error(msg.str());
    } // if
    projPJ csWGS84 = 
      pj_init_plus("+proj=latlong +ellps=WGS84 +datum=WGS84 +units=m");
    if (0 == csWGS84) {
      std::ostringstream msg;
      msg << "Error while initializing WGS84 coordinate system:\n"
	  << "  " << pj_strerrno(pj_errno) << "\n";
      throw std::runtime_error(msg.str());
    } // if
    const int numLocs = 1;
    const int numCoords = 2;
    *pLonWGS84 = lon;
    *pLatWGS84 = lat;
    const int pjerrno = pj_transform(csSrc, csWGS84,
				     numLocs, numCoords, 
				     pLonWGS84, pLatWGS84, 0);
    if (0 != pjerrno) {
      std::ostringstream msg;
      msg << "Error while converting coordinates:\n"
	  << "  " << pj_strerrno(pjerrno) << "\n";
      throw std::runtime_error(msg.str());
    } // if
  } else {
    *pLonWGS84 = lon;
    *pLatWGS84 = lat;
  } // else
} // _geoToWGS84

// ----------------------------------------------------------------------
// Convert coordinates from WGS84 to ECEF.
void
spatialdata::geocoords::CoordSysLocal::_wgs84ToECEF(double* pECEFX,
						    double* pECEFY,
						    double* pECEFZ,
						    const double lonWGS84,
						    const double latWGS84,
						    const double elevWGS84) const
{ // _wgs84ToECEF
  FIREWALL(0 != pECEFX);
  FIREWALL(0 != pECEFY);
  FIREWALL(0 != pECEFZ);

  // convert lon/lat in rad in WGS84 to ECEF in m
  projPJ csWGS84 = 
    pj_init_plus("+proj=latlong +ellps=WGS84 +datum=WGS84 +units=m");
  if (0 == csWGS84) {
    std::ostringstream msg;
    msg << "Error while initializing WGS84 coordinate system:\n"
	<< "  " << pj_strerrno(pj_errno) << "\n";
    throw std::runtime_error(msg.str());
  } // if
  projPJ csECEF = 
    pj_init_plus("+proj=geocent +ellps=WGS84 +datum=WGS84 +units=m");
  if (0 == csECEF) {
    std::ostringstream msg;
    msg << "Error while initializing ECEF coordinate system:\n"
	<< "  " << pj_strerrno(pj_errno) << "\n";
    throw std::runtime_error(msg.str());
  } // if
  const int numLocs = 1;
  const int numCoords = 3;
  *pECEFX = lonWGS84;
  *pECEFY = latWGS84;
  *pECEFZ = elevWGS84;
  const int pjerrno = pj_transform(csWGS84, csECEF,
				   numLocs, numCoords, 
				   pECEFX, pECEFY, pECEFZ);
  if (0 != pjerrno) {
    std::ostringstream msg;
    msg << "Error while converting coordinates:\n"
	<< "  " << pj_strerrno(pjerrno) << "\n";
    throw std::runtime_error(msg.str());
  } // if
} // _wgs84ToECEF

// ----------------------------------------------------------------------
// Get the PROJ4 string associated with the coordinate system.
std::string 
spatialdata::geocoords::CoordSysLocal::_projCSString(void) const
{ // _projCSString
  const char* projString =
    "+proj=geocent +ellps=WGS84 +datum=WGS84 +units=m";
  return std::string(projString);
} // initialize

// version
// $Id$

// version
// $Id$

// End of file 