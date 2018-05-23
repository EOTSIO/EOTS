/**
 *  @file
 *  @copyright defined in eot/LICENSE.txt
 */
#include <eotiolib/print.hpp> /// defines transfer struct (abi)

extern "C" {

    /// The apply method just prints forever
    void apply( uint64_t, uint64_t, uint64_t ) {
       int idx = 0;
       while(true) {
          eotio::print(idx++);
       }
    }
}
