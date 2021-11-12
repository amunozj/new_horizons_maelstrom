int Superbe_walk_count;
float Superbe_walk_verts[156];
int Superbe_walk_types[52];
int Superbe_walk_graph[52];

void Superbe_walk_init()
{
        Superbe_walk_count = 52;

        Superbe_walk_verts[0] = -1.8;
        Superbe_walk_verts[1] = 5.79;
        Superbe_walk_verts[2] = 20.5;
        Superbe_walk_verts[3] = -1.8;
        Superbe_walk_verts[4] = 5.61;
        Superbe_walk_verts[5] = 17;
        Superbe_walk_verts[6] = -1.8;
        Superbe_walk_verts[7] = 5.45;
        Superbe_walk_verts[8] = 13.1;
        Superbe_walk_verts[9] = -3.85;
        Superbe_walk_verts[10] = 5.38;
        Superbe_walk_verts[11] = 11.7;
        Superbe_walk_verts[12] = -3.85;
        Superbe_walk_verts[13] = 5.38;
        Superbe_walk_verts[14] = 0;
        Superbe_walk_verts[15] = 1.5;
        Superbe_walk_verts[16] = 1.05;
        Superbe_walk_verts[17] = -8;
        Superbe_walk_verts[18] = -2;
        Superbe_walk_verts[19] = 5.6;
        Superbe_walk_verts[20] = -7;
        Superbe_walk_verts[21] = -2;
        Superbe_walk_verts[22] = 5.68;
        Superbe_walk_verts[23] = -10.7;
        Superbe_walk_verts[24] = 1.21;
        Superbe_walk_verts[25] = 5.76;
        Superbe_walk_verts[26] = -12.17;
        Superbe_walk_verts[27] = 1.8;
        Superbe_walk_verts[28] = 5.79;
        Superbe_walk_verts[29] = 20.5;
        Superbe_walk_verts[30] = 1.8;
        Superbe_walk_verts[31] = 5.61;
        Superbe_walk_verts[32] = 17;
        Superbe_walk_verts[33] = 1.8;
        Superbe_walk_verts[34] = 5.45;
        Superbe_walk_verts[35] = 13.1;
        Superbe_walk_verts[36] = 3.85;
        Superbe_walk_verts[37] = 5.38;
        Superbe_walk_verts[38] = 11.7;
        Superbe_walk_verts[39] = 3.85;
        Superbe_walk_verts[40] = 5.38;
        Superbe_walk_verts[41] = 0;
        Superbe_walk_verts[42] = 2;
        Superbe_walk_verts[43] = 2.95;
        Superbe_walk_verts[44] = -10;
        Superbe_walk_verts[45] = 2;
        Superbe_walk_verts[46] = 5.6;
        Superbe_walk_verts[47] = -7;
        Superbe_walk_verts[48] = 2;
        Superbe_walk_verts[49] = 5.68;
        Superbe_walk_verts[50] = -10.7;
        Superbe_walk_verts[51] = 0.025;
        Superbe_walk_verts[52] = 6.482;
        Superbe_walk_verts[53] = -12.3;
        Superbe_walk_verts[54] = 0;
        Superbe_walk_verts[55] = 7.7;
        Superbe_walk_verts[56] = -13.5;
        Superbe_walk_verts[57] = 0;
        Superbe_walk_verts[58] = 7.65;
        Superbe_walk_verts[59] = -14.5;
        Superbe_walk_verts[60] = -2.7;
        Superbe_walk_verts[61] = 7.69;
        Superbe_walk_verts[62] = -16;
        Superbe_walk_verts[63] = -2;
        Superbe_walk_verts[64] = 8.22;
        Superbe_walk_verts[65] = -21.9;
        Superbe_walk_verts[66] = 2.7;
        Superbe_walk_verts[67] = 7.69;
        Superbe_walk_verts[68] = -16;
        Superbe_walk_verts[69] = 2;
        Superbe_walk_verts[70] = 8.22;
        Superbe_walk_verts[71] = -21.9;
        Superbe_walk_verts[72] = -5.83;
        Superbe_walk_verts[73] = 5.53;
        Superbe_walk_verts[74] = 12.93;
        Superbe_walk_verts[75] = 5.83;
        Superbe_walk_verts[76] = 5.53;
        Superbe_walk_verts[77] = 12.93;
        Superbe_walk_verts[78] = -0.7;
        Superbe_walk_verts[79] = 24;
        Superbe_walk_verts[80] = 17;
        Superbe_walk_verts[81] = 0.7;
        Superbe_walk_verts[82] = 24;
        Superbe_walk_verts[83] = 17;
        Superbe_walk_verts[84] = -6.2;
        Superbe_walk_verts[85] = 5.3;
        Superbe_walk_verts[86] = -3;
        Superbe_walk_verts[87] = 6.2;
        Superbe_walk_verts[88] = 5.3;
        Superbe_walk_verts[89] = -3;
        Superbe_walk_verts[90] = -0.7;
        Superbe_walk_verts[91] = 27;
        Superbe_walk_verts[92] = -3.5;
        Superbe_walk_verts[93] = 0.7;
        Superbe_walk_verts[94] = 27;
        Superbe_walk_verts[95] = -3.5;
        Superbe_walk_verts[96] = -4.52;
        Superbe_walk_verts[97] = 7.33;
        Superbe_walk_verts[98] = -18.8;
        Superbe_walk_verts[99] = 4.52;
        Superbe_walk_verts[100] = 7.33;
        Superbe_walk_verts[101] = -18.8;
        Superbe_walk_verts[102] = -0.6;
        Superbe_walk_verts[103] = 24;
        Superbe_walk_verts[104] = -18.6;
        Superbe_walk_verts[105] = 0.6;
        Superbe_walk_verts[106] = 24;
        Superbe_walk_verts[107] = -18.6;
        Superbe_walk_verts[108] = -3.2;
        Superbe_walk_verts[109] = 5.65;
        Superbe_walk_verts[110] = 19.2;
        Superbe_walk_verts[111] = -3.35;
        Superbe_walk_verts[112] = 5.55;
        Superbe_walk_verts[113] = 16.8;
        Superbe_walk_verts[114] = -3.35;
        Superbe_walk_verts[115] = 5.39;
        Superbe_walk_verts[116] = 14;
        Superbe_walk_verts[117] = -3.34;
        Superbe_walk_verts[118] = 5.48;
        Superbe_walk_verts[119] = -4.9;
        Superbe_walk_verts[120] = -3.24;
        Superbe_walk_verts[121] = 5.57;
        Superbe_walk_verts[122] = -7.3;
        Superbe_walk_verts[123] = -3.24;
        Superbe_walk_verts[124] = 5.64;
        Superbe_walk_verts[125] = -9.8;
        Superbe_walk_verts[126] = -3.24;
        Superbe_walk_verts[127] = 5.74;
        Superbe_walk_verts[128] = -12.3;
        Superbe_walk_verts[129] = -3.43;
        Superbe_walk_verts[130] = 5.4;
        Superbe_walk_verts[131] = -2.4;
        Superbe_walk_verts[132] = 3.2;
        Superbe_walk_verts[133] = 5.65;
        Superbe_walk_verts[134] = 19.2;
        Superbe_walk_verts[135] = 3.35;
        Superbe_walk_verts[136] = 5.55;
        Superbe_walk_verts[137] = 16.8;
        Superbe_walk_verts[138] = 3.35;
        Superbe_walk_verts[139] = 5.39;
        Superbe_walk_verts[140] = 14;
        Superbe_walk_verts[141] = 3.34;
        Superbe_walk_verts[142] = 5.48;
        Superbe_walk_verts[143] = -4.9;
        Superbe_walk_verts[144] = 3.24;
        Superbe_walk_verts[145] = 5.57;
        Superbe_walk_verts[146] = -7.3;
        Superbe_walk_verts[147] = 3.24;
        Superbe_walk_verts[148] = 5.64;
        Superbe_walk_verts[149] = -9.8;
        Superbe_walk_verts[150] = 3.24;
        Superbe_walk_verts[151] = 5.74;
        Superbe_walk_verts[152] = -12.3;
        Superbe_walk_verts[153] = 3.43;
        Superbe_walk_verts[154] = 5.4;
        Superbe_walk_verts[155] = -2.4;

        Superbe_walk_types[0] = 0;
        Superbe_walk_types[1] = 0;
        Superbe_walk_types[2] = 0;
        Superbe_walk_types[3] = 0;
        Superbe_walk_types[4] = 0;
        Superbe_walk_types[5] = 0;
        Superbe_walk_types[6] = 0;
        Superbe_walk_types[7] = 0;
        Superbe_walk_types[8] = 0;
        Superbe_walk_types[9] = 0;
        Superbe_walk_types[10] = 0;
        Superbe_walk_types[11] = 0;
        Superbe_walk_types[12] = 0;
        Superbe_walk_types[13] = 0;
        Superbe_walk_types[14] = 0;
        Superbe_walk_types[15] = 0;
        Superbe_walk_types[16] = 0;
        Superbe_walk_types[17] = 0;
        Superbe_walk_types[18] = 0;
        Superbe_walk_types[19] = 0;
        Superbe_walk_types[20] = 0;
        Superbe_walk_types[21] = 0;
        Superbe_walk_types[22] = 0;
        Superbe_walk_types[23] = 0;
        Superbe_walk_types[24] = 5;
        Superbe_walk_types[25] = 5;
        Superbe_walk_types[26] = 6;
        Superbe_walk_types[27] = 6;
        Superbe_walk_types[28] = 5;
        Superbe_walk_types[29] = 5;
        Superbe_walk_types[30] = 4;
        Superbe_walk_types[31] = 4;
        Superbe_walk_types[32] = 5;
        Superbe_walk_types[33] = 5;
        Superbe_walk_types[34] = 4;
        Superbe_walk_types[35] = 4;
        Superbe_walk_types[36] = 1;
        Superbe_walk_types[37] = 1;
        Superbe_walk_types[38] = 1;
        Superbe_walk_types[39] = 1;
        Superbe_walk_types[40] = 1;
        Superbe_walk_types[41] = 1;
        Superbe_walk_types[42] = 1;
        Superbe_walk_types[43] = 1;
        Superbe_walk_types[44] = 2;
        Superbe_walk_types[45] = 2;
        Superbe_walk_types[46] = 2;
        Superbe_walk_types[47] = 2;
        Superbe_walk_types[48] = 2;
        Superbe_walk_types[49] = 2;
        Superbe_walk_types[50] = 2;
        Superbe_walk_types[51] = 2;

        Superbe_walk_graph[0] = (0)*256 + (1);
        Superbe_walk_graph[1] = (1)*256 + (2);
        Superbe_walk_graph[2] = (2)*256 + (3);
        Superbe_walk_graph[3] = (3)*256 + (4);
        Superbe_walk_graph[4] = (4)*256 + (5);
        Superbe_walk_graph[5] = (5)*256 + (6);
        Superbe_walk_graph[6] = (6)*256 + (7);
        Superbe_walk_graph[7] = (9)*256 + (10);
        Superbe_walk_graph[8] = (10)*256 + (11);
        Superbe_walk_graph[9] = (11)*256 + (12);
        Superbe_walk_graph[10] = (12)*256 + (13);
        Superbe_walk_graph[11] = (13)*256 + (14);
        Superbe_walk_graph[12] = (14)*256 + (15);
        Superbe_walk_graph[13] = (15)*256 + (16);
        Superbe_walk_graph[14] = (0)*256 + (9);
        Superbe_walk_graph[15] = (7)*256 + (16);
        Superbe_walk_graph[16] = (16)*256 + (8);
        Superbe_walk_graph[17] = (8)*256 + (17);
        Superbe_walk_graph[18] = (17)*256 + (18);
        Superbe_walk_graph[19] = (18)*256 + (19);
        Superbe_walk_graph[20] = (19)*256 + (20);
        Superbe_walk_graph[21] = (20)*256 + (21);
        Superbe_walk_graph[22] = (23)*256 + (22);
        Superbe_walk_graph[23] = (22)*256 + (19);
        Superbe_walk_graph[24] = (3)*256 + (24);
        Superbe_walk_graph[25] = (24)*256 + (26);
        Superbe_walk_graph[26] = (12)*256 + (25);
        Superbe_walk_graph[27] = (25)*256 + (27);
        Superbe_walk_graph[28] = (4)*256 + (28);
        Superbe_walk_graph[29] = (28)*256 + (30);
        Superbe_walk_graph[30] = (13)*256 + (29);
        Superbe_walk_graph[31] = (29)*256 + (31);
        Superbe_walk_graph[32] = (22)*256 + (32);
        Superbe_walk_graph[33] = (32)*256 + (34);
        Superbe_walk_graph[34] = (20)*256 + (33);
        Superbe_walk_graph[35] = (33)*256 + (35);
        Superbe_walk_graph[36] = (0)*256 + (36);
        Superbe_walk_graph[37] = (1)*256 + (37);
        Superbe_walk_graph[38] = (2)*256 + (38);
        Superbe_walk_graph[39] = (5)*256 + (43);
        Superbe_walk_graph[40] = (5)*256 + (39);
        Superbe_walk_graph[41] = (6)*256 + (40);
        Superbe_walk_graph[42] = (7)*256 + (41);
        Superbe_walk_graph[43] = (7)*256 + (42);
        Superbe_walk_graph[44] = (9)*256 + (44);
        Superbe_walk_graph[45] = (10)*256 + (45);
        Superbe_walk_graph[46] = (11)*256 + (46);
        Superbe_walk_graph[47] = (14)*256 + (51);
        Superbe_walk_graph[48] = (14)*256 + (47);
        Superbe_walk_graph[49] = (15)*256 + (48);
        Superbe_walk_graph[50] = (16)*256 + (49);
        Superbe_walk_graph[51] = (16)*256 + (50);
}