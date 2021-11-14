int GALEON1_walk_count;
float GALEON1_walk_verts[147];
int GALEON1_walk_types[49];
int GALEON1_walk_graph[98];

void GALEON1_walk_init()
{
	GALEON1_walk_count = 49;

	GALEON1_walk_verts[0 ] = 2.479131;
	GALEON1_walk_verts[1 ] = 7.998534;
	GALEON1_walk_verts[2 ] = 21.627048;
	GALEON1_walk_verts[3 ] = -1.613778;
	GALEON1_walk_verts[4 ] = 8.022863;
	GALEON1_walk_verts[5 ] = 22.829573;
	GALEON1_walk_verts[6 ] = -2.240785;
	GALEON1_walk_verts[7 ] = 7.964279;
	GALEON1_walk_verts[8 ] = 17.140944;
	GALEON1_walk_verts[9 ] = 1.402238;
	GALEON1_walk_verts[10] = 7.931758;
	GALEON1_walk_verts[11] = 17.581398;
	GALEON1_walk_verts[12] = 1.525286;
	GALEON1_walk_verts[13] = 7.998534;
	GALEON1_walk_verts[14] = 20.311527;
	GALEON1_walk_verts[15] = 4.553928;
	GALEON1_walk_verts[16] = 4.404056;
	GALEON1_walk_verts[17] = 15.220333;
	GALEON1_walk_verts[18] = 2.588042;
	GALEON1_walk_verts[19] = 4.372091;
	GALEON1_walk_verts[20] = 13.694878;
	GALEON1_walk_verts[21] = 2.889347;
	GALEON1_walk_verts[22] = 4.377940;
	GALEON1_walk_verts[23] = -0.536930;
	GALEON1_walk_verts[24] = -2.774298;
	GALEON1_walk_verts[25] = 4.377940;
	GALEON1_walk_verts[26] = -0.757839;
	GALEON1_walk_verts[27] = -3.019857;
	GALEON1_walk_verts[28] = 4.372091;
	GALEON1_walk_verts[29] = 11.233974;
	GALEON1_walk_verts[30] = -2.967510;
	GALEON1_walk_verts[31] = 4.353580;
	GALEON1_walk_verts[32] = -5.342289;
	GALEON1_walk_verts[33] = -4.872569;
	GALEON1_walk_verts[34] = 4.371659;
	GALEON1_walk_verts[35] = -7.142319;
	GALEON1_walk_verts[36] = -3.499005;
	GALEON1_walk_verts[37] = 7.965878;
	GALEON1_walk_verts[38] = -12.292288;
	GALEON1_walk_verts[39] = -1.432216;
	GALEON1_walk_verts[40] = 7.991662;
	GALEON1_walk_verts[41] = -12.165691;
	GALEON1_walk_verts[42] = -1.387099;
	GALEON1_walk_verts[43] = 7.763645;
	GALEON1_walk_verts[44] = -8.525863;
	GALEON1_walk_verts[45] = 3.032868;
	GALEON1_walk_verts[46] = 7.748635;
	GALEON1_walk_verts[47] = -8.902446;
	GALEON1_walk_verts[48] = 3.404739;
	GALEON1_walk_verts[49] = 8.011088;
	GALEON1_walk_verts[50] = -12.891375;
	GALEON1_walk_verts[51] = 2.597231;
	GALEON1_walk_verts[52] = 11.605305;
	GALEON1_walk_verts[53] = -17.878019;
	GALEON1_walk_verts[54] = 0.399049;
	GALEON1_walk_verts[55] = 11.605305;
	GALEON1_walk_verts[56] = -18.647434;
	GALEON1_walk_verts[57] = 0.341518;
	GALEON1_walk_verts[58] = 11.351827;
	GALEON1_walk_verts[59] = -14.882166;
	GALEON1_walk_verts[60] = -2.315072;
	GALEON1_walk_verts[61] = 11.351825;
	GALEON1_walk_verts[62] = -14.940988;
	GALEON1_walk_verts[63] = -1.061784;
	GALEON1_walk_verts[64] = 12.005588;
	GALEON1_walk_verts[65] = -24.904451;
	GALEON1_walk_verts[66] = 1.132604;
	GALEON1_walk_verts[67] = 12.028965;
	GALEON1_walk_verts[68] = -25.107944;
	GALEON1_walk_verts[69] = 3.008331;
	GALEON1_walk_verts[70] = 4.404418;
	GALEON1_walk_verts[71] = -5.549284;
	GALEON1_walk_verts[72] = -0.350600;
	GALEON1_walk_verts[73] = 4.400444;
	GALEON1_walk_verts[74] = 15.267602;
	GALEON1_walk_verts[75] = -0.607223;
	GALEON1_walk_verts[76] = 4.390885;
	GALEON1_walk_verts[77] = -6.634556;
	GALEON1_walk_verts[78] = 0.933762;
	GALEON1_walk_verts[79] = 7.965878;
	GALEON1_walk_verts[80] = -12.416549;
	GALEON1_walk_verts[81] = 4.315394;
	GALEON1_walk_verts[82] = 4.404056;
	GALEON1_walk_verts[83] = 8.546732;
	GALEON1_walk_verts[84] = 4.324085;
	GALEON1_walk_verts[85] = 4.404056;
	GALEON1_walk_verts[86] = 0.078340;
	GALEON1_walk_verts[87] = -4.369485;
	GALEON1_walk_verts[88] = 4.404056;
	GALEON1_walk_verts[89] = 3.998842;
	GALEON1_walk_verts[90] = -3.988900;
	GALEON1_walk_verts[91] = 4.404056;
	GALEON1_walk_verts[92] = 12.730330;
	GALEON1_walk_verts[93] = -4.375827;
	GALEON1_walk_verts[94] = 4.404056;
	GALEON1_walk_verts[95] = 0.128785;
	GALEON1_walk_verts[96] = 4.195003;
	GALEON1_walk_verts[97] = 4.404056;
	GALEON1_walk_verts[98] = -4.378664;
	GALEON1_walk_verts[99] = 4.381739;
	GALEON1_walk_verts[100] = 4.404056;
	GALEON1_walk_verts[101] = 3.944144;
	GALEON1_walk_verts[102] = -0.350600;
	GALEON1_walk_verts[103] = 4.400444;
	GALEON1_walk_verts[104] = 16.290386;
	GALEON1_walk_verts[105] = -0.607223;
	GALEON1_walk_verts[106] = 4.390885;
	GALEON1_walk_verts[107] = -7.833758;
	GALEON1_walk_verts[108] = 0.933762;
	GALEON1_walk_verts[109] = 7.965878;
	GALEON1_walk_verts[110] = -13.362196;
	GALEON1_walk_verts[111] = -4.938903;
	GALEON1_walk_verts[112] = 8.818576;
	GALEON1_walk_verts[113] = 18.466112;
	GALEON1_walk_verts[114] = -6.862862;
	GALEON1_walk_verts[115] = 5.718855;
	GALEON1_walk_verts[116] = -5.313205;
	GALEON1_walk_verts[117] = 6.868483;
	GALEON1_walk_verts[118] = 5.686965;
	GALEON1_walk_verts[119] = -5.406012;
	GALEON1_walk_verts[120] = -0.846510;
	GALEON1_walk_verts[121] = 18.375372;
	GALEON1_walk_verts[122] = 19.731007;
	GALEON1_walk_verts[123] = -0.896742;
	GALEON1_walk_verts[124] = 19.107752;
	GALEON1_walk_verts[125] = -3.367912;
	GALEON1_walk_verts[126] = 0.940723;
	GALEON1_walk_verts[127] = 19.240494;
	GALEON1_walk_verts[128] = -3.216009;
	GALEON1_walk_verts[129] = -1.284124;
	GALEON1_walk_verts[130] = 20.773918;
	GALEON1_walk_verts[131] = 21.277502;
	GALEON1_walk_verts[132] = -1.068559;
	GALEON1_walk_verts[133] = 21.935522;
	GALEON1_walk_verts[134] = -2.310501;
	GALEON1_walk_verts[135] = 1.119918;
	GALEON1_walk_verts[136] = 21.935522;
	GALEON1_walk_verts[137] = -0.518597;
	GALEON1_walk_verts[138] = 5.528295;
	GALEON1_walk_verts[139] = 4.377940;
	GALEON1_walk_verts[140] = -2.195567;
	GALEON1_walk_verts[141] = 5.608262;
	GALEON1_walk_verts[142] = 4.372091;
	GALEON1_walk_verts[143] = 6.262029;
	GALEON1_walk_verts[144] = -5.492138;
	GALEON1_walk_verts[145] = 4.353580;
	GALEON1_walk_verts[146] = 2.052633;

	GALEON1_walk_types[0 ] = 0;
	GALEON1_walk_types[1 ] = 0;
	GALEON1_walk_types[2 ] = 0;
	GALEON1_walk_types[3 ] = 0;
	GALEON1_walk_types[4 ] = 0;
	GALEON1_walk_types[5 ] = 0;
	GALEON1_walk_types[6 ] = 0;
	GALEON1_walk_types[7 ] = 0;
	GALEON1_walk_types[8 ] = 0;
	GALEON1_walk_types[9 ] = 0;
	GALEON1_walk_types[10] = 0;
	GALEON1_walk_types[11] = 0;
	GALEON1_walk_types[12] = 0;
	GALEON1_walk_types[13] = 0;
	GALEON1_walk_types[14] = 0;
	GALEON1_walk_types[15] = 0;
	GALEON1_walk_types[16] = 0;
	GALEON1_walk_types[17] = 0;
	GALEON1_walk_types[18] = 0;
	GALEON1_walk_types[19] = 0;
	GALEON1_walk_types[20] = 0;
	GALEON1_walk_types[21] = 0;
	GALEON1_walk_types[22] = 0;
	GALEON1_walk_types[23] = 0;
	GALEON1_walk_types[24] = 2;
	GALEON1_walk_types[25] = 2;
	GALEON1_walk_types[26] = 2;
	GALEON1_walk_types[27] = 1;
	GALEON1_walk_types[28] = 1;
	GALEON1_walk_types[29] = 1;
	GALEON1_walk_types[30] = 1;
	GALEON1_walk_types[31] = 1;
	GALEON1_walk_types[32] = 1;
	GALEON1_walk_types[33] = 1;
	GALEON1_walk_types[34] = 3;
	GALEON1_walk_types[35] = 3;
	GALEON1_walk_types[36] = 3;
	GALEON1_walk_types[37] = 5;
	GALEON1_walk_types[38] = 5;
	GALEON1_walk_types[39] = 5;
	GALEON1_walk_types[40] = 4;
	GALEON1_walk_types[41] = 4;
	GALEON1_walk_types[42] = 4;
	GALEON1_walk_types[43] = 6;
	GALEON1_walk_types[44] = 6;
	GALEON1_walk_types[45] = 6;
	GALEON1_walk_types[46] = 0;
	GALEON1_walk_types[47] = 0;
	GALEON1_walk_types[48] = 0;

	GALEON1_walk_graph[0 ] = (25)*256 + (10);
	GALEON1_walk_graph[1 ] = (10)*256 + (11);
	GALEON1_walk_graph[2 ] = (25)*256 + (8);
	GALEON1_walk_graph[3 ] = (11)*256 + (25);
	GALEON1_walk_graph[4 ] = (25)*256 + (23);
	GALEON1_walk_graph[5 ] = (11)*256 + (38);
	GALEON1_walk_graph[6 ] = (23)*256 + (32);
	GALEON1_walk_graph[7 ] = (32)*256 + (46);
	GALEON1_walk_graph[8 ] = (32)*256 + (39);
	GALEON1_walk_graph[9 ] = (46)*256 + (28);
	GALEON1_walk_graph[10] = (28)*256 + (7);
	GALEON1_walk_graph[11] = (32)*256 + (7);
	GALEON1_walk_graph[12] = (8)*256 + (31);
	GALEON1_walk_graph[13] = (31)*256 + (48);
	GALEON1_walk_graph[14] = (48)*256 + (29);
	GALEON1_walk_graph[15] = (29)*256 + (8);
	GALEON1_walk_graph[16] = (25)*256 + (35);
	GALEON1_walk_graph[17] = (38)*256 + (41);
	GALEON1_walk_graph[18] = (39)*256 + (42);
	GALEON1_walk_graph[19] = (28)*256 + (33);
	GALEON1_walk_graph[20] = (11)*256 + (12);
	GALEON1_walk_graph[21] = (12)*256 + (13);
	GALEON1_walk_graph[22] = (13)*256 + (26);
	GALEON1_walk_graph[23] = (26)*256 + (16);
	GALEON1_walk_graph[24] = (16)*256 + (15);
	GALEON1_walk_graph[25] = (15)*256 + (14);
	GALEON1_walk_graph[26] = (14)*256 + (13);
	GALEON1_walk_graph[27] = (13)*256 + (15);
	GALEON1_walk_graph[28] = (36)*256 + (26);
	GALEON1_walk_graph[29] = (34)*256 + (24);
	GALEON1_walk_graph[30] = (24)*256 + (6);
	GALEON1_walk_graph[31] = (6)*256 + (27);
	GALEON1_walk_graph[32] = (27)*256 + (47);
	GALEON1_walk_graph[33] = (47)*256 + (33);
	GALEON1_walk_graph[34] = (7)*256 + (6);
	GALEON1_walk_graph[35] = (7)*256 + (8);
	GALEON1_walk_graph[36] = (41)*256 + (44); // mast
	GALEON1_walk_graph[37] = (42)*256 + (45); // mast
	GALEON1_walk_graph[38] = (16)*256 + (17); 
	GALEON1_walk_graph[39] = (17)*256 + (22);
	GALEON1_walk_graph[40] = (22)*256 + (21);
	GALEON1_walk_graph[41] = (21)*256 + (20);
	GALEON1_walk_graph[42] = (20)*256 + (19);
	GALEON1_walk_graph[43] = (19)*256 + (18);
	GALEON1_walk_graph[44] = (18)*256 + (17);
	GALEON1_walk_graph[45] = (18)*256 + (20);
	GALEON1_walk_graph[46] = (24)*256 + (30);
	GALEON1_walk_graph[47] = (30)*256 + (9);
	GALEON1_walk_graph[48] = (9)*256 + (29);
	GALEON1_walk_graph[49] = (6)*256 + (5);
	GALEON1_walk_graph[50] = (9)*256 + (8);
	GALEON1_walk_graph[51] = (9)*256 + (6);
	GALEON1_walk_graph[52] = (5)*256 + (0);
	GALEON1_walk_graph[53] = (0)*256 + (1);
	GALEON1_walk_graph[54] = (1)*256 + (2);
	GALEON1_walk_graph[55] = (2)*256 + (3);
	GALEON1_walk_graph[56] = (3)*256 + (4);
	GALEON1_walk_graph[57] = (4)*256 + (0);
	GALEON1_walk_graph[58] = (2)*256 + (37);
	GALEON1_walk_graph[59] = (37)*256 + (40);
	GALEON1_walk_graph[60] = (40)*256 + (43);
	GALEON1_walk_graph[61] = (25)*256 + (46);
	GALEON1_walk_graph[62] = (25)*256 + (28);
	GALEON1_walk_graph[63] = (23)*256 + (7);
	GALEON1_walk_graph[64] = (7)*256 + (33);
	GALEON1_walk_graph[65] = (16)*256 + (14);
	GALEON1_walk_graph[66] = (31)*256 + (10);
	GALEON1_walk_graph[67] = (30)*256 + (29);
	GALEON1_walk_graph[68] = (27)*256 + (33);
	GALEON1_walk_graph[69] = (10)*256 + (8);
	GALEON1_walk_graph[70] = (31)*256 + (29);
	GALEON1_walk_graph[71] = (-1)*256 + (-1);
	GALEON1_walk_graph[72] = (-1)*256 + (-1);
	GALEON1_walk_graph[73] = (-1)*256 + (-1);
	GALEON1_walk_graph[74] = (-1)*256 + (-1);
	GALEON1_walk_graph[75] = (-1)*256 + (-1);
	GALEON1_walk_graph[76] = (-1)*256 + (-1);
	GALEON1_walk_graph[77] = (-1)*256 + (-1);
	GALEON1_walk_graph[78] = (-1)*256 + (-1);
	GALEON1_walk_graph[79] = (-1)*256 + (-1);
	GALEON1_walk_graph[80] = (-1)*256 + (-1);
	GALEON1_walk_graph[81] = (-1)*256 + (-1);
	GALEON1_walk_graph[82] = (-1)*256 + (-1);
	GALEON1_walk_graph[83] = (-1)*256 + (-1);
	GALEON1_walk_graph[84] = (-1)*256 + (-1);
	GALEON1_walk_graph[85] = (-1)*256 + (-1);
	GALEON1_walk_graph[86] = (-1)*256 + (-1);
	GALEON1_walk_graph[87] = (-1)*256 + (-1);
	GALEON1_walk_graph[88] = (-1)*256 + (-1);
	GALEON1_walk_graph[89] = (-1)*256 + (-1);
	GALEON1_walk_graph[90] = (-1)*256 + (-1);
	GALEON1_walk_graph[91] = (-1)*256 + (-1);
	GALEON1_walk_graph[92] = (-1)*256 + (-1);
	GALEON1_walk_graph[93] = (-1)*256 + (-1);
	GALEON1_walk_graph[94] = (-1)*256 + (-1);
	GALEON1_walk_graph[95] = (-1)*256 + (-1);
	GALEON1_walk_graph[96] = (-1)*256 + (-1);
	GALEON1_walk_graph[97] = (-1)*256 + (-1);
}
