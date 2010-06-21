/**
 *  @file   PandoraPFANew/include/Algorithms/Clustering/ECalPhotonClusteringAlgorithm.h
 * 
 *  @brief  Header file for the ecal photon clustering algorithm class.
 * 
 *  $Log: $
 */
#ifndef ECAL_PHOTON_CLUSTERING_ALGORITHM_H
#define ECAL_PHOTON_CLUSTERING_ALGORITHM_H 1

#include "Algorithms/Algorithm.h"

#include "Objects/Cluster.h"

#include <cmath>

namespace pandora
{
    class Axis {
    public:
	typedef std::map<float,int> BinMap;

	class WrongBinNumber {};
	class WrongLimits    {};
	class XmlError {};
	class NotAxis {};

	Axis();
	Axis( int bins, float from, float to );
	Axis( const std::vector<float>& binBorders );

	void SetDimensions( int bins, float from, float to );
	void SetDimensions( const std::vector<float>& binBorders );

	int GetBinForValue( float value );
	
	int GetNumberBins();
	float GetMinValue();
	float GetMaxValue();

	void WriteToXml ( TiXmlElement * xmlElement );
	void ReadFromXml( const TiXmlElement &xmlElement );

	void Print( std::ostream& );

	static void TokenizeString(const std::string &inputString, StringVector &tokens, const std::string &delimiter);

    private:
	int numberBins;
	float minValue;
	float maxValue;
	float k;
       
	bool regularBins;

	BinMap bins;

	friend class Histogram1D;
	friend class Histogram2D;
    };

    inline float Axis::GetMinValue()
    {
	return minValue;
    }

    inline float Axis::GetMaxValue()
    {
	return maxValue;
    }


    class Histogram2D;

    class Histogram1D {
    public:
	typedef std::map<int,float> MapOfBins;

	class XmlError {};
	class NotHistogram1D {};


	Histogram1D();
	Histogram1D( const TiXmlElement &xmlElement );
	Histogram1D( const std::string& histogramName, int numberBins, float from, float to );
	Histogram1D( const std::string& histogramName, const std::vector<float>& binBorders );

	void SetDimensions( const std::string& histogramName, int numberBins, float from, float to );
	void SetDimensions( const std::string& histogramName, const std::vector<float>& binBorders );

	void Fill( float value, float weight = 1.0 );

	float GetBinContent( int bin );
	float Get( float value );

	float GetSumOfEntries();
	void Scale( float value );

	void WriteToXml ( TiXmlElement * &xmlElement );
	void ReadFromXml( const TiXmlElement &xmlElement );

	void Print( std::ostream& );

	static void TokenizeString(const std::string &inputString, StringVector &tokens, const std::string &delimiter);

    private:
	void CreateEmptyBins();

	std::string name;
	Axis axis;
	
	MapOfBins bins;
    };


    class Histogram2D {
    public:
	typedef std::map<int,float> MapOfBins;
	typedef std::map<int,MapOfBins> MapOfMapOfBins;

	class XmlError {};
	class NotHistogram2D {};
	class DataStructureError {};


	Histogram2D();
	Histogram2D( const TiXmlElement &xmlElement );
	Histogram2D( const std::string& histogramName, int numberBinsX, float fromX, float toX, int numberBinsY, float fromY, float toY );
	Histogram2D( const std::string& histogramName, const std::vector<float>& binBorders, int numberBinsY, float fromY, float toY );
	Histogram2D( const std::string& histogramName, int numberBinsX, float fromX, float toX, const std::vector<float>& binBorders );
	Histogram2D( const std::string& histogramName, const std::vector<float>& binBordersX, const std::vector<float>& binBordersY );

	void SetDimensions( const std::string& histogramName, int numberBinsX, float fromX, float toX, int numberBinsY, float fromY, float toY );
	void SetDimensions( const std::string& histogramName, int numberBinsX, float fromX, float toX, const std::vector<float>& binBorders );
	void SetDimensions( const std::string& histogramName, const std::vector<float>& binBorders, int numberBinsX, float fromX, float toX );
	void SetDimensions( const std::string& histogramName, const std::vector<float>& binBordersX, const std::vector<float>& binBordersY );

