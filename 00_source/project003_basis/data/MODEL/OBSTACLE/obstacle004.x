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
 236;
 268.72762;-0.48986;-11.04250;,
 268.72762;87.44218;-11.04250;,
 267.39436;87.44218;46.03676;,
 267.39436;-0.48986;46.03676;,
 15.91071;-0.48986;40.16264;,
 15.91071;87.44218;40.16264;,
 4.76518;87.44218;39.90238;,
 4.76518;-0.48986;39.90238;,
 6.63221;-0.48986;-40.02852;,
 6.63221;43.42240;-40.02852;,
 6.76999;32.05622;-45.92896;,
 6.76999;-0.48986;-45.92896;,
 258.25370;-0.48986;-40.05484;,
 258.25370;32.05622;-40.05484;,
 269.39917;32.05622;-39.79444;,
 269.39917;-0.48986;-39.79444;,
 17.77777;-0.48986;-39.76826;,
 17.91552;-0.48986;-45.66870;,
 258.11587;43.42240;-34.15440;,
 269.26142;43.42240;-33.89414;,
 256.24889;87.44218;45.77650;,
 257.58207;87.44218;-11.30276;,
 6.09840;-0.48986;-17.17702;,
 17.24393;-0.48986;-16.91662;,
 6.09840;87.44218;-17.17702;,
 268.86579;-0.48986;-16.95470;,
 268.86579;76.05332;-16.95470;,
 256.24889;-0.48986;45.77650;,
 257.58207;-0.48986;-11.30276;,
 45.95303;-0.48986;40.86432;,
 47.28625;-0.48986;-16.21494;,
 17.26619;85.60538;-17.87016;,
 47.35743;81.57030;-19.26316;,
 47.42425;76.05332;-22.12714;,
 17.38210;76.05332;-22.82882;,
 197.54588;83.45974;-14.77364;,
 227.58803;83.45974;-14.07196;,
 227.67792;76.05332;-17.91678;,
 197.63560;76.05332;-18.61846;,
 17.77777;43.42240;-39.76826;,
 17.91552;32.05622;-45.66870;,
 228.07355;43.42240;-34.85608;,
 228.21130;32.05622;-40.75652;,
 269.26142;-0.48986;-33.89414;,
 258.11587;-0.48986;-34.15440;,
 47.82005;-0.48986;-39.06658;,
 47.95780;-0.48986;-44.96688;,
 228.21130;-0.48986;-40.75652;,
 45.95303;87.44218;40.86432;,
 226.20649;87.44218;45.07482;,
 226.20649;-0.48986;45.07482;,
 196.16434;87.44218;44.37300;,
 196.16434;-0.48986;44.37300;,
 166.12202;87.44218;43.67132;,
 166.12202;-0.48986;43.67132;,
 136.07969;87.44218;42.96950;,
 136.07969;-0.48986;42.96950;,
 106.03746;87.44218;42.26782;,
 106.03746;-0.48986;42.26782;,
 75.99522;87.44218;41.56614;,
 75.99522;-0.48986;41.56614;,
 47.95780;32.05622;-44.96688;,
 77.86229;43.42240;-38.36476;,
 107.90452;43.42240;-37.66308;,
 107.96331;38.57210;-40.18098;,
 77.97388;34.22706;-43.13834;,
 78.00003;-0.48986;-44.26520;,
 73.05304;32.05622;-44.38070;,
 78.00020;29.61028;-44.26520;,
 138.08467;-0.48986;-42.86170;,
 138.08467;32.05622;-42.86170;,
 168.12683;32.05622;-42.16002;,
 168.12683;-0.48986;-42.16002;,
 198.16915;32.05622;-41.45820;,
 198.16915;-0.48986;-41.45820;,
 228.07355;-0.48986;-34.85608;,
 198.03140;-0.48986;-35.55790;,
 167.98908;-0.48986;-36.25958;,
 137.94676;-0.48986;-36.96126;,
 107.90452;-0.48986;-37.66308;,
 108.04227;-0.48986;-43.56338;,
 77.86229;-0.48986;-38.36476;,
 47.82005;43.42240;-39.06658;,
 108.04227;29.61028;-43.56338;,
 137.94676;43.42240;-36.96126;,
 167.98908;43.42240;-36.25958;,
 198.03140;43.42240;-35.55790;,
 77.46666;76.05332;-21.42546;,
 77.32840;87.44218;-15.51312;,
 59.94282;87.44218;-15.91926;,
 107.37081;87.44218;-14.81144;,
 137.41304;87.44218;-14.10976;,
 167.45519;87.44218;-13.40794;,
 227.00492;87.44218;10.89354;,
 227.53975;-0.48986;-12.00458;,
 197.49760;-0.48986;-12.70626;,
 167.45519;-0.48986;-13.40794;,
 137.41304;-0.48986;-14.10976;,
 107.37081;-0.48986;-14.81144;,
 77.32840;-0.48986;-15.51312;,
 167.59345;76.05332;-19.32014;,
 197.39267;87.44218;-8.21996;,
 137.55113;76.05332;-20.02196;,
 107.50889;76.05332;-20.72364;,
 47.23797;87.44218;-14.14574;,
 17.19561;87.44218;-14.84756;,
 47.42425;-0.48986;-22.12714;,
 77.46666;-0.48986;-21.42546;,
 107.50889;-0.48986;-20.72364;,
 137.55113;-0.48986;-20.02196;,
 167.59345;-0.48986;-19.32014;,
 197.63560;-0.48986;-18.61846;,
 227.67792;-0.48986;-17.91678;,
 257.72016;-0.48986;-17.21496;,
 17.38210;-0.48986;-22.82882;,
 257.72016;76.05332;-17.21496;,
 6.23658;-0.48986;-23.08922;,
 6.23658;76.05332;-23.08922;,
 -267.39436;-0.48986;46.03676;,
 -267.39436;87.44218;46.03676;,
 -268.72762;87.44218;-11.04250;,
 -268.72762;-0.48986;-11.04250;,
 -4.76518;-0.48986;39.90238;,
 -4.76518;87.44218;39.90238;,
 -15.91071;87.44218;40.16264;,
 -15.91071;-0.48986;40.16264;,
 -6.76999;-0.48986;-45.92896;,
 -6.76999;32.05622;-45.92896;,
 -6.63221;43.42240;-40.02852;,
 -6.63221;-0.48986;-40.02852;,
 -269.39917;-0.48986;-39.79444;,
 -269.39917;32.05622;-39.79444;,
 -258.25370;32.05622;-40.05484;,
 -258.25370;-0.48986;-40.05484;,
 -17.91552;-0.48986;-45.66870;,
 -17.77777;-0.48986;-39.76826;,
 -269.26142;43.42240;-33.89414;,
 -258.11587;43.42240;-34.15440;,
 -257.58207;87.44218;-11.30276;,
 -256.24889;87.44218;45.77650;,
 -17.24393;-0.48986;-16.91662;,
 -6.09840;-0.48986;-17.17702;,
 -6.09840;87.44218;-17.17702;,
 -268.86579;76.05332;-16.95470;,
 -268.86579;-0.48986;-16.95470;,
 -257.58207;-0.48986;-11.30276;,
 -256.24889;-0.48986;45.77650;,
 -47.28625;-0.48986;-16.21494;,
 -45.95303;-0.48986;40.86432;,
 -17.38210;76.05332;-22.82882;,
 -47.42425;76.05332;-22.12714;,
 -47.35743;81.57030;-19.26316;,
 -17.26619;85.60538;-17.87016;,
 -197.63560;76.05332;-18.61846;,
 -227.67792;76.05332;-17.91678;,
 -227.58803;83.45974;-14.07196;,
 -197.54588;83.45974;-14.77364;,
 -17.91552;32.05622;-45.66870;,
 -17.77777;43.42240;-39.76826;,
 -228.21130;32.05622;-40.75652;,
 -228.07355;43.42240;-34.85608;,
 -258.11587;-0.48986;-34.15440;,
 -269.26142;-0.48986;-33.89414;,
 -47.95780;-0.48986;-44.96688;,
 -47.82005;-0.48986;-39.06658;,
 -228.21130;-0.48986;-40.75652;,
 -45.95303;87.44218;40.86432;,
 -226.20649;-0.48986;45.07482;,
 -226.20649;87.44218;45.07482;,
 -196.16434;-0.48986;44.37300;,
 -196.16434;87.44218;44.37300;,
 -166.12202;-0.48986;43.67132;,
 -166.12202;87.44218;43.67132;,
 -136.07969;-0.48986;42.96950;,
 -136.07969;87.44218;42.96950;,
 -106.03746;-0.48986;42.26782;,
 -106.03746;87.44218;42.26782;,
 -75.99522;-0.48986;41.56614;,
 -75.99522;87.44218;41.56614;,
 -47.95780;32.05622;-44.96688;,
 -77.97388;34.22706;-43.13834;,
 -107.96331;38.57210;-40.18098;,
 -107.90452;43.42240;-37.66308;,
 -77.86229;43.42240;-38.36476;,
 -78.00003;-0.48986;-44.26520;,
 -73.05304;32.05622;-44.38070;,
 -78.00020;29.61028;-44.26520;,
 -168.12683;-0.48986;-42.16002;,
 -168.12683;32.05622;-42.16002;,
 -138.08467;32.05622;-42.86170;,
 -138.08467;-0.48986;-42.86170;,
 -198.16915;-0.48986;-41.45820;,
 -198.16915;32.05622;-41.45820;,
 -228.07355;-0.48986;-34.85608;,
 -198.03140;-0.48986;-35.55790;,
 -167.98908;-0.48986;-36.25958;,
 -137.94676;-0.48986;-36.96126;,
 -108.04227;-0.48986;-43.56338;,
 -107.90452;-0.48986;-37.66308;,
 -77.86229;-0.48986;-38.36476;,
 -47.82005;43.42240;-39.06658;,
 -108.04227;29.61028;-43.56338;,
 -137.94676;43.42240;-36.96126;,
 -167.98908;43.42240;-36.25958;,
 -198.03140;43.42240;-35.55790;,
 -77.32840;87.44218;-15.51312;,
 -77.46666;76.05332;-21.42546;,
 -59.94282;87.44218;-15.91926;,
 -107.37081;87.44218;-14.81144;,
 -137.41304;87.44218;-14.10976;,
 -167.45519;87.44218;-13.40794;,
 -227.00492;87.44218;10.89354;,
 -227.53975;-0.48986;-12.00458;,
 -197.49760;-0.48986;-12.70626;,
 -167.45519;-0.48986;-13.40794;,
 -137.41304;-0.48986;-14.10976;,
 -107.37081;-0.48986;-14.81144;,
 -77.32840;-0.48986;-15.51312;,
 -167.59345;76.05332;-19.32014;,
 -197.39267;87.44218;-8.21996;,
 -137.55113;76.05332;-20.02196;,
 -107.50889;76.05332;-20.72364;,
 -47.23797;87.44218;-14.14574;,
 -17.19561;87.44218;-14.84756;,
 -77.46666;-0.48986;-21.42546;,
 -47.42425;-0.48986;-22.12714;,
 -107.50889;-0.48986;-20.72364;,
 -137.55113;-0.48986;-20.02196;,
 -167.59345;-0.48986;-19.32014;,
 -197.63560;-0.48986;-18.61846;,
 -227.67792;-0.48986;-17.91678;,
 -257.72016;-0.48986;-17.21496;,
 -17.38210;-0.48986;-22.82882;,
 -257.72016;76.05332;-17.21496;,
 -6.23658;-0.48986;-23.08922;,
 -6.23658;76.05332;-23.08922;;
 
 252;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,8,11,17;,
 4;18,19,14,13;,
 4;20,2,1,21;,
 4;4,7,22,23;,
 4;7,6,24,22;,
 4;25,26,1,0;,
 4;3,27,28,0;,
 4;29,4,23,30;,
 4;31,32,33,34;,
 4;35,36,37,38;,
 4;9,39,40,10;,
 4;41,18,13,42;,
 4;43,44,12,15;,
 4;45,16,17,46;,
 4;11,10,40,17;,
 4;47,42,13,12;,
 4;3,2,20,27;,
 4;29,48,5,4;,
 4;27,20,49,50;,
 4;50,49,51,52;,
 4;52,51,53,54;,
 4;54,53,55,56;,
 4;56,55,57,58;,
 4;58,57,59,60;,
 4;60,59,48,29;,
 4;17,40,61,46;,
 4;62,63,64,65;,
 3;46,61,66;,
 3;61,67,66;,
 3;67,68,66;,
 4;69,70,71,72;,
 4;72,71,73,74;,
 4;74,73,42,47;,
 4;44,75,47,12;,
 4;75,76,74,47;,
 4;76,77,72,74;,
 4;77,78,69,72;,
 4;78,79,80,69;,
 4;79,81,66,80;,
 4;81,45,46,66;,
 4;39,82,61,40;,
 4;66,68,83,80;,
 4;63,84,70,64;,
 4;80,83,70,69;,
 4;84,85,71,70;,
 4;85,86,73,71;,
 4;86,41,42,73;,
 3;87,33,88;,
 3;88,33,89;,
 3;33,32,89;,
 4;59,57,90,88;,
 4;57,55,91,90;,
 4;55,53,92,91;,
 4;49,20,21,93;,
 4;27,50,94,28;,
 4;50,52,95,94;,
 4;52,54,96,95;,
 4;54,56,97,96;,
 4;56,58,98,97;,
 4;58,60,99,98;,
 4;60,29,30,99;,
 4;92,35,38,100;,
 4;53,51,101,92;,
 4;91,92,100,102;,
 4;90,91,102,103;,
 4;88,90,103,87;,
 3;88,89,59;,
 3;59,89,48;,
 3;89,104,48;,
 4;5,48,104,105;,
 4;99,30,106,107;,
 4;98,99,107,108;,
 4;97,98,108,109;,
 4;96,97,109,110;,
 4;95,96,110,111;,
 4;94,95,111,112;,
 4;28,94,112,113;,
 4;30,23,114,106;,
 4;0,28,113,25;,
 4;51,49,93,101;,
 4;6,5,105,24;,
 4;43,19,26,25;,
 4;21,1,26,115;,
 4;23,22,116,114;,
 4;22,24,117,116;,
 4;15,14,19,43;,
 4;107,106,45,81;,
 4;108,107,81,79;,
 4;109,108,79,78;,
 4;110,109,78,77;,
 4;111,110,77,76;,
 4;112,111,76,75;,
 4;113,112,75,44;,
 4;106,114,16,45;,
 4;25,113,44,43;,
 4;117,34,39,9;,
 4;115,26,19,18;,
 4;114,116,8,16;,
 4;116,117,9,8;,
 4;36,21,115,37;,
 3;65,67,62;,
 3;62,67,82;,
 3;67,61,82;,
 4;24,31,34,117;,
 4;41,86,37,115;,
 4;85,84,100,38;,
 4;63,62,103,102;,
 4;82,39,33,87;,
 4;86,85,38,37;,
 4;84,63,102,100;,
 4;62,82,87,103;,
 3;33,39,34;,
 3;115,18,41;,
 3;36,93,21;,
 3;101,35,92;,
 4;36,35,101,93;,
 3;65,68,67;,
 3;83,64,70;,
 4;65,64,83,68;,
 3;105,31,24;,
 3;32,104,89;,
 4;32,31,105,104;,
 4;118,119,120,121;,
 4;122,123,124,125;,
 4;126,127,128,129;,
 4;130,131,132,133;,
 4;134,126,129,135;,
 4;132,131,136,137;,
 4;138,120,119,139;,
 4;140,141,122,125;,
 4;141,142,123,122;,
 4;121,120,143,144;,
 4;121,145,146,118;,
 4;147,140,125,148;,
 4;149,150,151,152;,
 4;153,154,155,156;,
 4;127,157,158,128;,
 4;159,132,137,160;,
 4;130,133,161,162;,
 4;163,134,135,164;,
 4;134,157,127,126;,
 4;133,132,159,165;,
 4;146,139,119,118;,
 4;125,124,166,148;,
 4;167,168,139,146;,
 4;169,170,168,167;,
 4;171,172,170,169;,
 4;173,174,172,171;,
 4;175,176,174,173;,
 4;177,178,176,175;,
 4;148,166,178,177;,
 4;163,179,157,134;,
 4;180,181,182,183;,
 3;184,179,163;,
 3;184,185,179;,
 3;184,186,185;,
 4;187,188,189,190;,
 4;191,192,188,187;,
 4;165,159,192,191;,
 4;133,165,193,161;,
 4;165,191,194,193;,
 4;191,187,195,194;,
 4;187,190,196,195;,
 4;190,197,198,196;,
 4;197,184,199,198;,
 4;184,163,164,199;,
 4;157,179,200,158;,
 4;197,201,186,184;,
 4;181,189,202,182;,
 4;190,189,201,197;,
 4;189,188,203,202;,
 4;188,192,204,203;,
 4;192,159,160,204;,
 3;205,150,206;,
 3;207,150,205;,
 3;207,151,150;,
 4;205,208,176,178;,
 4;208,209,174,176;,
 4;209,210,172,174;,
 4;211,138,139,168;,
 4;145,212,167,146;,
 4;212,213,169,167;,
 4;213,214,171,169;,
 4;214,215,173,171;,
 4;215,216,175,173;,
 4;216,217,177,175;,
 4;217,147,148,177;,
 4;218,153,156,210;,
 4;210,219,170,172;,
 4;220,218,210,209;,
 4;221,220,209,208;,
 4;206,221,208,205;,
 3;178,207,205;,
 3;166,207,178;,
 3;166,222,207;,
 4;223,222,166,124;,
 4;224,225,147,217;,
 4;226,224,217,216;,
 4;227,226,216,215;,
 4;228,227,215,214;,
 4;229,228,214,213;,
 4;230,229,213,212;,
 4;231,230,212,145;,
 4;225,232,140,147;,
 4;144,231,145,121;,
 4;219,211,168,170;,
 4;142,223,124,123;,
 4;144,143,136,162;,
 4;233,143,120,138;,
 4;232,234,141,140;,
 4;234,235,142,141;,
 4;162,136,131,130;,
 4;199,164,225,224;,
 4;198,199,224,226;,
 4;196,198,226,227;,
 4;195,196,227,228;,
 4;194,195,228,229;,
 4;193,194,229,230;,
 4;161,193,230,231;,
 4;164,135,232,225;,
 4;162,161,231,144;,
 4;128,158,149,235;,
 4;137,136,143,233;,
 4;135,129,234,232;,
 4;129,128,235,234;,
 4;154,233,138,155;,
 3;183,185,180;,
 3;200,185,183;,
 3;200,179,185;,
 4;235,149,152,142;,
 4;233,154,204,160;,
 4;153,218,202,203;,
 4;220,221,183,182;,
 4;206,150,158,200;,
 4;154,153,203,204;,
 4;218,220,182,202;,
 4;221,206,200,183;,
 3;149,158,150;,
 3;160,137,233;,
 3;138,211,155;,
 3;210,156,219;,
 4;211,219,156,155;,
 3;185,186,180;,
 3;189,181,201;,
 4;186,201,181,180;,
 3;142,152,223;,
 3;207,222,151;,
 4;222,223,152,151;;
 
 MeshMaterialList {
  4;
  252;
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
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
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
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3;;
  Material {
   0.448627;0.448627;0.448627;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.097255;0.097255;0.097255;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.746667;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.464314;0.423529;0.439216;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  176;
  0.023357;0.000000;-0.999727;,
  0.022688;0.237185;-0.971199;,
  0.999727;0.000000;0.023352;,
  -0.999727;0.000000;-0.023346;,
  -0.023344;0.000000;0.999727;,
  0.999727;0.000000;0.023358;,
  0.000000;-1.000000;0.000000;,
  -0.999727;0.000000;-0.023358;,
  -0.023347;0.000000;0.999727;,
  0.000000;1.000000;0.000000;,
  0.023354;0.000000;-0.999727;,
  0.022683;0.237186;-0.971199;,
  0.022686;0.237186;-0.971199;,
  -0.038666;0.997832;-0.053266;,
  -0.023352;0.000000;0.999727;,
  -0.023350;0.000000;0.999727;,
  -0.023352;0.000000;0.999727;,
  -0.023352;0.000000;0.999727;,
  -0.023352;0.000000;0.999727;,
  -0.023352;0.000000;0.999727;,
  -0.023352;0.000000;0.999727;,
  0.023350;0.000000;-0.999727;,
  0.023352;0.000000;-0.999727;,
  0.023352;0.000000;-0.999727;,
  0.023350;0.000000;-0.999727;,
  0.023349;0.000000;-0.999727;,
  0.022929;0.189522;-0.981609;,
  0.016652;0.261232;-0.965132;,
  0.022685;0.237187;-0.971199;,
  0.022686;0.237185;-0.971199;,
  0.022684;0.237186;-0.971199;,
  0.030819;0.983576;-0.177845;,
  0.020725;0.460842;-0.887240;,
  0.999727;0.000000;0.023357;,
  -0.999727;0.000000;-0.023357;,
  0.020725;0.460837;-0.887243;,
  0.020723;0.460838;-0.887242;,
  0.020724;0.460839;-0.887242;,
  0.020724;0.460841;-0.887241;,
  0.020724;0.460838;-0.887242;,
  0.020725;0.460837;-0.887243;,
  0.020725;0.460837;-0.887243;,
  0.020723;0.460838;-0.887242;,
  0.020725;0.460837;-0.887243;,
  -0.999727;0.000000;-0.023347;,
  0.020722;0.460837;-0.887243;,
  0.020722;0.460837;-0.887243;,
  0.020725;0.460834;-0.887244;,
  0.020720;0.460839;-0.887242;,
  0.020725;0.460839;-0.887242;,
  0.020725;0.460838;-0.887242;,
  0.020723;0.460837;-0.887243;,
  0.020725;0.460836;-0.887244;,
  0.020724;0.460837;-0.887243;,
  0.020721;0.460836;-0.887243;,
  -0.004670;0.780119;-0.625614;,
  -0.014796;0.991761;-0.127247;,
  0.037653;0.974551;-0.220982;,
  0.049639;0.716387;-0.695935;,
  0.053431;0.365760;-0.929174;,
  0.054960;0.134232;-0.989425;,
  0.042306;0.276288;-0.960143;,
  0.018184;0.164487;-0.986212;,
  0.016668;0.393825;-0.919034;,
  0.037132;0.951703;-0.304768;,
  0.047017;0.653600;-0.755379;,
  -0.007688;0.593823;-0.804559;,
  -0.019432;0.925724;-0.377700;,
  -0.021285;0.528808;-0.848475;,
  -0.023357;0.000000;-0.999727;,
  -0.022688;0.237185;-0.971199;,
  -0.999727;0.000000;0.023352;,
  0.999727;0.000000;-0.023346;,
  0.023344;0.000000;0.999727;,
  -0.999727;0.000000;0.023358;,
  0.999727;0.000000;-0.023358;,
  0.023347;0.000000;0.999727;,
  -0.023354;0.000000;-0.999727;,
  -0.022683;0.237186;-0.971199;,
  -0.022686;0.237186;-0.971199;,
  0.038666;0.997832;-0.053266;,
  0.023352;0.000000;0.999727;,
  0.023350;0.000000;0.999727;,
  0.023352;0.000000;0.999727;,
  0.023352;0.000000;0.999727;,
  0.023352;0.000000;0.999727;,
  0.023352;0.000000;0.999727;,
  0.023352;0.000000;0.999727;,
  -0.023350;0.000000;-0.999727;,
  -0.023352;0.000000;-0.999727;,
  -0.023352;0.000000;-0.999727;,
  -0.023350;0.000000;-0.999727;,
  -0.023349;0.000000;-0.999727;,
  -0.022929;0.189522;-0.981609;,
  -0.016652;0.261232;-0.965132;,
  -0.022685;0.237187;-0.971199;,
  -0.022686;0.237185;-0.971199;,
  -0.022684;0.237186;-0.971199;,
  -0.030819;0.983576;-0.177845;,
  -0.020725;0.460842;-0.887240;,
  -0.999727;0.000000;0.023357;,
  0.999727;0.000000;-0.023357;,
  -0.020725;0.460837;-0.887243;,
  -0.020723;0.460838;-0.887242;,
  -0.020724;0.460839;-0.887242;,
  -0.020724;0.460841;-0.887241;,
  -0.020724;0.460838;-0.887242;,
  -0.020725;0.460837;-0.887243;,
  -0.020725;0.460837;-0.887243;,
  -0.020723;0.460838;-0.887242;,
  -0.020725;0.460837;-0.887243;,
  0.999727;0.000000;-0.023347;,
  -0.020722;0.460837;-0.887243;,
  -0.020722;0.460837;-0.887243;,
  -0.020725;0.460834;-0.887244;,
  -0.020720;0.460839;-0.887242;,
  -0.020725;0.460839;-0.887242;,
  -0.020725;0.460838;-0.887242;,
  -0.020723;0.460837;-0.887243;,
  -0.020725;0.460836;-0.887244;,
  -0.020724;0.460837;-0.887243;,
  -0.020721;0.460836;-0.887243;,
  0.004670;0.780119;-0.625614;,
  0.014796;0.991761;-0.127247;,
  -0.037653;0.974551;-0.220982;,
  -0.049639;0.716387;-0.695935;,
  -0.053431;0.365760;-0.929174;,
  -0.054960;0.134232;-0.989425;,
  -0.042306;0.276288;-0.960143;,
  -0.018184;0.164487;-0.986212;,
  -0.016668;0.393825;-0.919034;,
  -0.037132;0.951703;-0.304768;,
  -0.047017;0.653600;-0.755379;,
  0.007688;0.593823;-0.804559;,
  0.019432;0.925724;-0.377700;,
  0.021285;0.528808;-0.848475;,
  -0.999727;0.000000;-0.023351;,
  0.020721;0.460838;-0.887242;,
  0.022679;0.237188;-0.971199;,
  0.023345;0.000000;-0.999727;,
  0.023350;0.000000;-0.999727;,
  -0.023345;0.000000;0.999727;,
  -0.023347;0.000000;0.999727;,
  0.023352;0.000000;-0.999727;,
  0.023352;-0.000000;-0.999727;,
  0.020725;0.460838;-0.887243;,
  0.020725;0.460838;-0.887242;,
  0.020724;0.460840;-0.887241;,
  0.056130;0.961951;-0.267393;,
  0.999727;0.000000;0.023344;,
  0.020723;0.460838;-0.887243;,
  0.020718;0.460838;-0.887242;,
  0.020718;0.460838;-0.887242;,
  0.999728;0.000000;0.023339;,
  0.020726;0.460837;-0.887243;,
  0.020728;0.460837;-0.887243;,
  0.999727;0.000000;-0.023351;,
  -0.022679;0.237188;-0.971199;,
  -0.020721;0.460838;-0.887242;,
  -0.023350;0.000000;-0.999727;,
  -0.023345;0.000000;-0.999727;,
  0.023347;0.000000;0.999727;,
  0.023345;0.000000;0.999727;,
  -0.023352;0.000000;-0.999727;,
  -0.023352;-0.000000;-0.999727;,
  -0.020725;0.460838;-0.887243;,
  -0.020725;0.460838;-0.887242;,
  -0.020724;0.460840;-0.887241;,
  -0.056130;0.961951;-0.267393;,
  -0.999727;0.000000;0.023344;,
  -0.020718;0.460838;-0.887242;,
  -0.020718;0.460838;-0.887242;,
  -0.020723;0.460838;-0.887243;,
  -0.999728;0.000000;0.023339;,
  -0.020726;0.460837;-0.887243;,
  -0.020728;0.460837;-0.887243;;
  252;
  4;5,5,2,2;,
  4;8,8,4,4;,
  4;44,44,3,3;,
  4;10,12,1,0;,
  4;6,6,6,6;,
  4;46,54,1,12;,
  4;9,9,9,13;,
  4;6,6,6,6;,
  4;136,136,7,7;,
  4;33,33,5,5;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;65,66,37,35;,
  4;58,55,43,42;,
  4;137,45,11,138;,
  4;53,46,12,30;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;139,138,11,140;,
  4;21,30,12,10;,
  4;141,141,142,142;,
  4;20,20,8,8;,
  4;142,142,19,19;,
  4;19,19,18,18;,
  4;18,18,17,17;,
  4;17,17,16,16;,
  4;16,16,15,15;,
  4;15,15,14,14;,
  4;14,14,20,20;,
  4;140,11,26,143;,
  4;48,49,63,59;,
  3;143,26,25;,
  3;26,61,25;,
  3;61,60,25;,
  4;24,27,28,23;,
  4;23,28,29,22;,
  4;22,29,30,21;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;45,47,26,11;,
  4;25,60,62,144;,
  4;49,50,27,63;,
  4;144,62,27,24;,
  4;50,51,28,27;,
  4;51,52,29,28;,
  4;52,53,30,29;,
  3;38,37,32;,
  3;32,37,68;,
  3;37,66,68;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,9,31,9;,
  4;9,9,13,56;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;145,58,42,41;,
  4;9,9,57,31;,
  4;146,145,41,40;,
  4;147,146,40,39;,
  4;32,147,39,38;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,67,9;,
  4;9,9,67,64;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;9,9,56,57;,
  4;9,9,64,148;,
  4;149,149,33,33;,
  4;150,151,152,36;,
  4;6,6,6,6;,
  4;7,7,34,34;,
  4;153,153,149,149;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;154,35,45,137;,
  4;36,152,54,46;,
  4;6,6,6,6;,
  4;34,34,44,44;,
  4;55,150,36,43;,
  3;59,61,48;,
  3;48,61,47;,
  3;61,26,47;,
  4;155,65,35,154;,
  4;53,52,43,36;,
  4;51,50,41,42;,
  4;49,48,39,40;,
  4;47,45,37,38;,
  4;52,51,42,43;,
  4;50,49,40,41;,
  4;48,47,38,39;,
  3;37,45,35;,
  3;36,46,53;,
  3;55,56,13;,
  3;57,58,31;,
  4;55,58,57,56;,
  3;59,60,61;,
  3;62,63,27;,
  4;59,63,62,60;,
  3;64,65,148;,
  3;66,67,68;,
  4;66,65,64,67;,
  4;71,71,74,74;,
  4;73,73,76,76;,
  4;72,72,111,111;,
  4;69,70,79,77;,
  4;6,6,6,6;,
  4;79,70,121,113;,
  4;80,9,9,9;,
  4;6,6,6,6;,
  4;75,75,156,156;,
  4;74,74,100,100;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;102,104,133,132;,
  4;109,110,122,125;,
  4;157,78,112,158;,
  4;97,79,113,120;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;159,78,157,160;,
  4;77,79,97,88;,
  4;161,161,162,162;,
  4;76,76,87,87;,
  4;86,86,161,161;,
  4;85,85,86,86;,
  4;84,84,85,85;,
  4;83,83,84,84;,
  4;82,82,83,83;,
  4;81,81,82,82;,
  4;87,87,81,81;,
  4;163,93,78,159;,
  4;126,130,116,115;,
  3;92,93,163;,
  3;92,128,93;,
  3;92,127,128;,
  4;90,95,94,91;,
  4;89,96,95,90;,
  4;88,97,96,89;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;78,93,114,112;,
  4;164,129,127,92;,
  4;130,94,117,116;,
  4;91,94,129,164;,
  4;94,95,118,117;,
  4;95,96,119,118;,
  4;96,97,120,119;,
  3;99,104,105;,
  3;135,104,99;,
  3;135,133,104;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  4;9,98,9,9;,
  4;123,80,9,9;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;108,109,125,165;,
  4;98,124,9,9;,
  4;107,108,165,166;,
  4;106,107,166,167;,
  4;105,106,167,99;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,134,9;,
  4;131,134,9,9;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;124,123,9,9;,
  4;168,131,9,9;,
  4;100,100,169,169;,
  4;103,170,171,172;,
  4;6,6,6,6;,
  4;101,101,75,75;,
  4;169,169,173,173;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;6,6,6,6;,
  4;158,112,102,174;,
  4;113,121,170,103;,
  4;6,6,6,6;,
  4;111,111,101,101;,
  4;110,103,172,122;,
  3;115,128,126;,
  3;114,128,115;,
  3;114,93,128;,
  4;174,102,132,175;,
  4;103,110,119,120;,
  4;109,108,117,118;,
  4;107,106,115,116;,
  4;105,104,112,114;,
  4;110,109,118,119;,
  4;108,107,116,117;,
  4;106,105,114,115;,
  3;102,112,104;,
  3;120,113,103;,
  3;80,123,122;,
  3;98,125,124;,
  4;123,124,125,122;,
  3;128,127,126;,
  3;94,130,129;,
  4;127,129,130,126;,
  3;168,132,131;,
  3;135,134,133;,
  4;134,131,132,133;;
 }
 MeshTextureCoords {
  236;
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;;
 }
}