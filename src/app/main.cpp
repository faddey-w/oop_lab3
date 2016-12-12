

#include "shell_api.hpp"
#include "model/hierarchy.h"
#include "db.hpp"

#include "../shell/api.h"
#include "../shell/lib/builtins.h"


using namespace CM;


int main(int argc, char **argv) {
    World::Ptr world(new World(
        merge_dicts(builtins, {
            {"create_employee", create_employee},
            {"first_name", get_first_name},
            {"last_name", get_last_name},
            {"company", get_company},
            {"position", get_position},
            {"salary", get_salary},
            {"supervisor", get_supervisor},
            {"is_employed", is_employed},
            {"subordinates", get_subordinates},
            {"test_relation", is_supervisor_of},
            {"employ", employ},
            {"transfer", transfer_full},
            {"resubordinate", transfer_sv},
            {"rename_position", transfer_pos},
            {"set_salary", set_salary},
            {"leave", leave_company},
            {"new_company", create_company},
            {"director", get_director},
            {"company_name", get_company_name},
            {"save_to_file", save_company},
            {"load_from_file", load_company},
            {"filter_by_salary", filter_by_salary},
            {"filter_by_position", filter_by_position},
            {"print_hierarchy", hierarchy_to_text},
        }), {}));
    set_world(world);
    Interpreter(world).interactive_loop(std::cin, std::cout);

}

