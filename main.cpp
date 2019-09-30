#include <phpcpp.h>
#include <phphelper.h>

//#include "log_kit.h"
#include "php_logger.h"

// symbols are exported according to the "C" language
extern "C"
{
    // export the "get_module" function that will be called by the Zend engine
    PHPCPP_EXPORT void *get_module() 
    { 
        // create extension
        static Php::Extension extension("plog","1.0");

        // define classes
        Php::Class<log_kit> log_kit("log_kit");
        log_kit.method<&log_kit::init>("init", {
                Php::ByVal("prj",       Php::Type::String,  true),
                Php::ByVal("tag",       Php::Type::String,  true),
                Php::ByVal("level",     Php::Type::Numeric, true),
                });


        Php::Class<logger> logger("logger");
        logger.method<&logger::__construct>("__construct", {
                Php::ByVal("name",          Php::Type::String,  true),
                });
        logger.method<&logger::info>("info", {
                Php::ByVal("message",       Php::Type::String,  true),
                Php::ByVal("event",         Php::Type::String,  false),
                });
        logger.method<&logger::warn>("warn", {
                Php::ByVal("message",       Php::Type::String,  true),
                Php::ByVal("event",         Php::Type::String,  false),
                });
        logger.method<&logger::debug>("debug", {
                Php::ByVal("message",       Php::Type::String,  true),
                Php::ByVal("event",         Php::Type::String,  false),
                });
        logger.method<&logger::error>("error", {
                Php::ByVal("message",       Php::Type::String,  true),
                Php::ByVal("event",         Php::Type::String,  false),
                });

        // add to extension
//        extension.add(log_kit);
        extension.add(std::move(log_kit));
        extension.add(std::move(logger));

        extension.add(Php::Ini("plog.log_dir", "/data/projlogs"));
        
        // return the module entry
        return extension.module();
    }
}

