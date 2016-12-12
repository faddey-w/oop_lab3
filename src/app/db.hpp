#ifndef LAB3_DB_HPP
#define LAB3_DB_HPP

#include <ios>
#include <json.hpp>
#include "model/Employee.hpp"

using json = nlohmann::json;

namespace CM { namespace DB {

    inline void _hierarchy_to_json(const Employee::Ptr& empl, json& store) {
        store["first_name"] = *empl->get_first_name();
        store["last_name"] = *empl->get_last_name();
        store["position"] = *empl->get_position();
        store["salary"] = *empl->get_salary();
        store["subordinates"] = json::array();
        for(auto& sub: empl->get_subordinates()) {
            json sub_store;
            _hierarchy_to_json(sub, sub_store);
            store["subordinates"] += sub_store;
        }
    }

    inline Employee::Ptr _load_with_subordinates(const Employee::Ptr& supervisor, json& store) {
        auto empl = Employee::New(
            mk_string(store["first_name"].get<std::string>()),
            mk_string(store["last_name"].get<std::string>())
        );
        empl->employ(
            supervisor,
            mk_string(store["position"].get<std::string>()),
            mk_int(store["salary"].get<int>())
        );
        for(auto &sub_store: store["subordinates"]) {
            _load_with_subordinates(empl, sub_store);
        }
        return empl;
    }

    inline void save(const Company::Ptr& company, json& store) {
        store["company_name"] = *company->get_name();
        _hierarchy_to_json(company->get_director(), store["hierarchy"]);
    }

    inline void save(const Company::Ptr& company, std::ostream& stream) {
        json data;
        save(company, data);
        stream << data;
    }

    inline Company::Ptr load(std::istream &stream) {
        json data = json::parse(stream);
        auto ceo = Employee::New(
            mk_string(data["hierarchy"]["first_name"].get<std::string>()),
            mk_string(data["hierarchy"]["last_name"].get<std::string>())
        );
        auto company = ceo->create_company(mk_string(data["company_name"].get<std::string>()));
        ceo->set_salary(mk_int(data["hierarchy"]["salary"].get<int>()));
        for(auto &sub_store: data["hierarchy"]["subordinates"]) {
            _load_with_subordinates(ceo, sub_store);
        }
        return company;
    }

}}

#endif //LAB3_DB_HPP
