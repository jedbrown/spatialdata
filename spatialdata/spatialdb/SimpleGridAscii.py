#!/usr/bin/env python
#
# ----------------------------------------------------------------------
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
# ----------------------------------------------------------------------
#

## @file spatialdata/spatialdb/SimpleGridAscii.py
##
## @brief Python ascii I/O manager for simple gridd spatial database
## (SimpleGridDB).
##
## Factory: simplegrid_io

from pyre.components.Component import Component
from spatialdb import SimpleGridAscii as ModuleSimpleGridAscii

# Validator for filename
def validateFilename(value):
  """
  Validate filename.
  """
  if 0 == len(value):
    raise ValueError("Filename for spatial database not specified.")
  return value


# SimpleGridAscii class
class SimpleGridAscii(Component, ModuleSimpleGridAscii):
  """
  Python ascii I/O manager for simple grid spatial database
  (SimpleGridDB).

  Factory: simplegrid_io
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(Component.Inventory):
    """
    Python object for managing SimpleIO facilities and properties.
    """

    ## @class Inventory
    ## Python object for managing SimpleIO facilities and properties.
    ##
    ## \b Properties
    ## @li \b filename Name of database file
    ##
    ## \b Facilities
    ## @li None

    import pyre.inventory

    filename = pyre.inventory.str("filename", default="", validator=validateFilename)
    filename.meta['tip'] = "Name of database file."


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="simpleioascii"):
    """
    Constructor.
    """
    Component.__init__(self, name, facility="simplegrid_io")
    return


  def write(self, data):
    """
    Write database to file.

    @param data Dictionary of the following form:
      data = {'points': 2-D array (numLocs, spaceDim),
              'x': Array of x coordinates,
              'y': Array of y coordinates,
              'z': Array of z coordinates,
              'coordsys': Coordinate system associated with locations,
              'data_dim': Dimension of spatial distribution,
              'values': [{'name': Name of value,
                          'units': Units of value,
                          'data': Data for value (numLocs)}]}
    """
    import numpy

    (numLocs, spaceDim) = data['points'].shape
    numValues = len(data['values'])    
    names = []
    units = []
    values = numpy.zeros( (numLocs, numValues), dtype=numpy.float64)
    i = 0
    for value in data['values']:
      names.append(value['name'])
      units.append(value['units'])
      values[:,i] = value['data'][:]
      i += 1

    numX = data['x'].shape[0]
    numY = data['y'].shape[0]
    if data['coordsys'].spaceDim() == 2:
      numZ = 0
      if (numLocs != numX*numY):
        raise ValueError("Number of locations (%d) does not match coordinate dimensions (%d, %d)." % (numLocs, numX, numY))
    else:
      numZ = data['z'].shape[0]
      if (numLocs != numX*numY*numZ):
        raise ValueError("Number of locations (%d) does not match coordinate dimensions (%d, %d, %d)." % (numLocs, numX, numY, numZ))

    from SimpleGridDB import SimpleGridDB
    db = SimpleGridDB()
    db.inventory.label = "Temporary database for I/O"
    db.inventory.filename = self.filename
    db._configure()
    db.coordsys(data['coordsys'])
    db.allocate(numX, numY, numZ, numValues, spaceDim, data['data_dim'])
    db.x(data['x'])
    db.y(data['y'])
    if data['coordsys'].spaceDim() == 3:
      db.z(data['z'])
    db.data(data['points'], values)
    db.names(names)
    db.units(units)

    ModuleSimpleGridAscii.write(db)
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Set members using inventory.
    """
    try:
      Component._configure(self)
      self.filename = self.inventory.filename
    except ValueError, err:
      aliases = ", ".join(self.aliases)
      raise ValueError("Error while configuring spatial database reader "
                       "(%s):\n%s" % (aliases, err.message))
    return


  def _createModuleObj(self):
    """
    Create Python module object.
    """
    ModuleSimpleGridAscii.__init__(self)
    return


# FACTORIES ////////////////////////////////////////////////////////////

def simplegrid_io():
  """
  Factory associated with SimpleGridAscii.
  """
  return SimpleGridAscii()


# End of file 