	void Fill( float x, float y, float weight = 1.0 );

	float GetBinContent( int binX, int binY );
	float Get( float valueX, float valueY );

	float GetSumOfEntries();
	void Scale( float value );

	void WriteToXml ( TiXmlElement * &xmlElement );
	void ReadFromXml( const TiXmlElement &xmlElement );

	void Print( std::ostream& );

    private:
	void CreateEmptyBins();

	std::string name;
	Axis axisX, axisY;
	
	MapOfMapOfBins bins;

    };

// TODO to be extracted from xml file
#ifndef LIKELIHOOD_DATA
#define LIKELIHOOD_DATA
    const double likeSig[9] = {97482,77286,41054,45370,46813,29373,14689,7464,2401};

    const double likeBack[9] = {68208,24070,10781,11406,13768,10903,6651,3198,530};

    const double likesrms[9][22] = {
        { 0.00704745,0.0011079,0.0407768,0.273394,0.409132,0.193379,0.0559693,0.014259,0.00350834,0.00103609,0.000307749,
          6.15498e-05,2.05166e-05,0,0,0,0,0,0,0,0,0},
        { 0.00397226,0.000582253,0.00231607,0.0577854,0.375178,0.3714,0.132922,0.0359056,0.0119944,0.0049815,0.00174676,
          0.000763398,0.000349352,6.46948e-05,2.58779e-05,0,1.2939e-05,0,0,0,0,0},
        { 0.00433575,0.000292298,0.00216788,0.00672285,0.189799,0.47172,0.227383,0.058557,0.0208993,0.00969455,0.00513957,
          0.00197301,0.000755103,0.000341014,0.000194865,2.43582e-05,0,0,0,0,0,0},
        { 0.0047829,0.000396738,0.00264492,0.00304166,0.0623099,0.419506,0.352965,0.10335,0.0287855,0.0130703,0.00590699,
          0.00207185,0.000705312,0.000242451,0.000176328,4.4082e-05,0,0,0,0,0,0},
        { 0.00835238,0.000982633,0.0053404,0.00647256,0.00895051,0.207271,0.484374,0.204665,0.0478286,0.0149531,0.00604533,
          0.00228569,0.00136714,0.000469955,0.000277701,0.00012817,0.000106808,0.000106808,2.13616e-05,0,0,0},
        { 0.00374494,0.000204269,0.00680897,0.012903,0.00418752,0.0341811,0.381303,0.395227,0.103599,0.0285296,0.0139924,
          0.0069792,0.00398325,0.0019746,0.00112348,0.000646853,0.000374494,0.000204269,0,3.40449e-05,0,0},
        { 0.000816938,0,0.00197427,0.00708013,0.00258697,0.00442508,0.132752,0.486827,0.208183,0.0627,0.0345837,
          0.0222616,0.0164749,0.00769283,0.00619511,0.00245081,0.00136156,0.00074886,0.000408469,0.000136156,0.000340391,0},
        { 0,0,0.000401929,0.00120579,0.000535906,0.00187567,0.0258574,0.243435,0.283628,0.150456,0.120177,
          0.0841372,0.0400589,0.022776,0.0100482,0.00549303,0.00482315,0.00187567,0.00147374,0.00120579,0.000535906,0},
        { 0,0,0,0,0,0.000832986,0.00333195,0.0495627,0.225323,0.374427,0.149521,
          0.0787172,0.0528946,0.0316535,0.0129113,0.00832986,0.00458142,0.00374844,0.00166597,0.000416493,0.00208247,0}
    };

