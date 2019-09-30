#include <glog/logging.h>
#include <unistd.h>
#include <sstream>
#include <iomanip>
#include <iostream>
//#include "log_kit.h"
#include "php_logger.h"

using namespace std;

#define timehaschanged(t1, t2) \
     !(t1.tm_hour == t2.tm_hour && t1.tm_mday == t2.tm_mday && t1.tm_mon == t2.tm_mon && t1.tm_year == t2.tm_year)

void logger::__construct(__PHP_ARGS__)
{
    PHP_COPY_ARG(_name, string, 0)
}

void logger::__destruct()
{
}

void logger::prewrite()
{
    std::tm now = log_kit::gettime();
    if (timehaschanged(now, _time)) {
        _time = now;
        std::ostringstream ss, s;

        ss  << log_kit::s_dir << "/" << log_kit::s_prj << "/";
        log_kit::createdir(ss.str());

        ss  << "_all/";
        log_kit::createdir(ss.str());

        ss  << std::setw(4) << std::setfill('0') << 1900 + now.tm_year
            << std::setw(2) << std::setfill('0') << 1 + now.tm_mon
            << "/";
        log_kit::createdir(ss.str());

        ss  << std::setw(2) << std::setfill('0') << now.tm_mday << "/";

        log_kit::createdir(ss.str());

        s   << std::setw(2) << std::setfill('0') << now.tm_hour << "-";

        //设置文件名前缀
        //google::SetLogFilenameExtension(s.str().c_str());
        //google::SetLogFilenameExtension("log_");
       
        //不同级别的日志的生产路径
        google::SetLogDestination(google::GLOG_INFO,    ss.str().c_str());
        //不生成软链
        google::SetLogSymlink(google::GLOG_INFO, "");
        google::SetLogSymlink(google::GLOG_WARNING, "");
        google::SetLogSymlink(google::GLOG_ERROR, "");
        FLAGS_colorlogtostderr=true;
        FLAGS_v = 3;
        google::SetLogDestination(google::GLOG_WARNING, ss.str().c_str());
        google::SetLogDestination(google::GLOG_ERROR,   ss.str().c_str());
    }
}

void logger::info(__PHP_ARGS__)
{
    if(!log_kit::s_inited) {
        return;
    }

    PHP_EXTRACT_ARG(msg, string, 0, "")
    PHP_EXTRACT_ARG(evt, string, 1, log_kit::s_evt)

    prewrite();

    LOG_IF(INFO, log_kit::s_level <= log_kit::info) << _name << " [info] tag[" << log_kit::s_tag << "] evt[" << evt << "] " << msg;
}

void logger::debug(__PHP_ARGS__)
{
    if(!log_kit::s_inited) {
        return;
    }

    PHP_EXTRACT_ARG(msg, string, 0, "")
    PHP_EXTRACT_ARG(evt, string, 1, log_kit::s_evt)

    prewrite();

    LOG_IF(INFO, log_kit::s_level <= log_kit::debug) << _name << " [debug] tag[" << log_kit::s_tag << "] evt[" << evt << "] " << msg;
}

void logger::warn(__PHP_ARGS__)
{
    if(!log_kit::s_inited) {
        return;
    }

    PHP_EXTRACT_ARG(msg, string, 0, "")
    PHP_EXTRACT_ARG(evt, string, 1, log_kit::s_evt)
    
    prewrite();

    LOG_IF(WARNING, log_kit::s_level <= log_kit::warn) << _name << " [warn] tag[" << log_kit::s_tag << "] evt[" << evt << "] " << msg;
}

void logger::error(__PHP_ARGS__)
{
    if(!log_kit::s_inited) {
        return;
    }

    PHP_EXTRACT_ARG(msg, string, 0, "")
    PHP_EXTRACT_ARG(evt, string, 1, log_kit::s_evt)
    
    prewrite();

    LOG_IF(ERROR, log_kit::s_level <= log_kit::error) << _name << " [error] tag[" << log_kit::s_tag << "] evt[" << evt << "] " << msg;
}
