#!/usr/bin/env python
#
# ----------------------------------------------------------------------
#
#                           Brad T. Aagaard
#                        U.S. Geological Survey
#
# <LicenseText>
#
# ----------------------------------------------------------------------
#

## @file spatialdata/spatialdb/generator/Values.py
##
## @brief Python manager for values in database.
##
## Factory: database_values

from pyre.components.Component import Component

# Values class
class Values(Component):
  """
  Python manager for values in database.

  Factory: database_values
  """

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="values"):
    """
    Constructor.
    """
    Component.__init__(self, name, facility="database_values")
    self.values = []
    return


# FACTORIES ////////////////////////////////////////////////////////////

def database_values():
  """
  Factory associated with Values.
  """
  return Values()


# End of file 
