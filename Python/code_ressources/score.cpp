
/*
cable_allocation::cable_allocation(const std::set<int>& connections,
    std::shared_ptr<connector> connector)
: _reserved_cavities(connections), _score(0.0)
{
auto adjacency = [&](int idx) 
{
    return connector->get_adjacency_list(idx);
};

std::unordered_set<int> visited;
int connected_components = 0;

for (int i = 0; i < connector->size(); ++i) 
{
    if (_reserved_cavities.count(i)) continue;
    if (connector->get_component(i)->status() != 0) continue;
    if (visited.count(i)) continue;

    // BFS from cavity i
    std::queue<int> q;
    q.push(i);
    visited.insert(i);
    ++connected_components;

    while (!q.empty()) 
    {
        int current = q.front(); q.pop();
        for (int neighbor : adjacency(current)) 
        {
            if (_reserved_cavities.count(neighbor)) continue;
            if (connector->get_component(neighbor)->status() != 0) continue;
            if (visited.insert(neighbor).second) 
                q.push(neighbor);
        }
    }
}

// ---------- Freedom Score ----------
int freedom_loss = 0;
for (int idx : _reserved_cavities) 
{
    for (int neighbor : adjacency(idx)) 
    {
        if (_reserved_cavities.count(neighbor)) continue;
        if (connector->get_component(neighbor)->status() != 0) continue;

        // calculate current freedom Score
        int local_freedom = 0;
        for (int nn : adjacency(neighbor)) 
        {
            if (_reserved_cavities.count(nn)) continue;
            if (connector->get_component(nn)->status() == 0)
            ++local_freedom;
        }

        // freedol score too low
        if (local_freedom <= 1) ++freedom_loss;
    }
}

    _score = -(freedom_loss + 10 * (connected_components - 1));
}*/