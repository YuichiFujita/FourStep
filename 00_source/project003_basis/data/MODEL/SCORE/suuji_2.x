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
 77;
 -33.37627;198.79706;23.73149;,
 34.19614;186.12495;23.73149;,
 -9.79002;203.48502;23.73149;,
 -56.96252;184.44022;23.73149;,
 -11.84100;175.35730;23.73149;,
 12.66088;164.84605;23.73149;,
 51.15335;141.07666;23.73149;,
 -56.96252;148.40160;23.73149;,
 -33.74252;169.57062;23.73149;,
 22.43965;137.85370;23.73149;,
 36.79649;92.36594;23.73149;,
 18.94187;116.23455;23.73149;,
 8.37580;95.07615;23.73149;,
 -24.47649;48.19663;23.73149;,
 -10.96200;28.27284;23.73148;,
 -61.06448;3.07511;23.73149;,
 65.51019;28.27284;23.73147;,
 65.51019;1.02413;23.73147;,
 -61.06448;1.02413;23.73149;,
 -33.37627;198.79706;-5.56820;,
 -9.79002;203.48502;-5.56820;,
 34.19614;186.12495;-5.56820;,
 -56.96252;184.44022;-5.56819;,
 -11.84100;175.35730;-5.56820;,
 12.66088;164.84605;-5.56820;,
 51.15335;141.07666;-5.56820;,
 -56.96252;148.40160;-5.56819;,
 -33.74252;169.57062;-5.56820;,
 22.43965;137.85370;-5.56820;,
 36.79649;92.36594;-5.56820;,
 18.94187;116.23455;-5.56820;,
 8.37580;95.07615;-5.56820;,
 -24.47649;48.19663;-5.56820;,
 -10.96200;28.27284;-5.56821;,
 -61.06448;3.07511;-5.56820;,
 65.51019;28.27284;-5.56821;,
 65.51019;1.02413;-5.56821;,
 -61.06448;1.02413;-5.56820;,
 -61.06448;1.02413;23.73149;,
 -61.06448;3.07511;23.73149;,
 -61.06448;3.07511;-5.56820;,
 -24.47649;48.19663;23.73149;,
 -24.47649;48.19663;-5.56820;,
 8.37580;95.07615;23.73149;,
 8.37580;95.07615;-5.56820;,
 18.94187;116.23455;23.73149;,
 18.94187;116.23455;-5.56820;,
 22.43965;137.85370;23.73149;,
 22.43965;137.85370;-5.56820;,
 12.66088;164.84605;23.73149;,
 12.66088;164.84605;-5.56820;,
 -11.84100;175.35730;23.73149;,
 -11.84100;175.35730;-5.56820;,
 -33.74252;169.57062;23.73149;,
 -33.74252;169.57062;-5.56820;,
 -56.96252;148.40160;23.73149;,
 -56.96252;148.40160;-5.56819;,
 -56.96252;184.44022;23.73149;,
 -56.96252;184.44022;-5.56819;,
 -33.37627;198.79706;23.73149;,
 -33.37627;198.79706;-5.56820;,
 -9.79002;203.48502;23.73149;,
 -9.79002;203.48502;-5.56820;,
 34.19614;186.12495;23.73149;,
 34.19614;186.12495;-5.56820;,
 51.15335;141.07666;23.73149;,
 51.15335;141.07666;-5.56820;,
 36.79649;92.36594;23.73149;,
 36.79649;92.36594;-5.56820;,
 -10.96200;28.27284;23.73148;,
 -10.96200;28.27284;-5.56821;,
 65.51019;28.27284;23.73147;,
 65.51019;28.27284;-5.56821;,
 65.51019;1.02413;23.73147;,
 65.51019;1.02413;-5.56821;,
 -61.06448;1.02413;23.73149;,
 -61.06448;1.02413;-5.56820;;
 
 53;
 3;0,1,2;,
 3;3,1,0;,
 3;3,4,1;,
 3;4,5,1;,
 3;5,6,1;,
 3;7,8,3;,
 3;8,4,3;,
 3;9,6,5;,
 3;9,10,6;,
 3;11,10,9;,
 3;12,10,11;,
 3;13,10,12;,
 3;13,14,10;,
 3;15,14,13;,
 3;15,16,14;,
 3;15,17,16;,
 3;18,17,15;,
 3;19,20,21;,
 3;22,19,21;,
 3;22,21,23;,
 3;23,21,24;,
 3;24,21,25;,
 3;26,22,27;,
 3;27,22,23;,
 3;28,24,25;,
 3;28,25,29;,
 3;30,28,29;,
 3;31,30,29;,
 3;32,31,29;,
 3;32,29,33;,
 3;34,32,33;,
 3;34,33,35;,
 3;34,35,36;,
 3;37,34,36;,
 4;38,39,40,37;,
 4;39,41,42,40;,
 4;41,43,44,42;,
 4;43,45,46,44;,
 4;45,47,48,46;,
 4;47,49,50,48;,
 4;49,51,52,50;,
 4;51,53,54,52;,
 4;53,55,56,54;,
 4;55,57,58,56;,
 4;57,59,60,58;,
 4;59,61,62,60;,
 4;61,63,64,62;,
 4;63,65,66,64;,
 4;65,67,68,66;,
 4;67,69,70,68;,
 4;69,71,72,70;,
 4;71,73,74,72;,
 4;73,75,76,74;;
 
 MeshMaterialList {
  1;
  53;
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
  58;
  0.000000;0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;-0.000000;-1.000000;,
  -0.000000;-0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;-0.000000;-1.000000;,
  -0.000000;-0.000000;-1.000000;,
  -0.000000;-0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -0.000000;-0.000000;-1.000000;,
  -0.000000;0.000000;-1.000000;,
  -1.000000;0.000000;0.000000;,
  -0.942531;0.334118;0.000000;,
  -0.798321;0.602232;0.000000;,
  -0.859145;0.511733;0.000000;,
  -0.951790;0.306749;0.000000;,
  -0.995624;-0.093449;0.000000;,
  -0.727203;-0.686423;0.000000;,
  -0.073404;-0.997302;0.000000;,
  0.478345;-0.878172;-0.000000;,
  0.673716;-0.738990;-0.000000;,
  -0.871765;0.489925;0.000000;,
  -0.363009;0.931786;0.000000;,
  0.089731;0.995966;-0.000000;,
  0.712701;0.701468;-0.000000;,
  0.999327;0.036690;-0.000000;,
  0.894492;-0.447085;-0.000000;,
  0.801866;-0.597504;-0.000000;,
  0.000000;1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  53;
  3;11,13,12;,
  3;10,13,11;,
  3;10,7,13;,
  3;7,6,13;,
  3;6,14,13;,
  3;9,8,10;,
  3;8,7,10;,
  3;5,14,6;,
  3;5,15,14;,
  3;4,15,5;,
  3;3,15,4;,
  3;2,15,3;,
  3;2,16,15;,
  3;1,16,2;,
  3;1,17,16;,
  3;1,18,17;,
  3;0,18,1;,
  3;30,31,32;,
  3;29,30,32;,
  3;29,32,26;,
  3;26,32,25;,
  3;25,32,33;,
  3;28,29,27;,
  3;27,29,26;,
  3;24,25,33;,
  3;24,33,34;,
  3;23,24,34;,
  3;22,23,34;,
  3;21,22,34;,
  3;21,34,35;,
  3;20,21,35;,
  3;20,35,36;,
  3;20,36,37;,
  3;19,20,37;,
  4;38,39,39,38;,
  4;39,40,40,39;,
  4;40,41,41,40;,
  4;41,42,42,41;,
  4;42,43,43,42;,
  4;43,44,44,43;,
  4;44,45,45,44;,
  4;45,46,46,45;,
  4;46,47,47,46;,
  4;38,48,48,38;,
  4;48,49,49,48;,
  4;49,50,50,49;,
  4;50,51,51,50;,
  4;51,52,52,51;,
  4;52,53,53,52;,
  4;53,54,54,53;,
  4;55,55,55,55;,
  4;56,56,56,56;,
  4;57,57,57,57;;
 }
 MeshTextureCoords {
  77;
  0.611111;0.000000;,
  0.722222;0.000000;,
  0.666667;0.000000;,
  0.555556;0.000000;,
  0.388889;0.000000;,
  0.333333;0.000000;,
  0.777778;0.000000;,
  0.500000;0.000000;,
  0.444444;0.000000;,
  0.277778;0.000000;,
  0.833333;0.000000;,
  0.222222;0.000000;,
  0.166667;0.000000;,
  0.111111;0.000000;,
  0.888889;0.000000;,
  0.055556;0.000000;,
  0.944444;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.611111;0.000000;,
  0.666667;0.000000;,
  0.722222;0.000000;,
  0.555556;0.000000;,
  0.388889;0.000000;,
  0.333333;0.000000;,
  0.777778;0.000000;,
  0.500000;0.000000;,
  0.444444;0.000000;,
  0.277778;0.000000;,
  0.833333;0.000000;,
  0.222222;0.000000;,
  0.166667;0.000000;,
  0.111111;0.000000;,
  0.888889;0.000000;,
  0.055556;0.000000;,
  0.944444;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.052632;1.000000;,
  0.052632;0.000000;,
  0.105263;1.000000;,
  0.105263;0.000000;,
  0.157895;1.000000;,
  0.157895;0.000000;,
  0.210526;1.000000;,
  0.210526;0.000000;,
  0.263158;1.000000;,
  0.263158;0.000000;,
  0.315789;1.000000;,
  0.315789;0.000000;,
  0.368421;1.000000;,
  0.368421;0.000000;,
  0.421053;1.000000;,
  0.421053;0.000000;,
  0.473684;1.000000;,
  0.473684;0.000000;,
  0.526316;1.000000;,
  0.526316;0.000000;,
  0.578947;1.000000;,
  0.578947;0.000000;,
  0.631579;1.000000;,
  0.631579;0.000000;,
  0.684211;1.000000;,
  0.684211;0.000000;,
  0.736842;1.000000;,
  0.736842;0.000000;,
  0.789474;1.000000;,
  0.789474;0.000000;,
  0.842105;1.000000;,
  0.842105;0.000000;,
  0.894737;1.000000;,
  0.894737;0.000000;,
  0.947368;1.000000;,
  0.947368;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;;
 }
}
