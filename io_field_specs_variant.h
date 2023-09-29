#ifndef IO_FIELD_SPECS_VARIANT_H
#define IO_FIELD_SPECS_VARIANT_H
#include <iostream>
#include <iterator>
#include <vector>
#include <set>
#include <unordered_set>
#include "state_menu.h"
#include "io_field.h"

using State_menu_variant = std::variant<State_menu>;

/// Allows for the different data types that can be accepted from the user by a data field.
using  IO_field_spec_variant = std::variant<
    IO_field_spec_bool,
    //IO_field_spec_character,          // TODO:
    //IO_field_spec_uint64,             // TODO:
    //IO_field_spec_tm,                 // TODO:
    //IO_field_spec_time_point,         // TODO:
    IO_field_spec_alphanumeric,
    IO_field_spec_integer,
    IO_field_spec_decimal
    //IO_field_spec_scientific          // TODO:
>;

#endif // IO_FIELD_SPECS_VARIANT_H
