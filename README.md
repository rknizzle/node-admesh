# NodeJS wrapper for ADMesh
This package provides access to some [ADMesh](https://github.com/admesh/admesh) functionality via NodeJS. ADMesh is a library for processing triangulated solid meshes

## Installation
`npm install node-admesh`

## Usage
```
const admesh = require('node-admesh')

let mesh = new admesh.Mesh()
await mesh.open('broken.stl')
await mesh.repair()
await mesh.write('fixed.stl')

console.log(mesh.properties)
```
