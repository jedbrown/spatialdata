#!/usr/bin/env python
#
# ======================================================================
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2017 University of California, Davis
#
# See COPYING for license information.
#
# ======================================================================
#

import unittest

import numpy

lonlatNAD27ElevVals = numpy.array([
  [ -1.150000000000e+02,  3.900000000000e+01,  1.200000000000e+01],
  [ -1.203425320000e+02,  4.323423000000e+01,  1.010000000000e+01],
  [ -1.213425320000e+02,  4.523423000000e+01,  3.600000000000e+00],
  [ -1.153425320000e+02,  3.623423000000e+01,  7.200000000000e+00],
  [ -1.103425320000e+02,  3.923423000000e+01,  1.233000000000e+02],
  [ -1.073425320000e+02,  3.323423000000e+01,  3.460000000000e+01] ],
                                    numpy.float64)
xyzLocalVals = numpy.array([
  [ -1.284640403035e+06,  1.064304545254e+05, -1.314223692642e+05],
  [ -1.617989794934e+06,  6.524818198322e+05, -2.429529282853e+05],
  [ -1.637488936891e+06,  8.852730256818e+05, -2.774331803783e+05],
  [ -1.362847273202e+06, -1.913287267443e+05, -1.500646063011e+05],
  [ -8.881745585536e+05,  7.658679833419e+04, -6.239199171253e+04],
  [ -6.825105927499e+05, -6.111332573069e+05, -6.615476872030e+04] ],
                             numpy.float64)

class TestConverter(unittest.TestCase):


  def test_convert(self):
    from spatialdata.geocoords.CSGeo import CSGeo
    csNAD27 = CSGeo()
    csNAD27.inventory.ellipsoid = "clrk66"
    csNAD27.inventory.datumHoriz = "NAD27"
    csNAD27.inventory.datumVert = "mean sea level"
    csNAD27._configure()
    csNAD27.initialize()

    from spatialdata.geocoords.CSGeoLocalCart import CSGeoLocalCart
    csLocal = CSGeoLocalCart()
    csLocal.inventory.originLon = -100.0
    csLocal.inventory.originLat = 39.0
    from pyre.units.length import m
    csLocal.inventory.originElev = 0.01*m
    csLocal.inventory.ellipsoid = "clrk66"
    csLocal.inventory.datumHoriz = "NAD27"
    csLocal.inventory.datumVert = "mean sea level"
    csLocal._configure()
    csLocal.initialize()

    from spatialdata.geocoords.Converter import convert
    coordsXYZ = numpy.array(lonlatNAD27ElevVals)
    convert(coordsXYZ, csLocal, csNAD27)
    xyzLocalValsT = numpy.array(coordsXYZ)

    self.assertEqual(len(xyzLocalVals.shape), len(xyzLocalValsT.shape))
    for (xyz, xyzT) in zip(numpy.reshape(xyzLocalVals,-1),
                           numpy.reshape(xyzLocalValsT, -1)):
      self.assertAlmostEqual(1.0, xyz/xyzT, 6)
        
    return


# End of file 
