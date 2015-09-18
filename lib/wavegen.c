/* QB-50 picoSatellite TT&C subsystem
 * by BG2BHC & Mr.logic
 *
 * wavegen.c:part of DSP system
 *
 * Version control:
 * 2013-10-11:File Created.
 */

#include "wavegen.h"



const int16_t sinetable[] =
{
	0X0,	0XB8,	0X170,	0X228,	0X2E0,	0X398,	0X450,	0X508,	0X5C0,	0X677,	0X72F,	0X7E7,	0X89E,
	0X956,	0XA0D,	0XAC5,	0XB7C,	0XC33,	0XCEA,	0XDA1,	0XE58,	0XF0E,	0XFC5,	0X107B,	0X1131,
	0X11E7,	0X129D,	0X1353,	0X1408,	0X14BE,	0X1573,	0X1628,	0X16DC,	0X1791,	0X1845,	0X18F9,	0X19AD,
	0X1A60,	0X1B13,	0X1BC6,	0X1C79,	0X1D2B,	0X1DDD,	0X1E8F,	0X1F41,	0X1FF2,	0X20A3,	0X2154,	0X2204,
	0X22B4,	0X2364,	0X2413,	0X24C2,	0X2571,	0X261F,	0X26CD,	0X277A,	0X2827,	0X28D4,	0X2980,	0X2A2C,
	0X2AD8,	0X2B83,	0X2C2E,	0X2CD8,	0X2D82,	0X2E2B,	0X2ED4,	0X2F7D,	0X3025,	0X30CC,	0X3174,	0X321A,
	0X32C0,	0X3366,	0X340B,	0X34B0,	0X3554,	0X35F8,	0X369B,	0X373D,	0X37DF,	0X3881,	0X3922,	0X39C2,
	0X3A62,	0X3B02,	0X3BA0,	0X3C3F,	0X3CDC,	0X3D79,	0X3E16,	0X3EB1,	0X3F4D,	0X3FE7,	0X4081,	0X411B,
	0X41B3,	0X424B,	0X42E3,	0X437A,	0X4410,	0X44A5,	0X453A,	0X45CE,	0X4662,	0X46F5,	0X4787,	0X4818,
	0X48A9,	0X4939,	0X49C9,	0X4A57,	0X4AE5,	0X4B72,	0X4BFF,	0X4C8B,	0X4D16,	0X4DA0,	0X4E29,	0X4EB2,
	0X4F3A,	0X4FC2,	0X5048,	0X50CE,	0X5153,	0X51D7,	0X525A,	0X52DD,	0X535E,	0X53DF,	0X5460,	0X54DF,
	0X555D,	0X55DB,	0X5658,	0X56D4,	0X574F,	0X57CA,	0X5843,	0X58BC,	0X5934,	0X59AB,	0X5A21,	0X5A96,
	0X5B0A,	0X5B7E,	0X5BF0,	0X5C62,	0X5CD3,	0X5D43,	0X5DB2,	0X5E20,	0X5E8D,	0X5EF9,	0X5F65,	0X5FCF,
	0X6039,	0X60A1,	0X6109,	0X6170,	0X61D5,	0X623A,	0X629E,	0X6301,	0X6363,	0X63C4,	0X6424,	0X6483,
	0X64E2,	0X653F,	0X659B,	0X65F6,	0X6650,	0X66AA,	0X6702,	0X6759,	0X67AF,	0X6805,	0X6859,	0X68AC,
	0X68FE,	0X6950,	0X69A0,	0X69EF,	0X6A3D,	0X6A8B,	0X6AD7,	0X6B22,	0X6B6C,	0X6BB5,	0X6BFD,	0X6C44,
	0X6C8A,	0X6CCF,	0X6D13,	0X6D55,	0X6D97,	0X6DD8,	0X6E17,	0X6E56,	0X6E93,	0X6ED0,	0X6F0B,	0X6F45,
	0X6F7F,	0X6FB7,	0X6FEE,	0X7024,	0X7059,	0X708C,	0X70BF,	0X70F1,	0X7121,	0X7151,	0X717F,	0X71AC,
	0X71D9,	0X7204,	0X722E,	0X7257,	0X727E,	0X72A5,	0X72CB,	0X72EF,	0X7312,	0X7335,	0X7356,	0X7376,
	0X7395,	0X73B3,	0X73CF,	0X73EB,	0X7405,	0X741F,	0X7437,	0X744E,	0X7464,	0X7479,	0X748C,	0X749F,
	0X74B1,	0X74C1,	0X74D0,	0X74DE,	0X74EB,	0X74F7,	0X7502,	0X750B,	0X7514,	0X751B,	0X7521,	0X7526,
	0X752A,	0X752D,	0X752F,	0X7530,	0X752F,	0X752D,	0X752A,	0X7526,	0X7521,	0X751B,	0X7514,	0X750B,
	0X7502,	0X74F7,	0X74EB,	0X74DE,	0X74D0,	0X74C1,	0X74B1,	0X749F,	0X748C,	0X7479,	0X7464,	0X744E,
	0X7437,	0X741F,	0X7405,	0X73EB,	0X73CF,	0X73B3,	0X7395,	0X7376,	0X7356,	0X7335,	0X7312,	0X72EF,
	0X72CB,	0X72A5,	0X727E,	0X7257,	0X722E,	0X7204,	0X71D9,	0X71AC,	0X717F,	0X7151,	0X7121,	0X70F1,
	0X70BF,	0X708C,	0X7059,	0X7024,	0X6FEE,	0X6FB7,	0X6F7F,	0X6F45,	0X6F0B,	0X6ED0,	0X6E93,	0X6E56,
	0X6E17,	0X6DD8,	0X6D97,	0X6D55,	0X6D13,	0X6CCF,	0X6C8A,	0X6C44,	0X6BFD,	0X6BB5,	0X6B6C,	0X6B22,
	0X6AD7,	0X6A8B,	0X6A3D,	0X69EF,	0X69A0,	0X6950,	0X68FE,	0X68AC,	0X6859,	0X6805,	0X67AF,	0X6759,
	0X6702,	0X66AA,	0X6650,	0X65F6,	0X659B,	0X653F,	0X64E2,	0X6483,	0X6424,	0X63C4,	0X6363,	0X6301,
	0X629E,	0X623A,	0X61D5,	0X6170,	0X6109,	0X60A1,	0X6039,	0X5FCF,	0X5F65,	0X5EF9,	0X5E8D,	0X5E20,
	0X5DB2,	0X5D43,	0X5CD3,	0X5C62,	0X5BF0,	0X5B7E,	0X5B0A,	0X5A96,	0X5A21,	0X59AB,	0X5934,	0X58BC,
	0X5843,	0X57CA,	0X574F,	0X56D4,	0X5658,	0X55DB,	0X555D,	0X54DF,	0X5460,	0X53DF,	0X535E,	0X52DD,
	0X525A,	0X51D7,	0X5153,	0X50CE,	0X5048,	0X4FC2,	0X4F3A,	0X4EB2,	0X4E29,	0X4DA0,	0X4D16,	0X4C8B,
	0X4BFF,	0X4B72,	0X4AE5,	0X4A57,	0X49C9,	0X4939,	0X48A9,	0X4818,	0X4787,	0X46F5,	0X4662,	0X45CE,
	0X453A,	0X44A5,	0X4410,	0X437A,	0X42E3,	0X424B,	0X41B3,	0X411B,	0X4081,	0X3FE7,	0X3F4D,	0X3EB1,
	0X3E16,	0X3D79,	0X3CDC,	0X3C3F,	0X3BA0,	0X3B02,	0X3A62,	0X39C2,	0X3922,	0X3881,	0X37DF,	0X373D,
	0X369B,	0X35F8,	0X3554,	0X34B0,	0X340B,	0X3366,	0X32C0,	0X321A,	0X3174,	0X30CC,	0X3025,	0X2F7D,
	0X2ED4,	0X2E2B,	0X2D82,	0X2CD8,	0X2C2E,	0X2B83,	0X2AD8,	0X2A2C,	0X2980,	0X28D4,	0X2827,	0X277A,
	0X26CD,	0X261F,	0X2571,	0X24C2,	0X2413,	0X2364,	0X22B4,	0X2204,	0X2154,	0X20A3,	0X1FF2,	0X1F41,
	0X1E8F,	0X1DDD,	0X1D2B,	0X1C79,	0X1BC6,	0X1B13,	0X1A60,	0X19AD,	0X18F9,	0X1845,	0X1791,	0X16DC,
	0X1628,	0X1573,	0X14BE,	0X1408,	0X1353,	0X129D,	0X11E7,	0X1131,	0X107B,	0XFC5,	0XF0E,	0XE58,
	0XDA1,	0XCEA,	0XC33,	0XB7C,	0XAC5,	0XA0D,	0X956,	0X89E,	0X7E7,	0X72F,	0X677,	0X5C0,
	0X508,	0X450,	0X398,	0X2E0,	0X228,	0X170,	0XB8,	0X0,	0XFF48,	0XFE90,	0XFDD8,	0XFD20,	0XFC68,
	0XFBB0,	0XFAF8,	0XFA40,	0XF989,	0XF8D1,	0XF819,	0XF762,	0XF6AA,	0XF5F3,	0XF53B,	0XF484,	0XF3CD,
	0XF316,	0XF25F,	0XF1A8,	0XF0F2,	0XF03B,	0XEF85,	0XEECF,	0XEE19,	0XED63,	0XECAD,	0XEBF8,	0XEB42,
	0XEA8D,	0XE9D8,	0XE924,	0XE86F,	0XE7BB,	0XE707,	0XE653,	0XE5A0,	0XE4ED,	0XE43A,	0XE387,	0XE2D5,
	0XE223,	0XE171,	0XE0BF,	0XE00E,	0XDF5D,	0XDEAC,	0XDDFC,	0XDD4C,	0XDC9C,	0XDBED,	0XDB3E,	0XDA8F,
	0XD9E1,	0XD933,	0XD886,	0XD7D9,	0XD72C,	0XD680,	0XD5D4,	0XD528,	0XD47D,	0XD3D2,	0XD328,	0XD27E,
	0XD1D5,	0XD12C,	0XD083,	0XCFDB,	0XCF34,	0XCE8C,	0XCDE6,	0XCD40,	0XCC9A,	0XCBF5,	0XCB50,	0XCAAC,
	0XCA08,	0XC965,	0XC8C3,	0XC821,	0XC77F,	0XC6DE,	0XC63E,	0XC59E,	0XC4FE,	0XC460,	0XC3C1,	0XC324,
	0XC287,	0XC1EA,	0XC14F,	0XC0B3,	0XC019,	0XBF7F,	0XBEE5,	0XBE4D,	0XBDB5,	0XBD1D,	0XBC86,	0XBBF0,
	0XBB5B,	0XBAC6,	0XBA32,	0XB99E,	0XB90B,	0XB879,	0XB7E8,	0XB757,	0XB6C7,	0XB637,	0XB5A9,	0XB51B,
	0XB48E,	0XB401,	0XB375,	0XB2EA,	0XB260,	0XB1D7,	0XB14E,	0XB0C6,	0XB03E,	0XAFB8,	0XAF32,	0XAEAD,
	0XAE29,	0XADA6,	0XAD23,	0XACA2,	0XAC21,	0XABA0,	0XAB21,	0XAAA3,	0XAA25,	0XA9A8,	0XA92C,	0XA8B1,
	0XA836,	0XA7BD,	0XA744,	0XA6CC,	0XA655,	0XA5DF,	0XA56A,	0XA4F6,	0XA482,	0XA410,	0XA39E,	0XA32D,
	0XA2BD,	0XA24E,	0XA1E0,	0XA173,	0XA107,	0XA09B,	0XA031,	0X9FC7,	0X9F5F,	0X9EF7,	0X9E90,	0X9E2B,
	0X9DC6,	0X9D62,	0X9CFF,	0X9C9D,	0X9C3C,	0X9BDC,	0X9B7D,	0X9B1E,	0X9AC1,	0X9A65,	0X9A0A,	0X99B0,
	0X9956,	0X98FE,	0X98A7,	0X9851,	0X97FB,	0X97A7,	0X9754,	0X9702,	0X96B0,	0X9660,	0X9611,	0X95C3,
	0X9575,	0X9529,	0X94DE,	0X9494,	0X944B,	0X9403,	0X93BC,	0X9376,	0X9331,	0X92ED,	0X92AB,	0X9269,
	0X9228,	0X91E9,	0X91AA,	0X916D,	0X9130,	0X90F5,	0X90BB,	0X9081,	0X9049,	0X9012,	0X8FDC,	0X8FA7,
	0X8F74,	0X8F41,	0X8F0F,	0X8EDF,	0X8EAF,	0X8E81,	0X8E54,	0X8E27,	0X8DFC,	0X8DD2,	0X8DA9,	0X8D82,
	0X8D5B,	0X8D35,	0X8D11,	0X8CEE,	0X8CCB,	0X8CAA,	0X8C8A,	0X8C6B,	0X8C4D,	0X8C31,	0X8C15,	0X8BFB,
	0X8BE1,	0X8BC9,	0X8BB2,	0X8B9C,	0X8B87,	0X8B74,	0X8B61,	0X8B4F,	0X8B3F,	0X8B30,	0X8B22,	0X8B15,
	0X8B09,	0X8AFE,	0X8AF5,	0X8AEC,	0X8AE5,	0X8ADF,	0X8ADA,	0X8AD6,	0X8AD3,	0X8AD1,	0X8AD0,	0X8AD1,
	0X8AD3,	0X8AD6,	0X8ADA,	0X8ADF,	0X8AE5,	0X8AEC,	0X8AF5,	0X8AFE,	0X8B09,	0X8B15,	0X8B22,	0X8B30,
	0X8B3F,	0X8B4F,	0X8B61,	0X8B74,	0X8B87,	0X8B9C,	0X8BB2,	0X8BC9,	0X8BE1,	0X8BFB,	0X8C15,	0X8C31,
	0X8C4D,	0X8C6B,	0X8C8A,	0X8CAA,	0X8CCB,	0X8CEE,	0X8D11,	0X8D35,	0X8D5B,	0X8D82,	0X8DA9,	0X8DD2,
	0X8DFC,	0X8E27,	0X8E54,	0X8E81,	0X8EAF,	0X8EDF,	0X8F0F,	0X8F41,	0X8F74,	0X8FA7,	0X8FDC,	0X9012,
	0X9049,	0X9081,	0X90BB,	0X90F5,	0X9130,	0X916D,	0X91AA,	0X91E9,	0X9228,	0X9269,	0X92AB,	0X92ED,
	0X9331,	0X9376,	0X93BC,	0X9403,	0X944B,	0X9494,	0X94DE,	0X9529,	0X9575,	0X95C3,	0X9611,	0X9660,
	0X96B0,	0X9702,	0X9754,	0X97A7,	0X97FB,	0X9851,	0X98A7,	0X98FE,	0X9956,	0X99B0,	0X9A0A,	0X9A65,
	0X9AC1,	0X9B1E,	0X9B7D,	0X9BDC,	0X9C3C,	0X9C9D,	0X9CFF,	0X9D62,	0X9DC6,	0X9E2B,	0X9E90,	0X9EF7,
	0X9F5F,	0X9FC7,	0XA031,	0XA09B,	0XA107,	0XA173,	0XA1E0,	0XA24E,	0XA2BD,	0XA32D,	0XA39E,	0XA410,
	0XA482,	0XA4F6,	0XA56A,	0XA5DF,	0XA655,	0XA6CC,	0XA744,	0XA7BD,	0XA836,	0XA8B1,	0XA92C,	0XA9A8,
	0XAA25,	0XAAA3,	0XAB21,	0XABA0,	0XAC21,	0XACA2,	0XAD23,	0XADA6,	0XAE29,	0XAEAD,	0XAF32,	0XAFB8,
	0XB03E,	0XB0C6,	0XB14E,	0XB1D7,	0XB260,	0XB2EA,	0XB375,	0XB401,	0XB48E,	0XB51B,	0XB5A9,	0XB637,
	0XB6C7,	0XB757,	0XB7E8,	0XB879,	0XB90B,	0XB99E,	0XBA32,	0XBAC6,	0XBB5B,	0XBBF0,	0XBC86,	0XBD1D,
	0XBDB5,	0XBE4D,	0XBEE5,	0XBF7F,	0XC019,	0XC0B3,	0XC14F,	0XC1EA,	0XC287,	0XC324,	0XC3C1,	0XC460,
	0XC4FE,	0XC59E,	0XC63E,	0XC6DE,	0XC77F,	0XC821,	0XC8C3,	0XC965,	0XCA08,	0XCAAC,	0XCB50,	0XCBF5,
	0XCC9A,	0XCD40,	0XCDE6,	0XCE8C,	0XCF34,	0XCFDB,	0XD083,	0XD12C,	0XD1D5,	0XD27E,	0XD328,	0XD3D2,
	0XD47D,	0XD528,	0XD5D4,	0XD680,	0XD72C,	0XD7D9,	0XD886,	0XD933,	0XD9E1,	0XDA8F,	0XDB3E,	0XDBED,
	0XDC9C,	0XDD4C,	0XDDFC,	0XDEAC,	0XDF5D,	0XE00E,	0XE0BF,	0XE171,	0XE223,	0XE2D5,	0XE387,	0XE43A,
	0XE4ED,	0XE5A0,	0XE653,	0XE707,	0XE7BB,	0XE86F,	0XE924,	0XE9D8,	0XEA8D,	0XEB42,	0XEBF8,	0XECAD,
	0XED63,	0XEE19,	0XEECF,	0XEF85,	0XF03B,	0XF0F2,	0XF1A8,	0XF25F,	0XF316,	0XF3CD,	0XF484,	0XF53B,
	0XF5F3,	0XF6AA,	0XF762,	0XF819,	0XF8D1,	0XF989,	0XFA40,	0XFAF8,	0XFBB0,	0XFC68,	0XFD20,	0XFDD8,
	0XFE90,	0XFF48
};


