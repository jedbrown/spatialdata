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

from spatialdata.utils.UnitTestApp import UnitTestApp

import unittest

class TestApp(UnitTestApp):
  """Test application.
  """

  def __init__(self):
    """Constructor.
    """
    UnitTestApp.__init__(self)
    return

  def _suite(self):
    """Setup the test suite.
    """
    suite = unittest.TestSuite()

    from TestCSCart import TestCSCart
    suite.addTest(unittest.makeSuite(TestCSCart))

    from TestCSGeo import TestCSGeo
    suite.addTest(unittest.makeSuite(TestCSGeo))
    
    from TestCSGeoLocalCart import TestCSGeoLocalCart
    suite.addTest(unittest.makeSuite(TestCSGeoLocalCart))
    
    from TestCSGeoProj import TestCSGeoProj
    suite.addTest(unittest.makeSuite(TestCSGeoProj))
    
    from TestProjector import TestProjector
    suite.addTest(unittest.makeSuite(TestProjector))
    
    from TestConverter import TestConverter
    suite.addTest(unittest.makeSuite(TestConverter))
    
    return suite

# ----------------------------------------------------------------------
if __name__ == '__main__':
  app = TestApp()
  app.run()


# End of file 
