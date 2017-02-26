SetFactory("OpenCASCADE");

Mesh.CharacteristicLengthMin = 3;
Mesh.CharacteristicLengthMax = 3;

DefineConstant[
  z = {16, Name "Parameters/z position of block"}
  sph = {0, Choices{0,1}, Name "Parameters/Add sphere?"}
];

a() = ShapeFromFile("component8.step");

Block(2) = {0,156,z, 10,170,z+10};
b() = 2;

If(sph)
  Sphere(3) = {0,150,0, 20};
  b() += 3;
EndIf

r() = BooleanFragments{ Volume{a(0)}; Delete; }{ Volume{b()}; Delete; };

Recursive Color SteelBlue { Volume{r()}; }

Save "merged.brep";

Physical Volume("Combined volume", 1) = {r()};
Physical Surface("Combined boundary", 2) = CombinedBoundary{ Volume{r()}; };
