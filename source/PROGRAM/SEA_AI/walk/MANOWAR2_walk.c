int MANOWAR2_walk_count;
float MANOWAR2_walk_verts[201];
int MANOWAR2_walk_types[67];
int MANOWAR2_walk_graph[134];

void MANOWAR2_walk_init()
{
	MANOWAR2_walk_count = 67;

	MANOWAR2_walk_verts[0 ] = 0.615476;
	MANOWAR2_walk_verts[1 ] = 29.523232;
	MANOWAR2_walk_verts[2 ] = 24.986134;
	MANOWAR2_walk_verts[3 ] = 0.723437;
	MANOWAR2_walk_verts[4 ] = 35.126392;
	MANOWAR2_walk_verts[5 ] = 1.843230;
	MANOWAR2_walk_verts[6 ] = -0.751354;
	MANOWAR2_walk_verts[7 ] = 35.126392;
	MANOWAR2_walk_verts[8 ] = 1.843230;
	MANOWAR2_walk_verts[9 ] = -0.817035;
	MANOWAR2_walk_verts[10] = 29.433475;
	MANOWAR2_walk_verts[11] = 24.793106;
	MANOWAR2_walk_verts[12] = -3.191659;
	MANOWAR2_walk_verts[13] = 10.561493;
	MANOWAR2_walk_verts[14] = 34.609921;
	MANOWAR2_walk_verts[15] = 2.962568;
	MANOWAR2_walk_verts[16] = 10.559065;
	MANOWAR2_walk_verts[17] = 34.412598;
	MANOWAR2_walk_verts[18] = 4.606352;
	MANOWAR2_walk_verts[19] = 10.523885;
	MANOWAR2_walk_verts[20] = 27.483906;
	MANOWAR2_walk_verts[21] = -4.215181;
	MANOWAR2_walk_verts[22] = 10.542651;
	MANOWAR2_walk_verts[23] = 27.423426;
	MANOWAR2_walk_verts[24] = -5.347441;
	MANOWAR2_walk_verts[25] = 8.021749;
	MANOWAR2_walk_verts[26] = 19.434706;
	MANOWAR2_walk_verts[27] = 3.942326;
	MANOWAR2_walk_verts[28] = 8.062730;
	MANOWAR2_walk_verts[29] = 19.739679;
	MANOWAR2_walk_verts[30] = -3.318545;
	MANOWAR2_walk_verts[31] = 7.993612;
	MANOWAR2_walk_verts[32] = 8.508876;
	MANOWAR2_walk_verts[33] = -5.243299;
	MANOWAR2_walk_verts[34] = 8.011259;
	MANOWAR2_walk_verts[35] = -0.946870;
	MANOWAR2_walk_verts[36] = 3.304319;
	MANOWAR2_walk_verts[37] = 8.005899;
	MANOWAR2_walk_verts[38] = -0.861141;
	MANOWAR2_walk_verts[39] = 5.361075;
	MANOWAR2_walk_verts[40] = 8.332156;
	MANOWAR2_walk_verts[41] = 13.256797;
	MANOWAR2_walk_verts[42] = 1.725672;
	MANOWAR2_walk_verts[43] = 8.052353;
	MANOWAR2_walk_verts[44] = 8.870904;
	MANOWAR2_walk_verts[45] = 5.771314;
	MANOWAR2_walk_verts[46] = 8.061391;
	MANOWAR2_walk_verts[47] = 15.473398;
	MANOWAR2_walk_verts[48] = 5.623305;
	MANOWAR2_walk_verts[49] = 8.157812;
	MANOWAR2_walk_verts[50] = 5.953400;
	MANOWAR2_walk_verts[51] = 5.540526;
	MANOWAR2_walk_verts[52] = 8.011257;
	MANOWAR2_walk_verts[53] = 1.506391;
	MANOWAR2_walk_verts[54] = -5.862146;
	MANOWAR2_walk_verts[55] = 8.036299;
	MANOWAR2_walk_verts[56] = 15.483920;
	MANOWAR2_walk_verts[57] = -5.796908;
	MANOWAR2_walk_verts[58] = 8.011257;
	MANOWAR2_walk_verts[59] = 10.901548;
	MANOWAR2_walk_verts[60] = -5.686843;
	MANOWAR2_walk_verts[61] = 8.011259;
	MANOWAR2_walk_verts[62] = 1.515916;
	MANOWAR2_walk_verts[63] = -5.103421;
	MANOWAR2_walk_verts[64] = 10.787238;
	MANOWAR2_walk_verts[65] = -11.492319;
	MANOWAR2_walk_verts[66] = -4.865223;
	MANOWAR2_walk_verts[67] = 10.863337;
	MANOWAR2_walk_verts[68] = -16.154966;
	MANOWAR2_walk_verts[69] = 4.607425;
	MANOWAR2_walk_verts[70] = 10.917102;
	MANOWAR2_walk_verts[71] = -18.548159;
	MANOWAR2_walk_verts[72] = -2.684328;
	MANOWAR2_walk_verts[73] = 11.065875;
	MANOWAR2_walk_verts[74] = -26.717665;
	MANOWAR2_walk_verts[75] = -2.684328;
	MANOWAR2_walk_verts[76] = 11.065875;
	MANOWAR2_walk_verts[77] = -28.245045;
	MANOWAR2_walk_verts[78] = 8.639272;
	MANOWAR2_walk_verts[79] = 10.595881;
	MANOWAR2_walk_verts[80] = 23.339087;
	MANOWAR2_walk_verts[81] = -9.086784;
	MANOWAR2_walk_verts[82] = 10.595882;
	MANOWAR2_walk_verts[83] = 23.537605;
	MANOWAR2_walk_verts[84] = -9.362776;
	MANOWAR2_walk_verts[85] = 8.500584;
	MANOWAR2_walk_verts[86] = -1.165385;
	MANOWAR2_walk_verts[87] = 9.004411;
	MANOWAR2_walk_verts[88] = 8.361345;
	MANOWAR2_walk_verts[89] = -1.085608;
	MANOWAR2_walk_verts[90] = 1.846625;
	MANOWAR2_walk_verts[91] = 33.633144;
	MANOWAR2_walk_verts[92] = 25.163971;
	MANOWAR2_walk_verts[93] = -1.266117;
	MANOWAR2_walk_verts[94] = 33.538151;
	MANOWAR2_walk_verts[95] = 26.933126;
	MANOWAR2_walk_verts[96] = -1.672526;
	MANOWAR2_walk_verts[97] = 42.381802;
	MANOWAR2_walk_verts[98] = 1.907483;
	MANOWAR2_walk_verts[99] = 1.372005;
	MANOWAR2_walk_verts[100] = 42.381802;
	MANOWAR2_walk_verts[101] = 2.155982;
	MANOWAR2_walk_verts[102] = -4.572263;
	MANOWAR2_walk_verts[103] = 10.769656;
	MANOWAR2_walk_verts[104] = -9.888472;
	MANOWAR2_walk_verts[105] = -2.885259;
	MANOWAR2_walk_verts[106] = 10.881110;
	MANOWAR2_walk_verts[107] = -18.292221;
	MANOWAR2_walk_verts[108] = 3.543386;
	MANOWAR2_walk_verts[109] = 10.654981;
	MANOWAR2_walk_verts[110] = -5.455564;
	MANOWAR2_walk_verts[111] = -0.066603;
	MANOWAR2_walk_verts[112] = 10.785291;
	MANOWAR2_walk_verts[113] = -13.075970;
	MANOWAR2_walk_verts[114] = 3.751518;
	MANOWAR2_walk_verts[115] = 10.925003;
	MANOWAR2_walk_verts[116] = -22.083321;
	MANOWAR2_walk_verts[117] = 2.745775;
	MANOWAR2_walk_verts[118] = 13.848479;
	MANOWAR2_walk_verts[119] = -28.258793;
	MANOWAR2_walk_verts[120] = -4.417478;
	MANOWAR2_walk_verts[121] = 13.940515;
	MANOWAR2_walk_verts[122] = -32.608440;
	MANOWAR2_walk_verts[123] = -6.514974;
	MANOWAR2_walk_verts[124] = 8.052855;
	MANOWAR2_walk_verts[125] = 20.661814;
	MANOWAR2_walk_verts[126] = -6.350006;
	MANOWAR2_walk_verts[127] = 10.523885;
	MANOWAR2_walk_verts[128] = 25.593803;
	MANOWAR2_walk_verts[129] = 6.326313;
	MANOWAR2_walk_verts[130] = 8.077542;
	MANOWAR2_walk_verts[131] = 20.769575;
	MANOWAR2_walk_verts[132] = 6.076056;
	MANOWAR2_walk_verts[133] = 10.523885;
	MANOWAR2_walk_verts[134] = 24.973799;
	MANOWAR2_walk_verts[135] = -6.278878;
	MANOWAR2_walk_verts[136] = 8.042897;
	MANOWAR2_walk_verts[137] = -2.463721;
	MANOWAR2_walk_verts[138] = -6.107722;
	MANOWAR2_walk_verts[139] = 10.728044;
	MANOWAR2_walk_verts[140] = -6.923678;
	MANOWAR2_walk_verts[141] = 6.021126;
	MANOWAR2_walk_verts[142] = 8.058020;
	MANOWAR2_walk_verts[143] = -2.442505;
	MANOWAR2_walk_verts[144] = 5.990520;
	MANOWAR2_walk_verts[145] = 10.728044;
	MANOWAR2_walk_verts[146] = -6.923678;
	MANOWAR2_walk_verts[147] = 4.875544;
	MANOWAR2_walk_verts[148] = 11.052759;
	MANOWAR2_walk_verts[149] = -26.201519;
	MANOWAR2_walk_verts[150] = 5.145428;
	MANOWAR2_walk_verts[151] = 13.789887;
	MANOWAR2_walk_verts[152] = -30.556747;
	MANOWAR2_walk_verts[153] = -5.295714;
	MANOWAR2_walk_verts[154] = 11.052757;
	MANOWAR2_walk_verts[155] = -26.087223;
	MANOWAR2_walk_verts[156] = 4.756901;
	MANOWAR2_walk_verts[157] = 10.878154;
	MANOWAR2_walk_verts[158] = -16.129868;
	MANOWAR2_walk_verts[159] = -3.902009;
	MANOWAR2_walk_verts[160] = 14.359268;
	MANOWAR2_walk_verts[161] = -41.912182;
	MANOWAR2_walk_verts[162] = 3.398465;
	MANOWAR2_walk_verts[163] = 14.413998;
	MANOWAR2_walk_verts[164] = -40.497478;
	MANOWAR2_walk_verts[165] = 4.420041;
	MANOWAR2_walk_verts[166] = 13.920520;
	MANOWAR2_walk_verts[167] = -33.421120;
	MANOWAR2_walk_verts[168] = 2.455295;
	MANOWAR2_walk_verts[169] = 11.073269;
	MANOWAR2_walk_verts[170] = -26.868198;
	MANOWAR2_walk_verts[171] = 2.455295;
	MANOWAR2_walk_verts[172] = 11.073269;
	MANOWAR2_walk_verts[173] = -28.291796;
	MANOWAR2_walk_verts[174] = -3.315972;
	MANOWAR2_walk_verts[175] = 8.017762;
	MANOWAR2_walk_verts[176] = -3.112791;
	MANOWAR2_walk_verts[177] = -3.315972;
	MANOWAR2_walk_verts[178] = 8.017762;
	MANOWAR2_walk_verts[179] = -4.492827;
	MANOWAR2_walk_verts[180] = 3.038856;
	MANOWAR2_walk_verts[181] = 8.017762;
	MANOWAR2_walk_verts[182] = -3.130774;
	MANOWAR2_walk_verts[183] = 3.038856;
	MANOWAR2_walk_verts[184] = 8.017762;
	MANOWAR2_walk_verts[185] = -4.653948;
	MANOWAR2_walk_verts[186] = 3.225321;
	MANOWAR2_walk_verts[187] = 7.965959;
	MANOWAR2_walk_verts[188] = 21.468357;
	MANOWAR2_walk_verts[189] = 3.225321;
	MANOWAR2_walk_verts[190] = 7.965959;
	MANOWAR2_walk_verts[191] = 22.866987;
	MANOWAR2_walk_verts[192] = -3.355401;
	MANOWAR2_walk_verts[193] = 7.970070;
	MANOWAR2_walk_verts[194] = 21.524086;
	MANOWAR2_walk_verts[195] = -3.355401;
	MANOWAR2_walk_verts[196] = 7.970070;
	MANOWAR2_walk_verts[197] = 22.980444;
	MANOWAR2_walk_verts[198] = -5.358730;
	MANOWAR2_walk_verts[199] = 13.789887;
	MANOWAR2_walk_verts[200] = -30.584610;

	MANOWAR2_walk_types[0 ] = 4;
	MANOWAR2_walk_types[1 ] = 4;
	MANOWAR2_walk_types[2 ] = 4;
	MANOWAR2_walk_types[3 ] = 4;
	MANOWAR2_walk_types[4 ] = 0;
	MANOWAR2_walk_types[5 ] = 0;
	MANOWAR2_walk_types[6 ] = 0;
	MANOWAR2_walk_types[7 ] = 0;
	MANOWAR2_walk_types[8 ] = 0;
	MANOWAR2_walk_types[9 ] = 0;
	MANOWAR2_walk_types[10] = 0;
	MANOWAR2_walk_types[11] = 0;
	MANOWAR2_walk_types[12] = 0;
	MANOWAR2_walk_types[13] = 0;
	MANOWAR2_walk_types[14] = 0;
	MANOWAR2_walk_types[15] = 1;
	MANOWAR2_walk_types[16] = 1;
	MANOWAR2_walk_types[17] = 1;
	MANOWAR2_walk_types[18] = 1;
	MANOWAR2_walk_types[19] = 1;
	MANOWAR2_walk_types[20] = 1;
	MANOWAR2_walk_types[21] = 1;
	MANOWAR2_walk_types[22] = 1;
	MANOWAR2_walk_types[23] = 1;
	MANOWAR2_walk_types[24] = 2;
	MANOWAR2_walk_types[25] = 3;
	MANOWAR2_walk_types[26] = 5;
	MANOWAR2_walk_types[27] = 5;
	MANOWAR2_walk_types[28] = 5;
	MANOWAR2_walk_types[29] = 5;
	MANOWAR2_walk_types[30] = 6;
	MANOWAR2_walk_types[31] = 6;
	MANOWAR2_walk_types[32] = 6;
	MANOWAR2_walk_types[33] = 6;
	MANOWAR2_walk_types[34] = 0;
	MANOWAR2_walk_types[35] = 0;
	MANOWAR2_walk_types[36] = 0;
	MANOWAR2_walk_types[37] = 0;
	MANOWAR2_walk_types[38] = 0;
	MANOWAR2_walk_types[39] = 0;
	MANOWAR2_walk_types[40] = 0;
	MANOWAR2_walk_types[41] = 0;
	MANOWAR2_walk_types[42] = 0;
	MANOWAR2_walk_types[43] = 0;
	MANOWAR2_walk_types[44] = 0;
	MANOWAR2_walk_types[45] = 0;
	MANOWAR2_walk_types[46] = 0;
	MANOWAR2_walk_types[47] = 0;
	MANOWAR2_walk_types[48] = 0;
	MANOWAR2_walk_types[49] = 0;
	MANOWAR2_walk_types[50] = 0;
	MANOWAR2_walk_types[51] = 0;
	MANOWAR2_walk_types[52] = 1;
	MANOWAR2_walk_types[53] = 0;
	MANOWAR2_walk_types[54] = 0;
	MANOWAR2_walk_types[55] = 0;
	MANOWAR2_walk_types[56] = 2;
	MANOWAR2_walk_types[57] = 3;
	MANOWAR2_walk_types[58] = 2;
	MANOWAR2_walk_types[59] = 3;
	MANOWAR2_walk_types[60] = 2;
	MANOWAR2_walk_types[61] = 3;
	MANOWAR2_walk_types[62] = 2;
	MANOWAR2_walk_types[63] = 3;
	MANOWAR2_walk_types[64] = 2;
	MANOWAR2_walk_types[65] = 3;
	MANOWAR2_walk_types[66] = 0;

	MANOWAR2_walk_graph[0 ] = (61)*256 + (60);
	MANOWAR2_walk_graph[1 ] = (59)*256 + (58);
	MANOWAR2_walk_graph[2 ] = (60)*256 + (12);
	MANOWAR2_walk_graph[3 ] = (58)*256 + (11);
	MANOWAR2_walk_graph[4 ] = (12)*256 + (47);
	MANOWAR2_walk_graph[5 ] = (11)*256 + (45);
	MANOWAR2_walk_graph[6 ] = (47)*256 + (48);
	MANOWAR2_walk_graph[7 ] = (45)*256 + (46);
	MANOWAR2_walk_graph[8 ] = (45)*256 + (28);
	MANOWAR2_walk_graph[9 ] = (47)*256 + (29);
	MANOWAR2_walk_graph[10] = (12)*256 + (11);
	MANOWAR2_walk_graph[11] = (12)*256 + (17);
	MANOWAR2_walk_graph[12] = (11)*256 + (20);
	MANOWAR2_walk_graph[13] = (17)*256 + (16);
	MANOWAR2_walk_graph[14] = (20)*256 + (10);
	MANOWAR2_walk_graph[15] = (20)*256 + (19);
	MANOWAR2_walk_graph[16] = (10)*256 + (19);
	MANOWAR2_walk_graph[17] = (16)*256 + (14);
	MANOWAR2_walk_graph[18] = (14)*256 + (10);
	MANOWAR2_walk_graph[19] = (12)*256 + (20);
	MANOWAR2_walk_graph[20] = (17)*256 + (11);
	MANOWAR2_walk_graph[21] = (57)*256 + (56);
	MANOWAR2_walk_graph[22] = (25)*256 + (24);
	MANOWAR2_walk_graph[23] = (56)*256 + (49);
	MANOWAR2_walk_graph[24] = (24)*256 + (51);
	MANOWAR2_walk_graph[25] = (51)*256 + (66);
	MANOWAR2_walk_graph[26] = (49)*256 + (50);
	MANOWAR2_walk_graph[27] = (49)*256 + (38);
	MANOWAR2_walk_graph[28] = (38)*256 + (56);
	MANOWAR2_walk_graph[29] = (24)*256 + (35);
	MANOWAR2_walk_graph[30] = (51)*256 + (35);
	MANOWAR2_walk_graph[31] = (51)*256 + (22);
	MANOWAR2_walk_graph[32] = (35)*256 + (22);
	MANOWAR2_walk_graph[33] = (38)*256 + (23);
	MANOWAR2_walk_graph[34] = (23)*256 + (52);
	MANOWAR2_walk_graph[35] = (38)*256 + (35);
	MANOWAR2_walk_graph[36] = (23)*256 + (35);
	MANOWAR2_walk_graph[37] = (52)*256 + (35);
	MANOWAR2_walk_graph[38] = (52)*256 + (22);
	MANOWAR2_walk_graph[39] = (22)*256 + (23);
	MANOWAR2_walk_graph[40] = (24)*256 + (22);
	MANOWAR2_walk_graph[41] = (50)*256 + (55); // tail
	MANOWAR2_walk_graph[42] = (55)*256 + (39);
	MANOWAR2_walk_graph[43] = (55)*256 + (54);
	MANOWAR2_walk_graph[44] = (54)*256 + (39);
	MANOWAR2_walk_graph[45] = (54)*256 + (53);
	MANOWAR2_walk_graph[46] = (66)*256 + (40);
	MANOWAR2_walk_graph[47] = (40)*256 + (53);
	MANOWAR2_walk_graph[48] = (39)*256 + (40);
	MANOWAR2_walk_graph[49] = (55)*256 + (40);
	MANOWAR2_walk_graph[50] = (54)*256 + (40);
	MANOWAR2_walk_graph[51] = (53)*256 + (55);
	MANOWAR2_walk_graph[52] = (53)*256 + (39);
	MANOWAR2_walk_graph[53] = (50)*256 + (40);
	MANOWAR2_walk_graph[54] = (66)*256 + (39);
	MANOWAR2_walk_graph[55] = (22)*256 + (21); // middle
	MANOWAR2_walk_graph[56] = (52)*256 + (37);
	MANOWAR2_walk_graph[57] = (37)*256 + (48);
	MANOWAR2_walk_graph[58] = (51)*256 + (48);
	MANOWAR2_walk_graph[59] = (21)*256 + (37);
	MANOWAR2_walk_graph[60] = (22)*256 + (37);
	MANOWAR2_walk_graph[61] = (21)*256 + (34);
	MANOWAR2_walk_graph[62] = (34)*256 + (37);
	MANOWAR2_walk_graph[63] = (38)*256 + (37);
	MANOWAR2_walk_graph[64] = (35)*256 + (37);
	MANOWAR2_walk_graph[65] = (46)*256 + (34);
	MANOWAR2_walk_graph[66] = (46)*256 + (48);
	MANOWAR2_walk_graph[67] = (34)*256 + (48);
	MANOWAR2_walk_graph[68] = (23)*256 + (37);
	MANOWAR2_walk_graph[69] = (36)*256 + (48);
	MANOWAR2_walk_graph[70] = (46)*256 + (36);
	MANOWAR2_walk_graph[71] = (37)*256 + (36);
	MANOWAR2_walk_graph[72] = (52)*256 + (36);
	MANOWAR2_walk_graph[73] = (22)*256 + (36);
	MANOWAR2_walk_graph[74] = (34)*256 + (36);
	MANOWAR2_walk_graph[75] = (19)*256 + (18); // the deck with the boat
	MANOWAR2_walk_graph[76] = (10)*256 + (18);
	MANOWAR2_walk_graph[77] = (18)*256 + (8);
	MANOWAR2_walk_graph[78] = (8)*256 + (41);
	MANOWAR2_walk_graph[79] = (16)*256 + (13);
	MANOWAR2_walk_graph[80] = (14)*256 + (13);
	MANOWAR2_walk_graph[81] = (14)*256 + (9);
	MANOWAR2_walk_graph[82] = (13)*256 + (15);
	MANOWAR2_walk_graph[83] = (15)*256 + (43);
	MANOWAR2_walk_graph[84] = (9)*256 + (43);
	MANOWAR2_walk_graph[85] = (9)*256 + (15);
	MANOWAR2_walk_graph[86] = (9)*256 + (13);
	MANOWAR2_walk_graph[87] = (8)*256 + (64);
	MANOWAR2_walk_graph[88] = (64)*256 + (65);
	MANOWAR2_walk_graph[89] = (9)*256 + (62);
	MANOWAR2_walk_graph[90] = (62)*256 + (63);
	MANOWAR2_walk_graph[91] = (8)*256 + (9);
	MANOWAR2_walk_graph[92] = (10)*256 + (64);
	MANOWAR2_walk_graph[93] = (18)*256 + (13);
	MANOWAR2_walk_graph[94] = (18)*256 + (15);
	MANOWAR2_walk_graph[95] = (18)*256 + (9);
	MANOWAR2_walk_graph[96] = (8)*256 + (15);
	MANOWAR2_walk_graph[97] = (41)*256 + (42); // nose
	MANOWAR2_walk_graph[98] = (43)*256 + (44);
	MANOWAR2_walk_graph[99] = (42)*256 + (27);
	MANOWAR2_walk_graph[100] = (44)*256 + (26);
	MANOWAR2_walk_graph[101] = (42)*256 + (7);
	MANOWAR2_walk_graph[102] = (44)*256 + (6);
	MANOWAR2_walk_graph[103] = (7)*256 + (6);
	MANOWAR2_walk_graph[104] = (7)*256 + (4);
	MANOWAR2_walk_graph[105] = (4)*256 + (5);
	MANOWAR2_walk_graph[106] = (5)*256 + (6);
	MANOWAR2_walk_graph[107] = (4)*256 + (6);
	MANOWAR2_walk_graph[108] = (7)*256 + (5);
	MANOWAR2_walk_graph[109] = (24)*256 + (56); //adds
	MANOWAR2_walk_graph[110] = (60)*256 + (58);
	MANOWAR2_walk_graph[111] = (64)*256 + (62);
	MANOWAR2_walk_graph[112] = (62)*256 + (8);
	MANOWAR2_walk_graph[113] = (64)*256 + (9);
	MANOWAR2_walk_graph[114] = (14)*256 + (12);
	MANOWAR2_walk_graph[115] = (64)*256 + (15);
	MANOWAR2_walk_graph[116] = (10)*256 + (58);
	MANOWAR2_walk_graph[117] = (41)*256 + (18);
	MANOWAR2_walk_graph[118] = (62)*256 + (18);
	MANOWAR2_walk_graph[119] = (62)*256 + (19);
	MANOWAR2_walk_graph[120] = (64)*256 + (41);
	MANOWAR2_walk_graph[121] = (62)*256 + (43);
	MANOWAR2_walk_graph[122] = (47)*256 + (17);
	MANOWAR2_walk_graph[123] = (60)*256 + (11);
	MANOWAR2_walk_graph[124] = (12)*256 + (58);
	MANOWAR2_walk_graph[125] = (45)*256 + (20);
	MANOWAR2_walk_graph[126] = (28)*256 + (2); // masts
	MANOWAR2_walk_graph[127] = (2)*256 + (32);
	MANOWAR2_walk_graph[128] = (29)*256 + (1);
	MANOWAR2_walk_graph[129] = (1)*256 + (33);
	MANOWAR2_walk_graph[130] = (27)*256 + (3);
	MANOWAR2_walk_graph[131] = (3)*256 + (31);
	MANOWAR2_walk_graph[132] = (26)*256 + (0);
	MANOWAR2_walk_graph[133] = (0)*256 + (30);
}
