#include "global_entities.h"
/// gives a source location for printing.  Used for debugging.
std::string
source_loc() {
    using loc = std::source_location;
    //using ts = std::to_string;  // todo??: why not?  alternative approach?
    std::string result {"\n"s+loc::current().file_name() +":"s +std::to_string(loc::current().line()) +std::to_string(loc::current().column())+"]`"s +loc::current().function_name()+"`."s};
    return result;
}
/// Prints a stack trace of crash location for printing.  Used for debugging.
auto crash_tracer(int const signal_number) ->void { cout << "CRASH_ERROR: signal#, stack trace:<<<" << signal_number << ">>>,<<<" << std::stacktrace::current() << "<<<END STACK TRACE.\n"; }
/// Prints a stack trace of crash location for printing.  Used for debugging.
auto crash_signals_register() -> void {    // signals that cause "terminate" and sometimes "core dump"  https://en.wikipedia.org/wiki/Signal_(IPC)
    std::signal( SIGABRT, crash_tracer );
    std::signal( SIGALRM, crash_tracer );
    std::signal( SIGBUS,  crash_tracer );
    std::signal( SIGFPE,  crash_tracer );
    std::signal( SIGHUP,  crash_tracer );
    std::signal( SIGILL,  crash_tracer );
    std::signal( SIGINT,  crash_tracer );
    std::signal( SIGKILL, crash_tracer );
    std::signal( SIGPIPE, crash_tracer );
    std::signal( SIGPOLL, crash_tracer );
    std::signal( SIGPROF, crash_tracer );
    std::signal( SIGQUIT, crash_tracer );
    std::signal( SIGSEGV, crash_tracer );
    std::signal( SIGSYS,  crash_tracer );
    std::signal( SIGTERM, crash_tracer );
    std::signal( SIGTRAP, crash_tracer );
    std::signal( SIGUSR1, crash_tracer );
    std::signal( SIGUSR2, crash_tracer );
    std::signal( SIGVTALRM, crash_tracer );
    std::signal( SIGXCPU, crash_tracer );
    std::signal( SIGXFSZ, crash_tracer );
    std::signal( SIGVTALRM, crash_tracer );
}
