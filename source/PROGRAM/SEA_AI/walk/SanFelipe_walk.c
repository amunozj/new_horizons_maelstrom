int SanFelipe_walk_count;
float SanFelipe_walk_verts[225];
int SanFelipe_walk_types[75];
int SanFelipe_walk_graph[81];

void SanFelipe_walk_init()
{
        SanFelipe_walk_count = 75;

        SanFelipe_walk_verts[0] = -2.5;
        SanFelipe_walk_verts[1] = 5.2;
        SanFelipe_walk_verts[2] = 12.4;
        SanFelipe_walk_verts[3] = -2.5;
        SanFelipe_walk_verts[4] = 5.11;
        SanFelipe_walk_verts[5] = 7.1;
        SanFelipe_walk_verts[6] = -2.5;
        SanFelipe_walk_verts[7] = 5.05;
        SanFelipe_walk_verts[8] = 2.2;
        SanFelipe_walk_verts[9] = 2.5;
        SanFelipe_walk_verts[10] = 5.2;
        SanFelipe_walk_verts[11] = 12.4;
        SanFelipe_walk_verts[12] = 2.5;
        SanFelipe_walk_verts[13] = 5.11;
        SanFelipe_walk_verts[14] = 7.1;
        SanFelipe_walk_verts[15] = 2.5;
        SanFelipe_walk_verts[16] = 5.05;
        SanFelipe_walk_verts[17] = 2.2;
        SanFelipe_walk_verts[18] = -3.52;
        SanFelipe_walk_verts[19] = 5.03;
        SanFelipe_walk_verts[20] = -1.1;
        SanFelipe_walk_verts[21] = -4.49;
        SanFelipe_walk_verts[22] = 6.07;
        SanFelipe_walk_verts[23] = -1.35;
        SanFelipe_walk_verts[24] = -4.58;
        SanFelipe_walk_verts[25] = 6.82;
        SanFelipe_walk_verts[26] = -2;
        SanFelipe_walk_verts[27] = -4.58;
        SanFelipe_walk_verts[28] = 6.87;
        SanFelipe_walk_verts[29] = -5.5;
        SanFelipe_walk_verts[30] = -2.5;
        SanFelipe_walk_verts[31] = 7;
        SanFelipe_walk_verts[32] = -8;
        SanFelipe_walk_verts[33] = -2.5;
        SanFelipe_walk_verts[34] = 7.17;
        SanFelipe_walk_verts[35] = -12.8;
        SanFelipe_walk_verts[36] = -2.6;
        SanFelipe_walk_verts[37] = 7.27;
        SanFelipe_walk_verts[38] = -15.6;
        SanFelipe_walk_verts[39] = 3.52;
        SanFelipe_walk_verts[40] = 5.03;
        SanFelipe_walk_verts[41] = -1.1;
        SanFelipe_walk_verts[42] = 4.49;
        SanFelipe_walk_verts[43] = 6.07;
        SanFelipe_walk_verts[44] = -1.35;
        SanFelipe_walk_verts[45] = 4.58;
        SanFelipe_walk_verts[46] = 6.82;
        SanFelipe_walk_verts[47] = -2;
        SanFelipe_walk_verts[48] = 4.58;
        SanFelipe_walk_verts[49] = 6.87;
        SanFelipe_walk_verts[50] = -5.5;
        SanFelipe_walk_verts[51] = 2.5;
        SanFelipe_walk_verts[52] = 7;
        SanFelipe_walk_verts[53] = -8;
        SanFelipe_walk_verts[54] = 2.5;
        SanFelipe_walk_verts[55] = 7.17;
        SanFelipe_walk_verts[56] = -12.8;
        SanFelipe_walk_verts[57] = 2.6;
        SanFelipe_walk_verts[58] = 7.27;
        SanFelipe_walk_verts[59] = -15.6;
        SanFelipe_walk_verts[60] = -3.52;
        SanFelipe_walk_verts[61] = 8.09;
        SanFelipe_walk_verts[62] = -15.73;
        SanFelipe_walk_verts[63] = -3.61;
        SanFelipe_walk_verts[64] = 8.91;
        SanFelipe_walk_verts[65] = -16.5;
        SanFelipe_walk_verts[66] = -3.3;
        SanFelipe_walk_verts[67] = 8.99;
        SanFelipe_walk_verts[68] = -21;
        SanFelipe_walk_verts[69] = 3.52;
        SanFelipe_walk_verts[70] = 8.09;
        SanFelipe_walk_verts[71] = -15.73;
        SanFelipe_walk_verts[72] = 3.61;
        SanFelipe_walk_verts[73] = 8.91;
        SanFelipe_walk_verts[74] = -16.5;
        SanFelipe_walk_verts[75] = 3.3;
        SanFelipe_walk_verts[76] = 8.99;
        SanFelipe_walk_verts[77] = -21;
        SanFelipe_walk_verts[78] = -3.25;
        SanFelipe_walk_verts[79] = 5.05;
        SanFelipe_walk_verts[80] = -7.1;
        SanFelipe_walk_verts[81] = 3.25;
        SanFelipe_walk_verts[82] = 5.05;
        SanFelipe_walk_verts[83] = -7.1;
        SanFelipe_walk_verts[84] = 0;
        SanFelipe_walk_verts[85] = 5.79;
        SanFelipe_walk_verts[86] = -28.9;
        SanFelipe_walk_verts[87] = -3.55;
        SanFelipe_walk_verts[88] = 5.18;
        SanFelipe_walk_verts[89] = 14.9;
        SanFelipe_walk_verts[90] = -4.42;
        SanFelipe_walk_verts[91] = 5.97;
        SanFelipe_walk_verts[92] = 15.05;
        SanFelipe_walk_verts[93] = -4.65;
        SanFelipe_walk_verts[94] = 6.88;
        SanFelipe_walk_verts[95] = 15.7;
        SanFelipe_walk_verts[96] = -4.53;
        SanFelipe_walk_verts[97] = 6.9;
        SanFelipe_walk_verts[98] = 17.16;
        SanFelipe_walk_verts[99] = -2.4;
        SanFelipe_walk_verts[100] = 6.95;
        SanFelipe_walk_verts[101] = 18.3;
        SanFelipe_walk_verts[102] = -2.4;
        SanFelipe_walk_verts[103] = 6.95;
        SanFelipe_walk_verts[104] = 23;
        SanFelipe_walk_verts[105] = 3.55;
        SanFelipe_walk_verts[106] = 5.18;
        SanFelipe_walk_verts[107] = 14.9;
        SanFelipe_walk_verts[108] = 4.42;
        SanFelipe_walk_verts[109] = 5.97;
        SanFelipe_walk_verts[110] = 15.05;
        SanFelipe_walk_verts[111] = 4.65;
        SanFelipe_walk_verts[112] = 6.88;
        SanFelipe_walk_verts[113] = 15.7;
        SanFelipe_walk_verts[114] = 4.53;
        SanFelipe_walk_verts[115] = 6.9;
        SanFelipe_walk_verts[116] = 17.16;
        SanFelipe_walk_verts[117] = 2.4;
        SanFelipe_walk_verts[118] = 6.95;
        SanFelipe_walk_verts[119] = 18.3;
        SanFelipe_walk_verts[120] = 2.4;
        SanFelipe_walk_verts[121] = 6.95;
        SanFelipe_walk_verts[122] = 23;
        SanFelipe_walk_verts[123] = -6.22;
        SanFelipe_walk_verts[124] = 6.91;
        SanFelipe_walk_verts[125] = 17.8;
        SanFelipe_walk_verts[126] = -0.65;
        SanFelipe_walk_verts[127] = 21.7;
        SanFelipe_walk_verts[128] = 20.6;
        SanFelipe_walk_verts[129] = 6.22;
        SanFelipe_walk_verts[130] = 6.91;
        SanFelipe_walk_verts[131] = 17.8;
        SanFelipe_walk_verts[132] = 0.65;
        SanFelipe_walk_verts[133] = 21.7;
        SanFelipe_walk_verts[134] = 20.6;
        SanFelipe_walk_verts[135] = -6.8;
        SanFelipe_walk_verts[136] = 6.84;
        SanFelipe_walk_verts[137] = -5.05;
        SanFelipe_walk_verts[138] = -0.65;
        SanFelipe_walk_verts[139] = 23.5;
        SanFelipe_walk_verts[140] = -1.43;
        SanFelipe_walk_verts[141] = 6.8;
        SanFelipe_walk_verts[142] = 6.84;
        SanFelipe_walk_verts[143] = -5.05;
        SanFelipe_walk_verts[144] = 0.65;
        SanFelipe_walk_verts[145] = 23.5;
        SanFelipe_walk_verts[146] = -1.43;
        SanFelipe_walk_verts[147] = -5.73;
        SanFelipe_walk_verts[148] = 8.99;
        SanFelipe_walk_verts[149] = -20.26;
        SanFelipe_walk_verts[150] = -0.45;
        SanFelipe_walk_verts[151] = 21.8;
        SanFelipe_walk_verts[152] = -17;
        SanFelipe_walk_verts[153] = 5.73;
        SanFelipe_walk_verts[154] = 8.99;
        SanFelipe_walk_verts[155] = -20.26;
        SanFelipe_walk_verts[156] = 0.45;
        SanFelipe_walk_verts[157] = 21.8;
        SanFelipe_walk_verts[158] = -17;
        SanFelipe_walk_verts[159] = -3;
        SanFelipe_walk_verts[160] = 9.02;
        SanFelipe_walk_verts[161] = -21.7;
        SanFelipe_walk_verts[162] = 3;
        SanFelipe_walk_verts[163] = 9.02;
        SanFelipe_walk_verts[164] = -21.7;
        SanFelipe_walk_verts[165] = -3.2;
        SanFelipe_walk_verts[166] = 7.2;
        SanFelipe_walk_verts[167] = -13.5;
        SanFelipe_walk_verts[168] = -3.2;
        SanFelipe_walk_verts[169] = 7.15;
        SanFelipe_walk_verts[170] = -11.85;
        SanFelipe_walk_verts[171] = -3.5;
        SanFelipe_walk_verts[172] = 6.99;
        SanFelipe_walk_verts[173] = -8.8;
        SanFelipe_walk_verts[174] = 3.2;
        SanFelipe_walk_verts[175] = 7.2;
        SanFelipe_walk_verts[176] = -13.5;
        SanFelipe_walk_verts[177] = 3.2;
        SanFelipe_walk_verts[178] = 7.15;
        SanFelipe_walk_verts[179] = -11.85;
        SanFelipe_walk_verts[180] = 3.5;
        SanFelipe_walk_verts[181] = 6.99;
        SanFelipe_walk_verts[182] = -8.8;
        SanFelipe_walk_verts[183] = -4;
        SanFelipe_walk_verts[184] = 4.97;
        SanFelipe_walk_verts[185] = 1.3;
        SanFelipe_walk_verts[186] = -4;
        SanFelipe_walk_verts[187] = 5.02;
        SanFelipe_walk_verts[188] = 3;
        SanFelipe_walk_verts[189] = -4;
        SanFelipe_walk_verts[190] = 5.08;
        SanFelipe_walk_verts[191] = 8;
        SanFelipe_walk_verts[192] = -4;
        SanFelipe_walk_verts[193] = 5.1;
        SanFelipe_walk_verts[194] = 9.5;
        SanFelipe_walk_verts[195] = -4;
        SanFelipe_walk_verts[196] = 5.1;
        SanFelipe_walk_verts[197] = 12.7;
        SanFelipe_walk_verts[198] = 4;
        SanFelipe_walk_verts[199] = 4.97;
        SanFelipe_walk_verts[200] = 1.3;
        SanFelipe_walk_verts[201] = 4;
        SanFelipe_walk_verts[202] = 5.02;
        SanFelipe_walk_verts[203] = 3;
        SanFelipe_walk_verts[204] = 4;
        SanFelipe_walk_verts[205] = 5.08;
        SanFelipe_walk_verts[206] = 8;
        SanFelipe_walk_verts[207] = 4;
        SanFelipe_walk_verts[208] = 5.1;
        SanFelipe_walk_verts[209] = 9.5;
        SanFelipe_walk_verts[210] = 4;
        SanFelipe_walk_verts[211] = 5.1;
        SanFelipe_walk_verts[212] = 12.7;
        SanFelipe_walk_verts[213] = -3.7;
        SanFelipe_walk_verts[214] = 6.94;
        SanFelipe_walk_verts[215] = 19.2;
        SanFelipe_walk_verts[216] = -3.7;
        SanFelipe_walk_verts[217] = 6.91;
        SanFelipe_walk_verts[218] = 20.35;
        SanFelipe_walk_verts[219] = 3.7;
        SanFelipe_walk_verts[220] = 6.94;
        SanFelipe_walk_verts[221] = 19.2;
        SanFelipe_walk_verts[222] = 3.7;
        SanFelipe_walk_verts[223] = 6.91;
        SanFelipe_walk_verts[224] = 20.35;

        SanFelipe_walk_types[0] = 0;
        SanFelipe_walk_types[1] = 0;
        SanFelipe_walk_types[2] = 0;
        SanFelipe_walk_types[3] = 0;
        SanFelipe_walk_types[4] = 0;
        SanFelipe_walk_types[5] = 0;
        SanFelipe_walk_types[6] = 0;
        SanFelipe_walk_types[7] = 0;
        SanFelipe_walk_types[8] = 0;
        SanFelipe_walk_types[9] = 0;
        SanFelipe_walk_types[10] = 0;
        SanFelipe_walk_types[11] = 0;
        SanFelipe_walk_types[12] = 0;
        SanFelipe_walk_types[13] = 0;
        SanFelipe_walk_types[14] = 0;
        SanFelipe_walk_types[15] = 0;
        SanFelipe_walk_types[16] = 0;
        SanFelipe_walk_types[17] = 0;
        SanFelipe_walk_types[18] = 0;
        SanFelipe_walk_types[19] = 0;
        SanFelipe_walk_types[20] = 0;
        SanFelipe_walk_types[21] = 0;
        SanFelipe_walk_types[22] = 0;
        SanFelipe_walk_types[23] = 0;
        SanFelipe_walk_types[24] = 0;
        SanFelipe_walk_types[25] = 0;
        SanFelipe_walk_types[26] = 0;
        SanFelipe_walk_types[27] = 0;
        SanFelipe_walk_types[28] = 0;
        SanFelipe_walk_types[29] = 0;
        SanFelipe_walk_types[30] = 0;
        SanFelipe_walk_types[31] = 0;
        SanFelipe_walk_types[32] = 0;
        SanFelipe_walk_types[33] = 0;
        SanFelipe_walk_types[34] = 0;
        SanFelipe_walk_types[35] = 0;
        SanFelipe_walk_types[36] = 0;
        SanFelipe_walk_types[37] = 0;
        SanFelipe_walk_types[38] = 0;
        SanFelipe_walk_types[39] = 0;
        SanFelipe_walk_types[40] = 0;
        SanFelipe_walk_types[41] = 5;
        SanFelipe_walk_types[42] = 6;
        SanFelipe_walk_types[43] = 5;
        SanFelipe_walk_types[44] = 6;
        SanFelipe_walk_types[45] = 5;
        SanFelipe_walk_types[46] = 4;
        SanFelipe_walk_types[47] = 5;
        SanFelipe_walk_types[48] = 4;
        SanFelipe_walk_types[49] = 5;
        SanFelipe_walk_types[50] = 4;
        SanFelipe_walk_types[51] = 5;
        SanFelipe_walk_types[52] = 4;
        SanFelipe_walk_types[53] = 1;
        SanFelipe_walk_types[54] = 2;
        SanFelipe_walk_types[55] = 1;
        SanFelipe_walk_types[56] = 1;
        SanFelipe_walk_types[57] = 1;
        SanFelipe_walk_types[58] = 2;
        SanFelipe_walk_types[59] = 2;
        SanFelipe_walk_types[60] = 2;
        SanFelipe_walk_types[61] = 1;
        SanFelipe_walk_types[62] = 1;
        SanFelipe_walk_types[63] = 1;
        SanFelipe_walk_types[64] = 1;
        SanFelipe_walk_types[65] = 1;
        SanFelipe_walk_types[66] = 2;
        SanFelipe_walk_types[67] = 2;
        SanFelipe_walk_types[68] = 2;
        SanFelipe_walk_types[69] = 2;
        SanFelipe_walk_types[70] = 2;
        SanFelipe_walk_types[71] = 1;
        SanFelipe_walk_types[72] = 1;
        SanFelipe_walk_types[73] = 2;
        SanFelipe_walk_types[74] = 2;

        SanFelipe_walk_graph[0] = (0)*256 + (1);
        SanFelipe_walk_graph[1] = (1)*256 + (2);
        SanFelipe_walk_graph[2] = (3)*256 + (4);
        SanFelipe_walk_graph[3] = (4)*256 + (5);
        SanFelipe_walk_graph[4] = (0)*256 + (3);
        SanFelipe_walk_graph[5] = (2)*256 + (5);
        SanFelipe_walk_graph[6] = (2)*256 + (6);
        SanFelipe_walk_graph[7] = (6)*256 + (7);
        SanFelipe_walk_graph[8] = (7)*256 + (8);
        SanFelipe_walk_graph[9] = (8)*256 + (9);
        SanFelipe_walk_graph[10] = (9)*256 + (10);
        SanFelipe_walk_graph[11] = (10)*256 + (11);
        SanFelipe_walk_graph[12] = (11)*256 + (12);
        SanFelipe_walk_graph[13] = (5)*256 + (13);
        SanFelipe_walk_graph[14] = (13)*256 + (14);
        SanFelipe_walk_graph[15] = (14)*256 + (15);
        SanFelipe_walk_graph[16] = (15)*256 + (16);
        SanFelipe_walk_graph[17] = (16)*256 + (17);
        SanFelipe_walk_graph[18] = (17)*256 + (18);
        SanFelipe_walk_graph[19] = (18)*256 + (19);
        SanFelipe_walk_graph[20] = (9)*256 + (16);
        SanFelipe_walk_graph[21] = (12)*256 + (19);
        SanFelipe_walk_graph[22] = (10)*256 + (17);
        SanFelipe_walk_graph[23] = (12)*256 + (20);
        SanFelipe_walk_graph[24] = (20)*256 + (21);
        SanFelipe_walk_graph[25] = (21)*256 + (22);
        SanFelipe_walk_graph[26] = (19)*256 + (23);
        SanFelipe_walk_graph[27] = (23)*256 + (24);
        SanFelipe_walk_graph[28] = (24)*256 + (25);
        SanFelipe_walk_graph[29] = (22)*256 + (25);
        SanFelipe_walk_graph[30] = (12)*256 + (26);
        SanFelipe_walk_graph[31] = (26)*256 + (28);
        SanFelipe_walk_graph[32] = (28)*256 + (27);
        SanFelipe_walk_graph[33] = (27)*256 + (19);
        SanFelipe_walk_graph[34] = (0)*256 + (29);
        SanFelipe_walk_graph[35] = (29)*256 + (30);
        SanFelipe_walk_graph[36] = (30)*256 + (31);
        SanFelipe_walk_graph[37] = (31)*256 + (32);
        SanFelipe_walk_graph[38] = (33)*256 + (34);
        SanFelipe_walk_graph[39] = (3)*256 + (35);
        SanFelipe_walk_graph[40] = (35)*256 + (36);
        SanFelipe_walk_graph[41] = (36)*256 + (37);
        SanFelipe_walk_graph[42] = (37)*256 + (38);
        SanFelipe_walk_graph[43] = (38)*256 + (39);
        SanFelipe_walk_graph[44] = (39)*256 + (40);
        SanFelipe_walk_graph[45] = (33)*256 + (39);
        SanFelipe_walk_graph[46] = (34)*256 + (40);
        SanFelipe_walk_graph[47] = (32)*256 + (41);
        SanFelipe_walk_graph[48] = (41)*256 + (42);
        SanFelipe_walk_graph[49] = (38)*256 + (43);
        SanFelipe_walk_graph[50] = (43)*256 + (44);
        SanFelipe_walk_graph[51] = (9)*256 + (45);
        SanFelipe_walk_graph[52] = (45)*256 + (46);
        SanFelipe_walk_graph[53] = (16)*256 + (47);
        SanFelipe_walk_graph[54] = (47)*256 + (48);
        SanFelipe_walk_graph[55] = (22)*256 + (49);
        SanFelipe_walk_graph[56] = (49)*256 + (50);
        SanFelipe_walk_graph[57] = (25)*256 + (51);
        SanFelipe_walk_graph[58] = (51)*256 + (52);
        SanFelipe_walk_graph[59] = (22)*256 + (53);
        SanFelipe_walk_graph[60] = (25)*256 + (54);
        SanFelipe_walk_graph[61] = (11)*256 + (55);
        SanFelipe_walk_graph[62] = (11)*256 + (56);
        SanFelipe_walk_graph[63] = (10)*256 + (57);
        SanFelipe_walk_graph[64] = (18)*256 + (58);
        SanFelipe_walk_graph[65] = (18)*256 + (59);
        SanFelipe_walk_graph[66] = (17)*256 + (60);
        SanFelipe_walk_graph[67] = (2)*256 + (61);
        SanFelipe_walk_graph[68] = (2)*256 + (62);
        SanFelipe_walk_graph[69] = (1)*256 + (63);
        SanFelipe_walk_graph[70] = (1)*256 + (64);
        SanFelipe_walk_graph[71] = (0)*256 + (65);
        SanFelipe_walk_graph[72] = (5)*256 + (66);
        SanFelipe_walk_graph[73] = (5)*256 + (67);
        SanFelipe_walk_graph[74] = (4)*256 + (68);
        SanFelipe_walk_graph[75] = (4)*256 + (69);
        SanFelipe_walk_graph[76] = (3)*256 + (70);
        SanFelipe_walk_graph[77] = (33)*256 + (71);
        SanFelipe_walk_graph[78] = (33)*256 + (72);
        SanFelipe_walk_graph[79] = (39)*256 + (73);
        SanFelipe_walk_graph[80] = (39)*256 + (74);
}