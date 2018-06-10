/**
 *  @file
 *  @copyright defined in EOTS/LICENSE.txt
 */
#include <eotiolib/eotio.hpp>

#include "test_api.hpp"

void test_types::types_size() {

   eotio_assert( sizeof(int64_t) == 8, "int64_t size != 8");
   eotio_assert( sizeof(uint64_t) ==  8, "uint64_t size != 8");
   eotio_assert( sizeof(uint32_t) ==  4, "uint32_t size != 4");
   eotio_assert( sizeof(int32_t) ==  4, "int32_t size != 4");
   eotio_assert( sizeof(uint128_t) == 16, "uint128_t size != 16");
   eotio_assert( sizeof(int128_t) == 16, "int128_t size != 16");
   eotio_assert( sizeof(uint8_t) ==  1, "uint8_t size != 1");

   eotio_assert( sizeof(account_name) ==  8, "account_name size !=  8");
   eotio_assert( sizeof(token_name) ==  8, "token_name size !=  8");
   eotio_assert( sizeof(table_name) ==  8, "table_name size !=  8");
   eotio_assert( sizeof(time) ==  4, "time size !=  4");
   eotio_assert( sizeof(eotio::key256) == 32, "key256 size != 32" );
}

void test_types::char_to_symbol() {

   eotio_assert( eotio::char_to_symbol('1') ==  1, "eotio::char_to_symbol('1') !=  1");
   eotio_assert( eotio::char_to_symbol('2') ==  2, "eotio::char_to_symbol('2') !=  2");
   eotio_assert( eotio::char_to_symbol('3') ==  3, "eotio::char_to_symbol('3') !=  3");
   eotio_assert( eotio::char_to_symbol('4') ==  4, "eotio::char_to_symbol('4') !=  4");
   eotio_assert( eotio::char_to_symbol('5') ==  5, "eotio::char_to_symbol('5') !=  5");
   eotio_assert( eotio::char_to_symbol('a') ==  6, "eotio::char_to_symbol('a') !=  6");
   eotio_assert( eotio::char_to_symbol('b') ==  7, "eotio::char_to_symbol('b') !=  7");
   eotio_assert( eotio::char_to_symbol('c') ==  8, "eotio::char_to_symbol('c') !=  8");
   eotio_assert( eotio::char_to_symbol('d') ==  9, "eotio::char_to_symbol('d') !=  9");
   eotio_assert( eotio::char_to_symbol('e') == 10, "eotio::char_to_symbol('e') != 10");
   eotio_assert( eotio::char_to_symbol('f') == 11, "eotio::char_to_symbol('f') != 11");
   eotio_assert( eotio::char_to_symbol('g') == 12, "eotio::char_to_symbol('g') != 12");
   eotio_assert( eotio::char_to_symbol('h') == 13, "eotio::char_to_symbol('h') != 13");
   eotio_assert( eotio::char_to_symbol('i') == 14, "eotio::char_to_symbol('i') != 14");
   eotio_assert( eotio::char_to_symbol('j') == 15, "eotio::char_to_symbol('j') != 15");
   eotio_assert( eotio::char_to_symbol('k') == 16, "eotio::char_to_symbol('k') != 16");
   eotio_assert( eotio::char_to_symbol('l') == 17, "eotio::char_to_symbol('l') != 17");
   eotio_assert( eotio::char_to_symbol('m') == 18, "eotio::char_to_symbol('m') != 18");
   eotio_assert( eotio::char_to_symbol('n') == 19, "eotio::char_to_symbol('n') != 19");
   eotio_assert( eotio::char_to_symbol('o') == 20, "eotio::char_to_symbol('o') != 20");
   eotio_assert( eotio::char_to_symbol('p') == 21, "eotio::char_to_symbol('p') != 21");
   eotio_assert( eotio::char_to_symbol('q') == 22, "eotio::char_to_symbol('q') != 22");
   eotio_assert( eotio::char_to_symbol('r') == 23, "eotio::char_to_symbol('r') != 23");
   eotio_assert( eotio::char_to_symbol('s') == 24, "eotio::char_to_symbol('s') != 24");
   eotio_assert( eotio::char_to_symbol('t') == 25, "eotio::char_to_symbol('t') != 25");
   eotio_assert( eotio::char_to_symbol('u') == 26, "eotio::char_to_symbol('u') != 26");
   eotio_assert( eotio::char_to_symbol('v') == 27, "eotio::char_to_symbol('v') != 27");
   eotio_assert( eotio::char_to_symbol('w') == 28, "eotio::char_to_symbol('w') != 28");
   eotio_assert( eotio::char_to_symbol('x') == 29, "eotio::char_to_symbol('x') != 29");
   eotio_assert( eotio::char_to_symbol('y') == 30, "eotio::char_to_symbol('y') != 30");
   eotio_assert( eotio::char_to_symbol('z') == 31, "eotio::char_to_symbol('z') != 31");

   for(unsigned char i = 0; i<255; i++) {
      if((i >= 'a' && i <= 'z') || (i >= '1' || i <= '5')) continue;
      eotio_assert( eotio::char_to_symbol((char)i) == 0, "eotio::char_to_symbol() != 0");
   }
}

