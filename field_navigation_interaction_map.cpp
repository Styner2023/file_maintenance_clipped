#include "field_navigation_interaction_map.h"
#include <cassert>
#include <tuple>
#include <set>

bool FieldNavInteractionIntentTable::verify() const {
    size_t radix = static_cast<int>(Lib_tty::FieldCompletionNav::na) + 2;           // accounts for duplicate int
    assert( rows.size() % radix == 0 );                                         // accounts for duplicate int
    assert( rows.size() % (static_cast<int>( InteractionCategory::na )) == 0 );

    struct Compare {
        bool operator() (FieldNavInteractionIntentRow const & lhs, FieldNavInteractionIntentRow const & rhs ) const {
            return std::tie( lhs.category, lhs.field_nav ) < std::tie( rhs.category, rhs.field_nav );  // https://foonathan.net/2018/07/ordering-relations-programming/
        }
    };
    std::set< FieldNavInteractionIntentRow, Compare > temp { rows.begin(), rows.end() };  // todo: TODO: how do I capture radix, when this thing only takes a type?

    assert( rows.size() == temp.size() + static_cast<int>( InteractionCategory::na ));     // checks for duplicate int suppressed by std::set
    return true;
}
