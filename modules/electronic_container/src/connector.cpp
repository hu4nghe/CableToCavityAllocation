#include "connector.h"
#include <print>

connector::connector(const std::vector<p_component<cavity>>& cavities):
    electronic_container_base(cavities)
{
    //Calculer la distance entre les cavities, inutile si on connaît déjà ce chiffre.
    for(auto &gauge_type : _container)
    {
        double min_distance = std::numeric_limits<double>::max();
        for(const auto& i : gauge_type.second)
            for(const auto& j : gauge_type.second)
               min_distance = j->distance(*i) < min_distance ? j->distance(*i) : min_distance;

        //Trouver les cavités adjacentes 
        const double epsilon = 0.3 * min_distance;
        for(const auto& i : gauge_type.second)
            for(const auto& j : gauge_type.second)
                if(std::abs(j->distance(*i) - min_distance) < epsilon)
                 _adjacency_list[i->get_ID()].insert(*j);
    }
}

void connector::print_list() const
{
    for(auto& i : _adjacency_list)
    {
        std::print("cavity {} is adjacent to : ",i.first);
        for(auto& j : i.second) 
            std::print("{} ",j.get_ID());
        std::print("\n");
    }
}
