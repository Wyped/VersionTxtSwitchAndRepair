#ifndef FIRMWARE_VERSIONS_H
#define FIRMWARE_VERSIONS_H

typedef struct {
    const char *name;
    const char *release;
    const char *build;
    const char *system;
    const char *vsh;
    const char *target;
} FirmwareVersion;

// Order: 9.xx, 6.xx, 5.xx, 4.xx, 3.xx, 2.xx, 1.xx
static const FirmwareVersion firmware_versions[] = {
    // 9.xx
    { "9.90", "9.90", "6666,0,3,1,0:builder@vsh-build6", "54865@release_610,0x09090010:", "p6501@release_610,55286@release_610,20121221:", "1:WorldWide" },
    // 6.xx
    { "6.61", "6.61", "5553,0,3,1,0:builder@vsh-build6", "58401@release_661,0x06060110:", "p6621@release_661,v58692@release_661,20141113:", "1:WorldWide" },
    { "6.60", "6.60", "5455,0,3,1,0:builder@vsh-build6", "57716@release_660,0x06060010:", "p6616@release_660,v58533@release_660,20110727:", "1:WorldWide" },
    { "6.50", "6.50", "5185,0,3,1,0:builder@vsh-build6", "57469@release_650,0x06050010:", "p6613@release_650,v58373@release_650,20110527:", "1:WorldWide" },
    { "6.39", "6.39", "5148,0,3,1,0:builder@vsh-build6", "57445@release_639,0x06030910:", "p6611@release_639,v58354@release_639,20110518:", "1:WorldWide" },
    { "6.38", "6.38", "5023,0,3,1,0:builder@vsh-build6", "57374@release_638,0x06030810:", "p6610@release_638,v58299@release_638,20110406:", "1:WorldWide" },
    { "6.37", "6.37", "4884,0,3,1,0:builder@vsh-build6", "57081@release_637,0x06030710:", "p6598@release_637,v58248@release_637,20110118:", "1:WorldWide" },
    { "6.36", "6.36", "4812,0,3,1,0:builder@vsh-build6", "56919@release_636,0x06030610:", "p6588@release_636,v58190@release_636,20101013:", "1:WorldWide" },
    { "6.35", "6.35", "4801,0,3,1,0:builder@vsh-build6", "56918@release_635,0x06030510:", "p6587@release_635,v58189@release_635,20101013:", "1:WorldWide" },
    { "6.31", "6.31", "4614,0,3,1,0:builder@vsh-build6", "56684@release_631,0x06030110:", "p6579@release_631,v57952@release_631,20100726:", "1:WorldWide" },
    { "6.30", "6.30", "4530,0,3,1,0:builder@vsh-build6", "56422@release_630,0x06030010:", "p6576@release_630,v57929@release_630,20100625:", "1:WorldWide" },
    { "6.20", "6.20", "4047,0,3,1,0:builder@vsh-build6", "55383@release_620,0x06020010:", "p6544@release_620,v56454@release_620,20091118:", "1:WorldWide" },
    { "6.10", "6.10", "3745,0,3,1,0:builder@vsh-build6", "54865@release_610,0x06010010:", "p6501@release_610,v55286@release_610,20090918:", "1:WorldWide" },
    { "6.00", "6.00", "3642,0,3,1,0:builder@vsh-build6", "54442@release_600,0x06000010:", "p6496@release_600,v54812@release_600,20090831:", "1:WorldWide" },
    // 5.xx
    { "5.70", "5.70", "3188,0,3,1,0:builder@vsh-build6", "52442@release_570,0x05070010:", "p6437@release_570,v52500@release_570,20090602:", "1:WorldWide" },
    { "5.55", "5.55", "3230,0,3,1,0:builder@vsh-build6", "52556@release_555,0x05050510:", "p6434@release_555,v52629@release_555,20090608:", "1:WorldWide" },
    { "5.51", "5.51", "3218,0,3,1,0:builder@vsh-build6", "52303@release_551,0x05050110:", "p6427@release_551,v52628@release_551,20090605:", "1:WorldWide" },
    { "5.50", "5.50", "3062,0,3,1,0:builder@vsh-build6", "50781@release_550,0x05050010:", "p6399@release_550,v50953@release_550,20090415:", "1:WorldWide" },
    { "5.05", "5.05", "2852,0,3,1,0:builder@vsh-build6", "47559@release_505,0x05000510:", "p6295@release_505,v48066@release_505,20090106:", "1:WorldWide" },
    { "5.03", "5.03", "2811,0,3,1,0:builder@vsh-build6", "48582@release_503,0x05000310:", "p6335@release_503,v48069@release_503,20090115:", "1:WorldWide" },
    { "5.02", "5.02", "2786,0,3,1,0:builder@vsh-build6", "47558@release_502,0x05000210:", "p6294@release_502,v47301@release_502,20081114:", "1:WorldWide" },
    { "5.01", "5.01", "2753,0,3,1,0:builder@vsh-build6", "47042@release_501,0x05000110:", "p6284@release_501,v46801@release_501,20081020:", "1:WorldWide" },
    { "5.00", "5.00", "2740,0,3,1,0:builder@vsh-build6", "46876@release_500,0x05000010:", "p6264@release_500,v46652@release_500,20081010:", "1:WorldWide" },
    // 4.xx
    { "4.21", "4.21", "2652,0,3,1,0:builder@vsh-build6", "46193@release_421,0x04020110:", "p6218@release_421,v44731@release_421,20080829:", "1:WorldWide" },
    { "4.05", "4.05", "2601,0,3,1,0:builder@vsh-build5", "45626@release_405,0x04000510:", "p6105@release_405,v43522@release_405,20080708:", "1:WorldWide" },
    { "4.01", "4.01", "2561,0,3,1,0:builder@vsh-build5", "45479@release_401,0x04000110:", "p6114@release_401,v43161@release_401,20080623:", "1:WorldWide" },
    { "4.00", "4.00", "2535,0,3,1,0:builder@vsh-build5", "45313@release_400,0x04000010:", "p6093@release_400,v42748@release_400,20080610:", "1:WorldWide" },
    // 3.xx
    { "3.96", "3.96", "2448,0,3,1,0:builder@vsh-build5", "44741@release_396,0x03090610:", "p6025@release_396,v40745@release_396,20080416:", "1:WorldWide" },
    { "3.95", "3.95", "2427,0,3,1,0:builder@vsh-build5", "44605@release_395,0x03090510:", "p6002@release_395,v40572@release_395,20080407:", "1:WorldWide" },
    { "3.93", "3.93", "2395,0,3,1,0:builder@vsh-build5", "43758@release_393,0x03090310:", "p5988@release_393,v40066@release_393,20080311:", "1:WorldWide" },
    { "3.90", "3.90", "2342,0,3,1,0:builder@vsh-build5", "43306@release_390,0x03090010:", "p5941@release_390,v39072@release_390,20080129:", "1:WorldWide" },
    { "3.80", "3.80", "2291,0,3,1,0:builder@vsh-build5", "42902@release_380,0x03080010:", "p5932@release_380,v38534@release_380,20071216:", "1:WorldWide" },
    { "3.73", "3.73", "2240,0,3,1,0:builder@vsh-build5", "42642@release_373,0x03070310:", "p5929@release_373,v37902@release_373,20071121:", "1:WorldWide" },
    { "3.72", "3.72", "2175,0,3,1,0:builder@vsh-build5", "41849@release_372,0x03070210:", "p5875@release_372,v36714@release_372,20071022:", "1:WorldWide" },
    { "3.71", "3.71", "2131,0,3,1,0:builder@vsh-build5", "41608@release_371,0x03070110:", "p5863@release_371,v35667@release_371,20070912:", "1:WorldWide" },
    { "3.70", "3.70", "2125,0,3,1,0:builder@vsh-build5", "41477@release_370,0x03070010:", "p5848@release_370,v35510@release_370,20070905:", "1:WorldWide" },
    { "3.60", "3.60", "2006,0,3,1,0:builder@vsh-build5", "40313@release_360,0x03060010:", "p5660@release_360,v33295@release_360,20070628:", "1:WorldWide" },
    { "3.52", "3.52", "2028,0,3,1,0:builder@vsh-build5", "40477@release_352,0x03050210:", "p5744@release_352,v34071@release_352,20070723:", "1:WorldWide" },
    { "3.51", "3.51", "2002,0,3,1,0:builder@vsh-build5", "40303@release_351,0x03050110:", "p5725@release_351,v33277@release_351,20070627:", "1:WorldWide" },
    { "3.50", "3.50", "1964,0,3,1,0:builder@vsh-build5", "39738@release_350,0x03050010:", "p5655@release_350,v32747@release_350,20070530:", "1:WorldWide" },
    { "3.40", "3.40", "1869,0,3,1,0:builder@vsh-build5", "38823@release_340,0x03040010:", "p5578@release_340,v31191@release_340,20070417:", "1:WorldWide" },
    { "3.30", "3.30", "1834,0,3,1,0:builder@vsh-build5", "38497@release_330,0x03030010:", "p5532@release_330,v30286@release_330,20070327:", "1:WorldWide" },
    { "3.11", "3.11", "1757,0,3,1,0:builder@vsh-build5", "37879@release_311,0x03010110:", "p5481@release_311,v28756@release_311,20070206:", "1:WorldWide" },
    { "3.10", "3.10", "1743,0,3,1,0:builder@vsh-build5", "37782@release_310,0x03010010:", "p5472@release_310,v28518@release_310,20070129:", "1:WorldWide" },
    { "3.03", "3.03", "1668,0,3,1,0:builder@vsh-build5", "37312@release_303,0x03000310:", "p5427@release_303,v27416@release_303,20061216:", "1:WorldWide" },
    { "3.02", "3.02", "1641,0,3,1,0:builder@vsh-build2", "37108@release_302,0x03000210:", "p5416@release_302,v27377@release_302,20061204:", "1:WorldWide" },
    { "3.01", "3.01", "1628,0,3,1,0:builder@vsh-build2", "36993@release_301,0x03000110:", "p5403@release_301,v27265@release_301,20061122:", "1:WorldWide" },
    { "3.00", "3.00", "1623,0,3,1,0:builder@vsh-build2", "36960@release_300,0x03000010:", "p5396@release_300,v27170@release_300,20061120:", "1:WorldWide" },
    // 2.xx
    { "2.82", "2.82", "1490,0,3,1,0:builder@vsh-build2", "36351@release_282,0x02080210:", "p5354@release_282,v25802@release_282,20061004:", "1:WorldWide" },
    { "2.81", "2.81", "1450,0,3,1,0:builder@vsh-build2", "35536@release_281,0x02080110:", "p5291@release_281,v24983@release_281,20060828:", "1:WorldWide" },
    { "2.80", "2.80", "1415,0,3,1,0:builder@vsh-build2", "35183@release_280,0x02080010:", "p5270@release_280,v24399@release_280,20060724:", "" },
    { "2.71", "2.71", "1299,0,3,1,0:builder@vsh-build2", "33696@release_271,0x02070110:", "p5218@release_271,v22873@release_271,20060529:", "" },
    { "2.70", "2.70", "1238,0,3,1,0:builder@vsh-build2", "33151@release_270,0x02070010:", "p5186@release_270,v22631@release_270,20060420:", "" },
    { "2.60", "2.60", "962,0,3,1,0:root@vsh-build", "29904@release_260,0x02060010:", "p5029@release_260,v20391@release_260,20051125:", "" },
    { "2.50", "2.50", "863,0,3,1,0:root@vsh-build", "28611@release_250,0x02050010:", "p4810@release_250,v19039@release_250,20051011:", "1:WorldWide" },
    { "2.01", "2.01", "822,0,3,1,0:root@psp-vsh", "26084@release_200,0x02000010:", "p4793@release_201,v18444@release_201,20050928:", "1:WorldWide" },
    { "2.00", "2.00", "725,0,3,1,0:root@psp-vsh", "26084@release_200,0x02000010:", "p4705@release_200,v15867@release_200,20050726:", "1:WorldWide" },
    // 1.xx
    { "1.52", "1.52", "555,0,3,1,0:root@psp-vsh", "23740@release_152,0x01050200:", "p4421@release_152,v13394@release_152,20050525:", "" },
    { "1.51", "1.51", "513,0,3,1,0:root@psp-vsh", "22984@release_151,0x01050100:", "p4388@release_151_sc,v12875@release_151_sc,20050507:", "" },
    { "1.50", "1.50", "376,0,3,1,0:root@psp-vsh", "20182@release_150,0x01050001:", "p4201@release_150,v11079@release_150,20050201:", "" },
    { "1.00", "1.00", "106,1:root@psp-vsh", "16214,0x00100000:", "2004_1104_s16214_p3883_v8335:", "" }
};

#define NUM_FIRMWARES (sizeof(firmware_versions)/sizeof(firmware_versions[0]))

typedef struct {
    const char *series_name;
    int start;
    int end;
} FirmwareSeries;

// --- Use /script/calculateFwSeriesRanges.sh to calculare range easily ---
static const FirmwareSeries firmware_series[] = {
    { "Firmware 9.xx (Block firmware update)",  0,  0 },
    { "Firmware 6.xx",  1, 13 },
    { "Firmware 5.xx", 14, 22 },
    { "Firmware 4.xx", 23, 26 },
    { "Firmware 3.xx", 27, 47 },
    { "Firmware 2.xx", 48, 56 },
    { "Firmware 1.xx", 57, 60 }
};
#define NUM_SERIES (sizeof(firmware_series)/sizeof(firmware_series[0]))

#endif