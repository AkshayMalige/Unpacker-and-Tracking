#include "SttDetector.h"


detLoc SttDetector::GetDetectorLocFromTDCChannel(int channel) {
	return detMap[channel];
}



//********
//  OLD MAPPING	
/*
SttDetector::SttDetector() {

// TDC E100

// LAYER 1

//fee1
	detMap[1] = detLoc(1, 1, 1, 1);
	detMap[2] = detLoc(1, 1, 1, 2);
	detMap[3] = detLoc(1, 1, 1, 3);
	detMap[4] = detLoc(1, 1, 1, 4);

	detMap[5] = detLoc(1, 1, 1, 5);
	detMap[6] = detLoc(1, 1, 1, 6);
	detMap[7] = detLoc(1, 1, 1, 7);
	detMap[8] = detLoc(1, 1, 1, 8);

	detMap[9] = detLoc(1, 1, 1, 9);
	detMap[10] = detLoc(1, 1, 1, 10);
	detMap[11] = detLoc(1, 1, 1, 11);
	detMap[12] = detLoc(1, 1, 1, 12);


	detMap[13] = detLoc(1, 1, 1, 13);
	detMap[14] = detLoc(1, 1, 1, 14);
	detMap[15] = detLoc(1, 1, 1, 15);
	detMap[16] = detLoc(1, 1, 1, 16);



//fee2
	detMap[17] = detLoc(1, 1, 2, 1);
	detMap[18] = detLoc(1, 1, 2, 2);
	detMap[19] = detLoc(1, 1, 2, 3);
	detMap[20] = detLoc(1, 1, 2, 4);

	detMap[21] = detLoc(1, 1, 2, 5);
	detMap[22] = detLoc(1, 1, 2, 6);
	detMap[23] = detLoc(1, 1, 2, 7);
	detMap[24] = detLoc(1, 1, 2, 8);

	detMap[25] = detLoc(1, 1, 2, 9);
	detMap[26] = detLoc(1, 1, 2, 10);
	detMap[27] = detLoc(1, 1, 2, 11);
	detMap[28] = detLoc(1, 1, 2, 12);

	detMap[29] = detLoc(1, 1, 2, 13);
	detMap[30] = detLoc(1, 1, 2, 14);
	detMap[31] = detLoc(1, 1, 2, 15);
	detMap[32] = detLoc(1, 1, 2, 16);


//fee3
	detMap[33] = detLoc(1, 2, 1, 1);
	detMap[34] = detLoc(1, 2, 1, 2);
	detMap[35] = detLoc(1, 2, 1, 3);
	detMap[36] = detLoc(1, 2, 1, 4);

	detMap[37] = detLoc(1, 2, 1, 5);
	detMap[38] = detLoc(1, 2, 1, 6);
	detMap[39] = detLoc(1, 2, 1, 7);
	detMap[40] = detLoc(1, 2, 1, 8);

	detMap[41] = detLoc(1, 2, 1, 9);
	detMap[42] = detLoc(1, 2, 1, 10);
	detMap[43] = detLoc(1, 2, 1, 11);
	detMap[44] = detLoc(1, 2, 1, 12);

	detMap[45] = detLoc(1, 2, 1, 13);
	detMap[46] = detLoc(1, 2, 1, 14);
	detMap[47] = detLoc(1, 2, 1, 15);
	detMap[48] = detLoc(1, 2, 1, 16);



// TDC E101

//fee4
	detMap[50] = detLoc(1, 2, 2, 1);
	detMap[51] = detLoc(1, 2, 2, 2);
	detMap[52] = detLoc(1, 2, 2, 3);
	detMap[53] = detLoc(1, 2, 2, 4);

	detMap[54] = detLoc(1, 2, 2, 5);
	detMap[55] = detLoc(1, 2, 2, 6);
	detMap[56] = detLoc(1, 2, 2, 7);
	detMap[57] = detLoc(1, 2, 2, 8);

	detMap[58] = detLoc(1, 2, 2, 9);
	detMap[59] = detLoc(1, 2, 2, 10);
	detMap[60] = detLoc(1, 2, 2, 11);
	detMap[61] = detLoc(1, 2, 2, 12);

	detMap[62] = detLoc(1, 2, 2, 13);
	detMap[63] = detLoc(1, 2, 2, 14);
	detMap[64] = detLoc(1, 2, 2, 15);
	detMap[65] = detLoc(1, 2, 2, 16);


// LAYER 2

//fee5
	detMap[66] = detLoc(2, 1, 1, 1);
	detMap[67] = detLoc(2, 1, 1, 2);
	detMap[68] = detLoc(2, 1, 1, 3);
	detMap[69] = detLoc(2, 1, 1, 4);

	detMap[70] = detLoc(2, 1, 1, 5);
	detMap[71] = detLoc(2, 1, 1, 6);
	detMap[72] = detLoc(2, 1, 1, 7);
	detMap[73] = detLoc(2, 1, 1, 8);

	detMap[74] = detLoc(2, 1, 1, 9);
	detMap[75] = detLoc(2, 1, 1, 10);
	detMap[76] = detLoc(2, 1, 1, 11);
	detMap[77] = detLoc(2, 1, 1, 12);

	detMap[78] = detLoc(2, 1, 1, 13);
	detMap[79] = detLoc(2, 1, 1, 14);
	detMap[80] = detLoc(2, 1, 1, 15);
	detMap[81] = detLoc(2, 1, 1, 16);



//fee6
	detMap[82] = detLoc(2, 1, 2, 1);
	detMap[83] = detLoc(2, 1, 2, 2);
	detMap[84] = detLoc(2, 1, 2, 3);
	detMap[85] = detLoc(2, 1, 2, 4);

	detMap[86] = detLoc(2, 1, 2, 5);
	detMap[87] = detLoc(2, 1, 2, 6);
	detMap[88] = detLoc(2, 1, 2, 7);
	detMap[89] = detLoc(2, 1, 2, 8);

	detMap[90] = detLoc(2, 1, 2, 9);
	detMap[91] = detLoc(2, 1, 2, 10);
	detMap[92] = detLoc(2, 1, 2, 11);
	detMap[93] = detLoc(2, 1, 2, 12);

	detMap[94] = detLoc(2, 1, 2, 13);
	detMap[95] = detLoc(2, 1, 2, 14);
	detMap[96] = detLoc(2, 1, 2, 15);
	detMap[97] = detLoc(2, 1, 2, 16);


// TDC E102

//fee7
	detMap[115] = detLoc(2, 2, 1, 1);
	detMap[116] = detLoc(2, 2, 1, 2);
	detMap[117] = detLoc(2, 2, 1, 3);
	detMap[118] = detLoc(2, 2, 1, 4);

	detMap[119] = detLoc(2, 2, 1, 5);
	detMap[120] = detLoc(2, 2, 1, 6);
	detMap[121] = detLoc(2, 2, 1, 7);
	detMap[122] = detLoc(2, 2, 1, 8);

	detMap[123] = detLoc(2, 2, 1, 9);
	detMap[124] = detLoc(2, 2, 1, 10);
	detMap[125] = detLoc(2, 2, 1, 11);
	detMap[126] = detLoc(2, 2, 1, 12);

	detMap[127] = detLoc(2, 2, 1, 13);
	detMap[128] = detLoc(2, 2, 1, 14);
	detMap[129] = detLoc(2, 2, 1, 15);
	detMap[130] = detLoc(2, 2, 1, 16);




//fee8
	detMap[131] = detLoc(2, 2, 2, 1);
	detMap[132] = detLoc(2, 2, 2, 2);
	detMap[133] = detLoc(2, 2, 2, 3);
	detMap[134] = detLoc(2, 2, 2, 4);

	detMap[135] = detLoc(2, 2, 2, 5);
	detMap[136] = detLoc(2, 2, 2, 6);
	detMap[137] = detLoc(2, 2, 2, 7);
	detMap[138] = detLoc(2, 2, 2, 8);

	detMap[139] = detLoc(2, 2, 2, 9);
	detMap[140] = detLoc(2, 2, 2, 10);
	detMap[141] = detLoc(2, 2, 2, 11);
	detMap[142] = detLoc(2, 2, 2, 12);

	detMap[143] = detLoc(2, 2, 2, 13);
	detMap[144] = detLoc(2, 2, 2, 14);
	detMap[145] = detLoc(2, 2, 2, 15);
	detMap[146] = detLoc(2, 2, 2, 16);



///////////////////////////////////////////////////////////////////////////////////////////////////////

// TDC E200

// LAYER 3

//fee9
	detMap[148] = detLoc(3, 1, 1, 1);
	detMap[149] = detLoc(3, 1, 1, 2);
	detMap[150] = detLoc(3, 1, 1, 3);
	detMap[151] = detLoc(3, 1, 1, 4);

	detMap[152] = detLoc(3, 1, 1, 5);
	detMap[153] = detLoc(3, 1, 1, 6);
	detMap[154] = detLoc(3, 1, 1, 7);
	detMap[155] = detLoc(3, 1, 1, 8);

	detMap[156] = detLoc(3, 1, 1, 9);
	detMap[157] = detLoc(3, 1, 1, 10);
	detMap[158] = detLoc(3, 1, 1, 11);
	detMap[159] = detLoc(3, 1, 1, 12);

	detMap[160] = detLoc(3, 1, 1, 13);
	detMap[161] = detLoc(3, 1, 1, 14);
	detMap[162] = detLoc(3, 1, 1, 15);
	detMap[163] = detLoc(3, 1, 1, 16);



//fee10
	detMap[164] = detLoc(3, 1, 2, 1);
	detMap[165] = detLoc(3, 1, 2, 2);
	detMap[166] = detLoc(3, 1, 2, 3);
	detMap[167] = detLoc(3, 1, 2, 4);

	detMap[168] = detLoc(3, 1, 2, 5);
	detMap[169] = detLoc(3, 1, 2, 6);
	detMap[170] = detLoc(3, 1, 2, 7);
	detMap[171] = detLoc(3, 1, 2, 8);

	detMap[172] = detLoc(3, 1, 2, 9);
	detMap[173] = detLoc(3, 1, 2, 10);
	detMap[174] = detLoc(3, 1, 2, 11);
	detMap[175] = detLoc(3, 1, 2, 12);

	detMap[176] = detLoc(3, 1, 2, 13);
	detMap[177] = detLoc(3, 1, 2, 14);
	detMap[178] = detLoc(3, 1, 2, 15);
	detMap[179] = detLoc(3, 1, 2, 16);


//fee11
	detMap[180] = detLoc(3, 2, 1, 1);
	detMap[181] = detLoc(3, 2, 1, 2);
	detMap[182] = detLoc(3, 2, 1, 3);
	detMap[183] = detLoc(3, 2, 1, 4);

	detMap[184] = detLoc(3, 2, 1, 5);
	detMap[185] = detLoc(3, 2, 1, 6);
	detMap[186] = detLoc(3, 2, 1, 7);
	detMap[187] = detLoc(3, 2, 1, 8);

	detMap[188] = detLoc(3, 2, 1, 9);
	detMap[189] = detLoc(3, 2, 1, 10);
	detMap[190] = detLoc(3, 2, 1, 11);
	detMap[191] = detLoc(3, 2, 1, 12);

	detMap[192] = detLoc(3, 2, 1, 13);
	detMap[193] = detLoc(3, 2, 1, 14);
	detMap[194] = detLoc(3, 2, 1, 15);
	detMap[195] = detLoc(3, 2, 1, 16);



// TDC E201

//fee12


	detMap[197] = detLoc(3, 2, 2, 1);
	detMap[198] = detLoc(3, 2, 2, 2);
	detMap[199] = detLoc(3, 2, 2, 3);
	detMap[200] = detLoc(3, 2, 2, 4);

	detMap[201] = detLoc(3, 2, 2, 5);
	detMap[202] = detLoc(3, 2, 2, 6);
	detMap[203] = detLoc(3, 2, 2, 7);
	detMap[204] = detLoc(3, 2, 2, 8);

	detMap[205] = detLoc(3, 2, 2, 9);
	detMap[206] = detLoc(3, 2, 2, 10);
	detMap[207] = detLoc(3, 2, 2, 11);
	detMap[208] = detLoc(3, 2, 2, 12);

	detMap[209] = detLoc(3, 2, 2, 13);
	detMap[210] = detLoc(3, 2, 2, 14);
	detMap[211] = detLoc(3, 2, 2, 15);
	detMap[212] = detLoc(3, 2, 2, 16);


// LAYER 4

//fee13

	detMap[213] = detLoc(4, 1, 1, 1);
	detMap[214] = detLoc(4, 1, 1, 2);
	detMap[215] = detLoc(4, 1, 1, 3);
	detMap[216] = detLoc(4, 1, 1, 4);

	detMap[217] = detLoc(4, 1, 1, 5);
	detMap[218] = detLoc(4, 1, 1, 6);
	detMap[219] = detLoc(4, 1, 1, 7);
	detMap[220] = detLoc(4, 1, 1, 8);

	detMap[221] = detLoc(4, 1, 1, 9);
	detMap[222] = detLoc(4, 1, 1, 10);
	detMap[223] = detLoc(4, 1, 1, 11);
	detMap[224] = detLoc(4, 1, 1, 12);

	detMap[225] = detLoc(4, 1, 1, 13);
	detMap[226] = detLoc(4, 1, 1, 14);
	detMap[227] = detLoc(4, 1, 1, 15);
	detMap[228] = detLoc(4, 1, 1, 16);


//fee14


	detMap[229] = detLoc(4, 1, 2, 1);
	detMap[230] = detLoc(4, 1, 2, 2);
	detMap[231] = detLoc(4, 1, 2, 3);
	detMap[232] = detLoc(4, 1, 2, 4);

	detMap[233] = detLoc(4, 1, 2, 5);
	detMap[234] = detLoc(4, 1, 2, 6);
	detMap[235] = detLoc(4, 1, 2, 7);
	detMap[236] = detLoc(4, 1, 2, 8);

	detMap[237] = detLoc(4, 1, 2, 9);
	detMap[238] = detLoc(4, 1, 2, 10);
	detMap[239] = detLoc(4, 1, 2, 11);
	detMap[240] = detLoc(4, 1, 2, 12);

	detMap[241] = detLoc(4, 1, 2, 13);
	detMap[242] = detLoc(4, 1, 2, 14);
	detMap[243] = detLoc(4, 1, 2, 15);
	detMap[244] = detLoc(4, 1, 2, 16);


// TDC E202

//fee15

	detMap[246] = detLoc(4, 2, 1, 1);
	detMap[247] = detLoc(4, 2, 1, 2);
	detMap[248] = detLoc(4, 2, 1, 3);
	detMap[249] = detLoc(4, 2, 1, 4);

	detMap[250] = detLoc(4, 2, 1, 5);
	detMap[251] = detLoc(4, 2, 1, 6);
	detMap[252] = detLoc(4, 2, 1, 7);
	detMap[253] = detLoc(4, 2, 1, 8);

	detMap[254] = detLoc(4, 2, 1, 9);
	detMap[255] = detLoc(4, 2, 1, 10);
	detMap[256] = detLoc(4, 2, 1, 11);
	detMap[257] = detLoc(4, 2, 1, 12);

	detMap[258] = detLoc(4, 2, 1, 13);
	detMap[259] = detLoc(4, 2, 1, 14);
	detMap[260] = detLoc(4, 2, 1, 15);
	detMap[261] = detLoc(4, 2, 1, 16);


//fee16


	detMap[262] = detLoc(4, 2, 2, 1);
	detMap[263] = detLoc(4, 2, 2, 2);
	detMap[264] = detLoc(4, 2, 2, 3);
	detMap[265] = detLoc(4, 2, 2, 4);

	detMap[266] = detLoc(4, 2, 2, 5);
	detMap[267] = detLoc(4, 2, 2, 6);
	detMap[268] = detLoc(4, 2, 2, 7);
	detMap[269] = detLoc(4, 2, 2, 8);

	detMap[270] = detLoc(4, 2, 2, 9);
	detMap[271] = detLoc(4, 2, 2, 10);
	detMap[272] = detLoc(4, 2, 2, 11);
	detMap[273] = detLoc(4, 2, 2, 12);

	detMap[274] = detLoc(4, 2, 2, 13);
	detMap[275] = detLoc(4, 2, 2, 14);
	detMap[276] = detLoc(4, 2, 2, 15);
	detMap[277] = detLoc(4, 2, 2, 16);
}*/

