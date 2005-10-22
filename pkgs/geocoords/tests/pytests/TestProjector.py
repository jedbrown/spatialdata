#!/usr/bin/env python
#
# ======================================================================
#
#                           Brad T. Aagaard
#                        U.S. Geological Survey
#
# {LicenseText}
#
# ======================================================================
#

import unittest

projection = "aea"
falseEasting = -100.0
falseNorthing = 30.0
scaleFactor = 0.9996
units = "km"
lonlatVals = [ [-1.203425320000e+02,  5.323423000000e+01],
               [-5.330394500000e+01,  3.334902000000e+01],
               [ 3.422908500000e+01, -2.523422000000e+01],
               [ 1.420845230000e+02, -3.439085000000e+01],
               [ 4.990854300000e+01,  2.409830000000e+00] ]
xyVals = [ [ -1.397886620000e+03,  2.729173050000e+03],
           [  4.145823900000e+03,  1.412439200000e+03],
           [  1.424820130000e+04,  6.884278430000e+03],
           [ -1.424775469000e+04,  4.279122720000e+03],
           [  1.205623096000e+04,  9.239581410000e+03] ]

class TestProjector(unittest.TestCase):


  def setUp(self):
    from spatialdata.geocoords.CoordSysGeo import CoordSysGeo
    coordSys = CoordSysGeo()
    coordSys.initialize()
    
    from spatialdata.geocoords.Projector import Projector
    self.projector = Projector()
    
    self.projector.projection = projection
    self.projector.falseEasting = falseEasting
    self.projector.falseNorthing = falseNorthing
    self.projector.scaleFactor = scaleFactor
    self.projector.units = units
    self.projector.coordSys = coordSys
    return
  

  def test_initialize(self):
    self.projector.initialize()
    return


  def test_project(self):
    self.projector.initialize()
    xyValsT = self.projector.project(lonlatVals)
    self.assertEqual(len(xyVals), len(xyValsT))
    for (xy, xyT) in zip(xyVals, xyValsT):
      self.assertAlmostEqual(xy[0], xyT[0], 4)
      self.assertAlmostEqual(xy[1], xyT[1], 4)
    return

  def test_invproject(self):
    self.projector.initialize()
    lonlatValsT = self.projector.invproject(xyVals)
    self.assertEqual(len(lonlatVals), len(lonlatValsT))
    for (lonlat, lonlatT) in zip(lonlatVals, lonlatValsT):
      self.assertAlmostEqual(lonlat[0], lonlatT[0], 4)
      self.assertAlmostEqual(lonlat[1], lonlatT[1], 4)
    return

# version
__id__ = "$Id$"

# End of file 