#ifndef GLOBAL_ENTITIES_H
#define GLOBAL_ENTITIES_H

#include <vector>
#include <chrono>
#include <string>
#include <variant>
#include <cstdint>
#include <iostream>
#include <csignal>
#include <stacktrace>
#include <source_location>

// BEGIN OF SNIP todo
// END OF SNIP
/// define if asserts are NOT to be checked.  Put in *.h file not *.CPP
//#define 	NDEBUG
/// define I'm Debugging LT.  Put in *.h file not *.CPP
//#define  	GR_DEBUG
//#ifdef   	GR_DEBUG
//#endif  # GR_DEBUG

//#define LOGGER_( msg )   using loc = std::source_location;std::cerr<<"[loc::current().file_name()<<':'<<loc::current().line()<<','<<loc::current().column()<<"]`"<<loc::current().function_name()<<"`:" <<#msg<<".\n";
//#define LOGGER2( msg, x )using loc = std::source_location;std::cerr<<"[loc::current().file_name()<<':'<<loc::current().line()<<','<<loc::current().column()<<"]`"<<loc::current().function_name()<<"`:" <<#msg<<",{"<<x<<"}.\n";


using std::endl, std::cin, std::cout, std::cerr, std::string;
using namespace std::string_literals;

/* few items for debugging purposes */
#define LOGGER_( msg )   using loc = std::source_location;std::cerr<<"["<<loc::current().file_name()<<':'<<loc::current().line()<<','<<loc::current().column()<<"]`"<<loc::current().function_name()<<"`:" <<#msg<<".\n";
#define LOGGERS( msg, x )using loc = std::source_location;std::cerr<<"["<<loc::current().file_name()<<':'<<loc::current().line()<<','<<loc::current().column()<<"]`"<<loc::current().function_name()<<"`:" <<#msg<<",{"<<x<<"}.\n";
//#define LOGGER_( msg )
//#define LOGGER2( msg,x )

/// describes this program's versioning scheme, similar to how Linux does it.
inline constexpr uint8_t MDTUI_MAJOR 				{0};
inline constexpr uint8_t MDTUI_MINOR 				{1};
inline constexpr uint8_t MDTUI_PATCH 				{0};
inline constexpr uint8_t MDTUI_PRE_RELEASE 		{0};  // 0=alpha, 1=beta, 2=RC1, ... or some other meannig?  TBD.
inline constexpr uint8_t MDTUI_BUILD 				{1};
inline constexpr uint8_t MDTUI_SOFTWARE_PLATFORM   {1};  // 1 = linux
inline constexpr uint8_t MDTUI_HARDWARE_PLATFORM   {1};  // 1 = x86_64
inline constexpr uint8_t MDTUI_ENDIANNESS 			{0};  //  0=unknown, 1=big endian, 2=little endian, ... there are other types!!  todo: NOT set properly or USED

/// current limits of the program
inline constexpr int IO_ROW_FIELDS_NUM_MAX 		{20}; // zero origin, so human number is: this value + 1
inline constexpr int IO_ROW_FIELDS_NUM_PERSON 	  	{8};  // zero origin, so human number is: this value + 1, so if we have 9 actual fields, we use 8, since that gives 9 positions.
static_assert ( IO_ROW_FIELDS_NUM_MAX >= IO_ROW_FIELDS_NUM_PERSON );

inline constexpr std::string  DEFAULT_FILE_NAME { "file_data.json" };

/// some crypto stuff not used in this version
inline constexpr uint64_t ADATA_MAX_LENGTH = 4096;  // purely arbitrary, but exists to warn programmer of unlimited memory use and possible crash from attack.
static_assert ( ADATA_MAX_LENGTH <= INT16_MAX, "number too large" );
inline constexpr std::streamoff PDATA_MAX_LENGTH = 4096*100000;  // purely arbitrary, but exists to warn programmer of unlimited memory use and possible crash from attack.
static_assert ( PDATA_MAX_LENGTH <= INT32_MAX, "number too large" );