    const double likebrms[9][22] = {
        { 0.029454,0.0041784,0.060638,0.154967,0.246701,0.224123,0.142476,0.0785978,0.0366966,0.0137521,0.00517535,
          0.00234577,0.000527797,0.000234577,7.33052e-05,5.86441e-05,0,0,0,0,0,0},
        { 0.0157873,0.004113,0.0193187,0.0437059,0.120066,0.200415,0.204985,0.163731,0.103988,0.0598255,0.0339427,
          0.0167844,0.00801828,0.00286664,0.00116327,0.000747819,0.000290818,0.000124636,0.000124636,0,0,0},
        { 0.00806975,0.00268992,0.0147482,0.0124293,0.0442445,0.131806,0.175401,0.194694,0.158056,0.114646,0.064187,
          0.0381226,0.0202208,0.0106669,0.00454503,0.00324645,0.00139134,0.000371023,0.000371023,9.27558e-05,0,0},
        { 0.00569875,0.0022795,0.00876732,0.0102578,0.0172716,0.0730317,0.134666,0.166316,0.17824,0.150535,0.101701,
          0.0684727,0.0398913,0.0203402,0.0106961,0.00710153,0.00236718,0.0013151,0.000701385,0.000350693,0,0},
        { 0.00297792,0.000871586,0.00726322,0.00755375,0.00813481,0.0282539,0.0904997,0.126671,0.154852,0.172066,0.150131,
          0.109602,0.0680564,0.0374782,0.0180128,0.00900639,0.00479372,0.00188844,0.00116212,0.000363161,0.000363161,0},
        { 0.0010089,0.000458589,0.00366872,0.0061451,0.00449418,0.00642025,0.0467761,0.101348,0.148308,0.166835,0.171421,
          0.143538,0.0956617,0.057232,0.0249473,0.0132991,0.00467761,0.00192608,0.00137577,0.000366872,9.17179e-05,0},
        { 0.000751767,0,0.00180424,0.00345813,0.00466095,0.00360848,0.0190949,0.0805894,0.145392,0.176364,0.173959,
          0.15336,0.108405,0.0622463,0.0330777,0.0169899,0.00661555,0.00466095,0.00285671,0.00150353,0.000601413,0},
        { 0,0,0.00125078,0.00375235,0.0068793,0.00406504,0.00875547,0.0459662,0.146654,0.208568,0.178236,
          0.153533,0.103189,0.0587867,0.0397123,0.0190744,0.00875547,0.00625391,0.00312695,0.00250156,0.000938086,0},
        { 0,0,0.00566038,0.00943396,0.0169811,0.0150943,0.00943396,0.0339623,0.133962,0.188679,0.19434,
          0.130189,0.0867925,0.0660377,0.0396226,0.0358491,0.00754717,0.0150943,0.00188679,0.00754717,0.00188679,0}
    };

    const double likesfrac[9][22] = {
        { 0,0,0,2.05166e-05,6.15498e-05,0.000225683,0.000800148,0.00218502,0.00722185,0.0190086,0.0391559,
          0.0692436,0.0972487,0.118904,0.128937,0.125295,0.114052,0.0969718,0.0767116,0.0591802,0.0447775,0},
        { 0,0,0,0,6.46948e-05,0.000310535,0.00301478,0.0136247,0.0391662,0.0824988,0.122597,
          0.152744,0.153741,0.135497,0.104883,0.0750848,0.0483399,0.0310535,0.0187485,0.0117227,0.0069094,0},
        { 0,0,0,0,4.87163e-05,0.00160764,0.0116676,0.0483266,0.11044,0.169996,0.18746,
          0.166001,0.122302,0.0796268,0.0454523,0.0257466,0.0139329,0.00796512,0.00482292,0.00287426,0.00172943,0},
        { 0,0,0,0,0.000374697,0.00643597,0.0463081,0.124443,0.19266,0.208265,0.166938,
          0.115803,0.0670708,0.0336346,0.0169936,0.0088164,0.00509147,0.00284329,0.00227022,0.00125634,0.000793476,0},
        { 0,0,0,0.00012817,0.004785,0.0503493,0.154402,0.23549,0.225642,0.151091,0.0854677,
          0.0444962,0.0220024,0.0111721,0.00619486,0.00352466,0.00237114,0.000982633,0.00100399,0.000491316,0.00040587,0},
        { 0,0,0,0.00142988,0.0420454,0.186566,0.284819,0.22885,0.124672,0.0619617,0.0300276,
          0.0160351,0.00881762,0.00534504,0.00360876,0.0023491,0.00119157,0.00102135,0.000748987,0.000340449,0.000170224,0},
        { 0,0,6.80782e-05,0.0157941,0.164681,0.310777,0.238818,0.128055,0.0616107,0.0332902,0.0173599,
          0.0110967,0.0065355,0.00381238,0.0027912,0.0021785,0.000885016,0.00102117,0.000408469,0.000340391,0.000476547,0},
        { 0,0,0.00241158,0.0978028,0.287915,0.266881,0.156752,0.0766345,0.039523,0.0249196,0.0164791,
          0.0104502,0.00495713,0.00616292,0.00334941,0.00254555,0.000803859,0.00133976,0.000267953,0.000401929,0.000401929,0},
        { 0,0,0.027905,0.222407,0.253228,0.210329,0.130362,0.0703873,0.029571,0.0220741,0.0141608,
          0.0062474,0.00291545,0.00374844,0.00333195,0.00208247,0.000416493,0.000832986,0,0,0,0}
    };

