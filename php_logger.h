#include <glog/logging.h>
#include <ostream>
#include <ctime>
#include <phpcpp.h>
#include <phphelper.h>
#include "log_kit.h"

class logger : public Php::Base{
    public:
        void debug(__PHP_ARGS__);
        void info(__PHP_ARGS__);
        void warn(__PHP_ARGS__);
        void error(__PHP_ARGS__);
        
        logger() = default;
        virtual ~logger() = default;
        void __construct(__PHP_ARGS__);
        void __destruct();

    private :
        void prewrite();

        std::string _name;
        std::tm _time;
};
