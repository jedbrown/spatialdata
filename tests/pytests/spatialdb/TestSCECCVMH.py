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

import numpy

class TestSCECCVMH(unittest.TestCase):

  def setUp(self):
    from spatialdata.spatialdb.SCECCVMH import SCECCVMH
    db = SCECCVMH()
    db._configure()
    db.dataDir = "/Users/brad/data/sceccvm-h/vx52/bin"
    db.initialize()
    self._db = db
    return


  def test_query(self):
    locs = numpy.array( [[-118.520000,  34.120000,  -1400.00],
                         [-116.400000,  32.340000,  -1000.00]],
                        numpy.float64)
    from spatialdata.geocoords.CSGeo import CSGeo
    cs = CSGeo()
    cs._configure()
    cs.datumHoriz = "NAD27"
    cs.datumVert = "mean sea level"
    cs.ellipsoid = "clrk66"
    cs.initialize()
    queryVals = ["topo-elev", "moho-depth", "density"]
    dataE = numpy.array([[489.975189, -31178.105469,   2660.851074],
                         [801.209961, -34526.414062,   3022.192708]],
                        numpy.float64)
    errE = numpy.array( [0]*2, numpy.int32)
    
    self._db.open()
    self._db.queryVals(queryVals)
    (data, err) = self._db.query(locs, cs, 3)
    data = numpy.array(data)
    err = numpy.array(err)

    self.assertEqual(len(errE.shape), len(err.shape))
    for dE, d in zip(errE.shape, err.shape):
      self.assertEqual(dE, d)
    for vE, v in zip(numpy.reshape(errE, -1), numpy.reshape(err, -1)):
      self.assertEqual(vE, v)

    self.assertEqual(len(dataE.shape), len(data.shape))
    for dE, d in zip(dataE.shape, data.shape):
      self.assertEqual(dE, d)
    for vE, v in zip(numpy.reshape(dataE, -1), numpy.reshape(data, -1)):
      self.assertAlmostEqual(vE, v, 6)

    self._db.close()    
    return


  def test_querySquash(self):
    locs = numpy.array( [[-118.520000,  34.120000,  -1400.00],
                         [-116.400000,  32.340000,  -1000.00]],
                        numpy.float64)
    from spatialdata.geocoords.CSGeo import CSGeo
    cs = CSGeo()
    cs._configure()
    cs.datumHoriz = "NAD27"
    cs.datumVert = "mean sea level"
    cs.ellipsoid = "clrk66"
    cs.initialize()
    queryVals = ["topo-elev", "moho-depth", "density"]
    dataE = numpy.array([[489.975189, -31178.105469,   2660.851074],
                         [801.209961, -34526.414062,   3022.192708]],
                        numpy.float64)
    errE = numpy.array( [0]*2, numpy.int32)
    
    self._db.open()
    self._db.queryVals(queryVals)
    self._db.squash = True
    from pyre.units.length import km
    self._db.squashLimit = -2.5*km
    (data, err) = self._db.query(locs, cs, 3)
    data = numpy.array(data)
    err = numpy.array(err)

    self.assertEqual(len(errE.shape), len(err.shape))
    for dE, d in zip(errE.shape, err.shape):
      self.assertEqual(dE, d)
    for vE, v in zip(numpy.reshape(errE, -1), numpy.reshape(err, -1)):
      self.assertEqual(vE, v)

    self.assertEqual(len(dataE.shape), len(data.shape))
    for dE, d in zip(dataE.shape, data.shape):
      self.assertEqual(dE, d)
    for vE, v in zip(numpy.reshape(dataE, -1), numpy.reshape(data, -1)):
      self.assertAlmostEqual(vE, v, 6)

    self._db.close()    
    return


# End of file 