    const double likebfrac[9][22] = {
        { 0,0,0,1.4661e-05,5.86441e-05,0.000307882,0.00057178,0.00158339,0.00381187,0.00757976,0.0144851,
          0.0251437,0.0413734,0.0581457,0.0736277,0.087717,0.102554,0.115148,0.134588,0.156316,0.176973,0},
        { 0,0,0,0,0.000124636,0.000332364,0.00116327,0.0046531,0.011882,0.0249273,0.0429996,
          0.0599917,0.0740756,0.0836726,0.0909015,0.0955962,0.100956,0.103324,0.100457,0.10241,0.102534,0},
        { 0,0,0,0,0.000278267,0.000742046,0.00445228,0.0140989,0.0338559,0.0552824,0.0775438,
          0.0894166,0.088489,0.0917355,0.0870049,0.0859846,0.080141,0.0794917,0.0735553,0.0702161,0.0677117,0},
        { 0,0,0,0,0.000175346,0.00315623,0.0149921,0.0387515,0.0707522,0.0942486,0.101701,
          0.0993337,0.0955637,0.0785551,0.0803086,0.0648781,0.0614589,0.0553218,0.0512888,0.04559,0.0439242,0},
        { 0,0,0,7.26322e-05,0.00254213,0.0183033,0.0589773,0.112435,0.130811,0.125726,0.107132,
          0.0841807,0.070889,0.06319,0.0495352,0.044233,0.0340645,0.0291981,0.026075,0.0233876,0.0192475,0},
        { 0,0,0,0.0010089,0.0192608,0.0894249,0.151334,0.153719,0.134,0.0958452,0.0764927,
          0.0590663,0.0489773,0.0402641,0.0348528,0.0278822,0.0173347,0.0165092,0.0124736,0.0132074,0.00834633,0},
        { 0,0,0,0.0126297,0.0847993,0.168546,0.171403,0.125695,0.092768,0.0724703,0.0500677,
          0.0475117,0.0395429,0.0320253,0.0236055,0.019997,0.0184935,0.0157871,0.00932191,0.00857014,0.0067659,0},
        { 0,0,0.00187617,0.0534709,0.157598,0.174171,0.139775,0.0969356,0.072858,0.0612883,0.0515947,
          0.0381488,0.0390869,0.0243902,0.0209506,0.0222014,0.0134459,0.0115697,0.00906817,0.0068793,0.00469043,0},
        { 0,0,0.0132075,0.133962,0.186792,0.122642,0.130189,0.0962264,0.0641509,0.045283,0.0320755,
          0.0377358,0.0320755,0.0358491,0.0132075,0.0169811,0.0113208,0.0113208,0.00566038,0.00943396,0.00188679,0}
    };

