# NodeJS wrapper for ADMesh
This package provides access to some [ADMesh](https://github.com/admesh/admesh) functionality via NodeJS. ADMesh is a library for processing triangulated solid meshes

## Installation
`npm install node-admesh`

## Example
```
const admesh = require('node-admesh')

async function test() {
  let mesh = new admesh.Mesh()
  await mesh.open('broken.stl')
  const repairData = await mesh.repair()
  await mesh.scale(1.5)
  await mesh.rotate('x', 90)
  await mesh.write('fixed.stl')

  console.log(mesh.properties)
}
```

## Methods
#### All methods return a promise
* `open(filename)` - load an stl file into memeory
  * parameters
    * filename - [REQUIRED]
* `write(filename)`
  * parameters
    * filename - [REQUIRED]
returns: Promise
* `scale(factor)`
  * parameters
    * factor - scale multiplier
* `rotate(axis, angle)`
  * parameters
    * axis - Axis of rotation (must be 'x', 'y', or 'z')
    * angle - angle in degrees of rotation
* `repair()` -- runs a repair algorithm on the mesh
  * returns
```
{
  numberOfParts
  facetsAdded
  facetsRemoved
  degenerateFacets
  edgesFixed
  facetsReversed
  backwardsEdges
  normalsFixed
}
```
## Values
* `properties`
```
{
  numberOfParts
  numberOfFacets
  volume
  surfaceArea
}
```
