/**
 *  @file
 *  @copyright defined in EOTS/LICENSE.txt
 */
#include <utility>
#include <vector>
#include <string>
#include <eotiolib/eotio.hpp>
#include <eotiolib/contract.hpp>

class test_ram_limit : public eotio::contract {
   public:
      const uint32_t FIVE_MINUTES = 5*60;

      test_ram_limit(account_name self)
      :eotio::contract(self)
      {}

      //@abi action
      void setentry(account_name payer, uint64_t from, uint64_t to, uint64_t size) {
         const auto self = get_self();
         eotio::print("test_ram_limit::setentry ", eotio::name{self}, "\n");
         test_table table(self, self);
         for (int key = from; key <=to; ++key) {
            auto itr = table.find(key);
            if (itr != table.end()) {
               table.modify(itr, payer, [size](test& t) {
                  t.data.assign(size, (int8_t)size);
               });
            } else {
               table.emplace(payer, [key,size](test& t) {
                  t.key = key;
                  t.data.assign(size, (int8_t)size);
               });
            }
         }
      }

      //@abi action
      void rmentry(uint64_t from, uint64_t to) {
         const auto self = get_self();
         eotio::print("test_ram_limit::rmentry ", eotio::name{self}, "\n");
         test_table table(self, self);
         for (int key = from; key <=to; ++key) {
            auto itr = table.find(key);
            eotio_assert (itr != table.end(), "could not find test_table entry");
            table.erase(itr);
         }
      }

      //@abi action
      void printentry(uint64_t from, uint64_t to) {
         const auto self = get_self();
         eotio::print("test_ram_limit::printout ", eotio::name{self}, ":");
         test_table table(self, self);
         for (int key = from; key <=to; ++key) {
            auto itr = table.find(key);
            eotio::print("\nkey=", key);
            eotio_assert (itr != table.end(), "could not find test_table entry");
            eotio::print(" size=", itr->data.size());
         }
      }

   private:
      struct test {
         uint64_t            key;
         std::vector<int8_t> data;

         uint64_t primary_key()const { return key; }

         eotLIB_SERIALIZE( test, (key)(data) )
      };
      typedef eotio::multi_index< N(test.table), test> test_table;
};

eotIO_ABI( test_ram_limit, (setentry)(rmentry)(printentry) )
