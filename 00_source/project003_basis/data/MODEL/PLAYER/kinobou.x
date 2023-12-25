xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 81;
 -7.13909;47.21405;-102.77452;,
 -7.13909;53.22372;-102.77452;,
 -7.13909;53.22372;-204.58980;,
 -7.13909;47.21404;-204.58980;,
 5.14279;47.21405;-102.77452;,
 5.14278;47.21404;-215.07396;,
 5.14279;53.22372;-102.77452;,
 5.14278;53.22372;-215.07396;,
 -7.13909;47.21404;-204.58980;,
 -7.13909;53.22372;-204.58980;,
 -7.13909;53.22372;-204.58980;,
 -7.13908;47.21405;-59.15820;,
 5.14279;47.21405;-59.15820;,
 5.14279;53.22372;-59.15820;,
 -7.13908;53.22372;-59.15820;,
 5.14279;53.22372;-94.02967;,
 -7.13909;53.22372;-97.69607;,
 5.14279;47.21405;-94.02967;,
 -7.13909;47.21405;-97.69607;,
 -7.13909;53.22372;-97.69607;,
 -7.13909;53.22372;-102.77452;,
 -7.13908;53.22372;-82.94815;,
 -7.13908;53.22372;-96.80601;,
 -7.13908;47.21405;-96.80601;,
 -7.13908;47.21405;-82.94815;,
 5.14279;47.21405;-93.13991;,
 5.14279;47.21405;-87.87317;,
 5.14279;53.22372;-93.13991;,
 5.14279;53.22372;-87.87317;,
 -7.13908;53.22372;-96.80601;,
 -7.13908;53.22372;-82.94815;,
 5.14279;47.21405;-71.62799;,
 5.14279;47.21405;-77.20422;,
 5.14279;53.22372;-77.20422;,
 5.14279;53.22372;-71.62799;,
 -7.13908;47.21405;-77.01961;,
 -7.13908;53.22372;-64.34372;,
 -7.13908;53.22372;-76.42992;,
 -7.13908;47.21405;-76.42992;,
 -7.13908;47.21405;-64.34372;,
 5.14279;47.21405;-63.55531;,
 5.14279;47.21405;-70.55928;,
 5.14279;53.22372;-70.60522;,
 5.14279;53.22372;-63.58389;,
 -7.13908;53.22372;-76.42992;,
 -7.13908;53.22372;-64.34372;,
 5.14279;53.22372;-70.64180;,
 -7.13908;53.22372;-77.01961;,
 -7.13908;47.21405;-59.15820;,
 -7.13908;47.21405;-63.32228;,
 5.14279;47.21405;-62.48413;,
 5.14279;53.22372;-62.49725;,
 -7.13908;53.22372;-63.32228;,
 -7.13908;53.22372;-59.15820;,
 -7.13908;53.22372;-59.15820;,
 -7.13908;53.22372;-63.32228;,
 5.14279;53.22372;-78.05853;,
 5.14279;53.22372;-87.09740;,
 -7.13908;53.22372;-82.23592;,
 -7.13908;53.22372;-77.78255;,
 5.14279;47.21405;-78.05853;,
 5.14279;47.21405;-87.09740;,
 -7.13908;47.21405;-77.78255;,
 -7.13908;47.21405;-82.23592;,
 -7.13908;53.22372;-77.78255;,
 -7.13908;53.22372;-82.23592;,
 -7.13908;53.22372;-77.01961;,
 -8.75751;46.31147;-56.61867;,
 -8.75751;54.05490;-56.61867;,
 7.06757;54.05490;-56.61867;,
 7.06757;46.31147;-56.61867;,
 7.06756;46.31146;-219.91039;,
 7.06756;54.05489;-219.91039;,
 -8.75752;54.05489;-206.71977;,
 -8.75752;46.31146;-206.71977;,
 -8.75751;46.31147;-56.61867;,
 -8.75752;46.31146;-206.71977;,
 -8.75751;54.05490;-56.61867;,
 -8.75752;54.05489;-206.71977;,
 -8.75751;54.05490;-56.61867;,
 -8.75752;54.05489;-206.71977;;
 
 59;
 4;0,1,2,3;,
 4;4,0,3,5;,
 4;6,4,5,7;,
 4;5,8,9,7;,
 4;1,6,7,10;,
 4;11,12,13,14;,
 4;15,6,1,16;,
 4;17,4,6,15;,
 4;18,0,4,17;,
 4;19,20,0,18;,
 4;21,22,23,24;,
 4;24,23,25,26;,
 4;26,25,27,28;,
 4;28,27,29,30;,
 4;31,32,33,34;,
 3;35,32,31;,
 4;36,37,38,39;,
 4;40,41,42,43;,
 3;44,45,46;,
 3;45,43,42;,
 3;42,46,45;,
 4;39,38,41,40;,
 3;47,34,33;,
 4;48,49,50,12;,
 4;13,51,52,53;,
 4;12,50,51,13;,
 4;54,55,49,48;,
 4;56,57,58,59;,
 4;60,61,57,56;,
 4;62,63,61,60;,
 4;64,65,63,62;,
 4;22,19,18,23;,
 4;23,18,17,25;,
 4;25,17,15,27;,
 4;27,15,16,29;,
 4;44,46,34,47;,
 4;33,56,59,47;,
 4;32,60,56,33;,
 4;35,62,60,32;,
 4;37,66,35,38;,
 4;66,64,62,35;,
 3;41,31,42;,
 3;31,34,46;,
 3;46,42,31;,
 4;41,38,35,31;,
 4;49,39,40,50;,
 4;51,43,45,52;,
 4;50,40,43,51;,
 4;55,36,39,49;,
 4;57,28,30,58;,
 4;61,26,28,57;,
 4;63,24,26,61;,
 4;65,21,24,63;,
 4;67,68,69,70;,
 4;71,72,73,74;,
 4;75,70,71,76;,
 4;69,77,78,72;,
 4;70,69,72,71;,
 4;79,75,76,80;;
 
 MeshMaterialList {
  13;
  59;
  8,
  8,
  8,
  8,
  8,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  9,
  9,
  9,
  9,
  9,
  9;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.721600;0.721600;0.721600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.420000;0.009600;0.031200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.640000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.640000;0.640000;0.640000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.093105;0.093105;0.093105;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.095478;0.052423;0.024772;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.640000;0.640000;0.640000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.640000;0.640000;0.640000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  37;
  0.000000;0.000000;1.000000;,
  -0.908088;0.000000;-0.418778;,
  1.000000;0.000000;-0.000000;,
  0.000000;-1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  1.000000;0.000000;-0.000000;,
  0.000000;-1.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;0.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;-0.000000;,
  1.000000;-0.000000;-0.000000;,
  1.000000;-0.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.649249;0.000000;-0.760576;,
  -0.000000;1.000000;-0.000000;,
  -0.000000;1.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;-0.000000;-0.000000;,
  1.000000;-0.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.905614;0.000000;0.424104;,
  0.640272;0.000000;0.768149;,
  -0.000000;1.000000;-0.000000;,
  0.000000;-1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;-0.000000;;
  59;
  4;4,4,1,1;,
  4;5,5,3,3;,
  4;6,6,2,2;,
  4;19,1,1,19;,
  4;20,20,21,21;,
  4;0,0,0,0;,
  4;10,20,20,10;,
  4;9,6,6,9;,
  4;7,5,5,7;,
  4;22,4,4,22;,
  4;18,8,8,18;,
  4;7,7,7,7;,
  4;11,11,11,11;,
  4;10,10,10,10;,
  4;15,13,13,13;,
  3;7,7,7;,
  4;14,14,14,14;,
  4;16,16,17,16;,
  3;10,10,10;,
  3;10,10,10;,
  3;10,10,10;,
  4;7,7,7,7;,
  3;10,10,10;,
  4;7,7,7,7;,
  4;10,10,10,10;,
  4;23,24,24,23;,
  4;25,26,26,25;,
  4;10,10,10,10;,
  4;12,12,12,12;,
  4;7,7,7,7;,
  4;27,27,27,27;,
  4;8,22,22,8;,
  4;7,7,7,7;,
  4;11,9,9,11;,
  4;10,10,10,10;,
  4;10,10,10,10;,
  4;10,10,10,10;,
  4;13,12,12,13;,
  4;7,7,7,7;,
  4;14,28,28,14;,
  4;28,27,27,28;,
  3;16,15,17;,
  3;15,13,29;,
  3;29,17,15;,
  4;7,7,7,7;,
  4;7,7,7,7;,
  4;10,10,10,10;,
  4;24,16,16,24;,
  4;26,14,14,26;,
  4;10,10,10,10;,
  4;12,11,11,12;,
  4;7,7,7,7;,
  4;27,18,18,27;,
  4;30,30,30,30;,
  4;32,32,31,31;,
  4;33,33,33,33;,
  4;34,34,34,34;,
  4;35,35,35,35;,
  4;36,36,31,31;;
 }
 MeshTextureCoords {
  81;
  0.435000;0.250000;,
  0.435000;1.000000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.435000;0.500000;,
  0.625000;0.500000;,
  0.435000;0.750000;,
  0.625000;0.750000;,
  0.875000;0.500000;,
  0.875000;0.750000;,
  0.625000;1.000000;,
  0.125000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.125000;0.750000;,
  0.418301;0.750000;,
  0.418301;1.000000;,
  0.418301;0.500000;,
  0.418301;0.250000;,
  0.418301;0.000000;,
  0.435000;0.000000;,
  0.396497;0.000000;,
  0.398301;0.000000;,
  0.398301;0.250000;,
  0.396497;0.250000;,
  0.398301;0.500000;,
  0.396497;0.500000;,
  0.398301;0.750000;,
  0.396497;0.750000;,
  0.398301;1.000000;,
  0.396497;1.000000;,
  0.381842;0.500000;,
  0.385370;0.500000;,
  0.385370;0.750000;,
  0.381842;0.750000;,
  0.385370;0.250000;,
  0.379276;0.000000;,
  0.381842;0.000000;,
  0.381842;0.250000;,
  0.379276;0.250000;,
  0.379094;0.500000;,
  0.381551;0.500000;,
  0.381577;0.750000;,
  0.379111;0.750000;,
  0.381842;1.000000;,
  0.379276;1.000000;,
  0.381598;0.750000;,
  0.385370;1.000000;,
  0.375000;0.250000;,
  0.376996;0.250000;,
  0.376911;0.500000;,
  0.376918;0.750000;,
  0.376996;1.000000;,
  0.375000;1.000000;,
  0.375000;0.000000;,
  0.376996;0.000000;,
  0.393137;0.750000;,
  0.394776;0.750000;,
  0.394776;1.000000;,
  0.393137;1.000000;,
  0.393137;0.500000;,
  0.394776;0.500000;,
  0.393137;0.250000;,
  0.394776;0.250000;,
  0.393137;0.000000;,
  0.394776;0.000000;,
  0.385370;0.000000;,
  0.125000;0.500000;,
  0.125000;0.750000;,
  0.375000;0.750000;,
  0.375000;0.500000;,
  0.625000;0.500000;,
  0.625000;0.750000;,
  0.875000;0.750000;,
  0.875000;0.500000;,
  0.375000;0.250000;,
  0.625000;0.250000;,
  0.375000;1.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.625000;0.000000;;
 }
}
