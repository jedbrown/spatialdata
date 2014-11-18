#!/usr/bin/env python
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2014 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

## @file spatialdata/spatialdb/UniformDB.py
##
## @brief Python manager for spatial database with uniform values.
##
## Factory: spatial_database

from SpatialDBObj import SpatialDBObj
from spatialdb import UniformDB as ModuleUniformDB

# UniformDB class
class UniformDB(SpatialDBObj, ModuleUniformDB):
  """
  Python manager for spatial database with uniform values.

  Factory: spatial_database
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(SpatialDBObj.Inventory):
    """
    Python object for managing UniformDB facilities and properties.
    """

    ## @class Inventory
    ## Python object for managing UniformDB facilities and properties.
    ##
    ## \b Properties
    ## @li \b values Names of values in spatial database.
    ## @li \b data Values in spatial database.
    ##
    ## \b Facilities
    ## @li none

    import pyre.inventory

    values = pyre.inventory.list("values", default=[])
    values.meta['tip'] = "Names of values in spatial database."

    data = pyre.inventory.list("data", default=[])
    data.meta['tip'] = "Values in spatial database."


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="uniformdb"):
    """
    Constructor.
    """
    SpatialDBObj.__init__(self, name)
    from pyre.units import parser
    self.parser = parser()
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Set members based on inventory.
    """
    SpatialDBObj._configure(self)
    self._validateParameters(self.inventory)
    data = []
    units = []
    for x in self.inventory.data:
      if len(str(x).split("*")) > 1:
        xdim = self.parser.parse(str(x))
        data.append(float((xdim.value)))
        strDeriv = xdim._strDerivation()
        if len(strDeriv) > 0:
          units.append(xdim._strDerivation())
        else:
          units.append("none")
      else:
        data.append(float(x))
        units.append("none")
    values = []
    for v in self.inventory.values:
      values.append(v.lstrip().rstrip())
    self.setData(values, units, data)
    return

  
  def _createModuleObj(self):
    """
    Create Python module object.
    """
    ModuleUniformDB.__init__(self)
    return


  def _validateParameters(self, params):
    """
    Validate parameters.
    """
    if len(params.values) == 0:
      raise ValueError("Values in UniformDB not specified.")
    if len(params.data) == 0:
      raise ValueError("Data for UniformDB not specified.")
    if len(params.values) != len(params.data):
      raise ValueError, \
            "Incompatible settings for uniform spatial database '%s'.\n"\
            "'values' and 'data' must be lists of the same size.\n"\
            "'values' has size of %d but 'data' has size of %d." \
            % (self.label, len(params.values), len(params.data))
    try:
      for x in params.data:
        if len(str(x).split("*")) > 1:
          xdim = self.parser.parse(str(x))
          dataFloat = float(xdim.value)
        else:
          dataFloat = float(x)
    except:
        raise ValueError, \
              "'data' list must contain dimensioned or nondimensional values."
    return
  

# FACTORIES ////////////////////////////////////////////////////////////

def spatial_database():
  """
  Factory associated with UniformDB.
  """
  return UniformDB()


# End of file 
