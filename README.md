# mountain_sim
## Motivation
This code intends to be able to optimize mountaineering trails using several criterias:
- Safest, from the point of view of triggering avalanches and avoiding avalanches paths
- The least steep trail
- Other possible criterias
## Design
We will need to know the topology with the proper mathematical framework. We will need also to be able to import Digital Elevation Models (DEM) to have the surface terrain. We need ways to graphically represent the surface terrain and the layers corresponding to the risk zones as per the defined criteria to be optimized.
## Structure
* DEM reader
* Solar angle calculator module for solar radiation
* Surface Topology descriptors
* Projection tools
* 3D Plot tool (possibly invoked through a python)
* Fluid/Structure interaction
* Fluids simulator accounting for thermal effects
* Inclusionof weather influence
* Snow/Other materials simulation
* ...
## Execution



