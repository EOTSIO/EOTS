#include <eotiolib/eotio.hpp>

using namespace eotio;

class hello : public eotio::contract {
  public:
      using contract::contract;

      /// @abi action 
      void hi( account_name user ) {
         print( "Hello, ", name{user} );
      }
};

eotIO_ABI( hello, (hi) )
