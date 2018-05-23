/**
 *  @file
 *  @copyright defined in eot/LICENSE.txt
 */
#pragma once

#include <eotiolib/eot.hpp>
#include <eotiolib/token.hpp>
#include <eotiolib/reflect.hpp>
#include <eotiolib/generic_currency.hpp>

#include <bancor/converter.hpp>
#include <currency/currency.hpp>

namespace bancor {
   typedef eotio::generic_currency< eotio::token<N(other),S(4,OTHER)> >  other_currency;
   typedef eotio::generic_currency< eotio::token<N(bancor),S(4,RELAY)> > relay_currency;
   typedef eotio::generic_currency< eotio::token<N(currency),S(4,CUR)> > cur_currency;

   typedef converter<relay_currency, other_currency, cur_currency > example_converter;
} /// bancor