    const double likesstart[9][22] = {
        { 0,0.261525,0.183911,0.142119,0.107528,0.0771937,0.0531483,0.0433208,0.0301594,0.0213578,0.0163723,
          0.0125972,0.00963255,0.00841181,0.00680126,0.00578568,0.00481114,0.00435978,0.00325188,0.0038879,0.00382635,0},
        { 0,0.26182,0.183953,0.148966,0.11046,0.0808555,0.0587946,0.0398779,0.0292679,0.022035,0.0155397,
          0.0111275,0.00829387,0.00648242,0.00530497,0.00423104,0.00333825,0.00291126,0.00256191,0.0022255,0.00195378,0},
        { 0,0.26699,0.185122,0.151824,0.113217,0.0815268,0.0548546,0.0398256,0.0289375,0.0197788,0.01442,
          0.0115458,0.00725873,0.00587032,0.00450626,0.00319092,0.00328835,0.00263068,0.00202173,0.00143713,0.00175379,0},
        { 0,0.265969,0.184858,0.152237,0.11415,0.07959,0.055918,0.041393,0.0291823,0.0214018,0.015076,
          0.00980824,0.00751598,0.00568658,0.00425391,0.0034384,0.0023143,0.00216002,0.00185144,0.00167512,0.00152083,0},
        { 0,0.271014,0.182599,0.150364,0.112234,0.0795933,0.0589366,0.039348,0.02871,0.0212548,0.0141841,
          0.0107876,0.00749792,0.00602397,0.00442185,0.00333241,0.00275564,0.00196527,0.00198663,0.00160212,0.0013885,0},
        { 0,0.266878,0.180302,0.150274,0.118885,0.0800054,0.0600211,0.0391856,0.0286998,0.0198482,0.0154223,
          0.0110986,0.00718347,0.00544718,0.00408538,0.00320022,0.00282572,0.00241719,0.00160011,0.00136179,0.00125966,0},
        { 0,0.270406,0.178229,0.151542,0.116754,0.0848935,0.0578664,0.040098,0.0272313,0.0212404,0.0144326,
          0.00898632,0.0074886,0.00503778,0.00313159,0.00285928,0.00272313,0.00190619,0.00204234,0.00204234,0.00108925,0},
        { 0,0.265675,0.18328,0.153805,0.109861,0.0830654,0.0601554,0.0432744,0.0270632,0.0206324,0.0152733,
          0.00937835,0.00870847,0.00468917,0.00468917,0.00308146,0.00214362,0.00133976,0.00200965,0.000669882,0.00120579,0},
        { 0,0.341108,0.188671,0.153269,0.0995419,0.0595585,0.0478967,0.0358184,0.0199917,0.0137443,0.00749688,
          0.00832986,0.0062474,0.00374844,0.00291545,0.00416493,0.00208247,0.000832986,0.00124948,0.00166597,0.00166597,0}
    };