void test_types::string_to_name() {

   eotio_assert( eotio::string_to_name("a") == N(a) , "eotio::string_to_name(a)" );
   eotio_assert( eotio::string_to_name("ba") == N(ba) , "eotio::string_to_name(ba)" );
   eotio_assert( eotio::string_to_name("cba") == N(cba) , "eotio::string_to_name(cba)" );
   eotio_assert( eotio::string_to_name("dcba") == N(dcba) , "eotio::string_to_name(dcba)" );
   eotio_assert( eotio::string_to_name("edcba") == N(edcba) , "eotio::string_to_name(edcba)" );
   eotio_assert( eotio::string_to_name("fedcba") == N(fedcba) , "eotio::string_to_name(fedcba)" );
   eotio_assert( eotio::string_to_name("gfedcba") == N(gfedcba) , "eotio::string_to_name(gfedcba)" );
   eotio_assert( eotio::string_to_name("hgfedcba") == N(hgfedcba) , "eotio::string_to_name(hgfedcba)" );
   eotio_assert( eotio::string_to_name("ihgfedcba") == N(ihgfedcba) , "eotio::string_to_name(ihgfedcba)" );
   eotio_assert( eotio::string_to_name("jihgfedcba") == N(jihgfedcba) , "eotio::string_to_name(jihgfedcba)" );
   eotio_assert( eotio::string_to_name("kjihgfedcba") == N(kjihgfedcba) , "eotio::string_to_name(kjihgfedcba)" );
   eotio_assert( eotio::string_to_name("lkjihgfedcba") == N(lkjihgfedcba) , "eotio::string_to_name(lkjihgfedcba)" );
   eotio_assert( eotio::string_to_name("mlkjihgfedcba") == N(mlkjihgfedcba) , "eotio::string_to_name(mlkjihgfedcba)" );
   eotio_assert( eotio::string_to_name("mlkjihgfedcba1") == N(mlkjihgfedcba2) , "eotio::string_to_name(mlkjihgfedcba2)" );
   eotio_assert( eotio::string_to_name("mlkjihgfedcba55") == N(mlkjihgfedcba14) , "eotio::string_to_name(mlkjihgfedcba14)" );

   eotio_assert( eotio::string_to_name("azAA34") == N(azBB34) , "eotio::string_to_name N(azBB34)" );
   eotio_assert( eotio::string_to_name("AZaz12Bc34") == N(AZaz12Bc34) , "eotio::string_to_name AZaz12Bc34" );
   eotio_assert( eotio::string_to_name("AAAAAAAAAAAAAAA") == eotio::string_to_name("BBBBBBBBBBBBBDDDDDFFFGG") , "eotio::string_to_name BBBBBBBBBBBBBDDDDDFFFGG" );
}

void test_types::name_class() {

   eotio_assert( eotio::name{eotio::string_to_name("azAA34")}.value == N(azAA34), "eotio::name != N(azAA34)" );
   eotio_assert( eotio::name{eotio::string_to_name("AABBCC")}.value == 0, "eotio::name != N(0)" );
   eotio_assert( eotio::name{eotio::string_to_name("AA11")}.value == N(AA11), "eotio::name != N(AA11)" );
   eotio_assert( eotio::name{eotio::string_to_name("11AA")}.value == N(11), "eotio::name != N(11)" );
   eotio_assert( eotio::name{eotio::string_to_name("22BBCCXXAA")}.value == N(22), "eotio::name != N(22)" );
   eotio_assert( eotio::name{eotio::string_to_name("AAAbbcccdd")} == eotio::name{eotio::string_to_name("AAAbbcccdd")}, "eotio::name == eotio::name" );

   uint64_t tmp = eotio::name{eotio::string_to_name("11bbcccdd")};
   eotio_assert(N(11bbcccdd) == tmp, "N(11bbcccdd) == tmp");
}
