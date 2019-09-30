/* __phphelper_header_file__ */

#ifndef __PHPHELPER_H_
#define __PHPHELPER_H_

#include <phpcpp.h>

/* 保留 */
#define _php_int                 int
#define _php_long                long
#define _php_float               float
#define _php_double              double
#define _php_bool                bool
#define _php_string              std::string
#define _php_ZVAL                ZVAL

#define _php_get_int_arg(p)      p.numericValue()
#define _php_get_long_arg(p)     p.numericValue()
#define _php_get_float_arg(p)    p.floatValue()
#define _php_get_double_arg(p)   p.floatValue()
#define _php_get_bool_arg(p)     p.boolValue()
#define _php_get_string_arg(p)   p.stringValue()
#define _php_get_ZVAL_arg(p)     p

/* 辅助宏 */
#define ZVAL \
        Php::Value

#define __PHP_ARGS__ \
        Php::Parameters &_params

#define PHP_EXTRACT_ARG(var, type, idx, def)  \
        _php_ ## type var = def; \
        if(_params.size() > idx) { \
           var = static_cast<_php_ ## type>(_php_get_ ## type ##  _arg(_params[idx])); \
        }

#define PHP_ASSIGN_ARG(idx, value)  \
        if(_params.size() > idx) {  \
            _params[idx] = value;   \
        }

#define PHP_COPY_ARG(var, type, idx)  \
        if(_params.size() > idx) { \
           var = static_cast<_php_ ## type>(_php_get_ ## type ##  _arg(_params[idx])); \
        }

#define PHP_ASSERT(cond, r) \
        if(cond) { \
           return r; \
        }

#endif
