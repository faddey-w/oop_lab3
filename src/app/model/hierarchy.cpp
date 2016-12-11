#include "hierarchy.h"

namespace CM {
    bool ByLevel::has_next() const {
        return q.size() > 0;
    }
    const Employee::Ptr& ByLevel::next() {
        current_depth = q.front().first;
        current = q.front().second;
        for(const auto& sub : current->get_subordinates()) {
            q.push({current_depth+1, sub});
        }
        q.pop();
        return current;
    }
    const Employee::Ptr& ByLevel::get() const {
        return current;
    }
    int ByLevel::get_depth() const {
        return current_depth;
    }

    bool BySubordination::has_next() const {
        return (st.size() > 0 || !started);
    }
    const Employee::Ptr& BySubordination::next() {
        if (!started) {
            started = true;
            st.push({0, root});
            return root;
        }
        auto &curr_item = st.top();
        if (curr_item.first < curr_item.second->get_subordinates().size()) {
            st.push({0, curr_item.second->get_subordinates()[curr_item.first]});
            curr_item.first++;
            return get();
        } else {
            st.pop();
            return next();
        }
    }
    const Employee::Ptr& BySubordination::get() const {
        return st.top().second;
    }
    int BySubordination::get_depth() const {
        return int(st.size())-1;
    }
}

