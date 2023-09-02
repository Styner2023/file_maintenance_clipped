#include "global_entities.h"

/// define if asserts are NOT to be checked.  Put in *.h file not *.CPP
//#define 	NDEBUG
/// define I'm Debugging LT.  Put in *.h file not *.CPP
//#define  	GR_DEBUG
//#ifdef   	GR_DEBUG
//#endif  # GR_DEBUG

//#define LOGGER_( msg )   using loc = std::source_location;std::cerr<<"[loc::current().file_name()<<':'<<loc::current().line()<<','<<loc::current().column()<<"]`"<<loc::current().function_name()<<"`:" <<#msg<<".\n";
//#define LOGGER2( msg, x )using loc = std::source_location;std::cerr<<"[loc::current().file_name()<<':'<<loc::current().line()<<','<<loc::current().column()<<"]`"<<loc::current().function_name()<<"`:" <<#msg<<",{"<<x<<"}.\n";
//#define LOGGER_( msg )
//#define LOGGER2( msg,x )
