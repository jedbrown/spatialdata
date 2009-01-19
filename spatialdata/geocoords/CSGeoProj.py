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

## @file spatialdata/geocoords/CSGeoProj.py
##
## @brief Python manager for geographic coordinate systems.
##
## Factory: CSGeoProj

from CSGeo import CSGeo
from geocoords import CSGeoProj as ModuleCSGeoProj

# CoordSysGeo class
class CSGeoProj(CSGeo, ModuleCSGeoProj):
  """
  Python manager for projected geographic coordinate systems.

  Factory: CSGeoProj
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(CSGeo.Inventory):
    """
    Python object for managing CSGeoProj facilities and properties.
    """

    ## @class Inventory
    ## Python object for managing CSGeoProj facilities and properties.
    ##
    ## \b Properties
    ## @li None
    ##
    ## \b Facilities
    ## @li \b projector Geographic coordinate projector

    import pyre.inventory

    from Projector import Projector
    projector = pyre.inventory.facility("projector", family="projector",
                                        factory=Projector)
    projector.meta['tip'] = "Geographic coordinate projector."


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="csgeoproj"):
    """
    Constructor.
    """
    CSGeo.__init__(self, name)
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Setup members using inventory.
    """
    CSGeo._configure(self)
    self.projector(self.inventory.projector)
    return


  def _createModuleObj(self):
    """
    Create Python module object.
    """
    ModuleCSGeoProj.__init__(self)
    return


# FACTORIES ////////////////////////////////////////////////////////////

def coordsys():
  """
  Factory associated with CoordSys.
  """
  return CSGeoProj()


# End of file 
