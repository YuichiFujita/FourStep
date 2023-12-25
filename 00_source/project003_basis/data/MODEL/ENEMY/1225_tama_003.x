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
 204;
 -36.17181;76.68771;44.63422;,
 -36.17181;96.65602;44.63422;,
 -47.04765;96.65602;44.63422;,
 -47.04765;76.68771;44.63422;,
 -47.04765;96.65602;-26.04477;,
 -47.04765;76.68771;-26.04477;,
 -36.17181;3.77965;44.63422;,
 -47.04765;3.77965;44.63422;,
 -47.04765;3.77965;-26.04477;,
 -36.17181;3.77965;-26.04477;,
 -8.45747;76.68771;-26.04477;,
 -8.45747;96.65602;-26.04477;,
 -0.60941;96.65602;-26.04477;,
 -0.60941;76.68771;-26.04477;,
 -8.45747;96.65602;44.63422;,
 -0.60941;96.65602;44.63422;,
 -0.60941;96.65602;-26.04477;,
 -8.45747;96.65602;-26.04477;,
 -17.28074;44.57561;-26.04477;,
 -8.45747;57.56435;-26.04477;,
 -0.60941;57.56435;-26.04477;,
 -0.60941;44.57561;-26.04477;,
 -47.04765;44.57561;44.63422;,
 -47.04765;57.56435;44.63422;,
 -47.04765;57.56435;-26.04477;,
 -47.04765;44.57561;-26.04477;,
 -36.17181;44.57561;44.63422;,
 -36.17181;57.56435;44.63422;,
 -8.45747;44.57561;44.63422;,
 -8.45747;57.56435;44.63422;,
 -36.17181;57.56435;-26.04477;,
 -36.17181;44.57561;-26.04477;,
 -36.17181;96.65602;44.63422;,
 -36.17181;96.65602;-26.04477;,
 -36.17181;96.65602;-26.04477;,
 -36.17181;76.68771;-26.04477;,
 -8.45747;3.77965;44.63422;,
 -8.45747;3.77965;-26.04477;,
 -8.45747;76.68771;44.63422;,
 -8.45747;96.65602;44.63422;,
 -0.60941;76.68771;44.63422;,
 -0.60941;96.65602;44.63422;,
 -0.60941;3.77965;44.63422;,
 -0.60941;3.77965;-26.04477;,
 -0.60941;44.57561;44.63422;,
 -0.60941;57.56435;44.63422;,
 -36.17181;3.77965;-26.04477;,
 -36.17181;16.74518;-26.04477;,
 -17.28074;16.74518;-26.04477;,
 -8.45747;3.77965;-26.04477;,
 -0.60941;3.77965;44.63422;,
 -0.60941;16.74518;44.63422;,
 -8.45747;16.74518;44.63422;,
 -8.45747;3.77965;44.63422;,
 -47.04765;16.74518;-26.04477;,
 -36.17181;16.74518;44.63422;,
 -36.17181;3.77965;44.63422;,
 -47.04765;16.74518;44.63422;,
 -0.60941;16.74518;-26.04477;,
 -0.60941;3.77965;-26.04477;,
 -16.38450;18.27300;-48.24149;,
 -0.60941;18.27300;-48.24149;,
 34.95300;76.68771;44.63422;,
 45.82880;76.68771;44.63422;,
 45.82880;96.65602;44.63422;,
 34.95300;96.65602;44.63422;,
 45.82880;76.68771;-26.04477;,
 45.82880;96.65602;-26.04477;,
 34.95300;3.77965;44.63422;,
 34.95300;3.77965;-26.04477;,
 45.82880;3.77965;-26.04477;,
 45.82880;3.77965;44.63422;,
 7.23866;76.68771;-26.04477;,
 7.23866;96.65602;-26.04477;,
 7.23866;96.65602;44.63422;,
 7.23866;96.65602;-26.04477;,
 16.06191;44.57561;-26.04477;,
 7.23866;57.56435;-26.04477;,
 45.82880;44.57561;44.63422;,
 45.82880;44.57561;-26.04477;,
 45.82880;57.56435;-26.04477;,
 45.82880;57.56435;44.63422;,
 34.95300;44.57561;44.63422;,
 34.95300;57.56435;44.63422;,
 7.23866;44.57561;44.63422;,
 7.23866;57.56435;44.63422;,
 34.95300;44.57561;-26.04477;,
 34.95300;57.56435;-26.04477;,
 34.95300;96.65602;-26.04477;,
 34.95300;96.65602;44.63422;,
 34.95300;76.68771;-26.04477;,
 34.95300;96.65602;-26.04477;,
 7.23866;3.77965;44.63422;,
 7.23866;3.77965;-26.04477;,
 7.23866;76.68771;44.63422;,
 7.23866;96.65602;44.63422;,
 34.95300;3.77965;-26.04477;,
 7.23866;3.77965;-26.04477;,
 16.06191;16.74518;-26.04477;,
 34.95300;16.74518;-26.04477;,
 7.23866;3.77965;44.63422;,
 7.23866;16.74518;44.63422;,
 45.82880;16.74518;-26.04477;,
 34.95300;3.77965;44.63422;,
 34.95300;16.74518;44.63422;,
 45.82880;16.74518;44.63422;,
 15.16566;18.27300;-48.24149;,
 -16.38450;43.25216;-48.24149;,
 15.16566;43.25216;-48.24149;,
 -0.60941;43.25216;-48.24149;,
 -12.43259;39.30026;-48.24149;,
 -12.43259;22.22488;-48.24149;,
 -0.60941;22.22488;-48.24149;,
 -0.60941;39.30026;-48.24149;,
 11.21377;22.22488;-48.24149;,
 11.21377;39.30026;-48.24149;,
 11.21377;22.22488;-32.20798;,
 11.21377;39.30026;-32.20798;,
 -0.60941;39.30026;-32.20798;,
 -12.43259;22.22488;-32.20798;,
 -12.43259;39.30026;-32.20798;,
 -0.60941;22.22488;-32.20798;,
 -9.06117;100.21783;-28.75532;,
 -38.90240;100.21783;-28.75532;,
 -38.90240;47.31084;-28.75532;,
 -18.56243;47.31084;-28.75532;,
 -38.90240;100.21783;47.34467;,
 -38.90240;47.31084;47.34467;,
 -50.60941;47.31084;47.34467;,
 -50.60941;100.21783;47.34467;,
 -38.90240;0.21784;47.34467;,
 -38.90240;0.21784;-28.75532;,
 -50.60941;0.21784;-28.75532;,
 -50.60941;0.21784;47.34467;,
 -50.60941;47.31084;-28.75532;,
 -50.60941;100.21783;-28.75532;,
 -9.06117;100.21783;47.34467;,
 -9.06117;100.21783;-28.75532;,
 -0.60941;100.21783;-28.75532;,
 -0.60941;100.21783;47.34467;,
 -38.90240;100.21783;-28.75532;,
 -38.90240;100.21783;47.34467;,
 -0.60941;47.31084;-28.75532;,
 -0.60941;100.21783;-28.75532;,
 -9.06117;0.21784;47.34467;,
 -9.06117;0.21784;-28.75532;,
 -9.06117;100.21783;47.34467;,
 -9.06117;47.31084;47.34467;,
 -0.60941;0.21784;47.34467;,
 -0.60941;0.21784;-28.75532;,
 -0.60941;100.21783;47.34467;,
 -0.60941;47.31084;47.34467;,
 -38.90240;0.21784;-28.75532;,
 -9.06117;0.21784;-28.75532;,
 -18.56243;14.17715;-28.75532;,
 -38.90240;14.17715;-28.75532;,
 -0.60941;0.21784;47.34467;,
 -9.06117;0.21784;47.34467;,
 -9.06117;14.17715;47.34467;,
 -0.60941;14.17715;47.34467;,
 -50.60941;14.17715;-28.75532;,
 -38.90240;0.21784;47.34467;,
 -38.90240;14.17715;47.34467;,
 -50.60941;14.17715;47.34467;,
 -0.60941;0.21784;-28.75532;,
 -0.60941;14.17715;-28.75532;,
 -0.60941;15.82109;-52.65533;,
 -17.59652;15.82109;-52.65533;,
 7.83771;100.21783;-28.75532;,
 17.33897;47.31084;-28.75532;,
 37.68358;47.31084;-28.75532;,
 37.68358;100.21783;-28.75532;,
 49.39059;100.21783;47.34467;,
 49.39059;47.31084;47.34467;,
 37.68358;47.31084;47.34467;,
 37.68358;100.21783;47.34467;,
 37.68358;0.21784;47.34467;,
 49.39059;0.21784;47.34467;,
 49.39059;0.21784;-28.75532;,
 37.68358;0.21784;-28.75532;,
 49.39059;100.21783;-28.75532;,
 49.39059;47.31084;-28.75532;,
 7.83771;100.21783;47.34467;,
 7.83771;100.21783;-28.75532;,
 16.37770;45.88518;-52.65533;,
 -0.60941;45.88518;-52.65533;,
 16.37770;15.82109;-52.65533;,
 37.68358;100.21783;47.34467;,
 37.68358;100.21783;-28.75532;,
 7.83771;0.21784;47.34467;,
 7.83771;0.21784;-28.75532;,
 7.83771;47.31084;47.34467;,
 7.83771;100.21783;47.34467;,
 37.68358;0.21784;-28.75532;,
 37.68358;14.17715;-28.75532;,
 17.33897;14.17715;-28.75532;,
 7.83771;0.21784;-28.75532;,
 7.83771;14.17715;47.34467;,
 7.83771;0.21784;47.34467;,
 49.39059;14.17715;-28.75532;,
 37.68358;14.17715;47.34467;,
 37.68358;0.21784;47.34467;,
 49.39059;14.17715;47.34467;,
 -17.59652;45.88518;-52.65533;;
 
 162;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;6,7,8,9;,
 4;10,11,12,13;,
 4;14,15,16,17;,
 4;18,19,20,21;,
 4;22,23,24,25;,
 4;26,27,23,22;,
 4;28,29,27,26;,
 4;25,24,30,31;,
 4;2,32,33,4;,
 4;5,4,34,35;,
 4;36,6,9,37;,
 4;38,39,1,0;,
 4;40,41,39,38;,
 4;42,36,37,43;,
 4;44,45,29,28;,
 4;31,30,19,18;,
 4;32,14,17,33;,
 4;35,34,11,10;,
 3;35,10,19;,
 4;45,40,38,29;,
 4;29,38,0,27;,
 4;24,5,35,30;,
 4;19,10,13,20;,
 4;23,3,5,24;,
 4;27,0,3,23;,
 4;46,47,48,49;,
 4;47,31,18,48;,
 4;50,51,52,53;,
 4;51,44,28,52;,
 4;8,54,47,46;,
 4;54,25,31,47;,
 4;53,52,55,56;,
 4;52,28,26,55;,
 4;56,55,57,7;,
 4;55,26,22,57;,
 4;7,57,54,8;,
 4;57,22,25,54;,
 4;49,48,58,59;,
 4;58,48,60,61;,
 4;62,63,64,65;,
 4;63,66,67,64;,
 4;68,69,70,71;,
 4;72,13,12,73;,
 4;74,75,16,15;,
 4;76,21,20,77;,
 4;78,79,80,81;,
 4;82,78,81,83;,
 4;84,82,83,85;,
 4;79,86,87,80;,
 4;64,67,88,89;,
 4;66,90,91,67;,
 4;92,93,69,68;,
 4;94,62,65,95;,
 4;40,94,95,41;,
 4;42,43,93,92;,
 4;44,84,85,45;,
 4;86,76,77,87;,
 4;89,88,75,74;,
 4;90,72,73,91;,
 3;90,77,72;,
 4;45,85,94,40;,
 4;85,83,62,94;,
 4;80,87,90,66;,
 4;77,20,13,72;,
 4;81,80,66,63;,
 4;83,81,63,62;,
 4;96,97,98,99;,
 4;99,98,76,86;,
 4;50,100,101,51;,
 4;51,101,84,44;,
 4;70,96,99,102;,
 4;102,99,86,79;,
 4;100,103,104,101;,
 4;101,104,82,84;,
 4;103,71,105,104;,
 4;104,105,78,82;,
 4;71,70,102,105;,
 4;105,102,79,78;,
 4;97,59,58,98;,
 4;98,58,61,106;,
 4;48,18,107,60;,
 4;76,98,106,108;,
 4;21,76,108,109;,
 4;18,21,109,107;,
 4;110,111,60,107;,
 4;111,112,61,60;,
 4;113,110,107,109;,
 4;114,115,108,106;,
 4;112,114,106,61;,
 4;115,113,109,108;,
 3;30,35,19;,
 3;87,77,90;,
 4;115,114,116,117;,
 4;113,115,117,118;,
 4;119,120,118,121;,
 4;116,121,118,117;,
 4;112,111,119,121;,
 4;114,112,121,116;,
 4;110,113,118,120;,
 4;111,110,120,119;,
 4;122,123,124,125;,
 4;126,127,128,129;,
 4;130,131,132,133;,
 4;129,128,134,135;,
 4;136,137,138,139;,
 4;129,135,140,141;,
 4;122,125,142,143;,
 4;144,145,131,130;,
 4;135,134,124,123;,
 4;146,147,127,126;,
 4;148,149,145,144;,
 4;141,140,137,136;,
 4;150,151,147,146;,
 4;152,153,154,155;,
 4;155,154,125,124;,
 4;156,157,158,159;,
 4;159,158,147,151;,
 4;132,152,155,160;,
 4;160,155,124,134;,
 4;157,161,162,158;,
 4;158,162,127,147;,
 4;161,133,163,162;,
 4;162,163,128,127;,
 4;133,132,160,163;,
 4;163,160,134,128;,
 4;153,164,165,154;,
 4;165,166,167,154;,
 4;168,169,170,171;,
 4;172,173,174,175;,
 4;176,177,178,179;,
 4;180,181,173,172;,
 4;182,139,138,183;,
 4;184,185,166,186;,
 4;172,187,188,180;,
 4;143,142,169,168;,
 4;189,176,179,190;,
 4;171,170,181,180;,
 4;175,174,191,192;,
 4;148,189,190,149;,
 4;187,182,183,188;,
 4;192,191,151,150;,
 4;193,194,195,196;,
 4;194,170,169,195;,
 4;156,159,197,198;,
 4;159,151,191,197;,
 4;178,199,194,193;,
 4;199,181,170,194;,
 4;198,197,200,201;,
 4;197,191,174,200;,
 4;201,200,202,177;,
 4;200,174,173,202;,
 4;177,202,199,178;,
 4;202,173,181,199;,
 4;196,195,165,164;,
 4;195,186,166,165;,
 4;154,167,203,125;,
 4;169,184,186,195;,
 4;142,185,184,169;,
 4;125,203,185,142;,
 4;185,203,167,166;;
 
 MeshMaterialList {
  9;
  162;
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  4,
  4,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5;;
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
 }
 MeshNormals {
  25;
  0.000000;-1.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.998227;-0.059518;,
  -0.999186;0.000000;-0.040345;,
  0.000000;-0.997640;-0.068669;,
  0.000000;-0.997640;-0.068669;,
  0.999186;0.000000;-0.040345;,
  0.000000;0.998227;-0.059518;,
  0.000000;1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.999184;0.000000;0.040381;,
  0.000000;0.997643;0.068622;,
  0.000000;0.997643;0.068622;,
  -0.999192;0.000000;0.040188;,
  0.000000;-0.998226;0.059545;,
  0.000000;-0.998226;0.059545;,
  0.000000;-0.998226;0.059545;;
  162;
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  3;4,4,4;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;4,4,4,4;,
  4;9,8,8,9;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  3;4,4,4;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;4,4,4,4;,
  4;9,9,9,9;,
  4;7,7,7,7;,
  4;10,10,10,10;,
  4;6,6,6,6;,
  4;11,6,6,11;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;0,0,0,0;,
  4;5,5,5,5;,
  4;16,16,16,16;,
  4;14,14,14,14;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;15,15,15,15;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;12,12,12,12;,
  4;16,16,16,16;,
  4;14,14,14,14;,
  4;12,12,12,12;,
  4;15,15,15,15;,
  4;14,14,14,14;,
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;14,14,14,14;,
  4;14,14,14,14;,
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;14,14,14,14;,
  4;14,14,14,14;,
  4;14,14,14,14;,
  4;14,14,14,14;,
  4;13,13,13,13;,
  4;13,13,13,13;,
  4;16,16,16,16;,
  4;20,20,19,19;,
  4;16,16,16,16;,
  4;14,14,14,14;,
  4;12,12,12,12;,
  4;17,17,17,17;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;12,12,12,12;,
  4;16,16,16,16;,
  4;14,14,14,14;,
  4;12,12,12,12;,
  4;15,15,15,15;,
  4;14,14,14,14;,
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;14,14,14,14;,
  4;14,14,14,14;,
  4;16,16,16,16;,
  4;16,16,16,16;,
  4;14,14,14,14;,
  4;14,14,14,14;,
  4;14,14,14,14;,
  4;14,14,14,14;,
  4;17,17,17,17;,
  4;17,17,17,17;,
  4;16,16,16,16;,
  4;19,19,20,20;,
  4;18,18,18,18;,
  4;21,21,21,21;,
  4;22,22,23,23;,
  4;24,24,22,22;,
  4;16,16,16,16;;
 }
 MeshTextureCoords {
  204;
  0.571580;0.471830;,
  0.625000;0.471830;,
  0.625000;0.500000;,
  0.571580;0.500000;,
  0.625000;0.750000;,
  0.571580;0.750000;,
  0.346830;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.346830;0.750000;,
  0.571580;0.846830;,
  0.625000;0.846830;,
  0.625000;0.875000;,
  0.571580;0.875000;,
  0.721830;0.500000;,
  0.750000;0.500000;,
  0.750000;0.750000;,
  0.721830;0.750000;,
  0.452600;0.846830;,
  0.491400;0.846830;,
  0.491400;0.875000;,
  0.452600;0.875000;,
  0.452600;0.500000;,
  0.491400;0.500000;,
  0.491400;0.750000;,
  0.452600;0.750000;,
  0.452600;0.471830;,
  0.491400;0.471830;,
  0.452600;0.403170;,
  0.491400;0.403170;,
  0.491400;0.778170;,
  0.452600;0.778170;,
  0.653170;0.500000;,
  0.653170;0.750000;,
  0.625000;0.778170;,
  0.571580;0.778170;,
  0.278170;0.500000;,
  0.278170;0.750000;,
  0.571580;0.403170;,
  0.625000;0.403170;,
  0.571580;0.375000;,
  0.625000;0.375000;,
  0.250000;0.500000;,
  0.250000;0.750000;,
  0.452600;0.375000;,
  0.491400;0.375000;,
  0.375000;0.778170;,
  0.413800;0.778170;,
  0.413800;0.846830;,
  0.375000;0.846830;,
  0.375000;0.375000;,
  0.413800;0.375000;,
  0.413800;0.403170;,
  0.375000;0.403170;,
  0.413800;0.750000;,
  0.413800;0.471830;,
  0.375000;0.471830;,
  0.413800;0.500000;,
  0.413800;0.875000;,
  0.375000;0.875000;,
  0.413800;0.846830;,
  0.413800;0.875000;,
  0.571580;0.471830;,
  0.571580;0.500000;,
  0.625000;0.500000;,
  0.625000;0.471830;,
  0.571580;0.750000;,
  0.625000;0.750000;,
  0.346830;0.500000;,
  0.346830;0.750000;,
  0.375000;0.750000;,
  0.375000;0.500000;,
  0.571580;0.846830;,
  0.625000;0.846830;,
  0.721830;0.500000;,
  0.721830;0.750000;,
  0.452600;0.846830;,
  0.491400;0.846830;,
  0.452600;0.500000;,
  0.452600;0.750000;,
  0.491400;0.750000;,
  0.491400;0.500000;,
  0.452600;0.471830;,
  0.491400;0.471830;,
  0.452600;0.403170;,
  0.491400;0.403170;,
  0.452600;0.778170;,
  0.491400;0.778170;,
  0.653170;0.750000;,
  0.653170;0.500000;,
  0.571580;0.778170;,
  0.625000;0.778170;,
  0.278170;0.500000;,
  0.278170;0.750000;,
  0.571580;0.403170;,
  0.625000;0.403170;,
  0.375000;0.778170;,
  0.375000;0.846830;,
  0.413800;0.846830;,
  0.413800;0.778170;,
  0.375000;0.403170;,
  0.413800;0.403170;,
  0.413800;0.750000;,
  0.375000;0.471830;,
  0.413800;0.471830;,
  0.413800;0.500000;,
  0.413800;0.846830;,
  0.452600;0.846830;,
  0.452600;0.846830;,
  0.452600;0.875000;,
  0.446460;0.853890;,
  0.419940;0.853890;,
  0.419940;0.875000;,
  0.446460;0.875000;,
  0.419940;0.853890;,
  0.446460;0.853890;,
  0.419940;0.853890;,
  0.446460;0.853890;,
  0.446460;0.875000;,
  0.419940;0.853890;,
  0.446460;0.853890;,
  0.419940;0.875000;,
  0.625000;0.846830;,
  0.625000;0.778170;,
  0.452600;0.778170;,
  0.452600;0.846830;,
  0.625000;0.471830;,
  0.452600;0.471830;,
  0.452600;0.500000;,
  0.625000;0.500000;,
  0.346830;0.500000;,
  0.346830;0.750000;,
  0.375000;0.750000;,
  0.375000;0.500000;,
  0.452600;0.750000;,
  0.625000;0.750000;,
  0.721830;0.500000;,
  0.721830;0.750000;,
  0.750000;0.750000;,
  0.750000;0.500000;,
  0.653170;0.750000;,
  0.653170;0.500000;,
  0.452600;0.875000;,
  0.625000;0.875000;,
  0.278170;0.500000;,
  0.278170;0.750000;,
  0.625000;0.403170;,
  0.452600;0.403170;,
  0.250000;0.500000;,
  0.250000;0.750000;,
  0.625000;0.375000;,
  0.452600;0.375000;,
  0.375000;0.778170;,
  0.375000;0.846830;,
  0.413800;0.846830;,
  0.413800;0.778170;,
  0.375000;0.375000;,
  0.375000;0.403170;,
  0.413800;0.403170;,
  0.413800;0.375000;,
  0.413800;0.750000;,
  0.375000;0.471830;,
  0.413800;0.471830;,
  0.413800;0.500000;,
  0.375000;0.875000;,
  0.413800;0.875000;,
  0.413800;0.875000;,
  0.413800;0.846830;,
  0.625000;0.846830;,
  0.452600;0.846830;,
  0.452600;0.778170;,
  0.625000;0.778170;,
  0.625000;0.500000;,
  0.452600;0.500000;,
  0.452600;0.471830;,
  0.625000;0.471830;,
  0.346830;0.500000;,
  0.375000;0.500000;,
  0.375000;0.750000;,
  0.346830;0.750000;,
  0.625000;0.750000;,
  0.452600;0.750000;,
  0.721830;0.500000;,
  0.721830;0.750000;,
  0.452600;0.846830;,
  0.452600;0.875000;,
  0.413800;0.846830;,
  0.653170;0.500000;,
  0.653170;0.750000;,
  0.278170;0.500000;,
  0.278170;0.750000;,
  0.452600;0.403170;,
  0.625000;0.403170;,
  0.375000;0.778170;,
  0.413800;0.778170;,
  0.413800;0.846830;,
  0.375000;0.846830;,
  0.413800;0.403170;,
  0.375000;0.403170;,
  0.413800;0.750000;,
  0.413800;0.471830;,
  0.375000;0.471830;,
  0.413800;0.500000;,
  0.452600;0.846830;;
 }
}