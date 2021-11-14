int Fleut_walk_count;
float Fleut_walk_verts[126];
int Fleut_walk_types[42];
int Fleut_walk_graph[84];

void Fleut_walk_init()
{
	Fleut_walk_count = 42;

	Fleut_walk_verts[0 ] = -1.929874;
	Fleut_walk_verts[1 ] = 3.388806;
	Fleut_walk_verts[2 ] = 6.838603;
	Fleut_walk_verts[3 ] = -1.629202;
	Fleut_walk_verts[4 ] = 4.899935;
	Fleut_walk_verts[5 ] = 9.972677;
	Fleut_walk_verts[6 ] = -1.120867;
	Fleut_walk_verts[7 ] = 4.962006;
	Fleut_walk_verts[8 ] = 12.663636;
	Fleut_walk_verts[9 ] = 0.940432;
	Fleut_walk_verts[10] = 4.993339;
	Fleut_walk_verts[11] = 12.621218;
	Fleut_walk_verts[12] = -1.771641;
	Fleut_walk_verts[13] = 4.899935;
	Fleut_walk_verts[14] = 9.418664;
	Fleut_walk_verts[15] = 1.558220;
	Fleut_walk_verts[16] = 4.932073;
	Fleut_walk_verts[17] = 8.314543;
	Fleut_walk_verts[18] = -1.655774;
	Fleut_walk_verts[19] = 3.431772;
	Fleut_walk_verts[20] = 5.946877;
	Fleut_walk_verts[21] = 1.582354;
	Fleut_walk_verts[22] = 3.413070;
	Fleut_walk_verts[23] = 6.291374;
	Fleut_walk_verts[24] = 1.714048;
	Fleut_walk_verts[25] = 3.411724;
	Fleut_walk_verts[26] = 0.018841;
	Fleut_walk_verts[27] = -1.861085;
	Fleut_walk_verts[28] = 3.434575;
	Fleut_walk_verts[29] = -2.327683;
	Fleut_walk_verts[30] = 0.298227;
	Fleut_walk_verts[31] = 3.422914;
	Fleut_walk_verts[32] = -2.568628;
	Fleut_walk_verts[33] = 1.763107;
	Fleut_walk_verts[34] = 5.492230;
	Fleut_walk_verts[35] = -5.932146;
	Fleut_walk_verts[36] = 1.383388;
	Fleut_walk_verts[37] = 5.513145;
	Fleut_walk_verts[38] = -13.678864;
	Fleut_walk_verts[39] = 0.803734;
	Fleut_walk_verts[40] = 3.402864;
	Fleut_walk_verts[41] = 7.313381;
	Fleut_walk_verts[42] = 0.803734;
	Fleut_walk_verts[43] = 3.402864;
	Fleut_walk_verts[44] = 7.983641;
	Fleut_walk_verts[45] = 3.349013;
	Fleut_walk_verts[46] = 5.379055;
	Fleut_walk_verts[47] = 9.411176;
	Fleut_walk_verts[48] = -3.259134;
	Fleut_walk_verts[49] = 5.379055;
	Fleut_walk_verts[50] = 9.344265;
	Fleut_walk_verts[51] = -3.529994;
	Fleut_walk_verts[52] = 5.352733;
	Fleut_walk_verts[53] = -3.660413;
	Fleut_walk_verts[54] = 0.530705;
	Fleut_walk_verts[55] = 13.127201;
	Fleut_walk_verts[56] = 9.020707;
	Fleut_walk_verts[57] = -0.570331;
	Fleut_walk_verts[58] = 13.101786;
	Fleut_walk_verts[59] = 9.020707;
	Fleut_walk_verts[60] = -0.862457;
	Fleut_walk_verts[61] = 14.409208;
	Fleut_walk_verts[62] = -1.315888;
	Fleut_walk_verts[63] = 1.009281;
	Fleut_walk_verts[64] = 15.153740;
	Fleut_walk_verts[65] = 8.402053;
	Fleut_walk_verts[66] = -0.654266;
	Fleut_walk_verts[67] = 15.192825;
	Fleut_walk_verts[68] = 10.073030;
	Fleut_walk_verts[69] = -1.262729;
	Fleut_walk_verts[70] = 17.139860;
	Fleut_walk_verts[71] = -0.855095;
	Fleut_walk_verts[72] = -1.267675;
	Fleut_walk_verts[73] = 5.470477;
	Fleut_walk_verts[74] = -12.421252;
	Fleut_walk_verts[75] = 3.591863;
	Fleut_walk_verts[76] = 5.322402;
	Fleut_walk_verts[77] = -3.670884;
	Fleut_walk_verts[78] = 0.912208;
	Fleut_walk_verts[79] = 14.483976;
	Fleut_walk_verts[80] = -1.315888;
	Fleut_walk_verts[81] = -1.768763;
	Fleut_walk_verts[82] = 5.517570;
	Fleut_walk_verts[83] = -2.792763;
	Fleut_walk_verts[84] = 1.109514;
	Fleut_walk_verts[85] = 17.139860;
	Fleut_walk_verts[86] = -0.111349;
	Fleut_walk_verts[87] = 0.511884;
	Fleut_walk_verts[88] = 5.357726;
	Fleut_walk_verts[89] = -2.587435;
	Fleut_walk_verts[90] = 0.494634;
	Fleut_walk_verts[91] = 5.492230;
	Fleut_walk_verts[92] = -5.657519;
	Fleut_walk_verts[93] = 2.120644;
	Fleut_walk_verts[94] = 3.411724;
	Fleut_walk_verts[95] = -2.347161;
	Fleut_walk_verts[96] = 1.877136;
	Fleut_walk_verts[97] = 5.492230;
	Fleut_walk_verts[98] = -5.808963;
	Fleut_walk_verts[99] = -1.536985;
	Fleut_walk_verts[100] = 5.484803;
	Fleut_walk_verts[101] = -10.630485;
	Fleut_walk_verts[102] = -0.760864;
	Fleut_walk_verts[103] = 8.220182;
	Fleut_walk_verts[104] = -16.961889;
	Fleut_walk_verts[105] = -0.541892;
	Fleut_walk_verts[106] = 8.259561;
	Fleut_walk_verts[107] = -18.904396;
	Fleut_walk_verts[108] = 0.421716;
	Fleut_walk_verts[109] = 8.259561;
	Fleut_walk_verts[110] = -18.164906;
	Fleut_walk_verts[111] = 0.522212;
	Fleut_walk_verts[112] = 8.281096;
	Fleut_walk_verts[113] = -14.466308;
	Fleut_walk_verts[114] = -1.024896;
	Fleut_walk_verts[115] = 3.434103;
	Fleut_walk_verts[116] = -2.911971;
	Fleut_walk_verts[117] = -1.024896;
	Fleut_walk_verts[118] = 3.434103;
	Fleut_walk_verts[119] = -3.798866;
	Fleut_walk_verts[120] = 0.571683;
	Fleut_walk_verts[121] = 5.513434;
	Fleut_walk_verts[122] = -14.527671;
	Fleut_walk_verts[123] = 0.571683;
	Fleut_walk_verts[124] = 5.513434;
	Fleut_walk_verts[125] = -15.538573;

	Fleut_walk_types[0 ] = 0;
	Fleut_walk_types[1 ] = 0;
	Fleut_walk_types[2 ] = 0;
	Fleut_walk_types[3 ] = 0;
	Fleut_walk_types[4 ] = 0;
	Fleut_walk_types[5 ] = 0;
	Fleut_walk_types[6 ] = 0;
	Fleut_walk_types[7 ] = 0;
	Fleut_walk_types[8 ] = 0;
	Fleut_walk_types[9 ] = 0;
	Fleut_walk_types[10] = 0;
	Fleut_walk_types[11] = 0;
	Fleut_walk_types[12] = 0;
	Fleut_walk_types[13] = 2;
	Fleut_walk_types[14] = 3;
	Fleut_walk_types[15] = 5;
	Fleut_walk_types[16] = 5;
	Fleut_walk_types[17] = 5;
	Fleut_walk_types[18] = 4;
	Fleut_walk_types[19] = 4;
	Fleut_walk_types[20] = 4;
	Fleut_walk_types[21] = 6;
	Fleut_walk_types[22] = 6;
	Fleut_walk_types[23] = 6;
	Fleut_walk_types[24] = 0;
	Fleut_walk_types[25] = 5;
	Fleut_walk_types[26] = 4;
	Fleut_walk_types[27] = 0;
	Fleut_walk_types[28] = 6;
	Fleut_walk_types[29] = 0;
	Fleut_walk_types[30] = 0;
	Fleut_walk_types[31] = 0;
	Fleut_walk_types[32] = 0;
	Fleut_walk_types[33] = 0;
	Fleut_walk_types[34] = 0;
	Fleut_walk_types[35] = 0;
	Fleut_walk_types[36] = 0;
	Fleut_walk_types[37] = 0;
	Fleut_walk_types[38] = 2;
	Fleut_walk_types[39] = 3;
	Fleut_walk_types[40] = 2;
	Fleut_walk_types[41] = 3;

	Fleut_walk_graph[0 ] = (37)*256 + (36);
	Fleut_walk_graph[1 ] = (35)*256 + (36);
	Fleut_walk_graph[2 ] = (34)*256 + (35);
	Fleut_walk_graph[3 ] = (34)*256 + (36);
	Fleut_walk_graph[4 ] = (24)*256 + (34);
	Fleut_walk_graph[5 ] = (24)*256 + (33);
	Fleut_walk_graph[6 ] = (12)*256 + (33);
	Fleut_walk_graph[7 ] = (12)*256 + (40);
	Fleut_walk_graph[8 ] = (40)*256 + (41);
	Fleut_walk_graph[9 ] = (12)*256 + (30);
	Fleut_walk_graph[10] = (12)*256 + (11);
	Fleut_walk_graph[11] = (12)*256 + (33);
	Fleut_walk_graph[12] = (33)*256 + (27);
	Fleut_walk_graph[13] = (11)*256 + (30);
	Fleut_walk_graph[14] = (11)*256 + (32);
	Fleut_walk_graph[15] = (31)*256 + (32);
	Fleut_walk_graph[16] = ( 8)*256 + (31);
	Fleut_walk_graph[17] = (10)*256 + (31);
	Fleut_walk_graph[18] = ( 9)*256 + (38);
	Fleut_walk_graph[19] = (38)*256 + (39);
	Fleut_walk_graph[20] = ( 8)*256 + ( 7);
	Fleut_walk_graph[21] = ( 7)*256 + (13);
	Fleut_walk_graph[22] = (13)*256 + (14);
	Fleut_walk_graph[23] = ( 6)*256 + (13);
	Fleut_walk_graph[24] = ( 0)*256 + ( 6);
	Fleut_walk_graph[25] = ( 4)*256 + ( 0);
	Fleut_walk_graph[26] = ( 1)*256 + ( 4);
	Fleut_walk_graph[27] = ( 1)*256 + ( 2);
	Fleut_walk_graph[28] = ( 2)*256 + ( 3);
	Fleut_walk_graph[29] = ( 3)*256 + ( 5);
	Fleut_walk_graph[30] = (-1)*256 + (-1);
	Fleut_walk_graph[31] = (27)*256 + (30);
	Fleut_walk_graph[32] = ( 9)*256 + ( 6);
	Fleut_walk_graph[33] = ( 6)*256 + ( 7);
	Fleut_walk_graph[34] = (32)*256 + (25);
	Fleut_walk_graph[35] = (25)*256 + (26);
	Fleut_walk_graph[36] = (26)*256 + (28);
	Fleut_walk_graph[37] = (27)*256 + (17);
	Fleut_walk_graph[38] = (17)*256 + (20);
	Fleut_walk_graph[39] = (20)*256 + (23);
	Fleut_walk_graph[40] = ( 5)*256 + (15);
	Fleut_walk_graph[41] = (15)*256 + (18);
	Fleut_walk_graph[42] = (18)*256 + (21);
	Fleut_walk_graph[43] = ( 1)*256 + (16);
	Fleut_walk_graph[44] = (16)*256 + (19);
	Fleut_walk_graph[45] = (19)*256 + (22);
	Fleut_walk_graph[46] = (-1)*256 + (-1);
	Fleut_walk_graph[47] = (-1)*256 + (-1);
	Fleut_walk_graph[48] = (-1)*256 + (-1);
	Fleut_walk_graph[49] = (-1)*256 + (-1);
	Fleut_walk_graph[50] = (-1)*256 + (-1);
	Fleut_walk_graph[51] = (-1)*256 + (-1);
	Fleut_walk_graph[52] = (-1)*256 + (-1);
	Fleut_walk_graph[53] = (-1)*256 + (-1);
	Fleut_walk_graph[54] = (-1)*256 + (-1);
	Fleut_walk_graph[55] = (-1)*256 + (-1);
	Fleut_walk_graph[56] = (-1)*256 + (-1);
	Fleut_walk_graph[57] = (-1)*256 + (-1);
	Fleut_walk_graph[58] = (-1)*256 + (-1);
	Fleut_walk_graph[59] = (-1)*256 + (-1);
	Fleut_walk_graph[60] = (-1)*256 + (-1);
	Fleut_walk_graph[61] = (-1)*256 + (-1);
	Fleut_walk_graph[62] = (-1)*256 + (-1);
	Fleut_walk_graph[63] = (-1)*256 + (-1);
	Fleut_walk_graph[64] = (-1)*256 + (-1);
	Fleut_walk_graph[65] = (-1)*256 + (-1);
	Fleut_walk_graph[66] = (-1)*256 + (-1);
	Fleut_walk_graph[67] = (-1)*256 + (-1);
	Fleut_walk_graph[68] = (-1)*256 + (-1);
	Fleut_walk_graph[69] = (-1)*256 + (-1);
	Fleut_walk_graph[70] = (-1)*256 + (-1);
	Fleut_walk_graph[71] = (-1)*256 + (-1);
	Fleut_walk_graph[72] = (-1)*256 + (-1);
	Fleut_walk_graph[73] = (-1)*256 + (-1);
	Fleut_walk_graph[74] = (-1)*256 + (-1);
	Fleut_walk_graph[75] = (-1)*256 + (-1);
	Fleut_walk_graph[76] = (-1)*256 + (-1);
	Fleut_walk_graph[77] = (-1)*256 + (-1);
	Fleut_walk_graph[78] = (-1)*256 + (-1);
	Fleut_walk_graph[79] = (-1)*256 + (-1);
	Fleut_walk_graph[80] = (-1)*256 + (-1);
	Fleut_walk_graph[81] = (-1)*256 + (-1);
	Fleut_walk_graph[82] = (-1)*256 + (-1);
	Fleut_walk_graph[83] = (-1)*256 + (-1);
}