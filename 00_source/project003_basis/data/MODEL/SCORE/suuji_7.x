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
 25;
 -68.09641;173.59933;23.73149;,
 61.11524;200.84805;23.73148;,
 -68.09641;200.84805;23.73149;,
 18.33770;173.59933;23.73149;,
 -29.42080;-1.61284;23.73148;,
 -54.91153;9.52104;23.73148;,
 -68.09641;173.59933;-5.56819;,
 -68.09641;200.84805;-5.56819;,
 61.11524;200.84805;-5.56820;,
 18.33770;173.59933;-5.56820;,
 -29.42080;-1.61284;-5.56821;,
 -54.91153;9.52104;-5.56820;,
 -54.91153;9.52104;23.73148;,
 18.33770;173.59933;23.73149;,
 18.33770;173.59933;-5.56820;,
 -68.09641;173.59933;23.73149;,
 -68.09641;173.59933;-5.56819;,
 -68.09641;200.84805;23.73149;,
 -68.09641;200.84805;-5.56819;,
 61.11524;200.84805;23.73148;,
 61.11524;200.84805;-5.56820;,
 -29.42080;-1.61284;23.73148;,
 -29.42080;-1.61284;-5.56821;,
 -54.91153;9.52104;23.73148;,
 -54.91153;9.52104;-5.56820;;
 
 14;
 3;0,1,2;,
 3;0,3,1;,
 3;3,4,1;,
 3;5,4,3;,
 3;6,7,8;,
 3;6,8,9;,
 3;9,8,10;,
 3;11,9,10;,
 4;12,13,14,11;,
 4;13,15,16,14;,
 4;15,17,18,16;,
 4;17,19,20,18;,
 4;19,21,22,20;,
 4;21,23,24,22;;
 
 MeshMaterialList {
  1;
  14;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  18;
  0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;-0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.913138;0.407651;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.912883;-0.408221;-0.000000;,
  -0.400266;-0.916399;0.000000;;
  14;
  3;2,4,3;,
  3;2,1,4;,
  3;1,5,4;,
  3;0,5,1;,
  3;8,9,10;,
  3;8,10,7;,
  3;7,10,11;,
  3;6,7,11;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;;
 }
 MeshTextureCoords {
  25;
  0.400000;0.000000;,
  0.800000;0.000000;,
  0.600000;0.000000;,
  0.200000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.400000;0.000000;,
  0.600000;0.000000;,
  0.800000;0.000000;,
  0.200000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.166667;1.000000;,
  0.166667;0.000000;,
  0.333333;1.000000;,
  0.333333;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.666667;1.000000;,
  0.666667;0.000000;,
  0.833333;1.000000;,
  0.833333;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;;
 }
}