    const double likebstart[9][22] = {
        { 0,0.106395,0.0722789,0.0586441,0.0539819,0.0496716,0.0436166,0.0488506,0.0451853,0.0470473,0.0450094,
          0.0453319,0.037415,0.0449947,0.0442763,0.0420479,0.043382,0.0419892,0.0370778,0.0466514,0.0461529,0},
        { 0,0.151267,0.0752804,0.0653926,0.0568342,0.0551309,0.0466556,0.0458247,0.045243,0.0421687,0.0412547,
          0.0393851,0.0401329,0.0390943,0.0383049,0.035189,0.0372663,0.0366431,0.0355214,0.0354383,0.0379726,0},
        { 0,0.166775,0.0672479,0.0647435,0.0628884,0.0550969,0.0486968,0.0422966,0.0434097,0.040256,0.0411836,
          0.0399777,0.039885,0.0408125,0.0349689,0.0369168,0.0349689,0.0327428,0.0349689,0.0342269,0.0379371,0},
        { 0,0.176924,0.0695248,0.0641767,0.0555848,0.0537436,0.0499737,0.0449763,0.0440996,0.0409434,0.0384885,
          0.0406803,0.0369981,0.0366474,0.0378748,0.0347186,0.0384885,0.0352446,0.0350693,0.0338418,0.0320007,0},
        { 0,0.1733,0.0621005,0.061011,0.0555636,0.0506973,0.046412,0.0432888,0.0454678,0.0393666,0.0397298,
          0.0417635,0.0421267,0.0411098,0.0391488,0.0398024,0.0350087,0.036534,0.0348634,0.0327571,0.0399477,0},
        { 0,0.151885,0.061451,0.0560396,0.0577823,0.0518206,0.0497111,0.0501697,0.0428322,0.0436577,0.0430157,
          0.042924,0.0387049,0.0382464,0.040631,0.0418233,0.0365037,0.0365037,0.0367789,0.0392553,0.0402641,0},
        { 0,0.152909,0.0580364,0.0586378,0.0535258,0.0536761,0.052774,0.0466095,0.0469102,0.0430011,0.0448053,
          0.0443542,0.0413472,0.0392422,0.0393926,0.0365359,0.0407458,0.0386408,0.037889,0.0372876,0.0336791,0},
        { 0,0.15666,0.0644153,0.0600375,0.0590994,0.0537836,0.0587867,0.0478424,0.0440901,0.0422139,0.0459662,
          0.0350219,0.0456535,0.0384615,0.0406504,0.0368981,0.0347092,0.0368981,0.0362727,0.0306442,0.0318949,0},
        { 0,0.243396,0.0792453,0.0509434,0.0679245,0.0584906,0.0377358,0.0509434,0.0264151,0.0396226,0.0283019,
          0.0396226,0.0358491,0.0471698,0.0339623,0.0358491,0.0226415,0.0188679,0.0358491,0.0226415,0.0245283,0}
    };
#endif

    class PhotonIDLikelihoodCalculator
    {
    public:
	static PhotonIDLikelihoodCalculator* Instance();
	float  PID(float E, float rms, float frac, float start);
	void Delete();

	void WriteXmlSig( const std::string& fileName );
	void WriteXmlBkg( const std::string& fileName );
	void LoadXml(  const std::string& fileNameSig, const std::string& fileNameBkg );

	Histogram1D energySig;
	Histogram1D energyBkg;

	Histogram2D rmsSig;
	Histogram2D fracSig;
	Histogram2D startSig;
	Histogram2D rmsBkg;
	Histogram2D fracBkg;
	Histogram2D startBkg;


    protected:
        PhotonIDLikelihoodCalculator() {  }

    private:
        static PhotonIDLikelihoodCalculator* _instance;
	
	static bool fromXml;

	void ReadXmlSignal(      const std::string& fileNameSig );
	void ReadXmlBackground(  const std::string& fileNameBkg );

    };



    typedef struct
    {
        float energy;
        int   du;
        int   dv;
        float dmin;
        int   showerDepth90;
        int   showerDepth25;
        int   showerStartDepth;
        float rms;
        int peakNumber;
    } protoClusterPeaks_t;

} // namespace pandora

//------------------------------------------------------------------------------------------------------------------------------------------

/**
 *  @brief ECalPhotonClusteringAlgorithm class
 */
class ECalPhotonClusteringAlgorithm : public pandora::Algorithm
{
    /**
     * @brief provides the calculation of a running mean and RMS
     *
     */
    class RunningMeanRMS
    {
    public:
        /**
         * @brief Constructor
         */
	RunningMeanRMS() : m_mean(0), m_nEvents(0), m_weights(0), m_s2(0),m_Rms(0)
        {
        }

        /**
         * @brief getter for current RMS
         *
         * @return (double) RMS
         */
        double GetRMS()
        {
            return m_Rms;
        }

        /**
         * @brief getter for current mean value
         *
         * @return (double) mean value
         */
        double GetMean()
        {
            return m_mean;
        }

