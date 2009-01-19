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

from spatialdata.units.NondimElasticQuasistatic import NondimElasticQuasistatic

from pyre.units.length import meter
from pyre.units.pressure import pascal
from pyre.units.time import year
from pyre.units.mass import kilogram    

class TestNondimElasticQuasistatic(unittest.TestCase):

  def test_constructor(self):
    dim = NondimElasticQuasistatic()
    dim._configure()

    self.assertEqual(1.0e+3*meter, dim.lengthScale())
    self.assertEqual(3.0e+10*pascal, dim.pressureScale())
    self.assertEqual(1.0*year, dim.timeScale())
    self.assertEqual(1.0*kilogram/meter**3, dim.densityScale())

    return


# End of file 
