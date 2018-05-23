#include <eotiolib/eotio.hpp>
#include <eotiolib/print.hpp>
using namespace eotio;

class payloadless : public eotio::contract {
  public:
      using contract::contract;

      void doit() {
         print( "Im a payloadless action" );
      }
};

eotIO_ABI( payloadless, (doit) )
