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
 63;
 -62.52947;79.84031;23.73149;,
 50.86035;203.48502;23.73149;,
 38.55447;203.48502;23.73149;,
 21.56066;149.28058;23.73149;,
 22.14666;149.28058;23.73149;,
 50.86035;92.43918;23.73149;,
 -24.14686;92.43918;23.73149;,
 22.14666;92.43918;23.73149;,
 72.24912;92.43918;23.73148;,
 72.24912;66.65544;23.73148;,
 -62.52947;66.65544;23.73149;,
 22.14666;66.65544;23.73149;,
 22.14666;1.02413;23.73148;,
 50.86035;66.65544;23.73149;,
 50.86035;1.02413;23.73148;,
 -62.52947;79.84031;-5.56819;,
 38.55447;203.48502;-5.56820;,
 50.86035;203.48502;-5.56820;,
 21.56065;149.28058;-5.56820;,
 22.14665;149.28058;-5.56820;,
 50.86035;92.43918;-5.56820;,
 -24.14687;92.43918;-5.56820;,
 22.14665;92.43918;-5.56820;,
 72.24912;92.43918;-5.56820;,
 72.24912;66.65544;-5.56820;,
 -62.52947;66.65544;-5.56819;,
 22.14665;66.65544;-5.56820;,
 22.14665;1.02413;-5.56821;,
 50.86035;66.65544;-5.56820;,
 50.86035;1.02413;-5.56821;,
 72.24912;92.43918;23.73148;,
 72.24912;66.65544;23.73148;,
 72.24912;66.65544;-5.56820;,
 50.86035;66.65544;23.73149;,
 50.86035;66.65544;-5.56820;,
 50.86035;1.02413;23.73148;,
 50.86035;1.02413;-5.56821;,
 22.14666;1.02413;23.73148;,
 22.14665;1.02413;-5.56821;,
 22.14666;66.65544;23.73149;,
 22.14665;66.65544;-5.56820;,
 -62.52947;66.65544;23.73149;,
 -62.52947;66.65544;-5.56819;,
 -62.52947;79.84031;23.73149;,
 -62.52947;79.84031;-5.56819;,
 38.55447;203.48502;23.73149;,
 38.55447;203.48502;-5.56820;,
 50.86035;203.48502;23.73149;,
 50.86035;203.48502;-5.56820;,
 50.86035;92.43918;23.73149;,
 50.86035;92.43918;-5.56820;,
 72.24912;92.43918;23.73148;,
 72.24912;92.43918;-5.56820;,
 22.14666;92.43918;23.73149;,
 22.14666;149.28058;23.73149;,
 22.14665;149.28058;-5.56820;,
 22.14665;92.43918;-5.56820;,
 21.56066;149.28058;23.73149;,
 21.56065;149.28058;-5.56820;,
 -24.14686;92.43918;23.73149;,
 -24.14687;92.43918;-5.56820;,
 22.14666;92.43918;23.73149;,
 22.14665;92.43918;-5.56820;;
 
 45;
 3;0,1,2;,
 3;0,3,1;,
 3;3,4,1;,
 3;4,5,1;,
 3;0,6,3;,
 3;7,5,4;,
 3;0,7,6;,
 3;0,5,7;,
 3;0,8,5;,
 3;0,9,8;,
 3;10,9,0;,
 3;11,9,10;,
 3;12,13,11;,
 3;13,9,11;,
 3;12,14,13;,
 3;15,16,17;,
 3;15,17,18;,
 3;18,17,19;,
 3;19,17,20;,
 3;15,18,21;,
 3;22,19,20;,
 3;15,21,22;,
 3;15,22,20;,
 3;15,20,23;,
 3;15,23,24;,
 3;25,15,24;,
 3;26,25,24;,
 3;27,26,28;,
 3;28,26,24;,
 3;27,28,29;,
 4;30,31,32,23;,
 4;31,33,34,32;,
 4;33,35,36,34;,
 4;35,37,38,36;,
 4;37,39,40,38;,
 4;39,41,42,40;,
 4;41,43,44,42;,
 4;43,45,46,44;,
 4;45,47,48,46;,
 4;47,49,50,48;,
 4;49,51,52,50;,
 4;53,54,55,56;,
 4;54,57,58,55;,
 4;57,59,60,58;,
 4;59,61,62,60;;
 
 MeshMaterialList {
  1;
  45;
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
  37;
  0.000000;-0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;-0.000000;-1.000000;,
  -0.000000;-0.000000;-1.000000;,
  -0.000000;-0.000000;-1.000000;,
  -0.000000;-0.000000;-1.000000;,
  -0.000000;-0.000000;-1.000000;,
  -0.000000;-0.000000;-1.000000;,
  -0.000000;-0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  0.000000;-0.000000;1.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;-0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.941861;0.336004;0.000000;,
  -0.428405;0.903587;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.432057;-0.901846;-0.000000;,
  0.779299;-0.626653;-0.000000;;
  45;
  3;6,8,7;,
  3;6,12,8;,
  3;12,11,8;,
  3;11,9,8;,
  3;6,13,12;,
  3;10,9,11;,
  3;6,10,13;,
  3;6,9,10;,
  3;6,0,9;,
  3;6,1,0;,
  3;5,1,6;,
  3;4,4,4;,
  3;2,2,28;,
  3;18,18,18;,
  3;2,3,2;,
  3;20,21,22;,
  3;20,22,26;,
  3;26,22,25;,
  3;25,22,23;,
  3;20,26,27;,
  3;24,25,23;,
  3;20,27,24;,
  3;20,24,23;,
  3;20,23,14;,
  3;20,14,15;,
  3;19,20,15;,
  3;18,18,18;,
  3;16,17,16;,
  3;4,4,4;,
  3;16,16,17;,
  4;29,29,29,29;,
  4;4,4,4,4;,
  4;29,29,29,29;,
  4;4,4,4,4;,
  4;30,30,30,30;,
  4;4,4,4,4;,
  4;31,32,32,31;,
  4;32,33,33,32;,
  4;33,18,18,33;,
  4;29,29,29,29;,
  4;18,18,18,18;,
  4;34,34,34,34;,
  4;4,35,35,4;,
  4;35,36,36,35;,
  4;18,18,18,18;;
 }
 MeshTextureCoords {
  63;
  0.500000;0.000000;,
  0.642857;0.000000;,
  0.571429;0.000000;,
  0.928571;0.000000;,
  0.857143;0.000000;,
  0.714286;0.000000;,
  1.000000;0.000000;,
  0.785714;0.000000;,
  0.000000;0.000000;,
  0.071429;0.000000;,
  0.428571;0.000000;,
  0.357143;0.000000;,
  0.285714;0.000000;,
  0.142857;0.000000;,
  0.214286;0.000000;,
  0.500000;0.000000;,
  0.571429;0.000000;,
  0.642857;0.000000;,
  0.928571;0.000000;,
  0.857143;0.000000;,
  0.714286;0.000000;,
  1.000000;0.000000;,
  0.785714;0.000000;,
  0.000000;0.000000;,
  0.071429;0.000000;,
  0.428571;0.000000;,
  0.357143;0.000000;,
  0.285714;0.000000;,
  0.142857;0.000000;,
  0.214286;0.000000;,
  0.000000;1.000000;,
  0.090909;1.000000;,
  0.090909;0.000000;,
  0.181818;1.000000;,
  0.181818;0.000000;,
  0.272727;1.000000;,
  0.272727;0.000000;,
  0.363636;1.000000;,
  0.363636;0.000000;,
  0.454545;1.000000;,
  0.454545;0.000000;,
  0.545455;1.000000;,
  0.545455;0.000000;,
  0.636364;1.000000;,
  0.636364;0.000000;,
  0.727273;1.000000;,
  0.727273;0.000000;,
  0.818182;1.000000;,
  0.818182;0.000000;,
  0.909091;1.000000;,
  0.909091;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.000000;0.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;;
 }
}