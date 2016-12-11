

#include "shell_api.hpp"
#include "model/hierarchy.h"
#include "db.hpp"
#include "../shell/api.h"
#include "../shell/lib/builtins.h"


const std::string data = R"(
{
    "company_name": "",
    "hierarchy": {
        "first_name": "director",
        "last_name": "",
        "position": "CEO",
        "salary": 0,
        "subordinates": [
            {
                "first_name": "manager 1",
                "last_name": "",
                "position": "manager 1",
                "salary": 1,
                "subordinates": [
                    {
                        "first_name": "worker 1-1",
                        "last_name": "",
                        "position": "worker 1-1",
                        "salary": 1,
                        "subordinates": []
                    },
                    {
                        "first_name": "worker 1-2",
                        "last_name": "",
                        "position": "worker 1-2",
                        "salary": 1,
                        "subordinates": []
                    }
                ]
            },
            {
                "first_name": "manager 2",
                "last_name": "",
                "position": "manager 2",
                "salary": 1,
                "subordinates": [
                    {
                        "first_name": "worker 2-1",
                        "last_name": "",
                        "position": "worker 2-1",
                        "salary": 1,
                        "subordinates": []
                    },
                    {
                        "first_name": "worker 2-2",
                        "last_name": "",
                        "position": "worker 2-2",
                        "salary": 1,
                        "subordinates": []
                    }
                ]
            }
        ]
    }
}
)";


using namespace CM;


int main(int argc, char **argv) {
//    World::Ptr world(new World(
//        merge_dicts(builtins, {
//            {"position_title", get_position_title}
//        }), {
//            {"p", Position::NewObject<std::string>("test")}
//        }));
//    set_world(world);
//    Interpreter(world).interactive_loop(std::cin, std::cout);

#define EMPL(fn) Employee::New(mk_string(fn), mk_string(""))
    Employee::Ptr ceo = EMPL("director");
    Employee::Ptr mgr1 = EMPL("manager 1");
    Employee::Ptr mgr2 = EMPL("manager 2");
    Employee::Ptr wrk11 = EMPL("worker 1-1");
    Employee::Ptr wrk12 = EMPL("worker 1-2");
    Employee::Ptr wrk21 = EMPL("worker 2-1");
    Employee::Ptr wrk22 = EMPL("worker 2-2");
#undef EMPL

    Company::Ptr comp = ceo->create_company(mk_string("mycompany"));

    mgr1->employ(ceo, mgr1->get_first_name(), mk_int(1));
    mgr2->employ(ceo, mgr2->get_first_name(), mk_int(2));

    wrk11->employ(mgr1, wrk11->get_first_name(), mk_int(3));
    wrk12->employ(mgr1, wrk12->get_first_name(), mk_int(4));
    wrk21->employ(mgr2, wrk21->get_first_name(), mk_int(5));
    wrk22->employ(mgr2, wrk22->get_first_name(), mk_int(6));

//    CM::DB::save(comp, std::cout << std::setw(4));

}

