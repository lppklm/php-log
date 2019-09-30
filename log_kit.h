#include <phpcpp.h>
#include <glog/logging.h>
#include <phphelper.h>
#include <time.h>
#include <ctime>

class log_kit : public Php::Base{
    public:
        static void init(__PHP_ARGS__);
    public:
        static std::tm  gettime();
        static bool     createdir(const std::string &dir);
        static bool isdir(const std::string &dir);

        enum level_t {debug = 0, info = 1, warn = 2, error = 3};
        static std::string s_prj;
        static std::string s_tag;
        static log_kit::level_t s_level;
        static bool s_inited;
        static std::string s_dir;
        static std::string s_evt;
};
