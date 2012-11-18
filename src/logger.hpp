// ====================================================================
// This file is part of FlexibleSUSY.
//
// FlexibleSUSY is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
//
// FlexibleSUSY is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with FlexibleSUSY.  If not, see
// <http://www.gnu.org/licenses/>.
// ====================================================================

#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

/**
 * The following message logger macros are available:
 *
 * VERBOSE_MSG(message)  only printed if VERBOSE is defined
 * DEBUG_MSG(message)    only printed if DEBUG is defined
 * INFO(message)
 * WARNING(message)
 * ERROR(message)
 * FATAL(message)        aborts program execution
 *
 * All output can be disabled if SILENT is defined.
 * To define a preprocessor symbol, use either
 *
 *    #define DEBUG
 *    #define VERBOSE
 *
 * or compile via
 *
 *    make "CPPFLAGS += -DCOLOR_PRINTOUT -DDEBUG -DVERBOSE"
 *
 * or, to suppress all output,
 *
 *    make "CPPFLAGS += -DSILENT"
 */

enum ELogLevel { kVerbose, kDebug, kInfo, kWarning, kError, kFatal };

#ifdef VERBOSE
   #define VERBOSE_MSG(message) LOG(kVerbose, message)
#else
   #define VERBOSE_MSG(message)
#endif

#ifdef DEBUG
   #define DEBUG_MSG(message) LOG(kDebug,   message)
#else
   #define DEBUG_MSG(message)
#endif

#define INFO(message)    LOG(kInfo,    message)
#define WARNING(message) LOG(kWarning, message)
#define ERROR(message)   LOG(kError,   message)

#ifdef SILENT
   #define FATAL(message)                             \
      std::exit(1);                                   \
      assert(false);
#else
   #define FATAL(message)                                          \
      LOG(kFatal, message)                                         \
      std::cout << "*** abort program execution" << std::endl;     \
      std::exit(1);                                                \
      assert(false);
#endif

#ifdef SILENT
   #define LOG(level, message)
#else
   #ifdef COLOR_PRINTOUT
      #define LOG(level, message)                                \
         switch (level) {                                        \
         case kDebug:   std::cout << "\033[0;34m"; break;        \
         case kWarning: std::cout << "\033[0;31mWarning: "; break;      \
         case kError:   std::cout << "\033[1;31mError: "; break;        \
         case kFatal:   std::cout << "\033[41;1;37mFatal: "; break;     \
         case kInfo:                                                     \
         case kVerbose:                                                  \
         default:                                                        \
            break;                                                       \
         }                                                               \
         std::cout << message << "\033[0m" << std::endl;
   #else
      #define LOG(level, message)                  \
          std::cout << message << std::endl;
   #endif
#endif

#endif