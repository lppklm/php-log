#include <glog/logging.h>
#include <string>
#include <iostream>
#include <phpcpp.h>
#include <phphelper.h>
#include <sys/types.h>
#include <dirent.h>

#include <unistd.h>
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <sys/stat.h>

#include "log_kit.h"

using namespace std;

bool log_kit::s_inited   = false;
std::string log_kit::s_evt = "";
std::string log_kit::s_dir = "";
std::string log_kit::s_prj = "unknow";
std::string log_kit::s_tag = "";
log_kit::level_t log_kit::s_level = log_kit::error;

void log_kit::init(__PHP_ARGS__)
{
    PHP_COPY_ARG(s_prj, string, 0)
    PHP_COPY_ARG(s_tag,     string, 1)
    PHP_EXTRACT_ARG(level,  int,    2, debug)
    s_level = log_kit::level_t(level);
    switch(s_level) {
        case debug:
        case info:
        case warn:
        case error:
            break;
        default:
            s_level = debug;
    }
    if(!s_inited) {
        //使用glog之前必须先初始化库，仅需执行一次，括号内为程序名
        google::InitGoogleLogging(s_prj.c_str());
        //设置级别高于 google::GLOG_INFO 的日志同时输出到屏幕
        google::SetStderrLogging(google::NUM_SEVERITIES);
        //google::SetStderrLogging(google::GLOG_INFO);
        // 通过配置获取日志目录
        std::string log_dir = Php::ini_get("plog.log_dir");
        if(log_dir.length() > 0) {
            s_dir = log_dir;
        }
        //日志目录无效则使用/tmp
        if(!isdir(s_dir)) { 
            s_dir = "/tmp";
        }
        s_inited = true;
    }
    // cout << log_kit::s_dir<< endl;
    // cout << log_kit::s_prj << endl;
    // cout << log_kit::s_tag<< endl;
    // cout << "myMethod GETS CALLED!!!!" << endl;
}

bool log_kit::isdir(const std::string &dir){
    DIR *dirp = opendir(dir.c_str());
    if (dirp == 0) {
        return false;
    }
    closedir(dirp);
    return true;
}

bool log_kit::createdir(const std::string &dir)
{
    if(isdir(dir)) {
        return true;
    }
    return mkdir(dir.c_str(), 0775) == 0;
}

std::tm log_kit::gettime()
{
    std::tm tm;
    time_t t = time(0);
    localtime_r(&t, &tm);
    return tm;
}
