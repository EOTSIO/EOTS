/**
 *  @file
 *  @copyright defined in eot/LICENSE.txt
 */

#include <eotiolib/eotio.hpp>

namespace eotio {

   class noop: public contract {
      public:
         noop( account_name self ): contract( self ) { }
         void anyaction( account_name from,
                         const std::string& /*type*/,
                         const std::string& /*data*/ )
         {
            require_auth( from );
         }
   };

   eotIO_ABI( noop, ( anyaction ) )

} /// eotio     