        /**
         * @brief getter for current sum of event-weights
         *
         * @return (double) weights
         */
        double GetWeightSum()
        {
            return m_weights;
        }

        /**
         * @brief getter for current number of events
         *
         * @return (int) number of events
         */
        double GetN()
        {
            return m_nEvents;
        }
        
        /**
         * @brief reset everything
         */
        void Clear()
        {
            m_mean = 0;
            m_nEvents = 0;
            m_weights = 0;
            m_s2 = 0;
            m_Rms = 0;
        }

        /**
         * @brief calculate new mean and RMS value
         *
         * @param value
         * @param eventWeight
         */
        void Fill( double value, double eventWeight )
        {
            // calculate the mean-value
            int nNew = m_nEvents + 1;
            double meanNew = CalcMean( m_mean, m_nEvents, value, m_weights, eventWeight );

            double weightsumNew = m_weights + eventWeight;
            // calculate rms
            // S = SQRT( ((n-1)*sOld2 + (xNew-mNew)*(xnew-mOld) )/n )
            // calculate the rms
            double s2New = CalcS2( m_mean, meanNew, nNew, m_s2, value );

            m_Rms = sqrt( s2New );
            m_mean = meanNew;
            m_nEvents = nNew;
            m_weights = weightsumNew;
            m_s2 = s2New;
        }

    private:
        double m_mean;
        int    m_nEvents;
        double m_weights;
        double m_s2;
        double m_Rms;

        /**
         * @brief calculate the new mean value 
         *
         * @param meanOld
         * @param n
         * @param valNew
         * @param weightsumOld
         * @param evweight
         * @return
         */
        double CalcMean( double meanOld, double n, double valNew, double weightsumOld, double evweight ){
	    const double epsilon = 1e-7;
	    if( fabs(n - 0.)<epsilon ) 
		    return valNew;
            //        double meanNew = meanOld + ( valNew - meanOld )/(n +1 );
            double meanNew = (weightsumOld*meanOld + evweight*valNew) / (weightsumOld + evweight);
            return meanNew;
        }

        /**
         * @brief calculate the new s2 value (necessary for calculating the RMS)
         *
         * @param meanOld
         * @param meanNew
         * @param nNew
         * @param s2Old
         * @param valNew
         * @return
         */
        double CalcS2( double meanOld, double meanNew, double nNew, double s2Old, double valNew )
        {
	    const double epsilon = 1e-7;
            if( fabs(nNew - 0.)<epsilon ) return 0.;
            double s2New = ( (nNew-1)*s2Old + (valNew-meanNew)*(valNew-meanOld) )/nNew;
            return s2New;
        }
    };

    /**
     * @brief stores photon Id properties
     *
     */
    class PhotonIdProperties
    {
    public:
        float GetLongProfileShowerStart()  {return m_photonLongShowerStart;};
        float GetLongProfilePhotonFraction(){return m_photonLongProfileFraction;};
        void  SetLongProfileShowerStart(   float photonLongShowerStart    ){ m_photonLongShowerStart = photonLongShowerStart;          }
        void  SetLongProfilePhotonFraction( float photonLongProfileFraction){  m_photonLongProfileFraction = photonLongProfileFraction; }

        float m_photonLongProfileFraction;
        float m_photonLongShowerStart;
    };

    /**
     * @brief stores cluster properties
     */
    class ClusterProperties
    {
    public:
        float electromagneticEnergy;

        float m_hitMean[3]; // alyways x,y,z
        float m_centroid[3];
        float m_centroid10[3];
        float m_centroid20[3];

        float m_centroidEnergy;
        float m_centroid10Energy;
        float m_centroid20Energy;

        pandora::CartesianVector m_centroidFirstLayer; 

        int   m_innerPseudoLayer;
    };

public:
    /**
     *  @brief  Factory class for instantiating algorithm
     */
    class Factory : public pandora::AlgorithmFactory
    {
    public:
        Algorithm *CreateAlgorithm() const;
    };

    ECalPhotonClusteringAlgorithm();

    ~ECalPhotonClusteringAlgorithm();

