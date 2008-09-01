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


class TestCompositeDB(unittest.TestCase):

  def setUp(self):
    from spatialdata.spatialdb.UniformDB import UniformDB
    dbA = UniformDB()
    dbA.label = "db A"
    dbA.values = ["one", "two", "three"]
    dbA.data = [1.1, 2.2, 3.3]
    dbA.initialize()
    
    dbB = UniformDB()
    dbB.label = "db B"
    dbB.values = ["two", "three", "four", "five" ]
    dbB.data = [2.1, 3.1, 4.1, 5.1]
    dbB.initialize()

    from spatialdata.spatialdb.CompositeDB import CompositeDB
    db = CompositeDB()
    db.inventory.dbA = dbA
    db.inventory.namesA = ["two", "one"]
    db.inventory.dbB = dbB
    db.inventory.namesB = ["three", "five"]
    db._configure()
    db.initialize()

    self._db = db
    return

  def test_database(self):
    locs = numpy.array( [[1.0, 2.0, 3.0],
                         [5.6, 4.2, 8.6]],
                        numpy.float64)
    from spatialdata.geocoords.CSCart import CSCart
    cs = CSCart()
    queryVals = ["three", "one", "five"]
    dataE = numpy.array([[3.1, 1.1, 5.1],
                         [3.1, 1.1, 5.1]], numpy.float64)
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


# End of file 