int Volage_walk_count;
float Volage_walk_verts[228];
int Volage_walk_types[76];
int Volage_walk_graph[80];

void Volage_walk_init()
{
        Volage_walk_count = 76;

        Volage_walk_verts[0] = -0.02954;
        Volage_walk_verts[1] = 1.577424;
        Volage_walk_verts[2] = 10.818424;
        Volage_walk_verts[3] = 2.057585;
        Volage_walk_verts[4] = 1.58242;
        Volage_walk_verts[5] = 10.849753;
        Volage_walk_verts[6] = 0.867318;
        Volage_walk_verts[7] = 1.459947;
        Volage_walk_verts[8] = 8.151301;
        Volage_walk_verts[9] = 2.245208;
        Volage_walk_verts[10] = 1.494934;
        Volage_walk_verts[11] = 8.158548;
        Volage_walk_verts[12] = 1.424921;
        Volage_walk_verts[13] = 1.514918;
        Volage_walk_verts[14] = 5.550172;
        Volage_walk_verts[15] = 2.317883;
        Volage_walk_verts[16] = 1.494922;
        Volage_walk_verts[17] = 5.499753;
        Volage_walk_verts[18] = 1.40444;
        Volage_walk_verts[19] = 1.409973;
        Volage_walk_verts[20] = 2.936951;
        Volage_walk_verts[21] = 2.293655;
        Volage_walk_verts[22] = 1.369989;
        Volage_walk_verts[23] = 2.927774;
        Volage_walk_verts[24] = 1.392051;
        Volage_walk_verts[25] = 1.389996;
        Volage_walk_verts[26] = 0.305472;
        Volage_walk_verts[27] = 2.294246;
        Volage_walk_verts[28] = 1.387498;
        Volage_walk_verts[29] = 0.299836;
        Volage_walk_verts[30] = 1.353168;
        Volage_walk_verts[31] = 1.425001;
        Volage_walk_verts[32] = -2.366596;
        Volage_walk_verts[33] = 2.260137;
        Volage_walk_verts[34] = 1.427503;
        Volage_walk_verts[35] = -2.329343;
        Volage_walk_verts[36] = 1.325508;
        Volage_walk_verts[37] = 1.417506;
        Volage_walk_verts[38] = -4.905575;
        Volage_walk_verts[39] = 2.121823;
        Volage_walk_verts[40] = 1.495005;
        Volage_walk_verts[41] = -4.907144;
        Volage_walk_verts[42] = 0.1938;
        Volage_walk_verts[43] = 1.552505;
        Volage_walk_verts[44] = -7.583149;
        Volage_walk_verts[45] = 1.913189;
        Volage_walk_verts[46] = 1.652464;
        Volage_walk_verts[47] = -7.522829;
        Volage_walk_verts[48] = 0.060596;
        Volage_walk_verts[49] = 1.669941;
        Volage_walk_verts[50] = -10.145123;
        Volage_walk_verts[51] = 1.727858;
        Volage_walk_verts[52] = 1.684957;
        Volage_walk_verts[53] = -10.200073;
        Volage_walk_verts[54] = 0.700896;
        Volage_walk_verts[55] = 1.769998;
        Volage_walk_verts[56] = -10.931342;
        Volage_walk_verts[57] = 0.635242;
        Volage_walk_verts[58] = 1.894994;
        Volage_walk_verts[59] = -12.465153;
        Volage_walk_verts[60] = -0.048504;
        Volage_walk_verts[61] = 1.904996;
        Volage_walk_verts[62] = -13.059261;
        Volage_walk_verts[63] = 0.013718;
        Volage_walk_verts[64] = 3.727499;
        Volage_walk_verts[65] = -14.513887;
        Volage_walk_verts[66] = 2.25975;
        Volage_walk_verts[67] = 3.507504;
        Volage_walk_verts[68] = -12.136464;
        Volage_walk_verts[69] = 2.027557;
        Volage_walk_verts[70] = 3.627482;
        Volage_walk_verts[71] = -14.556194;
        Volage_walk_verts[72] = 1.569759;
        Volage_walk_verts[73] = 3.887475;
        Volage_walk_verts[74] = -17.474867;
        Volage_walk_verts[75] = -1.618023;
        Volage_walk_verts[76] = 3.809975;
        Volage_walk_verts[77] = -17.457273;
        Volage_walk_verts[78] = -2.283101;
        Volage_walk_verts[79] = 3.662493;
        Volage_walk_verts[80] = -14.67003;
        Volage_walk_verts[81] = -2.506191;
        Volage_walk_verts[82] = 3.532482;
        Volage_walk_verts[83] = -11.948545;
        Volage_walk_verts[84] = -1.777888;
        Volage_walk_verts[85] = 1.60746;
        Volage_walk_verts[86] = -7.581429;
        Volage_walk_verts[87] = -1.207816;
        Volage_walk_verts[88] = 1.45496;
        Volage_walk_verts[89] = -4.937025;
        Volage_walk_verts[90] = -2.117339;
        Volage_walk_verts[91] = 1.46246;
        Volage_walk_verts[92] = -4.933743;
        Volage_walk_verts[93] = -1.165732;
        Volage_walk_verts[94] = 1.304961;
        Volage_walk_verts[95] = -2.371018;
        Volage_walk_verts[96] = -2.144156;
        Volage_walk_verts[97] = 1.299959;
        Volage_walk_verts[98] = -2.40151;
        Volage_walk_verts[99] = -1.332168;
        Volage_walk_verts[100] = 1.307462;
        Volage_walk_verts[101] = 0.278969;
        Volage_walk_verts[102] = -2.363816;
        Volage_walk_verts[103] = 1.152459;
        Volage_walk_verts[104] = 0.256438;
        Volage_walk_verts[105] = -1.317386;
        Volage_walk_verts[106] = 1.29246;
        Volage_walk_verts[107] = 2.95114;
        Volage_walk_verts[108] = -2.327635;
        Volage_walk_verts[109] = 1.337458;
        Volage_walk_verts[110] = 2.943489;
        Volage_walk_verts[111] = -1.362538;
        Volage_walk_verts[112] = 1.294951;
        Volage_walk_verts[113] = 5.491929;
        Volage_walk_verts[114] = -2.323299;
        Volage_walk_verts[115] = 1.352448;
        Volage_walk_verts[116] = 5.504895;
        Volage_walk_verts[117] = -1.321583;
        Volage_walk_verts[118] = 1.334911;
        Volage_walk_verts[119] = 8.163626;
        Volage_walk_verts[120] = -2.327609;
        Volage_walk_verts[121] = 1.294908;
        Volage_walk_verts[122] = 8.190598;
        Volage_walk_verts[123] = -2.194189;
        Volage_walk_verts[124] = 1.469906;
        Volage_walk_verts[125] = 10.775055;
        Volage_walk_verts[126] = -3.465902;
        Volage_walk_verts[127] = 1.574906;
        Volage_walk_verts[128] = 11.982761;
        Volage_walk_verts[129] = -3.369658;
        Volage_walk_verts[130] = 3.117407;
        Volage_walk_verts[131] = 12.181541;
        Volage_walk_verts[132] = -2.788497;
        Volage_walk_verts[133] = 3.164909;
        Volage_walk_verts[134] = 14.759641;
        Volage_walk_verts[135] = -2.168491;
        Volage_walk_verts[136] = 3.284907;
        Volage_walk_verts[137] = 16.529066;
        Volage_walk_verts[138] = 0.134642;
        Volage_walk_verts[139] = 3.442408;
        Volage_walk_verts[140] = 17.795156;
        Volage_walk_verts[141] = 2.550151;
        Volage_walk_verts[142] = 3.26241;
        Volage_walk_verts[143] = 16.483585;
        Volage_walk_verts[144] = 2.838438;
        Volage_walk_verts[145] = 3.247409;
        Volage_walk_verts[146] = 14.744894;
        Volage_walk_verts[147] = 3.32212;
        Volage_walk_verts[148] = 3.149915;
        Volage_walk_verts[149] = 12.186987;
        Volage_walk_verts[150] = 3.397234;
        Volage_walk_verts[151] = 1.602446;
        Volage_walk_verts[152] = 11.922031;
        Volage_walk_verts[153] = 4.325031;
        Volage_walk_verts[154] = 3.10744;
        Volage_walk_verts[155] = 14.136931;
        Volage_walk_verts[156] = 0.341668;
        Volage_walk_verts[157] = 14.544795;
        Volage_walk_verts[158] = 13.917225;
        Volage_walk_verts[159] = 1.769473;
        Volage_walk_verts[160] = 14.492265;
        Volage_walk_verts[161] = 13.907582;
        Volage_walk_verts[162] = 0.304711;
        Volage_walk_verts[163] = 24.204411;
        Volage_walk_verts[164] = 14.163988;
        Volage_walk_verts[165] = 4.674273;
        Volage_walk_verts[166] = 2.892424;
        Volage_walk_verts[167] = -0.927807;
        Volage_walk_verts[168] = 0.413964;
        Volage_walk_verts[169] = 15.339706;
        Volage_walk_verts[170] = -0.747036;
        Volage_walk_verts[171] = 1.857916;
        Volage_walk_verts[172] = 15.34971;
        Volage_walk_verts[173] = -0.742232;
        Volage_walk_verts[174] = 0.264187;
        Volage_walk_verts[175] = 26.484327;
        Volage_walk_verts[176] = -0.706515;
        Volage_walk_verts[177] = 3.890547;
        Volage_walk_verts[178] = 3.377414;
        Volage_walk_verts[179] = -11.502397;
        Volage_walk_verts[180] = 0.285554;
        Volage_walk_verts[181] = 14.254958;
        Volage_walk_verts[182] = -11.674095;
        Volage_walk_verts[183] = 1.366587;
        Volage_walk_verts[184] = 14.334921;
        Volage_walk_verts[185] = -11.794085;
        Volage_walk_verts[186] = 0.274737;
        Volage_walk_verts[187] = 22.110281;
        Volage_walk_verts[188] = -11.964493;
        Volage_walk_verts[189] = -3.925544;
        Volage_walk_verts[190] = 3.352414;
        Volage_walk_verts[191] = -11.482952;
        Volage_walk_verts[192] = -0.265592;
        Volage_walk_verts[193] = 14.269753;
        Volage_walk_verts[194] = -11.689504;
        Volage_walk_verts[195] = -1.41071;
        Volage_walk_verts[196] = 14.339763;
        Volage_walk_verts[197] = -11.914489;
        Volage_walk_verts[198] = -0.250252;
        Volage_walk_verts[199] = 22.111946;
        Volage_walk_verts[200] = -12.017236;
        Volage_walk_verts[201] = -4.693917;
        Volage_walk_verts[202] = 2.929919;
        Volage_walk_verts[203] = -0.874804;
        Volage_walk_verts[204] = -0.210114;
        Volage_walk_verts[205] = 15.304762;
        Volage_walk_verts[206] = -0.696181;
        Volage_walk_verts[207] = -1.876591;
        Volage_walk_verts[208] = 15.307266;
        Volage_walk_verts[209] = -0.74838;
        Volage_walk_verts[210] = -0.080634;
        Volage_walk_verts[211] = 26.469349;
        Volage_walk_verts[212] = -0.696335;
        Volage_walk_verts[213] = -4.214262;
        Volage_walk_verts[214] = 3.134915;
        Volage_walk_verts[215] = 14.246792;
        Volage_walk_verts[216] = -0.328362;
        Volage_walk_verts[217] = 14.497295;
        Volage_walk_verts[218] = 13.866365;
        Volage_walk_verts[219] = -1.602334;
        Volage_walk_verts[220] = 14.549791;
        Volage_walk_verts[221] = 13.938282;
        Volage_walk_verts[222] = -0.339509;
        Volage_walk_verts[223] = 24.247404;
        Volage_walk_verts[224] = 14.148499;
        Volage_walk_verts[225] = -1.724549;
        Volage_walk_verts[226] = 1.562547;
        Volage_walk_verts[227] = -10.16127;

        Volage_walk_types[0] = 0;
        Volage_walk_types[1] = 2;
        Volage_walk_types[2] = 0;
        Volage_walk_types[3] = 2;
        Volage_walk_types[4] = 0;
        Volage_walk_types[5] = 2;
        Volage_walk_types[6] = 0;
        Volage_walk_types[7] = 2;
        Volage_walk_types[8] = 0;
        Volage_walk_types[9] = 2;
        Volage_walk_types[10] = 0;
        Volage_walk_types[11] = 2;
        Volage_walk_types[12] = 0;
        Volage_walk_types[13] = 2;
        Volage_walk_types[14] = 0;
        Volage_walk_types[15] = 2;
        Volage_walk_types[16] = 0;
        Volage_walk_types[17] = 2;
        Volage_walk_types[18] = 0;
        Volage_walk_types[19] = 0;
        Volage_walk_types[20] = 0;
        Volage_walk_types[21] = 0;
        Volage_walk_types[22] = 0;
        Volage_walk_types[23] = 0;
        Volage_walk_types[24] = 0;
        Volage_walk_types[25] = 0;
        Volage_walk_types[26] = 0;
        Volage_walk_types[27] = 0;
        Volage_walk_types[28] = 1;
        Volage_walk_types[29] = 0;
        Volage_walk_types[30] = 1;
        Volage_walk_types[31] = 0;
        Volage_walk_types[32] = 1;
        Volage_walk_types[33] = 0;
        Volage_walk_types[34] = 1;
        Volage_walk_types[35] = 0;
        Volage_walk_types[36] = 1;
        Volage_walk_types[37] = 0;
        Volage_walk_types[38] = 1;
        Volage_walk_types[39] = 0;
        Volage_walk_types[40] = 1;
        Volage_walk_types[41] = 1;
        Volage_walk_types[42] = 0;
        Volage_walk_types[43] = 0;
        Volage_walk_types[44] = 0;
        Volage_walk_types[45] = 0;
        Volage_walk_types[46] = 0;
        Volage_walk_types[47] = 0;
        Volage_walk_types[48] = 0;
        Volage_walk_types[49] = 0;
        Volage_walk_types[50] = 0;
        Volage_walk_types[51] = 5;
        Volage_walk_types[52] = 6;
        Volage_walk_types[53] = 5;
        Volage_walk_types[54] = 6;
        Volage_walk_types[55] = 5;
        Volage_walk_types[56] = 4;
        Volage_walk_types[57] = 5;
        Volage_walk_types[58] = 4;
        Volage_walk_types[59] = 5;
        Volage_walk_types[60] = 4;
        Volage_walk_types[61] = 5;
        Volage_walk_types[62] = 4;
        Volage_walk_types[63] = 5;
        Volage_walk_types[64] = 4;
        Volage_walk_types[65] = 5;
        Volage_walk_types[66] = 4;
        Volage_walk_types[67] = 5;
        Volage_walk_types[68] = 4;
        Volage_walk_types[69] = 5;
        Volage_walk_types[70] = 4;
        Volage_walk_types[71] = 5;
        Volage_walk_types[72] = 6;
        Volage_walk_types[73] = 5;
        Volage_walk_types[74] = 6;
        Volage_walk_types[75] = 1;

        Volage_walk_graph[0] = (1)*256 + (0);
        Volage_walk_graph[1] = (2)*256 + (0);
        Volage_walk_graph[2] = (2)*256 + (3);
        Volage_walk_graph[3] = (2)*256 + (4);
        Volage_walk_graph[4] = (5)*256 + (4);
        Volage_walk_graph[5] = (6)*256 + (4);
        Volage_walk_graph[6] = (6)*256 + (7);
        Volage_walk_graph[7] = (6)*256 + (8);
        Volage_walk_graph[8] = (9)*256 + (8);
        Volage_walk_graph[9] = (10)*256 + (8);
        Volage_walk_graph[10] = (10)*256 + (11);
        Volage_walk_graph[11] = (10)*256 + (12);
        Volage_walk_graph[12] = (13)*256 + (12);
        Volage_walk_graph[13] = (14)*256 + (12);
        Volage_walk_graph[14] = (14)*256 + (15);
        Volage_walk_graph[15] = (14)*256 + (16);
        Volage_walk_graph[16] = (17)*256 + (16);
        Volage_walk_graph[17] = (18)*256 + (16);
        Volage_walk_graph[18] = (18)*256 + (19);
        Volage_walk_graph[19] = (20)*256 + (19);
        Volage_walk_graph[20] = (20)*256 + (21);
        Volage_walk_graph[21] = (21)*256 + (23);
        Volage_walk_graph[22] = (22)*256 + (23);
        Volage_walk_graph[23] = (24)*256 + (23);
        Volage_walk_graph[24] = (24)*256 + (25);
        Volage_walk_graph[25] = (25)*256 + (26);
        Volage_walk_graph[26] = (27)*256 + (26);
        Volage_walk_graph[27] = (27)*256 + (21);
        Volage_walk_graph[28] = (14)*256 + (28);
        Volage_walk_graph[29] = (14)*256 + (29);
        Volage_walk_graph[30] = (30)*256 + (29);
        Volage_walk_graph[31] = (31)*256 + (29);
        Volage_walk_graph[32] = (31)*256 + (32);
        Volage_walk_graph[33] = (31)*256 + (33);
        Volage_walk_graph[34] = (34)*256 + (33);
        Volage_walk_graph[35] = (35)*256 + (33);
        Volage_walk_graph[36] = (35)*256 + (36);
        Volage_walk_graph[37] = (35)*256 + (37);
        Volage_walk_graph[38] = (38)*256 + (37);
        Volage_walk_graph[39] = (39)*256 + (37);
        Volage_walk_graph[40] = (39)*256 + (40);
        Volage_walk_graph[41] = (0)*256 + (39);
        Volage_walk_graph[42] = (42)*256 + (41);
        Volage_walk_graph[43] = (0)*256 + (39);
        Volage_walk_graph[44] = (0)*256 + (41);
        Volage_walk_graph[45] = (42)*256 + (43);
        Volage_walk_graph[46] = (43)*256 + (44);
        Volage_walk_graph[47] = (44)*256 + (45);
        Volage_walk_graph[48] = (45)*256 + (46);
        Volage_walk_graph[49] = (46)*256 + (47);
        Volage_walk_graph[50] = (47)*256 + (48);
        Volage_walk_graph[51] = (48)*256 + (49);
        Volage_walk_graph[52] = (49)*256 + (50);
        Volage_walk_graph[53] = (48)*256 + (51);
        Volage_walk_graph[54] = (48)*256 + (51);
        Volage_walk_graph[55] = (0)*256 + (50);
        Volage_walk_graph[56] = (51)*256 + (52);
        Volage_walk_graph[57] = (52)*256 + (53);
        Volage_walk_graph[58] = (53)*256 + (54);
        Volage_walk_graph[59] = (56)*256 + (55);
        Volage_walk_graph[60] = (57)*256 + (56);
        Volage_walk_graph[61] = (57)*256 + (58);
        Volage_walk_graph[62] = (60)*256 + (59);
        Volage_walk_graph[63] = (60)*256 + (61);
        Volage_walk_graph[64] = (61)*256 + (62);
        Volage_walk_graph[65] = (63)*256 + (64);
        Volage_walk_graph[66] = (65)*256 + (64);
        Volage_walk_graph[67] = (65)*256 + (66);
        Volage_walk_graph[68] = (68)*256 + (67);
        Volage_walk_graph[69] = (68)*256 + (69);
        Volage_walk_graph[70] = (70)*256 + (69);
        Volage_walk_graph[71] = (72)*256 + (71);
        Volage_walk_graph[72] = (72)*256 + (73);
        Volage_walk_graph[73] = (74)*256 + (73);
        Volage_walk_graph[74] = (8)*256 + (55);
        Volage_walk_graph[75] = (22)*256 + (59);
        Volage_walk_graph[76] = (27)*256 + (63);
        Volage_walk_graph[77] = (31)*256 + (67);
        Volage_walk_graph[78] = (44)*256 + (71);
        Volage_walk_graph[79] = (75)*256 + (16);
}