    /**
     *  @brief  Perform any operations that must occur after reading settings, but before running the algorithm
     */
    virtual StatusCode Initialize();

 private:
    bool       IsPhoton( pandora::Cluster* &pPhotonCandidateCluster, 
			 const pandora::OrderedCaloHitList& pOriginalOrderedCaloHitList, 
			 pandora::protoClusterPeaks_t& peak, 
			 ClusterProperties& originalClusterProperties, 
			 bool& useOriginalCluster, 
			 int& peaksSize); 

    StatusCode TransverseProfile(const pandora::Cluster* cluster, std::vector<pandora::protoClusterPeaks_t> &peaks, int maxLayers);
    pandora::Cluster* TransverseProfile( const ClusterProperties& clusterProperties, const pandora::OrderedCaloHitList& pOrderedCaloHitList, const int peakForProtoCluster, const unsigned int maxLayers, const int extraLayers = 0);

    float      GetTruePhotonContribution(const pandora::Cluster* cluster);
    void       GetClusterProperties(const pandora::Cluster* cluster, ClusterProperties& clusterProperties );
    void       DistanceToPositionAndDirection(const pandora::CartesianVector& position, 
					      const pandora::CartesianVector& referencePosition,
					      const pandora::CartesianVector& referenceDirection,
					      float& longitudinalComponent,
					      float& perpendicularComponent  );


    void CreateOrSaveLikelihoodHistograms(bool create);

    void ComputeTransverseVectors( const pandora::CartesianVector& direction, 
				   pandora::CartesianVector& transverseUnitVectorU, 
				   pandora::CartesianVector& transverseUnitVectorV );

    StatusCode Run();
    StatusCode ReadSettings(const TiXmlHandle xmlHandle);

    static const unsigned int m_maximumNumberOfLayers;

    unsigned int m_nECalLayers;
    unsigned int m_minimumHitsInClusters;
    int          m_producePrintoutStatements;
    int          m_makingPhotonIdLikelihoodHistograms;

    std::string     m_clusterListName;              ///< name of the initial cluster list (only needed when clustering algorithm is run)
    bool            m_preserveClusters;             ///< preserve clusters which were not split and split which are not photons

    std::string     m_monitoringFileName;           ///< filename for file where for monitoring information is stored
    std::string     m_configurationFileNameBkg;     ///< filename for file where the configuration of the photon clustering is stored : background
    std::string     m_configurationFileNameSig;     ///< filename for file where the configuration of the photon clustering is stored : signal
    float           m_likelihoodRatioCut;           ///< cut on likelihood ratio

    std::string     m_strategy;                     ///< The strategy used for photon recognition

    std::string     m_clusteringAlgorithmName;      ///< The name of the clustering algorithm to run

    pandora::StringVector    m_energyBins;                   ///< borders of bins of energy binning (only important at production of configuration xml files)
    pandora::StringVector    m_dimensionsRms;                ///< dimensions of photon candidate cluster Rms histogram (e.g. "20 0 5")
    pandora::StringVector    m_dimensionsFraction;           ///< dimensions of photon fraction histogram (e.g. "20 0 1.0")
    pandora::StringVector    m_dimensionsStart;              ///< dimensions of photon start histogram (e.g. "20 0 10.0" )


    int             m_produceConfigurationFiles;    ///< produce the configuration file (using the provided events) (0... signal events, 1 ... background events, 2 ... signal and background events, to be split by "fraction"


    bool m_isAlreadyInitialized;                    ///< set to true if initialisation has taken place

    pandora::TrackList* pTrackList;                  ///< tracks to be are checked if they are too close to the photoncandidate for a photon
};

//------------------------------------------------------------------------------------------------------------------------------------------

inline pandora::Algorithm *ECalPhotonClusteringAlgorithm::Factory::CreateAlgorithm() const
{
    return new ECalPhotonClusteringAlgorithm();
}

#endif // #ifndef ECAL_PHOTON_CLUSTERING_ALGORITHM_H
