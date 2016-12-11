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
        return unprocessed_cnt > 0 || unprocessed_cnt == -1;
    }
    const Employee::Ptr& BySubordination::next() {
        if (unprocessed_cnt == -1) {
            unprocessed_cnt = int(root->get_subordinates().size());
            st.push({unprocessed_cnt, root});
            return root;
        }
        auto &curr_item = st.top();
        auto& subordinates = curr_item.second->get_subordinates();
        if (curr_item.first > 0) {
            auto& next_empl = subordinates[subordinates.size() - curr_item.first];
            int n_next_from_here = int(next_empl->get_subordinates().size());
            st.push({n_next_from_here, next_empl});
            curr_item.first--;
            unprocessed_cnt += (n_next_from_here - 1);
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

