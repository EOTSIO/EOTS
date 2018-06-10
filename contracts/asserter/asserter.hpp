/**
 *  @file
 *  @copyright defined in EOTS/LICENSE.txt
 */

#include <eotiolib/eotio.hpp>

namespace asserter {
   struct assertdef {
      int8_t      condition;
      std::string message;

      eotLIB_SERIALIZE( assertdef, (condition)(message) )
   };
}
