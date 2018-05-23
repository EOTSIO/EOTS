/**
 *  @file
 *  @copyright defined in eot/LICENSE.txt
 */

#include <eotio/utilities/tempdir.hpp>

#include <cstdlib>

namespace eotio { namespace utilities {

fc::path temp_directory_path()
{
   const char* eot_tempdir = getenv("eot_TEMPDIR");
   if( eot_tempdir != nullptr )
      return fc::path( eot_tempdir );
   return fc::temp_directory_path() / "eot-tmp";
}

} } // eotio::utilities