//**********
//    NEW MAPPING


SttDetector::SttDetector() {

// TDC E100

// LAYER 1

//fee1
	detMap[1] = detLoc(1, 1, 1, 1);
	detMap[2] = detLoc(1, 1, 1, 2);
	detMap[3] = detLoc(1, 1, 1, 3);
	detMap[4] = detLoc(1, 1, 1, 4);

	detMap[5] = detLoc(1, 1, 1, 5);
	detMap[6] = detLoc(1, 1, 1, 6);
	detMap[7] = detLoc(1, 1, 1, 7);
	detMap[8] = detLoc(1, 1, 1, 8);

	detMap[9] = detLoc(1, 1, 1, 9);
	detMap[10] = detLoc(1, 1, 1, 10);
	detMap[11] = detLoc(1, 1, 1, 11);
	detMap[12] = detLoc(1, 1, 1, 12);


	detMap[13] = detLoc(1, 1, 1, 13);
	detMap[14] = detLoc(1, 1, 1, 14);
	detMap[15] = detLoc(1, 1, 1, 15);
	detMap[16] = detLoc(1, 1, 1, 16);



//fee2
	detMap[17] = detLoc(1, 1, 2, 1);
	detMap[18] = detLoc(1, 1, 2, 2);
	detMap[19] = detLoc(1, 1, 2, 3);
	detMap[20] = detLoc(1, 1, 2, 4);

	detMap[21] = detLoc(1, 1, 2, 5);
	detMap[22] = detLoc(1, 1, 2, 6);
	detMap[23] = detLoc(1, 1, 2, 7);
	detMap[24] = detLoc(1, 1, 2, 8);

	detMap[25] = detLoc(1, 1, 2, 9);
	detMap[26] = detLoc(1, 1, 2, 10);
	detMap[27] = detLoc(1, 1, 2, 11);
	detMap[28] = detLoc(1, 1, 2, 12);

	detMap[29] = detLoc(1, 1, 2, 13);
	detMap[30] = detLoc(1, 1, 2, 14);
	detMap[31] = detLoc(1, 1, 2, 15);
	detMap[32] = detLoc(1, 1, 2, 16);


//fee3
	detMap[33] = detLoc(1, 2, 1, 1);
	detMap[34] = detLoc(1, 2, 1, 2);
	detMap[35] = detLoc(1, 2, 1, 3);
	detMap[36] = detLoc(1, 2, 1, 4);

	detMap[37] = detLoc(1, 2, 1, 5);
	detMap[38] = detLoc(1, 2, 1, 6);
	detMap[39] = detLoc(1, 2, 1, 7);
	detMap[40] = detLoc(1, 2, 1, 8);

	detMap[41] = detLoc(1, 2, 1, 9);
	detMap[42] = detLoc(1, 2, 1, 10);
	detMap[43] = detLoc(1, 2, 1, 11);
	detMap[44] = detLoc(1, 2, 1, 12);

	detMap[45] = detLoc(1, 2, 1, 13);
	detMap[46] = detLoc(1, 2, 1, 14);
	detMap[47] = detLoc(1, 2, 1, 15);
	detMap[48] = detLoc(1, 2, 1, 16);



// TDC E101

//fee4
	detMap[50] = detLoc(1, 2, 2, 1);
	detMap[51] = detLoc(1, 2, 2, 2);
	detMap[52] = detLoc(1, 2, 2, 3);
	detMap[53] = detLoc(1, 2, 2, 4);

	detMap[54] = detLoc(1, 2, 2, 5);
	detMap[55] = detLoc(1, 2, 2, 6);
	detMap[56] = detLoc(1, 2, 2, 7);
	detMap[57] = detLoc(1, 2, 2, 8);

	detMap[58] = detLoc(1, 2, 2, 9);
	detMap[59] = detLoc(1, 2, 2, 10);
	detMap[60] = detLoc(1, 2, 2, 11);
	detMap[61] = detLoc(1, 2, 2, 12);

	detMap[62] = detLoc(1, 2, 2, 13);
	detMap[63] = detLoc(1, 2, 2, 14);
	detMap[64] = detLoc(1, 2, 2, 15);
	detMap[65] = detLoc(1, 2, 2, 16);


// LAYER 2

//fee5
	detMap[66] = detLoc(2, 1, 1, 1);
	detMap[67] = detLoc(2, 1, 1, 2);
	detMap[68] = detLoc(2, 1, 1, 3);
	detMap[69] = detLoc(2, 1, 1, 4);

	detMap[70] = detLoc(2, 1, 1, 5);
	detMap[71] = detLoc(2, 1, 1, 6);
	detMap[72] = detLoc(2, 1, 1, 7);
	detMap[73] = detLoc(2, 1, 1, 8);

	detMap[74] = detLoc(2, 1, 1, 9);
	detMap[75] = detLoc(2, 1, 1, 10);
	detMap[76] = detLoc(2, 1, 1, 11);
	detMap[77] = detLoc(2, 1, 1, 12);

	detMap[78] = detLoc(2, 1, 1, 13);
	detMap[79] = detLoc(2, 1, 1, 14);
	detMap[80] = detLoc(2, 1, 1, 15);
	detMap[81] = detLoc(2, 1, 1, 16);



//fee6
	detMap[82] = detLoc(2, 1, 2, 1);
	detMap[83] = detLoc(2, 1, 2, 2);
	detMap[84] = detLoc(2, 1, 2, 3);
	detMap[85] = detLoc(2, 1, 2, 4);

	detMap[86] = detLoc(2, 1, 2, 5);
	detMap[87] = detLoc(2, 1, 2, 6);
	detMap[88] = detLoc(2, 1, 2, 7);
	detMap[89] = detLoc(2, 1, 2, 8);

	detMap[90] = detLoc(2, 1, 2, 9);
	detMap[91] = detLoc(2, 1, 2, 10);
	detMap[92] = detLoc(2, 1, 2, 11);
	detMap[93] = detLoc(2, 1, 2, 12);

	detMap[94] = detLoc(2, 1, 2, 13);
	detMap[95] = detLoc(2, 1, 2, 14);
	detMap[96] = detLoc(2, 1, 2, 15);
	detMap[97] = detLoc(2, 1, 2, 16);


// TDC E102

//fee7




//fee8
	detMap[115] = detLoc(2, 2, 2, 1);
	detMap[116] = detLoc(2, 2, 2, 2);
	detMap[117] = detLoc(2, 2, 2, 3);
	detMap[118] = detLoc(2, 2, 2, 4);

	detMap[119] = detLoc(2, 2, 2, 5);
	detMap[120] = detLoc(2, 2, 2, 6);
	detMap[121] = detLoc(2, 2, 2, 7);
	detMap[122] = detLoc(2, 2, 2, 8);

	detMap[123] = detLoc(2, 2, 2, 9);
	detMap[124] = detLoc(2, 2, 2, 10);
	detMap[125] = detLoc(2, 2, 2, 11);
	detMap[126] = detLoc(2, 2, 2, 12);

	detMap[127] = detLoc(2, 2, 2, 13);
	detMap[128] = detLoc(2, 2, 2, 14);
	detMap[129] = detLoc(2, 2, 2, 15);
	detMap[130] = detLoc(2, 2, 2, 16);



///////////////////////////////////////////////////////////////////////////////////////////////////////

// TDC E200

// LAYER 3

//fee9
	detMap[148] = detLoc(3, 1, 1, 1);
	detMap[149] = detLoc(3, 1, 1, 2);
	detMap[150] = detLoc(3, 1, 1, 3);
	detMap[151] = detLoc(3, 1, 1, 4);

	detMap[152] = detLoc(3, 1, 1, 5);
	detMap[153] = detLoc(3, 1, 1, 6);
	detMap[154] = detLoc(3, 1, 1, 7);
	detMap[155] = detLoc(3, 1, 1, 8);

	detMap[156] = detLoc(3, 1, 1, 9);
	detMap[157] = detLoc(3, 1, 1, 10);
	detMap[158] = detLoc(3, 1, 1, 11);
	detMap[159] = detLoc(3, 1, 1, 12);

	detMap[160] = detLoc(3, 1, 1, 13);
	detMap[161] = detLoc(3, 1, 1, 14);
	detMap[162] = detLoc(3, 1, 1, 15);
	detMap[163] = detLoc(3, 1, 1, 16);



//fee10
	detMap[164] = detLoc(3, 1, 2, 1);
	detMap[165] = detLoc(3, 1, 2, 2);
	detMap[166] = detLoc(3, 1, 2, 3);
	detMap[167] = detLoc(3, 1, 2, 4);

	detMap[168] = detLoc(3, 1, 2, 5);
	detMap[169] = detLoc(3, 1, 2, 6);
	detMap[170] = detLoc(3, 1, 2, 7);
	detMap[171] = detLoc(3, 1, 2, 8);

	detMap[172] = detLoc(3, 1, 2, 9);
	detMap[173] = detLoc(3, 1, 2, 10);
	detMap[174] = detLoc(3, 1, 2, 11);
	detMap[175] = detLoc(3, 1, 2, 12);

	detMap[176] = detLoc(3, 1, 2, 13);
	detMap[177] = detLoc(3, 1, 2, 14);
	detMap[178] = detLoc(3, 1, 2, 15);
	detMap[179] = detLoc(3, 1, 2, 16);


//fee11
	detMap[180] = detLoc(3, 2, 1, 1);
	detMap[181] = detLoc(3, 2, 1, 2);
	detMap[182] = detLoc(3, 2, 1, 3);
	detMap[183] = detLoc(3, 2, 1, 4);

	detMap[184] = detLoc(3, 2, 1, 5);
	detMap[185] = detLoc(3, 2, 1, 6);
	detMap[186] = detLoc(3, 2, 1, 7);
	detMap[187] = detLoc(3, 2, 1, 8);

	detMap[188] = detLoc(3, 2, 1, 9);
	detMap[189] = detLoc(3, 2, 1, 10);
	detMap[190] = detLoc(3, 2, 1, 11);
	detMap[191] = detLoc(3, 2, 1, 12);

	detMap[192] = detLoc(3, 2, 1, 13);
	detMap[193] = detLoc(3, 2, 1, 14);
	detMap[194] = detLoc(3, 2, 1, 15);
	detMap[195] = detLoc(3, 2, 1, 16);



// TDC E201

//fee12


	detMap[197] = detLoc(3, 2, 2, 1);
	detMap[198] = detLoc(3, 2, 2, 2);
	detMap[199] = detLoc(3, 2, 2, 3);
	detMap[200] = detLoc(3, 2, 2, 4);

	detMap[201] = detLoc(3, 2, 2, 5);
	detMap[202] = detLoc(3, 2, 2, 6);
	detMap[203] = detLoc(3, 2, 2, 7);
	detMap[204] = detLoc(3, 2, 2, 8);

	detMap[205] = detLoc(3, 2, 2, 9);
	detMap[206] = detLoc(3, 2, 2, 10);
	detMap[207] = detLoc(3, 2, 2, 11);
	detMap[208] = detLoc(3, 2, 2, 12);

	detMap[209] = detLoc(3, 2, 2, 13);
	detMap[210] = detLoc(3, 2, 2, 14);
	detMap[211] = detLoc(3, 2, 2, 15);
	detMap[212] = detLoc(3, 2, 2, 16);


// LAYER 4

//fee13

	detMap[213] = detLoc(4, 1, 1, 1);
	detMap[214] = detLoc(4, 1, 1, 2);
	detMap[215] = detLoc(4, 1, 1, 3);
	detMap[216] = detLoc(4, 1, 1, 4);

	detMap[217] = detLoc(4, 1, 1, 5);
	detMap[218] = detLoc(4, 1, 1, 6);
	detMap[219] = detLoc(4, 1, 1, 7);
	detMap[220] = detLoc(4, 1, 1, 8);

	detMap[221] = detLoc(4, 1, 1, 9);
	detMap[222] = detLoc(4, 1, 1, 10);
	detMap[223] = detLoc(4, 1, 1, 11);
	detMap[224] = detLoc(4, 1, 1, 12);

	detMap[225] = detLoc(4, 1, 1, 13);
	detMap[226] = detLoc(4, 1, 1, 14);
	detMap[227] = detLoc(4, 1, 1, 15);
	detMap[228] = detLoc(4, 1, 1, 16);


//fee14


	detMap[229] = detLoc(4, 1, 2, 1);
	detMap[230] = detLoc(4, 1, 2, 2);
	detMap[231] = detLoc(4, 1, 2, 3);
	detMap[232] = detLoc(4, 1, 2, 4);

	detMap[233] = detLoc(4, 1, 2, 5);
	detMap[234] = detLoc(4, 1, 2, 6);
	detMap[235] = detLoc(4, 1, 2, 7);
	detMap[236] = detLoc(4, 1, 2, 8);

	detMap[237] = detLoc(4, 1, 2, 9);
	detMap[238] = detLoc(4, 1, 2, 10);
	detMap[239] = detLoc(4, 1, 2, 11);
	detMap[240] = detLoc(4, 1, 2, 12);

	detMap[241] = detLoc(4, 1, 2, 13);
	detMap[242] = detLoc(4, 1, 2, 14);
	detMap[243] = detLoc(4, 1, 2, 15);
	detMap[244] = detLoc(4, 1, 2, 16);


// TDC E202

//fee15

	detMap[246] = detLoc(4, 2, 1, 1);
	detMap[247] = detLoc(4, 2, 1, 2);
	detMap[248] = detLoc(4, 2, 1, 3);
	detMap[249] = detLoc(4, 2, 1, 4);

	detMap[250] = detLoc(4, 2, 1, 5);
	detMap[251] = detLoc(4, 2, 1, 6);
	detMap[252] = detLoc(4, 2, 1, 7);
	detMap[253] = detLoc(4, 2, 1, 8);

	detMap[254] = detLoc(4, 2, 1, 9);
	detMap[255] = detLoc(4, 2, 1, 10);
	detMap[256] = detLoc(4, 2, 1, 11);
	detMap[257] = detLoc(4, 2, 1, 12);

	detMap[258] = detLoc(4, 2, 1, 13);
	detMap[259] = detLoc(4, 2, 1, 14);
	detMap[260] = detLoc(4, 2, 1, 15);
	detMap[261] = detLoc(4, 2, 1, 16);


//fee16


	detMap[262] = detLoc(4, 2, 2, 1);
	detMap[263] = detLoc(4, 2, 2, 2);
	detMap[264] = detLoc(4, 2, 2, 3);
	detMap[265] = detLoc(4, 2, 2, 4);

	detMap[266] = detLoc(4, 2, 2, 5);
	detMap[267] = detLoc(4, 2, 2, 6);
	detMap[268] = detLoc(4, 2, 2, 7);
	detMap[269] = detLoc(4, 2, 2, 8);

	detMap[270] = detLoc(4, 2, 2, 9);
	detMap[271] = detLoc(4, 2, 2, 10);
	detMap[272] = detLoc(4, 2, 2, 11);
	detMap[273] = detLoc(4, 2, 2, 12);

	detMap[274] = detLoc(4, 2, 2, 13);
	detMap[275] = detLoc(4, 2, 2, 14);
	detMap[276] = detLoc(4, 2, 2, 15);
	detMap[277] = detLoc(4, 2, 2, 16);

//fee7

	detMap[278] = detLoc(2, 2, 1, 1);
	detMap[279] = detLoc(2, 2, 1, 2);
	detMap[280] = detLoc(2, 2, 1, 3);
	detMap[281] = detLoc(2, 2, 1, 4);

	detMap[282] = detLoc(2, 2, 1, 5);
	detMap[283] = detLoc(2, 2, 1, 6);
	detMap[284] = detLoc(2, 2, 1, 7);
	detMap[285] = detLoc(2, 2, 1, 8);

	detMap[286] = detLoc(2, 2, 1, 9);
	detMap[287] = detLoc(2, 2, 1, 10);
	detMap[288] = detLoc(2, 2, 1, 11);
	detMap[289] = detLoc(2, 2, 1, 12);

	detMap[290] = detLoc(2, 2, 1, 13);
	detMap[291] = detLoc(2, 2, 1, 14);
	detMap[292] = detLoc(2, 2, 1, 15);
	detMap[293] = detLoc(2, 2, 1, 16);


}