/// key program types
using Data_type_boolean 		= bool;
using Data_type_character 		= char;
using Data_type_uint64 			= uint64_t;  		// todo: should GUID be 128 bits?  Was that the only reason for this type?
using Data_type_time_point 		= std::chrono::system_clock::time_point;
using Data_type_tm				= std::tm;  		// todo: will probably never used.
using Data_type_alphanumeric 	= std::string;  	// todo: does not carry the correct characters, ie.  lib_tty::KbFundamentalUnit
//using Data_type_shortinteger 	= short int;  		// not implemented
using Data_type_integer 		= int;
//using Data_type_longinteger 	= long int;  		// not implemented
//using Data_type_longlonginteger	= long long int;  // not implemented
//using Data_type_xxdecimal 	= float;  			// a floating point
using Data_type_decimal 		= double;  			// a floating point
using Data_type_scientific 		= long double;  	// a floating point // todo: kludge!, see below regarding: Data_type_scientific

/// used for both software and file format versions.
struct Version {
    unsigned char major 			{ MDTUI_MAJOR };  // https://semver.org/
    unsigned char minor 			{ MDTUI_MINOR};
    unsigned char patch 			{ MDTUI_PATCH };
    unsigned char pre_release 		{ MDTUI_PRE_RELEASE };
    unsigned char build 			{ MDTUI_BUILD };  // aka: prerelease_number
    unsigned char software_platform { MDTUI_SOFTWARE_PLATFORM };
    unsigned char hardware_platform { MDTUI_HARDWARE_PLATFORM };
    unsigned char endian_ness 		{ MDTUI_ENDIANNESS };
    template< class Archive >
    void serialize( Archive & archive ) {
        archive( major, minor, patch, pre_release, build, software_platform, hardware_platform, endian_ness );
    }
};

static Version version_application {};  // the program code
static Version version_file {};			// SNIP SNIP not used in this version. // the data written to file that the program reads, needed for crypto version !

static_assert( sizeof(Version) <=255, "The lenght of Version is stored in a char, but its value is too great to fit." );

struct Software_product {
    std::string				product_category 		{"Grant's software"};  //
    std::string				product_series			{"USA Series"};  //
    std::string				product_model			{"Password Manager"};  // ie. password manager / secrets vault
    std::string				product_model_variant	{"Standard"};  // ie. basic/standard/advanced/expert
    // Version 				application_version 	{ '\x00', 0x1, 0, 0, 0, 0, 0, 0  };  // no warnings on these values.
    Version 				application_version 	{ version_application };  // no warnings on these values.
    uint64_t				product_gtin_14	  		{ 14 }; // GTIN-14, global UPC like code defined by GS1 organization.https://en.wikipedia.org/wiki/International_Article_Number
    template< class Archive >
    void serialize( Archive & archive ) {           // used by Cereal the serialization library
        archive( application_version, product_gtin_14, product_category, product_series, product_model, product_model_variant );
    }
};

/// types of data supported for file_maintenance and user input
using Data_type_variant = std::variant<		// todo: What was I thinking? How many of these are used?
    std::monostate,
    Data_type_boolean,
    Data_type_character,
    Data_type_uint64,
    Data_type_time_point,
    Data_type_tm,
    Data_type_alphanumeric,
    Data_type_integer,
    Data_type_decimal,
    Data_type_scientific  // NOTE: each of these types must be unique.
    >;

/// types of data supported for the result of user input, ie function return types
using InteractionResultData_Variant = std::variant<  // todo: What was I thinking? How many of these are used?
    std::monostate,
    Data_type_boolean,
    Data_type_character,
    Data_type_uint64,
    Data_type_time_point,
    Data_type_tm,
    Data_type_alphanumeric,
    Data_type_integer,
    Data_type_decimal,
    Data_type_scientific,  // NOTE: each of these types must be unique.
    std::vector<Data_type_variant>  // todo: Seriously a vector? What was I thinking? How many of these are used?
    >;

#endif // GLOBAL_ENTITIES_H
